## CS 225 Final Project Recap

### Final Deliverables

Our project included three main deliverables: a 2-Dimensional KD-Tree implementation with a find nearest neighbor algorithm to identify the closest airport to a given set of latitude/longitude coordinate pairs (friend's location), identifying the nearest airport for two friends to meet at using Djikstra's algorithm, and an animation of the Breadth-First Search from an identified starting airport. All algorithms work as expected and have corresponding demo(s) shown below.

### New Discoveries

Filler

### Final Demo

1) Find Closest Airport Given A Set of Lat, Long Coordinates
![find_closest_airport.png](https://i.imgur.com/L6InCPE.png)
The provided parameters refer to a point in South San Jose, CA. The nearest airport is successfully identified by the program as Reid-Hillview Airport, with airport code RHV.

2) Animate BFS Executable
![animate_bfs.png](https://i.imgur.com/7nxvZ5p.png)

A breadth-first traversal starting at ORD (O'Hare International Airport, Chicago, IL):
![bfs.gif](https://i.imgur.com/WnhFmdD.gif)

The breadth-first traversal also outputs a PNG of the complete breadth-first traversal.
![last_frame_bfs.png](https://i.gyazo.com/7257efa7296c5f13249781253f093874.jpg)

3) Find Best Airport Between Two Friends
![find_best_airport.png](https://i.imgur.com/rcYf4Yr.png)
Two friends, one in Chicago and one in San Jose, want to find the best airport to meet at from their airports of ORD (O'Hare International Airport) and SJC (San Jose International Airport). The best airport for the two friends to meet at is properly identified as SLC (Salt Lake City International Airport).

4) Test Executable
![tests.png](https://i.imgur.com/IbKKTM6.png)
Proof that our test suite produces accurate results for all aspects of the Flight Graph Platform.
