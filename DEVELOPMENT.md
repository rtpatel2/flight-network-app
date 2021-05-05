##Development Log

###4/12/21-4/19/21
We began by getting our work environments set up with CLION, CMAKE, and CINDER.
We then began designing our implementation for the graph data structure. Initially,
we thought we would represent the graph with a map of string keys, each representing an airport code.
However, we will need to store the locations of the airports for the visual component as well as for
computing the distances between airports. Instead of storing parallel data structures for the airport locations,
we ultimately decided to create an Airport class that contains the code of the airport and its location.
Since our Airport objects are now the keys in our graph, we had to write a hash function for them and decided to use the
string codes of the airports since they are unique. So far we have successfully implemented the data parsing in network.cc to
populate the graph with nodes and edges, including some regex logic for cleaning the input data.

###4/20/21-4/28/21
This week Rishi implemented distance calculations between each adjacent airport to be stored in the graph data structure for easy access. Shruthik tested the accuracy of these calculations and the 
data parsing. Manik and Jeremy implemented Djikstra's algorithm to compute the shortest distance to every airport from a starting airport.
 Currently, the method returns the shortest distance from a starting airport to a specified airport, but next week we will easily change
this to instead return an unordered map of distances to each airport to be used as a helper function for the optimal airport to meet at for 2 friends.
In this method, we plan to use the Djikstra algorithm method and call it on each of the 2 friend airports,
and then find the minimum combined distance for both of them. This week we discovered that Cinder does not come pre-installed on EWS, and so we will
instead use the cs225 PNG class for the visualization. Next week we plan to finish the algorithm for the optimal meeting airport for 2 friends 
and test its accuracy. We also will begin working on the visualization component, starting with helper functions that will project a (lat, long) coordinate
onto a Mercator projection of a US map. We have started to look into the necessary equations for such transformations but will narrow down which ones work best once
we begin implementing.

###4/29/21-
This week we discovered that incorporating the cs225 library for PNG and Animation classes would not compile locally on non-Linux computers. Thus we instead decided to use a traditional make file and develop on EWS. Jeremy used the make files from MP Traversals as a template and built around it to now support commands for building the main executable as well as the test suite for our project. 
We also noticed some inefficiency in our design for the Network class. Because our main data structures in that class mapped with Airport objects as keys, we were often initializing Airport objects each time we wanted to access elements in the map. This was a substantial waste of computer memory and time. Instead, we decided to modify our maps to use std::string as keys, which are more efficient and flexible. Rishi refactored the Network class, and all relevant test cases, to reflect these changes.
Our implementation of Dijkstra's algorithm currently only found the length of the shortest path between two provided airports. We realized that our usage of Dijkstra's algorithm relied on having the shortest paths from one starting airport to all other airports. However, the classic implementation of Dijkstra's algorithm computes all of those values with no extra time, similar to Prim's algorithm or a graph BFS. Thus, Rishi modified the function to return a full map between airport code and length of shortest path from the starting airport to that specific destination airport.
Now that the cs225 library has been linked, we (Jeremy, Manik, Rishi, and Shruthik working in the same room) implemented the basic functionality of our Map class that successfully draws all of the airports in the dataset onto a Mercator projection.
Shruthik also incorporated the KDTree class from MP Mosaics and refactored it to deal with wraparound and other specific changes necessary with a globe rather than a rectangular plane. Rishi added tests for this functionality as well, and in the process we discovered a few bugs regarding how we measure distance to the hyperplane on the equator rather than at a particular latitude or longitude which the four of us worked to fix.

For next week, we plan to finish the project. This includes adding a command line interface to pass parameters such as friend airports or the BFS visualization origin airport. We will also thoroughly test the remaining untested fucntionality. We will clean up the codebase and add documentation where necessary. Finally, we will draft a README that explains the project and how to run the executables.