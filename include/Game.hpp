#pragma once

#include "Camera.hpp"
#include "Color.hpp"
#include "Entity.hpp"
#include "Mesh.hpp"
#include "Renderer.hpp"
#include "Timestep.hpp"

#include "ColorPalette.hpp"

#include <array>
#include <vector>

namespace ld
{
	class game
	{
	public:
		game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::scene& scene);

		void start();
		void input(birb::input& input);
		void update();
		void render();

	private:
		birb::renderer& renderer;
		birb::window& window;
		birb::camera& camera;
		birb::timestep& timestep;
		birb::scene& scene;

		enum class game_state
		{
			main_menu, game
		};

		game_state state{game_state::main_menu};

		// main menu //

		void main_menu_camera_shake();
		void main_menu_update_button_highlights();
		void main_menu_hide();

		birb::entity main_menu = scene.create_entity("Main menu",
				birb::component::transform |
				birb::component::state |
				birb::component::default_shader);

		u8 main_menu_selected_button = 0;
		std::array<birb::entity, 3> main_menu_buttons = {
			scene.create_entity(birb::component::transform |
					birb::component::state |
					birb::component::default_shader), // start button

			scene.create_entity(birb::component::transform |
					birb::component::state |
					birb::component::default_shader), // settings button

			scene.create_entity(birb::component::transform |
					birb::component::state |
					birb::component::default_shader)  // exit button
		};

		std::array<birb::mesh*, 3> main_menu_button_meshes;

		std::array<birb::color, 3> main_menu_button_colors = {
			color_palette::start_game_button,
			color_palette::settings_button,
			color_palette::exit_game_button
		};
	};
}
