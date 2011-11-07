#ifndef _GROUP_H_
#define _GROUP_H_

#include <iostream>
using namespace std;

#include "Vector.h"
#include "Matrix.h"

#include "Object3D.h"
#include "Sphere.h"

// ====================================================
// ====================================================

class Group : public Object3D

{

	friend ostream & operator << (ostream &, const Group &);

public:

	Group(int num = 0);
	virtual ~Group();

	virtual bool intersect(const Ray & r, Hit & h, float tmin);
	void addObject(int index, Object3D * obj);

	int getObjectNumber() const { return objs_num; }

private:

	int objs_num;
	Object3D ** objs;

};

inline ostream & operator << (ostream & os, const Group & g)
{
	os << "Group Information:"	<< endl
	   << "Object Number = "	<< g.objs_num << endl;
	
	for (int i = 0; i < g.objs_num; ++i)
		os << g.objs[i] << endl;

	return os;
}

#endif