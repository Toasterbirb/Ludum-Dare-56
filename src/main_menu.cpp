#include "Transform.hpp"

#include "Game.hpp"
#include "State.hpp"

#include <cmath>

namespace ld
{
	void game::main_menu_camera_shake()
	{
		const f64 time = timestep.time_since_startup();
		camera.position.x = std::sin(time * 0.3 + 1) * 0.2;
		camera.position.y = std::cos(time * 0.2) * 0.2;
	}

	void game::main_menu_update_button_highlights()
	{
		// first set all buttons to inactive colors
		for (birb::mesh* m : main_menu_button_meshes)
			m->material.diffuse = color_palette::inactive_button;

		// set the active button to the "active" color
		main_menu_button_meshes.at(main_menu_selected_button)->material.diffuse = main_menu_button_colors.at(main_menu_selected_button);


		constexpr f32 inactive_button_position = -0.08f;
		constexpr f32 active_button_position = 0.05f;

		// move all buttons back to the inactive position
		for (birb::entity& button : main_menu_buttons)
		{
			birb::transform& t = button.get_component<birb::transform>();
			t.position.z = inactive_button_position;
		}

		// move the active button forward
		birb::transform& t = main_menu_buttons.at(main_menu_selected_button).get_component<birb::transform>();
		t.position.z = active_button_position;
	}

	void game::main_menu_hide()
	{
		// disable buttons
		for (birb::entity& button : main_menu_buttons)
			button.get_component<birb::state>().active = false;

		// hide the background
		main_menu.get_component<birb::state>().active = false;
	}
}
