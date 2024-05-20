#include "PX4Controller/CoordTranformer.h"
#include <cassert>
#include <iostream>
#include <cmath>

const double EPSILON = 1e-6; // Kabul edilebilir hata payı

void TestSetOrigin()
{
    FS::CoordTransformer transformer;
    transformer.SetOrigin(41.015137, 28.979530); // Istanbul, Turkey

    FGS::CommonCoordinate coord = transformer.LocalizeCoordinate(41.015137, 28.979530);
    assert(std::fabs(coord.latitude) < EPSILON && std::fabs(coord.longtitude) < EPSILON);
    std::cout << "TestSetOrigin passed." << std::endl;
}

void TestLocalizeCoordinate()
{
    FS::CoordTransformer transformer;
    transformer.SetOrigin(41.015137, 28.979530); // Istanbul, Turkey

    FGS::CommonCoordinate coord = transformer.LocalizeCoordinate(40.748817, -73.985428); // New York, USA
    std::cout << "Local Coordinates for New York (x, y): " << coord.latitude << ", " << coord.longtitude << std::endl;
    assert(coord.latitude != 0.0 && coord.longtitude != 0.0); // Check if the coordinates are transformed
    std::cout << "TestLocalizeCoordinate passed." << std::endl;
}

void TestGlobalizeCoordinate()
{
    FS::CoordTransformer transformer;
    transformer.SetOrigin(41.015137, 28.979530); // Istanbul, Turkey

    double x = -5806943.89, y = -4543747.92; // Approx local coordinates for New York relative to Istanbul
    FGS::CommonCoordinate coord = transformer.GlobalizeCoordinate(x, y);
    std::cout << "Global Coordinates for New York (lat, lon): " << coord.latitude << ", " << coord.longtitude << std::endl;
    assert(std::fabs(coord.latitude - 40.748817) < EPSILON && std::fabs(coord.longtitude + 73.985428) < EPSILON);
    std::cout << "TestGlobalizeCoordinate passed." << std::endl;
}

int main()
{
    TestSetOrigin();
    TestLocalizeCoordinate();
    TestGlobalizeCoordinate();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
