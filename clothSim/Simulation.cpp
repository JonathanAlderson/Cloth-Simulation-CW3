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

  // init cloth with obj file
  cloth = new Cloth(simFileName);

  Init();
}

// set everything up how we like
void Simulation::Init()
{
}

// Reset Function to Dump All The Clears In
void  Simulation::Clear()
{
	isLoadSuccess = false;

	fileName = "";
	objName = "";

	globalPositions.clear();

  // set default values
  numFrame = 5000;
  cFrame   = 0;
  interval = 1./ 60.;
}

// Calculates where we are allowed to click
void Simulation::FindGlobalPosition(Camera *camera)
{
  globalPositions.push_back(Cartesian3(1., 1., 1.));
}

// loads a file in and you know, loads it in and stuff
void Simulation::Load(const char *filename)
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

// updates all the physics for all the items in the scene
void Simulation::Update(float dT)
{
  // Calcualte all the new positions and velocities
  // of the items in the scene

  std::cout << "\n\n\n-------------------------" << std::endl;
  std::cout << "Simulation Update" << '\n';

  std::cout << "Spings: " << cloth->springs.size() << '\n';
  for(unsigned int i = 0; i < cloth->springs.size(); i++)
  {
     cloth->springs[i].Update(dT);
  }

  // for each pointMass, find the current forces acting on it
  std::cout << "PointsMasses: " << cloth->points.size() << '\n';
  for(unsigned int i = 0; i < cloth->points.size(); i++)
  {
     cloth->points[i].CalculateTotalForce();
   }

  // If we are in Euler Mode
  EulerUpdate(dT);

  // If we are in fancy Verlet mode
  //VerletUpdate();

  // Now calcualte the forces exerted by all the
  // springs in the system
}

void Simulation::EulerUpdate(float dT)
{
  Cartesian3 rt1;   // position 1
  Cartesian3 at1;   // acceleration 1
  Cartesian3 vt1;   // velocity 1
  Cartesian3 fNet;  // net forces
  float      m;     // mass of the object

  // for every pointMass in the cloth

  for(unsigned int i = 0; i < cloth->points.size(); i ++)
  {
    // only move if the point is not fixed
    if(cloth->points[i].fixed == false)
    {
      rt1  = cloth->points[i].pos;
      at1  = cloth->points[i].acc;
      vt1  = cloth->points[i].vel;
      fNet = cloth->points[i].cForce;
      m    = cloth->points[i].mass;

      std::cout << "\n\nEuler Update: "<< i << '\n';

      std::cout << "rt1: " << rt1 << std::endl;
      std::cout << "at1: " << at1 << std::endl;
      std::cout << "vt1: " << vt1 << std::endl;
      std::cout << "fNet: " << fNet << std::endl;
      std::cout << "m: " << m << std::endl;
      std::cout << "dt: " << dT << '\n';

      // update position
      cloth->points[i].pos = rt1 + vt1 * dT;

      // update acceleration
      cloth->points[i].acc = fNet / m;

      // update velocity
      cloth->points[i].vel = vt1 + (fNet / m) * dT;

      std::cout << "pos: " << cloth->points[i].pos << '\n';
      std::cout << "acc: "<< cloth->points[i].acc << '\n';
      std::cout << "vel: " << cloth->points[i].vel  << '\n';

    }
  }
}

// large render call, renders all the objects in the scene
void Simulation::Render(int frameNo, Camera *camera)
{
  cloth->Render();
  // ball->Render();
  // wind->Render();

}
