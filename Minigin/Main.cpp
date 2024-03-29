#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <glm/vec2.hpp>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"
#include "Transform.h"
#include "MoveComponent.h"
#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "TimerComponent.h"
#include "MovementBehaviorComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"

using namespace dae;

void load()
{
	// TODO: QUESTION is it possible to get constructor to show up, displaying necessary arguments when typing in AddComponent
	// analogous to how make_unique & make_shared show the constructor in the tooltip
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>(Transform{ {0,0} });
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<GameObject>(Transform{ { 216, 180 } });
	go->AddComponent<TextureComponent>("logo.tga");
	scene.Add(go);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	/*auto fpsCounterObj = std::make_shared<GameObject>();
	fpsCounterObj->AddComponent<FPSCounterComponent>(1.f);
	auto pFPSCounter =  fpsCounterObj.get();
	fpsCounterObj->AddComponent<TimerComponent>(1.f, true, false, [pFPSCounter]()
		{
			pFPSCounter->RemoveComponent<TextureComponent>();
		});
	scene.Add(fpsCounterObj);

	auto to = std::make_shared<GameObject>(Transform{ {80, 20} });
	to->AddComponent<TextComponent>("TestText", font);
	scene.Add(to);
	*/
	auto pacman = std::make_shared<GameObject>(Transform{ {300.f, 200.f}, 0 });
	pacman->AddComponent<MovementBehaviorComponent>(50.f);
	auto pacmanTexture{ pacman->AddComponent<TextureComponent>("PacMan.png") };
	pacmanTexture->SetSize(16, 16);
	scene.Add(pacman);

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadRight, KeyState::down }, 
		new MoveCommand{ pacman.get(), glm::vec3{1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadLeft, KeyState::down },
		new MoveCommand{ pacman.get(), glm::vec3{-1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadUp, KeyState::down }, 
		new MoveCommand{ pacman.get(), glm::vec3{0, -1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadDown, KeyState::down }, 
		new MoveCommand{ pacman.get(), glm::vec3{0, 1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_D, KeyState::down },
		new MoveCommand{ pacman.get(), glm::vec3{1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_A, KeyState::down },
		new MoveCommand{ pacman.get(), glm::vec3{-1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_W, KeyState::down },
		new MoveCommand{ pacman.get(), glm::vec3{0, -1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_S, KeyState::down },
		new MoveCommand{ pacman.get(), glm::vec3{0, 1, 0} });
	/*
	auto secondPacman = std::make_shared<GameObject>(Transform{ {400.f, 200.f}, static_cast<float>(M_PI) });
	pacmanTexture = secondPacman->AddComponent<TextureComponent>("PacMan.png");
	pacmanTexture->SetSize(16, 16);
	secondPacman->AddComponent<RotatorComponent>(static_cast<float>(-M_PI / 2));
	scene.Add(secondPacman);

	auto ghost = std::make_shared<GameObject>(Transform{ {0.f, 50.f} });
	auto ghostTexture{ ghost->AddComponent<TextureComponent>("ghost.png") };
	ghostTexture->SetSize(16, 16);
	auto pGhost = ghost.get();
	auto pSecondPacman = secondPacman.get();
	ghost->SetParent(pacman.get(), false);
	ghost->AddComponent<RotatorComponent>(3.f);
	ghost->AddComponent<TimerComponent>(10.f, true, false, [pSecondPacman, pGhost]()
		{
			pGhost->SetParent(pSecondPacman);
			std::cout << "Timer was triggered!\n";
			pGhost->RemoveComponent<TextureComponent>();
		});
	ghost->RemoveComponent<RotatorComponent>();
	ghost->RemoveComponent<MoveComponent>();
	scene.Add(ghost);

	auto secondGhost = std::make_shared<GameObject>(Transform{ {60.f, 0.f} });
	ghostTexture = secondGhost->AddComponent<TextureComponent>("ghost.png");
	ghostTexture->SetSize(16, 16);
	secondGhost->SetParent(ghost.get(), false);
	scene.Add(secondGhost);*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}