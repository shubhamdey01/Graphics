#include<stdio.h>
#include<GL/glut.h>
#include<math.h> 

int choice, choice1, choice2, choice3, xaux[8], yaux[8], zaux[8], i; 
int x[8] = {20, 120, 120, 20, 0, 100, 100, 0};
int y[8] = {70, 70, 20, 20, 50, 50, 0, 0};
int z[8] = {0, 0, 0, 0, 150, 150, 150, 150};

void init()
{
    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-500, 500,-500, 500, -500, 500);
}

void display() 
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowPosition(500,100);
    glutInitWindowSize(1000,750);
    glutCreateWindow("3D Transformations");
    init();

    // Drawing initial polygon
    glColor3f(0, 0, 1);                              
    glLineWidth(2.0);   

    // TOP BAEF
    glBegin(GL_LINE_LOOP);                                                           
        glVertex3f(x[1], y[1], z[1]);
        glVertex3f(x[0], y[0], z[0]);  
        glVertex3f(x[4], y[4], z[4]);
        glVertex3f(x[5], y[5], z[5]);  
    glEnd();

    // BOTTOM GHDC
    glBegin(GL_LINE_LOOP);
        glVertex3f(x[6], y[6], z[6]);
        glVertex3f(x[7], y[7], z[7]);  
        glVertex3f(x[3], y[3], z[3]);
        glVertex3f(x[2], y[2], z[2]);
    glEnd();

    // FRONT FEHG
    glBegin(GL_LINE_LOOP);
        glVertex3f(x[5], y[5], z[5]);  
        glVertex3f(x[4], y[4], z[4]);
        glVertex3f(x[7], y[7], z[7]);  
        glVertex3f(x[6], y[6], z[6]);
    glEnd();

    // BACK CDAB
    glBegin(GL_LINE_LOOP);
        glVertex3f(x[2], y[2], z[2]);
        glVertex3f(x[3], y[3], z[3]);
        glVertex3f(x[0], y[0], z[0]);  
        glVertex3f(x[1], y[1], z[1]);
    glEnd();

    // LEFT EADH
    glBegin(GL_LINE_LOOP);
        glVertex3f(x[4], y[4], z[4]);
        glVertex3f(x[0], y[0], z[0]);  
        glVertex3f(x[3], y[3], z[3]);
        glVertex3f(x[7], y[7], z[7]);  
    glEnd();

    // RIGHT BFGC
    glBegin(GL_LINE_LOOP);
        glVertex3f(x[1], y[1], z[1]);
        glVertex3f(x[5], y[5], z[5]);  
        glVertex3f(x[6], y[6], z[6]);
        glVertex3f(x[2], y[2], z[2]);
    glEnd();

    // Drawing polygon after transformation                                    
    glColor3f(1, 0, 0);                 
    glLineWidth(2.0);                                                            
    // TOP BAEF
    glBegin(GL_LINE_LOOP);                                                           
        glVertex3f(xaux[1], yaux[1], zaux[1]);
        glVertex3f(xaux[0], yaux[0], zaux[0]);  
        glVertex3f(xaux[4], yaux[4], zaux[4]);
        glVertex3f(xaux[5], yaux[5], zaux[5]);  
    glEnd();

    // BOTTOM GHDC
    glBegin(GL_LINE_LOOP);
        glVertex3f(xaux[6], yaux[6], zaux[6]);
        glVertex3f(xaux[7], yaux[7], zaux[7]);  
        glVertex3f(xaux[3], yaux[3], zaux[3]);
        glVertex3f(xaux[2], yaux[2], zaux[2]);
    glEnd();

    // FRONT FEHG
    glBegin(GL_LINE_LOOP);
        glVertex3f(xaux[5], yaux[5], zaux[5]);  
        glVertex3f(xaux[4], yaux[4], zaux[4]);
        glVertex3f(xaux[7], yaux[7], zaux[7]);  
        glVertex3f(xaux[6], yaux[6], zaux[6]);
    glEnd();

    // BACK CDAB
    glBegin(GL_LINE_LOOP);
        glVertex3f(xaux[2], yaux[2], zaux[2]);
        glVertex3f(xaux[3], yaux[3], zaux[3]);
        glVertex3f(xaux[0], yaux[0], zaux[0]);  
        glVertex3f(xaux[1], yaux[1], zaux[1]);
    glEnd();

    // LEFT EADH
    glBegin(GL_LINE_LOOP);
        glVertex3f(xaux[4], yaux[4], zaux[4]);
        glVertex3f(xaux[0], yaux[0], zaux[0]);  
        glVertex3f(xaux[3], yaux[3], zaux[3]);
        glVertex3f(xaux[7], yaux[7], zaux[7]);  
    glEnd();

    // RIGHT BFGC
    glBegin(GL_LINE_LOOP);
        glVertex3f(xaux[1], yaux[1], zaux[1]);
        glVertex3f(xaux[5], yaux[5], zaux[5]);  
        glVertex3f(xaux[6], yaux[6], zaux[6]);
        glVertex3f(xaux[2], yaux[2], zaux[2]);
    glEnd();

    glFlush();
    glutMainLoop();
}

void translation()
{
    printf("\n\nTRANSLATION\n");
    int T[3];
    printf("Enter translation factor (dx dy dz): ");
    scanf("%d%d%d",&T[0],&T[1],&T[2]);
    for(i=0; i<8; i++)
    {
        xaux[i] = x[i] + T[0];               
        yaux[i] = y[i] + T[1];
        zaux[i] = z[i] + T[2];
    }
    display();
}

void rotation()
{
    int angle;
    printf("\n\nOPERATIONS FOR ROTATION\n\n1. About X-AXIS\n2. About Y-AXIS\n3. About Z-AXIS\n\nEnter your choice: ");
    scanf("%d",&choice1);
    printf("Enter angle of rotation (in degree): ");
    scanf("%d",&angle);
    switch(choice1)
    {
        case 1:
        {
            printf("\n\nROTATION ABOUT X-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i];
                yaux[i] = (y[i] * cos(angle * 3.14/180)) - (z[i] * sin(angle * 3.14/180));
                zaux[i] = (y[i] * sin(angle * 3.14/180)) + (z[i] * cos(angle * 3.14/180));
            }
            display();
        }
        case 2: 
        {
            printf("\n\nROTATION ABOUT Y-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = (z[i] * sin(angle * 3.14/180)) + (x[i] * cos(angle * 3.14/180));
                yaux[i] = y[i];
                zaux[i] = (y[i] * cos(angle * 3.14/180)) - (x[i] * sin(angle * 3.14/180));
            }
            display();
        }
        case 3:
        {
            printf("\n\nROTATION ABOUT Z-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = (x[i] * cos(angle * 3.14/180)) - (y[i] * sin(angle * 3.14/180));
                yaux[i] = (x[i] * sin(angle * 3.14/180)) + (y[i] * cos(angle * 3.14/180));
                zaux[i] = z[i];
            }
            display();
        }
        default: printf("Wrong Choice\n"); break;
    }
}

void scaling()
{
    printf("\n\nSCALING\n");
    int SCALE[3];   
    printf("Enter the scaling factor (dx dy dz): ");
    scanf("%d%d%d",&SCALE[0],&SCALE[1],&SCALE[2]);                   
    for(i=0; i<8; i++)
    {
        xaux[i] = x[i] * SCALE[0];                         
        yaux[i] = y[i] * SCALE[1];
        zaux[i] = z[i] * SCALE[2];
    }
    display();
}

void reflection()
{
    printf("\n\nOPERATIONS FOR REFLECTION\n\n1. About XY-Plane\n2. About YZ-Plane\n3. About ZX-Plane\n\nEnter your choice: ");
    scanf("%d",&choice2);
    switch(choice2)
    {
        case 1:
        {
            printf("\n\nREFLECTION ABOUT XY-PLANE\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i];
                yaux[i] = y[i];
                zaux[i] = -z[i];
            }
            display();
        }
        case 2: 
        {
            printf("\n\nREFLECTION ABOUT YZ-PLANE\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = -x[i];
                yaux[i] = y[i];
                zaux[i] = z[i];
            }
            display();
        }
        case 3:
        {
            printf("\n\nREFLECTION ABOUT ZX-PLANE\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i];
                yaux[i] = -y[i];
                zaux[i] = z[i];
            }
            display();
        }
        default: printf("Wrong Choice\n"); break;
    }
}

void shearing()
{
    int SHEAR[3];
    printf("\n\nOPERATIONS FOR SHEARING\n\n1. About X-Axis\n2. About Y-Axis\n3. About Z-Axis\n\nEnter your choice: ");   
    scanf("%d",&choice3); 
    printf("Enter the shearing factor (sx sy sz): ");
    scanf("%d%d%d",&SHEAR[0],&SHEAR[1],&SHEAR[2]);
    
    switch(choice3)
    {
        case 1:
        {
            printf("\n\nSHEARING ABOUT X-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i];
                yaux[i] = y[i]  + SHEAR[1] * x[i];
                zaux[i] = z[i]  + SHEAR[2] * x[i];
            }
            display();
        }
        case 2: 
        {
            printf("\n\nSHEARING ABOUT Y-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i]  + SHEAR[0] * y[i];
                yaux[i] = y[i];
                zaux[i] = z[i]  + SHEAR[2] * y[i];
            }
            display();
        }
        case 3:
        {
            printf("\n\nSHEARING ABOUT Z-AXIS\n");
            for(i=0; i<8; i++)
            {
                xaux[i] = x[i]  + SHEAR[0] * z[i];
                yaux[i] = y[i]  + SHEAR[1] * z[i];
                zaux[i] = z[i];
            }
            display();
        }
        default: printf("Wrong Choice\n"); break;
    }
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);

    printf("Before transformation color - Blue\n");
    printf("After transformation color - Red\n");
    printf("Range of x and y is -500 to 500\n\n");

    // printf("Enter the coordinates in clockwise/anti-clockwise order:-\n");
    // for(i=0; i<8; i++)
    // {
    //     printf("Vertex %d: ",i+1);
    //     scanf("%d%d%d",&x[i],&y[i],&z[i]);
    // }
   
    printf("\n3D TRANSFORMATION\n\n1. Translation\n2. Rotation\n3. Scaling\n4. Reflection\n5. Shearing\n\nEnter your choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: 
            translation(); 
            break;
        case 2: 
            rotation(); 
            break;
        case 3: 
            scaling(); 
            break;
        case 4: 
            reflection(); 
            break;
        case 5: 
            shearing(); 
            break;
        default: 
            printf("Wrong Choice\n"); 
            break;
    }
    return 0; 
}