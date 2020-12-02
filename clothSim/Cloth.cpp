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

  // rendering mode
  wireframeRender = false;

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
  unsigned int c;
  std::vector<Cartesian3> uniqueVert;
  std::vector<Cartesian3> uniqueSprings;
  std::vector<Cartesian3> faceSprings;  // springs on the current face
  vertRef.clear();                      // unique references
  int idx;

  // add all unique verticies to a data structure
  for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
  {
    // construct a cartesian3
    tempPos = Cartesian3(curMesh.Vertices[j].Position.X,
                         curMesh.Vertices[j].Position.Y,
                         curMesh.Vertices[j].Position.Z);
    // if unique add
    idx = -1;
    for(unsigned int i = 0; i < uniqueVert.size(); i++)
    {
       if(uniqueVert[i] == tempPos){ idx = i; break; }
     }
    // this vertex is not unique
    if(idx != -1)
    { // so add the correct vertex reference
      vertRef.push_back(idx);
    }
    // this vertex is unique
    else
    { // unique vertex, so add to list
      // and create a pointmass
      uniqueVert.push_back(tempPos);
      vertRef.push_back(uniqueVert.size() - 1);
      points.push_back(PointMass(uniqueVert.back(), ballMasses));

      // also at this point get the texture coordiantes
      texCoords.push_back(Tex(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
    }
  }

  // find which unique vertices the edges are reffering to
  for (unsigned int j = 0; j < curMesh.Indices.size(); j+=3)
  {
    // find which indices connect the two
    a = curMesh.Indices[j];
    b = curMesh.Indices[j + 1];
    c = curMesh.Indices[j+ 2];

    // find unique index
    a = vertRef[a];
    b = vertRef[b];
    c = vertRef[c];

    // make a face out of springs
    faceSprings.clear();
    faceSprings.push_back(Cartesian3(a, b, 0));
    faceSprings.push_back(Cartesian3(b, c, 0));
    faceSprings.push_back(Cartesian3(c, a, 0));

    // search for all these springs
    for(unsigned int k = 0; k < faceSprings.size(); k++)
    {
      idx = -1;
      tempPos = faceSprings[k];
      // check this spring hasn't already been added
      for(unsigned int i = 0; i < uniqueSprings.size(); i++)
      {
        if(uniqueSprings[i] == tempPos){ idx = i; break; }
      }
      // this vertex is not unique
      if(idx != -1)
      {
        // don't need to add a spring as it is already there
      }
      else
      {
        // add the spring and it's 'backward' so it can't be added twice
        uniqueSprings.push_back(tempPos);
        tempPos = Cartesian3(tempPos.y, tempPos.x, 0);
        uniqueSprings.push_back(tempPos);

        // call a spring
        springs.push_back(Spring(&points[tempPos.x], &points[tempPos.y], springConstant, dampingConstant));

        // also tell the PointMasses which springs they are attached to
        points[a].springs.push_back(&springs.back());
        points[b].springs.push_back(&springs.back());
      }
    }
  }

  //points[0].fixed = true;
  // points[2].fixed = true;

  // give a temporary force to one of the point masses
  //points[1].eForces.push_back(Cartesian3(0., -9.81, 0.));ss

  // calculate all the colours of the points
  for(unsigned int i = 0; i < points.size(); i++)
  {
    points[i].eForces.push_back(Cartesian3(0., -1.81, 0.));
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

// gives an instantaneous force to the point we are dragging at the moment
void Cloth::ApplyForce(Cartesian3 movement)
{
  movement = movement * 1000.;
  std::cout << "Applying force to " << activePoint << " of " << movement << '\n';
  // add the force and update the colour
  points[activePoint].eForces.push_back(movement);
  points[activePoint].CalculateTotalForce();
  points[activePoint].CalculateColour();
}


void Cloth::Render()
{
  if(wireframeRender)
  {
    // Render All The Point Masses
    for(unsigned int i = 0; i < points.size(); i++){ points[i].Render(); }
    // Render All The Springs Between Them
    for(unsigned int i = 0; i < springs.size(); i++){ springs[i].Render(); }
  }
  else
  {
    // render with texutres and all that jazz
    glBegin(GL_TRIANGLES);

    // random colours
    //glColor3f((float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX, (float)rand()/(float)RAND_MAX);
    glColor3f(1., 1., 1.);
    Cartesian3 a;
    Cartesian3 b;
    Cartesian3 c;
    unsigned int aIdx;
    unsigned int bIdx;
    unsigned int cIdx;
    Cartesian3 norm;
    for(unsigned int i = 0; i < vertRef.size(); i+=3)
    {
      // find a, b, c that make up the traingle
      aIdx = vertRef[i    ];
      bIdx = vertRef[i + 1];
      cIdx = vertRef[i + 2];
      a = points[aIdx].pos;
      b = points[bIdx].pos;
      c = points[cIdx].pos;

      // compute and set normal
      norm = ((c - a).cross(c - b)).normalise();
      glNormal3f(norm.x, norm.y, norm.z);


      // render one triangle
      // set the texture coordinates
      if(useTextures)
      {
        std::cout << "Using textures" << '\n';
        glTexCoord2f(texCoords[aIdx].u, texCoords[aIdx].v);
        glVertex3f(a.x, a.y, a.z);
        glTexCoord2f(texCoords[bIdx].u, texCoords[bIdx].v);
        glVertex3f(b.x, b.y, b.z);
        glTexCoord2f(texCoords[cIdx].u, texCoords[cIdx].v);
        glVertex3f(c.x, c.y, c.z);
      }
      // render only points, no textures
      else
      {
        glVertex3f(a.x, a.y, a.z);
        glVertex3f(b.x, b.y, b.z);
        glVertex3f(c.x, c.y, c.z);
      }
    }
    glEnd();

    // also render any control points
    for(unsigned int i = 0; i < points.size(); i++){ if(points[i].fixed) { points[i].Render(); } }
  }
}
