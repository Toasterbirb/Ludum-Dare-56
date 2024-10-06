#pragma once

#include "Direction.hpp"
#include "Entity.hpp"
#include "Model.hpp"
#include "Scene.hpp"

namespace ld
{
	struct blob_king
	{
		blob_king(birb::scene& scene, birb::model& blob_model);
		birb::entity entity;

		f32 movement_speed{1.0f};
		const f32 king_size;

		void move(const direction d, const f64 deltatime);
		void reset();
	};
}
