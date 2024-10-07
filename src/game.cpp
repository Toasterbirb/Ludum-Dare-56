#include "Game.hpp"
#include "GameScenes.hpp"
#include "Model.hpp"
#include "Stopwatch.hpp"
#include "Text.hpp"

namespace ld
{
	game::game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:level_state(renderer, window, camera, timestep, audio_player)
	{}

	void game::awake()
	{
	}

	void game::start()
	{
		// create the text component during start()
		// the mononoki font might not exist during awake()
		if (!time_score_text.has_component<birb::text>())
		{
			birb::text t_time("Time", *big_mononoki, {static_cast<f32>(window.size().y), 540, 0});
			time_score_text.add_component(t_time);

			birb::text t_rescued("Rescued", *big_mononoki, {static_cast<f32>(window.size().y), 620, 0});
			rescued_text.add_component(t_rescued);

			birb::text t_help("Return to the main menu by hitting the Enter key", *mononoki, {static_cast<f32>(window.size().y - 80), 450, 0});
			help_text.add_component(t_help);
		}

		// set the texts
		time_score_text.get_component<birb::text>().set_text("Time: " + birb::stopwatch::format_time(timer));
		rescued_text.get_component<birb::text>().set_text("Blobs rescued: " + std::to_string(rescued_blobs));

		camera.mouse_controls_enabled = false;
		camera.keyboard_controls_enabled = false;

		// avoid cursor jumps by polling input before setting camera position
		// and rotation
		camera.process_input(window, timestep);

		camera.position = { 0.0f, 0.0f, 6.0f };
		camera.yaw = -90;
		camera.pitch = 0;
	}

	void game::input(birb::input& input)
	{
		if (input.state == birb::input::action::key_down)
		{
			switch (input.key)
			{
				case birb::input::keycode::enter:
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
