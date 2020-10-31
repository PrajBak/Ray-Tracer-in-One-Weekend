#pragma once
#include <iostream>
#include <cassert>
#include <cmath>
#include <random>

//s1mo_maths library contains various maths utlilities
//as seen fit for use by s1mo.
//created by s1mo

//Note:
//Already Done: +, -, *, /, [], +=, -=, /=, *=, length
//Todo: cross

const float PI = 3.141592654f;

const float DEG_TO_PI = PI / 180.0f;

inline float random_float() {
	static std::uniform_real_distribution<double> distribution(0.0f, 1.0f);
	static std::mt19937 generator;
	return distribution(generator);
}

class float3 {
	public:
		float3()
			:	x_(0.0), y_(0.0), z_(0.0) {}

		float3(float value)
			: x_(value), y_(value), z_(value) {}

		float3(float x, float y, float z)
			:	x_(x), y_(y), z_(z) {}

		float3(const float3& obj) {
			x_ = obj.x_;
			y_ = obj.y_;
			z_ = obj.z_;
		}

		float3& operator=(const float3& obj) {
			x_ = obj.x_;
			y_ = obj.y_;
			z_ = obj.z_;

			return *this;
		}

		const float operator[] (const int index) const {

			assert((index >= 0) && (index <= 2));

			if		(index == 0)	return x_;
			else if (index == 1)	return y_;
			else					return z_;
		}

		float3& operator+(const float3& obj) const {
			float3* temp = new float3();
			temp->x_ = x_ + obj.x_;
			temp->y_ = y_ + obj.y_;
			temp->z_ = z_ + obj.z_;

			return *temp;
		}

		float3& operator-(const float3& obj) const {
			float3* temp = new float3();
			temp->x_ = x_ - obj.x_;
			temp->y_ = y_ - obj.y_;
			temp->z_ = z_ - obj.z_;

			return *temp;
		}

		float3& operator-() {
			*this = -1.0 * (*this);
			return *this;
		}

		//dot product
		const float operator*(const float3& obj) const {
			return x_ * obj.x_ + y_ * obj.y_ + z_ * obj.z_;
		}

		void operator+=(const float3& obj) {
			x_ = x_ + obj.x_;
			y_ = y_ + obj.y_;
			z_ = z_ + obj.z_;
		}

		void operator-=(const float3& obj) {
			x_ = x_ - obj.x_;
			y_ = y_ - obj.y_;
			z_ = z_ - obj.z_;
		}

		void operator*=(const float scalar) {
			x_ = x_ * scalar;
			y_ = y_ * scalar;
			z_ = z_ * scalar;
		}

		void operator/=(const float scalar) {

			assert(scalar != 0.0f);

			x_ = x_ / scalar;
			y_ = y_ / scalar;
			z_ = z_ / scalar;
		}

		friend std::ostream& operator<<(std::ostream& os, const float3& obj);
		friend float3& operator*(const float3& obj, const float scalar);
		friend float3& operator*(const float scalar, const float3& obj);
		friend float3& operator/(const float3& obj, const float scalar);

		inline const float x() const {
			return x_;
		}

		inline const float y() const {
			return y_;
		}

		inline const float z() const {
			return z_;
		}

		const float length_squared() const {
			const float temp = x_ * x_ + y_ * y_ + z_ * z_;
			return temp;
		}

		const float length() const {
			return sqrt(length_squared());
		}

		float3& normalize() {
			const float float3_length = length();

			assert(float3_length != 0.0f);

			x_ /= float3_length;
			y_ /= float3_length;
			z_ /= float3_length;

			return *this;
		}

	private:
		float x_;
		float y_;
		float z_;
};

std::ostream& operator<<(std::ostream& os, const float3& obj) {
	os << "[ " << obj.x_ << ", " << obj.y_ << ", " << obj.z_ << " ]";
	return os;
}

float3& operator*(const float3& obj, const float scalar) {
	float3* temp = new float3(obj);
	temp->x_ = obj.x_ * scalar;
	temp->y_ = obj.y_ * scalar;
	temp->z_ = obj.z_ * scalar;

	return *temp;
}

float3& operator*(const float scalar, const float3& obj) {
	float3* temp = new float3(obj);
	temp->x_ = scalar * obj.x_;
	temp->y_ = scalar * obj.y_;
	temp->z_ = scalar * obj.z_;

	return *temp;
}

float3& operator/(const float3& obj, const float scalar) {

	assert(scalar != 0.0f);

	float3* temp = new float3(obj);
	temp->x_ = obj.x_ / scalar;
	temp->y_ = obj.y_ / scalar;
	temp->z_ = obj.z_ / scalar;

	return *temp;
}