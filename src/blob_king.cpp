#include "BlobKing.hpp"

#include "Transform.hpp"

namespace ld
{
	blob_king::blob_king(birb::scene& scene, birb::model& blob_model)
	:entity(scene.create_entity("King", birb::component::transform | birb::component::default_shader)),
	 king_size(0.2f)
	{
		entity.get_component<birb::transform>().local_scale = king_size;
		entity.get_component<birb::transform>().position.y = king_size;
		entity.add_component(blob_model);
	}

	void blob_king::move(const direction d, const f64 deltatime)
	{
		birb::vec3<f32>& position = entity.get_component<birb::transform>().position;
		f32& y_rotation = entity.get_component<birb::transform>().rotation.y;

		switch (d)
		{
			case direction::koillinen:
				position.x -= deltatime * movement_speed;
				position.z -= deltatime * movement_speed;
				y_rotation = 225;
				break;

			case direction::kaakko:
				position.x += deltatime * movement_speed;
				position.z -= deltatime * movement_speed;
				y_rotation = 135;
				break;

			case direction::lounas:
				position.x += deltatime * movement_speed;
				position.z += deltatime * movement_speed;
				y_rotation = 45;
				break;

			case direction::luode:
				position.x -= deltatime * movement_speed;
				position.z += deltatime * movement_speed;
				y_rotation = -45;
				break;

			case direction::left:
				position.z += deltatime * movement_speed;
				y_rotation = 0;
				break;

			case direction::right:
				position.z -= deltatime * movement_speed;
				y_rotation = 180;
				break;

			case direction::up:
				position.x -= deltatime * movement_speed;
				y_rotation = 270;
				break;

			case direction::down:
				position.x += deltatime * movement_speed;
				y_rotation = 90;
				break;

			case direction::none: break;
		}
	}

	void blob_king::reset()
	{
		birb::transform& t = entity.get_component<birb::transform>();
		t.position.y = king_size;

		t.position.x = 3;
		t.position.z = 3;
	}
}
