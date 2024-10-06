#pragma once

#include "Blob.hpp"
#include "BlobKing.hpp"
#include "GameState.hpp"

#include <vector>

namespace ld
{
	class level_state : public game_state
	{
	public:
		level_state(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_device)
		:game_state(renderer, window, camera, timestep, audio_device)
		{}

		virtual void awake() override;
		virtual void start() override;
		virtual void input(birb::input& input) override;
		virtual void update() override;
		virtual void render() override;
		game_scene end() override = 0;

		void blob_tick(std::vector<birb::entity>& walkable_area);

		// disables blob ticking
		bool debug_mode{false};


	protected:
		birb::entity floor = DEFAULT_3D_ENTITY;

		birb::entity goal = scene.create_entity("Goal");

		std::unique_ptr<blob_king> king;
		std::vector<std::unique_ptr<blob>> blobs;

	private:
	};
}
