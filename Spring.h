///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Spring.h
//	------------------------
//
//	Springs are really useful for lots of things.
//  You know, they spring this way and that way,
//  someone just sells a spring as a toy,
//  miilions of purchases to play with a spring?
//  I know, it sounds crazy, but paint it in a rainbow
//  and you've got yourself a slinky. - JJ Abrams
//
///////////////////////////////////////////////////

#ifndef _SPRING_H_
#define _SPRING_H_

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

class Spring
{
public:
  ~Spring();   // destructor

  Spring(PointMass *a, PointMass *b, float springK);    // empty constructor

  // resets all the forces acting on the PointMass
  void Reset();

public:

  // who is connecting it
  PointMass *pmA;
  PointMass *pmB;
  float springConst; // springiness of the spring
  float lr;          // rest length
  float lc;          // current length


  // render options
  GLdouble radius;
  GLdouble slices;
  GLdouble stack;

  // does a pysics calculation based on distacnes of Pointmasses
  void Update();

  // render a spring at position
  // colour indicates external forces
  void Render();

};

#endif // _SPRING_H_
