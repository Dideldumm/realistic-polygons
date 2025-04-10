//
// Created by dideldumm on 29.03.25.
//

#include "../utils/geometry/CgalTypes.h"

#include "PolygonImageSaver.h"

#include <QPainter>
#include <QImage>

int map_from_range_to_range(const auto &smallest_input, const auto &biggest_input, const auto &smallest_output,
                            const auto &biggest_output, const auto &value) {
    const auto scale = (biggest_output - smallest_output) / (biggest_input - smallest_input);

    auto result = scale * (value - smallest_input) + smallest_output;
    return static_cast<int>(CGAL::to_double(result));
}

std::ostream &operator<<(std::ostream &lhs, const QPoint &rhs) {
    return lhs << "(" << rhs.x() << ", " << rhs.y() << ")";
};

QImage polygon_to_image(const CgalTypes::Polygon &polygon) {
    constexpr int scale = 224;
    QImage image(scale, scale, QImage::Format_Grayscale8);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black));

    const auto bbox = polygon.bbox();
    std::cout << bbox.xmin() << ", " << bbox.xmax() << std::endl;
    std::cout << bbox.ymin() << ", " << bbox.ymax() << std::endl;

    QPolygonF qpolygon;
    for (const auto &p: polygon.vertices()) {
        const int x = map_from_range_to_range(bbox.xmin(), bbox.xmax(), 0, scale, p.x());
        const int y = map_from_range_to_range(bbox.ymin(), bbox.ymax(), 0, scale, p.y());

        qpolygon << QPoint(x, y);
        std::cout << QPoint(x, y) << " ";
    }
    painter.drawPolygon(qpolygon);
    return image;
}

void save_image(const QImage &image, const std::string &filename) {
    if (!image.save(filename.c_str())) {
        std::cerr << "Failed to save image " << filename << std::endl;
    }
}
