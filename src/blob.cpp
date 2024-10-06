#include "Blob.hpp"
#include "BoxCollider.hpp"
#include "Math.hpp"
#include "Random.hpp"
#include "State.hpp"
#include "Transform.hpp"

static birb::random rng(42);

namespace ld
{
	blob::blob(birb::scene& scene, birb::model& blob_model)
	:blob_size(rng.range_float(0.08, 0.15)),
	 entity(scene.create_entity("blob", birb::component::transform | birb::component::default_shader | birb::component::state))
	{
		preferred_distance = rng.range_float(0.5, 2.0);
		speed = rng.range_float(0.7, 1.0);

		entity.add_component(blob_model);
		entity.get_component<birb::transform>().local_scale = blob_size;
		entity.get_component<birb::transform>().position.y = blob_size;

		birb::collider::box collider(entity.get_component<birb::transform>());
		collider.set_size({0.15, 0.15, 0.15});
		entity.add_component(collider);

		// update the collider
		entity.get_component<birb::collider::box>().set_position(entity.get_component<birb::transform>().position);
	}

	void blob::reset()
	{
		birb::transform& t = entity.get_component<birb::transform>();
		t.position.x = 0.5 * rng.range_float(-0.5, 0.5);
		t.position.y = blob_size;
		t.position.z = 0.5 * rng.range_float(-0.5, 0.5);

		t.local_scale = blob_size;

		entity.get_component<birb::collider::box>().set_position(t.position);
		reached_goal = false;
		is_falling = false;
		is_crushed = false;

		entity.get_component<birb::state>().active = true;
	}

	void blob::follow(const birb::vec3<f32> target, const f32 deltatime)
	{
		birb::transform& t = entity.get_component<birb::transform>();

		// if the blob is falling, don't make it follow but rather fall
		if (is_falling)
		{
			constexpr f32 fall_speed = 2.0f;
			t.position.y -= deltatime * fall_speed;
			return;
		}

		// if the blob reached the goal, make it shrink until its size is zero
		if (reached_goal && t.local_scale.x > 0)
			t.local_scale -= deltatime * shrink_speed;
		else if (t.local_scale.x <= 0)
			entity.get_component<birb::state>().active = false;

		// don't move at all if we are close enough to the target
		if (birb::vec_distance(t.position, target) <= preferred_distance)
			return;


		glm::vec3 normalised_direction = glm::normalize(target.to_glm_vec() - t.position.to_glm_vec());

		glm::vec3 new_pos = t.position.to_glm_vec() + normalised_direction * speed * deltatime;
		t.position = { new_pos.x, t.position.y, new_pos.z };

		// update the collider
		entity.get_component<birb::collider::box>().set_position(entity.get_component<birb::transform>().position);
	}

	bool all_blobs_falling(const std::vector<std::unique_ptr<blob>>& blobs)
	{
		return std::all_of(blobs.begin(), blobs.end(), [](const std::unique_ptr<blob>& b) {
			return b->is_falling;
		});
	}

	bool all_blobs_reached_goal(const std::vector<std::unique_ptr<blob>>& blobs)
	{
		return std::all_of(blobs.begin(), blobs.end(), [](const std::unique_ptr<blob>& b) {
			return b->reached_goal;
		});
	}

	bool all_blobs_crushed(const std::vector<std::unique_ptr<blob>>& blobs)
	{
		return std::all_of(blobs.begin(), blobs.end(), [](const std::unique_ptr<blob>& b) {
			return b->is_crushed;
		});
	}
}
