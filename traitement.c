#include "traitement.h"
#include <math.h>

Point_carth point_new_C(int x, int y){
  Point_carth a;
  a.x = x;
  a.y = y;
  return a;
}

Point_polaire point_new_P(int theta, int d){
  Point_polaire a;
  a.theta = theta;
  a.d = d;
  return a;
}

Point_carth PolaireToCarth(Point_polaire pointP){
  return point_new_C(pointP.d*cos(pointP.theta), pointP.d*sin(pointP.theta));
}
