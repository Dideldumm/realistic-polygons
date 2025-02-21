#! usr/bin/bash


SECONDS=0
echo "Starting geojsonparser"
../build/geojsonparser "../build/data/bremen-lakes.geojson" "../sklearn/data/realistic.csv"
echo "geojsonparser ended - time elapsed: " $SECONDS
max_points=$(bat "../sklearn/data/realistic.csv.metadata" -r 1:1)
number_of_polygons=$(bat "../sklearn/data/realistic.csv.metadata" -r 2:2)
echo "Maximum number of points: " $max_points
echo "Number_of_realistic_polygons: " $number_of_polygons "\n"
echo "Starting generation of unrealistic polygons"
SECONDS=0
../build/unrealisticPolygons "../sklearn/data/unrealistic.csv" $max_points $number_of_polygons
echo "Generation finished - time elapsed: " $SECONDS "\n"
echo "Starting sklearn"
SECONDS=0
python train_on_polygons.py "data/realistic.csv" "data/unrealistic.csv"
echo "Training finished - time elapsed: " $SECONDS

