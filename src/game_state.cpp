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
	{}

}
