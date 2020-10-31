#pragma once
#include "s1mo_maths.h"

class ray {
	public:
		ray()
			:	ray_origin_(0.0),
				ray_direction_(0.0) {}

		ray(const float3 ray_origin, const float3 ray_direction)
			:	ray_origin_(ray_origin),
				ray_direction_(ray_direction) {}

		float3 ray_origin() const {
			return ray_origin_;
		}

		float3 ray_direction() const {
			return ray_direction_;
		}

		const float3 ray_at_point(float t) const {
			return ray_origin_ + t * ray_direction_;
		}

	private:
		const float3 ray_origin_;
		const float3 ray_direction_;

};