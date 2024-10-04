#pragma once

#include "GameScenes.hpp"

#include "AudioPlayer.hpp"
#include "Camera.hpp"
#include "Renderer.hpp"
#include "Timestep.hpp"

namespace ld
{
	class game_state
	{
	public:
		game_state(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_device);

		virtual void awake() = 0;
		virtual void start() = 0;
		virtual void input(birb::input& input) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual game_scene end() = 0;

		birb::scene scene;
		bool scene_over = false;

	protected:
		birb::renderer& renderer;
		birb::window& window;
		birb::camera& camera;
		birb::timestep& timestep;
		birb::audio_player& audio_player;
	};
}
