#pragma once
#include "ray.h"
#include "hit_info.h"

class hittable_object {
	public:
		virtual const bool isHit(
			const ray& r,
			float t0,
			float t1,
			hit_info& hi) const = 0;
};