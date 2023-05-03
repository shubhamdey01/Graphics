// Cyrus-Beck algorithm

#include <GL/glut.h>
#include <stdio.h>

#define N 4
#define XMIN -100
#define YMIN -100
#define XMAX 100
#define YMAX 100

typedef struct {
    float x, y;
} Point;

void myInit(void);
void display(void);
void draw(Point, Point);
void myKey(unsigned char,int,int);
void cyrusBeck(Point, Point);

Point p1, p2;
Point ver[N] = {{-100,-100},{100,-100},{100,100},{-100,100}};

int flag;

int main(int argc, char** argv) {
    printf("Enter coordinates of the point1 :\n");
    scanf("%f %f", &p1.x, &p1.y);
    printf("\nEnter coordinates of the point2 :\n");
    scanf("%f %f", &p2.x, &p2.y);
    flag = 1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Point Clipping");
    myInit();
    glutDisplayFunc(display);

    printf("\nPress key 'C' for clipping.\n");
    glutKeyboardFunc(myKey);
    glutMainLoop();
    return 0;
}

void myInit() {
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-540.0, 540.0, -360.0, 360.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.0);
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<N; i++)
        glVertex2i(ver[i].x, ver[i].y);
    glEnd();
    glFlush();

    if(flag) {
        glPointSize(2.0);
        glColor3f(1,0,0);
        glBegin(GL_LINES);
        glVertex2f(p1.x, p1.y);
        glVertex2f(p2.x, p2.y);
        glEnd();
        glFlush();
    }
}

void draw(Point p1, Point p2) {
    glPointSize(2.0);
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}

void myKey(unsigned char key,int x,int y) {
    if(key=='c') {
        flag = 0;
        display();
        cyrusBeck(p1, p2);
        glFlush();
    }
}

float dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

Point sub(Point a, Point b) {
    Point c = {a.x - b.x, a.y - b.y};
    return c;
}

Point add(Point a, Point b) {
    Point c = {a.x + b.x, a.y + b.y};
    return c;
}

Point scale(float c, Point a)
{
    Point b = {c * a.x, c * a.y};
    return b;
}

void cyrusBeck(Point p1, Point p2) {
    Point D = sub(p2, p1);
    Point p, n;
    float t0 = 0, t1 = 1;
    float num, deno;

    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case 0:
            n = (Point){-1, 0};
            p = (Point){XMIN, YMIN};
            break;
        case 1:
            n = (Point){1, 0};
            p = (Point){XMAX, YMIN};
            break;
        case 2:
            n = (Point){0, -1};
            p = (Point){XMIN, YMIN};
            break;
        case 3:
            n = (Point){0, 1};
            p = (Point){XMIN, YMAX};
            break;
        }

        num = dot(sub(p, p1), n);
        deno = dot(D, n);

        if (deno == 0) {
            if (num < 0)
                return;
        }
        else {
            float t = num / deno;
            if (deno < 0) {
                if (t > t1)
                    return;
                else if (t > t0)
                    t0 = t;
            }
            else {
                if (t < t0)
                    return;
                else if (t < t1)
                    t1 = t;
            }
        }
    }

    Point c1 = add(p1, scale(t0, D));
    Point c2 = add(p1, scale(t1, D));
    draw(c1, c2);
}