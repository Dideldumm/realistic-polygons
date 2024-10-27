//
// Created by dideldumm on 27.10.24.
//

#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

class PointGenerator {
public:

    virtual std::vector<Point> generatePoints(unsigned int numberOfPoints) = 0;
};

#endif //POINTGENERATOR_H
