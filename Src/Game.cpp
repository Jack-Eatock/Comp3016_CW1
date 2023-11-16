#include "../Headers/Game.h"
#include "../Headers/TextureManager.h"
#include "../Headers/Vector2D.h"
#include "../Headers/CollisionDetection.h"
#include "../Headers/AssetManager.h"
#include "../Components/Components.h"
#include <sstream>
#include <random>
#include "../Headers/DataManager.h"

Manager manager;
DataManager dataManager;
Game* Game::Instance;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Surface* backgroundSurface;
SDL_Texture* backgroundTexture;
SDL_Rect backgroundRect, backgroundDest;

// Current Playthrough
bool restarting = false;
float timeOfRestarting = 0;
float timeBeforeRestarting = 2 * 1000;

// Frequently used Entities. Easier to have a direct reference to them.
Entity* Player;
Entity* pointDisplayer;
Entity* storyDisplayer;
Entity* storyDisplayer2;
Entity* storyDisplayer3;

// Required
std::random_device seed;
bool menuScreen = true;
bool intro = true;
std::stringstream ss, ss2, ss3;

// Current game stats
int phase = 6;
int introPhase = 0;
int shipsDestroyed = 0;
std::string characterName = "Name";
std::string lastCharacterName = "";
bool progressedPhase = false;
bool captainKIA = false;
float timeOfLastInput = 0;

Game::Game() {};
Game::~Game() {}

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	Game::Instance = this;

	int flags = 0;
	if (fullscreen) 
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initiated!" << std::endl;

		// Create Window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window created!" << std::endl;

		// Create Renderer
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) 
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		// Run the 
		isRunning = true;
	}
	else
		std::cout << "[ERROR] Subsystems failed to Initialise!" << std::endl;

	if (TTF_Init() == -1)
		std::cout << "[ERROR] TTF failed to Initialise!" << std::endl;
	else
		std::cout << "TTF Initialised!" << std::endl;

	intro = true;
	menuScreen = true;
	SetupAssets();
	NewCharacter();
	StartGame();
}

/// <summary>
/// Sets up the text displayers so that they can be used to show information throughout the programme.
/// </summary>
void Game::SetupText() 
{
	pointDisplayer = &manager.AddEntity();
	SDL_Color white = { 255,255,255,255 };
	pointDisplayer->AddComponent<UiLabel>(Vector2D(20, 20), "Example", "PixelFont", white, 200, false);

	storyDisplayer = &manager.AddEntity();
	storyDisplayer->AddComponent<UiLabel>(Vector2D(WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2), "Example", "PixelFontBig", white, 800);
	storyDisplayer->drawFromManager = false;

	storyDisplayer2 = &manager.AddEntity();
	storyDisplayer2->AddComponent<UiLabel>(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100 ), "Bottom", "PixelFontBig", white, 800);
	storyDisplayer2->drawFromManager = false;

	storyDisplayer3 = &manager.AddEntity();
	storyDisplayer3->AddComponent<UiLabel>(Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100), "Top", "PixelFontBig", white, 800);
	storyDisplayer3->drawFromManager = false;
}

/// <summary>
/// Loads assets. Textfiles, Images and fonts from the assets folder into the programme.
/// </summary>
void Game::SetupAssets()
{
	// Friendly Ship
	assets->AddTexture("FriendlyShip", "Assets/FriendlyShip/FriendlyShip.png");
	assets->AddTexture("FriendlyShip_DMG1", "Assets/FriendlyShip/FriendlyShip_DMG1.png");
	assets->AddTexture("FriendlyShip_DMG2", "Assets/FriendlyShip/FriendlyShip_DMG2.png");
	assets->AddTexture("FriendlyShip_DMG3", "Assets/FriendlyShip/FriendlyShip_DMG3.png");

	// Enemy Ship
	assets->AddTexture("EnemyShip", "Assets/EnemyShip/EnemyShip.png");
	assets->AddTexture("EnemyShip_DMG1", "Assets/EnemyShip/EnemyShip_DMG1.png");
	assets->AddTexture("EnemyShip_DMG2", "Assets/EnemyShip/EnemyShip_DMG2.png");
	assets->AddTexture("EnemyShip_DMG3", "Assets/EnemyShip/EnemyShip_DMG3.png");

	// Projectiles
	assets->AddTexture("Bullet", "Assets/FriendlyBullet.png");
	assets->AddTexture("EnemyBullet", "Assets/EnemyBullet.png");

	// Background
	backgroundTexture = TextureManager::LoadTexture("Assets/Background.png");
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = WINDOW_WIDTH;
	backgroundRect.h = WINDOW_HEIGHT;
	backgroundDest.w = backgroundRect.w;
	backgroundDest.h = backgroundRect.h;

	// Point displayer
	assets->AddFont("PixelFont", "Assets/Fonts/vgafix.fon", 72);
	assets->AddFont("PixelFontBig", "Assets/Fonts/vgafix.fon", 72);

	// Read text files
	dataManager.GetNames();
	dataManager.GetPhasesStory();
	dataManager.GetIntroStory();
}

void Game::StartGame()
{
	SetupText();
	menuScreen = true;
}

/// <summary>
/// Starts the next wave.
/// Reset's game stats, spawns the player and x number of enemies. 
/// </summary>
void Game::StartNextWave()
{
	progressedPhase = false;
	captainKIA = false;

	Player = &manager.AddEntity(); // Create Player Entity
	Player->AddComponent<TransformComponent>(WINDOW_WIDTH/2 - 32, WINDOW_HEIGHT/2 -32);
	Player->AddComponent<SpriteComponent>("FriendlyShip");
	Player->AddComponent<KeyboardController>();
	Player->AddComponent<ColliderComponent>(32, 32, "Player");
	Player->AddComponent<PlayerComponent>();

	for (size_t i = 0; i < phase; i++)
	{
		std::mt19937 gen{ seed() }; // seed the generator

		std::uniform_int_distribution<> dist{ 30, WINDOW_WIDTH - 30 };
		int randX = dist(gen);

		std::uniform_int_distribution<> dist2{ 30, WINDOW_HEIGHT - 30 };
		int randY = dist2(gen);

		Entity& player2 = (manager.AddEntity());
		player2.AddComponent<TransformComponent>(randX, randY);
		player2.AddComponent<SpriteComponent>("EnemyShip");
		player2.AddComponent<ColliderComponent>(32, 32, "Enemy");
		player2.AddComponent<EnemyComponent>();
	}
}

/// <summary>
/// Listens to input events and stores them locally to be used throughout the game.
/// </summary>
void Game::HandleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			std::cout << "Input Registered: 'Quit' " << std::endl;
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::Update()
{
	// Clear all string streams.
	std::stringstream tmp1;
	ss.swap(tmp1);
	std::stringstream tmp2;
	ss2.swap(tmp2);
	std::stringstream tmp3;
	ss3.swap(tmp3);

	if (intro)
		IntroUpdate();

	else if (menuScreen)
		MenuUpdate();

	else
		GameUpdate();
}

/// <summary>
/// If we are displaying a menu, this update will be called every frame to react to the player inputs.
/// </summary>
void Game::MenuUpdate()
{
	// They have won the game!
	if (phase == 8)
	{
		// They survived all phases
		ss3 << characterName << " having survived for over a week, was met by the Federation's fleet";
		ss << "So yes.. I lied. Not all humans were eradicated by the 'Gruk'. " << characterName << " survived to tell the tale";
		ss2 << "Thank you for playing.";

		storyDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFontBig");
		storyDisplayer2->GetComponent<UiLabel>().SetLabelText(ss2.str(), "PixelFontBig");
		storyDisplayer3->GetComponent<UiLabel>().SetLabelText(ss3.str(), "PixelFontBig");

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				if (SDL_GetTicks() - timeOfLastInput > .5f * 1000)
					Clean();
			}
		}
		return;
	}

	// Display the current phase and any other information. Allow for them to press space to initate the next wave/phase.

	// Top text
	if (captainKIA)
		ss3 << lastCharacterName << " was lost in battle. ";
	else if (progressedPhase)
		ss3 << characterName << " progresses to the next day!";
	else if (phase == 1)
		ss3 << "Controls: WASD to move your ship, Left shift to boost and Left Click to fire!";
	else
		ss3 << "";

	// Bottom Text
	ss2 << "Press [Space] to play!";

	// Mid Text
	std::string phaseNote = "Error";
	try
	{
		phaseNote = dataManager.PhasesLines[phase-1];
	}
	catch (const std::exception&)
	{

	}
	ss << "[June " << (24 + phase - 1) << "] " << characterName << "'s perspective: " << phaseNote << "'" << std::endl;
	storyDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFontBig");
	storyDisplayer2->GetComponent<UiLabel>().SetLabelText(ss2.str(), "PixelFontBig");
	storyDisplayer3->GetComponent<UiLabel>().SetLabelText(ss3.str(), "PixelFontBig");
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (SDL_GetTicks() - timeOfLastInput > .5f * 1000)
			{
				timeOfLastInput = SDL_GetTicks();
				menuScreen = false;
				intro = false;
				Render();
				StartNextWave();
			}
		}
	}
}

/// <summary>
/// Currently displaying the introduction to the game. This is called every frame during the intro
/// allowing for the game to react to the players inputs.
/// </summary>
void Game::IntroUpdate()
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (SDL_GetTicks() - timeOfLastInput > .5f * 1000)
			{
				introPhase++;
				timeOfLastInput = SDL_GetTicks();
			}
		}
	}

	// Bottom text
	ss2 << "Press [Space] to continue";

	// Top text
	ss3 << "The Resiliance of Mankind";
	
	if (introPhase == 9)
	{
		intro = false;
	}
	else 
	{
		std::string textToDisplay = "";
		try
		{
			// Displays the intro lines, grabbed from the intro lines text folder.
			textToDisplay = dataManager.IntroLines[introPhase];
		}
		catch (const std::exception&)
		{
			std::cout << "[ERROR] Failed to parse intro line " << introPhase;
		}
		ss << textToDisplay;
	}
	
	storyDisplayer3->GetComponent<UiLabel>().SetLabelText(ss3.str(), "PixelFontBig");
	storyDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFontBig");
	storyDisplayer2->GetComponent<UiLabel>().SetLabelText(ss2.str(), "PixelFontBig");
}

/// <summary>
/// When the game is in game state. Iterates over all entities updating their components. They then react accordingly.
/// Updates the objects in the game.
/// </summary>
void Game::GameUpdate()
{
	manager.Refresh();
	manager.Update();
	CollisionDetection();

	ss << "Day: " << 24 + phase - 1 << "/16/2168";
	pointDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFont");

	// Are we restarting?
	if (restarting)
	{
		if (SDL_GetTicks() - timeOfRestarting > timeBeforeRestarting)
		{
			restarting = false;
			Restart();
		}
	}
}

/// <summary>
/// In game mode, it loops over every entity rendering their content.
/// In menu mode, it displays the appropriate text.
/// </summary>
void Game::Render()
{
	SDL_RenderClear(renderer);

	if (menuScreen)
	{
		storyDisplayer->Draw();
		storyDisplayer2->Draw();
		storyDisplayer3->Draw();
	}

	else
	{
		// Draw the background first so it on the bottom.
		SDL_RenderCopy(Game::renderer, backgroundTexture, &backgroundRect, &backgroundDest);

		// Draw the game content. All entities
		manager.Draw();

		// Draw the text last so it is on top!
		pointDisplayer->Draw();
	}

	SDL_RenderPresent(renderer);
}

/// <summary>
/// Clean up SDL rendering
/// </summary>
void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned " << std::endl;
}

/// <summary>
/// The player destroyed an enemy ship. Check if they are all destroyed.
/// if so, move to the next wave.
/// </summary>
void Game::PlayerDestroyedAShip()
{
	if (restarting)
		return;

	shipsDestroyed++;

	if (shipsDestroyed == phase)
	{
		// Wave complete.
		Player->GetComponent<PlayerComponent>().destroyed = true;
		phase++;
		progressedPhase = true;
		restarting = true;
		timeOfRestarting = SDL_GetTicks();
	}
}

/// <summary>
/// Reset all entities and start the current wave from fresh.
/// </summary>
void Game::Restart()
{
	shipsDestroyed = 0;
	colliders.clear();
	manager.DestroyAllEntities();
	StartGame();
}

/// <summary>
/// The player has died. Restart the current wave.
/// </summary>
void Game::PlayerDied()
{
	if (restarting)
		return;

	NewCharacter();
	std::cout << "Player Died!" << std::endl;
	captainKIA = true;
	restarting = true;
	timeOfRestarting = SDL_GetTicks();
}

/// <summary>
/// Grab a newly generate character name. And set the old one to last.
/// </summary>
void Game::NewCharacter()
{
	lastCharacterName = characterName;
	std::mt19937 gen{ seed() }; // seed the generator
	std::uniform_int_distribution<> dist{ 0, (int)dataManager.Names.size() -1};
	int randIndex = dist(gen);
	try
	{
		characterName = dataManager.Names[randIndex];
		if (characterName == lastCharacterName) {
			NewCharacter();
			return;
		}
			
		std::cout << "New character:"  << characterName  << randIndex << std::endl;
	}
	catch (const std::exception&)
	{
		std::cout << "[ERROR] failed to parse in name index " << randIndex << std::endl;
	}
	
}

/// <summary>
/// Check all entities for collisions.
/// </summary>
void Game::CollisionDetection()
{
	for (auto colider : Game::colliders)
	{
		for (auto colider2 : Game::colliders)
		{
			if (colider == colider2)
				continue;

			CollisionDetection::RectCollision_AABB(*colider, *colider2);
		}
	}
}

