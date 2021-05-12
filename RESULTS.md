## CS 225 Final Project Recap

### Final Deliverables

Our project included three main deliverables: a 2-Dimensional KD-Tree implementation with a find nearest neighbor algorithm to identify the closest airport to a given set of latitude/longitude coordinate pairs (friend's location), identifying the nearest airport for two friends to meet at using Djikstra's algorithm, and an animation of the Breadth-First Search from an identified starting airport. All algorithms work as expected and have corresponding demo(s) shown below.

### New Discoveries

One discovery we made by implementing the bfs gif is that many popular hub airports like O'Hare and JFK can get to the vast majority of airports in our dataset within 6 flights. Similarly, every continent (besides Antarctica) can be reached within 1-2 flights from such popular airports.

We also noticed that particular regions in northern Canada are mainly covered by smaller, regional airports. As such, we see in the bfs originating at O'Hare that there is a "trail" of airports that appear one at a time in northern Canada, indicating that these airports likely only serve small, local flights to neighboring regional airports. A similar observation applies to central Africa, central Alaska, northern Norway, and central Brazil. 

Using the color-coding of the last frame from the bfs, we can also draw conclusions about how interconnected two countries are. For example, the bfs from O'hare shows a surprising amount of purple in Japan, the Caribbean, coastal China, and Europe. This is likely attrituble to United States business and tourism interests abroad.

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
