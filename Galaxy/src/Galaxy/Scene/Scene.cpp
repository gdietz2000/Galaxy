#include "gxpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Component.h"

#include "Galaxy/Renderer/Renderer3D.h"

namespace Galaxy
{
	Scene::Scene()
	{
		m_SceneCamera = new SceneCamera();
	}

	Scene::~Scene()
	{
		delete m_Registry;
		delete m_SceneCamera;
	}

	Entity Scene::CreateEntity(std::string tagName)
	{
		EntityID id = m_Registry->create();
		m_Registry->add(id, TagComponent({ tagName }));
		m_Registry->add(id, TransformComponent());
		return { id, this };
	}

	void Scene::OnUpdate(Timestep ts)
	{
		Camera* mainCamera = nullptr;
		glm::mat4 tform(1.0f);

		{
			auto view = m_Registry->view<TransformComponent, CameraComponent>();
			for (auto entity : *view)
			{
				auto [transform, camera] = view->get(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					tform = transform.Transform;
					break;
				}
			}
		}

		if (mainCamera)
		{
			Renderer3D::BeginScene(*m_SceneCamera, tform);

			auto renderView = m_Registry->view<TransformComponent, SpriteRendererComponent>();
			for (auto entity : *renderView)
			{
				auto& [transform, sprite] = renderView->get(entity);

				Renderer3D::DrawQuad(transform, sprite.Color);
			}

			Renderer3D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_SceneCamera->SetViewportSize(width, height);
	}
}