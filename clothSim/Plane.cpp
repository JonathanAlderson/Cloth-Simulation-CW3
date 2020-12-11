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

Plane::Plane(Cartesian3 centerIn, float widthIn, float heightIn, float frictionIn)
{
  center = centerIn;
  width = widthIn;
  height = heightIn;

  // for collision detection
  delta = 0.4;

  friction = frictionIn;



}

void Plane::Collision(PointMass *p)
{



  // if at the right height
  if(BoundsCheck(p->pos))
  {
    // set position
    p->pos.y = center.y + delta;

    // add an external force upwards
    // and a frictional force
    p->eForces[COLLISION] = Cartesian3(0., -p->eForces[GRAVITY].y, 0.);

    // friction will resist the motion in the opposite direction of the total force
    p->eForces[PFRICTION] = Cartesian3(abs(friction * p->eForces[GRAVITY].y) * -p->vel.x, 0., abs(friction * p->eForces[GRAVITY].y) * -p->vel.z);
  }

  else
  {
    // reset external forces
    p->eForces[COLLISION] = Cartesian3(0., 0., 0.);
    p->eForces[PFRICTION]  = Cartesian3(0., 0., 0.);
  }
}

bool Plane::BoundsCheck(Cartesian3 pos)
{
  bool ret = false;

  // if at the right height
  if(pos.y <= center.y + delta && pos.y > center.y - 2.*delta)
  {
    // if in the bounding box
    if(pos.x > center.x - width && pos.x < center.x + width && pos.z > center.z - height && pos.z < center.z + height)
    {
      ret = true;
    }
  }

  return ret;
}

void Plane::Render()
{
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  // plane colour goes from red to blue depending on friction
  glColor3f(friction, 0.0, (1. - friction));
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
  glEnable(GL_TEXTURE_2D);
}
