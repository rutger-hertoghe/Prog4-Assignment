#include "Transform.h"

dae::Transform::Transform(const glm::vec2& position, float rotation)
	: m_Position(position)
	, m_Rotation(rotation)
{
}



//dae::Transform dae::Transform::operator*(const Transform& other) const
//{
//	// Transform constructor taking matrix extracts other values by itself
//	return Transform{ m_TransformMatrix * other.m_TransformMatrix };
//}
//
//dae::Transform& dae::Transform::operator*=(const Transform& other)
//{
//	m_TransformMatrix *= other.m_TransformMatrix;
//	ExtractCorrectValuesFromMatrix();
//	return *this;
//}
//
//void dae::Transform::SetRotation(float rotation)
//{
//	m_Rotation = rotation;
//	RecalculateMatrix();
//}
//
//void dae::Transform::SetPosition(const glm::vec2& position)
//{
//	m_Position = position;
//	RecalculateMatrix();
//}
//
//void dae::Transform::SetScale(const glm::vec2& scale)
//{
//	m_Scale = scale;
//	RecalculateMatrix();
//}
//
//void dae::Transform::AddRotation(float angle)
//{
//	m_Rotation += angle;
//	RecalculateMatrix();
//}
//
//void dae::Transform::AddPosition(const glm::vec2& position)
//{
//	m_Position += position;
//	RecalculateMatrix();
//}
//
//void dae::Transform::RelativeScale(float scalingFactor)
//{
//	m_Scale *= scalingFactor;
//	RecalculateMatrix();
//}
//
//void dae::Transform::RelativeScale(const glm::vec2& scalingFactors)
//{
//	m_Scale.x *= scalingFactors.x;
//	m_Scale.y *= scalingFactors.y;
//	RecalculateMatrix();
//}
//
//const glm::mat3x3& dae::Transform::GetTransformMatrix() const
//{
//	return m_TransformMatrix;
//}
//
//const glm::vec2& dae::Transform::GetPosition() const
//{
//	return m_Position;
//}
//
//const glm::vec2& dae::Transform::GetScale() const
//{
//	return m_Scale;
//}
//
//float dae::Transform::GetRotation() const
//{
//	return m_Rotation;
//}
//
//void dae::Transform::RecalculateMatrix()
//{
//	const float cos{ cosf(m_Rotation) };
//	const float sin{ sinf(m_Rotation) };
//
//	/*m_TransformMatrix =
//	{
//		m_Scale.x * cos,	m_Scale.x * sin, m_Position.x,
//		m_Scale.y * -sin,	m_Scale.y * cos, m_Position.y,
//		0,					0,				 1
//	};*/
//
//	m_TransformMatrix =
//	{
//		m_Scale.x * cos,	m_Scale.y * -sin,	0,
//		m_Scale.x * sin,	m_Scale.y * cos,	0,
//		m_Position.x,		m_Position.y,		1
//	};
//}
//
//void dae::Transform::ExtractCorrectValuesFromMatrix()
//{
//	// This is probably slow (atan2f & cos/sin are slow operations).
//	m_Rotation = atan2f(m_TransformMatrix[0][0], m_TransformMatrix[0][1]);
//
//	m_Position.x = m_TransformMatrix[2][0];
//	m_Position.y = m_TransformMatrix[2][1];
//
//	const float cos{ cosf(m_Rotation) };
//	m_Scale.x = cos / m_TransformMatrix[0][0];
//	m_Scale.y = cos / m_TransformMatrix[1][1];
//
//	//// Faster approach: [NOTE: DOES NOT WORK FOR NEGATIVE SCALING]
//	//m_Position.x = m_TransformMatrix[0][2];
//	//m_Position.y = m_TransformMatrix[1][2];
//
//	//const glm::vec2 xVec{ m_TransformMatrix[0][0], m_TransformMatrix[0][1] };
//	//m_Scale.x = glm::length(xVec);
//	//const glm::vec2 yVec{ m_TransformMatrix[1][0], m_TransformMatrix[1][1] };
//	//m_Scale.y = glm::length(yVec);
//}
