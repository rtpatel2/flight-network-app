#pragma once


#include <cinder/app/App.h>

namespace visualizer {
        class FlightApp : public ci::app::App {
        public:
            /** Creates a new IdealGasApp instance. **/
            FlightApp();

            /** Draws the next frame of the simulation. **/
            void draw() override;

        private:

        };
    }  // namespace visualizer

