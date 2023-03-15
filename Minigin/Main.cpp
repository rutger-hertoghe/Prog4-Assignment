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
#include "TransformComponent.h"

using namespace dae;

void load()
{
	// TODO: is it possible to get constructor to show up, displaying necessary arguments when typing in AddComponent
	// TODO: maybe ask teachers, because online resources are hard to find
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>(Transform{{0,0}} );
	go->AddComponent<TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<GameObject>(Transform{ { 216, 180 } });
	go->AddComponent<TextureComponent>("logo.tga");
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto fpsCounterObj = std::make_shared<GameObject>();
	fpsCounterObj->AddComponent<FPSCounterComponent>(1.f);	
	scene.Add(fpsCounterObj);

	auto to = std::make_shared<GameObject>(Transform{{80, 20}});
	to->AddComponent<TextComponent>("TestText", font);
	scene.Add(to);

	auto rotatorRoot = std::make_shared<GameObject>(Transform{ {50.f, 50.f} });
	scene.Add(rotatorRoot);

	auto pacman = std::make_shared<GameObject>(Transform{ {10.f, 0.f}, 0 });
	auto pacmanTexture{ pacman->AddComponent<TextureComponent>("PacMan.png") };
	pacmanTexture->SetSize(16, 16);
	pacman->SetParent(rotatorRoot.get());
	scene.Add(pacman);

	auto ghost = std::make_shared<GameObject>(Transform{ {0.f, 10.f} });
	auto ghostTexture{ ghost->AddComponent<TextureComponent>("ghost.png") };
	ghostTexture->SetSize(16, 16);
	//ghost->SetParent(pacman.get());
	ghost->AddComponent<MoveComponent>(glm::vec2{ 10.f, 0.f });
	scene.Add(ghost);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}