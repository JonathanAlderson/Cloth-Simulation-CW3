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

#ifndef _PLANE_H_
#define _PLANE_H_

using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "PointMass.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Plane
{
  public:

    ~Plane(); // destructor

    Plane(Cartesian3 centerIn, float widthIn, float heightIn, float frictionIn);

    // Renders the Plane
    void Render();


    // Checks for a collision against p
    void Collision(PointMass *p);

    // bounds check
    bool BoundsCheck(Cartesian3 pos);

    // plane dimensions
    Cartesian3 center;
    float width;
    float height;

    // for collision detection
    float delta;
    float friction;
};

#endif // _PLANE_H_
