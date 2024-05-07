#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void exit();

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

        void audioIn(float * input, int bufferSize, int nChannels);
        void audioOut();

        void onsetEvent(float & time);
        void onset2Event(float & time);
        void beatEvent(float & time);

    private:
        ofxAubioOnset onset;
        ofxAubioOnset onset2;
        ofxAubioPitch pitch;
        ofxAubioBeat beat;
        ofxAubioMelBands bands;

        ofxPanel pitchGui;
        ofxFloatSlider midiPitch;
        ofxFloatSlider pitchConfidence;

        ofxPanel beatGui;
        bool gotBeat;
        ofxFloatSlider beatThreshold;
        ofxFloatSlider bpm;
        ofxFloatSlider beatConfidence;
        ofxIntSlider tatum;
        ofxIntSlider tatumSig;

        ofxPanel onsetGui;
        bool gotOnset;
        ofxFloatSlider onsetThreshold;
        ofxFloatSlider onsetCompression;
        ofxToggle onsetWhiteningEn;
        ofxFloatSlider onsetMinioi;
        ofxFloatSlider onsetNovelty;
        ofxFloatSlider onsetThresholdedNovelty;

        ofxPanel onset2Gui;
        bool gotOnset2;
        ofxFloatSlider onset2Threshold;
        ofxFloatSlider onset2Compression;
        ofxToggle onset2WhiteningEn;
        ofxFloatSlider onset2Minioi;
        ofxFloatSlider onset2Novelty;
        ofxFloatSlider onset2ThresholdedNovelty;

        ofxPanel bandsGui;
        ofPolyline bandPlot;
};
