

#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>


// Car position
float carX = 0.0f, carY = 0.0f;
float step = 2.0f; // movement step
bool moveRight = false, moveLeft = false;

// Draw circle (for wheels)
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * 3.1415926f * (float)i / (float)num_segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

// Draw car (rectangle body + two wheels)
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, carY, 0.0f);

    // Car body
    glColor3f(0.2f, 0.6f, 1.0f); // blue body
    glBegin(GL_POLYGON);
    glVertex2f(-40.0f, -10.0f);
    glVertex2f(40.0f, -10.0f);
    glVertex2f(40.0f, 20.0f);
    glVertex2f(-40.0f, 20.0f);
    glEnd();

    glColor3f(0.7f, 0.9f, 1.0f); // light blue window
    glBegin(GL_POLYGON);
    glVertex2f(-20.0f, 20.0f);
    glVertex2f(20.0f, 20.0f);
    glVertex2f(10.0f, 35.0f);
    glVertex2f(-10.0f, 35.0f);
    glEnd();

    // Wheels
    glColor3f(0.1f, 0.1f, 0.1f); // black wheels
    drawCircle(-25.0f, -10.0f, 10.0f, 50);
    drawCircle(25.0f, -10.0f, 10.0f, 50);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCar();

    glutSwapBuffers();
}

void update(int value) {
    if (moveRight) carX += step;
    if (moveLeft) carX -= step;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 fps
}

// Keyboard special keys (arrow keys)
void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:  carX -= step; break;
        case GLUT_KEY_RIGHT: carX += step; break;
        case GLUT_KEY_UP:    carY += step; break;
        case GLUT_KEY_DOWN:  carY -= step; break;
    }
    glutPostRedisplay();
}

// Normal keyboard keys
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': // stop car
            moveRight = moveLeft = false;
            break;
        case 'r': // reset car
            carX = 0.0f;
            carY = 0.0f;
            moveRight = moveLeft = false;
            break;
    }
    glutPostRedisplay();
}

// Mouse function
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            moveRight = true;
            moveLeft = false;
        }
        if (button == GLUT_RIGHT_BUTTON) {
            moveLeft = true;
            moveRight = false;
        }
    }
    if (state == GLUT_UP) {
        moveRight = moveLeft = false;
    }
}

void initGL() {
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // light background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-200.0, 200.0, -150.0, 150.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Simple Car with Controls");

    initGL();

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
