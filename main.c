#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <GL/glut.h>
#include <stdbool.h>
//inicjalizacja zmiennej okna szerokosci i dlugosci
int window = 0, width = 400, height = 400;

//poruszanie sie bindy
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

//inicjalizacja zmiennych kluczowych dla gry
//poruszanie sie
int direction = DOWN;
const int move_speed = 100;
bool moved = false;

//jedzenie
bool food_avaible = false;
int food_coords[2];
const float map_half_length= 30.0f;

//wyniki
int score=0;

//wielkosc weza
int growth_stage = 0;
const int growth = 2;


void drawFood(){
    glLoadIdentity();
    glTranslatef(food_coords[0], food_coords[1], -40.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2d( 1.0f,  1.0f);
        glVertex2d( 1.0f, -1.0f);
        glVertex2d(-1.0f, -1.0f);
        glVertex2d(-1.0f,  1.0f);
    glEnd();
}


void spawnFood(){
    if (food_avaible){
        return;
    }
    int temp_food_coords[2];
    bool collides;
    do{
        collides = false;

        //temporary koordynaty jedzenia
        temp_food_coords[0] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;
        temp_food_coords[1] = 2 * (rand() % ((int) map_half_length + 1)) - (int) map_half_length;

        // sprawdzanie czy jedzenie nie zrespi sie na snake'u
        for(unsigned int a = 0; a < part_coords.size(); a++){
            if(temp_food_coords[0] == part_coords[a][0] &&
               temp_food_coords[1] == part_coords[a][1]){
                collides = true;
            }
        }

    }while(collides);
    //ustawienie koordynatow jedzenia
    food_coords[0] = temp_food_coords[0];
    food_coords[1] = temp_food_coords[1];

    food_avaible = true;
}
void drawSnake(){
     // Loop over snake size and draw each part at it's respective coordinates
    for(unsigned int a = 0; a < part_coords.size(); a++){
        glLoadIdentity();
        glTranslatef(part_coords[a][0], part_coords[a][1], -40.0f);
        glColor3f(0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2d( 1.0f,  1.0f);
            glVertex2d( 1.0f, -1.0f);
            glVertex2d(-1.0f, -1.0f);
            glVertex2d(-1.0f,  1.0f);
        glEnd();
    }
}



void display(void)
{

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    spawnFood();
    drawFood();
    
}
void initGL(){
    glMatrixMode(GL_PROJECTION);
    gluPerspective(76.0f,1.0f,0.0f,40.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}
void reshape(GLsizei width,GLsizei height)
    {
   glViewport (0, 0, (GLsizei) width, (GLsizei) height); 

}
//wypisywanie tekstu na displayu
void drawBitmapText(char* text, float x, float y, float z) {
    char* c;

    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos3f(x, y, z);

    for(c = text; *c != '\0'; c++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

int mainmenu(){
    int choice;
    char ch;

    printf("\nWcisnij 1 jesli chcesz rozpoczac\nWcisnij 2 by zobaczyc ostatnie wyniki\n");
    scanf("%d",&choice);
    if(choice==2){
        FILE *fptr;
        fptr =fopen("scoreboard.txt","a+");
        do{
            ch = fgetc(fptr);
            printf("%c",ch);
        }while(ch!=EOF);
        fclose(fptr);
        return 1;
    }
    return 2;
}

int main(int argc, char** argv)
{



    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL Snake");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    
    // Create  window main
    
    //glutReshapeFunc(reshape); reshaping na przyszlosc

    srand(time(NULL));
    initGL();
    glutMainLoop();
return 0;
}