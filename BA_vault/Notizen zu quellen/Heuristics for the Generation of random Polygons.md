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
- Vertices of a polygon $v_1, ..., v_n$ are assumed to be in counter clockwise order
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
The algorithm cannot generate all possible simple polygons for the given set of points.

Initially
- Let $S'$ be a subset of $S$
	- thus $CH(S')$ does not contain any point from $S\setminus S'$ 
- When generating a Polygon $P$ it is ensured that the intersection of $P$ with $CH(S')$ consists of a single chain
	- $s'_f$ is the first and
	- $s'_l$ is the last point of that chain
	- both points are located at the boundary of $CH(S')$
- initially $s'_f$ and $s'_l$ are chosen randomly
-  **TODO check:** all points on one side of $l(s'_f, s'_l)$ and the points itself determine $S'$
	- the rest of the points remains in $S$

To split a subset $S'$ in two smaller subsets $S''$ and $S'''$ 
- Pick a point $s'\in S'$ at random
- Select a random line $l$ through $s'$ that intersects $\overline{s'_fs'_l}$ 
- the line divides $S'$ into two smaller subsets $S''$ and $S'''$
	- $S''$ has $s'_f$ as first and $s'$ as last point
	- $S'''$ has $s'$ as first and $s'_l$ as last point

The recursion ends if a subset has only two points or less in it.

### Permute & Reject
Creates random permutations until a simple polygon is encountered.

### 2-opt Moves
Generates a random (non-simple) polygon and repairs the deficiencies.

- Initialize a Polygon $P$ with a random permutation of $S$ 
- Iteratively remove all self intersections of $P$ with 2-opt moves
	- replace a pair of intersection edges
	- $(v_i,v_{i+1}), (v_j,v_{j+1}) \Longrightarrow (v_{j+1},v_{i+1}), (v_j,v_i)$ 

The number of intersections to be removed is at most $O(n^3)$, which makes this algorithm run in $O(n^4)$ 
The algorithm can find all possible simple polygons for the given set of points but not uniformly distributed.

### Incremental Construction & Backtracking
Tries to minimize backtracking by eliminating dead search trees.

- Choose a random point
- Iteratively add more random points until the chain of points is not longer simple
	- **TODO check:** i think that means we make a polygon in each iteration with the points we have and check if that polygon is simple or not
- Stop when all points from $S$ could be added, or the chain is no longer simple
	- for the latter -> backtrack

Goal is to avoid extensive backtracking.
To achieve this, edges that are not usable to complete a polygon are marked

- Initially all edges are unmarked
- When a new point is added, thus using edge $e$
	- -> all edges that intersect $e$ are marked
- additionally if a point $p$ is adjacent to two other points $p_1, p_2$ that both
	- have only two unmarked edges
	- -> mark all edges incident to $p$, but those also incident to $p_1$ or $p_2$
- 