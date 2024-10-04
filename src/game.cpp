#include "Game.hpp"
#include "GameScenes.hpp"
#include "Model.hpp"
#include "RaycastTarget.hpp"
#include "Raycasting.hpp"
#include "Transform.hpp"

namespace ld
{
	game::game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:game_state(renderer, window, camera, timestep, audio_player)
	{}

	void game::awake()
	{
		birb::model m_suzanne("./assets/suzanne.obj");

		birb::raycast_target r_suzanne;
		r_suzanne.radius = 1.0f;

		suzanne.add_components(m_suzanne, r_suzanne);
	}

	void game::start()
	{
		camera.mouse_controls_enabled = true;
		camera.keyboard_controls_enabled = true;

		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { -1.68902, -0.157325, 4.73655 };
		camera.pitch = 2.1;
		camera.yaw = 292.1;

		suzanne_mesh = suzanne.get_component<birb::model>().get_mesh_by_name("Suzanne");
	}

	void game::input(birb::input& input)
	{
		if (input.state == birb::input::action::key_down)
		{
			switch (input.key)
			{
				case birb::input::keycode::e:
					scene_over = true;
					break;

				case birb::input::keycode::mouse_left:
					std::cout << camera.raycast(birb::camera::raycast_type::fps, window) << '\n';
					break;

				default:
					break;
			}
		}
	}

	void game::update()
	{
		const birb::vec3<f32> ray = camera.raycast(birb::camera::raycast_type::fps, window);
		if (birb::raycast_hit(ray, scene, camera.position).has_value())
			suzanne_mesh->material.diffuse = 0xc0c741;
		else
			suzanne_mesh->material.diffuse = 0x1f0e1c;
	}

	void game::render()
	{

	}

	game_scene game::end()
	{
		return game_scene::main_menu;
	}
}
