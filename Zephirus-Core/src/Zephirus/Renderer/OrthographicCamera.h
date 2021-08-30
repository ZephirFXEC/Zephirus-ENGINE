#pragma once

#include <glm/glm.hpp>
namespace ZPH
{
	class OrthographicCamera 
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);


		const glm::vec3& GetPos() const { return m_Pos; }
		float GetRotation() const { return m_rotation; }
		void SetPosition(const glm::vec3 pos) { m_Pos = pos; RecalculateViewMatrix(); }
		void SetRotation(float rot) { m_rotation = rot; RecalculateViewMatrix(); }

		const glm::mat4 GetProjMatrix() const { return m_ProjMatrix; }
		const glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4 GetViewProjMatrix() const { return m_ViewProjMatrix; }
	private:

		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;
		glm::vec3 m_Pos = {0.0f, 0.0f, 0.0f};
		float m_rotation = 0.0f;
	};
}