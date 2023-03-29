// Circle Drawing algorithm

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ddaLine.h"

void draw(void);
void myInit(void);
void circle(int, int, int);
void plot(int, int);

int a, b, r;

int main(int argc, char** argv) {
	printf("Enter coordinates of the center :\n");
	scanf("%d %d", &a, &b);
	printf("Enter radius :\t");
	scanf("%d", &r);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Circle Drawing");
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
	circle(a, b, r);
}

void circle(int x1, int y1, int r1) {
	int x = 0;
	int y = r1;
	int p = 1 - r1;
	plot(x, y);

	while (y > x) {
		x++; 
		if (p < 0) {
			p += 2*x+1;
		}
		else {
			y--;
			p += 2*(x-y)+1;
		}
		plot(x, y);
	}
}

void plot(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(a+x, b+y);
	glVertex2i(a-x, b+y);
	glVertex2i(a+x, b-y);
	glVertex2i(a-x, b-y);
	glVertex2i(a+y, b+x);
	glVertex2i(a-y, b+x);
	glVertex2i(a+y, b-x);
	glVertex2i(a-y, b-x);
	glEnd();
    glFlush();
}