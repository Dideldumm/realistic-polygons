[[Notes - Linear Time Algorithms For Visibility And Shortest Path Problems Inside Simple Polygons]]

# Calculating the Shortest Path Tree of a Simple Polygon
## Thoughts before the algorithm
Let $P$ be a simple polygon having $n$ vertices and let $s$ be a given _source vertex_ of $P$ 
- the algorithm will also apply in case $s$ is an arbitrary point interior or on the boundary of $P$
Denote, for each vertex $v$ of $P$, the Euclidean shortest path from $s$ to $v$ inside $P$ by $\pi(s,v)$. 
- It is well known that $\pi(s,v)$ is a polygonal path whose corners are vertices of $P$ (see [[#LP]]) 
- The Union $\cup_v \pi(s,v)$, taken over all vertices $v$ of $P$, is a planar tree $Q_{sp}$ (rooted at $s$), which we call the _shortest path tree_ of $P$ with respect to $s$.
- This tree has altogether $n$ nodes, namely the vertices of $P$, and its edges are straight segments connecting these nodes. 
Our goal is to calculate this tree in linear time.

Let $G$ be a triangulation of the interior of $P$ 
- which can be computed in $O(n)$ time using Tarjan and Van Wyk's algorithm
The planar dual Graph $T$ of $G$ is a tree.
- the vertices of $T$ are the triangles in $G$ and the edges in $T$ join two such triangles if they share an edge
Each vertices of that tree has a degree of at most 3. Thus, for each vertex $t$ of $P$, there is a unique minimal path $\pi$ in $T$ from some triangle containing $s$ to another triangle containing $t$, which induces an ordered sequence of diagonals $d_1, d_2, ..., d_l$ of $P$ 
- $d_1$ should be chosen as the first diagonal between two adjacent triangles in $\pi$ which does not terminate at $s$ 
- $d_l$ should be chosen as the last such diagonal not not terminating at $t$
- This takes care of situations in which $s$ or $t$ is a vertex of more that one triangles in $G$
Each diagonal $d_l$ thus divides $P$ in two parts containing $s$ and $t$ respectively and therefore $\pi(s,t)$ must intersect only diagonals $d_l$, and each of them exactly once.

Let $d=uw$ be a diagonal or an edge of $P$ and let $a$ be the least common ancestor of $u$ and $w$ in the shortest path tree $Q_{sp}$. It is shown in [[#LP]] that $\pi(a, u)$, $\pi(a, w)$ are both _outward convex_. Following [[#LP]] we cam call the union $F = F_{uw} = \pi(a,u) \cup \pi(a,w)$ the [[#^27ef42|funnel]] associated with $d=uw$, and $a$ is the $cusp$ of that funnel. (_cusp_ heißt Scheitelpunkt auf deutsch)
Suppose next that $d$ is a diagonal of $P$ used by $G$, and let $\Delta uwx$ be the unique triangle in $G$ having $d$ as an edge, which does not intersect the area bounded between $F$ and $d$. Then the shortest path from $s$ to $x$ must start with $\pi(s,a)$ and then either continue along the straight segment $ax$ if this segment does not intrersect $F$, or else proceed along either $\pi(a,u)$ or $\pi(a,w)$ to a vertex $v$ such that $vx$ is a tangent to $F$ at $v$, and then continue along the straight segment $vx$. (see [[#^27ef42|Fig 2.1]]). 
These observations form the basis of the algorithm.

![funnel_image](images/ShortestPathFunnel.png)^27ef42

## Description of the algorithm
We first triangulate $P$ in $O(n)$ time as in [[#TV]]. As the algorithm comes to process a diagonal $d=uw$ of $P$, it maintains the current funnel $F=F_{uw}$ as a sorted list $[u_l, u_{l-1}, ..., a, w_1, ..., w_k]$, where $a=u_0=w_0$ is the cusp of $F$, $\pi(a,u)=[u_0,...,u_l]$, $\pi(a,w)=[w_0,...,w_k]$, and $u_l=u$, $w_k=w$. This list is stored in a _finger tree_. This structure is essentially a search tree equipped with _fingers_, which in our application are always placed at the first element and at the last element of the tree. This structure supports searching for an element $x$ in time $O(log \delta)$, where $\delta$ is the distance from $x$ to the nearest finger, and also supports operations that split the tree into two subtrees at an element $x$ in amortized time $O(log \delta)$. The algorithm also maintains a pointer $CUSP(F)$ to the cusp $a$ of the present funnel.
The algorithm begins by placing $s$ and an adjacent vertex $v_1$ in $F$, with $CUSP(F)=s$. It the proceeds recusively as follows.
**Algorithm_Path(F)**
- Let $u$ and $w$ be the first and the last elements of $F$, and let $a=CUSP(F)$ (thus $F=\pi(a,u)\cup\pi(a,w)$). 
- Let $\Delta uwx$ be the unique triangle in the triangulation $G$ of $P$ that has $uw$ as an edge and that has not yet been processed

# 2. 
Given a fixed edge $e$ of $P$, calculate the subpolygon $Vis(P, e)$ consisting of all points in $P$ visible from the $e$.
- $Vis(P,e)$ denotes the visibility polygon that is visible from the edge $e$ bounded by the polygon $P$
# 3.


# Sources used by this paper
## LP
## TV

