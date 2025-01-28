#pragma once

#include <concepts>
#include "Component.h"
#include "Transform.h"
#include <vector>
#include <unordered_map>

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

        static T& GetComponent(int handle)
        {
            size_t index = handleToIndex[handle];
            return components[index];
        }

        static int CreateComponent(GameObject* gameObject)
        {
            components.emplace_back();
            T* component = &components[activeCount];
            component->handle = activeCount;
            handleToIndex[activeCount] = activeCount;
            component->gameObject = gameObject;
            activeCount++;
            return activeCount;
        }

        static void DestroyComponent(int handle)
        {
            size_t index = handleToIndex[handle];
            activeCount--;
            std::swap(components[index], components[activeCount]);
            components.pop_back();
            handleToIndex[components[index].handle] = index;

            //component->gameObject = nullptr;
            //int indexToRemove = component->poolIndex;
            //activeCount--;
            //if (activeCount > 0)
            //{
            //    std::swap(components[indexToRemove], components[activeCount]);
            //    components[indexToRemove].poolIndex = indexToRemove;
            //    //TODO: This will invalidate the stored pointer in the swapped gameObject to its component
            //}
        }

        static unsigned int activeCount;
        static std::vector<T> components;

        static std::unordered_map<int, size_t> handleToIndex;
	};


    // Define static member
    template <SpecificComponent T>
    std::vector<T> ComponentPool<T>::components;

    template<SpecificComponent T>
    unsigned int ComponentPool<T>::activeCount = 0;

    template<SpecificComponent T>
    std::unordered_map<int, size_t> ComponentPool<T>::handleToIndex;
}