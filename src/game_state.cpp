#include "GameState.hpp"

#include "Camera.hpp"
#include "Renderer.hpp"
#include "Timestep.hpp"
#include "Window.hpp"

namespace ld
{
	game_state::game_state(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_player)
	:renderer(renderer),
	 window(window),
	 camera(camera),
	 timestep(timestep),
	 audio_player(audio_player)
	 // font()
	 // blobs_saved("Blobs saved: 0", font, {10, 10, 0})
	{
		world.set_scene(scene);
	}

	direction game_state::held_direction()
	{
		const bool left = window.is_key_held(birb::input::keycode::right) || window.is_key_held(birb::input::keycode::d);
		const bool right = window.is_key_held(birb::input::keycode::left) || window.is_key_held(birb::input::keycode::a);
		const bool up = window.is_key_held(birb::input::keycode::down) || window.is_key_held(birb::input::keycode::s);
		const bool down = window.is_key_held(birb::input::keycode::up) || window.is_key_held(birb::input::keycode::w);

		if (up && right)
			return direction::koillinen;

		if (down && right)
			return direction::kaakko;

		if (down && left)
			return direction::lounas;

		if (up && left)
			return direction::luode;

		if (left)
			return direction::left;

		if (right)
			return direction::right;

		if (up)
			return direction::up;

		if (down)
			return direction::down;

		return direction::none;
	}
}
