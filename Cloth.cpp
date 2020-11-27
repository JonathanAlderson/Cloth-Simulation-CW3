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
  for(unsigned int i = 0; i < positionsIn->size(); i++)
  {
    // add a new ball at this point
    Cartesian3 a = positionsIn[0][i];

    std::cout << "A: " << a << '\n';

    points.push_back(PointMass(positionsIn[0][i]));
  }

  // add a temp spring
  springs.push_back(Spring(&points[0], &points[1], 1.0));
}

// reset
void Cloth::Reset()
{
  activePoint = -1;
}

// update everything once
void Cloth::Update(float dT)
{
  std::cout << "Here" << '\n';
  std::cout << "Spig: " << springs[0].springConst << '\n';

  // call all of the connections update functions
  springs[0].Update();
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
