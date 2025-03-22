#pragma once

#include "ECS_Types.h"
#include <set>

namespace Barebones
{
	class System
	{
	public:
		friend class SystemManager;
	protected:
		std::set<Entity> mEntities;
	private:
		virtual void EntityDestroyed(Entity entity) = 0;
		virtual Signature CreateSignature() = 0;
		Signature signature = 0;
	};

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();
			assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			system->signature = system->CreateSignature();

			return system;
		}

		void EntityDestroyed(Entity entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;
				if (system->mEntities.erase(entity))
				{
					system->EntityDestroyed(entity);
				}
			}
		}

		void EntitySignatureChanged(Entity entity, Signature entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = system->signature;

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->mEntities.insert(entity);
				}
				else
				{
					system->mEntities.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
	};
}