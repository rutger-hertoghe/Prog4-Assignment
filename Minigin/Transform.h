#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		// POSITION
		const glm::vec3& GetPosition() const;
		void SetPosition(float x, float y, float z);

		// ROTATION
		const glm::vec3& GetRotation() const;
		void SetRotation(float x, float y, float z);

		// SCALE
		const glm::vec3& GetScale() const;
		void SetScale(float x, float y, float z);

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale;
		glm::vec3 m_Rotation;
	};
}
