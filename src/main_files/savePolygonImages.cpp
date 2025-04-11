//
// Created by dideldumm on 11.04.25.
//

#include <string>

#include "../InputOutput/GeoJsonParser.h"
#include "../InputOutput/PolygonImageSaver.h"

#include "../PolygonGenerator/CgalPolygonGenerator.h"

void save_polygon_images(const std::string &image_directory, const std::vector<CgalTypes::Polygon> &polygons,
                         const std::string &class_name) {
    for (unsigned int i = 0; i < polygons.size(); ++i) {
        const CgalTypes::Polygon &polygon = polygons[i];
        const QImage image = polygon_to_image(polygon);
        const std::string file_path = image_directory + class_name + "_image_" + std::to_string(i) + ".jpg";
        save_image(image, file_path);
    }
}

void save_unrealistic_polygons(const std::string &geojson_input_filename,
                               const std::string &realistic_data_dir,
                               int &max_number_of_vertices,
                               int &number_of_polygons) {
    // create unrealistic polygons
    GeoJsonParser geo_json_parser(geojson_input_filename);
    const std::vector<CgalTypes::Polygon> polygons = geo_json_parser.parse_all_polygons();

    max_number_of_vertices = static_cast<int>(geo_json_parser.get_max_number_of_vertices());
    number_of_polygons = static_cast<int>(polygons.size());

    save_polygon_images(realistic_data_dir, polygons, "unrealistic");
}

int main(const int argc, char *argv[]) {
    assert(argc == 3);
    const std::string geojson_input_filename = argv[1];
    std::string dataset_base_dir = argv[2];
    if (!dataset_base_dir.ends_with("/")) {
        dataset_base_dir += "/";
    }
    const std::string realistic_data_dir = dataset_base_dir + "realistic/";
    const std::string unrealistic_data_dir = dataset_base_dir + "unrealistic/";

    int max_number_of_vertices;
    int number_of_polygons;
    save_unrealistic_polygons(geojson_input_filename, realistic_data_dir, max_number_of_vertices, number_of_polygons);

    const std::vector<CgalTypes::Polygon> generated_polygons = generate_polygons(
        number_of_polygons, max_number_of_vertices);
    save_polygon_images(unrealistic_data_dir, generated_polygons, "realistic");
}
