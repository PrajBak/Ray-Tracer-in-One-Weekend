#pragma once
#include "ray.h"
class camera {
	public:
		camera()
			:	asp_(0.0f),
				focal_length_(0.0f),
				origin_(float3(0.0f)),
				horizontal_(float3(0.0f)),
				vertical_(float3(0.0f)) {}

		camera(float3 origin, float width, float height)
			:	origin_(origin) {
		
			asp_ = width / height;
			const float view_height = 2.0f;
			const float view_width = view_height * asp_;
			focal_length_ = 1.0f;
			horizontal_ = float3(view_width, 0.0f, 0.0f);
			vertical_ = float3(0.0f, view_height, 0.0f);
			lower_left_ = origin - horizontal_/2.0f
				- vertical_ / 2.0f - float3(0.0f, 0.0f, focal_length_);
		}

		ray get_ray_to(const float u, const float v) const {
			return ray(origin_, lower_left_ + u * horizontal_ + v * vertical_ - origin_);
		}

	private:
		float asp_;
		float focal_length_;
		float3 origin_;
		float3 horizontal_;
		float3 vertical_;
		float3 lower_left_;
};