#include "Engine.h"

#include <iostream>

bool Engine::initialize()
{
    std::cout << "PuzzleForge Engine Initialized\n";

    return true;
}

void Engine::update()
{
    std::cout << "Engine Update\n";
}

void Engine::shutdown()
{
    std::cout << "Engine Shutdown\n";
}