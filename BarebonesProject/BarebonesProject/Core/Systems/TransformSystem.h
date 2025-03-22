#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

namespace Barebones
{
	class TransformSystem : public System
	{
	public:
		Signature CreateSignature() override
		{
			Signature s;
			s.set(Coordinator::GetComponentType<Transform>());
			return s;
		}

		void Update()
		{
			for (auto& entity : mEntities)
			{
				auto& transform = Coordinator::GetComponent<Transform>(entity);
				//transform.localToWorld = transform.GetLocalToParentMatrix();
				if (transform.parent) continue;
				UpdateTransformMatricesRecursively(transform);
			}
		}

		void EntityDestroyed(Entity entity) override
		{
			Transform& transform = Coordinator::GetComponent<Transform>(entity);
			Entity child = transform.firstChild;
			while (child)
			{
				Entity next = Coordinator::GetComponent<Transform>(child).nextSibling;
				Coordinator::DestroyEntity(child);
				child = next;
			}

			if (transform.parent)
			{
				RemoveChild(transform.parent, entity);
			}
		}

		static bool IsChildOf(Entity parent, Entity child)
		{
			auto& tChild = Coordinator::GetComponent<Transform>(child);
			return tChild.parent == parent;
		}

		static unsigned int GetSiblingIndex(Entity entity)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			unsigned int siblingIndex = 0;
			while (transform.prevSibling)
			{
				transform = Coordinator::GetComponent<Transform>(transform.prevSibling);
				siblingIndex++;
			}
			return siblingIndex;
		}

		static Entity GetChildAt(Entity entity, unsigned int index)
		{
			Transform* transform = &Coordinator::GetComponent<Transform>(entity);
			if (index < 0 || index >= transform->children) return 0;

			Entity child = transform->firstChild;
			if (index == 0) return child;
			transform = &Coordinator::GetComponent<Transform>(child);
			for (unsigned int i = 0; i < index && transform->nextSibling; i++)
			{
				child = transform->nextSibling;
				transform = &Coordinator::GetComponent<Transform>(child);
			}

			return child;
		}

		static Entity GetFirstChild(Entity entity)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			return transform.firstChild;
		}

		static Entity GetLastChild(Entity entity)
		{
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			return GetChildAt(entity, transform.children - 1);
		}

		static void AddChild(Entity parent, Entity child)
		{
			auto& tParent = Coordinator::GetComponent<Transform>(parent);
			auto& tChild = Coordinator::GetComponent<Transform>(child);

			if (tChild.parent)
			{
				RemoveChild(tChild.parent, child);
			}

			Entity lastChild = GetLastChild(parent);

			//Parent info
			tParent.children++;
			if (tParent.children == 1)
			{
				tParent.firstChild = child;
			}
			
			//Sibling info
			if (lastChild)
			{
				auto& tLastChild = Coordinator::GetComponent<Transform>(lastChild);
				tLastChild.nextSibling = child;
			}

			//Child info
			tChild.prevSibling = lastChild;
			tChild.parent = parent;
			tChild.dirty = true;
		}

		static void RemoveChild(Entity parent, Entity child)
		{
			if (!IsChildOf(parent, child)) return;

			auto& tParent = Coordinator::GetComponent<Transform>(parent);
			auto& tChild = Coordinator::GetComponent<Transform>(child);

			//Sibling info
			if (tChild.prevSibling)
			{
				auto& tPrevSibling = Coordinator::GetComponent<Transform>(tChild.prevSibling);
				tPrevSibling.nextSibling = tChild.nextSibling;
			}
			if (tChild.nextSibling)
			{
				auto& tNextSibling = Coordinator::GetComponent<Transform>(tChild.nextSibling);
				tNextSibling.prevSibling = tChild.prevSibling;
			}

			//Parent info
			tParent.children--;
			if (!tChild.prevSibling)
			{
				tParent.firstChild = tChild.nextSibling;
			}

			//Child info
			tChild.parent = 0;
			tChild.prevSibling = 0;
			tChild.nextSibling = 0;
			tChild.dirty = true;
		}

		static glm::mat4 GetWorldTransform(Entity entity)
		{
			const Transform& transform = Coordinator::GetComponent<Transform>(entity);
			return GetWorldTransform(transform);
		}

		static glm::mat4 GetWorldTransform(const Transform& transform)
		{
			glm::mat4 localToWorld = transform.GetLocalToParentMatrix();
			Entity parent = transform.parent;
			while (parent)
			{
				Transform& tParent = Coordinator::GetComponent<Transform>(parent);
				localToWorld = tParent.GetLocalToParentMatrix() * localToWorld;
				parent = tParent.parent;
			}
			return localToWorld;
		}

		static void GetWorldTransform(Entity entity, glm::vec3& position, glm::quat rotation, glm::vec3 scale)
		{
			const Transform& transform = Coordinator::GetComponent<Transform>(entity);
			GetWorldTransform(transform, position, rotation, scale);
		}

		static void GetWorldTransform(const Transform& transform, glm::vec3& position, glm::quat rotation, glm::vec3 scale)
		{
			glm::mat4 localToWorld = GetWorldTransform(transform);
			//set position
			//set rotation
			//set scale
			glm::vec3 skew;
			glm::vec4 perspective;
			glm::decompose(localToWorld, scale, rotation, position, skew, perspective);
		}

		static glm::vec3 GetWorldPosition(Entity entity)
		{
			const Transform& transform = Coordinator::GetComponent<Transform>(entity);
			GetWorldPosition(transform);
		}

		static glm::vec3 GetWorldPosition(const Transform& transform)
		{
			return glm::vec3(GetWorldTransform(transform)[3]);
		}

	private:
		void UpdateTransformMatricesRecursively(Transform& transform, bool parentDirty = false, glm::mat4 parentToWorld = glm::mat4(1.0f))
		{
			bool dirty = transform.dirty || parentDirty;
			if (dirty)
			{
				glm::mat4 localToParent = transform.GetLocalToParentMatrix();
				transform.localToWorld = parentToWorld * localToParent;
				transform.dirty = false;
			}
			
			Entity child = transform.firstChild;
			while (child)
			{
				Transform& childTransform = Coordinator::GetComponent<Transform>(child);
				child = childTransform.nextSibling;
				UpdateTransformMatricesRecursively(childTransform, dirty, transform.localToWorld);
			}
		}

	};
}