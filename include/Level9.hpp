#pragma once

#include "LevelState.hpp"
#include "PhysicsWorld.hpp"

namespace ld
{
	class level9 : public level_state
	{
	public:
		explicit level9(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player);

		void awake() override;
		void start() override;
		void input(birb::input& input) override;
		void update() override;
		void render() override;
		game_scene end() override;

	private:
	};
}
