///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Sphere.h
//	------------------------
//
//	Simple class to draw a ball and handle physics
//
///////////////////////////////////////////////////

#ifndef _SPHERE_H_
#define _SPHERE_H_

using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "camera.h"
#include "Spring.h"
#include "PointMass.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Sphere
{
public:
  ~Sphere(); // destructor

   Sphere(float frictionIn, float spinIn, Cartesian3 positionIn, float radiusIn); // constructor

   // reset
   void Reset();

   // internal clock
   float cTime;

   // pos
   Cartesian3 pos;
   float rotation;

   // radius
   float radius;

   // if it is in the scene or not
   bool show;

   // how fast the ball rotates
   float spin;
   float friction;

   // shows a ball
   void Render();

   // Spins a Little Bit
   void Update(float dT);

   // Checks for collision
   void Collision(PointMass  *p);
};

#endif // _SPHERE_H_
