#pragma once

#ifndef PHEX_HPP
#define PHEX_HPP

#include "icosahedron.hpp"
#include "point3.hpp"
#include <vector>

class Phex {

public:
  std::vector<CPP_GPoint3> points;
  CPP_Point3 center;

  Phex(std::vector<CPP_GPoint3> points, CPP_GPoint3 center);
  ~Phex();

  /**
   * @param all_points all icosahedron points, for generating phexes
   * @return vector of all icosahedron phexes
   **/
  static std::vector<Phex>
  all_phexes(CPP_Icosahedron::all_icosahedron_points all_points);

  /**
   * @param all_points all icosahedron points for res
   * @return vector of all phex centers
   **/
  static std::vector<CPP_GPoint3>
  all_phex_centers(CPP_Icosahedron::all_icosahedron_points all_points);

  /**
   * @param all_points all icosahedron points for res
   * @param p point to generate phex points for
   * @returns phex whose center is p
   **/
  static std::vector<CPP_GPoint3> not_lazy_surrounding_points(
      CPP_Icosahedron::all_icosahedron_points all_points, CPP_GPoint3 p);
};

#endif