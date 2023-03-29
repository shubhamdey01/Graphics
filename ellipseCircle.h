#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void circle(int, int, int);
void plotCircle(int, int, int, int);
void ellipse(int, int, int, int);
void plotEllipse(int, int, int, int);

void circle(int a, int b, int r1) {
	int x = 0;
	int y = r1;
	int p = 1 - r1;
	plotCircle(a, b, x, y);

	while (y > x) {
		x++; 
		if (p < 0) {
			p += 2*x+1;
		}
		else {
			y--;
			p += 2*(x-y)+1;
		}
		plotCircle(a, b, x, y);
	}
}

void plotCircle(int a, int b, int x, int y) {
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

void ellipse(int a, int b, int rx, int ry) {
	int rx2 = rx*rx;
	int ry2 = ry*ry;
    int Trx2 = 2*rx2;
    int Try2 = 2*ry2;
	int p;
    int x = 0;
    int y = ry;
    int px = 0;
    int py = Trx2 * y;
	plotEllipse(a, b, x, y);

    // Region 1
    p = (int)(ry2-(rx2*ry)+(0.25*rx2));
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
		plotEllipse(a, b, x, y);
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
		plotEllipse(a, b, x, y);
	}
}

void plotEllipse(int a, int b, int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(a+x, b+y);
	glVertex2i(a-x, b+y);
	glVertex2i(a+x, b-y);
	glVertex2i(a-x, b-y);
	glEnd();
    glFlush();
}