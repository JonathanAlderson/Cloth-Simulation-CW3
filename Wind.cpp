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

Wind::Wind(Cartesian3 originIn, Cartesian3 directionIn, float speedIn)
{
  // set
  origin    = originIn;
  direction = directionIn;
  speed     = speedIn;
}

void Wind::Render()
{  // todo
}

Cartesian3 Wind::Force(Cartesian3 target)
{
  // basic for now
  return (direction * speed);
}
