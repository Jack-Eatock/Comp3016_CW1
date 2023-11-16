#include "../Headers/Game.h"
#include "../Headers/TextureManager.h"
#include "../Headers/Vector2D.h"
#include "../Headers/CollisionDetection.h"
#include "../Headers/AssetManager.h"
#include "../Components/Components.h"
#include <sstream>
#include <random>

Manager manager;
Game* Game::Instance;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;
AssetManager* Game::assets = new AssetManager(&manager);
SDL_Surface* backgroundSurface;
SDL_Texture* backgroundTexture;
SDL_Rect backgroundRect, backgroundDest;
Game::Game() {};
Game::~Game() {}

// Current Playthrough
bool restarting = false;
float timeOfRestarting = 0;
float timeBeforeRestarting = 2 * 1000;

Entity* Player;
Entity* pointDisplayer;
Entity* storyDisplayer;
Entity* storyDisplayer2;
Entity* storyDisplayer3;

std::random_device seed;
bool menuScreen = true;
bool intro = true;
int phase = 1;
int introPhase = -1;
int shipsDestroyed = 0;
std::string characterName = "Captain Cheggs";
std::string lastCharacterName = "";
bool progressedPhase = false;
bool captainKIA = false;
std::stringstream ss, ss2, ss3;
float timeOfLastInput = 0;

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
	StartGame();
}

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
}

void Game::StartGame()
{
	SetupText();
	menuScreen = true;
}

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
	{
		IntroUpdate();
		return;
	}

	else if (menuScreen)
		MenuUpdate();

	else
		GameUpdate();
}

void Game::MenuUpdate()
{
	// Top text
	if (captainKIA)
		ss3 << lastCharacterName << " was lost in battle. ";
	else if (progressedPhase)
		ss3 << characterName << " progresses to the next day!";
	else
		ss3 << "";

	// Bottom Text
	ss2 << "Press [Space] to play!";

	// Mid Text
	ss << "[June " << (24 + phase - 1) << "] " << characterName << "'s perspective." << std::endl;

	storyDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFontBig");
	storyDisplayer2->GetComponent<UiLabel>().SetLabelText(ss2.str(), "PixelFontBig");
	storyDisplayer3->GetComponent<UiLabel>().SetLabelText(ss3.str(), "PixelFontBig");

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			menuScreen = false;
			intro = false;
			Render();
			StartNextWave();
		}
	}
}

void Game::IntroUpdate()
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			if (SDL_GetTicks() - timeOfLastInput > 1 * 1000)
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

	if (introPhase == -1)
		ss << "This story is told by 'Jerlich', a father from the species 'Jerayah' " << std::endl;

	if (introPhase == 0)
		ss << "'Happy rememberance day son! Ah what a great day. Actually.. now I think of it, i've never told you the reason for why we celebrate it so highly!'" << std::endl;

	else if (introPhase == 1)
		ss << "'It marks the day, centuries ago, that the federation was finally able to eradicate the 'Gurk' horde'";

	else if (introPhase == 2)
		ss << "'But more importantly, it honours the great sacrafice a species known as the 'Human Kind' gifted us. ";

	else if (introPhase == 3)
		ss << "'Before life was even able to comprehend the horrors of the 'Gurk's existence. The human's were the most powerfull species known. They boasted a fleet larger than three species combined and an economy twice as strong as the next highest! To be honest, at that time they were not the most.. liked, with their unusual culture and concerning urge to expand at a rapid rate.";

	else if (introPhase == 4)
		ss << "'On the 18th of June in the year 2168, all comms to earth, their capital, and various other planets and ships were lost in a matter of hours.' ";

	else if (introPhase == 5)
		ss << "'At the time we were confused in why the humans had suddenly gone so quiet. They were usually bothering us 24/7 on crazy things like.. ugh 'Recycling' and other rubbish. No pun intended.' ";

	else if (introPhase == 6)
		ss << "'22nd of June, an entire 4 days later, we finally recieved communication from the Humans. Only one string of text was recieved, that went as follows: '22/06/2168. All Human occupied planets have been invaded simultaneously. Zero succesfull resistances, survivors are being evacuated. The fleet has suffered excruciating loses. Their armour appears inpenetrable.' - President Eatock of Earth  ";

	else if (introPhase == 7)
		ss << "'Which was later followed by '24/06/2168. The enemies armour is immune to all energy weapons, however kinetic works efficiently. We have lost over 70% of our fleet and all occupied territories. They appear to have made every planet inhabitable, destroying most. We are unsure why they are here, but are certain their only purpose is to devour everything in their path. We, the remaining Human resistance shall hold the borders to the last being. We will not let this infection spread out of our teritory. The kinetic weapon discovery will give us a fighting chance, but not enough to win. Use the time we give you to build a fleet and destroy this threat. We pray for you all. - Commander Jefferson. ' ";

	else if (introPhase == 8)
		ss << "'They did exactly as they said. They held those borders to the very last ship. Here, let me read some of the logs from some commanders who were apart of the Human resistance..'";

	else if (introPhase == 9)
	{
		intro = false;
	}
	
	storyDisplayer3->GetComponent<UiLabel>().SetLabelText(ss3.str(), "PixelFontBig");
	storyDisplayer->GetComponent<UiLabel>().SetLabelText(ss.str(), "PixelFontBig");
	storyDisplayer2->GetComponent<UiLabel>().SetLabelText(ss2.str(), "PixelFontBig");
}

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

void Game::Clean() 
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned " << std::endl;
}

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

void Game::Restart()
{
	shipsDestroyed = 0;
	colliders.clear();
	manager.DestroyAllEntities();
	StartGame();
}

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

void Game::NewCharacter()
{
	lastCharacterName = characterName;
	characterName = "aa";
}

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

