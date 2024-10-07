#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "Level1.hpp"
#include "Model.hpp"
#include "Model.hpp"

#include <iostream>

namespace ld
{
	level1::level1(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void level1::awake()
	{
		blobs.resize(2);
		level_state::awake();

		floor_layout = {
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,1,1,1,0,0,0,
			0,0,0,0,0,0,0,0,0,0,
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

	void level1::start()
	{
		level_state::start();


		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { -4.49019, 4.56978, 3.54651 };
		camera.pitch = -32.9;
		camera.yaw = 15.8;

		rescued_blobs = 0;

		// reset the timer and boosts when the first level starts
		timer = 0;

		// use the same seed on every round
		rng.seed(42);

		// setup lighting
		birb::shader::directional_light.direction = {1, -1.7, 0};
		birb::shader::directional_light.ambient = { 0, 0, 0 };
		birb::shader::directional_light.diffuse = { 0, 0, 0 };
		birb::shader::directional_light.specular = { 0, 0, 0 };
	}

	void level1::input(birb::input& input)
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

	void level1::update()
	{
		level_state::update();
		blob_tick();
	}

	void level1::render()
	{
		level_state::render();

	}

	game_scene level1::end()
	{
		return game_scene::level2;
	}
}
