#pragma once

#include <iostream>
#include <string>

class GameObject;

class Component
{

public:
	GameObject* gameObject = nullptr;

	friend std::ostream& operator<<(std::ostream& os, const Component& component);
	friend std::ostream& operator<<(std::ostream& os, const Component* component);

protected:
	virtual std::string ToString() const;

private:
};

