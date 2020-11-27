///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	Spring.cpp
//	------------------------
//
//  Class to handle rendering and physics updates for springs
//  sorry about the comments at the top of spring.h, I dind't
//  really mean it.
//
///////////////////////////////////////////////////


#include "Spring.h"


Spring::~Spring()
{
  // I don't know how to write destructors properly
}

Spring::Spring(PointMass *a, PointMass *b, float springK)
{
    // set variables
    pmA = a;
    pmB = b;
    springConst = springK;

    //std::cout << "Spring:  " <<  << '\n';

    // render constants
    radius = 0.3;
    slices = 10;
    stack = 3;

    // calcualte initial distance as rest length
    lr = pmA->pos.distance(pmB->pos);
    lc = lr; // makes sense, we start the same as rest length
}

void Spring::Update()
{
  // here is where the difficult physics comes in

}

// draw a glu cylinder between pmA --> pmB
// if this code looks familiar, trust me, it isn't
// taken from RenderBone() bvh.
void Spring::Render()
{
  // Calculate a from -> to vector
  GLdouble  dir_x = pmA->pos.x - pmB->pos.x;
  GLdouble  dir_y = pmA->pos.y - pmB->pos.y;
  GLdouble  dir_z = pmA->pos.z - pmB->pos.z;

  // Uses GLU for rendering
  static GLUquadricObj *  quadObj = NULL;
  if ( quadObj == NULL )
    quadObj = gluNewQuadric();
  gluQuadricDrawStyle( quadObj, GLU_FILL );
  gluQuadricNormals( quadObj, GLU_SMOOTH );

  glPushMatrix();

  // translate to start
  glTranslated( pmA->pos.x, pmA->pos.y, pmA->pos.z );

  // if bone is too short, do this to avoid
  // wierd rendering errors
  double  length;
  length = sqrt( dir_x*dir_x + dir_y*dir_y + dir_z*dir_z );
  if ( length < 0.0001 ) {
    dir_x = 0.0; dir_y = 0.0; dir_z = 1.0;  length = 1.0;
  }
  dir_x /= length;  dir_y /= length;  dir_z /= length;

  // for calculating normals
  GLdouble  up_x, up_y, up_z;
  up_x = 0.0;
  up_y = 1.0;
  up_z = 0.0;

  // for calculating local rotation matrix
  double  side_x, side_y, side_z;
  side_x = up_y * dir_z - up_z * dir_y;
  side_y = up_z * dir_x - up_x * dir_z;
  side_z = up_x * dir_y - up_y * dir_x;

  // if bone is too short, do this to avoid
  // wierd rendering errors
  length = sqrt( side_x*side_x + side_y*side_y + side_z*side_z );
  if ( length < 0.0001 ) {
    side_x = 1.0; side_y = 0.0; side_z = 0.0;  length = 1.0;
  }
  side_x /= length;  side_y /= length;  side_z /= length;

  // cross product to calculate up
  up_x = dir_y * side_z - dir_z * side_y;
  up_y = dir_z * side_x - dir_x * side_z;
  up_z = dir_x * side_y - dir_y * side_x;

  // local rotation matrix
  GLdouble  m[16] = { side_x, side_y, side_z, 0.0,
                            up_x,   up_y,   up_z,   0.0,
                            dir_x,  dir_y,  dir_z,  0.0,
                            0.0,    0.0,    0.0,    1.0 };

  glMultMatrixd( m );


  // with all our new found info, render a gluCylinder
  gluCylinder( quadObj, radius, radius, lc, slices, stack );

  glPopMatrix();
}
