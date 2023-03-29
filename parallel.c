// Parallel line Drawing algorithm

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void draw(void);
void myInit(void);
void ddaLine(int, int, int, int, int);

int a, b, c, d, z;

int main(int argc, char** argv) {
	printf("Enter X1 :\t");
	scanf("%d", &a);
	printf("Enter Y1 :\t");
	scanf("%d", &b);
	printf("\nEnter X2 :\t");
	scanf("%d", &c);
	printf("Enter Y2 :\t");
	scanf("%d", &d);
	printf("\nEnter D :\t");
	scanf("%d", &z);


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing");
    myInit();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}

void myInit(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void draw(void){
	ddaLine(a, b, c, d, z);
}

void ddaLine(int x1, int y1, int x2, int y2, int z) {
	float dx, dy, step, x, y, k, xin, yin;

	dx = x2-x1;
	dy = y2-y1;
	step = abs(dx)>abs(dy) ? abs(dx) : abs(dy);

	xin = dx/step;
	yin = dy/step;
	x = x1;
	y = y1;

	glColor3f(1.0,0,0);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glVertex2i(x+z,y);
	glEnd();
	for(k=1; k<=step; k++) {
		x += xin;
		y += yin;
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glVertex2i(x+z,y);
		glEnd();
	}
	glFlush();
}