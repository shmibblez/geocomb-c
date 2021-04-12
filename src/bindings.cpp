#include "bindings.h"
#include "types.h"

// for preventing name conflicts with c++ classes & c structs
// namespace cpp {
#include "enums.hpp"
#include "icosahedron.hpp"
// } // namespace cpp

struct C_Icosahedron Icosahedron_create(enum map_orientation mo,
                                        enum rotation_method rm) {
  return {
      .mo = mo,
      .rm = rm,
  };
}

struct C_Point3 Icosahedron_pointFromCoords(struct C_Icosahedron *ico,
                                            double lat, double lon) {
  // create icosahedron
  const Icosahedron cpp_ico(ico->mo == dymaxion ? ico::map_orientation::dymaxion
                                                : ico::map_orientation::ECEF,
                            ico->rm == quaternion
                                ? ico::rotation_method::quaternion
                                : ico::rotation_method::gnomonic);
  // create point
  const Point3 p = cpp_ico.point_from_coords(lat, lon);
  // convert to C struct
  return {
      .x = p.x,
      .y = p.y,
      .z = p.z,
      .tri_num = p.tri_num,
      .is_pc = p.is_pc ? 1 : 0,
  };
}

struct C_hash_properties Icosahedron_hash(struct C_Icosahedron *ico,
                                          struct C_Point3 *p, int res) {
  // create icosahedron
  Icosahedron cpp_ico(ico->mo == dymaxion ? ico::map_orientation::dymaxion
                                          : ico::map_orientation::ECEF,
                      ico->rm == quaternion ? ico::rotation_method::quaternion
                                            : ico::rotation_method::gnomonic);
  // create point
  const Point3 cpp_p(p->x, p->y, p->z, p->is_pc == 1 ? true : false,
                     p->tri_num);
  // generate hash
  const Icosahedron::hash_properties hash = cpp_ico.hash(cpp_p, res);
  // convert to c hash props
  return {
      .mo = hash.mo == ico::map_orientation::dymaxion ? dymaxion : ECEF,
      .rm = hash.rm == ico::rotation_method::quaternion ? quaternion : gnomonic,
      .row = hash.row,
      .col = hash.col,
      .res = hash.res,
  };
}

struct C_GPoint3 Icosahedron_parseHash(struct C_hash_properties props) {
  // create icosahedron
  Icosahedron cpp_ico(props.mo == dymaxion ? ico::map_orientation::dymaxion
                                           : ico::map_orientation::ECEF,
                      props.rm == quaternion ? ico::rotation_method::quaternion
                                             : ico::rotation_method::gnomonic);
  // create cpp hash_properties
  const Icosahedron::hash_properties pprops = {
      .mo = props.mo == dymaxion ? ico::map_orientation::dymaxion
                                 : ico::map_orientation::ECEF,
      .rm = props.rm == quaternion ? ico::rotation_method::quaternion
                                   : ico::rotation_method::gnomonic,
      .row = props.row,
      .col = props.col,
      .res = props.res,
  };
  // parse hash
  const GPoint3 pp = cpp_ico.parse_hash(pprops);
  // convert to C_GPoint3
  return {
      .x = pp.x,
      .y = pp.y,
      .z = pp.z,
      .is_pc = pp.is_pc,
      .tri_num = pp.tri_num,
      .row = pp.row,
      .col = pp.col,
      .res = pp.res,
      .mo = props.mo,
      .rm = props.rm,
  };
}
