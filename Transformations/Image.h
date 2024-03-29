#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cassert>

#include "Vector.h"

// ====================================================================
// ====================================================================
// Simple Image Class

class Image
{

public:

	// ========================
	// CONSTRUCTOR & DESTRUCTOR
	Image(int w, int h) {
		width = w;
		height = h;

		data = new Vec3f[width * height];
	}

	~Image() {
		delete [] data;
	}

	// =========
	// ACCESSORS
	int Width() const { return width; }
	int Height() const { return height; }
	
	const Vec3f& GetPixel(int x, int y) const
	{
		assert(x >= 0 && x < width);
		assert(y >= 0 && y < height);
    
		return data[y * width + x];
	}
  
	// =========
	// MODIFIERS
	void SetAllPixels(const Vec3f &color) {
		int total =  width * height;
	
		for (int i = 0; i < total; i++) {
			data[i] = color; 
		} 
	}
  
	void SetPixel(int x, int y, const Vec3f &color) {
		assert(x >= 0 && x < width);
		assert(y >= 0 && y < height);
		
		data[y * width + x] = color; 
	}

	// ============
	// LOAD && SAVE
	static Image* LoadPPM(const char *filename);
	static Image* LoadTGA(const char *filename);
	
	void SavePPM(const char *filename) const;
	void SaveTGA(const char *filename) const;

private:

	// ================
	//  REPRESENTATION
	// ================
	
	int width;
	int height;

	Vec3f *data;

};

// ====================================================================
// ====================================================================

#endif

