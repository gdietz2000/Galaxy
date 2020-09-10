#pragma once

#include "Application.h"
#include "Log.h"
#include "Galaxy/Events/Event.h"
#include "Galaxy/Events/ApplicationEvent.h"

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{
	Galaxy::Log::Init();

	auto app = Galaxy::CreateApplication();
	app->Run();
	delete app;

	return 0;
}