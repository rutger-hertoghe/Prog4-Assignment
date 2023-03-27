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
#include "Transform.h"
#include "MovementBehaviorComponent.h"

#include "GameObject.h"
#include "InputManager.h"
#include "MoveCommand.h"

using namespace dae;

void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>(Transform{ {0,0} });
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<GameObject>(Transform{ { 216, 180 } });
	go->AddComponent<TextureComponent>("logo.tga");
	scene.Add(go);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pacman = std::make_shared<GameObject>(Transform{ {300.f, 200.f}, 0 });
	pacman->AddComponent<MovementBehaviorComponent>(100.f);
	auto pacmanTexture{ pacman->AddComponent<TextureComponent>("PacMan.png") };
	pacmanTexture->SetSize(32, 32);
	scene.Add(pacman);

	// TODO: get rid of the new?
	// I USE NEW HERE BUT THE POINTER GETS HIJACKED BY A SMART POINTER INSIDE BINDING OF THE COMMAND

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

	auto ghost = std::make_shared<GameObject>(Transform{ 500.f, 200.f, 0 });
	ghost->AddComponent<MovementBehaviorComponent>(200.f);
	auto ghostTexture{ ghost->AddComponent<TextureComponent>("ghost.png") };
	ghostTexture->SetSize(32, 32);
	scene.Add(ghost);

	// TODO: get rid of the new?
	// I USE NEW HERE BUT THE POINTER GETS HIJACKED BY A SMART POINTER INSIDE BINDING OF THE COMMAND

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadRight, KeyState::down },
		new MoveCommand{ ghost.get(), glm::vec3{1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadLeft, KeyState::down },
		new MoveCommand{ ghost.get(), glm::vec3{-1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadUp, KeyState::down },
		new MoveCommand{ ghost.get(), glm::vec3{0, -1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::DPadDown, KeyState::down },
		new MoveCommand{ ghost.get(), glm::vec3{0, 1, 0} });
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}