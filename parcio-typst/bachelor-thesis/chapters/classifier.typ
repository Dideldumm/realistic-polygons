= Classifier

== What is a classifier

== Why use a classifier
- Task: Automatically differentiate between realistic and unrealistic polygons
- not a trivial Task
- first idea: mathematical property to distinquish
- could not find a useful property 
- maybe a set of properties? -> to complex
- The classifier needs a lot of data
- data can be generated easily

= Training the classifier
- Need for realistic and unrealistic polygons for training

== Open street map data for realistic polygons
- Downloading the data
- using osmium to filter the data for realistic polygons
- in this case for lakes
- //image?
- exporting the results geojson format
- parsing the data using cpp to filter for polygons and collect the vertices of these polygons
- write the collected points in a .csv file

== CGALs random polygon generator for unrealistic polygons
- An algorithm to generate a random polygon for a given set of vertices
- Generate a set of random points first
- Get the random polygon from the algorithm for that set of points
- write the vertices of that polygon in a .csv file