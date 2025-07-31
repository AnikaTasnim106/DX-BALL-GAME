#include "iGraphics.h"
#include "iSound.h"
/*
function iDraw() is called again and again by the system.
*/
#define MAX_PLAYERS 15
char player_Names[MAX_PLAYERS][50];
int player_Scores[MAX_PLAYERS];
int players_num = 0;
int score=0;
int currentlevel=1;
bool is_paused = false;
bool pause_game = false;
bool instructions = false;
int lives=3;
int ball_x=100, ball_y=100;
int dx = 20, dy = 18;
int ball_radius = 15;
int paddle_x=0,paddle_y=0,paddle_width=100,paddle_height=20;
bool gameover=false;
bool gamewon=false;
bool MENU=true;
bool settings = false;
bool waittoresume=false;
bool hoverPlay = false;
bool hoverSettings = false;
bool hoverInstructions = false;
bool credit = false;
bool nextlevel=false;
int music = -1;
bool music_on = true;
bool player_name = false;
bool leaderboard = false;
char PlayerName[200];
int namelen = 0;
bool type_name = false;
bool score_saved = false;
int musicx=750,musicy=550,musicsize=27;
int poweruptimer[10]= {0};
bool activepowerup[10]= {false};
char slowball[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\slowball.bmp";
char fastball[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\fastball.bmp";
char fireball[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\fireball.png";
char paddleinc[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\incpaddle.png";
char exlife[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\life.bmp";
char paddledec[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\shrink paddle.png";
char exscore[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\extrascore.png";
char miniball[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\miniball.png";
char brick1[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\brick.jpg";
char brick2[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\brick2.png";
char brick3[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\brick3.png";
char unbreak[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\unbreakablebrick.png";
char steel1[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\steelbrick1.jpg";
char steel2[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\steelbrick2.jpg";
char fire[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\brickred.png";
//char paddle[]="E:\\game\\Modern-iGraphics-main\\assets\\images\\paddle.png";
void SaveScore();
void definebricks();
void deac_power();

struct brickStructure
{
    int x;
    int y;
    //int red=0,green=0,blue=0;
    int dx=100;
    int dy=20;
    bool show=true;
    bool steel=false;
    bool unbreakable=false;
    bool fire=false;
    int hitCount=1;
    int colorvar;
};
#define totalbricks 49
#define MAX_POWERUPS 10
bool gamestate=false;
struct brickStructure bricks[totalbricks];
typedef enum {NONE,SLOW_BALL,FAST_BALL,PADDLE_EXPAND,EXTRA_LIFE,FIRE_BALL, MINI_BALL, PADDLE_SHRINK, EXTRA_SCORE} PowerUpType;
typedef struct
{
    int x,y;
    int dy;
    PowerUpType type;
    bool active;
} PowerUp;
PowerUp powerUps[MAX_POWERUPS];

void reset()
{
    ball_x=100, ball_y=100;
    dx = 20, dy = 18;
    score=0;
    lives=3;
    currentlevel=1;
    gameover=false;
    gamewon=false;
    waittoresume=false;
    score_saved=false;
    deac_power();
    for(int i=0; i<10; i++)
    {
        poweruptimer[i]=0;
        activepowerup[i]=false;
    }
    for(int i=0; i<MAX_POWERUPS; i++)
    {
        powerUps[i].active=false;
    }
    definebricks();
    iResumeTimer(0);

}

void iDraw()
{
    iClear();
    if(MENU)
    {
        iShowImage(0, 0,"E:\\game\\Modern-iGraphics-main\\assets\\images\\menu2.jpg");
        iSetColor(255,255,255);
        iShowImage(50, 550,"E:\\game\\Modern-iGraphics-main\\assets\\images\\load.png");
        iShowImage(350, 250, "E:\\game\\Modern-iGraphics-main\\assets\\images\\play.jpg");
        iShowImage(350, 200,"E:\\game\\Modern-iGraphics-main\\assets\\images\\settings.jpg");
        iShowImage(350, 150,"E:\\game\\Modern-iGraphics-main\\assets\\images\\instr.jpg");
        iShowImage(350, 100,"E:\\game\\Modern-iGraphics-main\\assets\\images\\credit.jpg" );
        iShowImage(350, 50,"E:\\game\\Modern-iGraphics-main\\assets\\images\\exit.jpg" );
        iShowImage(350, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\LB1.jpg");
        if(is_paused && pause_game)
        {
            iShowImage(600, 550, "E:\\game\\Modern-iGraphics-main\\assets\\images\\resume_game (1).png");

        }
        //iShowImage(650, 50, "E:\\game\\Modern-iGraphics-main\\assets\\images\\menu.jpg");
        // iFilledRectangle(700, 550, 100, 50);
        return;
    }
    if (gameover)
    {
        iSetColor(255, 0, 0);
        //iText(300, 50, "Game Over!Press s to restart and q to quit",GLUT_BITMAP_HELVETICA_18);

        iShowImage(0, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\gameover.png");
        iShowImage(650, 50, "E:\\game\\Modern-iGraphics-main\\assets\\images\\menu.jpg");
        char Score[50];
        sprintf(Score,"Your Score: %d",score);
        iSetColor(255,255,255);
        iText(300,50,Score, GLUT_BITMAP_TIMES_ROMAN_24);
        return;
    }

    if(player_name)
    {
        iShowImage(0, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\name2.jpg");
        iSetColor(255, 255, 255);
        iRectangle(350, 250, 300, 40);
        iText(100, 260, "ENTER YOUR NAME:", GLUT_BITMAP_TIMES_ROMAN_24);
        if(type_name)
        {
            iText(370, 260, PlayerName, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else
        {
            iText(370, 260, PlayerName, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iText(700, 50, "DONE", GLUT_BITMAP_TIMES_ROMAN_24);

        return;
    }

    if(instructions)
    {
        iShowImage(0, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\instructions3.jpg");

        return;
    }

    if(leaderboard)
    {
        iShowImage(0, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\LB2.bmp");
        //for(int i = 0; i<players_num; i++)
        //{
        //char s[100];
        // sprintf(s, "%s                                                          %d", player_Names[i], player_Scores[i]);

        //  iSetColor(255, 255, 255);
        //  iText(160, 460-i*30, s, GLUT_BITMAP_TIMES_ROMAN_24);
        //}
        for (int i=0; i<players_num; i++)
        {
            int y=460- i*30;

            iSetColor(255,255, 255);
            iText(160,y,player_Names[i],GLUT_BITMAP_TIMES_ROMAN_24);

            int Length=strlen(player_Names[i]);
            int textWidth=Length*9;
            char score[10];
            sprintf(score, "%d", player_Scores[i]);
            iText(160 + 400,y,score,GLUT_BITMAP_TIMES_ROMAN_24);
        }
        return;
    }

    if(credit)
    {
        iShowImage(0, 0,"E:\\game\\Modern-iGraphics-main\\assets\\images\\creditbg.jpg");
        return;
    }
    if(settings)
    {
        iShowImage(0, 0, "E:\\game\\Modern-iGraphics-main\\assets\\images\\settings1.jpg");
        iCircle(230, 435, 12, 150);
        iCircle(230, 370, 12, 100);
        iCircle(240, 190, 12, 100);
        iCircle(240, 130, 12, 100);
        //if(iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", true,60)){
        if(music_on)
        {
            iFilledCircle(230, 435, 8, 100);
        }
        else if(!music_on)
        {
            iFilledCircle(230, 370, 8, 100);
        }

        if(is_paused)
        {
            iFilledCircle(240, 130, 8, 100);
        }
        else if(!is_paused)
        {
            iFilledCircle(240, 190, 8, 100);
        }

        return;
    }

    if(gamestate)
    {
        iShowImage(0,0,"E:\\game\\Modern-iGraphics-main\\assets\\images\\bg2.jpg");
        if(music_on )
        {
            iShowImage(750, 550, "E:\\game\\Modern-iGraphics-main\\assets\\images\\sound_on.png");
            iResumeSound(music);
        }
        else if(!music_on)
        {
            iShowImage(750, 550, "E:\\game\\Modern-iGraphics-main\\assets\\images\\mute.png");
            iPauseSound(music);
        }
        //iFilledRectangle(750, 550, 33, 33);

        /*for(int i=0; i<totalbricks; i++)
        {
            if(bricks[i].show)
            {
                iSetColor(bricks[i].red,bricks[i].green,bricks[i].blue);
                iFilledRectangle(bricks[i].x,bricks[i].y,bricks[i].dx,bricks[i].dy);
            }
            if(bricks[i].fire && bricks[i].show){
                 iSetColor(0,0,0);
            iRectangle(bricks[i].x-1,bricks[i].y-1,bricks[i].dx+2,bricks[i].dy+2);
            }
        }*/
        for(int i=0; i<totalbricks; i++)
        {
            if(!bricks[i].show) continue;
            if(bricks[i].unbreakable)
            {
                iShowImage(bricks[i].x,bricks[i].y,unbreak);
            }
            else if(bricks[i].steel)
            {
                if(bricks[i].hitCount>=2)
                    iShowImage(bricks[i].x,bricks[i].y,steel1);
                else iShowImage(bricks[i].x,bricks[i].y,steel2);
            }
            else if(bricks[i].fire)
            {
                iShowImage(bricks[i].x,bricks[i].y,fire);
            }
            else
            {
                switch(bricks[i].colorvar)
                {
                case 0:
                    iShowImage(bricks[i].x,bricks[i].y,brick1);
                    break;
                case 1:
                    iShowImage(bricks[i].x,bricks[i].y,brick2);
                    break;
                case 2:
                    iShowImage(bricks[i].x,bricks[i].y,brick3);
                    break;
                }
            }
        }

        for(int i=0; i<MAX_POWERUPS; i++)
        {
            //if(!pause_game){
            if (powerUps[i].active)
            {
                switch (powerUps[i].type)
                {
                case SLOW_BALL:
                    iShowImage(powerUps[i].x,powerUps[i].y,slowball);
                    break;
                case FAST_BALL:
                    iShowImage(powerUps[i].x,powerUps[i].y,fastball);
                    break;
                case PADDLE_EXPAND:
                    iShowImage(powerUps[i].x,powerUps[i].y,paddleinc);
                    break;
                case EXTRA_LIFE:
                    iShowImage(powerUps[i].x,powerUps[i].y,exlife);
                    break;
                case FIRE_BALL:
                    iShowImage(powerUps[i].x,powerUps[i].y,fireball);
                    break;
                case MINI_BALL:
                    iShowImage(powerUps[i].x,powerUps[i].y,miniball);
                    break;
                case PADDLE_SHRINK:
                    iShowImage(powerUps[i].x,powerUps[i].y,paddledec);
                    break;
                case EXTRA_SCORE:
                    iShowImage(powerUps[i].x,powerUps[i].y,exscore);
                    break;

                }
            }
            // }
        }

        char scorest[50],livest[50];
        sprintf(scorest,"Score: %d",score);
        sprintf(livest,"Lives: %d",lives);
        iSetColor(255,255,255);
        iText(10,570,scorest,GLUT_BITMAP_HELVETICA_18);
        iText(500,570,livest,GLUT_BITMAP_HELVETICA_18);
        //iShowImage(750,550,"E:\\game\\Modern-iGraphics-main\\assets\\images\\mute.png");
        if(pause_game)
        {
            iShowImage(710, 552, "E:\\game\\Modern-iGraphics-main\\assets\\images\\pause.png");
            iShowImage(600, 552, "E:\\game\\Modern-iGraphics-main\\assets\\images\\backtomenu.jpg");
        }
        else
        {
            iShowImage(710, 552, "E:\\game\\Modern-iGraphics-main\\assets\\images\\resume.png");
        }

        if (waittoresume)
        {
            iSetColor(255, 0, 0);
            iText(250, 270, "Press 'r' to resume",GLUT_BITMAP_HELVETICA_18);
        }


        if(activepowerup[FIRE_BALL])
        {
            iSetColor(255,0,0);
        }
        else
        {
            iSetColor(145,50,168);
        }
        iFilledCircle(ball_x, ball_y, ball_radius);

        iSetColor(255,0,0);
        iFilledRectangle(paddle_x,paddle_y,paddle_width,paddle_height);
    }

    if(gamewon)
    {
        iShowImage(0,0,"E:\\game\\Modern-iGraphics-main\\assets\\images\\levelcom.jpg");
        char Score[50];
        sprintf(Score,"Your Score: %d",score);
        iSetColor(255,255,255);
        iText(200,250,Score,GLUT_BITMAP_HELVETICA_18);
        iText(150,200,"Press 's' to restart the game.",GLUT_BITMAP_HELVETICA_18);
        iShowImage(650, 50, "E:\\game\\Modern-iGraphics-main\\assets\\images\\menu.jpg");
        return;
    }


    if (nextlevel)
    {
        iShowImage(0,0,"E:\\game\\Modern-iGraphics-main\\assets\\images\\levelcom.jpg");
        char Score[50];
        sprintf(Score,"Your Score: %d",score);
        iSetColor(255,255,255);
        iText(200,250,Score, GLUT_BITMAP_HELVETICA_18);
        iFilledRectangle(300,180,200,40);
        iSetColor(0,0,0);
        iText(340,190,"Next Level",GLUT_BITMAP_HELVETICA_18);
        iShowImage(650, 50, "E:\\game\\Modern-iGraphics-main\\assets\\images\\menu.jpg");
        return;
    }


    if(music)
    {
        //iShowImage(750,550,"E:\\game\\Modern-iGraphics-main\\assets\\images\\volume.png");
    }
    else
    {
        //iShowImage(750,550,"E:\\game\\Modern-iGraphics-main\\assets\\images\\mute.png");
        //if(pause_game){
        //   iShowImage(710, 552, "E:\\game\\Modern-iGraphics-main\\assets\\images\\pause.png");
        // }
        // else{
        //   iShowImage(710, 552, "E:\\game\\Modern-iGraphics-main\\assets\\images\\resume.png");
        // }
    }
}

/*void sortLeaderboard()
{
    for (int i = 0; i < players_num - 1; i++)
    {
        for (int j = i + 1; j < players_num; j++)
        {
            if (player_Scores[i] < player_Scores[j])
            {

                int tempScore = player_Scores[i];
                player_Scores[i] = player_Scores[j];
                player_Scores[j] = tempScore;


                char tempName[50];
                strcpy(tempName, player_Names[i]);
                strcpy(player_Names[i], player_Names[j]);
                strcpy(player_Names[j], tempName);
            }
        }
    }
}

void show_scores()
{
    FILE *file;
    file = fopen("scores.txt", "r");
    if(file == NULL)
    {
        printf("Failed to open scores.txt\n");
        return;
    }

    players_num = 0;
    while(fscanf(file, "%s %d", player_Names[players_num], &player_Scores[players_num])== 2)
    {
        players_num++;
        if(players_num >= MAX_PLAYERS) break;
    }fclose(file);
    sortLeaderboard();

}

void SaveScore()
{
    FILE *fp;
    fp = fopen("scores.txt", "a");
    if(fp == NULL)
    {
        printf("Error saving score\n");
    }
    else
    {
        fprintf(fp, "%s %d\n", PlayerName, score);
        fclose(fp);
    }
}
void save_game()
{
    FILE *fp = fopen("save.txt", "w");
    if(fp == NULL) {
        printf("Error: Could not create save file\n");
        return;
    }

    // Save basic game state
    fprintf(fp, "%d %d %d\n", currentlevel, ball_x, ball_y);
    fprintf(fp, "%d %d %d %d %d %d\n", score, paddle_x, paddle_y, lives, dx, dy);
    fprintf(fp, "%d %d\n", paddle_width, ball_radius);
    fprintf(fp, "%d %d\n", (int)gameover, (int)waittoresume);

    for(int i = 0; i < 10; i++) {
        fprintf(fp, "%d %d\n", poweruptimer[i], activepowerup[i] ? 1 : 0);
    }


    int activeCount = 0;
    for(int i = 0; i < MAX_POWERUPS; i++) {
        if(powerUps[i].active) activeCount++;
    }
    fprintf(fp, "%d\n", activeCount);

    for(int i = 0; i < MAX_POWERUPS; i++) {
        if(powerUps[i].active) {
            fprintf(fp, "%d %d %d %d\n", powerUps[i].type, powerUps[i].x, powerUps[i].y, powerUps[i].dy);
        }
    }

    fprintf(fp, "%d\n", totalbricks);


    int broken_count = 0;
    for(int i = 0; i < totalbricks; i++) {
        if (!bricks[i].show) broken_count++;

        fprintf(fp, "%d %d %d %d %d %d %d %d %d %d\n",
                bricks[i].x, bricks[i].y, bricks[i].dx, bricks[i].dy,
                bricks[i].show ? 1 : 0, bricks[i].steel ? 1 : 0,
                bricks[i].unbreakable ? 1 : 0, bricks[i].fire ? 1 : 0,
                bricks[i].hitCount, bricks[i].colorvar);
    }

    fclose(fp);
    printf("Game saved! %d bricks broken, score: %d\n", broken_count, score);
}
void load_game()
{
    FILE *fp = fopen("save.txt", "r");
    if(fp == NULL) {
        printf("Error: Could not open save file\n");
        return;
    }


    fscanf(fp, "%d %d %d", &currentlevel, &ball_x, &ball_y);
    fscanf(fp, "%d %d %d %d %d %d", &score, &paddle_x, &paddle_y, &lives, &dx, &dy);
    fscanf(fp, "%d %d", &paddle_width, &ball_radius);

    int gameover_int, waittoresume_int;
    fscanf(fp, "%d %d", &gameover_int, &waittoresume_int);
    gameover = (gameover_int == 1);
    waittoresume = (waittoresume_int == 1);

    // Load power-up timers and active states
    for(int i = 0; i < 10; i++) {
        int timer, active;
        fscanf(fp, "%d %d", &timer, &active);
        poweruptimer[i] = timer;
        activepowerup[i] = (active == 1);
    }

    int activeCount;
    fscanf(fp, "%d", &activeCount);

    for (int i = 0; i < MAX_POWERUPS; i++) {
        powerUps[i].active = false;
    }

    for(int i = 0; i < activeCount; i++) {
        int type, x, y, dy_val;
        fscanf(fp, "%d %d %d %d", &type, &x, &y, &dy_val);
        if(i < MAX_POWERUPS) {
            powerUps[i].type = (PowerUpType)type;
            powerUps[i].x = x;
            powerUps[i].y = y;
            powerUps[i].dy = dy_val;
            powerUps[i].active = true;
        }
    }

    int saved_totalbricks;
    fscanf(fp, "%d", &saved_totalbricks);

    for(int i = 0; i < totalbricks && i < saved_totalbricks; i++) {
        int show, steel, unbreakable, fire;
        fscanf(fp, "%d %d %d %d %d %d %d %d %d %d",
               &bricks[i].x, &bricks[i].y, &bricks[i].dx, &bricks[i].dy,
               &show, &steel, &unbreakable, &fire,
               &bricks[i].hitCount, &bricks[i].colorvar);

        bricks[i].show = (show == 1);
        bricks[i].steel = (steel == 1);
        bricks[i].unbreakable = (unbreakable == 1);
        bricks[i].fire = (fire == 1);
    }

    fclose(fp);

    MENU = false;
    gamestate = true;
    gamewon = false;
    player_name = false;
    settings = false;
    instructions = false;
    credit = false;
    leaderboard = false;

    if (!waittoresume && !pause_game) {
        iResumeTimer(0);
    }
    printf("Game loaded with score: %d\n", score);
}*/

void sortLeaderboard()
{
    for (int i=0; i<players_num -1; i++)
    {
        for (int j=i+1; j<players_num; j++)
        {
            if (player_Scores[i]<player_Scores[j])
            {
                int tempScore=player_Scores[i];
                player_Scores[i] =player_Scores[j];
                player_Scores[j]= tempScore;
                char tempName[50];
                strcpy(tempName,player_Names[i]);
                strcpy(player_Names[i], player_Names[j]);
                strcpy(player_Names[j], tempName);
            }
        }
    }
}


void load_game()
{
    FILE *fp=fopen("save.txt", "r");
    if(fp==NULL)
    {
        printf("Error: Could not open save file\n");
        return;
    }
    if(fgets(PlayerName, sizeof(PlayerName), fp)==NULL)
    {
        printf("Error reading player name\n");
        fclose(fp);
        return;
    }
    PlayerName[strcspn(PlayerName, "\n")] = 0;
    namelen= strlen(PlayerName);
    if(fscanf(fp, "%d %d %d",&currentlevel,&ball_x,&ball_y)!=3)
    {
        printf("Error reading basic game state\n");
        fclose(fp);
        return;
    }

    if(fscanf(fp,"%d %d %d %d %d %d",&score,&paddle_x,&paddle_y,&lives,&dx,&dy)!=6)
    {
        printf("Error reading game variables\n");
        fclose(fp);
        return;
    }

    if(fscanf(fp,"%d %d",&paddle_width,&ball_radius)!=2)
    {
        printf("Error reading paddle/ball dimensions\n");
        fclose(fp);
        return;
    }

    int gameover_int,waittoresume_int;
    if(fscanf(fp, "%d %d", &gameover_int, &waittoresume_int) != 2)
    {
        printf("Error reading game flags\n");
        fclose(fp);
        return;
    }
    gameover=(gameover_int==1);
    waittoresume=(waittoresume_int==1);
    for(int i=0; i<10; i++)
    {
        int timer,active;
        if(fscanf(fp,"%d %d", &timer,&active)!= 2)
        {
            printf("Error reading powerup %d\n", i);
            fclose(fp);
            return;
        }
        poweruptimer[i]=timer;
        activepowerup[i]= (active==1);
    }
    for (int i=0; i< MAX_POWERUPS; i++)
    {
        powerUps[i].active=false;
    }

    int activeCount;
    if(fscanf(fp,"%d",&activeCount)!=1)
    {
        printf("Error reading active powerup count\n");
        fclose(fp);
        return;
    }

    for(int i=0; i<activeCount && i<MAX_POWERUPS; i++)
    {
        int type, x, y, dy_val;
        if(fscanf(fp, "%d %d %d %d", &type, &x, &y, &dy_val) != 4)
        {
            printf("Error reading powerup %d data\n", i);
            break;
        }
        powerUps[i].type = (PowerUpType)type;
        powerUps[i].x = x;
        powerUps[i].y = y;
        powerUps[i].dy = dy_val;
        powerUps[i].active = true;
    }

    int saved_totalbricks;
    if(fscanf(fp, "%d", &saved_totalbricks) != 1)
    {
        printf("Error reading brick count\n");
        fclose(fp);
        return;
    }

    for(int i = 0; i < totalbricks && i < saved_totalbricks; i++)
    {
        int show, steel, unbreakable, fire;
        if(fscanf(fp, "%d %d %d %d %d %d %d %d %d %d",
                  &bricks[i].x, &bricks[i].y, &bricks[i].dx, &bricks[i].dy,
                  &show, &steel, &unbreakable, &fire,
                  &bricks[i].hitCount, &bricks[i].colorvar) != 10)
        {
            printf("Error reading brick %d data\n", i);
            break;
        }

        bricks[i].show = (show == 1);
        bricks[i].steel = (steel == 1);
        bricks[i].unbreakable = (unbreakable == 1);
        bricks[i].fire = (fire == 1);
    }

    fclose(fp);
    MENU = false;
    gamestate = true;
    gamewon = false;
    gameover = false;
    player_name = false;
    settings = false;
    instructions = false;
    credit = false;
    leaderboard = false;
    nextlevel = false;

    if (!waittoresume && !pause_game)
    {
        iResumeTimer(0);
    }
    else
    {
        iPauseTimer(0);
    }

    printf("Game loaded successfully! Score: %d, Level: %d, Lives: %d\n", score, currentlevel, lives);
}

void save_game()
{
    FILE *fp = fopen("save.txt", "w");
    if(fp == NULL)
    {
        printf("Error: Could not create save file\n");
        return;
    }
    fprintf(fp,"%s\n",PlayerName);
    fprintf(fp, "%d %d %d\n", currentlevel, ball_x, ball_y);
    fprintf(fp, "%d %d %d %d %d %d\n", score, paddle_x, paddle_y, lives, dx, dy);
    fprintf(fp, "%d %d\n", paddle_width, ball_radius);
    fprintf(fp, "%d %d\n", (int)gameover, (int)waittoresume);


    for(int i = 0; i < 10; i++)
    {
        fprintf(fp, "%d %d\n", poweruptimer[i], activepowerup[i] ? 1 : 0);
    }


    int activeCount = 0;
    for(int i = 0; i < MAX_POWERUPS; i++)
    {
        if(powerUps[i].active) activeCount++;
    }
    fprintf(fp, "%d\n", activeCount);

    for(int i = 0; i < MAX_POWERUPS; i++)
    {
        if(powerUps[i].active)
        {
            fprintf(fp, "%d %d %d %d\n", (int)powerUps[i].type, powerUps[i].x, powerUps[i].y, powerUps[i].dy);
        }
    }


    fprintf(fp, "%d\n", totalbricks);
    for(int i = 0; i < totalbricks; i++)
    {
        fprintf(fp, "%d %d %d %d %d %d %d %d %d %d\n",
                bricks[i].x, bricks[i].y, bricks[i].dx, bricks[i].dy,
                bricks[i].show ? 1 : 0, bricks[i].steel ? 1 : 0,
                bricks[i].unbreakable ? 1 : 0, bricks[i].fire ? 1 : 0,
                bricks[i].hitCount, bricks[i].colorvar);
    }

    fclose(fp);
    printf("Game saved successfully!\n");
}


void show_scores()
{
    FILE *file = fopen("scores.txt", "r");
    if(file == NULL)
    {
        printf("No scores file found or failed to open scores.txt\n");
        players_num = 0;
        return;
    }

    players_num = 0;
    char line[256];

    while(fgets(line, sizeof(line), file) && players_num < MAX_PLAYERS)
    {

        line[strcspn(line, "\n")] = 0;

        char name[50];
        int score_val;
        if(sscanf(line, "%49s %d", name, &score_val) == 2)
        {
            strcpy(player_Names[players_num], name);
            player_Scores[players_num] = score_val;
            players_num++;
        }
    }

    fclose(file);
    sortLeaderboard();
    printf("Loaded %d scores from leaderboard\n", players_num);
}
void SaveScore()
{

    if(strlen(PlayerName)==0)
    {
        printf("Cannot save score: No player name entered\n");
        return;
    }
    FILE *fp=fopen("scores.txt", "a");
    if(fp==NULL)
    {
        printf("Error: Could not open scores file for writing\n");
        return;
    }

    fprintf(fp, "%s %d\n", PlayerName, score);
    fclose(fp);
    printf("Score saved: %s - %d\n", PlayerName, score);
}



void iMouseMove(int mx, int my)
{
    if (!gameover && !MENU && !player_name && !leaderboard && !credit)
    {
        paddle_x=mx-paddle_width/2;
        if (paddle_x<0) paddle_x=0;
        if (paddle_x+paddle_width >800) paddle_x=800-paddle_width;
    }
}

void Music()
{
    if(music_on)
    {
        iPauseSound(music);
        music_on = false;
    }
    else
    {
        iResumeSound(music);
        music_on=true;
    }
}

void iMouseDrag(int mx, int my)
{
    // place your codes here
}

void iMouse(int button, int state, int mx, int my)
{
    if(nextlevel&&mx>=300&&mx<=500&&my>=180&&my<=220)
    {
        {
            if (currentlevel==1)
            {
                currentlevel=2;
            }
            else if(currentlevel==2)
            {
                currentlevel=3;
            }
            deac_power();
            definebricks();
            ball_x= paddle_x+paddle_width/2;
            ball_y=paddle_y+paddle_height+ball_radius+5;
            waittoresume=true;
            nextlevel=false;
            gamewon = false;
            gameover = false;
            iPauseTimer(0);
        }
    }
    if(mx>=musicx && mx<=musicx+musicsize && my>=musicy && my<=musicy+musicsize)
    {
        music=!music;
        if(music)
        {
            iResumeSound(music);
        }
        else
        {
            iPauseSound(music);
        }
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(music_on)
        {
            if(settings)
            {
                if(mx >= 218 && mx <= 242 && my >= 423 && my <= 447)
                {
                    //iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", true);
                    //iResumeSound();

                    Music();
                }
                //}
                // if(music_on){

            }
            if(gamestate)
            {
                if(mx >= 750 && mx <= 782 && my >= 550 && my <= 582)
                {
                    Music();
                }
            }
        }
        else if(!music_on)
        {
            if(settings)
            {
                if(mx >= 218 && mx <= 242 && my >= 358 && my <= 382)
                {
                    //iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", false);
                    //iPauseSound();

                    Music();
                }
            }
            if(gamestate)
            {
                if(mx >= 750 && mx <= 782 && my >= 550 && my <= 582)
                {
                    Music();
                }
            }
        }
        if(MENU)
        {

            if(mx >= 50 && mx <= 170 && my >= 550 && my <= 580)
            {
                FILE *test_file = fopen("save.txt", "r");
                if(test_file != NULL)
                {
                    fclose(test_file);
                    load_game();

                }
                else
                {
                    printf("No save file found!\n");

                }
            }
            else  if(mx >= 350 && mx <= 450 && my >= 250 && my <= 283)
            {
                //reset();
                //gameover = false;
                MENU = false;
                player_name = true;
                //iResumeTimer(0);
            }
            else if(mx >= 350 && mx <= 450 && my >= 50 && my <= 83)
            {
                exit(0);
            }
            else if(mx >= 350 && mx <= 450 && my >= 100 && my <= 133)
            {
                credit = true;
                MENU = false;

                iPauseTimer(0);
            }
            else if(mx >= 350 && mx <= 450 && my >= 0 && my <= 33)
            {
                show_scores();
                leaderboard = true;
                MENU = false;
                iPauseTimer(0);
            }
            else if(mx >= 350 && mx <= 450 && my >= 200 && my <= 233)
            {
                MENU = false;
                settings = true;
            }
            else if(mx >= 350 && mx <= 450 && my >= 150 && my <= 183)
            {
                MENU = false;
                instructions = true;

            }
        }
        if(credit)
        {
            if(mx >= 650 && mx <= 800 && my >= 50 && my<= 100)
            {
                credit = false;
                MENU = true;
            }
        }
        if(settings)
        {
            //if(!music_on){
            if(mx >= 218 && mx <= 242 && my >= 423 && my <= 447)
            {
                //iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", true);
                //iResumeSound();

                Music();
            }
            //}
            // if(music_on){
            if(mx >= 218 && mx <= 242 && my >= 358 && my <= 382)
            {
                //iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", false);
                //iPauseSound();

                Music();
            }
            //}
            if(mx >= 650 && mx <= 800 && my >= 20 && my <= 70)
            {
                settings = false;
                MENU = true;
            }
            if(mx >= 228 && mx <= 252 && my >= 178 && my <= 202)
            {
                if(is_paused)
                {
                    is_paused = false;
                    pause_game = false;
                    reset();
                }
            }
        }

        if(leaderboard)
        {
            if(mx >= 675  && mx <= 775 && my >= 35 && my <= 85)
            {
                leaderboard = false;
                MENU = true;
                //sortLeaderboard();
            }
        }

        if(instructions)
        {
            if(mx >= 670 && mx <= 770 && my >= 20 && my <= 53)
            {
                MENU = true;
                instructions = false;
            }
        }

        if(gamewon)
        {
            if(mx >= 650 && mx <= 742 && my >= 50 && my <= 83)
            {
                gameover = false;
                MENU = true;
            }
        }

        if(gameover)
        {
            if(mx >= 650 && mx <= 742 && my >= 50 && my <= 83)
            {
                gameover = false;
                MENU = true;
            }
        }
        if(nextlevel)
        {
            if(mx >= 650 && mx <= 742 && my >= 50 && my <= 83)
            {
                gameover = false;
                MENU = true;
                gamestate = false;
            }
        }

        if(player_name)
        {
            if(mx >= 350 && mx <= 650 && my >= 250 && my <= 290)
            {
                type_name = true;
            }
            else
            {
                type_name = false;
            }
            if(mx >= 700 && mx <= 800 && my >= 50 && my <= 100)
            {
                reset();
                gameover=false;
                gamestate=true;
                iResumeTimer(0);
                player_name=false;
            }
        }
        if(gamestate)
        {
            if(!pause_game)
            {
                if(mx >= 710 && mx <= 740  && my >= 552 && my <= 582)
                {
                    pause_game = true;
                }

                // place your codes here

            }
            else
            {
                if(mx >= 710 && mx <= 740  && my >= 552 && my <= 582)
                {
                    pause_game = false;
                }
                else if(mx >= 600 && mx <= 700 && my >= 552 && my <= 582)
                {
                    save_game();
                    MENU = true;
                    is_paused = true;
                    gamestate=false;
                    // if(is_paused){


                    // }
                }
            }
            //if(!music_on){
            if(mx >= 750 && mx <= 782 && my >= 550 && my <= 582)
            {
                Music();
                //}
            }
            //else if(music_on){
            if(mx >= 750 && mx <= 782 && my >= 550 && my <= 582)
            {
                Music();
            }
            //}
        }
        else if(MENU)
        {
            if(mx >= 600 && mx <= 750 && my >= 550 && my <= 583)
            {
                MENU = false;
                gamestate = true;
            }
        }
    }

    //if(mx >= 625 && mx <= 725 && my >= 40 && my <= 80){
    // reset();
    //  gameover = false;
    // iResumeTimer(0);
    //  player_name = false;
    //  }
    // place your codes here

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
    }

}

void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}
void iKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case 'p':
        if (!gameover && !MENU && !player_name && !leaderboard && !credit)
        {
            save_game();
            iPauseTimer(0);
        }
        break;
    case 'r':
        if (!gameover && !MENU && waittoresume)
        {
            waittoresume=false;
            iResumeTimer(0);
        }
        break;
    case 's':
        if(gameover || MENU || gamewon)
        {
            reset();
            gameover = false;
            gamewon=false;
            MENU = false;
            iResumeTimer(0);
        }
        break;
    case 'q':
        if(!player_name)
        {
            save_game();
            exit(0);
        }
        break;
    case 'n':
        if(nextlevel)
        {
            if (currentlevel==1)
            {
                currentlevel=2;
            }
            else if(currentlevel==2)
            {
                currentlevel=3;
            }
            deac_power();
            definebricks();
            ball_x=paddle_x + paddle_width/2;
            ball_y=paddle_y+paddle_height+ball_radius + 5;
            waittoresume=true;
            nextlevel=false;
            iPauseTimer(0);
        }
        break;
    default:
        break;
    }
    if(type_name && state == 0)
    {
        if(key == '\r')
        {
            type_name = false;
        }
        else if(key == '\b')
        {
            if(namelen > 0)
            {
                namelen--;
                PlayerName[namelen] = '\0';
            }
        }
        else if(namelen<99 && key>= 32 && key <= 126)
        {
            PlayerName[namelen++]= key;
            PlayerName[namelen] ='\0';
        }
    }
}

void iSpecialKeyboard(unsigned char key, int state)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (!gameover && !MENU && !player_name && !leaderboard && !credit)
        {
            paddle_x -= 20;
            if (paddle_x < 0) paddle_x = 0;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (!gameover && !MENU && !player_name && !leaderboard && !credit)
        {
            paddle_x += 20;
            if (paddle_x + paddle_width > 800) paddle_x = 800 - paddle_width;
        }
        break;
    default:
        break;
    }
}
void destroybricks(int idx)
{
    int firex=bricks[idx].x;
    int firey=bricks[idx].y;
    for(int i=0; i<totalbricks; i++)
    {
        if(!bricks[i].show||bricks[i].unbreakable) continue;
        int brickx=bricks[i].x;
        int bricky=bricks[i].y;
        bool isnear=false;
        if(abs(brickx-firex)<=100&&abs(bricky-firey)<=20)
            isnear=true;
        if (isnear)
        {
            bricks[i].show = false;
            score += 10;
            if(bricks[i].fire)
                destroybricks(i);
        }
    }
}
void destroyRow(int idx)
{
    int r=(450-bricks[idx].y)/ 20;
    for(int i =0; i<totalbricks; i++)
    {
        if(!bricks[i].show||bricks[i].unbreakable) continue;
        int br=(450-bricks[i].y)/20;
        if(br==r)
        {
            bricks[i].show = false;
            score += 15;
        }
    }
}
int breakablegone()
{
    for(int i=0; i<totalbricks; i++)
    {
        if(bricks[i].show && !bricks[i].unbreakable)
        {
            return 0;
        }
    }
    return 1;
}

void ballChange()
{
    if(gameover||gamewon) return;
    if(!pause_game)
    {
        ball_x += dx;
        ball_y += dy;
        if (ball_x + ball_radius > iScreenWidth || ball_x - ball_radius < 0)
        {
            if (ball_x + ball_radius > iScreenWidth)
                ball_x = iScreenWidth - ball_radius;
            else
                ball_x = ball_radius;
            dx = -dx;
        }
        for (int i = 0; i < totalbricks; i++)
        {
            if (bricks[i].show)
            {
                int bx = bricks[i].x;
                int by = bricks[i].y;
                int bw = bricks[i].dx;
                int bh = bricks[i].dy;

                if (ball_x + ball_radius > bx && ball_x - ball_radius < bx + bw &&
                        ball_y + ball_radius > by && ball_y - ball_radius < by + bh)
                {
                    if(bricks[i].unbreakable)
                    {
                        dy=-dy;
                        if(dy>0)ball_y=by+bh+ball_radius+1;
                        else ball_y=by-ball_radius-1;
                        break;
                    }
                    bricks[i].hitCount--;
                    iPlaySound("E:\\game\\Modern-iGraphics-main\\assets\\sounds\\sounds_message-incoming-132126.wav",false,60);
                    if (bricks[i].steel && bricks[i].hitCount==1)
                    {
                        if(bricks[i].unbreakable) continue;
                        score+=5;
                    }

                    if (bricks[i].hitCount<=0)
                    {
                        bool ballonfire=activepowerup[FIRE_BALL];
                        if(bricks[i].fire)
                        {
                            destroyRow(i);
                        }
                        else if(activepowerup[FIRE_BALL])
                        {
                            destroybricks(i);
                        }
                        else
                        {
                            bricks[i].show=false;
                            if(bricks[i].steel)score+=10;
                            else score+=10;
                        }
                        if (rand()%5==0)
                        {
                            for(int j=0; j<MAX_POWERUPS; j++)
                            {
                                if(!powerUps[j].active)
                                {
                                    powerUps[j].x=bricks[i].x +bricks[i].dx/2;
                                    powerUps[j].y=bricks[i].y;
                                    powerUps[j].dy=-5;
                                    powerUps[j].type=(PowerUpType)(rand()%8+ 1);
                                    powerUps[j].active=true;
                                    break;
                                }
                            }
                        }
                    }
                    dy*=-1;

                    break;
                }
            }
        }

        if (ball_y + ball_radius > iScreenHeight)
        {
            ball_y = iScreenHeight - ball_radius;
            dy = -dy;
        }
        if(ball_y-ball_radius<=paddle_y+paddle_height&&ball_y-ball_radius>=paddle_y&&ball_x>=paddle_x&&ball_x<=paddle_x+paddle_width&&dy<0)
        {
            dy=-dy;
        }
        if(ball_y<0)
        {
            lives--;
            if(lives>0)
            {
                waittoresume=true;
                iPauseTimer(0);
                ball_x=paddle_x+paddle_width/2;
                ball_y = paddle_y+paddle_height+ball_radius+5;
                dy = abs(dy);
            }
            else
            {
                gameover=true;
                if (!score_saved)
                {
                    SaveScore();
                    score_saved = true;
                }
                iPauseTimer(0);
            }
        }
        for (int i=0; i<MAX_POWERUPS; i++)
        {
            if (powerUps[i].active)
            {
                powerUps[i].y+=powerUps[i].dy;
                if (powerUps[i].y<=paddle_y+paddle_height &&powerUps[i].x>=paddle_x && powerUps[i].x <= paddle_x+paddle_width)
                {
                    switch (powerUps[i].type)
                    {
                    case SLOW_BALL:
                        dx /= 2;
                        dy /= 2;
                        poweruptimer[SLOW_BALL]=0;
                        activepowerup[SLOW_BALL]=true;
                        break;
                    case FAST_BALL:
                        dx *= 1.2;
                        dy *= 1.2;
                        poweruptimer[FAST_BALL]=0;
                        activepowerup[FAST_BALL]=true;
                        break;
                    case PADDLE_EXPAND:
                        paddle_width += 45;
                        poweruptimer[PADDLE_EXPAND]=0;
                        activepowerup[PADDLE_EXPAND]=true;
                        break;
                    case PADDLE_SHRINK:
                        paddle_width -= 10;
                        poweruptimer[PADDLE_SHRINK]=0;
                        activepowerup[PADDLE_SHRINK]=true;
                        break;
                    case EXTRA_LIFE:
                        if(lives<4) lives++;
                        break;
                    case EXTRA_SCORE:
                        score+=30;
                        break;
                    case MINI_BALL:
                        ball_radius=max(5,ball_radius-5);
                        poweruptimer[MINI_BALL]=0;
                        activepowerup[MINI_BALL]=true;
                        break;
                    case FIRE_BALL:
                        for(int k=0; k<totalbricks; k++)
                        {
                            if (bricks[k].show && bricks[k].steel)
                            {
                                bricks[k].hitCount=1;
                            }
                        }
                        poweruptimer[FIRE_BALL]=0;
                        activepowerup[FIRE_BALL]=true;
                        break;
                    default:
                        break;
                    }
                    powerUps[i].active = false;
                }
                if (powerUps[i].y < 0)
                {
                    powerUps[i].active = false;
                }
            }
        }

        bool allBroken=true;
        for(int i=0; i<totalbricks; i++)
        {
            if(bricks[i].show && !bricks[i].unbreakable)
            {
                allBroken=false;
                break;
            }
        }
        if(allBroken&&currentlevel==1)
        {
            nextlevel=true;
            iPauseTimer(0);
        }
        else if(allBroken&&currentlevel==2)
        {
            nextlevel=true;
            iPauseTimer(0);
        }
        else if(breakablegone()&&currentlevel==3)
        {
            gamewon=true;
            if (!score_saved)
            {
                SaveScore();
                score_saved = true;
            }
            iPauseTimer(0);
        }
    }
}

void randomizeBallPosition()
{
    ball_x = rand() % (iScreenWidth - 2 * ball_radius) + ball_radius;
    ball_y = rand() % (iScreenHeight - 2 * ball_radius) + ball_radius;
}

void definebricks()
{
    int sumx=50;
    int sumy=450;
    //int colors[4][3]={{30,130,76},{102,51,153},{184,134,11},{106,90,205}};
    for (int i=0; i<totalbricks; i++)
    {
        bricks[i].x = sumx;
        bricks[i].y = sumy;
        bricks[i].show = true;
        //bricks[i].unbreakable = false;
        //bricks[i].fire = false;
        // bricks[i].steel=false;
        bricks[i].hitCount=1;
        bricks[i].colorvar=i%3;
        int r=(450-sumy)/20;
        int c=(sumx-50)/100;

        if (currentlevel==1)
        {
            bricks[i].unbreakable = false;
            bricks[i].fire = false;
            bricks[i].steel=false;
            bricks[i].hitCount=1;

        }
        else if (currentlevel==2)
        {
            bricks[i].steel=(i%5==0);
            bricks[i].unbreakable = false;
            bricks[i].fire = false;
            bricks[i].hitCount=bricks[i].steel?2:1;
            /*if (bricks[i].steel)
            {
                bricks[i].red =128;
                bricks[i].green=128;
                bricks[i].blue=128;
            }
            else
            {
                int colorIdx=i%4;
                bricks[i].red =colors[colorIdx][0];
                bricks[i].green =colors[colorIdx][1];
                bricks[i].blue =colors[colorIdx][2];
            }*/
        }

        else if (currentlevel==3)
        {
            if ((r==0&&c==0)||(r==0&&c==6)||(r==6&&c==0)||(r==6&&c==6))
            {
                bricks[i].unbreakable = true;
                bricks[i].fire=false;
                bricks[i].steel=false;
                bricks[i].hitCount=10000;
            }

            /* else if (i % 9 == 0 || i % 13 == 0)
             {
                 bricks[i].unbreakable = false;
                 bricks[i].fire = false;//true;
                 bricks[i].steel = false;
                 bricks[i].red = 255;
                 bricks[i].green = 69;
                 bricks[i].blue = 0;
                 bricks[i].hitCount = 1;
             }*/
            else if(r==0||r==6)
            {
                bricks[i].unbreakable = false;
                bricks[i].fire = true;
                bricks[i].steel = false;
                bricks[i].hitCount = 1;
            }
            else if (i%6==0)
            {
                bricks[i].unbreakable = false;
                bricks[i].fire = false;
                bricks[i].steel = true;
                bricks[i].hitCount = 2;
            }
            else
            {
                bricks[i].unbreakable = false;
                bricks[i].fire = false;
                bricks[i].steel = false;
                bricks[i].hitCount = 1;
            }
        }
        sumx += 100;
        if (sumx + bricks[i].dx > 800)
        {
            sumx = 50;
            sumy -= 20;
        }
    }
}

void poweruplost()
{
    for(int i=0; i<10; i++)
    {
        if(activepowerup[i])
        {
            poweruptimer[i]++;
            if (poweruptimer[i]>=25)
            {
                activepowerup[i]=false;
                poweruptimer[i]=0;
                if(i==SLOW_BALL)
                {
                    dx*=2;
                    dy*=2;
                }
                else if(i==FAST_BALL)
                {
                    dx/=1.2;
                    dy/=1.2;
                }
                else if(i==PADDLE_EXPAND)
                {
                    paddle_width-=45;
                }
                else if(i==PADDLE_SHRINK)
                {
                    paddle_width+=10;
                }
                else if(i==MINI_BALL)
                {
                    ball_radius=15;
                }
                else if(i==FIRE_BALL)
                {
                    for(int j=0; j<totalbricks; j++)
                    {
                        if(bricks[j].steel&& bricks[j].show)
                            bricks[j].hitCount=2;
                    }
                }
            }
        }
    }
}

void deac_power()
{
    for(int i=0; i<10; i++)
    {
        activepowerup[i]=false;
        poweruptimer[i]=0;
    }
    for(int j=0; j<MAX_POWERUPS; j++)
    {
        powerUps[j].active=false;
    }
    ball_radius=15;
    paddle_width=100;
    dx=20;
    dy=18;
    lives=3;
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    reset();
    iSetTimer(75, ballChange);
    iSetTimer(1000,poweruplost);
    iInitializeSound();
    music = iPlaySound("E:/game/Modern-iGraphics-main/assets/sounds/bgm1.wav", true,60);
    iInitialize(800, 600, "DX Ball");
    return 0;
}




