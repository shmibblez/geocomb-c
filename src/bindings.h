#ifndef GEOCOMB_C_BINDINGS
#define GEOCOMB_C_BINDINGS

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @param mo map orientation, ECEF or dymaxion - ECEF is default
 * @param rm rotation method, gnomonic or quaternion - gnomonic is default
 * @returns C_Icosahedron struct
 */
struct C_Icosahedron Icosahedron_create(enum map_orientation mo,
                                        enum rotation_method rm);

/**
 * @param ico icosahedron struct
 * @param lat latitude in degrees, range: [-90, 90]
 * @param lon longitude in degrees, range: [-180, 180]
 * @returns C_Point3 struct
 */
struct C_Point3 Icosahedron_pointFromCoords(struct C_Icosahedron *ico,
                                            double lat, double lon);

/**
 * @param ico C_Icosahedron struct
 * @param p C_Point3 struct
 * @param res resolution
 * @returns C_hash_properties for point for resolution
 */
struct C_hash_properties Icosahedron_hash(struct C_Icosahedron *ico,
                                          struct C_Point3 *p, int res);

/**
 * @param props C_hash_properties to generate C_GPoint3 from
 */
struct C_GPoint3 Icosahedron_parseHash(struct C_hash_properties props);

#ifdef __cplusplus
}
#endif

#endif