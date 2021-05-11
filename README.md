# Flight Network App


## Authors
- Rishi Patel | rtpatel2@illinois.edu
- Jeremy Livshots | jel7@illinois.edu
- Manik Jain | manikj2@illinois.edu
- Shruthik Musukula | srm14@illinois.edu

## Table of Contents
- Overview
- Running the Code
- Demo
- Citations

## Overview
We created an application providing various analyses related to determining the shortest and roughly equal flight distance needed for two friends at two airports to meet. 

## Running the Code
Requirements:
- GCC
- Bash command line

To install, simply clone this repository onto your local machine. To run the code, use the command `make flights` to compile the code and build necessary executables. In order to run the executable, use one of the following commands:

```
./flights find_best_airport <first_airport> <second_airport> <tolerance>
./flights animate_bfs <starting_airport> <gif_output_file> <last_frame_output_file>
./flights find_closest_airport <starting_latitude> <starting_longitude>
```

To run the test suite, use `make test` followed by `./test'. The test suite thoroughly tests all non-trivial functions we implemented, excluding functions whose primary purpose is to write to files. We have tested for file parsing, computing the distance between two latitude/longitude coordinates, determining best airport for two friends to meet, finding nearest neighbor in a KDTree, projecting a latitude/longitude coordinate onto a Mercator map of the Earth, and modifying pixels on a map to be outputted as a PNG or GIF.
