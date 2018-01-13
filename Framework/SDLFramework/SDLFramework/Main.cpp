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

	Square2d square{ 150.f, 125.f, 25.f, 25.f };
	
	application->SetTargetFPS(120);
	application->SetColor(Color(48, 124, 56, 0));


	DebugDisplay dd {
		[application]() -> DebugDisplay::debug_list {
			return {
				std::make_pair("LINAL", "v0.1"),
				std::make_pair("Time", std::to_string(static_cast<float>(application->GetTimeSinceStartedMS()) / 1000.f)),
			};
		}
	};

	application->AddRenderable(&dd);
	application->AddRenderable(&square);

	while (application->IsRunning())
	{
		application->StartTick();
		

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				application->Quit();
				break;
			case SDL_KEYDOWN:
				// About what it's supposed to do

				break;
			}
		}
		
		// For the background
		application->SetColor(Color(48, 124, 56, 0));

		application->UpdateGameObjects();
		application->RenderGameObjects();

		application->SetColor(Color(48, 124, 56, 0));

		application->EndTick();


	}
		
	return EXIT_SUCCESS;
}