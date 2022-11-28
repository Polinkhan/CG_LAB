void checkUP()
{
    if(scr_menu.check_y < 0)scr_menu.check_y += 100;
    glutPostRedisplay();
}

void checkDOWN()
{
    if(scr_menu.check_y > -200)scr_menu.check_y -=100;
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    if(win_list.menu_Screen || win_list.setting_Screen || win_list.level_Screen)
    {
        switch (key)
        {
        case GLUT_KEY_UP:
            checkUP();
            break;

        case GLUT_KEY_DOWN:
            checkDOWN();
            break;
        }
    }
    if(win_list.level_Screen)
    {
        switch (key)
        {
        case GLUT_KEY_LEFT:
            sett.lvl - 1 < 0 ? sett.lvl += 2 : sett.lvl -= 1;
            sett.lvl == 0 ? game.ship.speed = 0.5 : sett.lvl == 1 ? game.ship.speed = 1.0 : game.ship.speed = 1.5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            sett.lvl = (sett.lvl+1)%3;
            sett.lvl == 0 ? game.ship.speed = 0.5 : sett.lvl == 1 ? game.ship.speed = 1.0 : game.ship.speed = 1.5;
            glutPostRedisplay();
            break;
        }
    }
}

void run()
{
    if(!game.pause)
    {
        game.bricks.rotate_x+=0.2;
        if(game.screen.bg_rotate < -1800)
        {
            game.screen.bg_rotate = 1700;
        }
        else
        {
            game.screen.bg_rotate -= 5;
        }
        if(game.ship.moveTo=='a' && game.ship.pos_x > (-screen.width+screen.padding))
        {
            game.ship.pos_x -= game.ship.speed;
            game.ship.rotateY += game.ship.speed;
        }
        else if (game.ship.moveTo=='d' && game.ship.pos_x < (screen.width-screen.padding))
        {
            game.ship.pos_x += game.ship.speed;
            game.ship.rotateY -= game.ship.speed;
        }
        for(int i=0; i<game.ship.ammo_count; i++)
        {
            for(int p=0; p<3; p++)
            {
                if(game.ship.ammo[i][1] == game.bricks.pos_Y[p]+500)
                {
                    for(int k=0; k<25; k++)
                    {
                        if(!game.bricks.isBreak[k][p] && game.ship.ammo[i][0] > game.bricks.pos_X[k]-10 && game.ship.ammo[i][0] < game.bricks.pos_X[k]+50)
                        {
                            game.ship.ammo_dismiss[i] = 1;
                            game.bricks.isBreak[k][p] = 1;
                        }
                    }
                }
                else if(!game.ship.ammo_dismiss[i] && game.ship.ammo[i][1] > 1100)
                {
                    game.ship.ammo_dismiss[i] = 1;
                    game.ship.ammo_missed++;
                }
            }
            if(!game.ship.ammo_dismiss[i])game.ship.ammo[i][1]++;
            //cout << game.ship.ammo[i][1] << endl;
        }
    }
    glutPostRedisplay();
}


void gamePause()
{
    cout << "Pause";
    game.pause = !game.pause;
    makeFont(-120,0,"Pause");
    //glutEstablishOverlay();
}



void keyboardKey(unsigned char key,int x,int y)
{
    if(win_list.menu_Screen)
    {
        switch(key)
        {
        case 13:
            if(scr_menu.check_y == 0)
            {
                win_list.game_Screen = true;
                win_list.menu_Screen = false;
                glutPostRedisplay();
            }
            else if(scr_menu.check_y == -100)
            {
                scr_menu.check_y = 0;
                win_list.menu_Screen = false;
                win_list.setting_Screen = true;
                glutPostRedisplay();
            }
            else if (scr_menu.check_y == -200)
            {
                exit(0);
            }
            break;
        default:
            break;
        }
    }
    else if(win_list.setting_Screen)
    {
        switch(key)
        {
        case 13:
            if(scr_menu.check_y == 0)
            {
                win_list.setting_Screen = false;
                win_list.level_Screen = true;
                glutPostRedisplay();
            }
            else if(scr_menu.check_y == -100)
            {
                scr_menu.check_y = 0;
                win_list.menu_Screen = true;
                win_list.setting_Screen = false;
                glutPostRedisplay();
            }
            break;
        default:
            break;
        }
    }
    else if(win_list.level_Screen)
    {
        switch(key)
        {
        case 13:
            if(scr_menu.check_y == -100)
            {
                scr_menu.check_y = 0;
                win_list.setting_Screen = true;
                win_list.level_Screen = false;
                glutPostRedisplay();
            }
            break;
        default:
            break;
        }
    }
    else if(win_list.game_Screen)
    {
        switch(key)
        {
        case 27:
            gamePause();
            break;

        case 'a':
            game.ship.moveTo = key;
            glutIdleFunc(run);

            break;

        case 'd':
            game.ship.moveTo = key;
            glutIdleFunc(run);
            break;

        case 32:
            game.ship.moveTo = key;
            glutIdleFunc(run);
            break;

        default:
            break;
        }
    }
}

void mouseKey(int button, int state, int x, int y)
{
    if(win_list.game_Screen)
    {

        switch(button)
        {
        case GLUT_LEFT_BUTTON ://
            if(state == GLUT_DOWN)
            {
                if(game.ship.ammo_count < ammo_size) game.ship.ammo_count++;
            }
            break;

        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN)
            {
                cout << "right" << endl;
            }
            break;

        default:
            break;
        }

    }
}
