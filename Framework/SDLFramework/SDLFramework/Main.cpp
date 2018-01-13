#include <iostream>
#include "Config.h"
#include "FWApplication.h"
#include <SDL_events.h>
#include "SDL_timer.h"
#include <vector>
#include <memory>
#include <string>
#include <time.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "DebugDisplay.h"
#include "Vector.h"
#include "Matrix.h"
#include "Shape.h"
#include "Square2d.h"
#include "Camera.h"
#include "Cube3d.h"

int main(int args[])
{
	/*Vec a{ 1.0f, 2.0f, 3.0f };
	Vec b{ 10.f, 10.f };

	Vec c = b + a;
	Vec d = b - a;
	Vec f = b * 5.f;

	Vec2 v2(10.f, 5.f);
	Vec2 v3(10.f, 5.f);

	v2.y() += 5.0f;

	v2 += b;

	Matrix ma {
		{ 1, 4, 6, 10 },
		{ 2, 7, 5, 3 }
	};

	Matrix mb{
		{ 1, 4, 6 },
		{ 2, 7, 5 },
		{ 9, 0, 11 },
		{ 3, 1, 0 }
	};

	Matrix result = ma * mb;

	Matrix expected {
		{ 93, 42, 92 },
		{ 70, 60, 102 }
	};

	Shape shape_a {
		{ 1, 4, 6, 10 },
		{ 2, 7, 5, 3 }
	};

	shape_a.add_transform(mb);
	shape_a.add_transform("test", {
		{ 0.0f }
	});*/

	
	//Matrix output = square.transform();

	/*auto transformed = shape_a.transform();

	bool worked = result == expected;

	if (Matrix mat{ v2, v3, b }) {
		auto worked = true;
	}*/

	//auto window = Window::CreateSDLWindow();
	auto application = new FWApplication();
	if (!application->GetWindow())
	{
		LOG("Couldn't create window...");
		return EXIT_FAILURE;
	}

	Camera camera;
	camera.eye() = { 0.f, 0.f, 0.f };
	camera.look_at() = { 0.f, 0.f, 1.f };
	camera.near() = 2.f;
	camera.far() = 100.f;
	camera.fov() = 40.f;
	camera.size() = 720.f;

	application->SetCamera(camera);

	//Square2d square{ 150.f, 125.f, 25.f, 25.f };

	//auto hmm = camera.fix(camera.matrix() * square.transform());

	Cube3d cube_a{ 0.f, 0.f, 100.f, 20.f, 20.f, 20.f };
	Cube3d cube_b{ -100.f, 0.f, 100.f, 20.f, 20.f, 20.f };
	Cube3d cube_c{ 200.f, 50.f, 200.f, 20.f, 20.f, 20.f };
	
	application->SetTargetFPS(120);
	application->SetColor(Color(48, 124, 56, 0));


	DebugDisplay dd {
		[application, &cube_a]() -> DebugDisplay::debug_list {
			return {
				std::make_pair("LINAL", "v0.1"),
				std::make_pair("Time", std::to_string(static_cast<float>(application->GetTimeSinceStartedMS()) / 1000.f)),
				std::make_pair("fov", std::to_string(application->GetCamera().fov())),
			};
		}
	};

	application->AddRenderable(&dd);
	application->AddRenderable(&cube_a);
	application->AddRenderable(&cube_b);
	application->AddRenderable(&cube_c);

	constexpr float movement = 5.0f;
	constexpr float camera_movement = 1.5f;

	while (application->IsRunning())
	{
		application->StartTick();
		

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEWHEEL:
				if (event.wheel.x == 1)
					cube_a.z() += 0.1f;
				else if (event.wheel.x == -1)
					cube_a.z() -= 0.1f;
				else {
					std::cout << event.wheel.x;
				}
				break;
			case SDL_QUIT:
				application->Quit();
				break;

			case SDL_KEYDOWN:
				// About what it's supposed to do

				if (event.key.keysym.scancode == SDL_SCANCODE_UP) {
					application->GetCamera().eye()[1] += camera_movement;
					application->GetCamera().look_at()[1] += camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					application->GetCamera().eye()[1] -= camera_movement;
					application->GetCamera().look_at()[1] -= camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					application->GetCamera().eye()[0] -= camera_movement;
					application->GetCamera().look_at()[0] -= camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					application->GetCamera().eye()[0] += camera_movement;
					application->GetCamera().look_at()[0] += camera_movement;
				}


				if (event.key.keysym.scancode == SDL_SCANCODE_KP_8) {
					application->GetCamera().look_at()[1] += 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_KP_2) {
					application->GetCamera().look_at()[1] -= 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_KP_4) {
					application->GetCamera().look_at()[0] += 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_KP_6) {
					application->GetCamera().look_at()[0] -= 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_W) {
					application->GetCamera().eye()[1] -= movement;
					application->GetCamera().look_at()[1] -= movement;
					cube_a.y() -= movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_S) {
					application->GetCamera().eye()[1] += movement;
					application->GetCamera().look_at()[1] += movement;
					cube_a.y() += movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_A) {
					application->GetCamera().eye()[0] += movement;
					application->GetCamera().look_at()[0] += movement;
					cube_a.x() += movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_D) {
					application->GetCamera().eye()[0] -= movement;
					application->GetCamera().look_at()[0] -= movement;
					cube_a.x() -= movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {
					application->SetShowDebug(!application->IsShowDebug());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
					cube_a.scale_x() += 0.1f;
					cube_a.scale_y() += 0.1f;
					cube_a.scale_z() += 0.1f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_X) {
					cube_a.scale_x() -= 0.1f;
					cube_a.scale_y() -= 0.1f;
					cube_a.scale_z() -= 0.1f;
				}


				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					auto& cam = application->GetCamera();

					cam.eye() = { 0.f, 0.f, 0.f };
					cam.look_at() = { 0.f, 0.f, 1.f };
					cam.near() = 2.f;
					cam.far() = 100.f;
					cam.fov() = 40.f;
					cam.size() = 720.f;

					cube_a.scale_x() = 1.f;
					cube_a.scale_y() = 1.f;
					cube_a.scale_z() = 1.f;
				}


				if (event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS) {
					application->GetCamera().fov() += 0.5f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS) {
					application->GetCamera().fov() -= 0.5f;
				}

				break;
			}
		}
		
		// For the background
		application->SetColor(Color(48, 124, 56, 0));

		

		application->UpdateGameObjects();
		application->RenderGameObjects();

		application->SetColor(Color(200, 200, 200, 255));

		application->EndTick();


	}
		
	return EXIT_SUCCESS;
}