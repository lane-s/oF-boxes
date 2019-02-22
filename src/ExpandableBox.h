#pragma once

#include "ofMain.h"

class ExpandableBox{
 public:
  ExpandableBox();
  void setup();
  void draw();
  void update();
  void beginExpand(glm::vec3 dir, float length);
	ofBoxPrimitive& getGeometry();
 private:
  ofBoxPrimitive geometry;
  ofMaterial material;

  ofNode forwardAnchor;
  ofNode backwardAnchor;
  ofNode leftAnchor;
  ofNode rightAnchor;
  ofNode upAnchor;
  ofNode downAnchor;

  bool bExpanding;

  void subdivide();
};
