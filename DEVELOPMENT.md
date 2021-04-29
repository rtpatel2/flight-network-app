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
