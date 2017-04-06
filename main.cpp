#include "libraries\glew\glew.h"
#include "libraries\freeGlut\freeglut.h"
#include "ObjLoader.h"
#include "ObjectMesh.h"
#include "Texture.h"
#include "glm\glm.hpp"
#include "Game.h"
#include "RenderedObject.h"
#include "MoveForwardNode.h"
#include "TurnLeftNode.h"
#include "TurnRightNode.h"
#include "RepeatNextNode.h"
#include <iostream>
#include <ctime>

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_TRANSLATE_X -5
#define DEFAULT_TRANSLATE_Y -8
#define DEFAULT_TRANSLATE_Z -15
#define DEFAULT_ROTATE_ANGLE_X 30
#define DEFAULT_ROTATE_ANGLE_Y 0
#define SPACEBAR 32

int windowWidth = DEFAULT_WINDOW_WIDTH;
int windowHeight = DEFAULT_WINDOW_HEIGHT;
float translateX = DEFAULT_TRANSLATE_X;
float translateY = DEFAULT_TRANSLATE_Y;
float translateZ = DEFAULT_TRANSLATE_Z;
float rotateXAngle = DEFAULT_ROTATE_ANGLE_X;
float rotateYAngle = DEFAULT_ROTATE_ANGLE_Y;

int fullscreen = 0;
int stereo = 0;

void renderScene(void);
GLvoid ReSizeGLScene(int width, int height);

bool mouseDown = false;
glm::vec2 lastDraggedPos(0, 0);
glm::vec2 currentMousePos(0, 0);
double gameTimer;

void getMouseInput(int button, int state, int x, int y) {
	Scene* myScene = Game::getScene();
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouseDown = true;
			lastDraggedPos = glm::vec2(x, y);
			myScene->onMousePressed(x, y);
		}
		else {
			mouseDown = false;
			lastDraggedPos = glm::vec2(0, 0);
			myScene->onMouseReleased(x, y);
		}
	}
}

void getMouseHeldAndMoved(int x, int y) {
	Scene* myScene = Game::getScene();
	if (mouseDown) {
		myScene->onMouseDragged(x, y, lastDraggedPos);
		lastDraggedPos = glm::vec2(x, y);
		glutPostRedisplay();
	}
}

void getMouseMoved(int x, int y) {
	currentMousePos = glm::vec2(x, y);
	Scene* myScene = Game::getScene();
	if (myScene->getHud()->hasSelectedConnection()) {
		myScene->getHud()->updateLineConnection(x, y);
		glutPostRedisplay();
	}
}

void handleNodeMenu(int value) {
	HudNode* newNode = NULL;
	Hud* hud = Game::getScene()->getHud();
	if (value == 0) {
		hud->deleteNodeAt(currentMousePos);
	}
	else if (value == 1) {
		newNode = new MoveForwardNode(currentMousePos, glm::vec2(120, 60), hud->requestNodeId());
	}
	else if (value == 2) {
		newNode = new TurnLeftNode(currentMousePos, glm::vec2(120, 60), hud->requestNodeId());
	}
	else if (value == 3) {
		newNode = new TurnRightNode(currentMousePos, glm::vec2(120, 60), hud->requestNodeId());
	}
	else if (value == 4) {
		newNode = new RepeatNextNode(currentMousePos, glm::vec2(120, 70), hud->requestNodeId());
	}
	else return;

	if (newNode != NULL) {
		Game::getScene()->getHud()->addNode(newNode);
	}
	glutPostRedisplay();
}

void getKeyboardInput(unsigned char key, int x, int y){
	Scene* myScene = Game::getScene();
	glm::vec3 transVals;
	SceneObject* camera = myScene->getCamera();

	switch (key) {
		//move up
	case 'w':
		transVals = glm::vec4(0.0, -1.0, 0.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
		//move down
	case 's':
		transVals = glm::vec4(0.0, 1.0, 0.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
		//move left
	case 'a':
		transVals = glm::vec4(1.0, 0.0, 0.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
		//move right
	case 'd':
		transVals = glm::vec4(-1.0, 0.0, 0.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
		//move forward
	case 'r':
		transVals = glm::vec4(0.0, 0.0, 1.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
		//move backward
	case 'f':
		transVals = glm::vec4(0.0, 0.0, -1.0, 1.0)*Transformer::getRotationMatrix(camera->getRotation());
		camera->translateBy(transVals);
		break;
	case SPACEBAR:
		Game::startSimulation();
		break;
	}
	glutPostRedisplay();
}

void getSpecialInput(int key, int x, int y)
{
	Scene* myScene = Game::getScene();
	SceneObject* camera = myScene->getCamera();
	switch (key)
	{
	case GLUT_KEY_UP:
		camera->rotateBy(glm::vec3(-5, 0, 0));
		break;
	case GLUT_KEY_DOWN:
		camera->rotateBy(glm::vec3(5, 0, 0));
		break;
	case GLUT_KEY_LEFT:
		camera->rotateBy(glm::vec3(0, 5, 0));
		break;
	case GLUT_KEY_RIGHT:
		camera->rotateBy(glm::vec3(0, -5, 0));
		break;
	}

	glutPostRedisplay();
}

GLvoid InitGL() {

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.7f, 0.8f, 1.0f, 1.0f); //light blue
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 1, 1);
	glViewport(0, 0, windowWidth, windowHeight);

	// Enable Lighting
	glEnable(GL_LIGHTING);
	
	GLfloat light_pos[] { -1, 8, -1, 1 };

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos); // Position the lights

	// Set light intensity and color for each component
	glLightf(GL_LIGHT0, GL_DIFFUSE, (0.6, 0.6, 0.6, 1));
	glLightf(GL_LIGHT0, GL_AMBIENT, (0.5, 0.5, 0.5, 1));
	glLightf(GL_LIGHT0, GL_SPECULAR, (1, 1, 1, 1));

	glEnable(GL_LIGHT0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)windowWidth / (GLfloat)windowHeight, 0.1f, 2000.0f);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	Game::draw();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char **argv) {

	//initialize glut stuff
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(300, 100);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("Lab 2: Model & Texture Importing");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_3")) {
		std::cout << " GLEW Version is 3.3\n ";
	}
	else {
		std::cout << "GLEW 3.3 not supported\n ";
	}

	InitGL();
	Game::init();
	Scene* myScene = Game::getScene();
	myScene->getCamera()->rotateBy(glm::vec3(DEFAULT_ROTATE_ANGLE_X, DEFAULT_ROTATE_ANGLE_Y, 0));
	myScene->getCamera()->translateBy(glm::vec3(DEFAULT_TRANSLATE_X, DEFAULT_TRANSLATE_Y, DEFAULT_TRANSLATE_Z));

	// set up display function
	glutDisplayFunc(renderScene);
	// This is called everytime the window is altered
	glutReshapeFunc(ReSizeGLScene);
	// set up keyboard input function
	glutKeyboardFunc(getKeyboardInput);
	glutSpecialFunc(getSpecialInput);
	//glutJoystickFunc(getJoystickInput, 25);
	//gets mouse input
	glutMouseFunc(getMouseInput);
	//function to call when the mouse is moved and held down
	glutMotionFunc(getMouseHeldAndMoved);
	//function to call when the mose is moved (not held)
	glutPassiveMotionFunc(getMouseMoved);

	glutCreateMenu(handleNodeMenu);
	glutAddMenuEntry("DELETE THIS NODE", 0);
	glutAddMenuEntry("Add 'Move Forward' node", 1);
	glutAddMenuEntry("Add 'Turn Left' node", 2);
	glutAddMenuEntry("Add 'Turn Right' node", 3);
	glutAddMenuEntry("Add 'Repeat Next' node", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	int milliseconds = 0;

	while (1) {
		clock_t startTime = clock();
		if (Game::getState() == playing && milliseconds >= 500) {
			milliseconds = 0;
			Game::runSimulation();
			glutPostRedisplay();
		}
		glutMainLoopEvent();
		clock_t endTime = clock();
		milliseconds += (endTime-startTime) / (CLOCKS_PER_SEC / 1000);
	}

	return 0;
}

/* this gets called everytime your window resizes or moves */
GLvoid ReSizeGLScene(int width, int height) {
	std::cout << "RESIZING WINDOW " <<width <<" " <<height <<std::endl;
	Transformer::setWindowSize(width, height);
	if (height == 0)
		height = 1;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 2000.0f);

	windowWidth = width;
	windowHeight = height;
}