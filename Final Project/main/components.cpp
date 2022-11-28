/*
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
*/

#include "variables.cpp"

void circle(float radiusX, float radiusY)
{
    glBegin(GL_POLYGON);
    for (float i = 0; i < 10; i += 0.01)
    {
        float x = cos(i) * radiusX;
        float y = sin(i) * radiusY;
        glVertex2f(x,y);
    }
    glEnd();
}

void line(int x1,int y1,int x2,int y2)
{
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void rectangle(int x,int y,int x_len,int y_len )
{
    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3d(x,y,0);
    glVertex3d(x+x_len,y,0);
    glVertex3d(x+x_len,y+y_len,0);
    glVertex3d(x,y+y_len,0);
    glEnd();
    glPopMatrix();
}

void rectangle3d(int x,int y,int lenX,int lenY,int depthIn,int depthOut)
{
    /*
    */
    //front
    glColor3f(0.5f,0.0f,0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y,depthOut);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glVertex3f(x,y-lenY,depthOut);
    glEnd();

    //back
    glColor3f(0.5f,0.0f,0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glEnd();

    //right
    glColor3f(0.0f,0.5f,0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glEnd();

    //left
    glColor3f(0.0f,0.5f,0.0f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y,depthOut);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glVertex3f(x,y-lenY,depthOut);
    glEnd();

    //bottom
    glColor3f(0.0f,0.0f,0.5f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x,y-lenY,depthOut);
    glVertex3f(x+lenX,y-lenY,depthOut);
    glVertex3f(x+lenX,y-lenY,depthIn);
    glVertex3f(x,y-lenY,depthIn);
    glEnd();

    //top
    glColor3f(0.0f,0.0f,0.5f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(x+lenX,y,depthOut);
    glVertex3f(x+lenX,y,depthIn);
    glVertex3f(x,y,depthIn);
    glVertex3f(x,y,depthOut);
    glEnd();
}


void makeFont(int x,int y,string text)
{

    if(scr_menu.check_y == y)
    {
        glColor3f(1.0f, 0.4f, 0.4f);
    }
    else
    {
        glColor3f(0.5f, 0.5f, 0.5f);
    }
    glNormal3f(0.0f, 0.0f, -1.0f);

    glRasterPos2f(x, y);
    for(char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void frameRateShow()
{
    game.screen.frame++;
    game.screen.time=glutGet(GLUT_ELAPSED_TIME);
    glColor3f(1.0f, 0.4f, 0.4f);
    makeFont(-1300,700,"FPS - "+to_string(game.screen.fps));
    if (!game.pause && game.screen.time - game.screen.timebase > game.screen.frameRateDelay)
    {
        game.screen.fps = game.screen.frame*1000.0/(game.screen.time-game.screen.timebase);
        game.screen.timebase = game.screen.time;
        game.screen.frame = 0;
    }
}

void ammoRemainingShow()
{
    makeFont(-1300,600,"Ammo Remaining - "+to_string(ammo_size-game.ship.ammo_count));
    makeFont(1000,700,"Ammo Missied - "+to_string(game.ship.ammo_missed));
}

void infoShow()
{
    frameRateShow();
    ammoRemainingShow();
}

void screen_menu()
{
    makeFont(-120,0,"Start Game");
    makeFont(-120,-100,"Settings");
    makeFont(-120,-200,"Exit");
    makeFont(scr_menu.check_x,scr_menu.check_y,">");
}

void Settings()
{
    makeFont(-120,0,"Select Level");
    makeFont(-120,-100,"Back");
    makeFont(scr_menu.check_x,scr_menu.check_y,">");
}

void level()
{
    makeFont(-120,0,level_list[sett.lvl]);
    makeFont(-120,-100,"Back");
    makeFont(level_list[sett.lvl].length()*level_list[sett.lvl].length()*4,5,">");
    makeFont(-200,5,"<");
}
