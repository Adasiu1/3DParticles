#include "ofMain.h"
#include "ofApp.h"

int main()
{
    ofGLWindowSettings settings;
    settings.setSize(1024, 1024);
    settings.windowMode = OF_WINDOW;

    ofCreateWindow(settings);

    ofRunApp(std::make_shared<ofApp>());

    return 0;
}
