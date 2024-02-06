#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include "framework/Application.h"

int main() 
{
	std::unique_ptr<ly::Application> game = std::make_unique<ly::Application>();
	//ly::Application* game = new ly::Application();
	game->Run();

	return 0;
}