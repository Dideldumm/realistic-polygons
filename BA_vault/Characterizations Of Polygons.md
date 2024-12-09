# Basic Terms

## Visibility
 Point *p* sees point *q* if the line section $\overline{pq}$ is completely inside a Polygon *P*

## Convex and reflex vertices
A vertex *v* is convex if its internal angle is less than 180° otherwise *v* is reflex

## Convex Chains
A path of points $p_1, ..., p_n$ is a convex chain, if for every edge of the chain the adjacent edges lie on the same side

## Diameter
The diameter of a set of points is the maximum distance between two points of the set.

## Fatness 


# Characterizations Of Polygons
## Simple Polygons
A Polygon is simple if its edges only intersect at their end points.

Every realistic Polygon is simple.

## $k$-Convex Polygons
Given a Polygon $P$ and any two points $p,q$ inside $P$. $P$ is $k$ -convex, if the intersection of $P$ with the line through $p$ and $q$ results in $k$ or less connected segments.

## $k$-Point Convex Polygons
A Polygon $P$ is $k$ -point convex, if for any $k$ points in $P$, at least one of the line segments they span is contained in $P$.

More intuitively: In a $k$-point convex Polygon it is impossible to find $k$ points, such that none of those sees at least one other point.

## $k$-Link Convex Polygons
Given a Polygon $P$ and two points $p,q$ inside $P$. $P$ is $k$ link convex, if the shortest path inside $P$ that connects $p$ with $q$ has at most $k$ edges.

## $k$-Guardable Polygons
A Polygon $P$ is $k$ -guardable, if there exists a set of $k$ points (guards) in $P$, such that every point of the boundary of $P$ can be seen by at least one of the guards.

## $k$-Border Guardable Polygons
A Polygon $P$ is $k$ -border-guardable, if there exists a set of points $Q$, such that every point of $P$ is visible from at least $k$ elements in $Q$ and no edge of $P$ has more than one element in $Q$.

## $\varepsilon$-Good Polygons
A Polygon $P$ is $\varepsilon$ -good, if each point in $P$ sees at least a certain fraction $\varepsilon$ of $P$.

## $\alpha$ -fat Polygons
A Polygon $P$ is $\alpha$ -fat, if $P$ is contained in some axis-parallel square $S⁺$ and $P$ contains another axis parallel square $S⁻$, so that the ration between the edge length of $S⁺$ and $S⁻$ is at most $\alpha$.

$a$ -fatness is rotation sensitive so it may be a good idea to use circles instead of squares.

## $\beta$ -fat Polygons
A Polygon $P$ is $\beta$ -fat, if for every circle $b$ whose Center is inside $P$ and which does not contain $P$ completely, the $volume (b\cap P)$ is at least $\beta \cdot volume(b)$

## $(\alpha, \beta)$ -covered Polygons
A Polygon $P$ is $(\alpha, \beta)$ -covered, if for each point $p$ on the boundary of $P$ there exists a triangle $T(p)$, called a good triangle of $p$, such that
1. $p$ is a vertex of $T(p)$
2. $T(p)$ is completely  contained in $P$
3. each angle of $T(p)$ is at least $\alpha$
4. the length of each edge of $T(p)$ is at least $\beta \cdot diameter(P)$



