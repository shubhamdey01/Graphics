// Cyrus-Beck algorithm

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x, y;
} Point;

void myInit(void);
void display(void);
void draw(float, float, Point);
void myKey(unsigned char,int,int);
void cyrusBeck(Point, Point, Point*, Point*, int);

Point p1, p2;
Point *n, *W;

int flag, N;

int main(int argc, char** argv) {
    int i;
    printf("Enter no. of vertices of the clipping window : \t");
    scanf("%d", &N);

    W = (Point*)calloc(N, sizeof(Point));
    n = (Point*)calloc(N, sizeof(Point));

    printf("Enter the vertices in clockwise direction :\n");
    for(i=0; i<N; i++) {
        printf("V%d :\t", i+1);
        scanf("%f %f", &W[i].x, &W[i].y);
    }

    for(i=0; i<N; i++) {
        n[i] = (Point){W[(i+1)%N].y-W[i].y, -(W[(i+1)%N].x-W[i].x)};
        // f[i] = 
    }


    printf("\nEnter coordinates of the point1 :\n");
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
    glLineWidth(2.0); 
    glLoadIdentity();
    gluOrtho2D(-540.0, 540.0, -360.0, 360.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(2.0);
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<N; i++)
        glVertex2i(W[i].x, W[i].y);
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

void draw(float tl, float tu, Point D) {
    Point a, b;
    a = (Point){p1.x + D.x*tl, p1.y + D.y*tl};
    b = (Point){p1.x + D.x*tu, p1.y + D.y*tu};

    p1 = a; p2 = b;
}

void myKey(unsigned char key,int x,int y) {
    if(key=='c') {
        flag = 0;
        display();
        cyrusBeck(p1, p2, n, W, N);
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

void cyrusBeck(Point p1, Point p2, Point *n, Point *f, int k) {
    Point D, w;
    float tl = 0, tu = 1, t, num, deno;
    D = sub(p2, p1);
    for(int i=0; i<k; i++) {
        w = sub(p1, f[i]);
        num = dot(w, n[i]);
        deno = dot(D, n[i]);

        if(deno != 0) {
            t = -num/deno;
            if(deno > 0) {
                if(t > 1)
                    flag = 0;
                else
                    tl = (t > tl) ? t : tl;
            }
            else {
                if(t < 0)
                    flag = 0;
                else
                    tu = (t < tu) ? t : tu;
            }
        }
        else {
            if(num < 0)
                flag = 0;
        }
    }
    if(tl <= tu)
        flag = 1;
    draw(tl, tu, D);
    display();
}