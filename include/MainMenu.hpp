#pragma once

#include "ColorPalette.hpp"
#include "GameState.hpp"

#include "Entity.hpp"
#include "Mesh.hpp"

#include <array>

namespace ld
{
	class main_menu : public game_state
	{
	public:
		explicit main_menu(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep);

		void awake() override;
		void start() override;
		void input(birb::input& input) override;
		void update() override;
		void render() override;
		game_scene end() override;

	private:
		// main menu //

		void main_menu_camera_shake();
		void main_menu_update_button_highlights();
		void main_menu_hide();

		birb::entity main_menu_background = scene.create_entity("Main menu",
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
