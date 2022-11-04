#include <CGAL/convex_hull_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include "utils.hpp"
#include <random>
#include <time.h>

typedef K::Point_2 Point_2;
typedef K::Segment_2 Segment_2;
typedef std::vector<Point_2> Points;
typedef CGAL::Polygon_2 <K> Polygon_2D;
typedef CGAL::Line_2 <K> Line_2D;
typedef Polygon_2D::Edge_const_iterator EdgeIterator;
typedef Polygon_2D::Vertex_iterator VertexIterator;

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

void orientation(Polygon_2& PK, Polygon_2& pol){
    if((pol.is_clockwise_oriented() && !PK.is_clockwise_oriented()) || (!pol.is_clockwise_oriented() && PK.is_clockwise_oriented())){
        cout<<"reverse"<<endl;
        PK.reverse_orientation();
    }
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
    cout << "Points sorted: " << endl;

    for(int i=0; i < points.size(); i++){
        cout << points.at(i) << endl;
    }

    return points;
}

vector<Segment_2> red_edges(Points points, Polygon_2 pol){
    Polygon_2 old;

    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(old));

    orientation(old,pol);

    vector<Segment_2> edges;
    for(const Segment_2& e  : old.edges())
        edges.push_back(e);

    cout<<"Edges:"<<endl;
    for(int i=0; i < edges.size(); i++)
        cout << edges.at(i) << endl;
        
    Polygon_2 pol1 = pol;
    pol1.push_back(points.at(0));

    Polygon_2 newp;
    CGAL::convex_hull_2(pol1.begin(), pol1.end(), std::back_inserter(newp));

    orientation(newp,pol1);

    vector<Segment_2> edges_new;
    for(const Segment_2& e  : newp.edges())
        edges_new.push_back(e);


    cout<<"New edges:"<<endl;
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
    // points.erase(points.begin());
    cout<<"Red edges:"<<endl;

    for(int i=0; i < red_edges.size(); i++){
        cout << red_edges.at(i) << endl;
    }

    return red_edges;
}

vector<Segment_2> visible_edges(Segment_2 red, Polygon_2 pol, Points points){
    vector<Segment_2> visible;
    vector<Segment_2> pol_edges;
    for(const Segment_2& e  : pol.edges())
        pol_edges.push_back(e);

    std::vector<Segment_2>::iterator it;
    it = find(pol_edges.begin(), pol_edges.end(), red);

    if(it != pol_edges.end()){
        visible.push_back(red);
        cout<<"Visible edges1:"<<endl;
        for(int i=0; i < visible.size(); i++){
            cout << visible.at(i) << endl;
        }
        return visible;
    }
    else{
        Point_2 first = red.point(0);
        Point_2 second = red.point(1);
        bool in_red = false;

        EdgeIterator it = pol.edges_begin();
        while( it != pol.edges_end()){

            if(it->point(0) == first || in_red){
                cout<<"edge-"<<*it<<endl;
                in_red = true;
                Point_2 to_add = points[0];
                Segment_2 seg1(to_add, it->point(0));
                Segment_2 seg2(to_add, it->point(1));
                Point_2 midPoint = CGAL::midpoint(it->point(0), it->point(1)); 
                Segment_2 PMID(to_add, midPoint);
                // if(seg1.has_on(it->point(1)) || seg2.has_on(it->point(0))){
                //     cout<<"has on"<<endl;
                //     it++;
                //     continue;
                // }
                EdgeIterator it1;
                for(it1 = pol.edges_begin(); it1 != pol.edges_end(); it1++){
                    if(it1 != it){
                        if(it1 != it-1 && CGAL::do_intersect(seg1, *it1)){
                            const auto result = CGAL::intersection(seg1, *it1);
                            const Point_2* p = boost::get<Point_2 >(&*result);
                            if(p->x() != it->point(0).x() && p->y() != it->point(0).y()){
                                cout<<"1intersects with "<<*it1<<endl;
                                break;
                            }
                        }
                        if(it1 != it+1 && CGAL::do_intersect(seg2, *it1)){
                            const auto result = CGAL::intersection(seg2, *it1);
                            const Point_2* p = boost::get<Point_2 >(&*result);
                            if(p->x() != it->point(1).x() && p->y() != it->point(1).y()){
                                cout<<"2intersects with "<<*it1<<endl;
                                break;
                            }
                        }
                        if(CGAL::do_intersect(PMID, *it1)){
                            break;
                        }
                        
                    }
                    
                    
                    
                }
                if(it1 == pol.edges_end()){
                    cout<<"end"<<endl;
                    visible.push_back(*it);

                }
            }
            
            if(it->point(1) == second && in_red){
                cout<<"second"<<endl;
                in_red = false;
                break;
            }
            it++;
            if(it == pol.edges_end() && in_red && it->point(1) != second){
                cout<<"here"<<endl;
                it = pol.edges_begin();
            }
        }
        cout<<"Visible edges:"<<endl;
        for(int i=0; i < visible.size(); i++){
            cout << visible.at(i) << endl;
        }
        return visible;
    }
}

int main(void){
    srand(time(NULL));
    Polygon_2 pol;
    Points points = input_handling("euro-night-0001000.instance", "1a");

    //Building initial triangle
    pol.push_back(points.at(0));
    pol.push_back(points.at(1));
    pol.push_back(points.at(2));

    vector<Segment_2> edges_new;
    for(const Segment_2& e  : pol.edges())
        edges_new.push_back(e);
    cout<<"Polygon:"<<endl;
    for(int i=0; i < edges_new.size(); i++)
        cout << edges_new.at(i) << endl;


    points.erase(points.begin());
    points.erase(points.begin());
    points.erase(points.begin());

    while(points.size() > 0){
        vector<Segment_2> red = red_edges(points, pol);

        Polygon_2 PK;
        CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(PK));

        orientation(PK,pol);

        vector<Segment_2> visible;
        for(const Segment_2& e  : red){
            vector<Segment_2> visible1 = visible_edges(e, pol, points);
            for(const Segment_2& e  : visible1)
                visible.push_back(e);

           
        }
        int random = rand() % visible.size();
        Segment_2 edge = visible[random];
        
        VertexIterator it;
        for(it = pol.vertices_begin(); it != pol.vertices_end(); it++){
            if(it->x() == edge.point(1).x() && it->y() == edge.point(1).y()){
                break;
            }
        }
        pol.insert(it, points[0]);
        
        vector<Segment_2> edges_new;
        for(const Segment_2& e  : pol.edges())
            edges_new.push_back(e);

        cout<<"Polygon:"<<endl;
        for(int i=0; i < edges_new.size(); i++)
            cout << edges_new.at(i) << endl;

        if(pol.is_simple() == false){
            cout<<"Not simple"<<endl;
            return -1;
        }

        points.erase(points.begin());
    }
    cout<<pol.is_simple()<<endl;
    return 0;
}
