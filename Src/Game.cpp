#include "../Headers/Game.h"
#include "../Headers/TextureManager.h"
#include "../Headers/Vector2D.h"
#include "../Headers/CollisionDetection.h"
#include "../Headers/AssetManager.h"
#include "../Components/Components.h"
#include <sstream>

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
int points = 0;
bool restarting = false;

float timeOfRestarting = 0;
float timeBeforeRestarting = 2 * 1000;

Entity* pointDisplayer;

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

	SetupAssets();
	StartGame();
}

void Game::SetupText() 
{
	pointDisplayer = &manager.AddEntity();
	SDL_Color white = { 255,255,255,255 };
	pointDisplayer->AddComponent<UiLabel>(Vector2D(20, 20), "Example", "PixelFont", white);
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
	assets->AddFont("PixelFont", "Assets/Fonts/coure.fon", 32);
}

void Game::StartGame()
{
	SetupText();
	Entity& player1 = manager.AddEntity(); // Create Player Entity
	player1.AddComponent<TransformComponent>(50, 50);
	player1.AddComponent<SpriteComponent>("FriendlyShip");
	player1.AddComponent<KeyboardController>();
	player1.AddComponent<ColliderComponent>(32, 32, "Player");
	player1.AddComponent<PlayerComponent>();

	for (size_t i = 0; i < 3; i++)
	{
		Entity& player2 = (manager.AddEntity());
		player2.AddComponent<TransformComponent>(100 * i, 200);
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
	manager.Refresh();
	manager.Update();
	CollisionDetection();

	std::stringstream ss;
	ss << "Points: " << points;
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

	// Draw the background first so it on the bottom.
	SDL_RenderCopy(Game::renderer, backgroundTexture, &backgroundRect, &backgroundDest);

	// Draw the game content. All entities
	manager.Draw();

	// Draw the text last so it is on top!
	pointDisplayer->Draw();

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
	points += 10;
}

void Game::Restart()
{
	colliders.clear();
	manager.DestroyAllEntities();

	StartGame();
}

void Game::PlayerDied()
{
	if (restarting)
		return;

	std::cout << "Player Died!" << std::endl;
	restarting = true;
	timeOfRestarting = SDL_GetTicks();

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

