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


// Destructor
Cloth::~Cloth()
{
  Reset();
}

// constructor
Cloth::Cloth(vector<Cartesian3> *positionsIn)
{
  float ballMasses = 1.;
  float springConstant = 10.;

  springs.reserve(2);
  points.reserve(positionsIn->size());

  for(unsigned int i = 0; i < positionsIn->size(); i++)
  {
    // add a new ball at this point
    points.push_back(PointMass(positionsIn[0][i], ballMasses));
  }

  std::cout << "Cloth: " << points.size() << '\n';

  // add a temp spring
  //springs.push_back(Spring(&points[0], &points[1], springConstant));

  springs.push_back(Spring(&points[1], &points[2], springConstant));
  points[1].springs.push_back(&springs[0]);
  points[2].springs.push_back(&springs[0]);

  springs.push_back(Spring(&points[0], &points[1], springConstant));
  points[0].springs.push_back(&springs[1]);
  points[1].springs.push_back(&springs[1]);

  //points[0].fixed = true;
  points[2].fixed = true;
  // give a temporary force to one of the point masses
  points[0].eForces.push_back(Cartesian3(0., -9.81, 0.));
  points[1].eForces.push_back(Cartesian3(0., -9.81, 0.));





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
