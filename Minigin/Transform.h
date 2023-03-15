#pragma once
#include <glm/glm.hpp>

namespace dae
{
	// TODO: POTENTIAL ISSUE: in fact I have duplicate data here
	// Scale, position & rotation are encoded both in the matrix and separate members.
	// While a matrix implementation felt 'correct', it might affect performance due to the costly atan2f operation
	// everytime the matrix gets changed.

	class Transform final
	{
	public:
		explicit Transform(const glm::vec2& position = { 0.f, 0.f }, float rotation = 0.f, const glm::vec2& scale = {1.f, 1.f})
			: m_Position(position)
			, m_Scale(scale)
			, m_Rotation(rotation)
		{
			RecalculateMatrix();
		}
		explicit Transform(const glm::mat3x3& matrix)
			: m_TransformMatrix(matrix)
		{
			ExtractCorrectValuesFromMatrix();
		}

		Transform operator*(const Transform& other) const;
		Transform& operator*=(const Transform& other);

		void SetRotation(float rotation);
		void SetPosition(const glm::vec2& position);
		void SetScale(const glm::vec2& scale);

		void AddRotation(float angle);
		void AddPosition(const glm::vec2& position);
		void RelativeScale(float scalingFactor);
		void RelativeScale(const glm::vec2& scalingFactors);

		[[nodiscard]] const glm::mat3x3& GetTransformMatrix() const;
		[[nodiscard]] const glm::vec2& GetPosition() const;
		[[nodiscard]] const glm::vec2& GetScale() const;
		[[nodiscard]] float GetRotation() const;

	private:
		glm::mat3x3 m_TransformMatrix{};
		glm::vec2 m_Position{0.f, 0.f};
		glm::vec2 m_Scale{1.f, 1.f};
		float m_Rotation{0.f};

		void RecalculateMatrix();
		void ExtractCorrectValuesFromMatrix();
	};
}
