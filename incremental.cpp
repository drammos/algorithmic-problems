#include <CGAL/convex_hull_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include "utils.hpp"

typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;

using namespace std;

bool compare_1a(Point_2 point1, Point_2 point2){
    if(point1.x() != point2.x())
        return (point1.x() < point2.x());
    else
        return (point1.y() < point2.y());
}

bool compare_1b(Point_2 point1, Point_2 point2){
    if(point1.x() != point2.x())
        return (point1.x() > point2.x());
    else
        return (point1.y() > point2.y());
}

bool compare_2a(Point_2 point1, Point_2 point2){
    if(point1.x() != point2.x())
        return (point1.y() < point2.y());
    else
        return (point1.x() < point2.x());
}

bool compare_2b(Point_2 point1, Point_2 point2){
    if(point1.x() != point2.x())
        return (point1.y() > point2.y());
    else
        return (point1.x() > point2.x());
}


Points input_handling(string input, char* sorting){
    ifstream file(input);
    string line;
    getline(file, line);
    getline(file, line);

    int i, x, y;
    Points points;
    while(file >> i >> x >> y){
        Point_2 point(x,y);

        points.push_back(point);
    }

    if(strcmp(sorting, "1a") == 0){
        cout<<"here\n";
        sort(points.begin(), points.end(), compare_1a);
    }
    else if(strcmp(sorting, "1b") == 0){
        sort(points.begin(), points.end(), compare_1b);
    }
    else if(strcmp(sorting, "2a") == 0){
        sort(points.begin(), points.end(), compare_2a);
    }
    else{
        sort(points.begin(), points.end(), compare_2b);
    }
    for(int i=0; i < points.size(); i++)
        cout << points.at(i) << endl;

    return points;
}

vector<Segment_2> red_edges(Points points, Polygon_2 pol){
    Points vertices;

    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(vertices));

    Polygon_2 old;

    for(int i=0; i < vertices.size(); i++)
        old.push_back(vertices.at(i));

    vector<Segment_2> edges;
    for(const Segment_2& e  : old.edges())
        edges.push_back(e);

    for(int i=0; i < edges.size(); i++)
        cout << edges.at(i) << endl;
        

    pol.push_back(points.at(0));

    Points vertices_new;
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(vertices_new));

    Polygon_2 newp;

    for(int i=0; i < vertices_new.size(); i++)
        newp.push_back(vertices_new.at(i));

    vector<Segment_2> edges_new;
    for(const Segment_2& e  : newp.edges())
        edges_new.push_back(e);

    for(int i=0; i < edges_new.size(); i++)
        cout << edges_new.at(i) << endl;

    std::vector<Segment_2>::iterator it;
    vector<Segment_2> red_edges;
    for(const Segment_2& e  : edges){
        it = find(edges_new.begin(), edges_new.end(), e);
        if(it == edges_new.end()){
            red_edges.push_back(e);
        }
    }
    points.erase(points.begin());

    for(int i=0; i < red_edges.size(); i++)
        cout << red_edges.at(i) << endl;

    return red_edges;
}

int main(void){
    Polygon_2 pol;
    Points points = input_handling("input.txt", "1a");

    //Building initial triangle
    pol.push_back(points.at(0));
    pol.push_back(points.at(1));
    pol.push_back(points.at(2));

    points.erase(points.begin());
    points.erase(points.begin());
    points.erase(points.begin());

    
    red_edges(points, pol);


    return 0;
}
