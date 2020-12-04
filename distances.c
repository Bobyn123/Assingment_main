//
// Code provided by Neal Snooke to implent the haversine function on 14/11/2020.
// modified by Robyn Vaughan-Williams to comply with in use data structure
//


#include <math.h>
#include "functions.h"
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)


/**
	 * The great circle distance or the orthodromic distance is the shortest distance
	 * between two points on a sphere
	 * @param other
	 * @return distance in m
	 */
double distance(sheep_position * first, sheep_position * second)
{
    double lon1 = degToRad(first->longitude);
    double lon2 = degToRad(second->longitude);
    double lat1 = degToRad(first->latitude);
    double lat2 = degToRad(second->latitude);

    // Haversine formula (alt. vincenties formula)
    double dlon = lon2 - lon1;
    double dlat = lat2 - lat1;
    double a = pow(sin(dlat / 2), 2)
               + cos(lat1) * cos(lat2)
                 * pow(sin(dlon / 2),2);

    double c = 2 * asin(sqrt(a));

    // Radius of earth in kilometers. Use 3956
    // for miles
    double r = 6371;

    // calculate the result (in m)
    return((c * r)*1000);
}