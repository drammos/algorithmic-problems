#include <iostream>

using namespace std;

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <fstream>
#include <time.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::istream_iterator< Point_2 > point2_iterator;
typedef std::vector<Point_2> Points;
typedef std::vector<Point_2>::iterator pveciterator;
typedef CGAL::Polygon_2<K> Polygon_2;
typedef K::Segment_2 Segment_2;
typedef Polygon_2::Vertex_iterator VertexIterator;


double convex_hull(vector<Point_2>, int);