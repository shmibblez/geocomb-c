#include "bindings.h"
#include "types.h"

#include "enums.hpp"
#include "icosahedron.hpp"

struct Icosahedron Icosahedron_create(enum map_orientation mo,
                                      enum rotation_method rm) {
  return {
      .mo = mo,
      .rm = rm,
  };
}

struct Point3 Icosahedron_pointFromCoords(struct Icosahedron *ico, double lat,
                                          double lon) {
  // create icosahedron
  const CPP_Icosahedron cpp_ico(
      ico->mo == dymaxion ? ico::map_orientation::dymaxion
                          : ico::map_orientation::ECEF,
      ico->rm == quaternion ? ico::rotation_method::quaternion
                            : ico::rotation_method::gnomonic);
  // create point
  const CPP_Point3 p = cpp_ico.point_from_coords(lat, lon);
  // convert to C struct
  return {
      .x = p.x,
      .y = p.y,
      .z = p.z,
      .tri_num = p.tri_num,
      .is_PC = p.is_pc ? 1 : 0,
  };
}

struct hash_properties Icosahedron_hash(struct Icosahedron *ico,
                                        struct Point3 *p, int res) {
  // create icosahedron
  CPP_Icosahedron cpp_ico(ico->mo == dymaxion ? ico::map_orientation::dymaxion
                                              : ico::map_orientation::ECEF,
                          ico->rm == quaternion
                              ? ico::rotation_method::quaternion
                              : ico::rotation_method::gnomonic);
  // create point
  const CPP_Point3 cpp_p(p->x, p->y, p->z, p->is_PC == 1 ? true : false,
                         p->tri_num);
  // generate hash
  const CPP_Icosahedron::hash_properties hash = cpp_ico.hash(cpp_p, res);
  // convert to c hash props
  return {
      .mo = hash.mo == ico::map_orientation::dymaxion ? dymaxion : ECEF,
      .rm = hash.rm == ico::rotation_method::quaternion ? quaternion : gnomonic,
      .row = hash.row,
      .col = hash.col,
      .res = hash.res,
  };
}

struct GPoint3 Icosahedron_parseHash(struct hash_properties props) {
  // create icosahedron
  CPP_Icosahedron cpp_ico(props.mo == dymaxion ? ico::map_orientation::dymaxion
                                               : ico::map_orientation::ECEF,
                          props.rm == quaternion
                              ? ico::rotation_method::quaternion
                              : ico::rotation_method::gnomonic);
  // create cpp hash_properties
  const CPP_Icosahedron::hash_properties pprops = {
      .mo = props.mo == dymaxion ? ico::map_orientation::dymaxion
                                 : ico::map_orientation::ECEF,
      .rm = props.rm == quaternion ? ico::rotation_method::quaternion
                                   : ico::rotation_method::gnomonic,
      .row = props.row,
      .col = props.col,
      .res = props.res,
  };
  // parse hash
  const CPP_GPoint3 pp = cpp_ico.parse_hash(pprops);
  // convert to GPoint3
  return {
      .x = pp.x,
      .y = pp.y,
      .z = pp.z,
      .is_PC = pp.is_pc,
      .tri_num = pp.tri_num,
      .row = pp.row,
      .col = pp.col,
      .res = pp.res,
      .mo = props.mo,
      .rm = props.rm,
  };
}
