//
// Created by dideldumm on 11.04.25.
//

#include <string>

#include "../InputOutput/GeoJsonParser.h"
#include "../InputOutput/PolygonImageSaver.h"

#include "../PolygonGenerator/CgalPolygonGenerator.h"

static const std::string realistic = "realistic";
static const std::string unrealistic = "unrealistic";
static const std::string image_infix = "_image_";
static const std::string jpg_extension = ".jpg";
static constexpr char slash = '/';


void save_polygon_images(const std::string &image_directory, const std::vector<CgalTypes::Polygon> &polygons,
                         const std::string &class_name) {
    for (unsigned int i = 0; i < polygons.size(); ++i) {
        const CgalTypes::Polygon &polygon = polygons[i];
        const QImage image = polygon_to_image(polygon);
        std::string file_path;
        file_path.append(image_directory).append(class_name).append(image_infix).append(std::to_string(i)).append(
            jpg_extension);

        save_image(image, file_path);
    }
}

void save_realistic_polygons(const std::string &geojson_input_filename,
                             const std::string &realistic_data_dir,
                             int &max_number_of_vertices,
                             int &number_of_polygons) {
    // create realistic polygons
    GeoJsonParser geo_json_parser(geojson_input_filename);
    const std::vector<CgalTypes::Polygon> polygons = geo_json_parser.parse_all_polygons();

    max_number_of_vertices = static_cast<int>(geo_json_parser.get_max_number_of_vertices());
    number_of_polygons = static_cast<int>(polygons.size());

    save_polygon_images(realistic_data_dir, polygons, realistic);
}

int main(const int argc, char *argv[]) {
    assert(argc == 3);
    const std::string geojson_input_filename = argv[1];
    std::string dataset_base_dir = argv[2];
    if (!dataset_base_dir.ends_with(slash)) {
        dataset_base_dir += slash;
    }
    const std::string realistic_data_dir = dataset_base_dir + realistic + slash;
    const std::string unrealistic_data_dir = dataset_base_dir + unrealistic + slash;

    int max_number_of_vertices;
    int number_of_polygons;
    save_realistic_polygons(geojson_input_filename, realistic_data_dir, max_number_of_vertices, number_of_polygons);
    std::cout << std::endl;
    std::cout << "number of polygons: " << number_of_polygons << std::endl;
    std::cout << "max number of vertices: " << max_number_of_vertices << std::endl;

    const std::vector<CgalTypes::Polygon> generated_polygons = generate_polygons(
        number_of_polygons, max_number_of_vertices);
    save_polygon_images(unrealistic_data_dir, generated_polygons, unrealistic);
}
