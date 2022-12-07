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

typedef std::vector<Point_2>::iterator pveciterator;
Polygon_2D simulated_annealing(Polygon_2D, int, string, double, string);



#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <stdlib.h>
#include <CGAL/Line_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/intersections.h>
#include <CGAL/Triangle_2.h>
#include <time.h>
#include <CGAL/squared_distance_2.h>
#include <fstream>


using namespace std::chrono;
using std::cout;
using std::endl;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangle_2 <K> triangle;
typedef CGAL::Convex_hull_traits_adapter_2 <K,
CGAL::Pointer_property_map<Point_2>::type> Convex_hull_traits_2;
typedef K::FT FT;

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Kd_tree.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/algorithm.h>
#include <CGAL/Fuzzy_iso_box.h>
#include <CGAL/Search_traits_2.h>
#include <bits/stdc++.h>
#include <random>

/* K-d tree typedefs*/
typedef CGAL::Random_points_in_square_2<Point_2> Random_points_iterator;
typedef CGAL::Counting_iterator<Random_points_iterator> N_Random_points_iterator;
typedef CGAL::Search_traits_2<K> Traits;
typedef CGAL::Kd_tree<Traits> Tree;
typedef CGAL::Fuzzy_iso_box<Traits> Fuzzy_iso_box;