#pragma once
//https://austinmorlan.com/posts/entity_component_system/

#include "ECS_Types.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace Barebones
{
	class Coordinator
	{
	public:
		Coordinator() = delete;
		Coordinator(const Coordinator&) = delete;
		Coordinator& operator=(const Coordinator&) = delete;
		Coordinator(Coordinator&&) = delete;
		Coordinator& operator=(Coordinator&&) = delete;

		static Entity CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}
		static void DestroyEntity(Entity entity)
		{
			mEntityManager->DestroyEntity(entity);
			mComponentManager->EntityDestroyed(entity);
			mSystemManager->EntityDestroyed(entity);
		}

		template<typename T>
		static void RegisterComponent()
		{
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		static void AddComponent(Entity entity, T component)
		{
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		static void RemoveComponent(Entity entity)
		{
			mComponentManager->RemoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		static T& GetComponent(Entity entity)
		{
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		static ComponentType GetComponentType()
		{
			return mComponentManager->GetComponentType<T>();
		}


		// System methods
		template<typename T>
		static std::shared_ptr<T> RegisterSystem()
		{
			return mSystemManager->RegisterSystem<T>();
		}

		template<typename T>
		static void SetSystemSignature(Signature signature)
		{
			mSystemManager->SetSignature<T>(signature);
		}
	private:
		static inline std::unique_ptr<ComponentManager> mComponentManager = std::make_unique<ComponentManager>();
		static inline std::unique_ptr<EntityManager> mEntityManager = std::make_unique<EntityManager>();
		static inline std::unique_ptr<SystemManager> mSystemManager = std::make_unique<SystemManager>();
	};
}
