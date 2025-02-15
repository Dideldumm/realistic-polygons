#! usr/bin/bash


../build/geojsonparser "../build/data/bremen-lakes.geojson" "../sklearn/data/realistic.csv"
max_points=$(bat "../sklearn/data/realistic.csv.metadata" -r 1:1)
number_of_polygons=$(bat "../sklearn/data/realistic.csv.metadata" -r 2:2)
echo "Maximum number of points: " $max_points
echo "Number_of_realistic_polygons: " $number_of_polygons
../build/unrealisticPolygons "../sklearn/data/unrealistic.csv" $max_points $number_of_polygons
python train_on_polygons.py "data/realistic.csv" "data/unrealistic.csv"

