#pragma once

#include "ofMain.h"
#include "ofxFileHelper.h"
#include "ofxDirList.h"

class testApp : public ofSimpleApp{

	public:
		
		void setup();
		void update();
		void draw();
			
		void keyPressed  (int key);
		void keyReleased (int key);
		
		void recursivelyListDirectory(string path, bool bFirst);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		string dummyFile;
		vector <string> operations;
		string folderContents;
		string levelSpace;
		
		bool bRefresh;
		
};


