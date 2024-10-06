#pragma once

#include "ColorPalette.hpp"
#include "GameState.hpp"

#include "AudioPlayer.hpp"
#include "Entity.hpp"
#include "Mesh.hpp"

#include <array>

namespace ld
{
	class main_menu : public game_state
	{
	public:
		explicit main_menu(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player);

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

		u8 selected_button = 0;
		std::array<birb::entity, 3> buttons = {
			DEFAULT_3D_ENTITY, // start button
			DEFAULT_3D_ENTITY, // settings button
			DEFAULT_3D_ENTITY  // exit button
		};

		std::array<birb::mesh*, 3> button_meshes;

		std::array<birb::color, 3> button_colors = {
			color_palette::start_game_button,
			color_palette::settings_button,
			color_palette::exit_game_button
		};

		std::array<birb::sound_file, 3> button_sounds = {
			birb::sound_file("./assets/sfx/play.wav"),
			birb::sound_file("./assets/sfx/settings.wav"),
			birb::sound_file("./assets/sfx/exit.wav")
		};

		birb::sound_file start_game = birb::sound_file("./assets/sfx/start_game.wav");
	};
}
