#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

void draw(void);
void myInit(void);
void bresenhem(int, int, int, int);

int a, b, c, d;

void display(void) {
    
}
int main(int argc, char** argv) {
	printf("Enter X1 :\t");
	scanf("%d", &a);
	printf("Enter Y1 :\t");
	scanf("%d", &b);
	printf("\nEnter X2 :\t");
	scanf("%d", &c);
	printf("Enter Y2 :\t");
	scanf("%d", &d);


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
	bresenhem(a, b, c, d);
}

void bresenhem(int x1, int y1, int x2, int y2) {
	int x, y, dx, dy, pk, k;
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    dx = x2 - x1;
    dy = y2 - y1;
    pk = 2 * dy - dx;
    x = x1;
    y = y1;
    for (k = 0; k < dx - 1; ++k) {
		if (pk < 0) {
		pk = pk + 2 * dy;
		} else {
		pk = pk + 2 * dy - 2 * dx;
		++y;
		}
		++x;
		// printf("k=%d, pk=%d, x%d=%d, y%d=%d\n",k,pk,k,x,k,y);
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
    }
    glFlush();
}