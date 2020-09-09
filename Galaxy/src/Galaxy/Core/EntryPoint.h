#pragma once

#include "Application.h"

extern Galaxy::Application* Galaxy::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Galaxy::CreateApplication();
	app->Run();
	delete app;

	return 0;
}