// Circle Drawing algorithm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "ddaLine.h"

void draw(void);
void myInit(void);
void circle(int, int, int, float[]);
void plot(int, int, int, int, float[]);
void fillCircle(float , float , float );
int angle(int, int, int, int, int);
void intersect();
void fillIntersect(int, int, int, int, int, int);


int a1, b1, r1, a2, b2, r2;

int main(int argc, char** argv) {
	printf("Enter coordinates of the center :\n");
	scanf("%d %d", &a1, &b1);
	printf("Enter radius :\t");
	scanf("%d", &r1);
	printf("\nEnter coordinates of the center :\n");
	scanf("%d %d", &a2, &b2);
	printf("Enter radius :\t");
	scanf("%d", &r2);

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
	float color[] = {0, 0, 0};
	ddaLine(0,-350,0,350);
	ddaLine(-350,0,350,0);
	color[0] = 1;
	circle(a1, b1, r1, color);
	color[1] = 1;
	circle(a2, b2, r2, color);
	intersect();
}

void circle(int x1, int y1, int r1, float color[]) {
	int x = 0;
	int y = r1;
	int p = 1 - r1;
	plot(x1, y1, x, y, color);

	while (y > x) {
		x++; 
		if (p < 0) {
			p += 2*x+1;
		}
		else {
			y--;
			p += 2*(x-y)+1;
		}
		plot(x1, y1, x, y, color);
	}
}

void plot(int a, int b, int x, int y, float color[]) {
	glBegin(GL_POINTS);
	glColor3f(color[0], color[1], color[2]);
    glPointSize(4.0);
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

void intersect() {
	float x, y, t;

	glColor3f(0,0,1);
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<=360; i++) {
		t = i * 2.0f * M_PI/360;

		x = a1 + r1 * cos(t);
		y = b1 + r1 * sin(t);
		if((x-a2)*(x-a2) + (y-b2)*(y-b2) <= r2*r2)
			glVertex2f(x,y);
		x = a2 + r2 * cos(t);
		y = b2 + r2 * sin(t);
		if((x-a1)*(x-a1) + (y-b1)*(y-b1) <= r1*r1)
			glVertex2f(x,y);		
	}
	glEnd();
	glFlush();
}