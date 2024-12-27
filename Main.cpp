
#pragma once
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ObjParser.h"
#include "Timer.h"

#include "glm/gtc/type_ptr.hpp"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")
#define WINDOW_TITLE "OpenGL Window"

HWND g_hWnd = NULL; //is variable, is a pointer, set to NULL for safety
WNDCLASS wndClass;

int xRot = 0;
int zRot = 0;

enum CAMERA_PROJECTION {
	ORTHO, PERSPECTIVE
};

//float eyeX = 0, eyeY = 0, centerX = 0, centerY = 0;

void createWindow();
void resetMaterial();
void loadMaterial(Material material);
void drawObject(Object* object);
void drawObject(Object* object, glm::mat4x4 ctm);
void drawObject(Object* object, glm::mat4x4 ctm, int depth);
void drawWithMatrix(Object* object, glm::mat4x4 ctm);
void setCamera(CAMERA_PROJECTION);

void rotateHead();
void raiseRArm();

// Parameters for gluLookAt
float eyeX = 0.0f, eyeY = 0.0f, eyeZ = 10.0f; // Camera position
float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f; // Target point
float upX = 0.0f, upY = 1.0f, upZ = 0.0f; // Up direction

float valueA = 0, valueB = 0, valueC = 0, valueD = 0;

float increVal = 0.2f;
float targetX = 0.0f;
float targetY = 0.0f;
float targetZ = 0.0f;

int raiseRArmCounter = -1;
int swingRArmCounter = -1;

Object* Chest;
Object* Pelvis;
Object* ArmJoint;
Object* Arm_002;
Object* ArmR;
Object* Hand;
Object* Forearm;
Object* CannonArm;
Object* Cannon;
Object* HandFinger;
Object* HandFinger2;
Object* Head;
Object* Neck;
Object* LegL;
Object* Anteana;
Object* LowerLegL;
Object* Eye;
Object* LegR;
Object* LowerLegR;
Object* ChestPlate;
Object* Tip;
Object* Weapon;


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:

		switch (wParam) {
			case 'Q':
				Head->rotate(glm::radians(5.f), 0, 1, 0);
				break;

			case 'A':
				Head->rotate(glm::radians(-5.f), 0, 1, 0);
				break;

			case 'W':
				Chest->rotate(glm::radians(5.f), 0, 1, 0);
				break;

			case 'S':
				Chest->rotate(glm::radians(-5.f), 0, 1, 0);
				break;

			case 'E':
				ArmR->rotate(glm::radians(5.f), 1, 0, 0);
				break;

			case 'D':
				ArmR->rotate(glm::radians(-5.f), 1, 0, 0);
				break;

			case 'C':
				ArmR->rotate(glm::radians(5.f), 0, 1, 0);
				break;

			case 'V': // Originally 'F'
				ArmR->rotate(glm::radians(-5.f), 0, 1, 0);
				break;

			case 'Z':
				ArmR->rotate(glm::radians(5.f), 0, 0, 1);
				break;

			case 'X': // Originally 'F'
				ArmR->rotate(glm::radians(-5.f), 0, 0, 1);
				break;

			//----------------------------------

			case 'R': // Originally 'T'
				Forearm->rotate(glm::radians(5.f), 1, 0, 0);
				break;

			case 'F': // Originally 'G'
				Forearm->rotate(glm::radians(-5.f), 1, 0, 0);
				break;

			case 'T': // Originally 'Y'
				Hand->rotate(glm::radians(5.f), 0, 1, 0);
				break;

			case 'G': // Originally 'H'
				Hand->rotate(glm::radians(-5.f), 0, 1, 0);
				break;

			case 'Y': // Originally 'U'
				HandFinger->rotate(glm::radians(5.f), 1, 0, 0);
				HandFinger2->rotate(glm::radians(-5.f), 1,0, 0);
				break;

			case 'H': // Originally 'J'
				HandFinger->rotate(glm::radians(-5.f), 1, 0, 0);
				HandFinger2->rotate(glm::radians(5.f), 1, 0, 0);
				break;

			//cannon arm --------------------------

			case 'U': // Originally 'I'
				CannonArm->rotate(glm::radians(5.f), 0, 1, 0);
				break;

			case 'J': // Originally 'K'
				CannonArm->rotate(glm::radians(-5.f), 0, 1, 0);
				break;

			case 'I': // Originally 'I'
				CannonArm->rotate(glm::radians(5.f), 0, 0, 1);
				break;

			case 'K': // Originally 'K'
				CannonArm->rotate(glm::radians(-5.f), 0, 0, 1);
				break;

			case 'O': // Originally 'I'
				CannonArm->rotate(glm::radians(5.f), 1, 0, 0);
				break;

			case 'L': // Originally 'K'
				CannonArm->rotate(glm::radians(-5.f), 1, 0, 0);
				break;

			case VK_NUMPAD4: // Numpad 4 increases targetX
				targetX += increVal;
				break;
			case VK_NUMPAD5: // Numpad 5 increases targetY
				targetY += increVal;
				break;
			case VK_NUMPAD6: // Numpad 6 increases targetZ
				targetZ += increVal;
				break;
			case VK_NUMPAD1: // Numpad 1 decreases targetX
				targetX -= increVal;
				break;
			case VK_NUMPAD2: // Numpad 2 decreases targetY
				targetY -= increVal;
				break;
			case VK_NUMPAD3: // Numpad 3 decreases targetZ
				targetZ -= increVal;
				break;

			case '1':
				raiseRArmCounter = 50;
				break;
			case '2':
				swingRArmCounter = 3;

			case VK_UP:
				xRot++;
				break;
			case VK_DOWN:
				xRot--;
				break;
			case VK_RIGHT:
				zRot++;
				break;
			case VK_LEFT:
				zRot--;
				break;
			default:
				break;
		}

		if (wParam == VK_ESCAPE) PostQuitMessage(0);
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

//Object* obj;
ObjParser parser = ObjParser();
GLUquadric* quad;

int ran = false;

float angle = 0;

glm::mat4 viewMat(1.0f);
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glPushMatrix();
	//	glTranslatef(centerX, centerY, -50.0f);
	//	quad = gluNewQuadric();
	//	gluQuadricDrawStyle(quad, GLU_OUTLINE_POLYGON);
	//	gluSphere(quad, 5, 10, 10);

	//glPopMatrix();

	glPushMatrix();

	//gluLookAt(eyeX, eyeY, 0, centerX, centerY, -50.0f, 0, 1, 0);
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

	glTranslatef(0, 5.0f, -20.0f);
	//glRotatef(-90, 0, 1, 0);
	glRotatef(zRot, 0, 1, 0);

	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	viewMat = glm::make_mat4(mat);

	//Head->scale(1.01f, 1.01f, 1.01f);
	//Head->rotate(glm::radians(5.0f), 0, 1, 0);

	//Head->position = { 50, 50, 0 };

	glm::mat4x4 ctm = glm::mat4x4(1.0f);
	drawObject(parser.objectList[0], ctm, 0);

	//glClear(GL_DEPTH_BUFFER_BIT);
	//glPushMatrix();
	//	glTranslatef(targetX, targetY, targetZ);
	//	float material1[3] = { 1,1,0 };
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material1);
	//	GLUquadricObj* var = nullptr;
	//	var = gluNewQuadric();
	//	gluQuadricDrawStyle(var, GLU_FILL);
	//	gluSphere(var, 0.5, 15, 15);
	//	gluDeleteQuadric(var);
	//glPopMatrix();
	//resetMaterial();
	//std::cout << "TargetX: " << targetX << ", TargetY: " << targetY << ", TargetZ: " << targetZ << std::endl;
	//Head->rotate(0.1f, 0, 1, 0);
	//angle += 1.5f;

	ran = true;
	//for (auto object : parser.objectList) {
	//	drawObject(object, ctm);
	//	//drawObject(object);
	//}

	//rotateHead();

	//Head->translate(0.1f, 0, 0);

	glPopMatrix();
}

float Lerp(float a, float b, float t) {
	return a * (1 - t) + b * t;
}

float headRotateStartTime = 0.0f;
void rotateHead() {
	auto angle = Lerp(0, 60, headRotateStartTime - Timer().currentTime());
	Head->rotate(glm::radians(1.f ), 0, 1, 0);
}

void raiseRArm() {
	if (raiseRArmCounter > 0) {
		ArmR->rotate(glm::radians(-1.0f), 1,0 , 0);
		ArmR->rotate(glm::radians(1.0f), 0, 1, 0);
		Forearm->rotate(glm::radians(-2.0f), 1, 0, 0);
		raiseRArmCounter--;

		if (raiseRArmCounter == 2) {
			std::cout << "ENABLE";
			Weapon->enabled = true;
		}
	}
}

void swingArmR() {
	if (swingRArmCounter > 0) {
		ArmR->rotate(glm::radians(18.0f), 1, 0, 0);
		ArmR->rotate(glm::radians(-18.0f), 0, 0, 1);
		Forearm->rotate(glm::radians(18.0f), 1, 0, 0);
		swingRArmCounter--;
	}
}


void drawObject(Object* object, glm::mat4x4 ctm, int depth) {
	ctm = ctm * object->getTransform();
	drawWithMatrix(object, ctm);

	//if (!ran)
	//{
	//	for (int i = 0; i < depth; i++) {
	//		std::cout << "\t";
	//	}
	//	std::cout << object->name << "\n";
	//}

	for (auto child : object->children) {
		if(child->enabled)
			drawObject(child, ctm, depth++);
	}
	return;
}

int debug = true;

void drawWithMatrix(Object* object, glm::mat4x4 ctm) {
	glm::vec3 scale = glm::vec3(1.0f);
	glm::quat rotation = glm::quat();
	glm::vec3 translation = glm::vec3(1.0f);
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(ctm, scale, rotation, translation, skew, perspective);

	auto axis = glm::axis(rotation);
	glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(rotation));

	if (debug && object == Arm_002) {
		glPushMatrix();
		glTranslatef(object->origin.x, object->origin.y, object->origin.z);
		float material[3] = { 1,0,0 };
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);

		GLUquadricObj* var = nullptr;
		var = gluNewQuadric();
		gluQuadricDrawStyle(var, GLU_FILL);
		gluSphere(var, 0.5, 15, 15);
		gluDeleteQuadric(var);

		glPopMatrix();
		resetMaterial();
	}

	glPushMatrix();	
	glMultMatrixf(glm::value_ptr(ctm));
	for (auto face : object->faceData) {
		if (face.size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else if (face.size() == 4) {
			glBegin(GL_QUADS);
		}
		else {
			glBegin(GL_POLYGON);
		}

		//glEnd();
		//glBegin(GL_LINE_STRIP);

		for (auto& vertex : face) {
			//glPushAttrib(GL_LIGHTING_BIT);
			if (vertex.material != nullptr) {
				loadMaterial(*vertex.material);
			}
			else {
				int a = 0;
			}
			glNormal3fv(vertex.normalData());
			glVertex3fv(vertex.vertexData());
			resetMaterial();
			//glPopAttrib();
		}

		glEnd();
	}
	glPopMatrix();
}

void drawObject(Object* object) {
	glPushMatrix();

	//object->getWorldTransform();
	//auto worldSpace = object->getWorldSpace();

	//glTranslatef(object->translation.x, object->translation.y, object->translation.z);

	//glTranslatef(worldSpace.x, worldSpace.y, worldSpace.z);
	//glTranslatef(object->localPosition.x, object->localPosition.y, object->localPosition.z);

	for (auto face : object->faceData) {
		if (face.size() == 3) {
			glBegin(GL_TRIANGLES);
		}
		else if (face.size() == 4) {
			glBegin(GL_QUADS);
		}
		else {
			glBegin(GL_POLYGON);
		}

		for (auto& vertex : face) {
			//glPushAttrib(GL_LIGHTING_BIT);

			if (vertex.material != nullptr) {
				loadMaterial(*vertex.material);
			}
			else {
				int a = 0;
			}

			glNormal3f(vertex.normX, vertex.normY, vertex.normZ);
			glVertex3f(vertex.x, vertex.y, vertex.z);

			resetMaterial();
			//glPopAttrib();
		}

		glEnd();
	}

	glPopMatrix();
}

void resetMaterial() {
	float defaultAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	float defaultDiffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	float defaultSpecular[] ={ 0.0, 0.0, 0.0, 1.0 };

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, defaultAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, defaultDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultSpecular);
}

void loadMaterial(Material material) {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.properties[GL_SHININESS][0]);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.properties[GL_AMBIENT].data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.properties[GL_DIFFUSE].data());
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.properties[GL_SPECULAR].data());

	float emission[4] = { 1.f,1.f,1.f,1.f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.properties[GL_EMISSION].data());

}

void Start() {
	headRotateStartTime = Timer().currentTime();
	Head->rotate(glm::radians(15.f), 0, 1, 0);
}

void Update() {
	raiseRArm();
	swingArmR();
}

//--------------------------------------------------------------------

int main(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	//WNDCLASSEX wc;
	//ZeroMemory(&wc, sizeof(WNDCLASSEX));
	
	//wc.cbSize = sizeof(WNDCLASSEX);
	//wc.hInstance = GetModuleHandle(NULL);
	//wc.lpfnWndProc = WindowProcedure;
	//wc.lpszClassName = WINDOW_TITLE;
	//wc.style = CS_HREDRAW | CS_VREDRAW;

	//if (!RegisterClassEx(&wc))
	//	return false;

	//HWND hWnd = CreateWindowExA(0, WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
	//	CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
	//	NULL, NULL, wc.hInstance, NULL);


	createWindow();

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	//HDC hdc = GetDC(hWnd);
	HDC hdc = GetDC(g_hWnd);
	
	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	//ShowWindow(hWnd, 1);
	ShowWindow(g_hWnd, 1);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//init

	//obj = new Object();
	//OpenGlParser parser = OpenGlParser();

	parser = ObjParser();

	parser.openMtl("robot2.mtl");
	parser.loadMaterial();

	parser.openObj("robot2.obj");
	parser.load();


	for (auto object : parser.objectList) {
		if (object->name == "Chest") Chest = object;
		else if (object->name == "Pelvis") Pelvis = object;
		else if (object->name == "ArmJoint") ArmJoint = object;
		else if (object->name == "Arm.002") Arm_002 = object; // Assuming the variable is adapted to Arm_002
		else if (object->name == "ArmR") ArmR = object;
		else if (object->name == "Hand") Hand = object;
		else if (object->name == "Forearm") Forearm = object;
		else if (object->name == "CannonArm") CannonArm = object;
		else if (object->name == "Cannon") Cannon = object;
		else if (object->name == "HandFinger") HandFinger = object;
		else if (object->name == "HandFinger2") HandFinger2 = object;
		else if (object->name == "Head") Head = object;
		else if (object->name == "Neck") Neck = object;
		else if (object->name == "LegL") LegL = object;
		else if (object->name == "Anteana") Anteana = object;
		else if (object->name == "LowerLegL") LowerLegL = object;
		else if (object->name == "Eye") Eye = object;
		else if (object->name == "LegR") LegR = object;
		else if (object->name == "LowerLegR") LowerLegR = object;
		else if (object->name == "ChestPlate") ChestPlate = object;
		else if (object->name == "Tip") Tip = object;
		else if (object->name == "Weapon") Weapon = object;
	}

	// Assigning parent-child relationships using Object's member function addParent
	Pelvis->addChild(Chest);
		Chest->addChild(ArmR);
			ArmR->addChild(Arm_002);
				Arm_002->addChild(ArmJoint);
				Arm_002->addChild(Forearm);
					Forearm->addChild(Hand);
						Hand->addChild(Weapon);
						Hand->addChild(HandFinger);
						Hand->addChild(HandFinger2);
		Chest->addChild(CannonArm);
			CannonArm->addChild(Cannon);
		Chest->addChild(Neck);
			Neck->addChild(Head);
				Head->addChild(Anteana);
				Head->addChild(Eye);
				Head->addChild(Tip);
		Chest->addChild(ChestPlate);
	Pelvis->addChild(LegL);
		LegL->addChild(LowerLegL);
	Pelvis->addChild(LegR);
		LowerLegL->addChild(LowerLegR);

		
	Weapon->enabled = false;

	ArmR->setOrigin(-2.8, 0.4, 0);
	Arm_002->setOrigin(-3.4, 0.4, 0);
	Forearm->setOrigin(-3.4, -0.4, 0);
	Hand->setOrigin(-1.f, -1.2, 0);
	HandFinger->setOrigin(-1.f, -1.2, 0);
	HandFinger2->setOrigin(-1.f, -1.2, 0);
	Chest->setOrigin(-0.f, -0.4f, 0);
	//ArmR->origin.x = 0.f;
	//ArmR->origin.y = 0.f;
	//ArmR->origin.z =0.f;


	//Arm_002->setOrigin(0,0, 0.695774f);
	//Forearm->setOrigin(0.f, 0.f, 0.f);
	//Hand->setOrigin(-2.8, -0.f, 1.0f);
	////HandFinger->setOrigin(-1.01921, -1, 4.86113);
	////HandFinger2->setOrigin(-1.01921, -1, 4.86113);
	//HandFinger->setOrigin(0.440792, -1.41174, -5.40215);
	//HandFinger2->setOrigin(-0.255423, -1.41174, -5.40215);

	//ArmR->setOrigin(0, 0.77307f, 0);
	//Arm_002->setOrigin(0, 0.786829f, 0);
	//Forearm->setOrigin(0, 1.37977f, 0.153257f);
	//Hand->setOrigin(-3.41106f, -0.079353f, -4.73028f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, 1, 1, 3000);
	
	//glFrustum(-10, 10, -10, 10, 0, 150);
	
	//glOrtho(-1, 1, -1, 1, -1, 1);
	
	
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	
	//glEnable(GL_LIGHT0);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, new float[3] {1.0f, 1.0f, 1.0f});
	////glLightfv(GL_LIGHT0, GL_SPECULAR,new float[3] {1.0f, 1.0f, 1.0f});
	//glLightfv(GL_LIGHT0, GL_POSITION, new float[3] {1, 1, 1});


	glEnable(GL_LIGHT0);
	float diffuse[] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	float specular[] = { 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	float lightDirection[] = { 1.3, -0.4, 0.2, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightDirection);

	//float ambeient[] = { 0.0f, 0.2f, 0.0f, 1.0f };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambeient);

	glMatrixMode(GL_MODELVIEW);
	Start();
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		Update();
		display();

		SwapBuffers(hdc);
	}

	//UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}

void createWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	/*
		Step 1
		Define and Register a Window.
	*/

	//	Window's structure
	//	Set all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//int x = 0;
	//ZeroMemory(&x, sizeof(x)); //set all memory in address of x to 0

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	//	MINIMAL
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;		//event handler, MUST HAVE
	wndClass.lpszClassName = "ABC";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//redraw

	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Practical", WS_OVERLAPPEDWINDOW, 0, 100, 1024, 1024, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);
}
//--------------------------------------------------------------------

