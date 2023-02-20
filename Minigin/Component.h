#pragma once
#include <memory>

class GameObject;

class Component
{
public:
	Component() = default;
private:
	std::shared_ptr<GameObject> parentObject;
};