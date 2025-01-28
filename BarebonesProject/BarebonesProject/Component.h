#pragma once

#include <iostream>
#include <string>

namespace Barebones
{
	class GameObject;

	class Component
	{

	public:
		GameObject* gameObject = nullptr;
		unsigned int handle;

		friend std::ostream& operator<<(std::ostream& os, const Component& component);
		friend std::ostream& operator<<(std::ostream& os, const Component* component);

	protected:
		virtual std::string ToString() const;

	private:
	};


}

