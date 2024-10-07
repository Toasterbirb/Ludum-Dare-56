#pragma once

#include "Entity.hpp"
#include "GameScenes.hpp"
#include "LevelState.hpp"

namespace ld
{
	class game : public level_state
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
		birb::entity time_score_text = scene.create_entity("Time");
		birb::entity rescued_text = scene.create_entity("Rescued");
		birb::entity help_text = scene.create_entity("Help");
	};
}
