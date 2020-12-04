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
  // setup
  cTime = 0.;
  area = 25;
  trailLen = 50;
  trailCount = 0;
  windAngle = 0;
  float randA;
  float randB;
  float randC;

  // seed
  srand(time(NULL));

  // this trail
  std::vector<Cartesian3> thisTrail;
  thisTrail.resize(trailLen);

  // add some particles randomly
  for(int i = 0; i < numParticles; i ++)
  {
    randA = (float)(rand()%(area+area+1)-area);
    randB = (float)(rand()%(area+area+1)-area);
    randC = (float)(rand()%(area+area+1)-area);

    // adding a lot of particles
    for(int j = 0; j < trailLen; j++)
    {
      thisTrail[j] = Cartesian3(randA, randB, randC);
    }
    particles.push_back(thisTrail);
  }
}

void Wind::Render()
{
  // don't waste draw calls if we don't need to
  if(show)
  {
    // setup opengl
    glLineWidth(2.);

    glBegin(GL_LINES);

    // offset for rendering trails
    int off = (trailCount) % trailLen;
    int first;
    int next;
    float col;

    // draw all the points
    for(unsigned int i = 0; i < particles.size(); i++)
    {
      for(unsigned int j = 0; j < trailLen -1 ; j++)
      {
        first = (j + off) % trailLen;
        next = (first + 1) % trailLen;

        col = (float) next / (float)trailLen;

        glColor3f(1., 0., 1.); // grey colour
        glVertex3f(particles[i][first].x, particles[i][first].y, particles[i][first].z);
        glVertex3f(particles[i][next].x, particles[i][next].y, particles[i][next].z);
      }

    }
    glEnd();
  }
}

void Wind::Update(float dT)
{
  cTime += dT;

  int prev;
  bool reset;

  // Don't waste calculation if we don't need to
  if(show && speed > 0)
  {
    prev = ((trailCount - 1) + trailLen) % trailLen;

    // Update all the wind particles
    for(unsigned int i = 0; i < particles.size(); i++)
    {
       // if the whole thing needs to teleport
       reset = false;

       // move the particle chain along one
       particles[i][trailCount] = particles[i][prev] + Force(particles[i][prev]) * dT;

       // check they don't go past the bounding box
       if(particles[i][trailCount].x > area)       { particles[i][trailCount].x = -area; reset = true; }
       else{ if(particles[i][trailCount].x < -area){ particles[i][trailCount].x = area; reset = true; }}

       if(particles[i][trailCount].y > area)       { particles[i][trailCount].y = -area; reset = true;}
       else{ if(particles[i][trailCount].y < -area){ particles[i][trailCount].y = area; reset = true; }}

       if(particles[i][trailCount].z > area)       { particles[i][trailCount].z = -area; reset = true; }
       else{ if(particles[i][trailCount].z < -area){ particles[i][trailCount].z = area; reset = true; }}

       // we teleport the whole trail
       if(reset)
       {
         for(unsigned int j = 0; j < trailLen; j++)
         {
            particles[i][j] = particles[i][trailCount];
        }
       }
    }
    // increment and reset if needed
    trailCount++;
    if(trailCount == trailLen){ trailCount = 0; }
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
