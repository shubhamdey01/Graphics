// Reflection

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "ddaLine.h"

void myInit(void);
void draw(void);
void point(int, int);
void polygon(int*, int*, float[]);
void reflection();

int n, a, b, xB, yB, xE, yE, ch1, ch2;
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

	printf("\nReflection along :-\n1. Axes\n2. Point\n3. Arbitrary line\n\nEnter your choice :\t");
	scanf("%d", &ch1);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Reflection");
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
	reflection();
}

void point(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glVertex2i(x-1,y);
	glVertex2i(x+1,y);
	glVertex2i(x,y-1);
	glVertex2i(x,y+1);
	glEnd();
	glFlush();
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

void reflection() {
	float m;
	int c;
	p = (int*)calloc(n, sizeof(int));
	q = (int*)calloc(n, sizeof(int));

	switch(ch1) {
	case 1:
		printf("\n1. along X-axis\n2. along Y-axis\n\nEnter your choice :\t");
		scanf("%d", &ch2);
		if(ch2 == 1) {
			printf("Enter Y :\n");
			scanf("%d",&yB);
			glColor3f(0, 1, 0);
			ddaLine(-530,yB,530,yB);
			for(int i=0; i<n; i++) {
				p[i] = x[i];
				q[i] = 2*yB - y[i];	
			}
		}
		if(ch2 == 2) {
			printf("Enter X :\n");
			scanf("%d",&xB);
			glColor3f(0, 1, 0);
			ddaLine(xB,-350,xB,350);
			for(int i=0; i<n; i++) {
				p[i] = 2*xB - x[i];
				q[i] = y[i];
			}
		}
		break;
	case 2:
		printf("Enter coordinates x & y :\n");
		scanf("%d %d", &xB, &yB);
		glColor3f(0, 1, 0);
    	glPointSize(5.0);
		point(xB, yB);
		for(int i=0; i<n; i++) {
			p[i] = 2*xB - x[i];
			q[i] = 2*yB - y[i];	
		}
		break;
	case 3:
		printf("Enter xB, yB :\n");
		scanf("%d %d", &xB, &yB);
		printf("Enter xE, yE :\n");
		scanf("%d %d", &xE, &yE);

		m = (yE-yB)/(float)(xE-xB);
		c = yE - m*xE;

		glColor3f(0, 1, 0);
		ddaLine(xB,yB,xE,yE);
		for(int i=0; i<n; i++) {
			p[i] = (1-m*m)*x[i]/(m*m+1) + 2*m*y[i]/(m*m+1) - 2*c*m/(m*m+1);
			q[i] = 2*m*x[i]/(m*m+1) + (m*m-1)*y[i]/(m*m+1) + 2*c/(m*m+1);	
		}
		break;
	default:
		printf("Invalid choice. Terminating...\n");
		exit(0);
	}

	float color[] = {0, 0, 1};
    glPointSize(2.0);
	polygon(p, q, color);
}