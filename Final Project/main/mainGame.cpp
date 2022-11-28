#include <cstdlib>
void spaceShip()
{
    glPushMatrix();

    glTranslatef(0+game.ship.pos_x,-600+game.ship.pos_y,0);

    glPushMatrix();
    glRotated(45,1,0,0);
    glRotated(game.ship.rotateY,0,0,1);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidTorus(12,50,10,10);

    glPushMatrix();
    glTranslatef(0,50,0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(20, 20, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-50,0);
    glColor3f(0.0f, 0.0f, 1.0f);
    glutSolidSphere(20, 20, 10);
    glPopMatrix();

    glPopMatrix();

    rectangle(-60,5,-80,-10);
    rectangle(60,5,80,-10);

    glPushMatrix();
    glRotated(game.ship.rotateY/5,1,0,0);
    rectangle3d(80,25,80,50,-30,30);
    rectangle3d(-160,25,80,50,-30,30);
    glPopMatrix();

    glPopMatrix();

    for (int i=0+game.ship.ammo_count; i<ammo_size; i++)
    {
        game.ship.ammo[i][0] = game.ship.pos_x;
        game.ship.ammo[i][1] = game.ship.pos_y;
    }
    for (int i=0; i< game.ship.ammo_count; i++)
    {
        if(!game.ship.ammo_dismiss[i])
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            //rectangle(game.ship.ammo[i][0],-550+game.ship.ammo[i][1],10,15);
            glPushMatrix();
            glTranslated(game.ship.ammo[i][0],-550+game.ship.ammo[i][1],0);
            glNormal3d(1, 0, 1);
            glutSolidSphere(10, 10, 10);
            glPopMatrix();
        }
    }
}

void bricks()
{
    for (int i=0; i< 25; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(!game.bricks.isBreak[i][j])
            {
                glPushMatrix();
                glTranslatef(game.bricks.pos_X[i],game.bricks.pos_Y[j],0);
                glColor3f(1.0f, 0.0f, 0.0f);;
                glPushMatrix();
                glTranslatef(25,-10,0);
                glPushMatrix();
                glRotated(game.bricks.rotate_x,1,1,1);
                glutSolidTorus(5,18,10,10);
                glPopMatrix();
                glPopMatrix();
                //rectangle3d(0,0,50,20,-5,5);
                glPopMatrix();
            }
        }
    }
}

void background()
{
    glColor3f(0.92f, 0.92f, 0.92f);
    glPushMatrix();
    glTranslatef(game.screen.bg_rotate/20,game.screen.bg_rotate,-100);
    line(-1300,-600,-1300,200);
    line(-1000,-400,-1000,400);
    line(-800,-300,-800,300);
    line(-500,-900,-500,900);
    line(-200,-800,-200,-100);
    line(0,700,0,200);
    line(200,800,200,-100);
    line(500,300,500,-100);
    line(800,300,800,400);
    line(1000,1200,1000,600);
    line(1300,-500,1300,500);
    glPopMatrix();
}

Game()
{
    infoShow();
    spaceShip();
    bricks();
    background();

    if(game.ship.ammo_count == 200)
    {
        bool flag = false;
        for(int i = 0; i<25; i++)
        {
            for(int j = 0; j< 3; j++)
            {
                if(!game.bricks.isBreak[i][j]) flag = true;
            }
        }
        if(flag)
        {
            makeFont(0,0,"Game Over");
            game.pause = true;
        }
    }
    else
    {
        bool flag = true;
        for(int i = 0; i<25; i++)
        {
            for(int j = 0; j< 3; j++)
            {
                if(!game.bricks.isBreak[i][j])
                {
                    flag = false;
                    break;
                }
            }
        }
        if(flag)
        {
            makeFont(0,0,"Congratulation");
            game.pause = true;
        }
    }
}
