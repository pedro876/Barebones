#pragma once

#include "../ECS/Coordinator.h"
#include "../Components/Transform.h"

namespace Barebones
{
	class TransformSystem : public System
	{
	public:
		void Update()
		{
			for (auto& entity : mEntities)
			{
				auto& transform = Coordinator::GetComponent<Transform>(entity);
				if (transform.parent) continue;
				UpdateTransformMatricesRecursively(transform);
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
			auto& transform = Coordinator::GetComponent<Transform>(entity);
			if (index < 0 || index >= transform.children) return 0;

			Entity child = transform.firstChild;
			if (index == 0) return child;

			transform = Coordinator::GetComponent<Transform>(child);
			for (unsigned int i = 0; i < index && transform.nextSibling; i++)
			{
				child = transform.nextSibling;
				transform = Coordinator::GetComponent<Transform>(child);
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
		}

	private:
		void UpdateTransformMatricesRecursively(Transform& transform, glm::mat4 parentToWorld = glm::mat4(1.0f))
		{
			glm::mat4 localToParent = transform.GetLocalToParentMatrix();
			glm::mat4 localToWorld = parentToWorld * localToParent;
			transform.localToWorld = localToWorld;
			Entity child = transform.firstChild;
			while (child)
			{
				Transform& childTransform = Coordinator::GetComponent<Transform>(child);
				child = transform.nextSibling;
				UpdateTransformMatricesRecursively(childTransform, localToWorld);
			}
		}

	};
}