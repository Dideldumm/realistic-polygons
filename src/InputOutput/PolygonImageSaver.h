//
// Created by dideldumm on 29.03.25.
//

#ifndef POLYGONIMAGESAVER_H
#define POLYGONIMAGESAVER_H

#include <QImage>
#include <string>


QImage polygon_to_image(const CgalTypes::Polygon &polygon);

void save_image(const QImage &image, const std::string &filename);

#endif //POLYGONIMAGESAVER_H
