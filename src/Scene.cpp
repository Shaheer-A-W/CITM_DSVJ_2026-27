#include "Engine.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name = "scene";
	img = nullptr;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	img = Engine::GetInstance().textures->Load("Assets/Textures/test.png");
	if (img == NULL) return false;

	Engine::GetInstance().audio->PlayMusic("Assets/Audio/Music/level-iv-339695.wav");
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	// L03: TODO 3: Make the camera movement independent of framerate.
	//   - Declare a camSpeed of 200.0f (pixels per second).
	//   - Multiply camSpeed by dt before adding/subtracting it below.
	//   - camera.x / camera.y are float (SDL_FRect), so just assign the result.
	float camSpeed = 200.0f;
	if (Engine::GetInstance().input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		Engine::GetInstance().render->camera.y -= camSpeed * dt;

	if (Engine::GetInstance().input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		Engine::GetInstance().render->camera.y += camSpeed * dt;

	if (Engine::GetInstance().input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		Engine::GetInstance().render->camera.x -= camSpeed * dt;

	if (Engine::GetInstance().input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		Engine::GetInstance().render->camera.x += camSpeed * dt;

	//Get the size of the window
	int windowW, windowH;
	Engine::GetInstance().window->GetWindowSize(windowW, windowH);

	//Get the size of the texture
	int texW, texH;
	Engine::GetInstance().textures->GetSize(img, texW, texH);

	// Renders the image in the center of the screen
	Engine::GetInstance().render->DrawTexture(img, windowW /2 - texW / 2, windowH /2 - texH / 2);

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	if(Engine::GetInstance().input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	Engine::GetInstance().textures->UnLoad(img);

	return true;
}
