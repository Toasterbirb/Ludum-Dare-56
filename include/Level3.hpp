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
		std::vector<birb::entity> walkable_area = { scene.create_entity("Walkable area") };
		birb::entity hazard = DEFAULT_3D_ENTITY;
		f32 hazard_timer{0};
		const f32 hazard_delay{1.0f};

		bool hazard_down{true};
		const f32 hazard_height{2.0f};
	};
}
