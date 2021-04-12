#include "bindings.h"
#include "types.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
  printf("let the geocomb begin\n");

  double lat = 47;
  double lon = 47;
  double res = 777;

  // create icosahedron
  struct Icosahedron ico = Icosahedron_create(ECEF, gnomonic);
  // generate point
  struct Point3 p = Icosahedron_pointFromCoords(&ico, lat, lon);

  // generate hash properties
  struct hash_properties props = Icosahedron_hash(&ico, &p, res);

  printf("hash properties,\n  row: %i\n  col:  %i\n  res: %i\n", props.row,
         props.col, props.res);

  // generate point from hash (parse hash)
  struct GPoint3 pp = Icosahedron_parseHash(props);

  printf("parsed point:\n  x: %f\n  y: %f\n  z: %f\n", (double)pp.x,
         (double)pp.y, (double)pp.z);

  printf("hash: e|g|%d|%d|%d\n", props.res, props.row, props.col);

  return 0;
}
