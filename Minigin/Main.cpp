#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <steam_api.h>
#include <glm/vec2.hpp>

#include "AddScoreCommand.h"
#include "HealthComponent.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "Transform.h"
#include "MovementBehaviorComponent.h"
#include "TimerComponent.h"

#include "TextComponent.h"

#include "InputManager.h"
#include "MoveCommand.h"
#include "HealthObserver.h"
#include "ScoreDisplayObserver.h"
#include "DamageCommand.h"
#include "ScoreComponent.h"
#include "SteamAchievements.h"
#include "SteamAchievementObserver.h"
#include <initializer_list>

using namespace dae;

void load()
{
	// TODO: Start thinking about how to clean this absolute monster of a function up
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto background = std::make_unique<GameObject>("Background", Transform{{0,0}});
	background->AddComponent<TextureComponent>("background.tga");

	scene.Add(background);

	auto logo = std::make_unique<GameObject>("Logo", Transform{{216, 180}});
	logo->AddComponent<TextureComponent>("logo.tga");
	scene.Add(logo);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//auto pacman = std::make_unique<GameObject>("PacMan", Transform{{300.f, 200.f}, 0});
	//pacman->AddComponent<MovementBehaviorComponent>(100.f);
	//auto pacmanTexture{ pacman->AddComponent<TextureComponent>("PacMan.png") };
	//pacmanTexture->SetSize(32, 32);
	//auto pRawPacman{ pacman.get() };
	//pacman->AddComponent<TimerComponent>(3.f, true, false, [pRawPacman]()
	//	{
	//		pRawPacman->Destroy();
	//	});

	//scene.Add(pacman);



	// SHIP

	auto ship = std::make_unique<GameObject>("SpaceShip", Transform{ 300.f, 150.f, 0 });
	ship->AddComponent<MovementBehaviorComponent>(200.f);
	auto shipTexture{ ship->AddComponent<TextureComponent>("GalagaShip.png") };
	shipTexture->SetSize(32, 32);
	auto pHealthComponent{ ship->AddComponent<HealthComponent>(3) };
	auto pShipScoreComponent{ ship->AddComponent<ScoreComponent>() };

	auto shipHealthUI{ std::make_unique<GameObject>("ShipHealthDisplay", Transform{0.f, 0.f, 0}) };
	shipHealthUI->AddComponent<TextComponent>("Lives: 3");
	std::unique_ptr<Observer> healthObserver{ std::make_unique<HealthDisplayObserver>(pHealthComponent, shipHealthUI.get()) };

	auto shipScoreUI{ std::make_unique<GameObject>("ShipScoreDisplay", Transform{0.f, 40.f, 0}) };
	shipScoreUI->AddComponent<TextComponent>("Score: 0");
	std::unique_ptr<Observer> scoreObserver{ std::make_unique<ScoreDisplayObserver>(pShipScoreComponent, shipScoreUI.get()) };

	scene.Add(healthObserver);
	scene.Add(scoreObserver);
	scene.Add(shipHealthUI);
	scene.Add(shipScoreUI);

	// TODO: get rid of the new?
	// I USE NEW HERE BUT THE POINTER GETS HIJACKED BY A SMART POINTER INSIDE BINDING OF THE COMMAND

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_D, KeyState::down },
		new MoveCommand{ ship.get(), glm::vec3{1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_A, KeyState::down },
		new MoveCommand{ ship.get(), glm::vec3{-1, 0, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_W, KeyState::down },
		new MoveCommand{ ship.get(), glm::vec3{0, -1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_S, KeyState::down },
		new MoveCommand{ ship.get(), glm::vec3{0, 1, 0} });

	InputManager::GetInstance().BindCommand(
		ButtonAction{SDL_SCANCODE_Q, KeyState::pressed},
		new DamageCommand{ship.get(), 1});

	InputManager::GetInstance().BindCommand(
		ButtonAction{ SDL_SCANCODE_E, KeyState::pressed },
		new AddScoreCommand{ ship.get(), 100 });

	// GHOST

	auto ghost = std::make_unique<GameObject>("Ghost", Transform{500.f, 200.f, 0});
	ghost->AddComponent<MovementBehaviorComponent>(100.f);
	auto ghostTexture{ ghost->AddComponent<TextureComponent>("ghost.png") };
	ghostTexture->SetSize(32, 32);
	pHealthComponent = ghost->AddComponent<HealthComponent>(3);
	auto pGhostScoreComponent = ghost->AddComponent<ScoreComponent>();

	auto ghostHealthUI{ std::make_unique<GameObject>("GhostHealthDisplay", Transform{0.f, 120.f, 0}) };
	ghostHealthUI->AddComponent<TextComponent>("Lives: 3");
	healthObserver = std::make_unique<HealthDisplayObserver>(pHealthComponent, ghostHealthUI.get());

	auto ghostScoreUI{ std::make_unique<GameObject>("GhostScoreDisplay", Transform{0.f, 160.f, 0}) };
	ghostScoreUI->AddComponent<TextComponent>("Score: 0");
	scoreObserver = std::make_unique<ScoreDisplayObserver>(pGhostScoreComponent, ghostScoreUI.get());

	scene.Add(healthObserver);
	scene.Add(scoreObserver);
	scene.Add(ghostHealthUI);
	scene.Add(ghostScoreUI);

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

	InputManager::GetInstance().BindCommand(
		ButtonAction{0, GamePad::A, KeyState::pressed},
		new DamageCommand{ ghost.get(), 1});

	InputManager::GetInstance().BindCommand(
		ButtonAction{ 0, GamePad::B, KeyState::pressed },
		new AddScoreCommand{ ghost.get(), 100 });

	std::unique_ptr<Observer> achievementObserver{ std::make_unique<SteamAchievementObserver>(std::initializer_list<ScoreComponent*>{pShipScoreComponent, pGhostScoreComponent}) };
	scene.Add(achievementObserver);

	scene.Add(ship);
	scene.Add(ghost);
}

int main(int, char*[])
{
	InitializeSteamAPI();

	dae::Minigin engine("../Data/");
	engine.Run(load);

	// TODO: fix error here upon closing of program
	CleanUpSteamResources();

    return 0;
}