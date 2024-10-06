#pragma once

namespace ld
{
	// empty type used to mark colliders as hazards
	struct hazard_tag
	{
		bool is_enabled = true;
	};
}
