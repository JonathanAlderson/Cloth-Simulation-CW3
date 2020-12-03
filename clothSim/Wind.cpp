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

Wind::Wind(int numParticles)
{
  std::cout << "Wind Init" << '\n';
  cTime = 0.;


  area = 25;
  windAngle = 0;
  float randA;
  float randB;
  float randC;

  // seed
  srand(time(NULL));

  // add some particles randomly
  for(int i = 0; i < numParticles; i ++)
  {
    randA = (float)(rand()%(area+area+1)-area);
    randB = (float)(rand()%(area+area+1)-area);
    randC = (float)(rand()%(area+area+1)-area);
    particles.push_back(Cartesian3(randA, randB, randC));
  }
}

void Wind::Render()
{
  // don't waste draw calls if we don't need to
  if(show)
  {
    // setup opengl
    glPointSize(3.);
    glColor3f(0., 0., 0.); // grey colour
    glBegin(GL_POINTS);

    // draw all the points
    for(unsigned int i = 0; i < particles.size(); i++)
    {
      glVertex3f(particles[i].x, particles[i].y, particles[i].z);
    }
    std::cout << "Wind Render" << '\n';
    glEnd();
  }
}

void Wind::Update(float dT)
{
  cTime += dT;

  // Don't waste calculation if we don't need to
  if(show && speed > 0)
  {
    // Update all the wind particles
    for(unsigned int i = 0; i < particles.size(); i++)
    {
       particles[i] = particles[i] + Force(particles[i]) * dT;

       // check they don't go past the bounding box
       if(particles[i].x > area)       { particles[i].x = -area; }
       else{ if(particles[i].x < -area){ particles[i].x = area; }}

       if(particles[i].y > area)       { particles[i].y = -area; }
       else{ if(particles[i].y < -area){ particles[i].y = area; }}

       if(particles[i].z > area)       { particles[i].z = -area; }
       else{ if(particles[i].z < -area){ particles[i].z = area; }}
    }
  }

  // wind changes direction randomly
  windAngle += (((float)rand() / (float)RAND_MAX) - 0.5) * 0.1;
}

Cartesian3 Wind::Force(Cartesian3 pos)
{
  // Don't bother calculating unless we need to
  if(speed != 0)
  {
    // general turbulent force
    Cartesian3 force = Cartesian3(sin(pos.x * pos.y * cTime), cos(pos.z * cTime), cos(5. * pos.x * pos.y * pos.z));

    // overall direction of wind
    Cartesian3 direction = Cartesian3(cos(windAngle), 0., sin(windAngle));

    // combination of turbulence and overall direction
    force = (direction + (force * 0.5)) * speed;
    return (force);
  }
  else
  {
    return Cartesian3(0., 0., 0.);
  }

}
