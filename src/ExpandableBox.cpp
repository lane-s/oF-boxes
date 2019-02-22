#include "ExpandableBox.h"

ExpandableBox::ExpandableBox(){
  bExpanding = false;
  geometry.set(1);
}

void ExpandableBox::setup(){
  // material.setDiffuseColor(ofFloatColor::white);
  material.setShininess( 120 );
  material.setSpecularColor(ofColor(230, 230, 230, 230));

  glm::vec3 anchorScale = glm::vec3(0.02f, 0.02f, 0.02f);

  forwardAnchor.setParent(geometry);
  forwardAnchor.setScale(anchorScale);
  forwardAnchor.setPosition({0, 0, 0.5f});
  forwardAnchor.lookAt(geometry.getLookAtDir());

  backwardAnchor.setParent(geometry);
  backwardAnchor.setScale(anchorScale);
  backwardAnchor.setPosition({0, 0, -0.5f});
  backwardAnchor.lookAt(-geometry.getLookAtDir());

  leftAnchor.setParent(geometry);
  leftAnchor.setScale(anchorScale);
  leftAnchor.setPosition({-0.5f, 0, 0});
  leftAnchor.lookAt(geometry.getSideDir());

  rightAnchor.setParent(geometry);
  rightAnchor.setScale(anchorScale);
  rightAnchor.setPosition({0.5f, 0, 0});
  rightAnchor.lookAt(-geometry.getSideDir());

  upAnchor.setParent(geometry);
  upAnchor.setScale(anchorScale);
  upAnchor.setPosition({0, 0.5f, 0});
  upAnchor.lookAt(-geometry.getUpDir());

  downAnchor.setParent(geometry);
  downAnchor.setScale(anchorScale);
  downAnchor.setPosition({0, -0.5f, 0});
  downAnchor.lookAt(geometry.getUpDir());
}

void ExpandableBox::draw(){
    material.begin();
    geometry.draw();
    material.end();

    forwardAnchor.draw();
    backwardAnchor.draw();
    leftAnchor.draw();
    rightAnchor.draw();
    upAnchor.draw();
    downAnchor.draw();
}

void ExpandableBox::update(){
}

void ExpandableBox::beginExpand(glm::vec3 dir, float length){
  // Expand length units in the given direction
}

void ExpandableBox::subdivide(){
  // Separate the box into multiple boxes joined by collapsed boxes which then begin expanding
}

ofBoxPrimitive& ExpandableBox::getGeometry(){
	return geometry;
}
