#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>

using std::string;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;
typedef CGAL::Polygon_2 <K> Polygon_2D;
typedef CGAL::Line_2 <K> Line_2D;
typedef Polygon_2D::Edge_const_iterator EdgeIterator;
typedef Polygon_2D::Vertex_iterator VertexIterator;

long double incremental(Points, int, string);