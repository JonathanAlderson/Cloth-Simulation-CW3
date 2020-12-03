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

  windParticles = 500;
  showSphere   = false;

  sphereFriction = 1.;
  sphereSpin     = 1.;

  // initialise wind
  wind = new Wind(windParticles);
  wind->speed = 0;

  // initialise ground plane
  ground = new Plane(Cartesian3(0., -10., 0.), 10., 10.);

  Init();
}

// Constructor with file
Simulation::Simulation(const char *simFileName)
{
  // reset
	Clear();

  windParticles = 500;
  showSphere   = false;

  sphereFriction = 1.;
  sphereSpin     = 1.;

  // init cloth with obj file
  cloth = new Cloth(simFileName);

  // initialise wind
  wind = new Wind(windParticles);
  wind->speed = 0;

  // initialise ground plane
  ground = new Plane(Cartesian3(0., -10., 0.), 10., 10.);

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
  // clear positions and add current values
  globalPositions.clear();
  for(unsigned int i = 0; i < cloth->points.size(); i++)
  {
    globalPositions.push_back(cloth->points[i].pos);
  }
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
// and find out what the global positions are
void Simulation::Update(float dT)
{
  std::cout << "\n\n\n-------------------------" << std::endl;

  // update the wind in our scene
  wind->Update(dT);

  // call the cloths update function
  cloth->Update(dT);

  // Check for gound plane intersections with our pointmasses
  for(unsigned int i = 0; i < cloth->points.size(); i++)
  {
    ground->Collision(&(cloth->points[i]));
  }

  // Calcualte all the new positions and velocities
  // of the items in the scene
  for(unsigned int i = 0; i < cloth->springs.size(); i++)
  {
     cloth->springs[i].Update(dT);
  }

  // apply windy forces on all the particles if they want it
  if(wind->speed > 0)
  {
    for(unsigned int i = 0; i < cloth->points.size(); i++)
    {
      cloth->points[i].eForces[WIND] = wind->Force(cloth->points[i].pos);
    }
  }

  // for each pointMass, find the current forces acting on it
  for(unsigned int i = 0; i < cloth->points.size(); i++)
  {
     cloth->points[i].CalculateTotalForce();
   }

  // If we are in Euler Mode
  EulerUpdate(dT);

  // If we are in fancy Verlet mode
  //VerletUpdate(dT);

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

      // update position
      cloth->points[i].pos = rt1 + vt1 * dT;

      // update acceleration
      cloth->points[i].acc = fNet / m;

      // update velocity
      cloth->points[i].vel = vt1 + (fNet / m) * dT;
    }
  }
}

void Simulation::VerletUpdate(float dT)
{
  Cartesian3 rt1;    // position 1
  Cartesian3 rt0;    // position before
  Cartesian3 at1;    // acceleration 1
  Cartesian3 vt1;    // velocity 1
  Cartesian3 vtHalf; //velocity half step in front
  Cartesian3 fNet;   // net forces
  float      m;      // mass of the object

  // for every pointMass in the cloth
  for(unsigned int i = 0; i < cloth->points.size(); i ++)
  {
    // only move if the point is not fixed
    if(cloth->points[i].fixed == false)
    {
      rt1  = cloth->points[i].pos;
      rt0  = cloth->points[i].prevPos;
      at1  = cloth->points[i].acc;
      vt1  = cloth->points[i].vel;
      fNet = cloth->points[i].cForce;
      m    = cloth->points[i].mass;

      // update position
      cloth->points[i].pos = (rt1 * 2.) - rt0 + (fNet / m) * (dT * dT);

      // find half velocity step
      vtHalf = vt1 + (fNet / m) * dT;

      // update acceleration
      cloth->points[i].acc = fNet / m;

      // update velocity
      cloth->points[i].vel = vt1 + (fNet / m) * dT;
    }
  }
}

// large render call, renders all the objects in the scene
void Simulation::Render(int frameNo, Camera *camera)
{
  cloth->Render();
  // ball->Render();
  wind->Render();

  ground->Render();

}
