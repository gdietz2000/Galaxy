#include <iostream>

#include "Galaxy.h"

class SandboxApp : public Galaxy::Application
{
public:
	SandboxApp()
	{
	
	}
	
	~SandboxApp()
	{
		
	}
};

Galaxy::Application* Galaxy::CreateApplication()
{
	return new SandboxApp();
}
