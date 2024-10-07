#pragma once

#include "LevelState.hpp"

namespace ld
{
	class level3 : public level_state
	{
	public:
		explicit level3(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player);

		void awake() override;
		void start() override;
		void input(birb::input& input) override;
		void update() override;
		void render() override;
		game_scene end() override;

	private:
		birb::entity tutorial = DEFAULT_3D_ENTITY;
	};
}
