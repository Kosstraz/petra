#ifndef COORDS_H
#define COORDS_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

typedef struct CoordsI {
    int x;
    int y;
  } CoordsI;

typedef struct CoordsF {
    float x;
    float y;
  } CoordsF;

typedef struct CoordsI CoordsI;
typedef struct CoordsF CoordsF;

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif