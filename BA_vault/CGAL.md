- Kernels 
	- provide most basic data structures, and functions
		- points
		- segments
		- orientation of points
		- etc
	- kernels can have 
		- exact or inexact predicates
		- exact or inexact constructions
	- exact is obviously more useful but 
- `CGAL::convex_hull_2(ForwardIterator begin, ForwardIterator end, OutputIterator result)`
	- Will create the *convex hull* for the points between `begin` and `end` and put that convex hull in the `result`

### Ausprobieren
#### Polygon ohne Überschneidungen

von StackOverflow
```
- find the leftmost point p
- find the rightmost point q
- assign all points above the line of p and q to set A
- assign all points below the line of p and q to set B
- sort the points in A by x-coordinate (increasing)
- sort the points in B by x-coordinate (decreasing)
- The Polygon defined by {p, A.getPoints, q, B.getPoints} will define a Polygon without intersections
```

