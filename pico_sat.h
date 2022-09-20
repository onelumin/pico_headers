/*
    @file pico_unit.h
    @brief Separating Axis Test (SAT) written in C99.

    ----------------------------------------------------------------------------
    Licensing information at end of header
    ----------------------------------------------------------------------------
*/

#ifndef PICO_SAT_H
#define PICO_SAT_H

#include "pico_math.h"

#ifndef PICO_SAT_MAX_POLY_VERTS
#define PICO_SAT_MAX_POLY_VERTS 8
#endif

typedef struct
{
    pm_v2  pos;
    pm_flt radius;
} sat_circle_t;

typedef struct
{
    int   vertex_count;
    pm_v2 vertices[PICO_SAT_MAX_POLY_VERTS];
    pm_v2 normals[PICO_SAT_MAX_POLY_VERTS - 1];
    pm_v2 edges[PICO_SAT_MAX_POLY_VERTS - 1];
} sat_polygon_t;
// } sat_poly_t?
typedef sat_polygon_t sat_poly_t;

typedef struct
{
    pm_v2  normal;
    pm_flt overlap;
} sat_response_t;

//pm_b2 sat_polygon_to_aabb(const sat_polygon_t* poly);
//pm_b2 sat_circle_to_aabb(const sat_circle_t* circle);

sat_circle_t sat_init_cicle(pm_v2 pos, pm_flt radius);
sat_polygon_t sat_init_polygon(int vertex_count, pm_v2 vertices[]);
sat_polygon_t sat_aabb_to_polygon(const pm_b2* aabb);

bool sat_test_polygon_polygon(const sat_poly_t* p1,
                              const sat_poly_t* p2,
                              sat_response_t* response);

bool sat_test_circle_polygon(const sat_circle_t* c,
                             const sat_poly_t* p,
                             sat_response_t* response);

bool sat_test_polygon_circle(const sat_poly_t* p,
                             const sat_circle_t* c,
                             sat_response_t* response);

bool sat_test_circle_circle(const sat_circle_t* c1,
                            const sat_circle_t* c2,
                            sat_response_t* response);

#endif // PICO_SAT_H

#ifdef PICO_SAT_IMPLEMENTATION

bool sat_is_separating_axist();

sat_circle_t sat_init_cicle(pm_v2 pos, pm_flt radius)
{
    sat_circle_t circle;
    circle.pos = pos;
    circle.radius = radius;
    return circle;
}

sat_polygon_t sat_init_polygon(int vertex_count, pm_v2 vertices[])
{
    //assert(vertex_count <= PICO_SAT_MAX_POLY_VERTS);

    sat_polygon_t poly;
    poly.vertex_count = vertex_count;

    for (int i = 0; i < vertex_count; i++)
    {
        poly.vertices[i] = vertices[i];
    }

    for (int i = 0; i < vertex_count - 1; i++)
    {
        pm_v2 v1 = vertices[i];
        pm_v2 v2 = (i < vertex_count - 1) ? vertices[i + 1] : vertices[0];
        poly.edges[i] = pm_v2_sub(v2, v1);
        poly.normals[i] = pm_v2_perp(&poly.edges[i]); //TODO: use pm_v2_normalized
        pm_v2_normalize(&poly.normals[i]);
    }

    return poly;
}



#endif // PICO_SAT_IMPLEMENTATION

