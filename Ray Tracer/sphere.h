#pragma once
#include "s1mo_maths.h"
#include "hittable_object.h"

class sphere : public hittable_object {
	public:
		sphere()
			:	centre_(0.0f), radius_(0.0f) {}

		sphere(float3 centre, float radius)
			:	centre_(centre), radius_(radius) {}

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
					hi.correct_normal(r.ray_direction());
					return true;
				}

				t = (-b + sqrt(discriminant)) / a;
				if (t > t0 && t < t1) {
					hi.t_ = t;
					hi.poc_ = r.ray_at_point(t);
					hi.normal_ = (hi.poc_ - centre_) / radius_;

					return true;
				}
			}

			hi.t_ = -100000.0f;
			hi.poc_ = float3(-100000.0f);
			hi.normal_ = float3(0.0f);
			hi.front_face_ = false;

			return false;
		}

		const float3 centre() const {
			return centre_;
		}

		const float radius() const {
			return radius_;
		}

	private:
		const float3 centre_;
		const float radius_;
};