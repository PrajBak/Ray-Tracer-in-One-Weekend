#pragma once
#include "hittable_object.h"
#include <vector>
#include <memory>

class hittable_objects : public hittable_object {
public:
	hittable_objects() {}

	hittable_objects(std::shared_ptr<hittable_object> obj) {
		add_hittable_object(obj);
	}

	void add_hittable_object(std::shared_ptr<hittable_object> obj) {
		hittable_objects_.push_back(obj);
	}

	void clear_all_objects() {
		hittable_objects_.clear();
	}

	const bool isHit(
		const ray& r,
		float t0,
		float t1,
		hit_info& hi) const override {

		hit_info temp_info;
		bool anyHits = false;
		float tmin = t1;

		for (const auto& hitt_obj : hittable_objects_) {
			if (hitt_obj->isHit(r, t0, tmin, temp_info) == true) {
				anyHits = true;
				tmin = temp_info.t_;
				hi = temp_info;
			}
		}

		return anyHits;
	}

private:
	std::vector<std::shared_ptr<hittable_object>> hittable_objects_;
};