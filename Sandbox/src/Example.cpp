#include <iostream>

#include "Galaxy.h"

class SandboxApp : public Galaxy::Application
{
public:
	SandboxApp()
	{
		GX_ERROR("Sandbox Application Created");
	}
	
	~SandboxApp()
	{
		
	}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new SandboxApp();
}
