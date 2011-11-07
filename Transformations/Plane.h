#ifndef _PLANE_H_
#define _PLANE_H_

#include "Object3D.h"
#include "Vector.h"
#include "Ray.h"
#include "Hit.h"

#include <cassert>

/****************************
 *
 * Class Of Plane:
 * In the form of P * N = d
 *
 ****************************/

class Plane : public Object3D

{

public:

	Plane(Vec3f &n, float d, Vec3f &color) : Object3D(color), normal(n), offset(d) { normal.Normalize(); }
	Plane(Vec3f &a, Vec3f &b, Vec3f &c, float d, Vec3f &color) : Object3D(color), offset(d) { normal = calcNormal(a, b, c); normal.Normalize(); }

	virtual ~Plane() {}

	virtual bool intersect(const Ray &r, Hit &h, float tmin);

protected:

	Vec3f normal;
	float offset;

};

#endif