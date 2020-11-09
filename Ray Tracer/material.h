#pragma once
#include "s1mo_maths.h"

class material {
	private:
		float3 albedo_;
		float3 reflectance_;
		float3 ambient_coeff_;

	public:
		material()
			:	albedo_(float3(0.0f)),
				reflectance_(float3(0.0f)),
				ambient_coeff_(float3(0.0f)) {}

		material(float3 alebdo, float3 reflectance, float3 ambient_coeff)
			:	albedo_(alebdo),
				reflectance_(reflectance),
				ambient_coeff_(ambient_coeff) {}

		const float3 albedo() const {
			return albedo_;
		}

		const float3 reflectance() const {
			return reflectance_;
		}

		const float3 ambient_coeff() const {
			return ambient_coeff_;
		}
};