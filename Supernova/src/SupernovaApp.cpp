#include <Galaxy.h>

#include "EditorLayer.h"
#include "Galaxy/Core/EntryPoint.h"

namespace Galaxy
{
	class Supernova : public Application
	{
	public:
		Supernova() : Application("Supernova Editor")
		{
			PushLayer(new EditorLayer());
		}

		~Supernova()
		{
			
		}
	};

	Application* CreateApplication()
	{
		return new Supernova();
	}
}
