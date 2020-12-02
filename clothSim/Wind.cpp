///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Wind.cpp
//	------------------------
//
//	Very simple class to add forces
//
///////////////////////////////////////////////////

#include "Wind.h"

Wind::Wind()
{
  std::cout << "Wind Init" << '\n';
  cTime = 0.;
}

void Wind::Render()
{  // todo
}

void Wind::Update(float dT)
{
  cTime += dT;
}

Cartesian3 Wind::Force(Cartesian3 pos)
{
  Cartesian3 force = Cartesian3(sin(pos.x * pos.y * cTime), cos(pos.z * cTime), cos(5. * pos.x * pos.y * pos.z));

  force = force * speed;

  return (force);
}
