#include "shapes.h"
#include <GL/freeglut.h>

void drawBox(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]){
    // Set color
    glColor3f(color[0], color[1], color[2]);

    // Draw box
    
    // Front face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x1, y2, z1);
    glEnd();

    // Back face
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);
    glEnd();

    // Left face
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x1, y2, z1);
    glVertex3f(x1, y2, z2);
    glVertex3f(x1, y1, z2);
    glEnd();

    // Right face
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x2, y1, z2);
    glEnd();

    // Top face
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(x1, y2, z1);
    glVertex3f(x2, y2, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x1, y2, z2);
    glEnd();

    // Bottom face
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glEnd();
}
void drawPyramid(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]) {
    // Set color
    glColor3f(color[0], color[1], color[2]);

    // Draw pyramid
    
    // Front face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f((x1 + x2) / 2, y2, (z1 + z2) / 2);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glEnd();

    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f((x1 + x2) / 2, y2, (z1 + z2) / 2);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glEnd();

    // Right face
    glBegin(GL_TRIANGLES);
    glNormal3f(1, 0, 0);
    glVertex3f((x1 + x2) / 2, y2, (z1 + z2) / 2);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glEnd();

    // Left face
    glBegin(GL_TRIANGLES);
    glNormal3f(-1, 0, 0);
    glVertex3f((x1 + x2) / 2, y2, (z1 + z2) / 2);
    glVertex3f(x1, y1, z2);
    glVertex3f(x1, y1, z1);
    glEnd();

    // Draw base
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glVertex3f(x2, y1, z2);
    glVertex3f(x1, y1, z2);
    glEnd();
}
void drawCylinder(float radius, float height, int slices, int stacks) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, stacks);
    gluDeleteQuadric(quad);
}
void drawPrism(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]) {
    // Draw base
    drawBox(x1, y1, z1, x2, y1, z2, color);

    // Draw Faces
    glColor3f(color[0], color[1], color[2]);
    // Back face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, -1);
    glVertex3f((x1 + x2) / 2, y2, z1);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y1, z1);
    glEnd();

    // Front face
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1);
    glVertex3f((x1 + x2) / 2, y2, z2);
    glVertex3f(x1, y1, z2);
    glVertex3f(x2, y1, z2);
    glEnd();

    // // Right Face
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f((x1 + x2) / 2, y2, z1);
    glVertex3f((x1 + x2) / 2, y2, z2);
    glVertex3f(x1, y1, z2);
    glEnd();

    // Left Face
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(x2, y1, z1);
    glVertex3f((x1 + x2) / 2, y2, z1);
    glVertex3f((x1 + x2) / 2, y2, z2);
    glVertex3f(x2, y1, z2);
    glEnd();
}