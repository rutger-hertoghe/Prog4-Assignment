#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

namespace dae
{
	// TODO: consider turning this into a class
	struct Transform final
	{
		explicit Transform(float x, float y, float rotation = 0.f);
		explicit Transform(const glm::vec2& position = { 0.f, 0.f }, float rotation = 0.f);

		glm::vec2 m_Position;
		float m_Rotation;

		glm::mat3x3 m_TransformMatrix;

		void ConstructMatrix();
		void ExtractDataFromMatrix();
	};
}
#endif