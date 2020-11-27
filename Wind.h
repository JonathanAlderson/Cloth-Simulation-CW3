///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Wind.h
//	------------------------
//
//	Very simple class to add forces
//
///////////////////////////////////////////////////

#ifndef _WIND_H_
#define _WIND_H_

using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "camera.h"
#include "PointMass.h"
#include "Spring.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

class Wind
{
public:
  ~Wind(); // destructor

   Wind(Cartesian3 origin, Cartesian3 direction, float speed); // constructor

   // reset
   void Reset();

   Cartesian3 origin;
   Cartesian3 direction;
   float speed;

   // shows a big arrow for the wind direction
   void Render();

   // calculates how much force the wind gives to a
   // point in 3D space
   Cartesian3 Force(Cartesian3 target);
};

#endif // _WIND_H_
