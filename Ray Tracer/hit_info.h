#pragma once
#include "s1mo_maths.h"

struct hit_info {
	public:
		bool front_face_;
		float t_;
		float3 poc_;
		float3 normal_;
		float3 albedo_;				//diffuse coeffecient
		float3 reflectance_;		//reflectance coeffecient
		float3 ambient_coeff_;

	public:

		//Normals always face outwards from the surface ...
		//Can be against the ray or with the ray.
		const void correct_normal(const float3& ray_direction) {
			
			front_face_ = ray_direction * normal_ < 0.0f;
			normal_ = front_face_ ? normal_ : -normal_;
		}
};