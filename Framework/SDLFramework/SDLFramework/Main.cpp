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
#include "TargetCube.h"
#include "Ship.h"
#include "RandomGenerator.h"
#include "Bullet.h"
#include <iomanip>
#include "Main.h"

void fire_bullet(Cube3d &bullet, Ship &ship)
{
	Matrix spawn_on_matrix = ship.transform(Vec{ 0.f, -3.f, 0.f, 1.f });
	Vec4 spawn_on = spawn_on_matrix[0];

	bullet.is_active(true);
	bullet.visible() = true;
	bullet.heading() = ship.up();
	bullet.roll() = ship.roll();
	bullet.dive() = ship.dive();
	bullet.turn() = ship.turn();
	bullet.x() = spawn_on.x();
	bullet.y() = spawn_on.y();
	bullet.z() = spawn_on.z();

	bullet.speed() = ship.speed() + 100.f;
}

int main(int args[])
{
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
	camera.fov() = 90.f;
	camera.size() = 720.f;

	application->SetCamera(camera);

	Ship ship{ 0.f, 0.f, 200.f, 10.f, 20.f, 10.f };
	TargetCube target_cube{ -100.f, 0.f, 200.f, 20.f, 20.f, 20.f };
	
	Cube3d bullet1{ 0.f, 0.f, 200.f, 2.5f, 20.f, 2.5f };
	set_bullet(bullet1);

	Cube3d bullet2{ 0.f, 0.f, 200.f, 2.5f, 20.f, 2.5f };
	set_bullet(bullet2);

	Cube3d bullet3{ 0.f, 0.f, 200.f, 2.5f, 20.f, 2.5f };
	set_bullet(bullet3);

	ship.dampening() = 0.f;
	
	int bullet_count = 0;

	std::vector<Cube3d> cubes;

	for (size_t i = 0; i < 6; i++)
	{
		float x = random(-400.f, 400.f);
		float y = random(-400.f, 400.f);
		float z = random(100.f, 200.f);

		float size = random(5.f, 20.f);

		cubes.push_back(Cube3d{ x, y, z, size, size, size });
	}

	for (Cube3d& cube : cubes) {
		application->AddRenderable(&cube);
	}

	target_cube.line_color(Color(255, 0, 0, 255));
	
	application->SetTargetFPS(60);
	application->SetColor(Color(48, 124, 56, 0));


	DebugDisplay dd {
		[application, &ship]() -> DebugDisplay::debug_list {

			std::stringstream fov;
			fov << std::fixed << std::setprecision(1) << application->GetCamera().fov();

			std::stringstream fps;
			fps << std::fixed << std::setprecision(1) << 1.0f / application->DeltaTime();

			std::stringstream time;
			time << std::fixed << std::setprecision(1) << static_cast<float>(application->GetTimeSinceStartedMS()) / 1000.f;

			return {
				std::make_pair("LINAL", "v0.1"),
				std::make_pair("Time", time.str()),
				std::make_pair("fps", fps.str()),
				std::make_pair("fov", fov.str()),
			};
		}
	, 10, 1};

	float bullet1_dist = 0.0f;
	float bullet2_dist = 0.0f;
	float bullet3_dist = 0.0f;
	float bullet_dist = 0.0f;

	DebugDisplay dd2{
		[&ship, &target_cube, &bullet_dist]() -> DebugDisplay::debug_list {

			std::stringstream pos;
			pos << "( " << std::setw(8) << std::fixed << std::setprecision(2) << ship.location()[0]
				<< ", " << std::setw(8) << std::fixed << std::setprecision(2) << ship.location()[1]
				<< ", " << std::setw(8) << std::fixed << std::setprecision(2) << ship.location()[2]
				<< " )";

			std::stringstream speed;
			speed << std::fixed << std::setw(6) << std::setprecision(2) << ship.velocity().length();


			std::stringstream target_dist;
			target_dist << std::fixed << std::setw(6) << std::setprecision(2) << (ship.location() - target_cube.location()).length();

			std::stringstream b_dist;
			b_dist << std::fixed << std::setw(6) << std::setprecision(2) << bullet_dist;

			return {
				std::make_pair("ship speed", speed.str()),
				std::make_pair("ship pos", pos.str()),
				std::make_pair("target dist", target_dist.str()),
				std::make_pair("bullet dist", b_dist.str()),
			};
		}
	, 10, 14};

	/*DebugDisplay dd3{
		[application, &ship]() -> DebugDisplay::debug_list {

		std::stringstream eye;
		eye << "( " << std::setw(8) << std::fixed << std::setprecision(4) << application->GetCamera().eye()[0]
			<< ", " << std::setw(8) << std::fixed << std::setprecision(4) << application->GetCamera().eye()[1]
			<< " )";

		std::stringstream look_at;
		look_at << "( " << std::setw(8) << std::fixed << std::setprecision(4) << application->GetCamera().look_at()[0]
			<< ", " << std::setw(8) << std::fixed << std::setprecision(4) << application->GetCamera().look_at()[1]
			<< " )";

		return {
			std::make_pair("eye", eye.str()),
			std::make_pair("look at", look_at.str()),
		};
	}
	, 10, 28 };*/

	application->AddRenderable(&dd);
	application->AddRenderable(&dd2);
	//application->AddRenderable(&dd3);

	application->AddRenderable(&ship);
	application->AddRenderable(&target_cube);
	application->AddRenderable(&bullet1);
	application->AddRenderable(&bullet2);
	application->AddRenderable(&bullet3);

	constexpr float movement = 10.f;
	constexpr float camera_movement = 10.f;

	float rotation = 0.f;
	float roll_angle = 0.f;
	float z_angle = 0.f;
	float track_ship = true;

	bool fire = false;
	bool fire_done = false;

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
					ship.z() += 0.1f;
				else if (event.wheel.x == -1)
					ship.z() -= 0.1f;
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
					track_ship = false;
					application->GetCamera().eye()[1] += camera_movement;
					application->GetCamera().look_at()[1] += camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_DOWN) {
					track_ship = false;
					application->GetCamera().eye()[1] -= camera_movement;
					application->GetCamera().look_at()[1] -= camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_LEFT) {
					track_ship = false;
					application->GetCamera().eye()[0] += camera_movement;
					application->GetCamera().look_at()[0] += camera_movement;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
					track_ship = false;
					application->GetCamera().eye()[0] -= camera_movement;
					application->GetCamera().look_at()[0] -= camera_movement;
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

				if (event.key.keysym.scancode == SDL_SCANCODE_I) {
					application->GetCamera().eye()[1] += 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_K) {
					application->GetCamera().eye()[1] -= 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_J) {
					application->GetCamera().eye()[0] += 0.01f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_L) {
					application->GetCamera().eye()[0] -= 0.01f;
				}

				/*if (event.key.keysym.scancode == SDL_SCANCODE_W) {
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
				}*/

				if (event.key.keysym.scancode == SDL_SCANCODE_I) {
					application->SetShowDebug(!application->IsShowDebug());
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_Z) {
					ship.scale_x() += 0.1f;
					ship.scale_y() += 0.1f;
					ship.scale_z() += 0.1f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_X) {
					ship.scale_x() -= 0.1f;
					ship.scale_y() -= 0.1f;
					ship.scale_z() -= 0.1f;
				}


				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					auto& cam = application->GetCamera();

					cam.eye() = { 0.f, 0.f, 0.f };
					cam.look_at() = { 0.f, 0.f, 1.f };
					cam.near() = 2.f;
					cam.far() = 100.f;
					cam.fov() = 80.f;
					cam.size() = 720.f;

					ship.scale_x() = 1.f;
					ship.scale_y() = 1.f;
					ship.scale_z() = 1.f;

					track_ship = true;
				}


				if (event.key.keysym.scancode == SDL_SCANCODE_KP_PLUS) {
					application->GetCamera().fov() += 0.5f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_KP_MINUS) {
					application->GetCamera().fov() -= 0.5f;
				}

				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE) {

					if (bullet_count == 0)
						fire_bullet(bullet1, ship);
					else if (bullet_count == 1)
						fire_bullet(bullet2, ship);
					else if (bullet_count == 2)
						fire_bullet(bullet3, ship);

					bullet_count++;
					if (bullet_count > 2)
						bullet_count = 0;
				}

				break;
			}
		}

		SDL_PumpEvents();

		int keys_down;
		const uint8_t* keys = SDL_GetKeyboardState(&keys_down);

		float direction = 0.f;

		if (keys[SDL_SCANCODE_LSHIFT]) {
			direction = 1.f;
		}

		if (keys[SDL_SCANCODE_LCTRL]) {
			direction = -1.f;
		}

		if (keys[SDL_SCANCODE_W]) {
			ship.dive() += 1.f;
		}
		else if (keys[SDL_SCANCODE_S]) {
			ship.dive() -= 1.f;
		}

		if (keys[SDL_SCANCODE_A]) {
			ship.turn() += 2.5f;
		}

		if (keys[SDL_SCANCODE_D]) {
			ship.turn() -= 2.5f;
		}

		if (keys[SDL_SCANCODE_Q]) {
			ship.roll() += 2.5f;
		}

		if (keys[SDL_SCANCODE_E]) {
			ship.roll() -= 2.5f;
		}

		if (keys[SDL_SCANCODE_F]) {
			ship.roll() = 0.f;
			ship.dive() = 0.f;
			ship.turn() = 0.f;
		}

		bullet1_dist = (bullet1.location() - target_cube.location()).length();
		bullet2_dist = (bullet2.location() - target_cube.location()).length();
		bullet3_dist = (bullet3.location() - target_cube.location()).length();

		bullet_dist = std::min(bullet1_dist, std::min(bullet2_dist, bullet3_dist));

		if (bullet1_dist <= target_cube.scale_x() * target_cube.width() || bullet1_dist > 1000.f) {
			bullet1.visible() = false;
			bullet1.speed() = 0.f;
		}

		if (bullet2_dist <= target_cube.scale_x() * target_cube.width() || bullet2_dist > 1000.f) {
			bullet2.visible() = false;
			bullet2.speed() = 0.f;
		}

		if (bullet3_dist <= target_cube.scale_x() * target_cube.width() || bullet3_dist > 1000.f) {
			bullet3.visible() = false;
			bullet3.speed() = 0.f;
		}

		ship.heading() = ship.up();
		ship.speed() += movement * direction;

		//bullet.speed() += movement * direction;
		
		// For the background
		application->SetColor(Color(48, 124, 56, 0));

		
		//constexpr int point_size = 5;
		//constexpr int half_point_size = point_size / 2;

		//int end_x = 720 / 2;
		//int end_y = 720 / 2;

		//application->SetColor(Color(204, 141, 16, 128));
		//application->DrawRect(end_x - half_point_size, end_y - half_point_size, point_size, point_size, true);

		application->UpdateGameObjects();
		application->RenderGameObjects();

		application->SetColor(Color(200, 200, 200, 255));

		application->EndTick();

		if (track_ship) {
			application->GetCamera().eye()[0] = ship.x();
			application->GetCamera().look_at()[0] = ship.x();

			application->GetCamera().eye()[1] = ship.y() + 160.f;
			application->GetCamera().look_at()[1] = ship.y() + 159.0f;
		}

		
	}
		
	return EXIT_SUCCESS;
}

void set_bullet(Cube3d &bullet)
{
	bullet.visible() = false;
	bullet.dampening() = 0.f;
	bullet.vmax() = 1000.f;
	bullet.line_color(Color(66, 158, 244, 255));
}
