///////////////////////////////////////////////////
//
//	Jonathan Alderson
//	October, 2020
//
//	------------------------
//	MousePick.h
//	------------------------
//
//  Class to get mouse position in world space from screen space
//
///////////////////////////////////////////////////

#ifndef MOUSEPICK_H
#define MOUSEPICK_H
#define GLM_ENABLE_EXPERIMENTAL

#include "Cartesian3.h"
#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/intersect.hpp>
#include <vector>

class MousePick
{
public:

  MousePick(std::vector<Cartesian3> *targetPoints, float size);

  void UpdateTargetPoints(std::vector<Cartesian3> *targetPoints);

  int click(float x, float y, Camera *camera);

  Cartesian3 drag(float x, float y, Camera *camera);

  bool dragging;
  int closest;
  glm::vec3 start;
  float size;

  std::vector<Cartesian3> *targetPoints;

};

#endif
