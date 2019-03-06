#pragma once

#include "ofMain.h"
#include "ObjectPool.cpp"
#include "ExpandableBox.h"

class ofApp : public ofBaseApp{
	public:
    ofApp()
      : mBoxPool(100, &mBoxInitializer), mActiveBoxes(50, nullptr) {}

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    ofLight directionalLightGreen;
    ofLight directionalLightPurple;

    ofMaterial material;
    ofCamera cam;

    ExpandableBoxInitializer mBoxInitializer;
    ExpandableBoxPool mBoxPool;

    std::vector<ExpandableBox*> mActiveBoxes;
    std::vector<ExpandableBoxPool::ptr> topLevelBoxes;
    float mNewBoxInterval;
    float mLastNewBox;
    void makeNewBox();
};

