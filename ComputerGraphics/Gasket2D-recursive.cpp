#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef GLfloat point2[2];

void triangle(point2 a, point2 b, point2 c) {
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
        glVertex2fv(a);
        glVertex2fv(b);
        glVertex2fv(c);
        glEnd();
}

void recur(point2 a, point2 b, point2 c, int k) {
    if(k>0) {
        point2 ab, bc, ac;
        for (int i = 0; i < 2; i++) ab[i] = (a[i] + b[i]) / 2;
        for (int i = 0; i < 2; i++) ac[i] = (a[i] + c[i]) / 2;
        for (int i = 0; i < 2; i++) bc[i] = (b[i] + c[i]) / 2;
        recur(a, ac, ab,k-1);
        recur(b, bc, ab,k-1);
        recur(c, ac, bc,k-1);
    }
    else {
        triangle(a, b, c);
    }

}

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    point2 a = {0,1};
    point2 b = {-1,0};
    point2 c = {1,0};
    int n = 5;
    recur(a, b, c, n);

    glFlush();
}


int32_t main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("2D Sirepinski Gasket");
	glutDisplayFunc(display);

    myInit();

    glutMainLoop();

}