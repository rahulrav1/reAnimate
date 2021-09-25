
# Leading Question

In order to produce an animation of any kind, an image must move slowly and in small steps between frames in order to look natural. The goal of the project is to proceed between images specified by the user to produce the most natural-looking animation based on a set of pre-produced images. In our project, we will be using sprites from video game characters, as they have a wide variety of different poses they may find themselves in that need to be interpolated between, while still having a small enough size to make complicated processing take a reasonable amount of time.

  

## Dataset Acquisition and Processing

The data can be taken from game files themselves, or from widely available sprite sheets. It is image data, so all sprites should be on individual images of the same size.

## Graph Algorithms

First, a metric between images would be determined through dimensionality reduction (most likely LLE)

## Graph Algorithm Options:

### K sized ball:

An image node will be connected to any node within k amount of distance of it, optimal pathfinding algorithm A* will be run to find the quickest path with no jumps in distance over K.

### K number of neighbors

An image node will be connected to its closest K neighbors and an optimal pathfinding algorithm A* will be run to determine the quickest path that only moves between neighbors

### Modified Optimal Pathfinding 

All nodes are connected to all other nodes. We modify Dijkstra’s algorithm to, instead of finding the shortest path, find the path with the smallest largest member.

### MST (serves as an addition to the above options)

Can be utilized to determine the quickest route given a smoothness threshold.

## Timeline

### Week 1: April 9-16

Data set must be determined and obtained

Dimensionality reduction algorithm must be determined

Start implementing Dimensionality Reduction algorithm

### Week 2: April 17-23

Dimensionality Reduction algorithm should be finished (untested)

### Week 3: April 24-30

The pathfinding algorithm should be finished (untested)

### Week 4: May 1-7

Code should run

Testing code

### Week 4.5: May 8-12

Debugging, testing, cleaning up code