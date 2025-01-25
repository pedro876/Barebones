#include "Scene.h"

#include <stdexcept>

namespace Barebones
{
	Scene::Scene(const std::string& name) : name(name)
	{
		
	}

	Scene::~Scene()
	{
		
	}

	const std::string& Scene::GetName() const
	{
		return name;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		throw std::runtime_error("not implemented");
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		throw std::runtime_error("not implemented");
	}
}