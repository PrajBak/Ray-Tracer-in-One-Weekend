#pragma once
#include "s1mo_maths.h"
#include "hittable_object.h"

class sphere : public hittable_object {
	public:
		sphere()
			:	centre_(0.0f),
				radius_(0.0f),
				albedo_(float3(0.0f)),
				reflectance_(float3(0.0f)),
				ambient_coeff_(float3(0.0f)) {}

		sphere(float3 centre, float radius, float3 albedo, float3 reflectance, float3 ambient_coeff)
			:	centre_(centre),
				radius_(radius),
				albedo_(albedo),
				reflectance_(reflectance),
				ambient_coeff_(ambient_coeff) {}

		const bool isHit(
			const ray& r, 
			float t0, 
			float t1, 
			hit_info& hi) const override {
		
			const float3 roc = r.ray_origin() - centre_;
			const float a = r.ray_direction().length_squared();
			const float b = r.ray_direction() * (roc);
			const float c = roc * roc - radius_ * radius_;

			const float discriminant = b * b - a * c;

			if (discriminant >= 0.0f) {
				float t = (-b - sqrt(discriminant)) / a;
				if (t > t0 && t < t1) {
					hi.t_ = t;
					hi.poc_ = r.ray_at_point(t);
					hi.normal_ = (hi.poc_ - centre_) / radius_;
					hi.albedo_ = albedo_;
					hi.reflectance_ = reflectance_;
					hi.ambient_coeff_ = ambient_coeff_;
					hi.correct_normal(r.ray_direction());
					return true;
				}

				t = (-b + sqrt(discriminant)) / a;
				if (t > t0 && t < t1) {
					hi.t_ = t;
					hi.poc_ = r.ray_at_point(t);
					hi.normal_ = (hi.poc_ - centre_) / radius_;
					hi.albedo_ = albedo_;
					hi.reflectance_ = reflectance_;
					hi.ambient_coeff_ = ambient_coeff_;
					hi.correct_normal(r.ray_direction());
					return true;
				}
			}

			hi.t_ = -100000.0f;
			hi.poc_ = float3(-100000.0f);
			hi.normal_ = float3(0.0f);
			hi.front_face_ = false;
			hi.albedo_ = float3(0.0f);
			hi.reflectance_ = float3(0.0f);
			hi.ambient_coeff_ = float3(0.0f);

			return false;
		}

		const float3 centre() const {
			return centre_;
		}

		const float radius() const {
			return radius_;
		}

	private:
		const float radius_;
		const float3 centre_;
		const float3 albedo_;
		const float3 reflectance_;
		const float3 ambient_coeff_;
};