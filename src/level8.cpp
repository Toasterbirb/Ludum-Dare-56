#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "Level8.hpp"
#include "Model.hpp"
#include "Model.hpp"

#include <iostream>

namespace ld
{
	level8::level8(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void level8::awake()
	{
		blobs.resize(4);
		level_state::awake();

		floor_layout = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,1,1,0,0,0,
			0,0,0,0,1,0,1,0,0,0,
			0,0,0,0,1,0,1,0,0,0,
			0,0,0,0,1,0,1,0,0,0,
			0,0,0,0,0,1,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
		};

		goal_locations = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
		};

		load_level();
	}

	void level8::start()
	{
		level_state::start();


		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { -10.4083, 5.27306, 3.34636 };
		camera.pitch = -30;
		camera.yaw = 12.5;

		// use the same seed on every round
		rng.seed(42);

		// setup lighting
		birb::shader::directional_light.direction = {1, -1.7, 0};
	}

	void level8::input(birb::input& input)
	{
		level_state::input(input);

		if (input.state == birb::input::action::key_down)
		{
			switch (input.key)
			{
				default:
					break;
			}
		}
	}

	void level8::update()
	{
		level_state::update();
		blob_tick();
	}

	void level8::render()
	{
		level_state::render();

	}

	game_scene level8::end()
	{
		return game_scene::level9;
	}
}
