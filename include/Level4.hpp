#pragma once

#include "LevelState.hpp"

namespace ld
{
	class level4 : public level_state
	{
	public:
		explicit level4(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player);

		void awake() override;
		void start() override;
		void input(birb::input& input) override;
		void update() override;
		void render() override;
		game_scene end() override;

	private:
	};
}
