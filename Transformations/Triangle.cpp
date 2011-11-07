#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "Object3D.h"
#include "Triangle.h"

#include "Vector.h"
#include "Matrix.h"

bool Triangle::intersect(const Ray & r, Hit & h, float tmin)

{
	
	Vec3f ab = a - b;
	Vec3f ac = a - c;
	Vec3f ar = a - r.getOrigin();
	Vec3f dir = r.getDirection();

	float coff[3][3] = {
							{ ab[0], ac[0], dir[0] },
							{ ab[1], ac[1], dir[1] },
							{ ab[2], ac[2], dir[2] }
					   };

	float mat_1[3][3] = {
							{ ar[0], ac[0], dir[0] },
							{ ar[1], ac[1], dir[1] },
							{ ar[2], ac[2], dir[2] }
					    };

	float mat_2[3][3] = {
							{ ab[0], ar[0], dir[0] },
							{ ab[1], ar[1], dir[1] },
							{ ab[2], ar[2], dir[2] }
					    };

	float mat_3[3][3] = {
							{ ab[0], ac[0], ar[0] },
							{ ab[1], ac[1], ar[1] },
							{ ab[2], ac[2], ar[2] }
					    };

	float coff_det = calcDeterminant3_3(coff);
	if (coff_det < 1.0e-6 && coff_det > -1.0e-6)
		return false;

	float beta = calcDeterminant3_3(mat_1) / coff_det;
	float alpha = calcDeterminant3_3(mat_2) / coff_det;
	float t = calcDeterminant3_3(mat_3) / coff_det;

	if (beta > 0.0f && alpha > 0.0f && beta + alpha < 1.0f)				// Intesection if ( p + r < 1 && r > 0 && p > 0 )
	{
		assert (tmin >= 0.0f);

		if (t > 1e-6 && t > tmin && t < h.getT()) 
		{
			normal.Normalize();
			h.set(t, NULL, normal, color, r);

			return true;
		}
		else
			return false;
	}
	else { 
		return false;
	}

}