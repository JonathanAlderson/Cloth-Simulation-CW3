///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	PointMass.cpp
//	------------------------
//
//	Renders and Simluates a PointMass, where external forces can be applied
//
///////////////////////////////////////////////////

#include "PointMass.h"

PointMass::PointMass(Cartesian3 position)
{
  // reset forces etc
  Reset();

  // set postion
  pos = position;
}

PointMass::~PointMass()
{
  // how do you write destructors
}

// reset all forces
void PointMass::Reset()
{
  for(unsigned int i = 0; i < eForces.size(); i++)
  {
    eForces[i] == Cartesian3(0., 0., 0.);
  }
}

// renders a ball
void PointMass::Render()
{
  GLUquadric *quad;
  quad = gluNewQuadric();

  // save current state
  glPushMatrix();

  // set col
  glColor3f(0., 0.6, 0.);

  // Find the global position to draw the point
  glTranslatef(pos.x, pos.y, pos.z);
  gluSphere(quad, .5, 15, 15);
  glPopMatrix();
}
