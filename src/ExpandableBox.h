#pragma once

#include "ofMain.h"

class ExpandableBox{
 public:
  ExpandableBox();
  void setup(glm::vec3 initScale, int initUnits);
  void draw();
  void update();
  void beginExpand(glm::vec3 axis, int units);
	ofBoxPrimitive& getGeometry();
 private:
  ofBoxPrimitive mGeometry;
  ofMaterial mMaterial;

  ofNode mForwardAnchor;
  ofNode mBackwardAnchor;
  ofNode mLeftAnchor;
  ofNode mRightAnchor;
  ofNode mUpAnchor;
  ofNode mDownAnchor;

  glm::vec3 mBaseScale;
  glm::vec3 mCurrentScale;

  bool bExpanding;
  float mExpandTime;
  float mExpandStartTime;

  int mExpandUnits;
  glm::vec3 mExpandInitScale;
  glm::vec3 mExpandTargetScale;

  void subdivide();

};
