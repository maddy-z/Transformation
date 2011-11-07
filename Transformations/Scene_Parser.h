#ifndef _SCENE_PARSER_H_
#define _SCENE_PARSER_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

// ===============================
// Header Files for Camera Classes
// ===============================
#include "Camera.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

// ================================
// Header Files for Utility Classes
// ================================
#include "Vector.h"
#include "Matrix.h"
#include "Image.h"

// ==================================
// Header Files for Object 3D Classes
// ==================================
#include "Object3D.h"
#include "Group.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Transform.h"

#include "Ray.h"
#include "Light.h"
#include "Hit.h"

#define  MAX_PARSER_TOKEN_LENGTH  100


// ===================================================
// ===================================================

class SceneParser 

{

	friend ostream & operator << (ostream & os, const SceneParser & sparser);

public:

	// CONSTRUCTORS, DESTRUCTOR & INITIALIZE
	SceneParser();
	SceneParser(const char* filename);
	
	virtual ~SceneParser();

	// ACCESSORS
	Group* getGroup() const { return group; }
	Camera* getCamera() const { return camera; }
	Light **getLights() const { return lights; }

	Vec3f getBackgroundColor() const { return background_color; }
	Vec3f getAmbientLightColor() const { return ambient_light; }
	
	int getLightNum() const { return num_lights; }

protected:

	// HELPER FUNCTIONS
	void initialize();
	int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);

	void parseFile();
	void parseBackground();
	void parseMaterial();

	Object3D* parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
	Sphere* parseSphere();
	Group* parseGroup();
	Plane* SceneParser::parsePlane();
	Triangle* SceneParser::parseTriangle();
	Group* SceneParser::parseTriangleMesh();
	Transform* SceneParser::parseTransform();
	
	void parseLights();
	void parseOrthographicCamera();
	void parsePerspectiveCamera();

	Vec3f readVec3f(); 
	float readFloat();
	int readInt();

private:

	// REPRESENTATION
	Group * group;
	Camera * camera;

	Vec3f ambient_light;
	Vec3f background_color;
	Vec3f current_object_color;
	
	FILE * file;

	Light ** lights;
	int num_lights;

};

// ========================================================
// ========================================================

#endif
