// C program to demonstrate 
// drawing a circle using 
// OpenGL 
#include<stdio.h> 
#include<GL/glut.h>

#define FOV 60
#define WIDTH 800
#define HEIGHT 600

// function to initialize 
void ChangeSize(int w, int h)  
    {  
    GLfloat fAspect;  
  
    // Prevent a divide by zero  
    if(h == 0)  
        h = 1;  
  
    // Set Viewport to window dimensions  
    glViewport(0, 0, w, h);  
  
    fAspect = (GLfloat)w/(GLfloat)h;  
  
    // Reset coordinate system  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
  
    // Produce the perspective projection  
    gluPerspective(35.0f, fAspect, 1.0, 40.0);  
  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
} 

void display (void) 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLUquadricObj *pObj;

    // Create a sphere
    glPushMatrix();
    glTranslatef(0.0f, -6.0f, -20.0f);
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glColor3f(1.0f, 1.0f, 1.0f);
    gluSphere(pObj, 1.0, 25, 25);
    glPopMatrix();

    glPopMatrix();
	glutSwapBuffers();
} 

int main (int argc, char** argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	
	// giving window size in X- and Y- direction 
	glutInitWindowSize(WIDTH, HEIGHT); 
	glutInitWindowPosition(0, 0); 
	
	// Giving name to window 
	glutCreateWindow("Sphere Drawing");
    glutReshapeFunc(ChangeSize);
	
	glutDisplayFunc(display); 
	glutMainLoop(); 
} 
