#include <visualizer/network_app.h>
#include <cinder/app/RendererGl.h>

using visualizer::FlightApp;

void prepareSettings(FlightApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(FlightApp, ci::app::RendererGl, prepareSettings);
