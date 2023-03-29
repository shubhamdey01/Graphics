// Ellipse Drawing algorithm

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ddaLine.h"

void draw(void);
void myInit(void);
void ellipse(int, int, int, int);
void plot(int, int);

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
	ddaLine(-530,0,530,0);
	ellipse(a, b, rx, ry);
}

void ellipse(int x1, int y1, int r1, int r2) {
	int rx2 = r1*r1;
	int ry2 = r2*r2;
    int Trx2 = 2*rx2;
    int Try2 = 2*ry2;
	int p;
    int x = 0;
    int y = r2;
    int px = 0;
    int py = Trx2 * y;
	plot(x, y);

    // Region 1
    p = (int)(ry2-(rx2*r2)+(0.25*rx2));
	while (px < py) {
		x++;
        px += Try2;
		if (p < 0) {
			p += ry2 + px;
		}
		else {
			y--;
            py -= Trx2;
			p += ry2 + px - py;
		}
		plot(x, y);
	}

    // Region 2
    p = (int)(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2);
	while (y > 0) {
		y--;
        py -= Trx2;
		if (p > 0) {
			p += rx2 - py;
		}
		else {
			x++;
            px += Try2;
			p += rx2 + px - py;
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
	glEnd();
    glFlush();
}