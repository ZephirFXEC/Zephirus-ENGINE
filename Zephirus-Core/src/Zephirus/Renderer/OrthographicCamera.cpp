#pragma once
#include "zphpch.h"
#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
using namespace glm;
namespace ZPH
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjMatrix(ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		mat4 transform = translate(mat4(1.0f), m_Pos) * rotate(mat4(1.0f), radians(m_rotation), vec3(0, 0, 1));
		m_ViewMatrix = inverse(transform);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

}