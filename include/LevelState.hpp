#pragma once

#include "Blob.hpp"
#include "BlobKing.hpp"
#include "Font.hpp"
#include "FontManager.hpp"
#include "GameState.hpp"
#include "Hazard.hpp"
#include "Text.hpp"

#include <vector>

namespace ld
{
	class level_state : public game_state
	{
	public:
		level_state(birb::renderer& renderer, birb::window& window, birb::camera& camera, birb::timestep& timestep, birb::audio_player& audio_device)
		:game_state(renderer, window, camera, timestep, audio_device)
		{}

		virtual void awake() override;
		virtual void start() override;
		virtual void input(birb::input& input) override;
		virtual void update() override;
		virtual void render() override;
		game_scene end() override = 0;

		void blob_tick();

		// disables blob ticking
		bool debug_mode{false};


	protected:
		static constexpr size_t map_size = 10;
		std::array<std::array<bool, map_size>, map_size> floor_layout;
		std::array<std::array<bool, map_size>, map_size> goal_locations;
		std::array<std::array<bool, map_size>, map_size> hazard_layout;

		struct tile
		{
			std::unique_ptr<birb::entity> floor_entity;
			std::unique_ptr<birb::entity> goal_entity;
			std::unique_ptr<birb::entity> hazard_entity;
		};

		std::array<std::array<tile, 16>, 16> floor_tiles;
		std::unique_ptr<birb::model> floor_model;
		std::unique_ptr<birb::model> goal_model;
		std::unique_ptr<birb::model> hazard_model;

		std::vector<tile*> tiles;

		void load_level();

		f32 hazard_timer{0};
		f32 hazard_delay{1.0f};

		bool hazard_down{true};
		const f32 hazard_height{2.0f};
		void update_hazards();

		birb::entity floor = DEFAULT_3D_ENTITY;

		birb::entity goal = scene.create_entity("Goal");

		std::unique_ptr<blob_king> king;
		std::vector<std::unique_ptr<blob>> blobs;

		static inline birb::font_manager font_manager;
		static inline std::unique_ptr<birb::font> mononoki;
		static inline std::unique_ptr<birb::font> big_mononoki;
		std::unique_ptr<birb::entity> timer_text;
		std::unique_ptr<birb::entity> speed_text;

		static inline f32 timer{0};

		static inline i32 rescued_blobs{0};
		i32 fallen_blob_count{0};
		i32 reached_goal_blob_count{0};
		i32 crushed_blob_count{0};

		// increase speed by tapping j and k
		static inline f32 movement_boost{0};
		static constexpr f32 movement_boost_increment = 0.2f;
		static constexpr f32 movement_boost_decay = 0.5f;
		bool punch_sound_toggle{false};

		enum class sfx
		{
			punch1 = 0,
			punch2 = 1,
			blob_goal_1 = 2,
			blob_goal_2 = 3,
			blob_goal_3 = 4,
			blob_goal_4 = 5,
			blob_goal_5 = 6,
			blob_goal_6 = 7,
			blob_goal_7 = 8,
			blob_goal_8 = 9,
			hazard_fall = 10
		};

		static inline bool sfx_loaded{false};
		static inline std::array<std::unique_ptr<birb::sound_file>, 11> sound_effects;


		// camera shaking
		void start_camera_shake(const f32 duration, const f32 strength);
		void camera_shake();

	private:
		static inline glm::vec3 original_camera_pos;
		static inline f32 original_camera_pitch;
		static inline f32 original_camera_yaw;
		f32 camera_shake_timer{0.0f};
		f32 camera_shake_strength{0.3f};
	};
}
