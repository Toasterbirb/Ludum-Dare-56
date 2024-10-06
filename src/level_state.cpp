#include "Assert.hpp"
#include "BoxCollider.hpp"
#include "LevelState.hpp"
#include "Math.hpp"
#include "Stopwatch.hpp"
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

		mononoki = std::make_unique<birb::font>(font_manager.load_font("./assets/mononoki-Regular.ttf", 32));

		timer_text = std::make_unique<birb::entity>(scene.create_entity("Timer text"));

		birb::text t_timer_text("Timer: ", *mononoki, {20, 20, 0});
		timer_text->add_component(t_timer_text);

		if (!sfx_loaded)
		{
			sound_effects.at(static_cast<i32>(sfx::punch1)) = std::make_unique<birb::sound_file>("./assets/sfx/punch1.wav");
			sound_effects.at(static_cast<i32>(sfx::punch2)) = std::make_unique<birb::sound_file>("./assets/sfx/punch2.wav");

			sound_effects.at(static_cast<i32>(sfx::blob_goal_1)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_1.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_2)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_2.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_3)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_3.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_4)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_4.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_5)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_5.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_6)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_6.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_7)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_7.wav");
			sound_effects.at(static_cast<i32>(sfx::blob_goal_8)) = std::make_unique<birb::sound_file>("./assets/sfx/blob_8.wav");

			sound_effects.at(static_cast<i32>(sfx::hazard_fall)) = std::make_unique<birb::sound_file>("./assets/sfx/hazard_fall.wav");
		}
	}

	void level_state::start()
	{
		// reset blobs
		king->reset();
		for (size_t i = 0; i < blobs.size(); ++i)
			blobs[i]->reset();

		fallen_blob_count = 0;
		reached_goal_blob_count = 0;
		crushed_blob_count = 0;
		movement_boost = 0;
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

				case birb::input::keycode::j:
				case birb::input::keycode::k:
					movement_boost += movement_boost_increment + movement_boost * 0.05;
					audio_player.play_sound(*sound_effects.at(punch_sound_toggle
								? static_cast<int>(sfx::punch1)
								: static_cast<int>(sfx::punch2)));
					punch_sound_toggle = !punch_sound_toggle;
					break;

				default:
					break;
			}
		}
	}

	void level_state::update()
	{
		timer += timestep.deltatime();
		timer_text->get_component<birb::text>().set_text("Time: " + birb::stopwatch::format_time(timer));
		camera_shake();
	}

	void level_state::render()
	{

	}

	void level_state::blob_tick(std::vector<birb::entity>& walkable_area)
	{
		if (debug_mode)
			return;

		const f32 boosted_deltatime = timestep.deltatime() + timestep.deltatime() * movement_boost;
		king->move(held_direction(), boosted_deltatime);

		if (movement_boost > 0)
			movement_boost -= movement_boost_decay * timestep.deltatime();
		else
			movement_boost = 0;

		for (auto& b : blobs)
		{
			if (b->is_crushed)
				continue;

			b->follow(king->entity.get_component<birb::transform>().position, boosted_deltatime);
		}

		// check if a blob entered the goal area
		std::unordered_set<entt::entity> goal_collisions = world.collides_with(goal);
		for (size_t i = 0; i < blobs.size(); ++i)
		{
			if (goal_collisions.contains(blobs[i]->entity.entt()) && !blobs[i]->reached_goal)
			{
				std::cout << "Blob reached the goal!\n";
				blobs[i]->reached_goal = true;

				const i32 blob_index = reached_goal_blob_count < 8
					? static_cast<i32>(level_state::sfx::blob_goal_1) + reached_goal_blob_count
					: static_cast<i32>(level_state::sfx::blob_goal_8);
				audio_player.play_sound(*sound_effects.at(blob_index));

				reached_goal_blob_count++;
			}
		}

		// check if blobs are still in the walkable area
		std::unordered_set<entt::entity> walkable_area_collisions;
		for (birb::entity area : walkable_area)
		{
			auto new_collisions = world.collides_with(area);
			walkable_area_collisions.insert(new_collisions.begin(), new_collisions.end());
		}

		// check hazard collisions
		std::unordered_set<entt::entity> hazard_collisions;
		const auto hazard_view = scene.registry.view<hazard_tag, birb::collider::box>();
		for (auto& entity : hazard_view)
		{
			auto new_collisions = world.collides_with(entity);
			hazard_collisions.insert(new_collisions.begin(), new_collisions.end());
		}

		for (size_t i = 0; i < blobs.size(); ++i)
		{
			if (!walkable_area_collisions.contains(blobs[i]->entity.entt()) && !blobs[i]->is_falling)
			{
				blobs[i]->is_falling = true;
				fallen_blob_count++;
			}

			if (hazard_collisions.contains(blobs[i]->entity.entt()) && !blobs[i]->is_crushed)
			{
				blobs[i]->is_crushed = true;
				blobs[i]->entity.get_component<birb::transform>().local_scale.y = 0.05f;
				blobs[i]->entity.get_component<birb::transform>().position.y = 0.05f;
				crushed_blob_count++;
			}
		}

		const bool all_reached_goal = all_blobs_reached_goal(blobs);
		const bool all_fell = all_blobs_falling(blobs);
		const bool all_crushed = all_blobs_crushed(blobs);

		// if all blobs got crushed, restart the level
		if (all_crushed)
			start();

		// if all blobs that are alive reached the goal, end the level
		if (all_reached_goal || ((fallen_blob_count + reached_goal_blob_count + crushed_blob_count) == blobs.size() && !all_fell && !all_crushed))
			scene_over = true;

		// if all of the blobs have fallen and didn't reach the goal, reset the level
		if (all_fell)
			start();
	}

	void level_state::start_camera_shake(const f32 duration, const f32 strength)
	{
		original_camera_pos = camera.position;
		original_camera_pitch = camera.pitch;
		original_camera_yaw = camera.yaw;

		camera_shake_timer = duration;
		camera_shake_strength = strength;
	}

	void level_state::camera_shake()
	{
		if (camera_shake_timer <= 0)
			return;

		camera.position.x += rng.range_float(-camera_shake_strength, camera_shake_strength);
		camera.position.x += rng.range_float(-camera_shake_strength, camera_shake_strength);
		camera.position.z += rng.range_float(-camera_shake_strength, camera_shake_strength);

		camera.pitch += rng.range_float(-camera_shake_strength, camera_shake_strength) * 5;
		camera.yaw += rng.range_float(-camera_shake_strength, camera_shake_strength) * 5;

		camera_shake_timer -= timestep.deltatime();
		if (camera_shake_timer <= 0)
		{
			camera.position = original_camera_pos;
			camera.pitch = original_camera_pitch;
			camera.yaw = original_camera_yaw;
		}
	}
}
