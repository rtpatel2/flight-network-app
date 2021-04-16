## CS 225 Final Project Proposal

### Leading Question

Say two friends live very far apart -- possibly across a very large country or continent, or several continents apart. If these two friends wanted to meet, how would they decide where to fly? One could fly to the other, but one friend has to travel much further than the other. Alternatively, consider if they wanted to explore a new city together. How might they find the most convenient city, closest to both by flight? We will create an application that will determine the best airport for two friends to meet at, given their departure airports. The best airport will be the one where the travel distance for both friends is roughly equal and minimized. 

### Dataset Acquisition & Processing

We will use public flight data from [openflights.org](https://openflights.org/data.html); specifically, we will use this data of [airports](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat) and [flight routes](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat). The data is already available in CSV format, and will be easily parseable via C++. We will use this data to build a directed graph, where the airports serve as nodes and the flights serve as directed edges. This data can be maintained as a two-dimensional map with the following keys and values: 

```std::unordered_map<std::string, std::unordered_map<std::string, double>> graph``` 

If a flight exists from airport A to airport B, then graph[A][B] will be the distance between the airports. If a flight does not exist between airports A and B, then graph[A] will not contain B as a key. If there are flights in the data to or from an airport not maintained in our data, we will disregard this flight.

### Graph Algorithms

First, the two friends will want to know which airport

We will use the longitude and latitude of the airports to determine the travel distance from one departure airport to a valid arrival airport. These values will serve as weights for the edges connecting airports. We will use a graph traversal algorithm, specifically Dijkstra's algorithm, to determine the shortest path between the two starting airports and all other airports. This algorithm will rely on a breadth-first search and a priority queue in order to compute the shortest possible path. The algorithm will take the aforementioned two-dimensional map as well as the names of the two starting airports as inputs. The algorithm will be $$O(n + m)$$ time complexity, where $$n$$ is the number of airports and $$m$$ is the number of connecting flights. We can then iterate through the shortest paths from the two starting airport to all other airports in $$O(n)$$ time to determine the optimal airport for the two friends to meet. 

In order to help the friends decide from which airports to begin their trips, we will implement a k-d tree rooted at the starting location (longitude and latitude), and all the non-root nodes of the tree will be airports. Using a nearest neighbor algorithm, we will be able to determine which airport is closest to a specified starting location. This algorithm will require the longitude and latitudes of each of the airports as input, as well as the starting location. It will output the closest airport as an std::string. Building a k-d tree will run in $$O(d * nlog(n))$$, where $$d$$ is the number of dimensions of the k-d tree (in this case, $$ d = 2$$), and $$n$$ is the number of airports. Finding the nearest neighbor will run in $$O(nlog(n))$$. 

We will also use include a visualization component regarding flights within the contiguous US. The user will specify a starting airport, and using the Cinder library we will draw a breadth-first traversal from the starting airport in real-time. As we arrive at new airports (nodes) in our traversal, we will draw them in the visualization at their appropriate geographic location with a circle. As the number of inbound and outbound flights to an airport increases, we will increase the size of the circle on the visualization, thereby allowing the user to identify the most accessible airports. This algorithm will require the starting airport and the aforementioned two-dimension map ```graph``` as inputs, and will perform the breadth-first traversal in $$O(n + m)$$, where again $$n$$ is the number of airports and $$m$$ is the number of connecting flights.

### Timeline

Our current tasks are data processing, computing weights for the edges, implementing Dijkstra's algorithm to determine the shortest path between airports and determining the best airport for the friends to meet, implementing the k-d tree and nearest neighbor algorithm, and implementing the breadth-first traversal and visualization logic.

By April 19th, we plan to complete the data processing.

By April 23rd, we plan to implement Dijkstra's algorithm and to build an algorithm to determine the best airport for the friends to meet.

By April 26th, we plan to implement the k-d tree and nearest neighbor algorithm.

By May 3rd, we plan to implement the visualization and breath-first traversal algorithm.

By May 10th, we plan to finalize and clean up our code base, and to prepare the report, README file for Github, and presentation.
