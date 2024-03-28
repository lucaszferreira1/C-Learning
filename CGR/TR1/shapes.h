#ifndef SHAPES_H
#define SHAPES_H

void drawBox(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]);
void drawPyramid(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]);
void drawCylinder(float radius, float height, int slices, int stacks);
void drawPrism(float x1, float y1, float z1, float x2, float y2, float z2, float color[3]);

#endif