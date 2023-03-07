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
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(new dae::TextureComponent(go.get(), "background.tga"));
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>(new dae::TextureComponent(go.get(), "logo.tga"));
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto fpsCounterObj = std::make_shared<dae::GameObject>();
	//fpsCounterObj->AddComponent<dae::TextureComponent>(new dae::TextureComponent(fpsCounterObj.get()));
	//fpsCounterObj->AddComponent<dae::TextComponent>(new dae::TextComponent(fpsCounterObj.get(), "placeholder", font));
	fpsCounterObj->AddComponent<dae::FPSCounterComponent>(new dae::FPSCounterComponent(fpsCounterObj.get(), 1.f));
	scene.Add(fpsCounterObj);

	auto to = std::make_shared<dae::GameObject>();
	//to->AddComponent<dae::TextureComponent>(new dae::TextureComponent(to));
	to->AddComponent<dae::TextComponent>(new dae::TextComponent(to.get(), "TestText", font));
	to->RemoveComponent<dae::TextComponent>();
	to->SetPosition(80, 20);
	scene.Add(to);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}