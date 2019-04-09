#if defined(_WIN32)
    #include "GL/glut.h"
#else
    #include <GLUT/glut.h>
#endif

#include "../common/coordinateFrame.h"

#include <iostream>

using namespace std;

GLfloat x = 0.0f;
GLfloat y = 1.0f;
GLfloat z = 0.0f;

CoordinateFrame mainframe;

void changeSize(int w, int h) {
	if(h == 0) h = 1;

    double ratio = w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glViewport(0, 0, w, h);
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
	glMatrixMode(GL_MODELVIEW);
}

void init() {

	frameBufferData(mainframe);

}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(	12.0,12.0,12.0,
				0.0 ,0.0 ,0.0,
				0.0 ,1.0 ,0.0
	);

	glRotatef(x, 1.0, 0.0, 0.0);
	glRotatef(y, 0.0, 1.0, 0.0);
	glRotatef(z, 0.0, 0.0, 1.0);

	glColor3f(1.0,1.0,1.0);

    frameDraw(mainframe);

	glutSwapBuffers();
}

void keyboardCallback(unsigned char key_code, int xaaa, int yaaa) {
	switch (key_code) {
        case 'w':
            x += 10.0f;
            break;
        case 's':
            x -= 10.0f;
            break;
        case 'a':
            y -= 10.0f;
            break;
        case 'd':
            y += 10.0f;
            break;
        case 'e':
            z += 10.0f;
            break;
        case 'r':
            z -= 10.0f;
            break;
        default:
            break;
	}

	glutPostRedisplay();
}

void glut(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(0,0);
	glutInitWindowSize(1450,900);
    glutCreateWindow(argv[1]);

    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
	glutKeyboardFunc(keyboardCallback);

    glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	init();

    glutMainLoop();
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		cout << "No scene file provided." << endl;
		return 2;
	}
	mainframe = parse(argv[1]);
	if (!mainframe) {
		return 3;
	}

	glut(argc, argv);

	unmkCoordinateFrame(mainframe);

	return 1;
}




