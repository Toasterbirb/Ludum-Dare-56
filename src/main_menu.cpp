#include "MainMenu.hpp"

#include "Model.hpp"
#include "State.hpp"
#include "Transform.hpp"

#include <cmath>

namespace ld
{
	main_menu::main_menu(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep)
	:game_state(renderer, window, camera, timestep)
	{}

	void main_menu::awake()
	{
		birb::model m_main_menu("./assets/main_menu.obj");
		main_menu_background.add_component(m_main_menu);

		// setup buttons
		birb::model m_start("./assets/main_menu_button_start.obj");
		main_menu_buttons[0].add_component(m_start);
		main_menu_button_meshes[0] = m_start.get_mesh_by_name("start_button");
		birb::ensure(main_menu_button_meshes[0] != nullptr, "Can't find the main menu start button mesh");

		birb::model m_settings("./assets/main_menu_button_settings.obj");
		main_menu_buttons[1].add_component(m_settings);
		main_menu_button_meshes[1] = m_settings.get_mesh_by_name("settings_button");
		birb::ensure(main_menu_button_meshes[1] != nullptr, "Can't find the main menu settings button mesh");

		birb::model m_exit("./assets/main_menu_button_exit.obj");
		main_menu_buttons[2].add_component(m_exit);
		main_menu_button_meshes[2] = m_exit.get_mesh_by_name("exit_button");
		birb::ensure(main_menu_button_meshes[2] != nullptr, "Can't find the main menu exit button mesh");
	}

	void main_menu::start()
	{
#ifndef NDEBUG
		window.hot_reload_assets_on_focus_change = true;
#endif

		window.lock_cursor_to_window();

		main_menu_update_button_highlights();

		// setup the camera for the main menu
		camera.mouse_controls_enabled = false;
		camera.keyboard_controls_enabled = false;
		camera.position = { 0.0f, 0.0f, 6.0f };
		camera.yaw = -90;
		camera.pitch = 0;
	}

	void main_menu::input(birb::input& input)
	{
		if (input.state == birb::input::action::key_down)
		{
			switch (input.key)
			{
				// case (birb::input::keycode::escape):
				// 	window.quit();

				case (birb::input::keycode::w):
				case (birb::input::keycode::k):
				case (birb::input::keycode::up):
				{
					main_menu_selected_button = main_menu_selected_button > 0
						? main_menu_selected_button - 1
						: 0;
					main_menu_update_button_highlights();
					break;
				}

				case (birb::input::keycode::s):
				case (birb::input::keycode::j):
				case (birb::input::keycode::down):
				{
					main_menu_selected_button = main_menu_selected_button < main_menu_buttons.size() - 1
						? main_menu_selected_button + 1
						: main_menu_buttons.size() - 1;
					main_menu_update_button_highlights();
					break;
				}

				case (birb::input::keycode::enter):
				{
					switch (main_menu_selected_button)
					{
						case 0:
							scene_over = true;
							break;

						case 1:
							break;

						case 2:
							window.quit();
							break;

						default:
							birb::ensure(true == false, "Invalid button was pressed");
							break;
					}
				}

				default:
					break;
			}
		}
	}

	void main_menu::update()
	{
		main_menu_camera_shake();
	}

	void main_menu::render()
	{

	}

	game_scene main_menu::end()
	{
		// if we are not closing, assume that the game should be started

		if (window.should_close())
			return game_scene::exit;

		return game_scene::game;
	}

	void main_menu::main_menu_camera_shake()
	{
		const f64 time = timestep.time_since_startup();
		camera.position.x = std::sin(time * 0.3 + 1) * 0.2;
		camera.position.y = std::cos(time * 0.2) * 0.2;
	}

	void main_menu::main_menu_update_button_highlights()
	{
		// first set all buttons to inactive colors
		for (birb::mesh* m : main_menu_button_meshes)
			m->material.diffuse = color_palette::inactive_button;

		// set the active button to the "active" color
		main_menu_button_meshes.at(main_menu_selected_button)->material.diffuse = main_menu_button_colors.at(main_menu_selected_button);


		constexpr f32 inactive_button_position = -0.08f;
		constexpr f32 active_button_position = 0.05f;

		// move all buttons back to the inactive position
		for (birb::entity& button : main_menu_buttons)
		{
			birb::transform& t = button.get_component<birb::transform>();
			t.position.z = inactive_button_position;
		}

		// move the active button forward
		birb::transform& t = main_menu_buttons.at(main_menu_selected_button).get_component<birb::transform>();
		t.position.z = active_button_position;
	}

	void main_menu::main_menu_hide()
	{
		// disable buttons
		for (birb::entity& button : main_menu_buttons)
			button.get_component<birb::state>().active = false;

		// hide the background
		main_menu_background.get_component<birb::state>().active = false;
	}
}
