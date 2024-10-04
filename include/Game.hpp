#pragma once

#include "Entity.hpp"
#include "GameState.hpp"
#include "Mesh.hpp"

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
		birb::entity suzanne = scene.create_entity("Suzanne",
				birb::component::transform | birb::component::default_shader);

		birb::mesh* suzanne_mesh{nullptr};
	};
}
