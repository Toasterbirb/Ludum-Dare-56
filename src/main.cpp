#include "AudioDevice.hpp"
#include "Camera.hpp"
#include "CameraInfoOverlay.hpp"
#include "PerformanceOverlay.hpp"
#include "Renderer.hpp"
#include "RendererOverlay.hpp"
#include "Timestep.hpp"
#include "Window.hpp"

#include "Level1.hpp"
#include "Level2.hpp"
#include "Level3.hpp"
#include "Level4.hpp"
#include "Level5.hpp"
#include "Level6.hpp"

#include "Game.hpp"
#include "GameScenes.hpp"
#include "MainMenu.hpp"

#define LEVEL(NAME) ld::NAME NAME(renderer, window, camera, timestep, audio_player)
#define LEVEL_PAIR(NAME) { ld::game_scene::NAME, &NAME }

int main(void)
{
	birb::window window("Playground", birb::vec2<int>(1280, 720));
	window.init_imgui();

	birb::timestep timestep;
	birb::renderer renderer;
	birb::camera camera(window.size());

	birb::overlay::performance perf_widget(timestep);
	birb::overlay::renderer_overlay render_widget(renderer);
	birb::overlay::camera_info camera_widget(camera);

	renderer.debug.alloc_camera_info(camera);
	renderer.debug.alloc_performance_stats(timestep);
	renderer.debug.alloc_render_stats(renderer);
	renderer.debug.alloc_world(window);

	birb::audio_device audio_dev;
	birb::audio_player audio_player;

	ld::main_menu main_menu_scene(renderer, window, camera, timestep, audio_player);
	ld::game game_scene(renderer, window, camera, timestep, audio_player);

	// level states
	LEVEL(level1);
	LEVEL(level2);
	LEVEL(level3);
	LEVEL(level4);
	LEVEL(level5);
	LEVEL(level6);

	std::unordered_map<ld::game_scene, ld::game_state*> scenes = {
		{ ld::game_scene::main_menu, &main_menu_scene },
		{ ld::game_scene::game, &game_scene },

		// // levels
		LEVEL_PAIR(level1),
		LEVEL_PAIR(level2),
		LEVEL_PAIR(level3),
		LEVEL_PAIR(level4),
		LEVEL_PAIR(level5),
		LEVEL_PAIR(level6),
	};

	// call awake on each of the scenes
	for (auto& [scene, game_state] : scenes)
		game_state->awake();

	const auto activate_scene = [&](const ld::game_scene scene) -> ld::game_state*
	{
		// return a null pointer if the next scene is the exit scene
		if (scene == ld::game_scene::exit)
			return nullptr;

		birb::ensure(scenes.contains(scene), "Tried to activate a game scene that hasn't been implemented yet");

		scenes.at(scene)->start();
		renderer.set_scene(scenes.at(scene)->scene);
		renderer.debug.alloc_entity_editor(scenes.at(scene)->scene);
		return scenes.at(scene);
	};

	ld::game_state* active_scene = activate_scene(ld::game_scene::main_menu);


	while (!window.should_close())
	{
		// check if the scene should be swapped out
		if (active_scene->scene_over)
		{
			active_scene->scene_over = false;
			renderer.debug.dealloc_entity_editor(); // deallocate the previous entity inspector
			active_scene = activate_scene(active_scene->end()); // swap to the next scene

			// if the next scene is nullptr, the game is over
			if (active_scene == nullptr)
				continue;
		}

		camera.process_input(window, timestep);

		while (window.inputs_available())
		{
			birb::input input = window.next_input();
			active_scene->input(input);
		}

		active_scene->update();

		window.clear();

		active_scene->render();

		renderer.draw_entities(camera, window.size());
		window.flip();

		window.poll();
		timestep.step();
	}

	audio_player.free_sources();
}
