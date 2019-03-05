#include "ExpandableBox.h"

ExpandableBox::ExpandableBox()
  : mBaseScale(glm::vec3(1)), mCurrentScale(glm::vec3(1)),
    bExpanding(false), mExpandTime(1.75f) {
}

void ExpandableBox::setup(glm::vec3 baseScale = glm::vec3(1), int initUnits = 1) {
  mBaseScale = baseScale;
  mCurrentScale = baseScale * initUnits;
  mGeometry.set(mCurrentScale.x, mCurrentScale.y, mCurrentScale.z);

  // mMaterial.setDiffuseColor(ofFloatColor::white);
  mMaterial.setShininess( 120 );
  mMaterial.setSpecularColor(ofColor(230, 230, 230, 230));

  glm::vec3 anchorScale = glm::vec3(0.02f, 0.02f, 0.02f);

  mForwardAnchor.setParent(mGeometry);
  mForwardAnchor.setScale(anchorScale);
  mForwardAnchor.setPosition({0, 0, 0.5f});
  mForwardAnchor.lookAt(mGeometry.getLookAtDir());

  mBackwardAnchor.setParent(mGeometry);
  mBackwardAnchor.setScale(anchorScale);
  mBackwardAnchor.setPosition({0, 0, -0.5f});
  mBackwardAnchor.lookAt(-mGeometry.getLookAtDir());

  mLeftAnchor.setParent(mGeometry);
  mLeftAnchor.setScale(anchorScale);
  mLeftAnchor.setPosition({-0.5f, 0, 0});
  mLeftAnchor.lookAt(mGeometry.getSideDir());

  mRightAnchor.setParent(mGeometry);
  mRightAnchor.setScale(anchorScale);
  mRightAnchor.setPosition({0.5f, 0, 0});
  mRightAnchor.lookAt(-mGeometry.getSideDir());

  mUpAnchor.setParent(mGeometry);
  mUpAnchor.setScale(anchorScale);
  mUpAnchor.setPosition({0, 0.5f, 0});
  mUpAnchor.lookAt(-mGeometry.getUpDir());

  mDownAnchor.setParent(mGeometry);
  mDownAnchor.setScale(anchorScale);
  mDownAnchor.setPosition({0, -0.5f, 0});
  mDownAnchor.lookAt(mGeometry.getUpDir());
}

void ExpandableBox::draw(){
    mMaterial.begin();
    mGeometry.draw();
    mMaterial.end();

    mForwardAnchor.draw();
    mBackwardAnchor.draw();
    mLeftAnchor.draw();
    mRightAnchor.draw();
    mUpAnchor.draw();
    mDownAnchor.draw();
}

void ExpandableBox::update(){
  mGeometry.set(mCurrentScale.x, mCurrentScale.y, mCurrentScale.z);

  if (bExpanding) {
    float elapsedTime = ofGetElapsedTimef() - mExpandStartTime;
    if (elapsedTime >= mExpandTime) {
      bExpanding = false;
    }else {
      mCurrentScale = glm::lerp(mExpandInitScale, mExpandTargetScale, elapsedTime / mExpandTime);
    }
  }
}

/*
 * Expand to the scale of units * baseScale on the given axis over time
 */
void ExpandableBox::beginExpand(glm::vec3 axis, int units){
  ofLog(OF_LOG_NOTICE) << "Beginning expansion" << endl;
  bExpanding = true;
  mExpandUnits = units;

  mExpandInitScale = mCurrentScale;
  glm::vec3 expandVec = glm::proj(mBaseScale, axis) * units;
  mExpandTargetScale = mBaseScale - glm::proj(mBaseScale, axis) + expandVec;

  ofLog(OF_LOG_NOTICE) << "Target scale:" << mExpandTargetScale << endl;

  mExpandStartTime = ofGetElapsedTimef();
}

void ExpandableBox::subdivide(){
  // Separate the box into multiple boxes joined by collapsed boxes which then begin expanding
}

ofBoxPrimitive& ExpandableBox::getGeometry(){
	return mGeometry;
}
