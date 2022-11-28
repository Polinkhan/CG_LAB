#include<windows.h>
#include <GL/glut.h>
#include<math.h>
#include <stdlib.h>
#include <iostream>
#include "variable.h"
#include "components.cpp"
#include "eventHandler.cpp"
#include "mainGame.cpp"

using namespace std;

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);   // Enable lighting
    glEnable(GL_LIGHT0);     // Enable light #0    // Enable light #1
    glEnable(GL_NORMALIZE);  // Automatically normalize normals
    glShadeModel(GL_SMOOTH); // Enable smooth shading
}

void shape(int width,int height)
{
    //glClearColor(1, 1, 1, 0);
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,(double)width/(double)height,1.00,200.0);
}

void myDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    GLfloat ambientColor[] = {1, 1, 1, 0.1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    // Add positioned light
    GLfloat diffuseLightColor0[] = {0.8, 0.8, 0.8, 0.9};
    GLfloat specularLightColor0[] = {0.2, 0.2, 0.2, 0.1f};
    GLfloat lightPos0[] = {1, 1, 1, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLightColor0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    glPushMatrix();
    //glRotated(45,1,0,0);
    glBegin(GL_POLYGON);
    glColor3f(0.92f, 0.92f, 0.92f);
    glVertex3d(-1000,-800,-200);
    glColor3f(0.5f, 0.0, 0.0);
    glVertex3d(1000,-800,-200);
    glColor3f(0.92f, 0.92f, 0.92f);
    glVertex3d(1000,800,-200);
    glColor3f(0.0f, 0.0f, 0.5f);
    glVertex3d(-1000,800,-200);
    glEnd();
    glPopMatrix();

    glutPostRedisplay();

    glPushMatrix();
    glTranslatef(0,0,-20);
    glScaled(0.01,0.01,0.01);
    if(win_list.menu_Screen) screen_menu();
    if(win_list.setting_Screen)Settings();
    if(win_list.level_Screen)level();
    if(win_list.game_Screen)Game();
    //if(game.pause)pauseScreen();



    glPopMatrix();

    glutSwapBuffers();
}



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    //screen.width = glutGet(GLUT_SCREEN_WIDTH);
    //screen.height = glutGet(GLUT_SCREEN_HEIGHT);

    screen.width = 1366;
    screen.height = 768;

    cout << screen.width << " " << screen.height;

    glutInitWindowSize(screen.width,screen.height);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("");
    glEnable(GL_DEPTH_TEST);
    glutReshapeFunc(shape);
    //glutFullScreen();

    initRendering();

    glutDisplayFunc(myDisplay);
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyboardKey);
    glutMouseFunc(mouseKey);
    glutMainLoop();

    return 0;
}
