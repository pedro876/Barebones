#include "GameObject.h"
#include "Transform.h"

namespace Barebones
{
	int GameObject::s_id = 0;

	GameObject::GameObject(const std::string& name) :
		Object(name)
	{
		this->id = GameObject::s_id++;
		this->components = std::vector<Component*>();
		this->transform = Transform();
		this->transform.gameObject = this;
		this->components.push_back(&this->transform);
	}

	int GameObject::GetID()
	{
		return this->id;
	}

	Component* GameObject::AddComponent(Component* component)
	{
		if (component->gameObject != nullptr)
		{
			component->gameObject->RemoveComponent(component);
		}

		component->gameObject = this;
		this->components.push_back(component);

		return component;
	}

	bool GameObject::RemoveComponent(Component* component)
	{
		int size = components.size();
		for (int i = 0; i < size; i++)
		{
			if (components[i] == component)
			{
				delete component;

				if (size > 1)
				{
					components[i] = components[size - 1];
				}

				components.pop_back();

				return true;
			}
		}
		return false;
	}


	std::ostream& operator<<(std::ostream& os, const GameObject& b)
	{
		os << "GameObject_" << b.id << "_" << b.GetName();
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const GameObject* b)
	{
		os << *b;
		return os;
	}
}

