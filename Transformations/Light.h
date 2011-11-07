#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <iostream>
using namespace std;

#include "Vector.h"

// ====================================================================
// ====================================================================

class Light

{

public:

	// CONSTRUCTOR & DESTRUCTOR
	Light() {}
	virtual ~Light() {}

	// VIRTUAL METHOD
	virtual void getIllumination (const Vec3f &pos, Vec3f &dir, Vec3f &col) const = 0;

};

// ====================================================================
// ====================================================================

class DirectionalLight : public Light 

{
	friend ostream & operator << (ostream & os, const DirectionalLight & dirLight);

public:

	// CONSTRUCTOR & DESTRUCTOR
	DirectionalLight() { 
		direction = Vec3f(0, 0, 0);
		color = Vec3f(1, 1, 1); 
	}
	
	DirectionalLight(const Vec3f & d, const Vec3f & c) {
		direction = d; direction.Normalize();
		color = c;
	}
	
	virtual ~DirectionalLight() {}

	// VIRTUAL METHOD
	void getIllumination (const Vec3f &p, Vec3f &dir, Vec3f &col) const 
	{
		// The direction to the light is the opposite of the direction of the directional light source
		dir = direction * (-1.0f);
		col = color; 
	}

private:

	// REPRESENTATION
	Vec3f direction;
	Vec3f color;

};

inline ostream & operator << (ostream & os, const DirectionalLight & dirLight)
{
	os << "DirectionLight Information:" << endl
	   << "\tDirection:\t" << dirLight.direction << endl
	   << "\tLight Color:\t" << dirLight.color << endl;

	return os;
}


// ====================================================================
// ====================================================================

#endif
