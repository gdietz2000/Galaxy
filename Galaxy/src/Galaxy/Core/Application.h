#pragma once


namespace Galaxy
{
	class Application 
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}