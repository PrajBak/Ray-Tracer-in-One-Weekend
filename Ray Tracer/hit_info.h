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
};