#pragma once
#include "s1mo_maths.h"
#include "hit_info.h"

class light {
	public:
		light()
			:	intensity_(0.0f),
				ambient_intensity_(0.0f),
				position_(float3(0.0f)) {}

		light(float intensity, float ambient_intensity, float3 position)
			:	intensity_(intensity), 
				ambient_intensity_(ambient_intensity),
				position_(position) {}

		const float3 compute_color(const hit_info& hi) const {
			float3 point_of_contact = hi.poc_;
			float3 point_to_light = (position_ - point_of_contact).normalize();
			float3 point_to_viewer = -(point_of_contact.normalize());
			float3 color = lambertian_color(hi, point_to_light)
				+ blinn_phong_color(hi, point_to_light, point_to_viewer)
				+ ambient_color(hi);
			
			return color;
		}

		const float3 position() const {
			return position_;
		}

	private:
		float3 lambertian_color(
			const hit_info& hi,
			float3 point_to_light) const {

			return hi.albedo_ * intensity_ * max(0.0f, hi.normal_ * point_to_light);
		}

		float3 blinn_phong_color(
			const hit_info& hi,
			const float3 point_to_light,
			const float3 point_to_viewer) const {

			const float3 half_angle_vector = (point_to_viewer + point_to_light).normalize();
			const float phong_exp = std::powf(max(0.0f, hi.normal_ * half_angle_vector), 10.0f);

			return hi.reflectance_ * intensity_ * phong_exp;
		}

		float3 ambient_color(const hit_info& hi) const {
			return hi.ambient_coeff_ * ambient_intensity_;
		}

	private:
		float intensity_;
		float ambient_intensity_;
		float3 position_;
};