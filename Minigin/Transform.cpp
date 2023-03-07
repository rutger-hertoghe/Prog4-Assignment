#include "Transform.h"

const glm::vec3& dae::Transform::GetPosition() const
{
	return m_Position;
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

const glm::vec3& dae::Transform::GetRotation() const
{
	return m_Rotation;
}

void dae::Transform::SetRotation(float x, float y, float z)
{
	m_Rotation.x = x;
	m_Rotation.y = y;
	m_Rotation.z = z;
}

const glm::vec3& dae::Transform::GetScale() const
{
	return m_Scale;
}

void dae::Transform::SetScale(float x, float y, float z)
{
	m_Scale.x = x;
	m_Scale.y = y;
	m_Scale.z = z;
}
