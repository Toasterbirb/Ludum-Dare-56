#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "Level10.hpp"
#include "Model.hpp"
#include "Model.hpp"

#include <iostream>

namespace ld
{
	level10::level10(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void level10::awake()
	{
		blobs.resize(10);
		level_state::awake();

		floor_layout = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,0,0,0,0,0,
			0,0,0,0,0,1,0,0,0,0,
			0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
		};

		goal_locations = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
		};

		hazard_layout = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,1,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
		};

		load_level();
	}

	void level10::start()
	{
		level_state::start();


		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { -4.49019, 4.56978, 3.54651 };
		camera.pitch = -32.9;
		camera.yaw = 15.8;

		// use the same seed on every round
		rng.seed(42);

		// setup lighting
		birb::shader::directional_light.direction = {1, -1.7, 0};
	}

	void level10::input(birb::input& input)
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

	void level10::update()
	{
		level_state::update();
		blob_tick();
		update_hazards();
	}

	void level10::render()
	{
		level_state::render();

	}

	game_scene level10::end()
	{
		return game_scene::game;
	}
}
