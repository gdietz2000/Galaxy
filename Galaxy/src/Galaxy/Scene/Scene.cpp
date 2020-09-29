#include "gxpch.h"
#include "Scene.h"

#include "Galaxy/Renderer/Renderer3D.h"

namespace Galaxy
{
	Scene::Scene()
	{
		camera = new SceneCamera();
	}

	Scene::~Scene()
	{
		delete camera;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		Renderer3D::BeginScene(*camera, glm::mat4(1.0f));

		Renderer3D::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(1.0f, -1.0f, 0.0f), glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.5f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec4(0.0f, 0, 1.0f, 1.0f));
		Renderer3D::DrawQuad(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec4(0.5f, 0, 1.0f, 1.0f));

		Renderer3D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		camera->SetViewportSize(width, height);
	}
}