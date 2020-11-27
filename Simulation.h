///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Simulation.h
//	------------------------
//
//	Capable of loading, rendering and updating a physically based cloth simulation
//
///////////////////////////////////////////////////

#ifndef _SIMULATION_H_
#define _SIMULATION_H_


using namespace std;

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "Cartesian3.h"
#include "camera.h"
#include "Cloth.h"
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



class Simulation
{
// constructors and destructors
public:
    ~Simulation();   // destructor

    Simulation();    // empty constructor

    Simulation( const char * objFileName ); // filename constructor

    // setup functions
    void Clear();

    void Load( const char * objFileName );

    // lets initialise this innit
    void Init();

public:
  // all our public variables and funcitons
  // that our GUI and users can call

  // used for error messages
  bool isLoadSuccess;

  // filename and motion name from file
  string fileName;
  string objName;

  // main pointers
  Cloth     *cloth;
  PointMass *ball;
  Wind      *wind;


  // for mouse interaction with the cloth
  vector<Cartesian3> globalPositions;

  // which item the user is controlling
  int activePointMass;

  // for playback
  int numFrame;
  int cFrame;
  double interval;

  // for saving loading
  std::string fileContents;

  // bools controlled by checkboxes
  bool useWind;
  bool showSphere;
  bool fixedCorners;

  // values updated from sliders
  float sphereFriction;
  float sphereSpin;
  float windSpeed;
  float gravity;

public:

  // Call For Rendering
  void Render(int frameNo, Camera *camera);

  // moves a specific part of the cloth with a force
  void MovePoint(glm::vec3 move);

  // saves the frame as a .obj
  void SaveFile(std::string fileName);

  // finds all the points in the simulation we can click on
  void FindGlobalPosition(Camera *camera);


};


#endif //_SIMULATION_H_