/////////////////////////////////////////////////////////////////////         
// Cylinder Roll Game
//
// The main objective of this game is to roll/move the cylinder along tha textured path
// and avoid collision with the other object.
//
// Interaction:
// Press Space to move the Cylinder and 
// Press x, X, y, Y, z, Z to turn the viewing angle.
//
// Surya Rao Karri.
///////////////////////////////////////////////////////////////////// 
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h> 

#include "getBMP.h"

#define PI 3.14159265358979324

using namespace std;
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate canoe.


													   // Globals.
static float zmove = 0, ztrack6move = 0, track6direction = 0, xmovesobj = -3.0, xmovesobjl = 3.0;
static float cylinderrotation = 0;
static float lookat0 = 0;
static float lookat1 = -6;
static float ymovement = 0;
static int obj1move = 0;
static float resultobj1;
static float resultobj2;
static float movetrack2 = 0;
static float movedirectiontrack2 = 0;
static float framescount = 100;
static float sharpeobjupanddown = 0;
static float sharpeobjupanddown1 = 0;
static float sharpeobjdirection = 0; // 0 for down and 1 for up.
static int p = 30; // Number of grid columns.
static int q = 10; // Number of grid rows
static float *vertices = NULL; // Vertex array of the mapped sample on the cylinder.
static float *normals = NULL; // Normal array of the mapped sample on the cylinder.
static float *textureCoordinates = NULL; // Texture co-ordinates array of the mapped sample on the cylinder.
static unsigned int texture[2]; // Array of texture indices.

static float ylookat0 = 0;
static float ytop = -1.5;
static float ybottom = -1.8;
/*static float controlPointstop[3][4][3] =
{
{ { 3.0, ytop, 0.0 },{ 1, ytop, 0.0 },{ -1, ytop, 0.0 },{ -3.0, ytop, 0.0 } },
{ { 3.0, ytop, 10.0 },{ 1, ytop, 10.0 },{ -1, ytop, 10.0 },{ -3.0, ytop, 10.0 } },
{ { 3.0, ytop, 50.0 },{ 1, ytop, 50.0 },{ -1, ytop, 50.0 },{ -3.0, ytop, 50.0 } },

};

static float controlPointsbottom[3][4][3] =
{
{ { 3.0, ybottom, 0.0 },{ 1, ybottom, 0.0 },{ -1, ybottom, 0.0 },{ -3.0, ybottom, 0.0 } },
{ { 3.0, ybottom, 10.0 },{ 1, ybottom, 10.0 },{ -1, ybottom, 10.0 },{ -3.0, ybottom, 10.0 } },
{ { 3.0, ybottom, 50.0 },{ 1, ybottom, 50.0 },{ -1, ybottom, 50.0 },{ -3.0, ybottom, 50.0 } },

};

static float controlPointsleft[3][4][3] =
{
{ { 3.0, ybottom, 0.0 },{ 3.0, ytop, 0.0 } },
{ { 3.0, ybottom, 10.0 },{ 3.0, ytop, 10.0 } },
{ { 3.0, ybottom, 50.0 },{ 3.0, ytop, 50.0 } },

};

static float controlPointsright[3][2][3] =
{
{ { -3.0, ybottom, 0.0 },{ -3.0, ytop, 0.0 } },
{ { -3.0, ybottom, 10.0 },{ -3.0, ytop, 10.0 } },
{ { -3.0, ybottom, 50.0 },{ -3.0, ytop, 50.0 } },

};

*/

// Load external textures.
void loadTextures()
{
	// Local storage for bmp image data.
	imageFile *image[5];

	// Load the textures.
	image[0] = getBMP("clue.bmp");
	image[1] = getBMP("track.bmp");
	image[2] = getBMP("yellowbrickroad.bmp");
	image[3] = getBMP("sky.bmp");
	image[4] = getBMP("sharpeplane.bmp");

	// Bind can label image to texture[0]. 
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Bind can top image to texture[1]
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[1]->width, image[1]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[1]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Bind can top image to texture[2]
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[2]->width, image[2]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[2]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Bind can top image to texture[3]
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[3]->width, image[3]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[3]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Bind can top image to texture[4]
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[4]->width, image[4]->height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image[4]->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

// Fuctions to map the grid vertex (u_i,v_j) to the mesh vertex (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)) on the cylinder.
float f(int i, int j)
{
	return (cos((-1 + 2 * (float)i / p) * PI));
}

float g(int i, int j)
{
	return (sin((-1 + 2 * (float)i / p) * PI));
}

float h(int i, int j)
{
	return (-1 + 2 * (float)j / q);
}

// Fuctions to map the grid vertex (u_i,v_j) to the normal (fn(u_i,v_j), gn(u_i,v_j), hn(u_i,v_j)) to the cylinder 
// at the mesh vertex (f(u_i,v_j), g(u_i,v_j), h(u_i,v_j)).
float fn(int i, int j)
{
	return (cos((-1 + 2 * (float)i / p) * PI));
}

float gn(int i, int j)
{
	return (sin((-1 + 2 * (float)i / p) * PI));
}

float hn(int i, int j)
{
	return (0);
}

// Routine to fill the vertex array with co-ordinates of the mapped sample points.
void fillVertexArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			vertices[k++] = f(i, j);
			vertices[k++] = g(i, j);
			vertices[k++] = h(i, j);
		}
}

// Routine to fill the normal array with normal vectors at the mapped sample points.
void fillNormalArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			normals[k++] = fn(i, j);
			normals[k++] = gn(i, j);
			normals[k++] = hn(i, j);
		}
}

// Routine to fill the texture co-ordinates array with the texture co-ordinate values at the mapped sample points.
void fillTextureCoordArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			textureCoordinates[k++] = (float)i / p;
			textureCoordinates[k++] = (float)j / q;
		}
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Turn on OpenGL lighting.
	glEnable(GL_LIGHTING);

	// Light property vectors.
	float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 0.0, 1.5, 3.0, 0.0 };
	float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };

	// Light properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0); // Enable particular light source.
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint.
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR); // Enable separate specular light calculation.

																			 // Material property vectors.
	float matAmbAndDif[] = { 1.0, 1.0, 1.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 50.0 };

	// Material properties.
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

	// Enable vertex, normals and texture coordinate arrays.
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Allocate space for vertex, normals and texture coordinates arrays.
	vertices = new float[3 * (p + 1)*(q + 1)];
	normals = new float[3 * (p + 1)*(q + 1)];
	textureCoordinates = new float[2 * (p + 1)*(q + 1)];

	// Set the array pointers.
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);

	// Fill the vertex, normals and texture co-ordinates arrays.
	fillVertexArray();
	fillNormalArray();
	fillTextureCoordArray();

	// Create texture ids. 
	glGenTextures(4, texture);

	// Load external textures.
	loadTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

// Drawing routine.
void drawScene(void)
{
	int  i, j;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 3.0 + ymovement, lookat1, 0.0, ylookat0, lookat0 + ymovement, 0.0, 1.0, 0.0);
	//gluLookAt(0.0, 3.0 + 5, 145, 0.0, 8.0, 155, 0.0, 1.0, 0.0);

	// Commands to turn the cylinder.
	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);


	//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//Move only the Cylinder
	glPushMatrix();

	glTranslatef(0, ymovement, zmove);
	//Bottom Cylinder
	glPushMatrix();
	glTranslatef(0, -0.5, 2);
	glRotatef(-cylinderrotation, -1, 0, 0.0);
	glTranslatef(0, 0, 0);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glRotatef(90, 0, 1, 0.0);
	// Map the label texture onto the cylinder.
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	for (j = 0; j < q; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i <= p; i++)
		{
			glArrayElement((j + 1)*(p + 1) + i);
			glArrayElement(j*(p + 1) + i);
		}
		glEnd();
	}

	glPopMatrix();
	glPopMatrix();

	//sky start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(50, ybottom - 2, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-50, ybottom - 2, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(50, ybottom - 2, 50);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-50, ybottom - 2, 50);
	glEnd();
	glPopMatrix();
	//sky end


	// //////////////////////// Track 
	glPushMatrix();
	///////////////////////////////////////// track 1 ////////////////////////////////////

	//Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop, 50);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop, 50);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom, 50);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom, 50);
	glEnd();
	glPopMatrix();
	//track bottom end
	glPushMatrix(); // side cover
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-3, ybottom, 0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(3, ybottom, 0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-3, ytop, 0);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(3, ytop, 0);
	glEnd();
	glPopMatrix(); // side cover over
				   //glDisable(GL_TEXTURE_2D);
				   //////////////////////////////////////////////////////// track 1 end ///////////////////////////

				   /////////////////////////////////////////////////////////////////// track 2 /////////////////////
				   //glEnable(GL_TEXTURE_2D);
				   //Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + movetrack2, 50);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + movetrack2, 50);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + movetrack2, 55);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + movetrack2, 55);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + movetrack2, 50);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + movetrack2, 50);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + movetrack2, 55);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + movetrack2, 55);
	glEnd();
	glPopMatrix();
	//track bottom end
	glPushMatrix();//side cover
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-3, ybottom + movetrack2, 50);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(3, ybottom + movetrack2, 50);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-3, ytop + movetrack2, 50);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(3, ytop + movetrack2, 50);
	glEnd();
	glPopMatrix();//side cover end
				  ///////////////////////////////////////////////////////// track 2 end /////////////////////


				  //////////////////////////////////////////////////////// track 3 //////////////////////////
				  //Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 55);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 55);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 75);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 75);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 55);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 55);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 75);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 75);
	glEnd();
	glPopMatrix();
	//track bottom end
	glPushMatrix();//side cover
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-3, ybottom + 5, 55);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(3, ybottom + 5, 55);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-3, ytop + 5, 55);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(3, ytop + 5, 55);
	glEnd();
	glPopMatrix();//side cover end
				  ///////////////////////////////////////////track 3 end///////////////////////////////////

				  /////////////////////////////////////////////// track 4 start .......//////////////////

	float t, zplace = 0, xplace = -2.3;
	float sharpemove = ytop;

	//glPushMatrix();//Sharpe Object

	for (zplace = 0; zplace < 3; zplace += 1.3) {
		for (xplace = -2.3; xplace < 3; xplace += 1.15) {
			glPushMatrix();//Sharpe Object 1
			glTranslatef(xplace, sharpeobjupanddown, zplace);
			t = 0;
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i < 30; ++i)
			{
				glVertex3f(0, sharpemove + 6, 75.8);
				glVertex3f(0 + 0.45 * cos(t), ytop + 5, 75.8 + 0.45 * sin(t));

				t += 2 * PI / 30;
			}
			glVertex3f(0 + 0.45 * cos(t), ytop + 5, 75.8 + 0.45 * sin(t));
			glEnd();
			glPopMatrix();//sharpe object 1 end

		}
	}
	//glPopMatrix();//sharpe object


	//Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 75);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 75);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 79);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 79);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 75);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 75);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 79);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 79);
	glEnd();
	glPopMatrix();
	//track bottom end


	/////////////////////////////////////////////// track 4 end ///////////////////////////

	////////////////////////////////////////////// track 5 start //////////////////////////
	//Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 79);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 79);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 85);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 85);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 79);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 79);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 85);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 85);
	glEnd();
	glPopMatrix();
	//track bottom end

	/////////////////////////////////////////////  track 5 end  //////////////////////////

	////////////////////////////////////////////// track 6 start /////////////////////////
	//Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 85 + ztrack6move);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 85 + ztrack6move);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 90 + ztrack6move);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 90 + ztrack6move);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 85 + ztrack6move);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 85 + ztrack6move);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 90 + ztrack6move);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 90 + ztrack6move);
	glEnd();
	glPopMatrix();
	//track bottom end
	glPushMatrix();//side cover
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-3, ybottom + 5, 85 + ztrack6move);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(3, ybottom + 5, 85 + ztrack6move);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-3, ytop + 5, 85 + ztrack6move);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(3, ytop + 5, 85 + ztrack6move);
	glEnd();
	glPopMatrix();//side cover end
				  ////////////////////////////////////////////// track 6 end /////////////////////////

				  ////////////////////////////////////////////// track 7 start /////////////////////////
				  //Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 130);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 130);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 140);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 140);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 130);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 130);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 140);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 140);
	glEnd();
	glPopMatrix();
	//track bottom end
	glPushMatrix();//side  cover
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-3, ybottom + 5, 130);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(3, ybottom + 5, 130);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-3, ytop + 5, 130);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(3, ytop + 5, 130);
	glEnd();
	glPopMatrix();//side cover end
				  ////////////////////////////////////////////// track 7 end /////////////////////////

				  /////////////////////////////////////////////  track 8 start ////////////////////////
	t, zplace = 0, xplace = -2.3;
	sharpemove = ytop;

	//glPushMatrix();//Sharpe Object

	for (zplace = 0; zplace < 3; zplace += 1.3) {
		for (xplace = -2.3; xplace < 3; xplace += 1.15) {
			glPushMatrix();//Sharpe Object 1
			glTranslatef(xplace, sharpeobjupanddown1, zplace);
			t = 0;
			glBegin(GL_TRIANGLE_STRIP);
			for (i = 0; i < 30; ++i)
			{
				glVertex3f(0, sharpemove + 9, 140.8);
				glVertex3f(0 + 0.45 * cos(t), ytop + 10, 140.8 + 0.45 * sin(t));

				t += 2 * PI / 30;
			}
			glVertex3f(0 + 0.45 * cos(t), ytop + 10, 140.8 + 0.45 * sin(t));
			glEnd();
			glPopMatrix();//sharpe object 1 end

		}
	}
	//glPopMatrix();//sharpe object

	glPushMatrix();//Base up on the sharpe object.
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTranslatef(0, sharpeobjupanddown1, 0);
	glBegin(GL_TRIANGLE_STRIP); // ground
	glVertex3f(-3, ytop + 10, 140);
	glVertex3f(-3, ytop + 10, 144);
	glVertex3f(3, ytop + 10, 140);
	glVertex3f(3, ytop + 10, 144);
	glEnd();// ground end
	glBegin(GL_TRIANGLE_STRIP); // up
	glVertex3f(-3, ytop + 12, 140);
	glVertex3f(-3, ytop + 12, 144);
	glVertex3f(3, ytop + 12, 140);
	glVertex3f(3, ytop + 12, 144);
	glEnd();// up end
	glBegin(GL_TRIANGLE_STRIP); // front
	glVertex3f(-3, ytop + 10, 140);
	glVertex3f(-3, ytop + 12, 140);
	glVertex3f(3, ytop + 10, 140);
	glVertex3f(3, ytop + 12, 140);
	glEnd();// front end
	glBegin(GL_TRIANGLE_STRIP); // far
	glVertex3f(-3, ytop + 10, 144);
	glVertex3f(-3, ytop + 12, 144);
	glVertex3f(3, ytop + 10, 144);
	glVertex3f(3, ytop + 12, 144);
	glEnd();// far end
	glPopMatrix();//Base up on the sharpe object end.

				  //Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 140);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 140);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 144);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 144);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 140);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 140);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 144);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 144);
	glEnd();
	glPopMatrix();
	//track bottom end

	/////////////////////////////////////////////  track 8 end ////////////////////////

	//////////////////////////////////////////// track 9 start ///////////////////////


	//Track top
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ytop + 5, 144);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ytop + 5, 144);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ytop + 5, 170);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ytop + 5, 170);
	glEnd();
	glPopMatrix();
	//track top end
	//track bottom start
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(3, ybottom + 5, 144);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-3, ybottom + 5, 144);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(3, ybottom + 5, 170);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-3, ybottom + 5, 170);
	glEnd();
	glPopMatrix();
	//track bottom end

	glPushMatrix();// square obj
				   //right
				   //middle
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobj, ytop + 6, 163);
	glVertex3f(xmovesobj, ytop + 6, 166);
	glVertex3f(xmovesobj, ytop + 10, 163);
	glVertex3f(xmovesobj, ytop + 10, 166);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobj + 0.2, ytop + 6, 163);
	glVertex3f(xmovesobj + 0.2, ytop + 6, 166);
	glVertex3f(xmovesobj + 0.2, ytop + 10, 163);
	glVertex3f(xmovesobj + 0.2, ytop + 10, 166);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobj, ytop + 6, 163);
	glVertex3f(xmovesobj + 0.2, ytop + 6, 163);
	glVertex3f(xmovesobj, ytop + 10, 163);
	glVertex3f(xmovesobj + 0.2, ytop + 10, 163);
	glEnd();
	//spring
	t = 0;
	float cirdist = xmovesobj;
	for (float cirr = 0.1; cirr <= 1.6; cirr += 0.2) {
		//glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 20; ++i)
		{
			glVertex3f(cirdist, (ytop + 8) + cirr * sin(t), 164.5 + cirr * cos(t));
			t += 2 * PI / 20;

		}
		glEnd();
		cirdist -= 0.4;
	}
	//spring cover plate
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-6, ytop + 6, 162);
	glVertex3f(-3, ytop + 6, 162);
	glVertex3f(-6, ytop + 10, 162);
	glVertex3f(-3, ytop + 10, 162);
	glEnd();
	//spring end
	//corners
	//bottom
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-3, ytop + 5, 162);
	glVertex3f(-3, ytop + 5, 167);
	glVertex3f(-3, ytop + 6, 162);
	glVertex3f(-3, ytop + 6, 167);
	glEnd();
	//front
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-3, ytop + 6, 162);
	glVertex3f(-3, ytop + 6, 163);
	glVertex3f(-3, ytop + 10, 162);
	glVertex3f(-3, ytop + 10, 163);
	glEnd();
	//up
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-3, ytop + 10, 162);
	glVertex3f(-3, ytop + 10, 167);
	glVertex3f(-3, ytop + 11, 162);
	glVertex3f(-3, ytop + 11, 167);
	glEnd();
	//far
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-3, ytop + 6, 166);
	glVertex3f(-3, ytop + 6, 167);
	glVertex3f(-3, ytop + 10, 167);
	glVertex3f(-3, ytop + 10, 167);
	glEnd();
	//corner end
	//right end
	//left 
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobjl, ytop + 6, 163);
	glVertex3f(xmovesobjl, ytop + 6, 167);
	glVertex3f(xmovesobjl, ytop + 10, 163);
	glVertex3f(xmovesobjl, ytop + 10, 167);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobjl - 0.2, ytop + 6, 163);
	glVertex3f(xmovesobjl - 0.2, ytop + 6, 167);
	glVertex3f(xmovesobjl - 0.2, ytop + 10, 163);
	glVertex3f(xmovesobjl - 0.2, ytop + 10, 167);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(xmovesobjl, ytop + 6, 163);
	glVertex3f(xmovesobjl - 0.2, ytop + 6, 163);
	glVertex3f(xmovesobjl, ytop + 10, 163);
	glVertex3f(xmovesobjl - 0.2, ytop + 10, 163);
	glEnd();
	//spring
	t = 0;
	float cirdistl = xmovesobjl;
	for (float cirr = 0.1; cirr <= 1.6; cirr += 0.2) {
		//glColor3f(1,0,0);
		glBegin(GL_LINE_LOOP);
		for (i = 0; i < 20; ++i)
		{
			glVertex3f(cirdistl, (ytop + 8) + cirr * sin(t), 164.5 + cirr * cos(t));
			t += 2 * PI / 20;

		}
		glEnd();
		cirdistl += 0.4;
	}
	//spring cover plate
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(6, ytop + 6, 162);
	glVertex3f(3, ytop + 6, 162);
	glVertex3f(6, ytop + 10, 162);
	glVertex3f(3, ytop + 10, 162);
	glEnd();
	//spring end
	//corners
	//bottom
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(3, ytop + 5, 162);
	glVertex3f(3, ytop + 5, 167);
	glVertex3f(3, ytop + 6, 162);
	glVertex3f(3, ytop + 6, 167);
	glEnd();
	//front
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(3, ytop + 6, 162);
	glVertex3f(3, ytop + 6, 163);
	glVertex3f(3, ytop + 10, 162);
	glVertex3f(3, ytop + 10, 163);
	glEnd();
	//up
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(3, ytop + 10, 162);
	glVertex3f(3, ytop + 10, 167);
	glVertex3f(3, ytop + 11, 162);
	glVertex3f(3, ytop + 11, 167);
	glEnd();
	//far
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(3, ytop + 6, 167);
	glVertex3f(3, ytop + 6, 166);
	glVertex3f(3, ytop + 10, 166);
	glVertex3f(3, ytop + 10, 167);
	glEnd();
	//corner end
	// left end
	glPopMatrix();//square obj end

				  /////////////////////////////////////////// track 9 end /////////////////////////

	glPopMatrix();
	/////////////////////////////////////// track end





	//object 1
	glPushMatrix();
	//right
	glTranslatef(0, -1.5, 22.5);
	glRotatef(obj1move, 0, 1, 0);
	glTranslatef(0, 1.5, -22.5);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-3, -1.5, 20);
	glVertex3f(-3, 2, 20);
	glVertex3f(-3, -1.5, 25);
	glVertex3f(-3, 2, 25);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-2.7, -1.5, 20);
	glVertex3f(-2.7, 2, 20);
	glVertex3f(-2.7, -1.5, 25);
	glVertex3f(-2.7, 2, 25);
	glEnd();
	//side cover
	glBegin(GL_TRIANGLE_STRIP);//front z =20
	glVertex3f(-3, -1.5, 20);
	glVertex3f(-2.7, -1.5, 20);
	glVertex3f(-3, 2, 20);
	glVertex3f(-2.7, 2, 20);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);//far z = 25
	glVertex3f(-3, -1.5, 25);
	glVertex3f(-2.7, -1.5, 25);
	glVertex3f(-3, 2, 25);
	glVertex3f(-2.7, 2, 25);
	glEnd();
	//side cover end
	//right end
	//left
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(3, -1.5, 20);
	glVertex3f(3, 2, 20);
	glVertex3f(3, -1.5, 25);
	glVertex3f(3, 2, 25);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(2.7, -1.5, 20);
	glVertex3f(2.7, 2, 20);
	glVertex3f(2.7, -1.5, 25);
	glVertex3f(2.7, 2, 25);
	glEnd();

	//side cover
	glBegin(GL_TRIANGLE_STRIP);// front z = 20
	glVertex3f(2.7, -1.5, 20);
	glVertex3f(3, -1.5, 20);
	glVertex3f(2.7, 2, 20);
	glVertex3f(3, 2, 20);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);// front z = 25
	glVertex3f(2.7, -1.5, 25);
	glVertex3f(3, -1.5, 25);
	glVertex3f(2.7, 2, 25);
	glVertex3f(3, 2, 25);
	glEnd();
	//side cover end
	//left end
	glPopMatrix();//obj1 end
	glutSwapBuffers();
}//draw scene end

 //Animate objects

 //obj1
void obj1(int value)
{
	resultobj1 = obj1move % 360;
	if (((resultobj1 >= 28 && resultobj1 <= 152) || (resultobj1 >= 208 && resultobj1 <= 332)) && (zmove >= 16.6 && zmove <= 18.6)) {
		cout << "Game Over." << endl;
	}
	if (((resultobj1 >= 28 && resultobj1 <= 152) || (resultobj1 >= 208 && resultobj1 <= 332)) && (zmove >= 23 && zmove <= 27)) {
		cout << "Game Over." << endl;
	}
	obj1move += 3.0;

	glutPostRedisplay();
	glutTimerFunc(100, obj1, 1);

}
//obj1 end

//obj2 track 2
static float counttimerseconds = 0;
static float flag = 0;
static float stopdir = 0; // 0 down and 1 for up slide.
void obj2(int value) {

	if (movedirectiontrack2 == 0) {
		if (movetrack2 < 4.8) {
			movetrack2 += 0.2;
			//cout << zmove<<" and "<<(movetrack2-0.2)<< endl;
			if ((movetrack2 - 0.2) <= 0 && zmove >= 48.3 && zmove <= 52.3) {
				flag = 1;
			}
			if (flag == 1) {
				ymovement = movetrack2;
				cout << ymovement << endl;
			}
			if (zmove >= 51) {
				flag = 0;
			}


		}
		if (movetrack2 >= 4.8) { // up stop of the slide
			stopdir = 1;
			counttimerseconds += 1.0;
			if (counttimerseconds == 30) {
				movedirectiontrack2 = 1;
				counttimerseconds = 0;
			}
		}
	}
	if (movedirectiontrack2 == 1) {
		if (movetrack2 > 0.1) {
			movetrack2 -= 0.2;
			if (flag == 1) {
				ymovement = movetrack2;
			}
			if (zmove >= 51 && ymovement >= movedirectiontrack2) {
				ymovement = ytop + 6.5;
				flag = 0;
			}
		}
		if (movetrack2 <= 0.1) { // down wait slide
			stopdir = 0;
			counttimerseconds += 1.0;
			if (counttimerseconds == 30) {
				movedirectiontrack2 = 0;
				counttimerseconds = 0;
			}

		}
	}

	if (zmove >= 48.3 && zmove <= 52.3 && stopdir != 0 && ymovement == 0) { // fall cylinder case
		cout << "fall down" << endl;
		ymovement = -6;
	}

	glutPostRedisplay();
	glutTimerFunc(framescount, obj2, 1);
}

//sharpe obj move up and down

void sharpeobj(int val) {
	//0 down  and 1 up
	if (sharpeobjupanddown >= -0.1) {
		sharpeobjdirection = 0;
	}
	if (sharpeobjupanddown <= -1.5) {
		sharpeobjdirection = 1;
	}

	if (sharpeobjdirection == 0) sharpeobjupanddown -= 0.05;
	else sharpeobjupanddown += 0.05;

	//Collision
	if (sharpeobjupanddown > -1 && sharpeobjupanddown < 0 && zmove >= 72.8 && zmove <= 77.5) {
		cout << "gameover at track4 " << endl;
	}
	glutPostRedisplay();
	glutTimerFunc(100, sharpeobj, 1);
}

//sharpe obj1 move up and down
static float sharpeobjdirection1 = 0;
void sharpeobj1(int val) {
	//0 down  and 1 up
	if (sharpeobjupanddown1 >= -0.1) {
		sharpeobjdirection1 = 0;
	}
	if (sharpeobjupanddown1 <= -4) {
		sharpeobjdirection1 = 1;
	}

	if (sharpeobjdirection1 == 0) sharpeobjupanddown1 -= 0.05;
	else sharpeobjupanddown1 += 0.05;

	if (sharpeobjupanddown1 < -1.9 && zmove >= 138 && zmove <= 143) {
		cout << "Game Over" << endl;
	}

	//Collision
	/*if (sharpeobjupanddown > -1 && sharpeobjupanddown < 0 && zmove >= 72.8 && zmove <= 77.5) {
	cout << "gameover at track4 " << endl;
	}*/

	glutPostRedisplay();
	glutTimerFunc(100, sharpeobj1, 1);
}

static float countertimetrack6 = 0;
float stopdirt6 = 0; // 0 for near and 1 for far.
void track6(int val) {
	//ztrack6move
	if (track6direction == 0) {

		if (ztrack6move >= 40) {
			countertimetrack6 += 1.0;
			stopdirt6 = 0;
			if (countertimetrack6 == 30) {
				track6direction = 1;
				countertimetrack6 = 0;
			}
		}
		else {
			if (zmove >= 83 + ztrack6move && zmove <= 90 + ztrack6move) {
				zmove += 1.0;
				lookat0 += 1.0;
				lookat1 += 1.0;
			}
			ztrack6move += 1.0;
		}
	}
	if (track6direction == 1) {

		if (ztrack6move <= 0) {
			stopdirt6 = 1;
			countertimetrack6 += 1.0;
			if (countertimetrack6 == 30) {
				track6direction = 0;
				countertimetrack6 = 0;
			}
		}
		else {
			if (zmove >= 83 + ztrack6move && zmove <= 90 + ztrack6move) {
				zmove -= 1.0;
				lookat0 -= 1.0;
				lookat1 -= 1.0;
			}
			ztrack6move -= 1.0;

		}
	}

	if (zmove >= 83 && stopdirt6 == 0 && zmove <= 88) {
		cout << "fall down at track 6" << endl;
		ymovement = -6;
	}

	glutPostRedisplay();
	glutTimerFunc(100, track6, 1);
}
static float sobjdirection = 0;
void sobj(int val) {
	if (sobjdirection == 0) {
		xmovesobj += 0.1;
		xmovesobjl -= 0.1;

		if (xmovesobj >= -0.2) {
			sobjdirection = 1;
		}
	}
	if (sobjdirection == 1) {
		xmovesobj -= 0.1;
		xmovesobjl += 0.1;

		if (xmovesobj <= -3) {
			sobjdirection = 0;
		}
	}

	if (xmovesobj > -1.8 && zmove > 161 && zmove < 166) {
		cout << "Game Over!!!!!!!!!" << endl;
	}

	//change lookat
	if (zmove > 144 && zmove < 170) {

		if (ylookat0 < 3) ylookat0 += 0.1;
	}
	if (zmove > 170) if (ylookat0 >= 0) ylookat0 -= 0.1;
	//change lookat end

	glutPostRedisplay();
	glutTimerFunc(100, sobj, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'X':
		Xangle -= 5.0;
		if (Xangle < 0.0) Xangle += 360.0;
		glutPostRedisplay();
		break;
	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 0.0) Yangle += 360.0;
		glutPostRedisplay();
		break;
	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;
	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 0.0) Zangle += 360.0;
		glutPostRedisplay();
		break;
	case ' ':
		zmove += 0.3;

		cylinderrotation += 5;
		lookat0 += 0.3;
		lookat1 += 0.3;
		//cout <<"OBJ 1 = "<< resultobj1 <<endl;

		glutPostRedisplay();
		break;
	case 'a':
		cout << xmovesobj << endl;
		//cout << obj1move%360 << endl;
		//cout << "z move = " << zmove << endl;
		cout << "cal val = " << sharpeobjupanddown1 << endl;
		cout << "Zmove = " << zmove;
		break;
	default:
		break;
	}
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press Space to move and Press x, X, y, Y, z, Z to turn the cylinder." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("SuryaRaoKarri_Game_Beta.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	obj1(1);
	obj2(1);
	sharpeobj(1);
	sharpeobj1(1);
	track6(1);
	sobj(1);
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}

