#include "SceneHierarchy.h"

#include "Galaxy/Scene/Component.h"

#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Galaxy
{
	static void DrawStylizedVec3(const std::string& label, glm::vec3& values, float resetValue = 0.0f, float columnWidth = 100);

	SceneHierarcyPanel::SceneHierarcyPanel(const Ref<Scene>& scene)
	{
		SetContext(scene);
	}

	void SceneHierarcyPanel::SetContext(const Ref<Scene>& scene)
	{
		m_Context = scene;
	}

	void SceneHierarcyPanel::OnImGuiRender()
	{
		//Scene Hierarcy Panel
		ImGui::Begin("Scene Hierarcy");

		m_Context->m_Registry->each([&](auto& id)
			{
				Entity entity{ id, m_Context.get() };
				DrawEntityNode(entity);
			});

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_SelectionContext = {};

		if (ImGui::BeginPopupContextWindow(0,1,false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");

			ImGui::EndPopup();
		}

		ImGui::End();

		//Inspector Panel
		ImGui::Begin("Inspector");

		if (m_SelectionContext)
			DrawComponents(m_SelectionContext);

		ImGui::End();
	}

	void SceneHierarcyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow 
			| ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0);
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked())
			m_SelectionContext = entity;

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			bool opened = ImGui::TreeNodeEx((void*)9817239, flags, tag.c_str());
			if (opened)
				ImGui::TreePop();
			ImGui::TreePop();
		}

		if (entityDeleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	void SceneHierarcyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, sizeof(buffer), tag.c_str());
			if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
				tag = std::string(buffer);

			ImGui::SameLine();
			ImGui::PushItemWidth(-1);

			if (ImGui::Button("Add Component"))
				ImGui::OpenPopup("AddComponent");

			if (ImGui::BeginPopup("AddComponent"))
			{
				if (ImGui::MenuItem("Camera"))
				{
					m_SelectionContext.AddComponent<CameraComponent>();
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::MenuItem("Sprite Component"))
				{
					m_SelectionContext.AddComponent<SpriteRendererComponent>();
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			ImGui::PopItemWidth();

			DrawComponent<TransformComponent>("Transform Component", entity, [](TransformComponent& component)
				{
					DrawStylizedVec3("Translation", component.Translation);
					glm::vec3 rotation = glm::degrees(component.Rotation);
					DrawStylizedVec3("Rotation", rotation);
					component.Rotation = glm::radians(rotation);
					DrawStylizedVec3("Scale", component.Scale, 1.0f);
				});

			DrawComponent<CameraComponent>("Camera Component", entity, [](CameraComponent& component)
				{
					auto& camera = component.Camera;

					ImGui::Checkbox("Primary", &component.Primary);

					const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
					const char* currentProjectionTypeString = projectionTypeStrings[(int)camera.GetProjectionType()];
					if (ImGui::BeginCombo("Projection", currentProjectionTypeString))
					{
						for (size_t i = 0; i < 2; ++i)
						{
							bool isSelected = currentProjectionTypeString == projectionTypeStrings[i];
							if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
							{
								currentProjectionTypeString = projectionTypeStrings[i];
								camera.SetProjectionType((SceneCamera::ProjectionType)i);
							}

							if (isSelected)
								ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if (camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
					{
						float perFov = glm::degrees(camera.GetPerspectiveFov());
						float perNear = camera.GetPerspectiveNearClip();
						float perFar = camera.GetPerspectiveFarClip();

						if (ImGui::DragFloat("Field Of View", &perFov))
							camera.SetPerspectiveFov(glm::radians(perFov));
						
						if (ImGui::DragFloat("Near Plane", &perNear))
							camera.SetPerspectiveNearClip(perNear);
						
						if (ImGui::DragFloat("Far Plane", &perFar))
							camera.SetPerspectiveFarClip(perFar);
					}
					else
					{
						float orthoSize = camera.GetOrthographicSize();
						float orthoNear = camera.GetOrthographicNearClip();
						float orthoFar = camera.GetOrthographicFarClip();

						if (ImGui::DragFloat("Size", &orthoSize))
							camera.SetOrthographicSize(orthoSize);

						if (ImGui::DragFloat("Near", &orthoNear))
							camera.SetOrthographicNearClip(orthoNear);

						if (ImGui::DragFloat("Far", &orthoFar))
							camera.SetOrthographicFarClip(orthoFar);

						ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
					}
				});

			DrawComponent<SpriteRendererComponent>("Sprite Renderer Component", entity, [](auto& component)
				{
					ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
				});
		}
	}

	template<typename T, typename UIFunction>
	void SceneHierarcyPanel::DrawComponent(const std::string& label, Entity entity, UIFunction func)
	{
		const ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen
			| ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap
			| ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4,4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, label.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("+", ImVec2{ lineHeight, lineHeight }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}
		
			bool removeComponent = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove Component"))
					removeComponent = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				func(component);
				ImGui::TreePop();
			}

			if (removeComponent)
				entity.RemoveComponent<T>();
		}
	
	}

	static void DrawStylizedVec3(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		//X
		if (ImGui::Button("X"))
			values.x = resetValue;
		ImGui::PopStyleColor(3);
		

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		//Y
		if (ImGui::Button("Y"))
			values.y = resetValue;
		ImGui::PopStyleColor(3);
		

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		//Z
		if (ImGui::Button("Z"))
			values.z = resetValue;
		ImGui::PopStyleColor(3);
		

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

}