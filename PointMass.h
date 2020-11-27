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
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

// openGL includes
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

class PointMass
{
public:
  ~PointMass();   // destructor

   PointMass(Cartesian3 position);    // empty constructor

  // resets all the forces acting on the PointMass
  void Reset();

public:

  // current position
  Cartesian3 pos;

  // external forces (usually empty)
  std::vector<Cartesian3> eForces;

  // no update function as the springs handle that

  // render a ball at position
  // colour indicates external forces
  void Render();

};

#endif // _POINTMASS_H_
