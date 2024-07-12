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
- the kernels of two distinct star-shaped polygons share at most one edge

... complicated stuff

### Quick Star
Wir mache basically einen rotational plane sweep
- Any point in $CH(S)$ defines a star-shaped polygon
- Choose a random point $p$ within $CH(S)$
- Sort the points of $S$ around $p$

## Simple Polygons
### Steady Growth
An **incremental algorithm** adding one point after another.
- Init by selecting three points $s_1,s_2,s_3\in S$ 
	- such that no other point of $S$ lies within $CH(\{s_1,s_2,s_3\})$ 
	- Let $S_1:=S\setminus\{s_1,s_2,s_3\}$  
- During the $i$-th iteration with $1\leq i\leq n-3$ 
	- Choose a point $s_i\in S_i$ 
		- such that no other Point lies within $CH(P_{i-1}\cup\{s_i\})$ 
	- Find an edge $(v_k,v_{k+1})$ of $P_{i-1}$ that is completely visible from $s_i$ and replace it with the edges $(v_k,s_i)$ and $(s_i, v_{k+1})$ 


### Space Partioning
A **divide and conquer** algorithm that recursively partitions $S$ into subsets which have disjoint convex hulls.




### Permute & Reject
Creates random permutations until a simple polygon is encountered.

### 2-opt Moves
Generates a random (non-simple) polygon and repairs the deficiencies.

### Incremental Construction & Backtracking
Tries to minimize backtracking by eliminating dead search trees.