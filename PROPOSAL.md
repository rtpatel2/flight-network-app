## CS 225 Final Project Proposal

### Leading Question

Say two friends live very far apart -- possibly across a very large country or continent, or several continents apart. If these two friends wanted to meet, how would they decide where to fly? One could fly to the other, but one friend has to travel much further than the other. Alternatively, consider if they wanted to explore a new city together. How might they find the most convenient city, closest to both by flight? We will create an application that will determine the best airport for two friends to meet at, given their departure airports. The best airport will be the one where the travel distance for both friends is roughly equal and minimized. 

### Dataset Acquisition & Processing

We will use public flight data from [openflights.org](https://openflights.org/data.html); specifically, we will use this data of [airports](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat) and [flight routes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat) to build a directed graph, where the airports serve as nodes and the flights serve as edges. The data is already available in CSV format, and will be easily parseable via C++.

### Graph Algorithms

We will use the longitude and latitude of the airports to determine the travel distance from one departure airport to a valid arrival airport. These values will serve as weights for the edges connecting airports. We will use a graph traversal algorithm, namely Dijkstra's algorithm, to determine the shortest path between the two starting airports and all other airports. This will be $$O(n + m)$$ time complexity, where $$n$$ is the number of airports and $$m$$ is the number of connecting flights. We can then iterate through these values in $$O(n)$$ time to determine the optimal airport for the two friends to meet. We will also use a connectivity algorithm to decide if there is a path between two airports, which also runs in $$O(n + m)$$ time. We will use a clustering algorithm to determine the main hub airports, which will receive higher precedence in terms of determining the best way for the two friends to meet, due to the added convenience.

### Timeline

Our current tasks are data processing, computing weights for the edges, using Dijkstra's algorithm to determine the shortest path between airports, and then finally iterating through to determine the best airport to meet. 

By April 12th, we plan to complete the data processing.

By April 19th, we plan to complete the computations for the weights of the edges and the connectivity algorithm.

By April 26th, we plan to implement Dijkstra's algorithm and to build an algorithm to determine the best airport for the friends to meet. 

By May 3rd, we plan to implement the clustering algorithm logic

By May 10th, we plan to finalize and clean up our code base, and to prepare the report, README file for Github, and presentation.
