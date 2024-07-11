[[Heuristics_for_the_Generation_of_Random_Polygons.pdf]]
# Introduction

- random generation of simple polygons on a given set of points
- No polynomial-time solution is known for the **uniformly** random generation of simple polygons 
	- uniform in the sense that all possible polygons on that set of points have the same probability of being generated
- -> focus on heuristics that offer a good time complexity and still generate a rich variety of polygons
- **two main areas of application**
	1. testing the correctness 
	2. evaluating the CPU-time consumption 
	- of algorithms that  operate on polygons

## Notations
- Vertices of a polygon $v_1, ..., v_n$ are assumed to be in counterclockwise order
- A point of the input set $S$ is denoted by $s$ 
- A arbitrary point is denoted by $p$
- $P_i$ denotes the polygon obtained after the execution of phases $1$ through $i$ of the algorithm
- For a set $Q$ the convex hull is denoted as $CH(Q)$ 
- $l(p_1, p_2)$ stands for a line through $p_1$ and $p_2$ 
- The restriction to the line segment is denoted by $\overline{p_1p_2}$ 

The set of input points $S$ is assumed to be in general position
	- that means no 3 points are collinear 

# Algorithms
## Star shaped Polygons
### Star Universe
Algorithm for the enumeration of all star-shaped polygons on a given set of points

- a [star-shaped](Notizen%20zu%20quellen/Characterizations%20of%20real%20world%20Polygons) polygon $P$ is fixed once its kernel has been specified