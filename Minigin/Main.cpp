#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSCounterComponent.h"

void load()
{
	// TODO: is it possible to get constructor to show up, displaying necessary arguments when typing in AddComponent
	// TODO: maybe ask teachers, because online resources are hard to find
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto fpsCounterObj = std::make_shared<dae::GameObject>();
	fpsCounterObj->AddComponent<dae::FPSCounterComponent>(1.f);	
	scene.Add(fpsCounterObj);

	auto to = std::make_shared<dae::GameObject>();
	to->AddComponent<dae::TextComponent>("TestText", font);
	to->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}