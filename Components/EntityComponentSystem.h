#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
	// This will iterate every time it is called. So each has a unique ID.
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept 
{
	static ComponentID typeID = GetComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>; // Active components
using ComponentArray  = std::array<Component*, maxComponents>; // All possible components.

// Adds extra functionality to an entity.
class Component 
{
public:
	Entity* entity;
	virtual void Init(){}
	virtual void Update(){}
	virtual void Draw(){}
	virtual ~Component(){}
};

// Manages all components on an object in the game.
class Entity 
{
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
public:
	void Update()
	{
		// Update the components of this entity.
		for (auto& c : components) { c->Update(); }
		
	}
	void Draw() 
	{
		for (auto& c : components) { c->Draw(); }
	}
	bool IsActive() const{ return active; }
	void Destroy() { active = false; }

	template <typename T> bool HasComponent() const 
	{
		// Check if the entity has a component of the type T.
		return componentBitSet[GetComponentTypeID<T>];
	}

	template <typename T, typename... TArgs>
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& GetComponent() const 
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr); // Allows you to continue after get.
	}
};

// Manages all entities in the game. 
class Manager 
{
private:
	std::vector<std::unique_ptr<Entity>> entities; // All entities in the game. Such as car or player.

public:
	void Update() 
	{
		// Update all entities
		for (auto& e : entities)
			e->Update();
	}
	void Draw() 
	{
		// Draw all entities
		for (auto& e : entities)
			e->Draw();
	}
	void Refresh() 
	{
		// Erase all entities that are inactive.
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->IsActive();
			}),
			std::end(entities));
	}
	Entity& AddEntity() 
	{
		Entity* e = new Entity(); // Create new entity.
		std::unique_ptr<Entity> uPtr{ e }; // Pointer to new entity
		entities.emplace_back(std::move(uPtr)); // Add new entity to the list of  entities.
		return *e;
	}
};