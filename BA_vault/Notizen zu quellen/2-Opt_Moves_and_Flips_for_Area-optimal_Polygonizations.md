[[2-Opt_Moves_and_Flips_for_Area-optimal_Polygonizations.pdf]]

# Summary
## Abstract
- based on two key components
	1. sampling the search space to obtain initial polygonizations
	2. optimizing such a polygonizations
- Creates a polygonization for a random given set of points
- relies on 2-opt moves and line sweep
## Introduction
- 2 components: 
	- **Sampler**: computes an initial simple polygonization of *P*
	- **Optimizer**: modifies a given polygonization to optimize its area, while maintaining the simplicity
- two samplers are
	- [RandomPolygonGenerator](https://github.com/cgalab/genpoly-rpg)
	- [SweepPolygonGenerator](https://github.com/cgalab/genpoly-spg)
- the Optimizer is
	- [PAO-Flip](https://github.com/cgalab/pao-flip)

## Methods
### Polygonization
- RPG-star
	- compute the convex hull *CH(P)* of *P* 
	- pick a random locus *p* within *CH(P)*
	- sort the Points of *P* radially around *p*
	- obtains a star-shaped polygonization
	- runs in *O(n log n)*
- RPG-space
	- divide and conquer approach
	- partition *P* recursively into two subsets with disjoint convex hulls
	- the recursion ends when a subset has 3 or less points
	- trivially find a chain of vertices in each subset
	- splice the chains together to obtain the polygonization
	- worst time *O(n²)* expected *O(n log n)*
- RPG-2opt
	- initial non-simple polygon by random permutation of input points
	- remove self-intersections by applying 2-opt moves
	- [[2-opt-move.svg.png]]
	- *O(n³)* 2-opt moves may be needed to convert an initial polygon into a simple polygonization

### PAO-Flip
