#include "BoxCollider.hpp"
#include "GameScenes.hpp"
#include "Info.hpp"
#include "Level3.hpp"
#include "Model.hpp"
#include "Transform.hpp"

namespace ld
{
	level3::level3(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void level3::awake()
	{
		blobs.resize(4);
		level_state::awake();

		birb::model m_floor("./assets/level3.obj");
		floor.add_component(m_floor);

		// setup goal collider
		birb::collider::box c_goal;
		c_goal.set_position({0, 1.0, -4});
		c_goal.set_size({2, 2, 2});
		goal.add_component(c_goal);

		// setup walkable area collider
		birb::collider::box c_walk_area;
		c_walk_area.set_position({0, 1, -2});
		c_walk_area.set_size({2, 2, 6});
		walkable_area[0].add_component(c_walk_area);

		// setup the hazard
		hazard.add_component(birb::info("Hazard"));

		birb::collider::box c_hazard(hazard.get_component<birb::transform>());
		c_hazard.set_size(2);
		c_hazard.set_position({0, 1, -2});
		hazard.add_component(c_hazard);

		birb::model m_hazard("./assets/level3_hazard.obj");
		hazard.add_component(m_hazard);
		hazard.add_component(hazard_tag{});
	}

	void level3::start()
	{
		level_state::start();

		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { 7, 3.0, 0.1 };
		camera.pitch = -28;
		camera.yaw = 200;
	}

	void level3::input(birb::input& input)
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

	void level3::update()
	{
		level_state::update();
		blob_tick(walkable_area);

		const auto move_hazard = [&](const f32 offset)
		{
			hazard.get_component<birb::transform>().position.y += offset;

			birb::vec3<f32> collider_pos = hazard.get_component<birb::collider::box>().position();
			collider_pos.y += offset;
			hazard.get_component<birb::collider::box>().set_position(collider_pos);
		};

		hazard_timer -= timestep.deltatime();
		if (hazard_timer < 0)
		{
			if (hazard_down)
			{
				move_hazard(hazard_height);
			}
			else
			{
				move_hazard(-hazard_height);
				audio_player.play_sound(*sound_effects.at(static_cast<i32>(sfx::hazard_fall)));
				start_camera_shake(0.2, 0.2);
			}

			hazard_down = !hazard_down;
			hazard_timer = hazard_delay;
		}
	}

	void level3::render()
	{
		level_state::render();

	}

	game_scene level3::end()
	{
		return game_scene::level4;
	}
}
