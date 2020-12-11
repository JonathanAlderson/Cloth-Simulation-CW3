///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Sphere.h
//	------------------------
//
//	Simple class to draw a ball and handle physics
//
///////////////////////////////////////////////////

#include "Sphere.h"

Sphere::Sphere(float frictionIn, float spinIn, Cartesian3 positionIn, float radiusIn)
{
  // set variables
  friction = frictionIn;
  spin     = spinIn;
  pos      = positionIn;
  radius   = radiusIn;

  rotation = 0.;
}

void Sphere::Update(float dT)
{
  rotation += dT * spin;
}

void Sphere::Collision(PointMass *p)
{

  Cartesian3 toSurf;
  Cartesian3 a = p->pos;
  Cartesian3 b = pos;
  Cartesian3 proj;        // projection for friction
  Cartesian3 grav;        // force of graivty
  float      angle;       // angle of the projection
  float len;
  float circH;            // circumference at intersection height
  float speed;            // how fast the sphere is rotating at point of intersection

  float relX;             // relative position on the sphere
  float relZ;

  // for collision detection
  float pi = 3.14159;
  float delta = 0.1;


  // If inside the sphere and above the equator
  if(a.distance(b) < (radius + delta))
  {

    // compute the position the point should be by
    // computing a vector to the point and resizing until on the surface of the sphere
    toSurf =  (a - b);
    len = sqrt(toSurf.length());
    // resize
    toSurf = (toSurf / len);
    // calculate new position on sphere
    p->pos = pos + (toSurf * (radius + delta));

    // if less than the equator
    if(p->pos.y < pos.y)
    {
      p->eForces[COLLISION] = Cartesian3(0., 0., 0.);
      p->eForces[BFRICTION]  = Cartesian3(0., 0., 0.);
    }
    else
    {
      // Now calculate a force to stop the point falling through the sphere
      // depending on the angle the point is on
      p->eForces[COLLISION] = Cartesian3(0, -p->eForces[GRAVITY].y, 0.);
      p->eForces[COLLISION] = p->eForces[COLLISION].dotProd(toSurf);


      // Now calculate friction
      // by resoving to a 2D case through vector projection and rotation
      // calculating friction in 2D then rotating back and caluclting final forces

      grav = Cartesian3(0., p->eForces[GRAVITY].y, 0.);
      proj = grav * (toSurf.dot(grav) / grav.dot(grav));
      proj = toSurf - proj;


      // find the angle we are currently rotated at
      // and make it between 0 and 2pi
      angle = atan(proj.x / proj.z);
      // top half
      if(proj.z > 0.){ angle += pi * 0.5; }
      // bottom half
      else           {angle += (pi * 1.5); }
      // put between 2pi and 0
      angle = fmod(angle, pi * 2.0);


      // now rotate the vector to be alligned in one plane
      Cartesian3 rotToSurf = Cartesian3(toSurf.x * cos(-angle) + toSurf.z * sin(-angle), toSurf.y, -toSurf.x * sin(-angle) + toSurf.z * cos(-angle));

      // calculate the direction of friction
      Cartesian3 frictionDir = Cartesian3(rotToSurf.y, -rotToSurf.x, 0.);

      // now rotate back again
      frictionDir = Cartesian3(frictionDir.x * cos(angle) + frictionDir.z * sin(angle), frictionDir.y, -frictionDir.x * sin(angle) + frictionDir.z * cos(angle));

      // apply the frictional force

      std::cout << "frictionDir: " << frictionDir << std::endl;
      std::cout << "p->vel: " << p->vel << std::endl;
      std::cout << "p->eForces[GRAVTIY]: " << p->eForces[GRAVITY] << std::endl;


      p->eForces[BFRICTION] = Cartesian3( abs(frictionDir.x * (friction * p->eForces[GRAVITY].y)) * -p->vel.x,
                                          abs(frictionDir.y * (friction * p->eForces[GRAVITY].y)) * -p->vel.y,
                                          abs(frictionDir.z * (friction * p->eForces[GRAVITY].y)) * -p->vel.z );


      std::cout << "p->eForces[BFRICTION]: " << p->eForces[BFRICTION] << std::endl;
      std::cout << "" << '\n';

      // Calculate the spinning force based on how high up the sphere the point is

      // find the circumference at point on sphere
      circH = 2. * sqrt(((radius + delta) * (radius + delta)) - ((pos.y - p->pos.y) * (pos.y - p->pos.y)));

      // rotational speed at that point on the sphere
      speed = circH * spin;

      // get position relative to
      relX = pos.x - p->pos.x;
      relZ = pos.z - p->pos.z;


      // add the spinning force
      p->eForces[COLLISION] = p->eForces[COLLISION] + Cartesian3(-relZ * speed, 0., relX * speed); //cos(relZ) * speed);

    }


  }
  else
  {
     p->eForces[COLLISION] = Cartesian3(0., 0., 0.);
     p->eForces[BFRICTION]  = Cartesian3(0., 0., 0.);
  }

  // do friction

  // apply force
}

void Sphere::Render()
{
  //glDisable(GL_TEXTURE_2D);

  // dark blue plane
  glColor3f(friction, 0.0, (1. - friction)); // static normal

  // get glu to do it
  GLUquadricObj *quadric;
  quadric = gluNewQuadric();
  glPushMatrix();
  glRotatef(rotation, 0., 1., 0.);
  glTranslatef(pos.x, pos.y, pos.z);
  gluQuadricDrawStyle(quadric, GLU_FILL );
  gluSphere( quadric , radius , 15 , 15 );
  glPopMatrix();
  //glEnable(GL_TEXTURE_2D);
}
