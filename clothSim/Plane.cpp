///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Plane.h
//	------------------------
//
//	Very simple plane class to handle collisions with cloths
//
///////////////////////////////////////////////////

#include "Plane.h"

Plane::Plane(Cartesian3 centerIn, float widthIn, float heightIn)
{
  center = centerIn;
  width = widthIn;
  height = heightIn;
}

void Plane::Collision(PointMass *p)
{

  float delta = 0.5;

  float r = 5000. * float(rand() / RAND_MAX);

  if(p->pos.y <= center.y)
  {
    p->pos.y = center.y + delta;
    p->acc = Cartesian3(0., 0., 0.);
    p->vel = Cartesian3(r, 0., -r);
  }
}

void Plane::Render()
{
  glDisable(GL_LIGHTING);
  glBegin(GL_TRIANGLES);
  // glPushMatrix();
  //
  // glTranslatef(center.x, center.y, center.z);

  // dark blue plane
  glColor3f(0., 0.8, 0.8);
  glNormal3f(0., 1., 0.); // static normal

  // lower triangle
  glVertex3f(center.x - width, center.y, center.z - height);
  glVertex3f(center.x - width, center.y, center.z + height);
  glVertex3f(center.x + width, center.y, center.z - height);

  // upper triangle
  glVertex3f(center.x - width, center.y, center.z + height);
  glVertex3f(center.x + width, center.y, center.z + height);
  glVertex3f(center.x + width, center.y, center.z - height);

  glEnd();
  glEnable(GL_LIGHTING);
  //glPopMatrix();

  std::cout << "Render Plane" << '\n';
}
