#pragma once

#include "ofMain.h"
#include "ObjectPool.cpp"

class ExpandableBox;
struct ExpandableBoxInitializer;
struct ExpandableBoxActivator;
struct ExpandableBoxDeactivator;

using ExpandableBoxPool = ObjectPool<ExpandableBox, ExpandableBoxInitializer, ExpandableBoxActivator, ExpandableBoxDeactivator>;

class ExpandableBox {
 public:
  ExpandableBox();
  ExpandableBox(ExpandableBoxPool* pool);

  void setup(glm::vec3 initScale, int initUnits);
  void draw();
  void update();
  void beginExpand(glm::vec3 axis, int units);
	ofBoxPrimitive& getGeometry();

 private:
  ExpandableBoxPool* mPool;

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

struct ExpandableBoxInitializer {
  ExpandableBoxPool* mPool;

  ExpandableBoxInitializer() {}
  void init(ExpandableBoxPool* pool) {
    mPool = pool;
  }

  void operator () (ExpandableBox* addr) {
    if (mPool) {
      addr = new ExpandableBox(mPool);
    } else {
      ofLog(OF_LOG_ERROR) << "Call ExpandableBoxInitializer.init before attempting to initialize an object pool using ExpandableBoxInitializer" << endl;
    }
  }
};

struct ExpandableBoxActivator {
  float mOffsetX;

  ExpandableBoxActivator() {}
  void operator () (ExpandableBox* box) {
    box->setup(glm::vec3(120.0f), 1);
    box->beginExpand(glm::vec3(0.0f, 1.0f, 0.0f), 8);

    float screenWidth = ofGetWidth();
    float screenHeight = ofGetHeight();

    box->getGeometry()
      .setPosition( -screenWidth * .5 + mOffsetX,
                    screenHeight * 1.0/16.f, 0);

    mOffsetX += 15;
  }
};

struct ExpandableBoxDeactivator {
  ExpandableBoxDeactivator() {}
  void operator () (ExpandableBox* box) {
    //Deactivate box and any children
  }
};
