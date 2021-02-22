#include "types.h"

Vec::Vec(float xx, float yy, float zz) :x(xx), y(yy), z(zz) {}

float Vec::operator * (Vec& v) {
	return (x*v.x + y*v.y + z*v.z);
}
Vec Vec::operator - (Vec& v) {
	return Vec(x - v.x, y - v.y, z - v.z);
}
Vec Vec::operator + (Vec& v) {
	return Vec(x + v.x, y + v.y, z + v.z);
}
float Vec::length() {
	return sqrt(x*x + y*y + z*z);
}
Vec Vec::normalize() {
	float l = length();
	if (l == 0)
		return Vec(0, 0, 0);
	return Vec(x / l, y / l, z / l);
}

Vec operator * (Vec& v, float k) {
	return Vec(v.x*k, v.y*k, v.z*k);
}

Vec operator * (float k, Vec&v) {
	return v * k;
}

Vec operator / (Vec& v, float k) {
	if (k == 0)
		return v;
	return v*(1 / k);
}

ostream& operator << (ostream& ost, Vec&v) {
	ost << "<" << v.x << "," << v.y << "," << v.z << ">";
	return ost;
}

Vec Vec::dc(Vec& v) {
	return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}