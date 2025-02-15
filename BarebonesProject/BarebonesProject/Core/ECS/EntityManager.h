#pragma once

#include "ECS_Types.h"

namespace Barebones
{

	class EntityManager
	{
	public:
		EntityManager()
		{
			// Start from 1, zero is considered a null entity
			mAvailableEntitiesTail = MAX_ENTITIES-1;
			for (unsigned int i = 0; i < MAX_ENTITIES; i++)
			{
				mAvailableEntities[i] = MAX_ENTITIES - i;
			}
		}

		Entity CreateEntity()
		{
			assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence");

			Entity id = mAvailableEntities[mAvailableEntitiesTail--];
			++mLivingEntityCount;
			return id;
		}

		void DestroyEntity(Entity entity)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");

			mSignatures[entity].reset();
			mAvailableEntities[++mAvailableEntitiesTail] = entity;
			--mLivingEntityCount;
		}

		void SetSignature(Entity entity, Signature signature)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");
			mSignatures[entity] = signature;
		}

		Signature GetSignature(Entity entity)
		{
			assert(entity < MAX_ENTITIES && "Entity out of range.");
			return mSignatures[entity];
		}

	private:
		Entity mAvailableEntities[MAX_ENTITIES];
		unsigned int mAvailableEntitiesTail;
		Signature mSignatures[MAX_ENTITIES];
		std::uint32_t mLivingEntityCount{};
	};
}

