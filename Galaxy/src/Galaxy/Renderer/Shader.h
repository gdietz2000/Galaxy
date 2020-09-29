#pragma once

#include "gxpch.h"
#include "glm/glm.hpp"
#include "Galaxy/Core/Core.h"

namespace Galaxy
{
	class Shader
	{
	public:
		enum class ShaderType
		{
			Vertex = 0,
			Pixel = 1,
			Geometry = 2,
			Compute = 3,
			Hull = 4,
			Domain = 5,
		};

	public:
		virtual ~Shader() {};

		virtual void Bind() const = 0;
		virtual void Unbind() = 0;

		virtual const std::string& GetName() const = 0;

		virtual void SetMat4(const glm::mat4& matrix) = 0;

		virtual void* GetData() const = 0;
		virtual size_t GetSize() const = 0;

		static Ref<Shader> Create(const std::string& filepath, ShaderType st);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}