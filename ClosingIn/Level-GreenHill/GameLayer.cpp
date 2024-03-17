//
// Created by Let'sBlend on 29/02/2024.
//

#include "GameLayer.h"
#include "EngineAPI.h"

void GameLayer::OnAttach()
{
    std::cout << "Initialized gamelayer sub system" << std::endl;
}

void GameLayer::OnDetach()
{
    std::cout << "Shut downed gamelayer sub system" << std::endl;
}

void GameLayer::OnUpdate()
{
    if(Input::GetKeyDown(KeyCode::M))
        std::cout << "M" << std::endl;
}