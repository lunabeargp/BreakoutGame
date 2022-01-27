//
// Created by georg on 12/2/2021.
//

#include "graphics.h"
#include "circle.h"
#include "rect.h"
#include "Brick.h"
#include <vector>
#include <time.h>
enum ballInPlay {yes, no};
enum paddleMoving{l, r, still};
paddleMoving paddle_moving;
ballInPlay ball_in_play;
using namespace std;
GLdouble width, height;
int wd;
int xvel, yvel;
int lives;
int score;


Circle ball;
vector<Brick> bricksRow1;
Rect paddle;

const color cadet(84/255.0, 106/255.0, 118/255.0);
const color greenYellowCrayola(249/255.0, 234/255.0, 154/255.0);
const color princetonOrange(241/255.0, 127/255.0, 41/255.0);
const color pastelPink(207/255.0, 152/255.0, 147/255.0);

const color skyBlueCrayola(144/255.0, 224/255.0, 239/255.0);
const color frenchLime(152/255.0, 245/255.0, 71/255.0);


//push back the bricks in the 4 rows
void initBricks1() {
    int totalWidth=0;
    dimensions1 size;
    size.width=75;
    size.height=25;
    while(totalWidth<width-120) {
        bricksRow1.push_back(Brick(pastelPink, totalWidth + size.width , size.height, size, 5, true));
        totalWidth += size.width+10;
    }



}
void initBricks2() {
    int totalWidth = 0;
    dimensions1 size;
    size.width = 75;
    size.height = 25;
    while (totalWidth < width - 120) {
        bricksRow1.push_back(Brick(pastelPink, totalWidth + size.width, size.height + 35, size, 5, true));
        totalWidth += size.width + 10;
    }
}
void initBricks3() {
    int totalWidth = 0;
    dimensions1 size;
    size.width = 75;
    size.height = 25;
    while (totalWidth < width - 120) {
        bricksRow1.push_back(Brick(pastelPink, totalWidth + size.width, size.height+70, size, 5, true));
        totalWidth += size.width + 10;

    }
}
void initBricks4() {
    int totalWidth = 0;
    dimensions1 size;
    size.width = 75;
    size.height = 25;
    while (totalWidth < width - 120) {
        bricksRow1.push_back(Brick(pastelPink, totalWidth + size.width, size.height+105, size, 5, true));
        totalWidth += size.width + 10;
    }
}
//create paddle
void initPaddle() {
    paddle.setCenter(width/2, height-5);
    paddle.setSize(100, 10);
    paddle.setColor(cadet);
}
//create ball
void initBall() {
    ball.setRadius(5);
    ball.setCenter(paddle.getCenterX(), paddle.getTopY()-5);
    ball.setColor(princetonOrange);
    xvel=0;
    yvel=0;

}
//erase brick
void eraseBrick(vector<Rect>(brickRow), int index){
    brickRow[index].setColor(greenYellowCrayola);
    brickRow[index].draw();

}
//the cooler (overloaded) erase brick
void eraseBrick(Rect &brick){
    brick.setColor(greenYellowCrayola);
    brick.draw();

}

void init() {
    width = 500;
    height = 500;
    srand(time(0));
    lives=3;
    score=0;
    ball_in_play=no;
    paddle_moving=still;

    initBricks1();
    initBricks2();
    initBricks3();
    initBricks4();

    initPaddle();
    initBall();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(249/255.0, 234/255.0, 154/255.0, 1);
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you are running Catalina on Mac)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

        //draw lives and points
        string label = to_string(lives);
        glColor3f(241/255.0, 127/255.0, 41/255.0);
        glRasterPos2i(10, 20);
        for (const char &letter : label) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
        string points = to_string(score);
        glColor3f(0, 0, 0);
        glRasterPos2i(470, 20);
        for (const char &letter : points) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, letter);
        }
        //draw paddle
        paddle.draw();
        //draw bricks
        for (int i = 0; i < bricksRow1.size(); i++)
            bricksRow1[i].draw();

        //ball collision with top of window, and bottom which loses you a life and destroys the window when you run out of lives
        if (ball.getTopY() <= (0))
            yvel *= -1;
        if (ball.getCenterY()>=515) {
            lives--;
            ball_in_play = no;
            initBall();
            if (lives == 0) {
                glutDestroyWindow(wd);
                exit(0);
            }
        }
        //ball bouncing off paddle with semi random angles
        if (ball.getBottomY() == paddle.getTopY() &&
            ball.getCenterX() >= paddle.getLeftX() &&
            ball.getCenterX() <= paddle.getRightX()) {
            yvel *= -1;
            if (paddle_moving == r && ball_in_play == yes) {
                xvel = rand()%3+2;
            }
            if (paddle_moving == l && ball_in_play == yes) {
                xvel = rand()%-3-2;
            }


        }
        //ball bouncing off of sides of window
        if (ball.getRightX() <= 500)
            xvel *= -1;
        if (ball.getLeftX() >= 0)
            xvel *= -1;
        //brick collision/deletion/color change
        for (Brick &brick: bricksRow1) {
            if (ball.getBottomY() <= brick.getTopY() && ball.getTopY() >= brick.getBottomY() &&
                ball.getRightX() >= brick.getLeftX() && ball.getLeftX() <= brick.getRightX() &&
                brick.getBrickInPlay() == true) {
                yvel *= -1;
                brick.setBrickHealth(brick.getBrickHealth() - 1);
                if (brick.getBrickHealth() == 3) {
                    brick.setColor(skyBlueCrayola);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 1) {
                    brick.setColor(frenchLime);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 0) {
                    eraseBrick(brick);
                    brick.setBrickInPlay(false);
                    score++;

                }
            } else if (ball.getTopY() <= brick.getBottomY() && ball.getBottomY() >= brick.getTopY() &&
                       ball.getRightX() >= brick.getLeftX() && ball.getLeftX() <= brick.getRightX() &&
                       brick.getBrickInPlay() == true) {
                yvel *= -1;
                brick.setBrickHealth(brick.getBrickHealth() - 1);
                if (brick.getBrickHealth() == 3) {
                    brick.setColor(skyBlueCrayola);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 1) {
                    brick.setColor(frenchLime);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 0) {
                    eraseBrick(brick);
                    brick.setBrickInPlay(false);
                    score++;

                }
            } else if (ball.getRightX() <= brick.getLeftX() && ball.getLeftX() >= brick.getRightX() &&
                       ball.getBottomY() >= brick.getTopY() && ball.getTopY() <= brick.getBottomY() &&
                       brick.getBrickInPlay() == true) {
                xvel *= -1;
                brick.setBrickHealth(brick.getBrickHealth() - 1);
                if (brick.getBrickHealth() == 3) {
                    brick.setColor(skyBlueCrayola);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 1) {
                    brick.setColor(frenchLime);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 0) {
                    eraseBrick(brick);
                    brick.setBrickInPlay(false);
                    score++;

                }
            } else if (ball.getLeftX() <= brick.getRightX() && ball.getRightX() >= brick.getLeftX() &&
                       ball.getBottomY() >= brick.getTopY() && ball.getTopY() <= brick.getBottomY() &&
                       brick.getBrickInPlay() == true) {
                xvel *= -1;
                brick.setBrickHealth(brick.getBrickHealth() - 1);
                if (brick.getBrickHealth() == 3) {
                    brick.setColor(skyBlueCrayola);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 1) {
                    brick.setColor(frenchLime);
                    brick.draw();
                }
                if (brick.getBrickHealth() == 0) {
                    eraseBrick(brick);
                    brick.setBrickInPlay(false);
                    score++;

                }
            }

        }
        //ball moves
        ball.draw();
        ball.move(xvel, yvel);

        if (score==20){
            string message = "You win! Let the ball drop until the game ends to exit or press escape.";
            glColor3f(0, 0, 0);
            glRasterPos2i(10, 200);
            for (const char &letter : message) {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, letter);
            }
        }


glFlush();
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {

        case GLUT_KEY_DOWN:
            //there are a few edge cases where the ball just leaves the screen. I think it has something to do with the processing
            //speed but its hard to tell. It happens very infrequently and with no discernible pattern. You can use arrow down to spawn
            //a new ball so you don't get soft locked.
            initBall();
            ball_in_play=no;
            break;
        case GLUT_KEY_LEFT:
            //move paddle left. If ball hasn't been launched yet it moves with the paddle
            paddle_moving=l;
            if (paddle.getLeftX()>0) {
                paddle.move(-40, 0);
                if (ball_in_play == no) {
                    ball.move(-40, 0);
                }
            }

            break;
        case GLUT_KEY_RIGHT:
            //same deal with paddle right
            paddle_moving=r;
            if (paddle.getRightX()<width) {
                paddle.move(40, 0);
                {
                    if (ball_in_play == no)
                        ball.move(40, 0);
                }
            }

            break;
        case GLUT_KEY_UP:
            //launch ball and start game
            if (ball_in_play==no) {
                yvel=rand()%2+9;
                ball_in_play=yes;
            }

            break;
    }



}

void cursor(int x, int y) {


}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {


}

void ballTimer(int dummy) {


    glutPostRedisplay();
    glutTimerFunc(25, ballTimer, dummy);
}



/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Breakout" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, space bar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, ballTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}