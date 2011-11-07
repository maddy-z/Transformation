#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "Object3D.h"
#include "Vector.h"
#include "Ray.h"
#include "Hit.h"

class Triangle : public Object3D

{

public:

	Triangle(Vec3f & x, Vec3f & y, Vec3f & z, Vec3f & color): Object3D(color), a(x), b(y), c(z) 
	{ normal = calcNormal(a, b, c); normal.Normalize(); }

	virtual ~Triangle() {};
	virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:

	Vec3f a, b, c;
	Vec3f normal;

};

#endif