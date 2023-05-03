// Midpoint Subdivision algorithm

#include <GL/glut.h>
#include <stdio.h>

#define Xmin -100
#define Xmax 100
#define Ymin -100
#define Ymax 100

#define TOP 8
#define BOTTOM 4
#define RIGHT 2
#define LEFT 1

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

typedef struct {
    float x, y;
} Point;

void myInit(void);
void display(void);
void draw(Point, Point);
void myKey(unsigned char,int,int);
int endCode(int, int);
Point mid(Point p1, Point p2);
float dist(Point t1, Point t2);
void midPointSub(Point, Point);

Point p1, p2;
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
    glVertex2i(Xmin,Ymin);
    glVertex2i(Xmin,Ymax);
    glVertex2i(Xmax,Ymax);
    glVertex2i(Xmax,Ymin);
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
        midPointSub(p1, p2);
        glFlush();
    }
}

int endCode(int x, int y) {
    int c = 0;
    if(x < Xmin)
        c |= LEFT;
    if(x > Xmax)
        c |= RIGHT;
    if(y < Ymin)
        c |= BOTTOM;
    if(y > Ymax)
        c |= TOP;
    return c;
}

Point mid(Point p1, Point p2) {
    Point m;
    m.x=(p1.x+p2.x)/2;
    m.y=(p1.y+p2.y)/2;
    return m;
}

float dist(Point t1, Point t2) {
    float dsx=t1.x-t2.x,dsy=t1.y-t2.y,ds;
    ds=dsx>dsy?dsx:dsy;
    return ds;
}

void midPointSub(Point p1, Point p2) {
    Point m;
    int code1, code2, code;
    if(p1.x > p2.x) {
        m = p1;
        p1 = p2;
        p2 = m;
    }
    code1 = endCode((int)p1.x, (int)p1.y);
    code2 = endCode((int)p2.x, (int)p2.y);
    if(REJECT(code1, code2)) {
        return;
    }
    else if(ACCEPT(code1, code2)) {
        draw(p1, p2);
    }
    else {
        m = mid(p1, p2);
        if(dist(m, p1)>=1 || dist(m, p2)>=1) {
            code = endCode((int)m.x, (int)m.y);
            if(INSIDE(code)) {
                if(INSIDE(code1)) {
                    draw(p1, m);
                    midPointSub(m, p2);
                }
                else if(INSIDE(code2)) {
                    draw(p2, m);
                    midPointSub(p1, m);
                }
                else {
                    midPointSub(p1, m);
                    midPointSub(m, p2);
                }
            }
            else {
                if(REJECT(code1, code))
                    p1 = m;
                else if(REJECT(code2, code))
                    p2 = m;
                midPointSub(p1, p2);
            }
        }
    }
}