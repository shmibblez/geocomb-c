#ifndef GEOCOMB_BINDINGS
#define GEOCOMB_BINDINGS

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param mo map orientation, ECEF or dymaxion - ECEF is default
 * @param rm rotation method, gnomonic or quaternion - gnomonic is default
 * @returns Icosahedron struct
 */
struct Icosahedron Icosahedron_create(enum map_orientation mo,
                                      enum rotation_method rm);

/**
 * @param ico icosahedron struct
 * @param lat latitude in degrees, range: [-90, 90]
 * @param lon longitude in degrees, range: [-180, 180]
 * @returns Point3 struct
 */
struct Point3 Icosahedron_pointFromCoords(struct Icosahedron *ico, double lat,
                                          double lon);

/**
 * @param ico Icosahedron struct
 * @param p Point3 struct
 * @param res resolution
 * @returns hash_properties for point for resolution
 */
struct hash_properties Icosahedron_hash(struct Icosahedron *ico,
                                        struct Point3 *p, int res);

/**
 * @param props hash_properties to generate GPoint3 from
 */
struct GPoint3 Icosahedron_parseHash(struct hash_properties props);

#ifdef __cplusplus
}
#endif

#endif