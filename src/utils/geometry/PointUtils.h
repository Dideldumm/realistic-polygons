//
// Created by dideldumm on 11.07.24.
//

#ifndef ALGOGEOUTILS_H
#define ALGOGEOUTILS_H

#include "CgalTypes.h"

bool is_left_of(const CgalTypes::Point &a, const CgalTypes::Point &b);

bool is_right_of(const CgalTypes::Point &a, const CgalTypes::Point &b);

bool is_above(const CgalTypes::Point &a, const CgalTypes::Point &b);

bool is_below(const CgalTypes::Point &a, const CgalTypes::Point &b);

CgalTypes::Point get_leftmost(const std::vector<CgalTypes::Point> &points);

CgalTypes::Point get_rightmost(const std::vector<CgalTypes::Point> &points);

CgalTypes::Point get_topmost(const std::vector<CgalTypes::Point> &points);

CgalTypes::Point get_bottommost(const std::vector<CgalTypes::Point> &points);


#endif //ALGOGEOUTILS_H
