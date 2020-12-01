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
#include "Spring.h"

PointMass::PointMass(Cartesian3 position, float massIn)
{
  // reset forces etc
  Reset();

  fixed = false;

  // set postion
  pos = position;

  // set the mass
  mass = massIn;

  // set default velocities and accelerations
  vel = Cartesian3(0., 0, 0);
  acc = Cartesian3(0., 0, 0);

}

PointMass::~PointMass()
{
  // how do you write destructors
}

// reset all forces
void PointMass::Reset()
{
  // reserve 4 spaces in springs
  springs.reserve(4);
  for(unsigned int i = 0; i < eForces.size(); i++)
  {
    eForces[i] == Cartesian3(0., 0., 0.);
  }
  CalculateColour();
}

// updates the colour depending on the forces applied
void PointMass::CalculateTotalForce()
{
  cForce = Cartesian3(0., 0., 0.);

  // sum up the external forces acting on the point mass
  for(unsigned int i = 0; i < eForces.size(); i++)
  {
     cForce = cForce + eForces[i];
  }

  // sum up the forces of the springs connected to the point mass
  for(unsigned int i = 0; i < springs.size(); i++)
  {
    // pmA --> left hand side
    if(this == springs[i]->pmA)  cForce = cForce - springs[i]->force;
    // pmB --> Right Hand Size
    else                         cForce = cForce + springs[i]->force;
   }
}


void PointMass::CalculateColour()
{
  float maxForce = 50.;
  float cForceFloat = abs(cForce.x) + abs(cForce.y) + abs(cForce.z);
  float ratio;

  ratio = cForceFloat / maxForce;

  // 1. if no forces
  ratio = 1. - ratio;

  // point masses get bluer as more force is applied to them
  col = Cartesian3(ratio, 1., ratio);
  

  if(fixed){ col = Cartesian3(0., .7, .7); }
}


// renders a ball
void PointMass::Render()
{
  // Find out what colour we need to be this frame
  CalculateColour();

  GLUquadric *quad;
  quad = gluNewQuadric();

  // save current state
  glPushMatrix();

  // set col depending on the forces acting on it
  glColor3f(col.x, col.y, col.z);

  // Find the global position to draw the point
  glTranslatef(pos.x, pos.y, pos.z);
  gluSphere(quad, .25, 15, 15);
  glPopMatrix();
}
