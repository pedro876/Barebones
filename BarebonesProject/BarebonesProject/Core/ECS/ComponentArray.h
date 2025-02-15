#pragma once

#include "ECS_Types.h"

namespace Barebones
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(Entity entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		ComponentArray()
		{
			for (Entity i = 0; i < MAX_ENTITIES; i++)
			{
				mEntityToIndexMap[i] = -1;
				mIndexToEntityMap[i] = 0;
			}
			mSize = 0;
		}

		void InsertData(Entity entity, T component)
		{
			//assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");
			assert(mEntityToIndexMap[entity] < 0 && "Component added to same entity more than once.");

			unsigned int newIndex = mSize;
			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;
			mComponentArray[newIndex] = component;
			++mSize;
		}

		void RemoveData(Entity entity)
		{
			//assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");
			assert(mEntityToIndexMap[entity] >= 0 && "Removing non-existent component.");

			unsigned int indexOfRemovedEntity = mEntityToIndexMap[entity];
			unsigned int indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			mEntityToIndexMap[entity] = -1;
			mIndexToEntityMap[indexOfLastElement] = 0;
			/*mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);*/

			--mSize;
		}

		T& GetData(Entity entity)
		{
			//assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");
			assert(mEntityToIndexMap[entity] >= 0 && "Retrieving non-existent component.");

			return mComponentArray[mEntityToIndexMap[entity]];
		}

		void EntityDestroyed(Entity entity) override
		{
			if (mEntityToIndexMap[entity] >= 0) RemoveData(entity);
			//if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) //TODO: Maybe this check shouldn't be executed, and instead allow the program to fail.
			//{
			//	RemoveData(entity);
			//}
		}

	private:
		T mComponentArray[MAX_ENTITIES];
		int mEntityToIndexMap[MAX_ENTITIES];
		Entity mIndexToEntityMap[MAX_ENTITIES];
		/*std::array<T, MAX_ENTITIES> mComponentArray;
		std::unordered_map<Entity, size_t> mEntityToIndexMap;
		std::unordered_map<size_t, Entity> mIndexToEntityMap;*/
		unsigned int mSize;
	};
}