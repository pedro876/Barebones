#pragma once

#include <vector>
#include "GameObject.h"+

namespace Barebones
{
	class Scene
	{
	public:
		Scene(const std::string& name);
		~Scene();
		const std::string& GetName() const;
		void AddGameObject(GameObject* gameObject);
		void RemoveGameObject(GameObject* gameObject);
	private:
		std::string name;
		std::vector<GameObject> gameObjects;
	};
}

