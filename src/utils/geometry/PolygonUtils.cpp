//
// Created by dideldumm on 22.10.24.
//

#include "PolygonUtils.h"

void insert_point_at_segment(Polygon &polygon, const Segment &segment, const Point &point) {
    //TODO unit tests
    const Point segment_end = segment.end();
    for (auto iterator = polygon.vertices_begin(); iterator != polygon.vertices_end(); ++iterator) {
        if (*iterator == segment_end) {
            polygon.insert(iterator, point);
            break;
        }
    }
}
