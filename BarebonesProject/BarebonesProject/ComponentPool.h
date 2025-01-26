#pragma once

#include <concepts>
#include "Component.h"
#include "Transform.h"
#include <vector>

namespace Barebones
{
    /// <summary>
    /// The provided type must be derived from Component.
    /// </summary>
    template<typename T>
    concept SpecificComponent = std::is_base_of_v<Component, T> && !std::same_as<T, Component>;

    /// <summary>
    /// Transform is a mandatory component for a gameObject, so the provided 
    /// type must be a specific component and different from Transform.
    /// </summary>
    template<typename T>
    concept OptionalComponent = SpecificComponent<T> && !std::same_as<T, Transform>;

    class GameObject;

	template <SpecificComponent T>
	class ComponentPool
	{
    public:
        friend class GameObject;

        static const std::vector<T>& GetComponents()
        { 
            return components;
        }

        static int GetActiveCount()
        {
            return activeCount;
        }
    private:
        static T* CreateComponent(GameObject* gameObject)
        {
            components.emplace_back();
            T* component = &components[activeCount];
            component->poolIndex = activeCount;
            component->gameObject = gameObject;
            activeCount++;
            return component;
        }

        static void DestroyComponent(T* component)
        {
            component->gameObject = nullptr;
            int indexToRemove = component->poolIndex;
            activeCount--;
            if (activeCount > 0)
            {
                std::swap(components[indexToRemove], components[activeCount]);
                components[indexToRemove].poolIndex = indexToRemove;
                //TODO: This will invalidate the stored pointer in the swapped gameObject to its component
            }
        }

        static unsigned int activeCount;
        static std::vector<T> components;
	};


    // Define static member
    template <SpecificComponent T>
    std::vector<T> ComponentPool<T>::components;

    template<SpecificComponent T>
    unsigned int ComponentPool<T>::activeCount = 0;
}