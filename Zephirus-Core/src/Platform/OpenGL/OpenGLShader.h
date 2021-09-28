#pragma once

#include "Zephirus/Renderer/Shader.h"
#include "glm/glm.hpp"
namespace ZPH {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual	void Bind() const override;
		virtual void UnBind() const override;


		void UploadUniformInt(const std::string& name, int val);
		void UploadUniformFloat(const std::string& name, float val);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& val);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& val);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& val);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t m_RendererID;
	};
}