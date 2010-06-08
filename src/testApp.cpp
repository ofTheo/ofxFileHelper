#include "testApp.h"

//WORK IN PROGRESS! MESSY FOR NOW :) 

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(127,127,127);
	ofSetVerticalSync(true);

	bRefresh  = true;
}

//--------------------------------------------------------------
void testApp::recursivelyListDirectory(string path, bool bFirst){
	//note this will be moved out into a better file lister module of ofxControlPanel
	
	ofxDirList lister;

	lister.reset();
	int numElements = lister.listDir(path);
	if( numElements != 0 ){
		levelSpace += string("  ");
		for(int k = 0; k < numElements; k++){
			folderContents += levelSpace + lister.getName(k);
			//printf("crashing on %s\n", lister.getName(k).c_str());
			if( ofxFileHelper::getFileExt( lister.getName(k) ) == "" ){
				folderContents += string("/\n");
				recursivelyListDirectory(path+lister.getName(k)+"/", false);
			}else{
				folderContents += string("\n");			
			}
		}
	
		if( levelSpace.length() >= 2 ){
			levelSpace = levelSpace.substr(0, levelSpace.length()-2);
		}

	}
}


//--------------------------------------------------------------
void testApp::update(){
	
	if( bRefresh ){
		folderContents		= "data/\n";

		string folderPath	= "./";
		levelSpace			= "";
		
		//note this will be moved out into a better file lister module of ofxControlPanel	
		recursivelyListDirectory(folderPath, true);
		bRefresh = false;
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofDrawBitmapString("listing data folder - hit 'r' key to refresh. hit 'c' to copy a file - 'm' to move a folder", 10, 20);
	
	//lets draw fake bars behind the file listing.
	vector <string> strList = ofSplitString(folderContents, "\n");
	
	//note this will be moved out into a better file lister module of ofxControlPanel
	float x = 10;
	float y = 80;
	float w = 350;
	float h = 20;
	
	for(int k = 0; k < strList.size(); k++){
		if(k%2==0){
			ofSetColor(230, 230, 230);
		}else{
			ofSetColor(210, 210, 210);
		}
		ofFill();
		ofRect(x, y, w, -h);
		ofNoFill();
		ofSetColor(100, 100, 100);
		ofRect(x, y, w, -h);
		ofSetColor(0, 0, 0);
		ofDrawBitmapString(strList[k], x+2, y-5);	
		
		y+=h;
	}
	

		
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	if( key == 'r' ){
		bRefresh = true;
	}
	
	if( key == 'c' ){
		string unique = ofToString(ofGetYear()) + ofToString(ofGetMonth()) + ofToString(ofGetDay()) + ofToString(ofGetHours()) + ofToString(ofGetMinutes()) + ofToString(ofGetSeconds());
		ofxFileHelper::copyFromTo("sampleFileDontDelete.txt", "copiedFile"+unique+".txt");
		
		bRefresh = true;
	}
	
	if( key == 'm' ){
		
		if( ofxFileHelper::doesDirectoryExist("dummyFolder/") ){
			//be careful with slashes here - appending a slash when moving a folder will causes mad headaches
			ofxFileHelper::moveFromTo("dummyFolder", "aMovedFolder");
		}else if( ofxFileHelper::doesDirectoryExist("aMovedFolder/") ){
			//be careful with slashes here - appending a slash when moving a folder will causes mad headaches
			ofxFileHelper::moveFromTo("aMovedFolder", "dummyFolder");
		}
		
		bRefresh = true;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}
