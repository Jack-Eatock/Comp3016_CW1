#include "../Headers/AssetManager.h"
#include "../Components/Components.h"

AssetManager::AssetManager(Manager* manager) : manager(manager)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::SpawnBullet(Vector2D startPos, int range, int speed, std::string spriteId, std::string colliderId, Vector2D direction)
{
	std::cout << "Game Cleaned " << std::endl;
	auto& bullet(manager->AddEntity());
	bullet.AddComponent<TransformComponent>().Position = startPos;
	bullet.AddComponent<SpriteComponent>(spriteId);
	bullet.AddComponent<BulletComponent>(range, speed, direction);
	bullet.AddComponent<ColliderComponent>(15, 15, colliderId);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

