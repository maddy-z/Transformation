#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Object3D.h"
#include "Vector.h"
#include "Matrix.h"
#include "Ray.h"
#include "Hit.h"

class Transform : public Object3D

{

public:

	Transform(Matrix & m, Object3D * obj);
	virtual ~Transform() {}
	
	virtual bool intersect(const Ray & r, Hit & h, float tmin);

private:

	Object3D * object;
	Matrix transformMat;

};

#endif