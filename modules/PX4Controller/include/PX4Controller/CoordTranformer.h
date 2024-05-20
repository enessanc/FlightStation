#pragma once
#include <iostream>
#include <cmath>
#include "FGSCommon/Telemetry.h"


namespace FS
{
    constexpr double EARTH_RADIUS = 6371000.0; // Dünya'nın yarıçapı metre cinsinden

    class CoordTransformer
    {
    public:
        CoordTransformer() = default;
        void SetOrigin(const double& org_lat, const double& org_lon);
        [[nodiscard]] FGS::CommonCoordinate LocalizeCoordinate(const double& lat, const double& lon) const;
        [[nodiscard]] FGS::CommonCoordinate GlobalizeCoordinate(const double& x, const double& y) const;
    private:
        static double DegreesToRadians(double degrees);
        static double RadiansToDegrees(double radians);

        double origin_lat = 0;
        double origin_long = 0;
    };

}



