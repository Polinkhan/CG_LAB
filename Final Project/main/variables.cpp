struct WindowList
{
    bool menu_Screen = true;
    bool setting_Screen = false;
    bool level_Screen = false;
    bool game_Screen = false;

    //bool menu_Screen = false;
    //bool game_Screen = true;
} win_list;

struct Screen
{
    int height = 0;
    int width = 0;
    int padding = 100;
} screen;

struct Screen_menu
{
    int check_x = -170;
    int check_y = 0;
} scr_menu;


string level_list[3] = {"EASY","MEDIUM","HARD"};
const int ammo_size = 200;

struct Settings
{
    int lvl = 0;
} sett;

struct MainGame
{
    struct SpaceShip
    {
        float pos_x = 0;
        float pos_y = 0;
        float speed = 0.5;
        char moveTo = '32';
        int ammo_count = 0;
        int ammo_missed = 0;
        int ammo[ammo_size][2] = {0};
        bool ammo_dismiss[ammo_size] = {0};
        float rotateY = 0;
    } ship;
    struct Bricks{
        int isBreak[25][3] = {0};
        int pos_X[25] = {-1200,-1100,-1000,-900,-800,-700,-600,-500,-400,-300,-200,-100,0,100,200,300,400,500,600,700,800,900,1000,1100,1200};
        int pos_Y[3] = {500,400,300};
        float rotate_x = 0.0;
    }bricks;
    struct Screen
    {
        int fps = 0;
        int frame=0;
        int time;
        int timebase=0;
        int frameRateDelay = 500;
        float bg_rotate = 0.0;
    }screen;
    bool pause = false;
} game;
