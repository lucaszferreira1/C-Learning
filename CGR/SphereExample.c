// C program to demonstrate 
// drawing a circle using 
// OpenGL 
#include<stdio.h> 
#include<GL/glut.h>

#define FOV 60
#define WIDTH 800
#define HEIGHT 600
#define ASPECT_RATIO 4/3

void init();
void display();
void idle();

struct TVector{
    double x, y, z;
};

struct TObject3D{
    struct TVector position;
    struct TVector velocity;
};

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, ASPECT_RATIO, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glColor3f(0.0f, 0.0f, 0.0f);
}

void display (void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLUquadricObj *pObj;

    // Create a sphere
    glPushMatrix();
    glTranslatef(0.0f, -1.0f, -3.0f);
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(pObj, 1.0, 25, 25);
    glPopMatrix();

    glPopMatrix();
	glutSwapBuffers();
}

void idle(){
    // runPhysics();
    display();
}

int main (int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	
	// giving window size in X- and Y- direction 
	glutInitWindowSize(WIDTH, HEIGHT); 
	glutInitWindowPosition(50, 50); 
	
	// Giving name to window 
	glutCreateWindow("Sphere Drawing");
    
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0, 0, WIDTH, HEIGHT);
    init();
	 
	glutMainLoop(); 
} 
