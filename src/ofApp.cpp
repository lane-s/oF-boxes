#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofSetVerticalSync(true);
  ofBackground(20);

  mBoxInitializer.init(&mBoxPool);
  mBoxPool.init(50);

  mNewBoxInterval = 0.5f;
  makeNewBox();

  float width = ofGetWidth() * .12;
  float height = ofGetHeight() * .12;

  ofSetSmoothLighting(true);
  directionalLightGreen.setup();
  directionalLightGreen.setDirectional();
  directionalLightGreen.setDiffuseColor( ofFloatColor(.2, .85, .2) );
  directionalLightGreen.setAmbientColor( ofFloatColor(0.0f, 0.0f, 1.0f) );

  directionalLightPurple.setup();
  directionalLightPurple.setDirectional();
  directionalLightPurple.setDiffuseColor( ofFloatColor(.55, .1, .75) );
  directionalLightPurple.setSpecularColor( ofFloatColor(.55f, .1f, .75f) );
  directionalLightPurple.setAmbientColor( ofFloatColor(0.0f, 0.0f, 1.0f) );
}

void ofApp::makeNewBox() {
  ExpandableBoxPool::ptr newBox = mBoxPool.acquire();
  if (newBox) {
    topLevelBoxes.push_back(std::move(newBox));
    mLastNewBox = ofGetElapsedTimef();
  }
}

//--------------------------------------------------------------
void ofApp::update(){
  if (ofGetElapsedTimef() - mLastNewBox > mNewBoxInterval) {
    makeNewBox();
  }

  glm::vec3 greenLightDir = glm::vec3(45, 45, 0);
  directionalLightGreen.setOrientation(glm::quat(greenLightDir));

  glm::vec3 purpleLightDir = glm::vec3(-45, -45, 0);
  directionalLightPurple.setOrientation(glm::quat(purpleLightDir));

  mBoxPool.getActiveObjects(mActiveBoxes);
  for (ExpandableBox* box : mActiveBoxes) {
    box->update();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
  float spinX = sin(ofGetElapsedTimef()*.8f) * 0.35f;
  float spinY = sin(ofGetElapsedTimef()*.4f) * 0.35f;

  ofEnableLighting();
  directionalLightPurple.enable();
  directionalLightGreen.enable();

  cam.setGlobalPosition({ 0, 0, cam.getImagePlaneDistance(ofGetCurrentViewport()) });
  cam.begin();

  ofEnableDepthTest();

  for (ExpandableBox* box : mActiveBoxes) {
    ofLog(OF_LOG_NOTICE) << "Drawin a box" << endl;
    box->getGeometry().rotateDeg(spinY, 0.0, 1.0, 0.0);
    box->draw();
  }

  ofDisableDepthTest();
  ofFill();
  cam.end();

  directionalLightGreen.disable();
  directionalLightPurple.disable();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
