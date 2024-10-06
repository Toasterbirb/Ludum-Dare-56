#pragma once

#include "Entity.hpp"
#include "Model.hpp"
#include "Scene.hpp"
#include "Vector.hpp"

#include <vector>

namespace ld
{
	struct blob
	{
		blob(birb::scene& scene, birb::model& blob_model);

		void reset();
		void follow(const birb::vec3<f32> target, const f32 deltatime);

		birb::entity entity;
		f32 preferred_distance;
		f32 speed;
		const f32 blob_size;
		static constexpr f32 shrink_speed = 0.1f;

		bool reached_goal{false};
		bool is_falling{false};
	};

	bool all_blobs_falling(const std::vector<std::unique_ptr<blob>>& blobs);
	bool all_blobs_reached_goal(const std::vector<std::unique_ptr<blob>>& blobs);
}
