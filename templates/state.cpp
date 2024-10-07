#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "TEMPLATE.hpp"
#include "Model.hpp"
#include "Model.hpp"

#include <iostream>

namespace ld
{
	TEMPLATE::TEMPLATE(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void TEMPLATE::awake()
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

	void TEMPLATE::start()
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

	void TEMPLATE::input(birb::input& input)
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

	void TEMPLATE::update()
	{
		level_state::update();
		blob_tick();
	}

	void TEMPLATE::render()
	{
		level_state::render();

	}

	game_scene TEMPLATE::end()
	{
		return game_scene::level2;
	}
}
