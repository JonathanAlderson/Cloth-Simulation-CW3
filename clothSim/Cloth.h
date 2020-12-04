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

// tiny struct for texture coordinates
struct Tex
{
  float u;
  float v;

  Tex(float uIn, float vIn)
  {
    u = uIn;
    v = vIn;
  }
};

class Cloth
{
  // constructors and destructors
  public:
      ~Cloth();   // destructor

      Cloth(const char *filename);    // empty constructor

      // setup functions
      void Reset();

  public:
    vector<PointMass> points;          // pointmasses
    vector<Spring> springs;            // connecting springs
    vector<unsigned int> vertRef;      // for rendering cloth
    vector<Tex> texCoords;             // for rendering cloth
    vector<unsigned int> saveIndicies; // so we can rewrite later
    vector<Tex> saveTexCoords;         // so we can rewrite later

    // for interacting with the cloth
    Cartesian3 mouseForce;
    int mouseTimeout;
    int mouseMaxTimeout;

    // changes the rendering mode from cloth to rods and srpings
    bool wireframeRender;
    bool useTextures;
    unsigned int activePoint;
    unsigned int lastActivePoint;

    // perform one step of physics calculations
    void Update(float dT);

    // Show the current state of the cloth
    void Render();

    void UpdateGravity(float gravity);

    // gives a force like you are dragging part of the cloth
    void ApplyForce(Cartesian3 forceIn);


};

#endif //_CLOTH_H_
