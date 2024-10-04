#include "Game.hpp"

#include "Camera.hpp"
#include "Info.hpp"
#include "Input.hpp"
#include "Model.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Timestep.hpp"
#include "Window.hpp"

namespace ld
{
	game::game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::scene& scene)
	:renderer(renderer),
	 window(window),
	 camera(camera),
	 timestep(timestep),
	 scene(scene)
	{}

	void game::start()
	{
#ifndef NDEBUG
		window.hot_reload_assets_on_focus_change = true;
#endif

		window.lock_cursor_to_window();

		birb::model m_main_menu("./assets/main_menu.obj");
		main_menu.add_component(m_main_menu);

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

		main_menu_update_button_highlights();

		// setup the camera for the main menu
		camera.mouse_controls_enabled = false;
		camera.keyboard_controls_enabled = false;
		camera.position = { 0.0f, 0.0f, 6.0f };
		camera.yaw = -90;
		camera.pitch = 0;
	}

	void game::input(birb::input& input)
	{
		if (input.state == birb::input::action::key_down)
		{
			switch (state)
			{
				case game_state::main_menu:
				{
					switch (input.key)
					{
						// case (birb::input::keycode::escape):
						// 	window.quit();

						case (birb::input::keycode::up):
						{
							main_menu_selected_button = main_menu_selected_button > 0
								? main_menu_selected_button - 1
								: 0;
							main_menu_update_button_highlights();
							break;
						}

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
									main_menu_hide();
									state = game_state::game;
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
					break;
				}

				case game_state::game:
				{
					break;
				}
			}
		}
	}

	void game::update()
	{
		switch (state)
		{
			case game_state::main_menu:
			{
				main_menu_camera_shake();
				break;
			};

			case game_state::game:
			{
				break;
			};
		}
	}

	void game::render()
	{

	}
}
