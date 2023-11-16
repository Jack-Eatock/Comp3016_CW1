#include "../Headers/AssetManager.h"
#include "../Components/Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{

}

AssetManager::~AssetManager()
{

}

/// <summary>
/// Spawns and fires a bullet in the set direction.
/// </summary>
/// <param name="startPos"> The position to spawn the bullet</param>
/// <param name="range">How far can this bullet go?</param>
/// <param name="speed">How fast is the bullet</param>
/// <param name="spriteId">What texture should the bullet have</param>
/// <param name="colliderId">What is the id of the collider? Such as enemy or friendly</param>
/// <param name="direction">What direction should it fire?</param>
void AssetManager::SpawnBullet(Vector2D startPos, int range, int speed, std::string spriteId, std::string colliderId, Vector2D direction)
{
	std::cout << "Game Cleaned " << std::endl;
	auto& bullet(manager->AddEntity());
	bullet.AddComponent<TransformComponent>().Position = startPos;
	bullet.AddComponent<SpriteComponent>(spriteId);
	bullet.AddComponent<BulletComponent>(range, speed, direction);
	bullet.AddComponent<ColliderComponent>(15, 15, colliderId);
}

/// <summary>
/// Loads and stores a reference to a texture for easy use.
/// </summary>
/// <param name="id">The id to give the texture</param>
/// <param name="path">The path to the asset to load</param>
void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

/// <summary>
/// Grabs a loaded texture by its id.
/// </summary>
SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

/// <summary>
/// Loads a font to be used when writing text.
/// </summary>
void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fonts[id];
}

