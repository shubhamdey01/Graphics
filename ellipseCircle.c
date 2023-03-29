// Ellipse Drawing algorithm

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ellipseCircle.h"
#include "ddaLine.h"

void draw(void);
void myInit(void);

int a, b, rx, ry;

int main(int argc, char** argv) {
	printf("Enter coordinates of the center :\n");
	scanf("%d %d", &a, &b);
	printf("Enter Rx & Ry :\n");
	scanf("%d %d", &rx, &ry);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ellipse Drawing");
    myInit();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
    glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-540.0, 540.0, -360.0, 360.0);
}

void draw(void){
	ddaLine(0,-350,0,350);
	ddaLine(-350,0,350,0);
    glColor3f(1, 0, 0);
	ellipse(a, b, rx, ry);
    glColor3f(0, 1, 0);
    circle(a, b, rx);
    glColor3f(0, 0, 1);
    circle(a, b, ry);
}