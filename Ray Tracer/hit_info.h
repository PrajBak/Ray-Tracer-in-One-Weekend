#pragma once
#include "s1mo_maths.h"

struct hit_info {
	public:
		float t_;
		float3 poc_;
		float3 normal_;
		bool front_face_;

	public:

		//Normals always face outwards from the surface ...
		//Can be against the ray or with the ray.
		const void correct_normal(const float3& ray_direction) {
			
			front_face_ = ray_direction * normal_ < 0.0f;
			normal_ = front_face_ ? normal_ : -normal_;
		}
};