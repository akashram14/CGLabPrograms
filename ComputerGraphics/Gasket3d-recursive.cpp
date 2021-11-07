#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef GLfloat point3[3];

void triangle(point3 a, point3 b, point3 c) {
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glEnd();
}

void recur(point3 a, point3 b, point3 c, int k) {
    if (k > 0) {
        point3 ab, bc, ac;
        for (int i = 0; i < 3; i++) ab[i] = (a[i] + b[i]) / 2;
        for (int i = 0; i < 3; i++) ac[i] = (a[i] + c[i]) / 2;
        for (int i = 0; i < 3; i++) bc[i] = (b[i] + c[i]) / 2;
        recur(a, ac, ab, k - 1);
        recur(b, bc, ab, k - 1);
        recur(c, ac, bc, k - 1);
    }
    else {
        triangle(a, b, c);
    }

}

void tetrahedron(point3 a, point3 b, point3 c, point3 d, int n) {
    glColor3f(1.0, 0.0, 0.0);
    recur(a, b, c, n);

    glColor3f(0, 1.0, 0.0);
    recur(a, c, d, n);

    glColor3f(0, 0, 1.0);
    recur(a, b, d, n);

    glColor3f(0, 0, 0);
    recur(b, c, d, n);

}

void myInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glClearColor(0, 0, 0, 1.0);
    glColor3f(0.0, 0.0, 0.0);

    //z-buffer
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    point3 a = { 0,1,0 };
    point3 b = { -1,0,0 };
    point3 c = { 1,0,0 };
    point3 d = { 0,0,1 };
    int n = 5;
    
    tetrahedron(a, b, c, d, n);

    glFlush();
}


int32_t main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);


    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("2D Sirepinski Gasket");
    glutDisplayFunc(display);

    myInit();

    glutMainLoop();

}