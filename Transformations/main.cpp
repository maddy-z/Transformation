#include <cmath>
#include <cfloat>

#include "Common.h"


// =====================================================
//  Static Global Variables used to parse the arguments 
// =====================================================

char *input_file  = NULL;
char *output_file = NULL;
char *normal_file = NULL;

int imageWidth  = 100;
int imageHeight = 100;


// ==============
//  Test Program
// ==============

int main(int argc, char **argv)

{

	// Sample Command Lines:
	// raycast -input scene.txt -size 1000 1000 -output image.tga
	// raycast -input scene.txt -size 1000 1000 -normal normal.tga

	for (int i = 1; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-input")) 
		{
			i++; assert (i < argc); 
			input_file = argv[i];
		}
		else if (!strcmp(argv[i], "-size")) 
		{
			i++; assert (i < argc); 
			imageWidth = atoi(argv[i]);
			
			i++; assert (i < argc);
			imageHeight = atoi(argv[i]);
		}
		else if (!strcmp(argv[i], "-output")) 
		{
			i++; assert (i < argc);
			output_file = argv[i];
		}
		else if (!strcmp(argv[i], "-normal")) 
		{
			i++; assert (i < argc);
			normal_file = argv[i];
		}
		else 
		{
			printf ("Whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	printf("Command Arguments Information:\n");
	printf("\t-input %s\n", input_file);
	printf("\t-size %d %d\n", imageHeight, imageWidth);
	
	if ( output_file ) {
		printf("\t-output %s\n", output_file);
	}
	
	if ( normal_file ) {
		printf("\t-normal %s\n", normal_file);
	}

	cout << endl;


	// ======================
	//  Scene Initialization
	// ======================

	SceneParser sparser(input_file);
	cout << sparser;

	Image img( imageWidth, imageHeight );
	Image normal_img( imageWidth, imageHeight );
	img.SetAllPixels(sparser.getBackgroundColor());
	normal_img.SetAllPixels(Vec3f(0.0f, 0.0f, 0.0f));
	
	Group *scene = sparser.getGroup();
	Camera *cam = sparser.getCamera();
	Light **sceneLights = sparser.getLights(); int lightNum = sparser.getLightNum();
	Vec3f amb_color = sparser.getAmbientLightColor();

	Vec2f cameraPoint;
	Vec3f normal(0.0f, 1.0f, 0.0f);

	std::cout << "Start to Generate Ray" << endl << endl;

	for (int i = 0; i < imageHeight; ++i)
	{
		for (int j = 0; j < imageWidth; ++j)
		{
			cameraPoint.Set( (float)(i) / (float)(imageHeight), (float)(j) / (float)(imageWidth) );
			Ray r = cam -> generateRay(cameraPoint);

			Hit hitPoint ( FLT_MAX, NULL, normal, Vec3f(0.0f, 0.0f, 0.0f) );
			if ( scene -> intersect(r, hitPoint, 0) == true )
			{
				Vec3f pos, l_dir, l_col, hitColor = hitPoint.getColor(), hitNormal = hitPoint.getNormal(); hitNormal.Normalize();
				Vec3f pixel(hitColor[0] * amb_color[0], hitColor[1] * amb_color[1], hitColor[2] * amb_color[2]);

				// cout << "Hit Point Color:\t" << hitColor << endl;
				// cout << "Hit Point Normal:\t" << hitNormal << endl;

				for (int k = 0; k < lightNum; ++k) 
				{
					sceneLights[k] -> getIllumination(pos, l_dir, l_col);
					l_dir.Normalize();
					
					float tmp = l_dir.Dot3( hitPoint.getNormal() );
					tmp = ( tmp > 0.0f ) ? ( tmp ) : ( 0.0f );

					pixel += tmp * Vec3f( hitColor[0] * l_col[0], hitColor[1] * l_col[1], hitColor[2] * l_col[2] );

				}

				if ( hitNormal[0] < 0.0f ) hitNormal.Set( -hitNormal[0],  hitNormal[1],  hitNormal[2] );
				if ( hitNormal[1] < 0.0f ) hitNormal.Set(  hitNormal[0], -hitNormal[1],  hitNormal[2] );
				if ( hitNormal[2] < 0.0f ) hitNormal.Set(  hitNormal[0],  hitNormal[1], -hitNormal[2] );
				
				if ( hitNormal[0] > 1.0f ) hitNormal.Set(1.0f, hitNormal[1], hitNormal[2]);
				if ( hitNormal[1] > 1.0f ) hitNormal.Set(hitNormal[0], 1.0f, hitNormal[2]);
				if ( hitNormal[2] > 1.0f ) hitNormal.Set(hitNormal[0], hitNormal[1], 1.0f);

				if ( pixel[0] > 1.0f ) pixel.Set( 1.0f, pixel[1], pixel[2] );
				if ( pixel[1] > 1.0f ) pixel.Set( pixel[0], 1.0f, pixel[2] );
				if ( pixel[2] > 1.0f ) pixel.Set( pixel[0], pixel[1], 1.0f );
				
				img.SetPixel(j, i, pixel);
				normal_img.SetPixel(j, i, hitNormal);
			}
		}
	}

	if (output_file != NULL) {
		img.SaveTGA(output_file);
	} 

	if (normal_file != NULL) { 
		normal_img.SaveTGA(normal_file);
	}

	// system("pause");
	return 0;

}