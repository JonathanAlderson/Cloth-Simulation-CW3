///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Cloth.cpp
//	------------------------
//
//	Renders and Simluates a Cloth
//
///////////////////////////////////////////////////

#include "Cloth.h" // we might be needing this
#include "../objLoader/OBJ_Loader.h"


// Destructor
Cloth::~Cloth()
{
  Reset();
}

// constructor
Cloth::Cloth(const char *filename)
{
  // Initialize Loader
  // Load .obj File
  objl::Loader Loader;
  bool loadout = Loader.LoadFile(filename);
  objl::Mesh curMesh = Loader.LoadedMeshes[0];

  // constants
  float ballMasses = 1.;
  float springConstant = 10.;
  float dampingConstant = 10.;

  // reserve the correct sized vectors to avoid horrible memory problems
  points.reserve(curMesh.Vertices.size());
  springs.reserve(curMesh.Indices.size());

  // temp variables for reading in
  Cartesian3 tempPos;
  unsigned int a;
  unsigned int b;

  // read in all the verticies from the file and turn into point masses
  for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
  {
    // construct a cartesian3
    tempPos = Cartesian3(curMesh.Vertices[j].Position.X,
                         curMesh.Vertices[j].Position.Y,
                         curMesh.Vertices[j].Position.Z);

    points.push_back(PointMass(tempPos, ballMasses));
  }

  // read in all the edges from the file and make them springs
  for (unsigned int j = 0; j < curMesh.Indices.size(); j+=1)
  {
    // find which indices connect the two
    a = curMesh.Indices[j];
    b = curMesh.Indices[j + 1];
    springs.push_back(Spring(&points[a], &points[b], springConstant, dampingConstant));

    // also tell the PointMasses which springs they are attached to
    points[a].springs.push_back(&springs[j]);
    points[b].springs.push_back(&springs[j]);
  }


  points[0].fixed = true;
  // points[2].fixed = true;

  // give a temporary force to one of the point masses
  points[1].eForces.push_back(Cartesian3(0., -9.81, 0.));
  points[2].eForces.push_back(Cartesian3(0., -9.81, 0.));

  // calculate all the colours of the points
  for(unsigned int i = 0; i < points.size(); i++)
  {
     points[i].CalculateColour();
   }
}

// reset
void Cloth::Reset()
{
  activePoint = -1;
}

// update everything once
void Cloth::Update(float dT)
{
  // update all of the forces in the springs depending
  // on the balls positions
}

void Cloth::Render()
{
  // Render All The Point Masses
  for(unsigned int i = 0; i < points.size(); i++)
  {
    points[i].Render();
  }

  // Render All The Springs Between Them
  for(unsigned int i = 0; i < springs.size(); i++)
  {

    springs[i].Render();
  }

  std::cout << "Cloth Render" << '\n';
}
