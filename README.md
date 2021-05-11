# Flight Network App


## Authors
- Rishi Patel | rtpatel2@illinois.edu
- Jeremy Livshots | jel7@illinois.edu
- Manik Jain | manikj2@illinois.edu
- Shruthik Musukula | srm14@illinois.edu

## Table of Contents
- [Overview](#overview)
- [Running the App](#running-the-app)
- [Demo](#demo)
- [Citations](#citations)

## Overview
We created an application providing three analyses related to determining the best airport for two friends in different parts of the world to meet. The primary functionality of our codebase, as well as the function to find the best airport for two friends to meet, is located in the Network class. The Airport class is fairly simple, only maintaining relevant fields about one airport. The KDTree class is used to perform a nearest neighbor search, in order to determine the airport closest to a person based on given latitude and longitude coordinates. The Map class is used to visualize a breath-first traversal from a given starting airport and output the result as a PNG and GIF. The main.cpp file contains the logic for parsing CLI arguments and executing the appropriate functions.

CLI arguments can be executed based on any datapaths provided by the user. Our main datasets can be found in the data folder, and the datasets used for unit testing can be found in the tests/data folder. Additionally, there is one GIF and one PNG in the directory by default -- these are produced by performing a breadth-first traversals of airports starting at ORD. Similar PNG/GIFs can be produced via the command-line, as discussed in the [Running the App](#running-the-app) section.

## Running the App
Requirements:
- GCC
- Bash command line

To install, simply clone this repository onto your local machine. To run the code, use the command `make flights` to compile the code and build necessary executables. In order to run the executable, use one of the following commands to run one of the three primary algorithms of our app:

```
./flights find_best_airport <airport_data> <flight_data> <first_airport> <second_airport> [tolerance]
./flights animate_bfs <airport_data> <flight_data> <starting_airport> <gif_output_file> <last_frame_output_file>
./flights find_closest_airport <airport_data> <flight_data> <starting_latitude> <starting_longitude>
```

To run the test suite, use `make test` followed by `./test`. The test suite thoroughly tests all non-trivial functions we implemented, excluding functions whose primary purpose is to write to files. We have tested for file parsing, computing the distance between two latitude/longitude coordinates, determining best airport for two friends to meet, finding nearest neighbor in a KDTree, projecting a latitude/longitude coordinate onto a Mercator map of the Earth, and modifying pixels on a map to be outputted as a PNG or GIF.

## Demo

A breadth-first traversal starting at ORD:
![bfs.gif](https://i.imgur.com/WnhFmdD.gif)
This GIF shows out all airports that can be reached by a sequence of one or more flights from ORD; the darker the color, the fewer flights are required.

The breadth-first traversal also outputs a PNG of the complete breadth-first traversal.
![last_frame_bfs.png](https://i.gyazo.com/7257efa7296c5f13249781253f093874.jpg)

The other functionalities produce output to the console, so there aren't similarly interesting visualizations for those pieces of functionality.

## Citations

Our main dataset for airports and flight data was sourced from [openflights.org](https://openflights.org/)
