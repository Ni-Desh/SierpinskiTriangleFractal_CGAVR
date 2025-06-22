#include <GL/glut.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int maxDepth = 5;
int currentDepth = 0;

void delay(int ms) {
    usleep(ms * 1000);  // delay in milliseconds
}

void drawTriangle(float* a, float* b, float* c) {
    glBegin(GL_TRIANGLES);
    glVertex2fv(a);
    glVertex2fv(b);
    glVertex2fv(c);
    glEnd();
}

void sierpinskiStep(float* a, float* b, float* c, int depth) {
    if (depth == 0) {
        drawTriangle(a, b, c);
        return;
    }

    float ab[] = { (a[0] + b[0]) / 2, (a[1] + b[1]) / 2 };
    float bc[] = { (b[0] + c[0]) / 2, (b[1] + c[1]) / 2 };
    float ca[] = { (c[0] + a[0]) / 2, (c[1] + a[1]) / 2 };

    // Recursive step - draw smaller triangles
    sierpinskiStep(a, ab, ca, depth - 1);
    sierpinskiStep(ab, b, bc, depth - 1);
    sierpinskiStep(ca, bc, c, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float a[] = { -0.8f, -0.6f };  // Bottom-left
    float b[] = {  0.0f,  0.8f };  // Top
    float c[] = {  0.8f, -0.6f };  // Bottom-right

    glColor3f(0.2f, 0.6f, 1.0f);  // Triangle color

    // Draw all previous depths up to currentDepth
    sierpinskiStep(a, b, c, currentDepth);

    glFlush();

    if (currentDepth < maxDepth) {
        currentDepth++;          // Next level
        delay(800);              // Pause before next frame
        glutPostRedisplay();     // Redraw
    }
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // Background: white
    gluOrtho2D(-1, 1, -1, 1);          // Coordinate system
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Progressive Triangle Subdivision");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
