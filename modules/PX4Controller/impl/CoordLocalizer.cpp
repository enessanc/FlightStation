#include "PX4Controller/CoordTranformer.h"

namespace FS
{
    void CoordTransformer::SetOrigin(const double& org_lat, const double& org_lon)
    {
        this->origin_lat = org_lat;
        this->origin_long = org_lon;
    }
    FGS::CommonCoordinate CoordTransformer::LocalizeCoordinate(const double& lat, const double& lon) const
    {
        double latRad = DegreesToRadians(lat);
        double lonRad = DegreesToRadians(lon);

        double deltaLat = latRad - origin_lat;
        double deltaLon = lonRad - origin_long;

        double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
                   cos(origin_lat) * cos(latRad) *
                   sin(deltaLon / 2) * sin(deltaLon / 2);

        double c = 2 * atan2(sqrt(a), sqrt(1 - a));

        double distance = EARTH_RADIUS * c;

        double bearing = atan2(sin(deltaLon) * cos(latRad),
                               cos(origin_lat) * sin(latRad) -
                               sin(origin_long) * cos(latRad) * cos(deltaLon));

        FGS::CommonCoordinate coord{};

        coord.latitude = distance * cos(bearing);
        coord.longtitude = distance * sin(bearing);

        return coord;
    }
    FGS::CommonCoordinate CoordTransformer::GlobalizeCoordinate(const double& x, const double& y) const
    {
        double distance = sqrt(x * x + y * y);
        double bearing = atan2(y, x);

        double angularDistance = distance / EARTH_RADIUS;

        double latRad = asin(origin_lat * cos(angularDistance) +
                             cos(origin_lat) * sin(angularDistance) * cos(bearing));

        double lonRad = origin_long + atan2(sin(bearing) * sin(angularDistance) * cos(origin_lat),
                                           cos(angularDistance) - sin(origin_lat) * sin(latRad));

        FGS::CommonCoordinate coord{};

        coord.latitude = RadiansToDegrees(latRad);
        coord.longtitude = RadiansToDegrees(lonRad);

        return coord;
    }

    double CoordTransformer::DegreesToRadians(double degrees)
    {
        return degrees * M_PI / 180.0;
    }

    double CoordTransformer::RadiansToDegrees(double radians)
    {
        return radians * 180.0 / M_PI;
    }
}