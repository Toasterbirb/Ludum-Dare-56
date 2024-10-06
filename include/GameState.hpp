#pragma once

#include "GameScenes.hpp"

#include "AudioPlayer.hpp"
#include "Camera.hpp"
#include "Direction.hpp"
#include "Entity.hpp"
#include "Font.hpp"
#include "FontManager.hpp"
#include "PhysicsWorld.hpp"
#include "Random.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"
#include "Text.hpp"
#include "Timestep.hpp"

#define DEFAULT_3D_ENTITY scene.create_entity(birb::component::transform | birb::component::default_shader)

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

		direction held_direction();

		birb::scene scene;
		birb::physics_world world;
		bool scene_over = false;
		birb::random rng;

	protected:
		birb::renderer& renderer;
		birb::window& window;
		birb::camera& camera;
		birb::timestep& timestep;
		birb::audio_player& audio_player;
	};
}
