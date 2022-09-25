#include<windows.h>
#include <GL/glut.h>
#include<math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

float cx = 0;
float cy = 0;
float angle = 0;

void init()
{
    glClearColor(1, 1, 1, 0);
    glOrtho(-1280, 1280, -720, 720, -500, 500);
}
void circle(float radiusX, float radiusY, int r)
{
    glBegin(GL_POLYGON);
    for (float i = 0; i < 10; i += 0.01)
    {
        float x = cos(i) * r;
        float y = sin(i) * r;
        glVertex2f(x + radiusX, y + radiusY);
    }
    glEnd();
}

void line(int x2,int y2)
{
    glBegin(GL_LINES);
    glVertex2d(0, 0);
    glVertex2d(x2, y2);
}

void wheel(float x, float y)
{
    // glColor3f(1.0f,1.0f,0.0f);
    glColor3b(255, 255, 255);

    glTranslatef(x + cx, y, 0);
    glTranslatef(x, y + cy, 0);
    glRotated(angle, 0, 0, 1);

    glColor3f(1.0f, 0.0f, 0.0f);
    circle(0, 0, 100);

    glColor3f(0.0f, 0.0f, 0.0f);
    line(0,100);
    line(100,0);
    line(-100,0);
    line(0,-100);

    glEnd();
}
void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();

    // glRotated(angle,0,0,1);
    wheel(200, 100);
    glPopMatrix();

    glPushMatrix();

    // glRotated(angle,0,0,1);
    wheel(-200, 100);
    glPopMatrix();

    glPushMatrix();

    // glRotated(angle,0,0,1);
    wheel(-200, -100);
    glPopMatrix();

    glPushMatrix();
    // glRotated(angle,0,1,1);
    wheel(200, -100);
    glPopMatrix();
    //std::cout << "MAX width : " << GL_MAX_WIDTH << std::endl;

    glFlush();
}

void wheelMoveForward()
{
    cx += 0.5;
    cx > 1780 ? cx-=3560:cx;
    angle -= 0.32;
    glutPostRedisplay();
}

void wheelMoveReverse()
{
    cx -= 0.5;
    cx < -1780 ? cx+=3560:cx;
    angle += 0.32;
    glutPostRedisplay();
}

void wheelMoveUp()
{
    cy += 0.5;
    angle -= 0.32;
    glutPostRedisplay();
}

void wheelMoveDown()
{
    cy -= 0.5;
    angle += 0.32;
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{

    switch (key)
    {
    case GLUT_KEY_DOWN:
        glutIdleFunc(wheelMoveDown);
        break;

    case GLUT_KEY_UP:
        glutIdleFunc(wheelMoveUp);
        break;

    case GLUT_KEY_LEFT:
        glutIdleFunc(wheelMoveReverse);
        break;

    case GLUT_KEY_RIGHT:
        glutIdleFunc(wheelMoveForward);
        break;
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(50, 50);

    glutCreateWindow("");
    init();

    glutDisplayFunc(myDisplay);
    glutSpecialFunc(specialKey);
    glutMainLoop();

    return 0;
}
