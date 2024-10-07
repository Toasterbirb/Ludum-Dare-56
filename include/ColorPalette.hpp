#pragma once

#include "Color.hpp"
#include "Vector.hpp"

namespace ld
{
	namespace color_palette
	{
		static constexpr birb::color start_game_button = 0x98BB6C;
		static constexpr birb::color settings_button = 0xDCA561;
		static constexpr birb::color exit_game_button = 0xC34043;
		static constexpr birb::color inactive_button = 0x54546D;

		static constexpr birb::vec3<f32> point_diffuse = { 0.7f, 0.4f, 0.4f };
		static constexpr birb::vec3<f32> point_specular = { 1.0f, 0.0f, 0.0f };
		static constexpr birb::vec3<f32> point_ambient = { 0.2f, 0.2f, 0.2f };
	}
}
