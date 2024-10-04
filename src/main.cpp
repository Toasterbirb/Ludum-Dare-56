#include "Camera.hpp"
#include "CameraInfoOverlay.hpp"
#include "PerformanceOverlay.hpp"
#include "Renderer.hpp"
#include "RendererOverlay.hpp"
#include "Scene.hpp"
#include "Timestep.hpp"
#include "Window.hpp"

#include "Game.hpp"

int main(void)
{
	birb::window window("Playground", birb::vec2<int>(1280, 720));
	window.init_imgui();

	birb::timestep timestep;
	birb::renderer renderer;
	birb::camera camera(window.size());
	birb::scene scene;

	birb::overlay::performance perf_widget(timestep);
	birb::overlay::renderer_overlay render_widget(renderer);
	birb::overlay::camera_info camera_widget(camera);

	renderer.set_scene(scene);

	renderer.debug.alloc_camera_info(camera);
	renderer.debug.alloc_entity_editor(scene);
	renderer.debug.alloc_performance_stats(timestep);
	renderer.debug.alloc_render_stats(renderer);
	renderer.debug.alloc_world(window);

	ld::game game(renderer, window, camera, timestep, scene);
	game.start();

	while (!window.should_close())
	{
		camera.process_input(window, timestep);

		while (window.inputs_available())
		{
			birb::input input = window.next_input();
			game.input(input);
		}

		game.update();

		window.clear();

		game.render();

		renderer.draw_entities(camera, window.size());
		window.flip();

		window.poll();
		timestep.step();
	}
}
