#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
  #include <windows.h>
  #include <mmsystem.h>
  #include <tchar.h>
  #pragma comment(lib, "winmm.lib")
#endif

#define WIN_W 800
#define WIN_H 600
#define MAX_EGGS 100
#define MAX_SCORES 5
#define MAX_HENS 3
#define MAX_CLOUDS 5

typedef enum { MENU, GAME, INSTRUCTIONS, SCORE, GAME_OVER } GameState;
GameState currentState = MENU;

int score = 0;
int timeLeft = 60;
int gamePaused = 0;
int basketSpeed = 15;
int highScores[MAX_SCORES] = {100,80,50,30,20};
int lastSecondTick = 0;

typedef struct { float x,y,w,h; char label[24]; float r,g,b; } Button;
/* --- UPDATED Hen struct: kept original fields plus animation ones --- */
typedef struct {
    float x,y,w,h;
    float speed;
    int dir;
    /* new animation fields (only hen part changed) */
    float legAngle;   /* leg swing angle */
    int legDir;       /* leg swing direction +/-1 */
    float bobOffset;  /* vertical bob (for subtle body movement) */
    int colorIndex;   /* index to choose color theme (0..MAX_HENS-1) */
} Hen;

typedef struct { float x,y,radius; } Basket;
typedef enum { NORMAL, GOLDEN, POOP } EggType;
typedef struct { EggType type; float x,y,rx,ry,speed; int active; } Egg;
typedef struct { float x,y,speed; } Cloud;

Button menuButtons[5];
Basket basket;
Hen hens[MAX_HENS];
Egg eggs[MAX_EGGS];
Cloud clouds[MAX_CLOUDS];

// -------- Game Over UI state --------
char playerName[32] = "";
int  nameLen = 0;
int  nameFocused = 1;
int  goBtnHover = -1;   // -1 none, 0=RETRY, 1=QUIT, 2=MENU

// ---------- SOUND HELPERS ----------
// Using Windows system sound aliases so no external files are required.
// If not on Windows these functions are no-ops.
static void playLoopMusic(void) {
#ifdef _WIN32
    // Loop a system alias. System aliases are short tones; looping them approximates background audio.
    // Common aliases: "SystemAsterisk", "SystemExclamation", "SystemHand", "SystemQuestion", "SystemExit"
    PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_LOOP | SND_ASYNC);
#endif
}
static void stopMusic(void) {
#ifdef _WIN32
    PlaySound(NULL, NULL, 0);
#endif
}
static void sfxCatch(void) {
#ifdef _WIN32
    // brief positive chime
    PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC);
#endif
}
static void sfxMiss(void) {
#ifdef _WIN32
    // error / miss sound — noticeable system exclamation/hand
    PlaySound(TEXT("SystemExclamation"), NULL, SND_ALIAS | SND_ASYNC);
#endif
}
static void sfxGameOver(void) {
#ifdef _WIN32
    // game over tone
    PlaySound(TEXT("SystemHand"), NULL, SND_ALIAS | SND_ASYNC);
#endif
}

// ---------- Helpers ----------
static float randf(float a,float b){ return a+(b-a)*(rand()/(float)RAND_MAX); }
static int inRect(float px,float py,float x,float y,float w,float h){ return (px>=x && px<=x+w && py>=y && py<=y+h); }

static void pushHighScore(int s){
    for(int i=0;i<MAX_SCORES;i++){
        if(s>highScores[i]){
            for(int j=MAX_SCORES-1;j>i;j--) highScores[j]=highScores[j-1];
            highScores[i]=s; break;
        }
    }
}

// ---------- Drawing primitives ----------
void drawText(float x,float y,const char* text,void* font){
    glRasterPos2f(x,y);
    for(int i=0;text[i];i++) glutBitmapCharacter(font,text[i]);
}
void drawCircle(float cx,float cy,float r){
    glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
    int slices=48;
    for(int i=0;i<=slices;i++){ float t=2*M_PI*i/slices; glVertex2f(cx+r*cosf(t),cy+r*sinf(t)); }
    glEnd();
}
void drawEllipse(float cx,float cy,float rx,float ry){
    glBegin(GL_TRIANGLE_FAN); glVertex2f(cx,cy);
    int slices=48;
    for(int i=0;i<=slices;i++){ float t=2*M_PI*i/slices; glVertex2f(cx+rx*cosf(t),cy+ry*sinf(t)); }
    glEnd();
}
void drawRect(float x,float y,float w,float h){
    glBegin(GL_QUADS);
        glVertex2f(x,y); glVertex2f(x+w,y);
        glVertex2f(x+w,y+h); glVertex2f(x,y+h);
    glEnd();
}
void drawOutlined(float x,float y,float w,float h, float tr,float tg,float tb){
    glColor3f(tr,tg,tb);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,y); glVertex2f(x+w,y); glVertex2f(x+w,y+h); glVertex2f(x,y+h);
    glEnd();
}

// ---------- Pills & Buttons ----------
void drawPill(float x,float y,float w,float h, float r,
              float r1,float g1,float b1, float r2,float g2,float b2){
    glBegin(GL_QUADS);
        glColor3f(r1,g1,b1); glVertex2f(x+r, y);
        glColor3f(r2,g2,b2); glVertex2f(x+w-r, y);
        glColor3f(r2,g2,b2); glVertex2f(x+w-r, y+h);
        glColor3f(r1,g1,b1); glVertex2f(x+r, y+h);
    glEnd();
    int slices=36;
    glBegin(GL_TRIANGLE_FAN); // left cap
        glColor3f(r1,g1,b1); glVertex2f(x+r, y+h/2);
        for(int i=0;i<=slices;i++){ float t=M_PI/2 + (float)i/slices*M_PI;
            glVertex2f(x+r + r*cosf(t), y+h/2 + r*sinf(t)); }
    glEnd();
    glBegin(GL_TRIANGLE_FAN); // right cap
        glColor3f(r2,g2,b2); glVertex2f(x+w-r, y+h/2);
        for(int i=0;i<=slices;i++){ float t=-M_PI/2 + (float)i/slices*M_PI;
            glVertex2f(x+w-r + r*cosf(t), y+h/2 + r*sinf(t)); }
    glEnd();
}
void drawPillButton(Button *b){
    glColor3f(0,0,0); drawPill(b->x+4,b->y-6,b->w,b->h,b->h/2,0,0,0,0,0,0); // shadow
    if(strcmp(b->label,"PLAY")==0)            drawPill(b->x,b->y,b->w,b->h,b->h/2, 1.0f,0.2f,0.3f, 1.0f,0.9f,0.2f);
    else if(strcmp(b->label,"SETTINGS")==0)   drawPill(b->x,b->y,b->w,b->h,b->h/2, 1.0f,0.6f,0.0f, 1.0f,0.85f,0.25f);
    else if(strcmp(b->label,"EXIT")==0)       drawPill(b->x,b->y,b->w,b->h,b->h/2, 0.25f,0.8f,0.25f, 0.65f,1.0f,0.45f);
    else if(strcmp(b->label,"INSTRUCTIONS")==0) drawPill(b->x,b->y,b->w,b->h,b->h/2, 0.15f,0.45f,1.0f, 0.25f,0.75f,1.0f);
    else if(strcmp(b->label,"SCORE")==0)      drawPill(b->x,b->y,b->w,b->h,b->h/2, 0.95f,0.25f,0.25f, 1.0f,0.55f,0.55f);
    else                                      drawPill(b->x,b->y,b->w,b->h,b->h/2, b->r,b->g,b->b, b->r,b->g,b->b);
    glColor3f(1,1,1);
    float tx=b->x + (b->w/2 - (float)strlen(b->label)*9/2.0f);
    float ty=b->y + b->h/2 - 5;
    drawText(tx,ty,b->label,GLUT_BITMAP_HELVETICA_18);
}

// ---------- Background ----------
void drawCloud(float x,float y){
    glColor3f(1,1,1);
    drawCircle(x,y,20); drawCircle(x+15,y+5,25);
    drawCircle(x-20,y+5,22); drawCircle(x+30,y,18);
}
void drawGrass(float t){
    glColor3f(0.1f,0.7f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(0,0); glVertex2f(WIN_W,0);
        glColor3f(0.2f,0.8f,0.2f);
        glVertex2f(WIN_W,120); glVertex2f(0,120);
    glEnd();
    glColor3f(0.2f,0.8f,0.2f);
    glBegin(GL_LINES);
    for(int i=0;i<WIN_W;i+=10){
        float wave=sinf((i*0.05f)+t*0.005f)*5;
        glVertex2f(i,120); glVertex2f(i+wave,120+8+(i%30));
    }
    glEnd();
}
void drawFence(){
    glColor3f(0.6f,0.3f,0.1f);
    for(int i=0;i<WIN_W;i+=40){
        glBegin(GL_QUADS);
            glVertex2f(i,120); glVertex2f(i+10,120);
            glVertex2f(i+10,170); glVertex2f(i,170);
        glEnd();
    }
    glBegin(GL_QUADS);
        glVertex2f(0,150); glVertex2f(WIN_W,150);
        glVertex2f(WIN_W,160); glVertex2f(0,160);
    glEnd();
}
void drawBarn(){
    glColor3f(0.8f,0.1f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(80,120); glVertex2f(200,120);
        glVertex2f(200,220); glVertex2f(80,220);
    glEnd();
    glColor3f(0.6f,0,0);
    glBegin(GL_TRIANGLES);
        glVertex2f(70,220); glVertex2f(210,220); glVertex2f(140,270);
    glEnd();
    glColor3f(0.3f,0.15f,0.05f);
    glBegin(GL_QUADS);
        glVertex2f(120,120); glVertex2f(160,120);
        glVertex2f(160,170); glVertex2f(120,170);
    glEnd();
}
void drawTreeBranch(){
    glColor3f(0.4f,0.25f,0.1f);
    glBegin(GL_QUADS);
        glVertex2f(50,400); glVertex2f(WIN_W-50,400);
        glVertex2f(WIN_W-50,420); glVertex2f(50,420);
    glEnd();
}
void drawFarmBackground(){
    float t=(float)glutGet(GLUT_ELAPSED_TIME);
    glBegin(GL_QUADS);
        glColor3f(0.45f,0.95f,1.0f); glVertex2f(0,0);
        glColor3f(0.12f,0.65f,1.0f); glVertex2f(WIN_W,0);
        glColor3f(0.15f,0.55f,0.95f); glVertex2f(WIN_W,WIN_H);
        glColor3f(0.65f,0.95f,1.0f); glVertex2f(0,WIN_H);
    glEnd();
    for(int i=0;i<MAX_CLOUDS;i++){
        clouds[i].x+=clouds[i].speed;
        if(clouds[i].x>WIN_W+50) clouds[i].x=-50;
        drawCloud(clouds[i].x,clouds[i].y);
    }
    drawGrass(t); drawFence(); drawBarn(); drawTreeBranch();
}

// ---------- Game art ----------
/* -------------- Modified drawEgg --------------
   - NORMAL & GOLDEN: same as before (ellipse)
   - POOP: draw as a dark brown circle with radius = (max(rx,ry) / 3.0)
     This keeps gameplay logic unchanged (collision remains same),
     only visual changes so poop is small circular and dark brown.
*/
void drawEgg(Egg *e){
    if(!e->active) return;
    if(e->type==NORMAL) {
        glColor3f(1,1,1);
        drawEllipse(e->x,e->y,e->rx,e->ry);
    }
    else if(e->type==GOLDEN) {
        glColor3f(1.0f,0.85f,0.1f);
        drawEllipse(e->x,e->y,e->rx,e->ry);
    }
    else { // POOP - small dark brown circle (one third size)
        /* dark brown color */
        glColor3f(0.36f, 0.20f, 0.10f);
        float base = fmaxf(e->rx, e->ry); /* use larger radius as reference */
        float pr = base / 3.0f;           /* one third size visually */
        drawCircle(e->x, e->y, pr);
    }
}
void drawBasket(){
    glColor3f(0.5f,0.25f,0.05f); drawCircle(basket.x,basket.y,basket.radius);
    glColor3f(0.85f,0.55f,0.25f); drawCircle(basket.x,basket.y,basket.radius-8);
}
void drawMascotHen(){
    float cx=WIN_W/2.0f, cy=165.0f;
    glColor3f(0.99f,0.80f,0.30f); drawEllipse(cx,cy,75,22);
    glColor3f(0.55f,0.90f,0.60f); drawEllipse(cx,cy+18,60,17);
    glColor3f(0.30f,0.75f,0.95f); drawEllipse(cx,cy+34,46,13);
    glColor3f(0.96f,0.96f,0.96f); drawEllipse(cx,cy+48,34,18);
    glColor3f(1.00f,0.98f,0.98f); drawCircle(cx,cy+78,22);
    glColor3f(0.95f,0.25f,0.25f); drawCircle(cx-8,cy+93,6); drawCircle(cx,cy+97,6); drawCircle(cx+8,cy+93,6);
    glColor3f(0,0,0); drawCircle(cx-7,cy+82,3.2f); drawCircle(cx+7,cy+82,3.2f);
    glColor3f(1,1,1); drawCircle(cx-6,cy+83,1.4f); drawCircle(cx+8,cy+83,1.4f);
    glColor3f(1.0f,0.6f,0.0f);
    glBegin(GL_TRIANGLES); glVertex2f(cx,cy+73); glVertex2f(cx+10,cy+66); glVertex2f(cx-10,cy+66); glEnd();
    glColor3f(0.96f,0.96f,0.96f); drawEllipse(cx-26,cy+55,12,8); drawEllipse(cx+26,cy+55,12,8);
}
void drawBottomEggDots(){
    float y=95,r=10,gap=60,sx=WIN_W/2 - 2*gap;
    float cols[5][3]={{1,0.6f,0.1f},{0.9f,0.2f,0.2f},{0.2f,0.6f,1},{1,0.8f,0.2f},{1,0.3f,0.6f}};
    for(int i=0;i<5;i++){ glColor3f(cols[i][0],cols[i][1],cols[i][2]); drawCircle(sx+i*gap,y,r); }
}

/* ----------------- REPLACED/ENHANCED drawHen (keeps signature same) -----------------
   This implementation replaces the previous simple hen with a slightly more detailed
   animated hen: body, wing, tail, head, beak, eyes, and animated legs & subtle bob.
   It uses the Hen struct's new animation fields but keeps its x,y,w,h usage so the
   rest of the game (spawnEggFromHen, updateHens) remains compatible.
*/
void drawHen(Hen *h){
    /* choose color theme by colorIndex (0..2) */
    float bodyR, bodyG, bodyB;
    float wingR, wingG, wingB;
    float tailR, tailG, tailB;
    float headR, headG, headB;
    float beakR, beakG, beakB;
    float legR, legG, legB;

    int idx = h->colorIndex % MAX_HENS;
    if(idx==0){
        bodyR=0.7f; bodyG=0.8f; bodyB=1.0f;
        wingR=1.0f; wingG=0.9f; wingB=0.95f;
        tailR=0.8f; tailG=0.8f; tailB=1.0f;
        headR=1.0f; headG=0.6f; headB=0.9f;
        beakR=1.0f; beakG=0.8f; beakB=0.2f;
        legR=1.0f; legG=0.8f; legB=0.0f;
    } else if(idx==1){
        bodyR=1.0f; bodyG=0.8f; bodyB=0.9f;
        wingR=1.0f; wingG=1.0f; wingB=0.8f;
        tailR=1.0f; tailG=0.9f; tailB=0.9f;
        headR=1.0f; headG=0.6f; headB=0.8f;
        beakR=1.0f; beakG=0.8f; beakB=0.0f;
        legR=1.0f; legG=0.9f; legB=0.0f;
    } else {
        bodyR=1.0f; bodyG=1.0f; bodyB=0.5f;
        wingR=0.7f; wingG=1.0f; wingB=0.7f;
        tailR=1.0f; tailG=0.7f; tailB=0.9f;
        headR=1.0f; headG=0.5f; headB=0.8f;
        beakR=1.0f; beakG=0.8f; beakB=0.0f;
        legR=1.0f; legG=0.9f; legB=0.0f;
    }

    /* base coordinates */
    float bx = h->x + h->w * 0.5f;   /* center x */
    float by = h->y + 24.0f + h->bobOffset; /* center y (add bob) */

    glPushMatrix();
    glTranslatef(bx, by, 0);

    /* BODY (ellipse) */
    glColor3f(bodyR, bodyG, bodyB);
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++){
        float rad = i * (3.1415926f/180.0f);
        glVertex2f(cosf(rad) * 34.0f, sinf(rad) * 22.0f);
    }
    glEnd();

    /* WING (slightly layered) */
    glColor3f(wingR, wingG, wingB);
    glBegin(GL_POLYGON);
    for(int i=0;i<180;i++){
        float rad = i * (3.1415926f/180.0f);
        glVertex2f(cosf(rad) * 28.0f - 6.0f, sinf(rad) * 18.0f);
    }
    glEnd();

    /* TAIL */
    glColor3f(tailR, tailG, tailB);
    glBegin(GL_TRIANGLES);
        glVertex2f(-30, 10);
        glVertex2f(-50, 25);
        glVertex2f(-40, -5);
    glEnd();

    /* HEAD */
    glColor3f(headR, headG, headB);
    drawCircle(18, 28, 12);

    /* BEAK */
    glColor3f(beakR, beakG, beakB);
    glBegin(GL_TRIANGLES);
        glVertex2f(28, 28);
        glVertex2f(40, 32);
        glVertex2f(28, 24);
    glEnd();

    /* EYES */
    glColor3f(1,1,1); drawCircle(15,32,3.5f); drawCircle(21,32,3.5f);
    glColor3f(0,0,0); drawCircle(15.4f,32.2f,1.4f); drawCircle(21.4f,32.2f,1.4f);

    /* LEGS - animated lines rotating around hip points */
    glColor3f(legR, legG, legB);

    /* left leg */
    glPushMatrix();
        glTranslatef(-10.0f, -22.0f, 0.0f);
        glRotatef(h->legAngle, 0, 0, 1);
        glBegin(GL_LINES);
            glVertex2f(0,0); glVertex2f(0,-15);
        glEnd();
    glPopMatrix();

    /* right leg */
    glPushMatrix();
        glTranslatef(10.0f, -22.0f, 0.0f);
        glRotatef(-h->legAngle, 0, 0, 1);
        glBegin(GL_LINES);
            glVertex2f(0,0); glVertex2f(0,-15);
        glEnd();
    glPopMatrix();

    glPopMatrix();
}

/* ---------- Game logic ---------- */
void resetGame(){
    score=0; timeLeft=60; gamePaused=0; playerName[0]='\0'; nameLen=0; nameFocused=1;
    basket.x=WIN_W/2; basket.y=80; basket.radius=70;
    for(int i=0;i<MAX_EGGS;i++) eggs[i].active=0;
    for(int i=0;i<MAX_HENS;i++){
        hens[i].w=100; hens[i].h=80; hens[i].x=200+i*180; hens[i].y=420;
        hens[i].speed=randf(0.4f,0.9f); hens[i].dir=(rand()%2)?1:-1;
        /* initialize new animation fields */
        hens[i].legAngle = 0.0f;
        hens[i].legDir = 1;
        hens[i].bobOffset = 0.0f;
        hens[i].colorIndex = i; /* keep each hen distinct */
    }
    for(int i=0;i<MAX_CLOUDS;i++){ clouds[i].x=randf(0,WIN_W); clouds[i].y=randf(WIN_H-150,WIN_H-50); clouds[i].speed=randf(0.2f,0.5f); }

    // NOTE: no music here anymore; we only start it when GAME actually begins
}
void spawnEggFromHen(int i){
    int idx=-1; for(int k=0;k<MAX_EGGS;k++){ if(!eggs[k].active){ idx=k; break; } } if(idx==-1) return;
    Egg *e=&eggs[idx]; e->active=1; e->x=hens[i].x+hens[i].w*0.5f; e->y=hens[i].y-10; e->rx=10; e->ry=14;
    float r=randf(0,1); if(r<0.12f) e->type=GOLDEN; else if(r<0.22f) e->type=POOP; else e->type=NORMAL; e->speed=randf(1.8f,3.6f);
}
void updateEggs(){
    for(int i=0;i<MAX_EGGS;i++){
        Egg *e=&eggs[i]; if(!e->active) continue; e->y -= e->speed;
        float dx=e->x-basket.x, dy=e->y-basket.y, rad=basket.radius*0.9f;
        if(dx*dx+dy*dy <= rad*rad && e->y < basket.y + basket.radius){
            if(e->type==NORMAL){ score+=5;  sfxCatch(); }
            else if(e->type==GOLDEN){ score+=10; sfxCatch(); }
            else { score-=10; sfxMiss(); } // miss sound for catching poop (still plays miss sound)
            e->active=0; continue;
        }
        if(e->y<120){
            if(e->type==NORMAL||e->type==GOLDEN){ score-=3; sfxMiss(); } // missed good egg -> play miss sound
            e->active=0;
        }
    }
}
void updateHens(){
    /* existing movement logic preserved; we add leg animation and bobbing */
    for(int i=0;i<MAX_HENS;i++){
        Hen *h = &hens[i];

        /* horizontal movement */
        h->x += h->speed * h->dir;
        if(h->x < 80){ h->x = 80; h->dir = 1; }
        if(h->x + h->w > WIN_W-80){ h->x = WIN_W-80-h->w; h->dir = -1; }

        /* occasionally spawn egg (same probability as before) */
        if(rand()%200==0) spawnEggFromHen(i);

        /* leg angle swing */
        h->legAngle += h->legDir * 2.0f;
        if(h->legAngle > 25.0f || h->legAngle < -25.0f) h->legDir *= -1;

        /* subtle vertical bob based on elapsed time and hen index */
        float t = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        h->bobOffset = sinf(t*3.0f + i*0.7f) * 2.5f;
    }
}

// ---------- UI / Screens ----------
void drawTitle(){
    glColor3f(1.0f,0.95f,0.2f);
    drawText(WIN_W/2-135, WIN_H-90, "CATCH THE EGGS", GLUT_BITMAP_TIMES_ROMAN_24);
}
void initMenu(){
    float bw=300,bh=70,cx=(WIN_W-bw)/2.0f, top=WIN_H-220, space=85;
    menuButtons[0]=(Button){cx, top,           bw,bh, "PLAY",        0,0,0};
    menuButtons[1]=(Button){cx, top-space,     bw,bh, "SETTINGS",    0,0,0}; // -> INSTRUCTIONS
    menuButtons[2]=(Button){cx, top-2*space,   bw,bh, "EXIT",        0,0,0};
    float sbw=170,sbh=45,rx=WIN_W - sbw - 40;
    menuButtons[3]=(Button){rx, top+15,       sbw,sbh, "INSTRUCTIONS", 0,0,0};
    menuButtons[4]=(Button){rx, top-space+15, sbw,sbh, "SCORE",        0,0,0};
}
void drawMenu(){
    drawFarmBackground(); drawTitle();
    for(int i=0;i<3;i++) drawPillButton(&menuButtons[i]);
    for(int i=3;i<5;i++) drawPillButton(&menuButtons[i]);
    drawMascotHen(); drawBottomEggDots();
}
void drawHUD(){
    glColor3f(0,0,0); char buf[64];
    sprintf(buf,"Score: %d",score); drawText(20, WIN_H-30, buf, GLUT_BITMAP_HELVETICA_18);
    sprintf(buf,"Time: %ds",timeLeft); drawText(WIN_W-140, WIN_H-30, buf, GLUT_BITMAP_HELVETICA_18);
    if(gamePaused) drawText(WIN_W/2-40, WIN_H-30, "PAUSED", GLUT_BITMAP_HELVETICA_18);
}
void renderInstructions(){
    drawFarmBackground(); glColor3f(0,0,0);
    drawText(120,500,"Instructions",GLUT_BITMAP_TIMES_ROMAN_24);
    drawText(120,460,"Move basket: Left/Right or A/D or Mouse",GLUT_BITMAP_HELVETICA_18);
    drawText(120,435,"Pause/Resume: Space",GLUT_BITMAP_HELVETICA_18);
    drawText(120,410,"Back to Menu: Esc",GLUT_BITMAP_HELVETICA_18);
    drawText(120,370,"Egg types:",GLUT_BITMAP_HELVETICA_18);
    glColor3f(1,1,1); drawEllipse(260,350,10,14); glColor3f(0,0,0); drawText(280,345,"Normal +5",GLUT_BITMAP_HELVETICA_18);
    glColor3f(1.0f,0.85f,0.1f); drawEllipse(260,320,10,14); glColor3f(0,0,0); drawText(280,315,"Golden +10",GLUT_BITMAP_HELVETICA_18);
    /* Show poop icon sample: small dark brown circle */
    glColor3f(0.36f, 0.20f, 0.10f); drawCircle(260,290, fmaxf(10,14)/3.0f ); glColor3f(0,0,0); drawText(280,285,"Poop -10 (small)",GLUT_BITMAP_HELVETICA_18);
    glColor3f(0,0,0); drawText(120,240,"Missed good eggs: -3 each",GLUT_BITMAP_HELVETICA_18);
    drawText(120,210,"Game ends when timer hits 0.",GLUT_BITMAP_HELVETICA_18);
    drawText(120,160,"Press Esc to return to Menu.",GLUT_BITMAP_HELVETICA_18);
}
void renderScores(){
    drawFarmBackground(); glColor3f(0,0,0);
    drawText(140,500,"High Scores",GLUT_BITMAP_TIMES_ROMAN_24);
    for(int i=0;i<MAX_SCORES;i++){ char buf[64]; sprintf(buf,"%d) %d",i+1,highScores[i]); drawText(160,460-i*35,buf,GLUT_BITMAP_HELVETICA_18); }
    drawText(120,220,"Press Esc to return to Menu.",GLUT_BITMAP_HELVETICA_18);
}

// ---- GAME OVER (dark UI with name input + buttons) ----
void drawGOButton(float x,float y,float w,float h,const char* txt,int hovered){
    if(hovered) glColor3f(0.30f,0.30f,0.30f); else glColor3f(0.15f,0.15f,0.15f);
    drawRect(x,y,w,h); glColor3f(1,1,1); drawOutlined(x,y,w,h,1,1,1);
    glColor3f(1,1,1);
    float tx=x+(w/2.0f-(float)strlen(txt)*8/2.0f), ty=y+h/2.0f-5;
    drawText(tx,ty,txt,GLUT_BITMAP_9_BY_15);
}
void drawInputBox(float x,float y,float w,float h,int focused){
    glColor3f(0.08f,0.08f,0.08f); drawRect(x,y,w,h);
    if(focused) glColor3f(0.9f,0.25f,0.25f); else glColor3f(0.7f,0.7f,0.7f);
    drawOutlined(x,y,w,h,1,1,1);
    glColor3f(1,1,1); drawText(x+8,y+h/2-5, playerName, GLUT_BITMAP_9_BY_15);
    if(focused){
        int ms=glutGet(GLUT_ELAPSED_TIME);
        if((ms/500)%2==0){ float caretX=x+8+nameLen*9; glBegin(GL_LINES); glVertex2f(caretX,y+6); glVertex2f(caretX,y+h-6); glEnd(); }
    }
}
void renderGameOver(){
    glColor3f(0.10f,0.10f,0.10f); drawRect(0,0,WIN_W,WIN_H);
    glColor3f(1,1,1); drawText(WIN_W/2-90, WIN_H-140, "GAME OVER", GLUT_BITMAP_9_BY_15);

    drawText(WIN_W/2-170, WIN_H-200, "Your name:", GLUT_BITMAP_9_BY_15);
    float ibx=WIN_W/2-60, iby=WIN_H-215, ibw=180, ibh=24;
    drawInputBox(ibx,iby-ibh,ibw,ibh,nameFocused);

    drawText(WIN_W/2-70, WIN_H-260, "YOUR SCORE", GLUT_BITMAP_9_BY_15);
    char sbuf[32]; sprintf(sbuf,"%d",score);
    drawText(WIN_W/2-10, WIN_H-285, sbuf, GLUT_BITMAP_9_BY_15);

    float bw=140,bh=40;
    float rx1=WIN_W/2-bw-20, ry1=WIN_H-350; // RETRY
    float rx2=WIN_W/2+20,    ry2=WIN_H-350; // QUIT
    float mx =WIN_W/2-70,    my =WIN_H-420; // MENU

    drawGOButton(rx1,ry1,bw,bh,"RETRY", goBtnHover==0);
    drawGOButton(rx2,ry2,bw,bh,"QUIT",  goBtnHover==1);
    if(goBtnHover==2) glColor3f(0.30f,0.30f,0.30f); else glColor3f(0.18f,0.18f,0.18f);
    drawRect(mx,my,140,44); glColor3f(1,1,1); drawOutlined(mx,my,140,44,1,1,1);
    glColor3f(1,1,1); drawText(mx+45,my+15,"MENU",GLUT_BITMAP_9_BY_15);
}

// ---------- Render loop ----------
void renderGame(){
    drawFarmBackground();
    for(int i=0;i<MAX_HENS;i++) drawHen(&hens[i]);
    for(int i=0;i<MAX_EGGS;i++) drawEgg(&eggs[i]);
    drawBasket();
    drawHUD();
}

// ---------- Timers ----------
void timerFunc(int v){
    if(currentState==GAME && !gamePaused){
        int ms=glutGet(GLUT_ELAPSED_TIME);
        if(ms-lastSecondTick>=1000){
            lastSecondTick=ms; timeLeft--;
            if(timeLeft<=0){
                timeLeft=0;
                pushHighScore(score);
                currentState=GAME_OVER;
                nameFocused=1;
                stopMusic();          // ensure music stops at game over
                sfxGameOver();
            }
        }
        updateHens(); updateEggs();
    }
    glutPostRedisplay();
    glutTimerFunc(16,timerFunc,0);
}

// ---------- Input ----------
void kbd(unsigned char key,int x,int y){
    if(currentState==MENU){
        if(key==27) exit(0);
    } else if(currentState==INSTRUCTIONS || currentState==SCORE){
        if(key==27) currentState=MENU;
    } else if(currentState==GAME){
        if(key==27){ currentState=MENU; stopMusic(); }   // leaving game -> stop music
        else if(key==' '){
            gamePaused=!gamePaused;
            if(gamePaused) stopMusic();                 // pause -> stop
            else           playLoopMusic();             // resume -> start
        } else if(key=='a'||key=='A'){ basket.x-=basketSpeed; if(basket.x<basket.radius) basket.x=basket.radius; }
        else if(key=='d'||key=='D'){ basket.x+=basketSpeed; if(basket.x>WIN_W-basket.radius) basket.x=WIN_W-basket.radius; }
    } else if(currentState==GAME_OVER){
        if(key==27){ currentState=MENU; }
        else if(key==13){ // Enter -> Retry
            playerName[0]='\0'; nameLen=0; resetGame(); currentState=GAME;
            lastSecondTick=glutGet(GLUT_ELAPSED_TIME);
            playLoopMusic();                             // retry -> start music
        } else {
            if(key==8){ if(nameLen>0){ playerName[--nameLen]='\0'; } } // backspace
            else if(key>=32 && key<=126){
                if(nameLen < (int)sizeof(playerName)-1){
                    playerName[nameLen++]=(char)key; playerName[nameLen]='\0';
                }
            }
        }
    }
    glutPostRedisplay();
}
void skbd(int key,int x,int y){
    if(currentState==GAME){
        if(key==GLUT_KEY_LEFT){ basket.x-=basketSpeed; if(basket.x<basket.radius) basket.x=basket.radius; }
        else if(key==GLUT_KEY_RIGHT){ basket.x+=basketSpeed; if(basket.x>WIN_W-basket.radius) basket.x=WIN_W-basket.radius; }
    }
    glutPostRedisplay();
}
void mouseMove(int x,int y){
    if(currentState==GAME){
        basket.x=(float)x; if(basket.x<basket.radius) basket.x=basket.radius; if(basket.x>WIN_W-basket.radius) basket.x=WIN_W-basket.radius;
    } else if(currentState==GAME_OVER){
        float mx=x, my=WIN_H - y; goBtnHover=-1;
        if(mx>=WIN_W/2-140-20 && mx<=WIN_W/2-20 && my>=WIN_H-350 && my<=WIN_H-310) goBtnHover=0;
        else if(mx>=WIN_W/2+20 && mx<=WIN_W/2+20+140 && my>=WIN_H-350 && my<=WIN_H-310) goBtnHover=1;
        else if(mx>=WIN_W/2-70 && mx<=WIN_W/2-70+140 && my>=WIN_H-420 && my<=WIN_H-420+44) goBtnHover=2;
    }
}
void mouseClick(int button,int state,int x,int y){
    if(button!=GLUT_LEFT_BUTTON || state!=GLUT_DOWN) return;

    if(currentState==MENU){
        int my=WIN_H-y;
        for(int i=0;i<5;i++){
            Button b=menuButtons[i];
            if(inRect(x,my,b.x,b.y,b.w,b.h)){
                if(strcmp(b.label,"PLAY")==0){
                    resetGame();
                    currentState=GAME;
                    lastSecondTick=glutGet(GLUT_ELAPSED_TIME);
                    playLoopMusic();                     // start music only when game starts
                }
                else if(strcmp(b.label,"SETTINGS")==0){ currentState=INSTRUCTIONS; }
                else if(strcmp(b.label,"EXIT")==0){ exit(0); }
                else if(strcmp(b.label,"INSTRUCTIONS")==0){ currentState=INSTRUCTIONS; }
                else if(strcmp(b.label,"SCORE")==0){ currentState=SCORE; }
                break;
            }
        }
    } else if(currentState==GAME_OVER){
        float mx=x, my=WIN_H-y;
        float ibx=WIN_W/2-60, iby=WIN_H-215, ibw=180, ibh=24;
        if(inRect(mx,my,ibx,iby-ibh,ibw,ibh)) nameFocused=1; else nameFocused=0;

        if(inRect(mx,my,WIN_W/2-140-20,WIN_H-350,140,40)){ // RETRY
            playerName[0]='\0'; nameLen=0; resetGame(); currentState=GAME;
            lastSecondTick=glutGet(GLUT_ELAPSED_TIME);
            playLoopMusic();                               // retry -> start music
        } else if(inRect(mx,my,WIN_W/2+20,WIN_H-350,140,40)){ // QUIT
            exit(0);
        } else if(inRect(mx,my,WIN_W/2-70,WIN_H-420,140,44)){ // MENU
            currentState=MENU;                              // (no music in menu)
        }
    }
}

// ---------- Display / Init ----------
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    switch(currentState){
        case MENU:         drawMenu(); break;
        case INSTRUCTIONS: renderInstructions(); break;
        case SCORE:        renderScores(); break;
        case GAME_OVER:    renderGameOver(); break;
        case GAME:         renderGame(); break;
    }
    glutSwapBuffers();
}
void reshape(int w,int h){
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    gluOrtho2D(0,WIN_W,0,WIN_H);
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}
void init(){
    srand((unsigned int)time(NULL));
    glClearColor(0.9f,0.9f,1.0f,1.0f);
    glDisable(GL_DEPTH_TEST);
    initMenu();
    resetGame();  // no music here anymore
}
int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(WIN_W,WIN_H);
    glutCreateWindow("Catch the Eggs - Music only in GAME");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(kbd);
    glutSpecialFunc(skbd);
    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutTimerFunc(16,timerFunc,0);

    glutMainLoop();
    return 0;
}
