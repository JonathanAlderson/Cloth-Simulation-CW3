///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	PointMass.h
//	------------------------
//
//	Renders and Simluates a PointMass, where external forces can be applied
//
///////////////////////////////////////////////////

#ifndef _POINTMASS_H_
#define _POINTMASS_H_

using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "camera.h"
#include "PointMass.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// openGL includes
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

// forward decleration of Spring
class Spring;

class PointMass
{
public:
  ~PointMass();   // destructor

   PointMass(Cartesian3 position, float massIn);    // empty constructor

  // resets all the forces acting on the PointMass
  void Reset();

  // colour changes depending on forces applied
  void CalculateColour();

  // sums all the forces and find the total
  void CalculateTotalForce();

  // if we are going to render the ball or not
  bool rendered;

  // if we can move the point mass
  bool fixed;

  // all the springs that are attached to the ball
  std::vector<Spring *> springs;

public:

  // current position
  Cartesian3 pos;

  // current colour
  Cartesian3 col;

  // mass of the ball
  float mass;

  // external forces (usually empty)
  std::vector<Cartesian3> eForces;

  // total force acting on the object
  Cartesian3 cForce;

  // acceleration and velocity (initalised as 0)
  Cartesian3 vel;
  Cartesian3 acc;

  // has not update function and is handed by the simulation class

  // render a ball at position
  // colour indicates external forces
  void Render();

};

#endif // _POINTMASS_H_
