#include "Transform.h"

// TODO: NOTE: does not include scaling yet, does not seem very relevant

dae::Transform::Transform(float x, float y, float rotation)
	: Transform({x, y}, rotation)
{}

dae::Transform::Transform(const glm::vec2& position, float rotation)
	: m_Position(position)
	, m_Rotation(rotation)
{
	ConstructMatrix();
}

void dae::Transform::ConstructMatrix()
{
	// USING ROW MAJOR ORDER NOTATION
	m_TransformMatrix =
	{
		cosf(m_Rotation),	-sinf(m_Rotation),	m_Position.x,
		sinf(m_Rotation),	 cosf(m_Rotation),	m_Position.y,
		0,					 0,				1
	};
}

void dae::Transform::ExtractDataFromMatrix()
{
	m_Rotation = atan2f(m_TransformMatrix[1][1], m_TransformMatrix[0][0]);

	m_Position.x = m_TransformMatrix[0][2]; // Equal to zeroth row, second column, see above
	m_Position.y = m_TransformMatrix[1][2]; // Equal to first row, second column, see above

	//	m_Scale.x = cos / m_TransformMatrix[0][0];
	//	m_Scale.y = cos / m_TransformMatrix[1][1];
}


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
