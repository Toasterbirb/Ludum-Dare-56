#include "Game.hpp"
#include "GameScenes.hpp"
#include "Model.hpp"

namespace ld
{
	game::game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:game_state(renderer, window, camera, timestep, audio_player)
	{}

	void game::awake()
	{
		birb::model m_suzanne("./assets/suzanne.obj");
		suzanne.add_component(m_suzanne);
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

				default:
					break;
			}
		}
	}

	void game::update()
	{

	}

	void game::render()
	{

	}

	game_scene game::end()
	{
		return game_scene::main_menu;
	}
}
