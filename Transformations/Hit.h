#ifndef _HIT_H_
#define _HIT_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "Vector.h"
#include "Ray.h"
#include "Hit.h"

class Material;

// ==============================================
// ==============================================

class Hit

{

public:

	// Constructor & Destructor
	Hit() { material = NULL; color = Vec3f(0.0f, 0.0f, 0.0f); }
	Hit(float _t, Material * m, Vec3f & n, Vec3f c = Vec3f(0.0f, 0.0f, 0.0f)) : t(_t), material(m), normal(n), color(c) {}
	
	Hit(const Hit & h) 
	{
		t = h.t; 

		material = h.material; 
		normal = h.normal; 
		intersectionPoint = h.intersectionPoint; 
		color = h.color;
	}

	Hit & operator = (const Hit & h)
	{
		t = h.t; 

		material = h.material; 
		normal = h.normal; 
		intersectionPoint = h.intersectionPoint; 
		color = h.color;
	}
	
	virtual ~Hit() {}

	// Accessors
	float getT() const { return t; }
	
	Material * getMaterial() const { return material; }
	Vec3f getNormal() const { return normal; }
	Vec3f getIntersectionPoint() const { return intersectionPoint; }
	Vec3f getColor() const { return color; }

	// Modifiers
	void set(float _t, Material * m, Vec3f n, const Ray & ray) {
		t = _t; material = m; normal = n;
		intersectionPoint = ray.pointAtParameter(t); 
	}

	void set(float _t, Material * m, Vec3f n, Vec3f c, const Ray & ray) {
		t = _t; material = m; normal = n; color = c;
		intersectionPoint = ray.pointAtParameter(t); 
	}


private: 

	// Representations
	float t;

	Material *material;
	Vec3f normal;
	Vec3f intersectionPoint;

	Vec3f color;
};


inline ostream & operator << (ostream & os, const Hit & h)
{
	os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
	return os;
}

// ===========================================
// ===========================================

#endif
