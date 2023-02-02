#include "ofApp.h"
#include "ParticleUpdaters.h"

void ofApp::setup()
{
    // Ustawienie synchronizacji pionowej, aby zapobiec zacięciom w animacji.
    ofSetVerticalSync(true);
    // Ustawienie rozdzielczości okręgu, który jest rysowany.
    ofSetCircleResolution(100);
    // Pobranie aktualnego czasu.
    time = ofGetCurrentTime();

    // Dodawanie emiterów ognia i śniegu.
    particle_system.addEmitter(std::make_shared<FireEmitter>(1000, ofVec3f(0, 0, 0), 5));
  
    particle_system.addEmitter(std::make_shared<RainEmitter>(1000, ofVec3f(0, 300, 0), 100));

    // Tworzenie wektora wskaźników na updatery cząsteczek.
    std::vector<std::shared_ptr<ParticleUpdater>> updaters = {
        std::make_shared<GravityUpdater>(),
        std::make_shared<EulerUpdater>(),
        std::make_shared<FloorUpdater>(),
        std::make_shared<TimeUpdater>(),
        std::make_shared<TimeColorUpdater>()
    };

    // Dodawanie updaterów cząsteczek.
    for (const auto& updater : updaters)
    {
        particle_system.addUpdater(updater);
    }
}

void ofApp::update()
{
    // Sprawdzenie, czy minęła jedena sekunda od ostatniej zmiany położenia emiterów
    if (ofGetCurrentTime().getAsSeconds() - time.getAsSeconds() > 1.f)
    {
        // Aktualizacja czasu
        time = ofGetCurrentTime();

    }
    particle_system.update(float(ofGetLastFrameTime()));
}
void ofApp::draw()
{
    ofBackground(0);
    camera.begin();
    ofEnableDepthTest();
    
    //Narysuj system cząstek
    particle_system.draw();
    ofPushMatrix();
    ofTranslate(0, floor_level, 0);
    ofSetColor(ofColor(64,64,64,-200));
    ofDrawBox(1000, 0.1, 1000);
    ofPopMatrix();

    ofDisableDepthTest();
    camera.end();
    ofDrawBitmapString("Count | " + ofToString(particle_system.particles.alive_count), 40, 40);
}
