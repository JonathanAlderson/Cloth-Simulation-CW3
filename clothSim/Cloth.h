///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Cloth.h
//	------------------------
//
//	Renders and Simluates a Cloth
//
///////////////////////////////////////////////////

#ifndef _CLOTH_H_
#define _CLOTH_H_


using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "camera.h"
#include "PointMass.h"
#include "Spring.h"
#include "Wind.h"
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


class Cloth
{
  // constructors and destructors
  public:
      ~Cloth();   // destructor

      Cloth(const char *filename);    // empty constructor

      // setup functions
      void Reset();

  public:
    vector<PointMass> points;
    vector<Spring> springs;

    // perform one step of physics calculations
    void Update(float dT);

    // Show the current state of the cloth
    void Render();

    // gives a force like you are dragging part of the cloth
    void ApplyForce(Cartesian3 forceIn);

    // which point we are dragging
    unsigned int activePoint;
};

#endif //_CLOTH_H_
