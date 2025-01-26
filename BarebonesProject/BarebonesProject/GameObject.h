#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Object.h"
#include "ComponentPool.h"

namespace Barebones
{


    /// <summary>
    /// A GameObject is a collection of components that define an entity and its behaviour.
    /// When created, it automatically gets a transform component as this is mandatory.
    /// </summary>
    class GameObject : public Object
    {
    public:
        Transform* transform;

        GameObject(const std::string& name);

        /// <summary>
        /// Each GameObject instantiated has a unique id corresponding to an incremental static 
        /// count that starts from zero.
        /// </summary>
        /// <returns>The gameObject's unique id.</returns>
        int GetID();

        /// <summary>
        /// Linear search of all components looking for the specified type with O(N) complexity.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns>The first component whose type matches the specified one.</returns>
        template <SpecificComponent T>
        T* GetComponent();

        /// <summary>
        /// Instantiates and adds a new component of the specified type to the gameObject with O(1) complexity.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns>The newly instantiated component.</returns>
        template <OptionalComponent T>
        T* AddComponent();

        /// <summary>
        /// Adds a component to the gameObject with O(1) complexity.
        /// If the provided component already belonged to another GameObject,
        /// it is first removed from its original GameObject.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns>The added component.</returns>
        //Component* AddComponent(Component* component);

        /// <summary>
        /// Removes a component given its type with O(N) complexity. The internal order of the components
        /// will vary after this operation.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns>True if the component was found and removed.</returns>
        template<OptionalComponent T>
        bool RemoveComponent();

        /// <summary>
        /// Removes a component given its instance with O(N) complexity. The internal order of the components
        /// will vary after this operation.
        /// </summary>
        /// <param name="component"></param>
        /// <returns>True if the component was found and removed.</returns>
        //bool RemoveComponent(Component* component);

        friend std::ostream& operator<<(std::ostream& os, const GameObject& b);
        friend std::ostream& operator<<(std::ostream& os, const GameObject* b);

    private:
        static int s_id;
        int id;
        std::vector<Component*> components;
    };


    template<SpecificComponent T>
    T* GameObject::GetComponent()
    {
        for (auto& component : components)
        {
            // Attempt to cast the component to the requested type
            T* typedComponent = dynamic_cast<T*>(component);
            if (typedComponent)
            {
                return typedComponent; // Return the matching component
            }
        }
        return nullptr; // If no matching component is found
    }

    template<OptionalComponent T>
    T* GameObject::AddComponent()
    {
        T* instance = ComponentPool<T>::CreateComponent(this);
        this->components.push_back(instance);
        return instance;
    }

    template<OptionalComponent T>
    bool GameObject::RemoveComponent()
    {
        T* component = GetComponent<T>();
        if (component != nullptr)
        {
            ComponentPool<T>::DestroyComponent(component);
            return true;
        }
        return false;
    }

}

