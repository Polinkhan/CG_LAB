#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

float rotatex = 0;
float rotatey = 0;
float rotateVal = 0;

void shape(int width,int height)
{
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(double)width/(double)height,1.00,200.0);
}

void squre3d(int x,int y,int lenX,int lenY,int depthIn,int depthOut, int rX,int rY,int rV)
{
    glTranslated(0,0,-20);
    glRotated(rV+rotateVal,rX+rotatex,rY,0);

    //front
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y,depthOut);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glVertex3f(x,y-lenY,depthOut);
    glEnd();
    glPopMatrix();

    //back
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glEnd();
    glPopMatrix();

    //right
    glPushMatrix();
    glColor3f(0.0f,0.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glEnd();
    glPopMatrix();

    //left
    glPushMatrix();
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y,depthOut);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glVertex3f(x,y-lenY,depthOut);
    glEnd();
    glPopMatrix();

    //bottom
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y-lenY,depthOut);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glEnd();
    glPopMatrix();

    //top
    glPushMatrix();
    glColor3f(0.0f,1.0f,1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y,depthOut);
    glEnd();
    glPopMatrix();
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    squre3d(-3,3,6,6,-4,-3,0,0,0);
    glPopMatrix();

    glPushMatrix();
    squre3d(-3,-3,6,1,-4,4,0,0,0);
    glPopMatrix();

    glPushMatrix();
    squre3d(-3,-4,1,4,3,4,0,0,0);
    glPopMatrix();

    glPushMatrix();
    squre3d(2,-4,1,4,3,4,0,0,0);
    glPopMatrix();

    glPushMatrix();
    squre3d(-3,-4,1,4,-3,-4,0,0,0);
    glPopMatrix();

    glPushMatrix();
    squre3d(2,-4,1,4,-3,-4,0,0,0);
    glPopMatrix();


    glutSwapBuffers();
}

void rotateX()
{
    rotatex = 1;
    rotatey = 0;
    rotateVal += 0.1;
    glutPostRedisplay();
}

void rotateY()
{
    rotatey = 1;
    rotatex = 0;
    rotateVal += 0.1;
    glutPostRedisplay();
}

void rotateXY()
{
    rotatey = 1;
    rotatex = 1;
    rotateVal += 0.1;
    glutPostRedisplay();
}


void keyboardKey(unsigned char key,int x,int y)
{
    switch(key)
    {
    case 'a':
        glutIdleFunc(rotateX);
        break;
    case 'd':
        glutIdleFunc(rotateY);
        break;
    case 'w':
        glutIdleFunc(rotateXY);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("3D Objects");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(shape);
    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboardKey);
    glutMainLoop();

    return 0;
}
