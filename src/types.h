#ifndef GEOCOMB_TYPES
#define GEOCOMB_TYPES

enum map_orientation { ECEF, dymaxion };
enum rotation_method { gnomonic, quaternion };

struct C_Icosahedron {
  enum map_orientation mo;
  enum rotation_method rm;
};

struct C_hash_properties {
  enum map_orientation mo;
  enum rotation_method rm;
  int row;
  int col;
  int res;
};

struct C_Point3 {
  long double x;
  long double y;
  long double z;
  int tri_num;
  int is_pc; // bool -> 0 = false, 1 = true
};

struct C_GPoint3 {
  long double x;
  long double y;
  long double z;
  int tri_num;
  int is_pc; // bool -> 0 = false, 1 = true  int row;
  int row;
  int col;
  int res;
  enum map_orientation mo;
  enum rotation_method rm;
};

#endif