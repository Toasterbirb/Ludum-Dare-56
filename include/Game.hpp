#pragma once

#include "Entity.hpp"
#include "GameState.hpp"
#include "GameScenes.hpp"
#include "Model.hpp"

namespace ld
{
	class game : public game_state
	{
	public:
		explicit game(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player);

		void awake() override;
		void start() override;
		void input(birb::input& input) override;
		void update() override;
		void render() override;
		game_scene end() override;

	private:
		birb::entity level_select_background = scene.create_entity("Background",
			birb::component::transform | birb::component::default_shader
		);

		static constexpr u8 level_count = 1;
		size_t current_level_index{0};
		game_scene next_scene;

		// Instantiate levels
		std::array<game_scene, level_count> levels = {
			game_scene::level1
		};

		std::array<std::unique_ptr<birb::entity>, level_count> button_entities;
		std::array<birb::model, level_count> button_models;
	};
}
