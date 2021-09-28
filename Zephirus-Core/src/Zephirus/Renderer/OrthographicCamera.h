#pragma once

#include <glm/glm.hpp>
namespace ZPH
{
	class OrthographicCamera 
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);


		const glm::vec3& GetPos() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3 pos) { m_Position = pos; RecalculateViewMatrix(); }
		void SetRotation(float rot) { m_Rotation = rot; RecalculateViewMatrix(); }

		const glm::mat4 GetProjMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 GetViewProjMatrix() const { return m_ViewProjectionMatrix; }
	private:

		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		float m_Rotation = 0.0f;
	};
}