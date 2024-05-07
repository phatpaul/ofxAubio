#include "ofApp.h"
#include "ofEventUtils.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // set the size of the window
    ofSetWindowShape(750, 250);

    // setup onset object
    onset.setup();
    //onset.setup("mkl", 2 * bufferSize, bufferSize, sampleRate);
    // listen to onset event
    ofAddListener(onset.gotOnset, this, &ofApp::onsetEvent);

    // setup onset object
    // The parameter method is a string that can be any of: default, old_default,
    // - onset novelty functions: complex, energy, hfc, kl, mkl, phase, specdiff, specflux, wphase, 
    // - spectral descriptors: centroid, decrease, kurtosis, rolloff, skewness, slope, spread
    onset2.setup("energy", 512, 256, 44100);
    // listen to onset event
    ofAddListener(onset2.gotOnset, this, &ofApp::onset2Event);

    // setup pitch object
    pitch.setup();
    //pitch.setup("yinfft", 8 * bufferSize, bufferSize, sampleRate);

    // setup beat object
    beat.setup();
    //beat.setup("default", 2 * bufferSize, bufferSize, samplerate);
    // listen to beat event
    ofAddListener(beat.gotBeat, this, &ofApp::beatEvent);

    // setup mel bands object
    bands.setup();

    ofSoundStreamListDevices();

    ofSoundStreamSettings settings;
    settings.numOutputChannels = 0;
    settings.numInputChannels = 1;
    settings.setOutListener(ofGetAppPtr());
    settings.setInListener(ofGetAppPtr());
    //settings.numBuffers = nBuffers;
    //settings.sampleRate = sampleRate;
    //settings.bufferSize = bufferSize;

    ofSoundStreamSetup(settings);
    //ofSoundStreamSetup(nOutputs, nInputs, sampleRate, bufferSize, nBuffers);
    

    // setup the gui objects
    // GUI ofxAubioBeat
    int start = 0;
    beatGui.setup("ofxAubioBeat", "settings.xml", start + 10, 10);
    beatGui.add(beatThreshold.setup( "threshold", 0, 0, 2));
    beatGui.add(tatumSig.setup("tatum signature", 1, 1, 64));
    beatGui.add(bpm.setup( "bpm", 0, 0, 250));
    beatGui.add(beatConfidence.setup ("beat confidence", 0, 0, 1));
    beatGui.add(tatum.setup ("tatum", 0, 0, 2));
    tatumSig = beat.tatumSignature;
    beatThreshold = beat.threshold;

    // GUI ofxAubioOnset
    start += 250;
    onsetGui.setup("ofxAubioOnset", "settings.xml", start + 10, 10);
    onsetGui.add(onsetThreshold.setup( "threshold", 0, 0, 2));
    onsetGui.add(onsetCompression.setup("compression", 0, 0, 10));
    onsetGui.add(onsetWhiteningEn.setup( "whitening", false));
    onsetGui.add(onsetMinioi.setup( "min interval", 0, 0, 2000));
    onsetGui.add(onsetNovelty.setup( "onset novelty", 0, 0, 10000));
    onsetGui.add(onsetThresholdedNovelty.setup( "thr. novelty", 0, -1000, 1000));
    // set default value
    onsetThreshold = onset.threshold;
    onsetMinioi = onset.minioi;
    onsetWhiteningEn = onset.whiteningEn?(true):(false);
    onsetCompression = onset.compression;

    // GUI ofxAubioOnset2
    start += 250;
    onset2Gui.setup("ofxAubioOnset2", "settings.xml", start + 10, 10);
    onset2Gui.add(onset2Threshold.setup( "threshold", 0, 0, 2));
    onset2Gui.add(onset2Compression.setup("compression", 0, 0, 10));
    onset2Gui.add(onset2WhiteningEn.setup( "whitening", false));
    onset2Gui.add(onset2Minioi.setup( "min interval", 0, 0, 2000));
    onset2Gui.add(onset2Novelty.setup( "onset novelty", 0, 0, 10000));
    onset2Gui.add(onset2ThresholdedNovelty.setup( "thr. novelty", 0, -1000, 1000));
    // set default value
    onset2Threshold = onset2.threshold;
    onset2Minioi = onset2.minioi;
    onset2WhiteningEn = onset2.whiteningEn?(true):(false);
    onset2Compression = onset2.compression;

    // GUI ofxAubioPitch
    start += 250;
    pitchGui.setup("ofxAubioPitch", "settings.xml", start + 10, 10);
    pitchGui.add(midiPitch.setup( "midi pitch", 0, 0, 128));
    pitchGui.add(pitchConfidence.setup( "confidence", 0, 0, 1));

    // GUI ofxAubioMelBands
    bandsGui.setup("ofxAubioMelBands", "settings.xml", start + 10, 115);
    for (int i = 0; i < 40; i++) {
        bandPlot.addVertex( 50 + i * 650 / 40., 240 - 100 * bands.energies[i]);
    }
}

void ofApp::exit(){
    ofSoundStreamStop();
    ofSoundStreamClose();
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // compute onset detection
    onset.audioIn(input, bufferSize, nChannels);
    // compute onset2 detection
    onset2.audioIn(input, bufferSize, nChannels);
    // compute pitch detection
    pitch.audioIn(input, bufferSize, nChannels);
    // compute beat location
    beat.audioIn(input, bufferSize, nChannels);
    // compute bands
    bands.audioIn(input, bufferSize, nChannels);
}

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::update(){
    onset.setThreshold(onsetThreshold);
    onset.setCompression(onsetCompression);
    onset.setMinioi(onsetMinioi);
    onset.setWhiteningEn(onsetWhiteningEn);

    onset2.setThreshold(onset2Threshold);
    onset2.setCompression(onset2Compression);
    onset2.setMinioi(onset2Minioi);
    onset2.setWhiteningEn(onset2WhiteningEn);

    beat.setThreshold(beatThreshold);
    beat.setTatumSig(tatumSig);
}

//--------------------------------------------------------------
void ofApp::draw(){
    // update beat info
    if (gotBeat) {
        ofSetColor(ofColor::green);
        ofRect(90,150,50,50);
        gotBeat = false;
    }
    bpm = beat.bpm;
    beatConfidence = beat.confidence;
    tatum = beat.tatum;
    beatGui.draw();

    // update onset info
    if (gotOnset) {
        ofSetColor(ofColor::red);
        ofRect(250 + 90,150,50,50);
        gotOnset = false;
    }
    onsetNovelty = onset.novelty;
    onsetThresholdedNovelty = onset.thresholdedNovelty;
    onsetGui.draw();

    // update onset2 info
    if (gotOnset2) {
        ofSetColor(ofColor::red);
        ofRect(500 + 90,150,50,50);
        gotOnset2 = false;
    }
    onset2Novelty = onset2.novelty;
    onset2ThresholdedNovelty = onset2.thresholdedNovelty;
    onset2Gui.draw();

    // update pitch info
    pitchConfidence = pitch.pitchConfidence;
    if (pitch.latestPitch) midiPitch = pitch.latestPitch;
    pitchGui.draw();
    
    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.);
    bandsGui.draw();
    //bandPlot.clear();
    for (int i = 0; i < (int)bandPlot.size(); i++) {
        bandPlot[i].y = 240 - 100 * bands.energies[i];
    }
    bandPlot.draw();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

//----
void ofApp::onsetEvent(float & time) {
    //ofLog() << "got onset at " << time << " s";
    gotOnset = true;
}

//----
void ofApp::onset2Event(float & time) {
    //ofLog() << "got onset at " << time << " s";
    gotOnset2 = true;
}

//----
void ofApp::beatEvent(float & time) {
    //ofLog() << "got beat at " << time << " s";
    gotBeat = true;
}
