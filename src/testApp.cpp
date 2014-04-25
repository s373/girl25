#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	screen.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	screen.begin();
	ofClear(1,1,1,1);
	screen.end();
	
	
	girlimage.loadImage("girl25.jpeg");
	int w = girlimage.getWidth();
	int h = girlimage.getHeight();

	dnared.setup(w);
	dnagreen.setup(w);
	dnablue.setup(w);
		
	y = 0;
	dnamutatefactor = ofRandom(0.001, 0.05);
	readimg = true;
	
	ofSetBackgroundAuto(false);
	ofBackground(255);
	ofSetFrameRate(60);
	ofEnableAlphaBlending();
	
	buffersize = 1024;
	samplerate = 44100;
	audio.assign(buffersize, 0.0);
	soundStream.setup(this, 2, 0, samplerate, buffersize, 4);
	volume = 0.5;
	
	ofHideCursor();
}

//--------------------------------------------------------------
void testApp::update(){
	ygap=ofRandom(1,26);
	y+=ygap;
	if(y>ofGetHeight()){
		y=0;
		dnamutatefactor = ofRandom(1) < 0.5 ? ofRandom(0.00001, 0.0005) : ofRandom(0.0001, 0.025);				
	}
	
	if(!readimg && ofRandom(1) < 0.00055){
		readimg = true;
	}
		
	if(readimg){
		
		int w = girlimage.getWidth();
		int h = girlimage.getHeight();
		
		if(y == h-1){
			readimg = false;
		}
		
		int yindex = y % (h-1);
		
		
		unsigned char *pix = girlimage.getPixels();
		vector<float> * datared = dnared.getDna();
		vector<float> * datagreen = dnagreen.getDna();
		vector<float> * datablue = dnablue.getDna();
		
		for(int i=0; i<w*3; i+=3){
			int index = i*3 + yindex*w*3;
			
			unsigned char red = pix[index];
			unsigned char green = pix[index+1];
			unsigned char blue = pix[index+2];
			
			datared->at(i/3) = red / 255.0f;
			datagreen->at(i/3) = green / 255.0f;
			datablue->at(i/3) = blue / 255.0f;
			
		}
		
		
	}	else	{
		
		
		dnared.mutate(dnamutatefactor);
		dnagreen.mutate(dnamutatefactor);
		dnablue.mutate(dnamutatefactor);
		
	}
}


int bufferindex = 0;

//--------------------------------------------------------------
void testApp::draw(){
		
	
	screen.begin();
	
	int w = girlimage.getWidth();
	float width = ofGetWidth() / w;
	
	vector<float> * datared = dnared.getDna();
	vector<float> * datagreen = dnagreen.getDna();
	vector<float> * datablue = dnablue.getDna();
	
	for(int i=0; i<w; i++){
		float valred = datared->at(i) * 255;
		float valgreen = datagreen->at(i) * 255;
		float valblue = datablue->at(i) * 255;
		
		ofSetColor(valred, valgreen, valblue, 125);
		ofRect(  ofMap(i, 0, w, 0, ofGetWidth())   , y, width, ygap+2);
		
		audio[bufferindex] = (valred + valgreen + valblue) / (255*1.5) - 1;
		bufferindex = (bufferindex + 1) % buffersize;
		
	}
	
	screen.end();
	
	ofBackground(255);
	ofSetColor(255);
	screen.draw(0,0,ofGetWidth(), ofGetWidth());
	
}


//--------------------------------------------------------------
void testApp::audioOut(float * output, int bufferSize, int nChannels){

		for (int i = 0; i < bufferSize; i++){
			output[i*nChannels] = audio[i] * volume;
			output[i*nChannels+1] = audio[i] * volume;
		}

}





//--------------------------------------------------------------
void testApp::keyPressed(int key){

	if(key=='+'){
		volume += 0.1;
	}
	if(key=='-'){
		volume -= 0.1;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
