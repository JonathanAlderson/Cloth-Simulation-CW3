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
  float len;
  float circH;            // circumference at intersection height
  float speed;            // how fast the sphere is rotating at point of intersection

  float relX;             // relative position on the sphere
  float relZ;

  // for collision detection
  float delta = 0.1;

  if(a.distance(b) < (radius + delta))
  {

    // resolve position
    toSurf =  (a - b);
    len = sqrt(toSurf.length());

    // resize
    toSurf = (toSurf / len);

    // calculate new position on sphere
    p->pos = pos + (toSurf * (radius + delta));

    // stop falling through the sphere
    p->eForces[COLLISION] = Cartesian3(0, -p->eForces[GRAVITY].y, 0.);

    p->eForces[COLLISION] = p->eForces[COLLISION].cross(toSurf);

    // find the circumference at point on sphere
    circH = 2. * sqrt(((radius + delta) * (radius + delta)) - ((pos.y - p->pos.y) * (pos.y - p->pos.y)));

    // rotational speed at that point on the sphere
    speed = circH * spin;

    // get position relative to
    relX = pos.x - p->pos.x;
    relZ = pos.z - p->pos.z;


    // add the spinning force
    //p->eForces[COLLISION] = p->eForces[COLLISION] + Cartesian3(-relZ * speed, 0., relX * speed); //cos(relZ) * speed);
  }
  else
  {
     p->eForces[COLLISION] = Cartesian3(0., 0., 0.);
  }

  // do friction

  // apply force
}

void Sphere::Render()
{
  //glDisable(GL_TEXTURE_2D);

  // dark blue plane
  glColor3f(0.8, 0., 0.8);
  glNormal3f(friction, 0.0, (1. - friction)); // static normal

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
