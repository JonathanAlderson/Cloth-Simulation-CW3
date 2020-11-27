///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	November, 2020
//
//	------------------------
//	Simulation.cpp
//	------------------------
//
//	Capable of loading, rendering and updating a Pysics based cloth simulation
//
///////////////////////////////////////////////////

#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include <iostream>
#include "Simulation.h"

////////////////////////////////////////////////
// CONSTRUCTORS
////////////////////////////////////////////////

// Destructor
Simulation::~Simulation()
{
  Clear();
}
// Empty Constructor
Simulation::Simulation()
{
  // reset
	Clear();

  useWind      = false;
  showSphere   = false;
  fixedCorners = false;

  sphereFriction = 1.;
  sphereSpin     = 1.;
  windSpeed      = 1.;
  gravity        = 10.; // close enough to 9.81

  Init();
}

// Constructor with file
Simulation::Simulation(const char *simFileName)
{
  // reset
	Clear();

  useWind      = false;
  showSphere   = false;
  fixedCorners = false;

  sphereFriction = 1.;
  sphereSpin     = 1.;
  windSpeed      = 1.;
  gravity        = 10.; // close enough to 9.81

  // finally load the file
  Load(simFileName);

  Init();
}

// set everything up how we like
void Simulation::Init()
{
  // make a test mesh that's very small
  // Cartesian3 a = Cartesian3(0., 1., 0.);
  // Cartesian3 b = Cartesian3(1., 1., 0.);
  //
  // std::vector<Cartesian3> clothMesh;
  // clothMesh.push_back(a);
  // clothMesh.push_back(b);
  //
  // cloth = new Cloth(&clothMesh);
}

// Reset Function to Dump All The Clears In
void  Simulation::Clear()
{
	isLoadSuccess = false;

	fileName = "";
	objName = "";

	globalPositions.clear();

  // set default values
  numFrame = 0;
  cFrame   = 0;
  interval = 1./ 60.;
}

// Calculates where we are allowed to click
void Simulation::FindGlobalPosition(Camera *camera)
{
  globalPositions.push_back(Cartesian3(1., 1., 1.));
}

// large render call, renders all the objects in the scene
void Simulation::Render(int frameNo, Camera *camera)
{

  std::cout << "\n\n\nG: " << gravity << '\n';
  std::cout << "WS: " << windSpeed << '\n';
  std::cout << "SS: " << sphereSpin << '\n';
  std::cout << "SF: " << sphereFriction << '\n';
  // cloth->Render();
  // ball->Render();
  // wind->Render();

}

// loads a file in and you know, loads it in and stuff
void Simulation::Load(char const *)
{

}

// saves the info on the current frame as a file
void Simulation::SaveFile(std::string fileName)
{
  ofstream  file;
  file.open(fileName);

  // write file contents
  //fileContents
  file << fileContents;

  std::cout << "Saved File" << '\n';
}
