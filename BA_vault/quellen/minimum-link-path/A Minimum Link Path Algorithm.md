```
compute_minimum_link_path(start, end) {
	w(e[0]) = start;
	for (i=1; i>0; i++) {
		e[i] = w(e[i-1]);
		Compute V(e[i]);
		if (end in V(e[i])) {
			break;
		}
	}
	for (j=i; j>0; j--) {
		d[j] = a point on e[j] that can see d[j+1];
	}
	minimumLinkPath = {s=d[1], d[2], ..., d[i], d[i+1]=d}
	return minimumLinkPath
}
```

# Visibility Polygon 
```
compute_visibility_polygon(e) {
	P[1] = union of all the triangles that are intersected by e;
	V[1] = region of P[1] visible from e;
	for (j=2; TODO LOREM IPSUM; j++) {
		P[j] = P[j-1] vereinigt mit {|P[j-1] new triangles of T[1,k]}
		V[j] = region of P[j] visible from e;
		tjmax = highes indexed trinagle in P[j];
	}
	finalP = P[j] union {all triangles t[u] in T - T[1,k] whose least common ancestor with tjmax in G is indeced between eimin and jmax};
	V[e] = region of finalP visible from e;
}
