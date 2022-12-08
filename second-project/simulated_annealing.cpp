#include "simulated_annealing.hpp"

using namespace std;

double global_step(Polygon_2D& pol, string min_max){
    vector<Point_2> vertices;
    for(const Point_2& v  : pol.vertices())
        vertices.push_back(v);

    bool valid = false;
    Polygon_2D new_pol;
    while(valid == false){
        new_pol = pol;

        int size = vertices.size();
        int first = rand() % size;
        int second = rand() % size;

        while(second == first || second == first-1 || (second == 0 && first == size-1)){
            first = rand() % size;
            second = rand() % size;
        }

        for(VertexIterator vit = new_pol.vertices_begin(); vit != new_pol.vertices_end(); vit++){
            if(vit->x() == vertices.at(first).x() && vit->y() == vertices.at(first).y()){
                new_pol.erase(vit);
                break;
            }
        }

        for(VertexIterator vit = new_pol.vertices_begin(); vit != new_pol.vertices_end(); vit++){
            if(vit->x() == vertices.at(second).x() && vit->y() == vertices.at(second).y()){
                Point_2 point = vertices.at(first);
                new_pol.insert(vit, point);
                break;
            }
        }

        if(new_pol.is_simple()){
            valid = true;
        }
    }

    pol = new_pol;
    Polygon_2D KP;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(KP));
    double new_energy = energy(vertices.size(), pol.area(), KP.area(), min_max);
    return new_energy;
}

Polygon_2D simulated_annealing(Polygon_2D polygon, int L, string min_max, double threshold, string annealing){
    Polygon_2D new_polygon = polygon;


    double temperature = 1;
    Points internal_points = polygon.vertices();
    int vertices_size = internal_points.size();
    Points result;

    // Create the convex hull
    CGAL::convex_hull_2(internal_points.begin(), internal_points.end(), std::back_inserter(result));
    Polygon_2D polygon_convex_hull;

    for (pveciterator iter=result.begin(); iter!=result.end(); ++iter){
        polygon_convex_hull.push_back(*iter);
    }

    // Area for convex hull 
    // The convex hull is same for all program
    double area_convex_hull = polygon_convex_hull.area();

    // Start energy for polygon
    double start_energy = energy(vertices_size, polygon.area(), area_convex_hull, min_max);


    while(temperature > 0){
        double new_energy;
        if(annealing.compare("local") == 0){
            new_energy = local_algorithm(new_polygon, area_convex_hull, vertices_size, min_max);
        }   
        else if(annealing.compare("global") == 0){
            cout << "hh" << endl;
        }
        else{
            cout << "hh" << endl;
        }
        temperature = temperature - (1/L);
    }

    return new_polygon;
}

double local_algorithm( Polygon_2D polygon, double area_convex_hull, int vertices_size, string min_max){
    srand(time(NULL));
    int my_rand = rand();
    // Points vertices = polygon.
    int num_vertice = my_rand%vertices_size;
vertices.begin+20
    return 1.1;
}

// Energy for min or max
double energy(int vertices_size, double area_polygon, double area_convex_hull, string min_max){
    if(min_max.compare("-min") == 0){
        return vertices_size*(area_polygon/area_convex_hull);
    }
    else{
        return vertices_size*(1 - (area_polygon/area_convex_hull));
    }
}