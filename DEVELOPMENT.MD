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