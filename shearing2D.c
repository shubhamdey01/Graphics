// Shearing

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ddaLine.h"

void myInit(void);
void draw(void);
void polygon(int*, int*, float[]);
void shearing(int, int);

int n, a, b, xref, yref;
int *x, *y, *p, *q;

int main(int argc, char** argv) {
	printf("Enter no. of vertices :\t");
	scanf("%d", &n);
	
	x = (int*)calloc(n, sizeof(int));
	y = (int*)calloc(n, sizeof(int));
	for(int i=0; i<n; i++) {
		printf("Enter x%d & y%d :\n", i+1, i+1);
		scanf("%d %d", x+i, y+i);
	}

	printf("\nEnter SHx & SHy for shearing :\n");
	scanf("%d %d", &a, &b);
	printf("\nEnter Xref & Yref :\n");
	scanf("%d %d", &xref, &yref);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Shearing");
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
	float color[] = {1, 0, 0};
	polygon(x, y, color);
	shearing(a, b);
}

void polygon(int *x, int *y, float color[]) {
	glColor3f(color[0], color[1], color[2]);
	for(int i=0; i<n; i++) {
		if(i < n-1) {
			ddaLine(x[i], y[i], x[i+1], y[i+1]);
			continue;
		}
		ddaLine(x[i], y[i], x[0], y[0]);
	}
}

void shearing(int shx, int shy) {
	p = (int*)calloc(n, sizeof(int));
	q = (int*)calloc(n, sizeof(int));
	for(int i=0; i<n; i++) {
		p[i] = x[i] + shx*(y[i]-yref);
		q[i] = shy*(x[i]-xref) + y[i];
	}
	float color[] = {0, 0, 1};
	polygon(p, q, color);
}