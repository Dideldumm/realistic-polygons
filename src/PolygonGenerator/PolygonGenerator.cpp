//
// Created by dideldumm on 20.02.25.
//

#include <argparse/argparse.hpp>

#include "../geojson/GeoJsonParser.h"
#include "../utils/PolygonCsvWriter.h"

enum GeneratorAlgorithm {
    GEOJSON_PARSER,
    CGAL_TWO_OPT,
    UNION_OF_CONVEX_HULLS
};

CsvWriter::Polygon map_to_polygon(GeoJsonPolygon const &polygon) {
    std::vector<CsvWriter::Point> mapped_vertices;
    for (const auto vertex: polygon.getVertices()) {
        CsvWriter::Point mapped_vertex(vertex.longitude, vertex.latitude);
        mapped_vertices.emplace_back(mapped_vertex);
    }
    return mapped_vertices;
}

std::vector<CsvWriter::Polygon> map_polygons(std::vector<GeoJsonPolygon> geo_json_polygons) {
    std::vector<CsvWriter::Polygon> mapped_polygons;
    for (const GeoJsonPolygon &polygon: geo_json_polygons) {
        mapped_polygons.push_back(map_to_polygon(polygon));
    }
    return mapped_polygons;
}

void geojson_parser(const argparse::ArgumentParser &arguments) {
    const std::string file_path = arguments.get<std::string>("file");
    const std::string output_path = arguments.get<std::string>("output");
    const unsigned long max_number_of_points = arguments.get<unsigned long>("max-points");

    GeoJsonParser geo_json_parser(file_path);
    const auto parsed_polygons = geo_json_parser.parse_all_polygons();
    const auto mapped_polygons = map_polygons(parsed_polygons);
    CsvWriter::write_polygons(output_path, mapped_polygons, max_number_of_points);
}

void union_of_convex_hulls(argparse::ArgumentParser &arguments) {
}

void cgal_two_opt(argparse::ArgumentParser &arguments) {
}

int main(const int argc, char *argv[]) {
    argparse::ArgumentParser arg_parser("PolygonGenerator");
    arg_parser.add_argument("-a", "--algorithm").help("Choose an algorithm for generating polygons.");
    arg_parser.add_argument("-n", "--n-polygons").help("Choose the number of polygons to generate.");
    arg_parser.add_argument("-o", "--output").help("Choose the output file. (Format will be .csv)");

    // For most of the algorithms
    arg_parser.add_argument("-p" "--max-points").help("The maximum number of points a generated polygon can have.");
    arg_parser.add_argument("-r" "--radius").help("The radius of the disk where points may be randomly generated.");

    // GEOJSON_PARSER args
    arg_parser.add_argument("-f", "--file").help("Choose an input file. (Format must be .geojson)");

    // CGAL_TWO_OPT args
    arg_parser.add_argument("-d", "--distance").help(
        "Maximum distance between convex hulls for the UNION_OF_CONVEX_HULLS-algorithm");

    try {
        arg_parser.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    switch (arg_parser.get<GeneratorAlgorithm>("algorithm")) {
        case GEOJSON_PARSER: geojson_parser(arg_parser);
            break;
        case CGAL_TWO_OPT: cgal_two_opt(arg_parser);
            break;
        case UNION_OF_CONVEX_HULLS: union_of_convex_hulls(arg_parser);
            break;
    }
}
