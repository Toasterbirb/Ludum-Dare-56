#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "Level2.hpp"
#include "Model.hpp"

namespace ld
{
	level2::level2(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void level2::awake()
	{
		blobs.resize(3);
		level_state::awake();

		birb::model m_floor("./assets/level2.obj");
		floor.add_component(m_floor);

		// setup goal collider
		birb::collider::box c_goal;
		c_goal.set_position({0, 1.0, -4});
		c_goal.set_size({2, 2, 2});
		goal.add_component(c_goal);

		// setup walkable area collider
		{
			birb::collider::box c_walk_area;
			c_walk_area.set_position({-2, 1, -2});
			c_walk_area.set_size({2, 2, 6});
			walkable_area[0].add_component(c_walk_area);
		}
		{
			birb::collider::box c_walk_area;
			c_walk_area.set_position({0, 1.0, 0});
			c_walk_area.set_size({2, 2, 2});
			walkable_area[1].add_component(c_walk_area);
		}
	}

	void level2::start()
	{
		level_state::start();

		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { 7, 3.0, 0.1 };
		camera.pitch = -28;
		camera.yaw = 200;
	}

	void level2::input(birb::input& input)
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

	void level2::update()
	{
		level_state::update();
		blob_tick(walkable_area);
	}

	void level2::render()
	{
		level_state::render();

	}

	game_scene level2::end()
	{
		return game_scene::game;
	}
}
