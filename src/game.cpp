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
		birb::model m_background("./assets/level_select_background.obj");
		level_select_background.add_component(m_background);

		constexpr f32 button_position_offset = 4;
		for (size_t i = 0; i < level_count; ++i)
		{
			const size_t level_num = i + 1;

			button_entities.at(i) = std::make_unique<birb::entity>(
				scene.create_entity(birb::component::transform | birb::component::default_shader)
			);

			// add model
			button_models.at(i).load_model("./assets/level_buttons/level" + std::to_string(level_num) + ".obj");
			button_entities.at(i)->add_component(button_models.at(i));

			// set position
			button_entities.at(i)->get_component<birb::transform>().position.x = i * 2 - button_position_offset;
		}
	}

	void game::start()
	{
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
				{
					birb::shader::directional_light.direction = {-3.8, -9.4, -3};

					scene_over = true;
					next_scene = levels.at(current_level_index);
					break;
				}

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

	}

	void game::render()
	{

	}

	game_scene game::end()
	{
		return next_scene;
	}
}
