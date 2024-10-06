#include "Assert.hpp"
#include "LevelState.hpp"
#include "Transform.hpp"

namespace ld
{
	void level_state::awake()
	{
		birb::ensure(!blobs.empty(), "Resize the blob vector before calling level state awake");
		birb::model m_king("./assets/Blob_crown.obj");
		king = std::make_unique<blob_king>(scene, m_king);

		birb::model m_blob("./assets/blob.obj");

		// blob models
		for (size_t i = 0; i < blobs.size(); ++i)
			blobs[i] = std::make_unique<blob>(scene, m_blob);

	}

	void level_state::start()
	{
		// reset blobs
		king->reset();
		for (size_t i = 0; i < blobs.size(); ++i)
			blobs[i]->reset();
	}

	void level_state::input(birb::input& input)
	{
		if (input.state == birb::input::action::key_down)
		{
			switch (input.key)
			{
				case birb::input::keycode::f8:
					scene_over = true;
					break;

				case birb::input::keycode::f9:
					debug_mode = !debug_mode;
					break;

				default:
					break;
			}
		}
	}

	void level_state::update()
	{

	}

	void level_state::render()
	{

	}

	void level_state::blob_tick(std::vector<birb::entity>& walkable_area)
	{
		if (debug_mode)
			return;

		king->move(held_direction(), timestep.deltatime());

		for (auto& b : blobs)
			b->follow(king->entity.get_component<birb::transform>().position, timestep.deltatime());

		// check if a blob entered the goal area
		std::unordered_set<entt::entity> goal_collisions = world.collides_with(goal);
		for (size_t i = 0; i < blobs.size(); ++i)
		{
			if (goal_collisions.contains(blobs[i]->entity.entt()) && !blobs[i]->reached_goal)
			{
				std::cout << "Blob reached the goal!\n";
				blobs[i]->reached_goal = true;
			}
		}

		// check if blobs are still in the walkable area
		std::unordered_set<entt::entity> walkable_area_collisions;

		for (birb::entity area : walkable_area)
		{
			auto new_collisions = world.collides_with(area);
			walkable_area_collisions.insert(new_collisions.begin(), new_collisions.end());
		}

		for (size_t i = 0; i < blobs.size(); ++i)
		{
			if (!walkable_area_collisions.contains(blobs[i]->entity.entt()))
				blobs[i]->is_falling = true;
		}

		// if all blobs reached the goal, end the level
		if (all_blobs_reached_goal(blobs))
			scene_over = true;

		// if all of the blobs have fallen and didn't reach the goal, reset the level
		if (all_blobs_falling(blobs))
			start();
	}
}
