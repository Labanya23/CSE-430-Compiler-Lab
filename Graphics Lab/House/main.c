// Decorated House (More Colorful)
#include <GL/glut.h>

void init(void)
{
    glClearColor(0.8, 0.9, 1.0, 0.0); // light sky background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 300.0, 0.0, 220.0);
}

void buildHouse(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // House body
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.6, 0.4); // peach color
    glVertex2i(60, 40);
    glVertex2i(60, 150);
    glVertex2i(240, 150);
    glVertex2i(240, 40);
    glEnd();

    // Roof
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.2, 0.0); // brown
    glVertex2i(50, 150);
    glVertex2i(250, 150);
    glVertex2i(150, 200);
    glEnd();

    // Door
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.2, 0.7); // purple-blue
    glVertex2i(120, 40);
    glVertex2i(120, 90);
    glVertex2i(180, 90);
    glVertex2i(180, 40);
    glEnd();

    // Door handle (small circle)
    glColor3f(1.0, 1.0, 0.0); // yellow
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(175, 65);
    glEnd();

    // Left window
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.7, 0.9); // cyan-blue
    glVertex2i(80, 110);
    glVertex2i(110, 110);
    glVertex2i(110, 85);
    glVertex2i(80, 85);
    glEnd();

    // Right window
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.7, 0.9);
    glVertex2i(190, 110);
    glVertex2i(220, 110);
    glVertex2i(220, 85);
    glVertex2i(190, 85);
    glEnd();

    // Window frames (cross design)
    glColor3f(1.0, 1.0, 1.0); // white frames
    glBegin(GL_LINES);
    // Left window vertical
    glVertex2i(95, 110);
    glVertex2i(95, 85);
    // Left window horizontal
    glVertex2i(80, 97);
    glVertex2i(110, 97);

    // Right window vertical
    glVertex2i(205, 110);
    glVertex2i(205, 85);
    // Right window horizontal
    glVertex2i(190, 97);
    glVertex2i(220, 97);
    glEnd();

    // Stairs (3 yellow steps)
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.8, 0.0);
    glVertex2i(110, 30);
    glVertex2i(190, 30);
    glVertex2i(190, 40);
    glVertex2i(110, 40);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.8, 0.0);
    glVertex2i(105, 20);
    glVertex2i(195, 20);
    glVertex2i(195, 30);
    glVertex2i(105, 30);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.8, 0.0);
    glVertex2i(100, 10);
    glVertex2i(200, 10);
    glVertex2i(200, 20);
    glVertex2i(100, 20);
    glEnd();

    // Chimney
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.1, 0.1); // dark brown
    glVertex2i(190, 170);
    glVertex2i(190, 190);
    glVertex2i(210, 190);
    glVertex2i(210, 150);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(700, 600);
    glutCreateWindow("Decorated House OpenGL");
    init();
    glutDisplayFunc(buildHouse);
    glutMainLoop();
}
