#include "mylib.h"
#include "finaldestination.h"
#include "sky.h"
#include "healthbar.h"
#include "text.h"
#include "lastpage.h"
int main(void);
extern const u16 finaldestination[38400];
extern const u16 sky[38400];
extern const u16 lastpage[38400];
extern const u16 healthbar[1000];
enum{MENU,GAME,WIN,LOSE};
void menu();
void game();
void winlose(int);
int state = MENU;
int main(){
    while(1){
    switch(state)
        {
            case MENU:
                menu();
            case GAME:
                game();
            case WIN:
                winlose(WIN);
            case LOSE:
                winlose(LOSE);
        }    
    }
}
void menu()
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;
    drawImage3(0,0,240,160,sky);
    while(1){
        drawString(60,50,"A FIGHTING GAME",RED);
        drawString(60,80,"PRESS A TO BEGIN",RED);
        if(BUTTON_DOWN_NOW(BUTTON_A)){
            state = GAME;
            drawImage3(0,20,240,160,finaldestination);
            break;
        }
    }
}

void game()
{
    REG_DISPCTL = MODE3 | BG2_ENABLE;

    PLAYER p1;
    p1.c = 50;
    p1.r = 50;
    p1.oldc = 50;
    p1.oldr = 50;
    p1.fc = 50;
    p1.fr = 50;
    p1.width = 5;
    p1.height = 10;
    p1.color = GREEN;
    p1.direction = 1;
    p1.health = 0;
    p1.armLength = 4;
    p1.armWidth = 2;

    PLAYER p2;
    p2.c = 200;
    p2.r = 120;
    p2.fc = 100;
    p2.fr = 50;
    p2.width = 5;
    p2.height = 10;
    p2.color = RED;
    p2.direction = 0;
    p2.health = 0;
    p2.armLength = 4;
    p2.armWidth = 2;



    int moveCounter = 0;
    int jumpCounter = 0;
    int pCounter = 0;
    int enemyCount = 0;
    drawImage3(0,0,240,160,finaldestination);
    while(1){
        
        waitForVBlank();
        if (BUTTON_DOWN_NOW(BUTTON_SELECT))
        {
            state = MENU;
            break;
        }

        drawImage3(0,20,240,160,finaldestination);
        drawImage3(40,0,50,20,healthbar);
        plotLine(0,130,240,130,WHITE);
        drawRect(p2.c,p2.r,p2.width,p2.height,p2.color);

        if(p1.health >= 50){
            break;
        }
        if(p2.health >= 50){
            break;
        }
        if(isCollision(&p1, &p2)==true){
            p1.fc-=10;
            p2.c +=10;
            p1.health+=10;
        }

        if(enemyCount == 10){
            if(p2.c < p1.c){
                p2.c++;
                drawRect(p2.c,p2.r,p2.width,p2.height,p2.color);
            } else if(p2.c > p1.c){
                p2.c--;
                drawRect(p2.c,p2.r,p2.width,p2.height,p2.color);
            }
            enemyCount-=10;
        }
    
        if(p1.health > 0){
            drawRect(40,0,p1.health,20,BLACK);
        } 
        // else {
            // drawImage3(160,0,50,20,healthbar);
        // }

        drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
        if(p1.r+p1.height < 130){
            p1.fr+=1;
        }
        if(p2.r+p2.height < 130){
            p2.r++;
            drawRect(p2.c,p2.r,p2.width,p2.height,p2.color);
        }


        if(p1.c < p1.fc && p1.fc < 240 ){
            p1.c++;
            drawRect(p1.oldc,p1.oldr,p1.width,p1.height,BLACK);
            // drawImage3(0,20,240,160,finaldestination);
            drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
            p1.oldc++;
        } else if (p1.c > p1.fc && p1.fc > 0){
            p1.c--;
            drawRect(p1.oldc,p1.oldr,p1.width,p1.height,BLACK);
            // drawImage3(0,20,240,160,finaldestination);
            drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
            // plotLine(0,130,240,130,WHITE);
            p1.oldc--;
        }

        if(p1.r < p1.fr){
            p1.r+=2;
            drawRect(p1.oldc,p1.oldr,p1.width,p1.height,BLACK);
            // drawImage3(0,20,240,160,finaldestination);
            drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
            // plotLine(0,130,240,130,WHITE);
            p1.oldr+=2;
        } else if (p1.r > p1.fr){       
            p1.r--;
            drawRect(p1.oldc,p1.oldr,p1.width,p1.height,BLACK);
            // drawImage3(0,20,240,160,finaldestination);
            drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
            // plotLine(0,130,240,130,WHITE);
            p1.oldr--;
        }
        drawRect(p1.c,p1.r,p1.width,p1.height,p1.color);
        if(moveCounter >= 1){
            moveCounter = 1;
            if(BUTTON_DOWN_NOW(BUTTON_LEFT)&& !BUTTON_DOWN_NOW(BUTTON_A)){
                p1.fc--;
                if(p1.fc == 0){
                    p1.fc++;
                }
                p1.direction = 0;
            }
            if(BUTTON_DOWN_NOW(BUTTON_RIGHT) && !BUTTON_DOWN_NOW(BUTTON_A)){
                p1.fc++;
                if((p1.fc+p1.width) == 240){
                    p1.fc--;
                }
                p1.direction = 1;
                
            }
            moveCounter -= 2;
        }
            

        if(BUTTON_DOWN_NOW(BUTTON_A) && BUTTON_DOWN_NOW(BUTTON_RIGHT)){ 
            drawRect(p1.c+p1.width,+p1.r+2,p1.armLength,p1.armWidth,p1.color);
            if(isPunched(&p1, &p2) == true){
                p2.c+=10;
                p2.health+=10;
            }
        }
        else if(BUTTON_DOWN_NOW(BUTTON_A) && BUTTON_DOWN_NOW(BUTTON_LEFT)){
            drawRect(p1.c-p1.armLength,p1.r+2,p1.armLength, p1.armWidth,p1.color);
            if(isPunched(&p1, &p2) == true){
                p2.c+=10;
                p2.health+=10;
            }
        } else if(BUTTON_DOWN_NOW(BUTTON_A)&& !BUTTON_DOWN_NOW(BUTTON_LEFT) && !BUTTON_DOWN_NOW(BUTTON_RIGHT)){
            if(p1.direction == 0){
                drawRect(p1.c-p1.armLength,p1.r+2,p1.armLength, p1.armWidth,p1.color);
            } else {
                drawRect(p1.c+p1.width,+p1.r+2,p1.armLength,p1.armWidth,p1.color);  
            }
            if(isPunched(&p1, &p2) == true){
                p2.c+=10;
                p2.health+=10;
            }
        }
        if(jumpCounter >= 40){
            if(BUTTON_DOWN_NOW(BUTTON_UP)){
                jumpCounter=40;
                p1.fr-=10;
                jumpCounter-=40;
                
            }       
            
        }
    
        jumpCounter++;  
        moveCounter++;
        pCounter++;
        enemyCount++;
    }
    if(p2.health >= 50 && p1.health < 50){
        state = LOSE; 
    } else {
        state = WIN; 
    }
    
}
void winlose(int win)
{
    drawImage3(0,0,240,160,lastpage);
    while(1){ 
        drawString(20,50,"press select to return to the menu.", RED);
        if(win == WIN) {
            drawString(60,20,"you win!",RED);    
        } else {
            drawString(60,20,"you lose !",RED);    
        }
        if (BUTTON_DOWN_NOW(BUTTON_SELECT))
        {
            state = MENU;    
            break;
        }
    }
}
