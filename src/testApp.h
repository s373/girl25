#pragma once

#include "ofMain.h"
#include "ofxDna.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	
	void audioOut(float * output, int bufferSize, int nChannels);
	ofSoundStream soundStream;
	int	buffersize, samplerate;
	vector <float> audio;
	float volume;
	
	ofImage	girlimage;
	ofxDna dnared;
	ofxDna dnagreen;
	ofxDna dnablue;

	int y,ygap;
	bool readimg;
		
	float dnamutatefactor;
	
	ofFbo screen;
	
};
