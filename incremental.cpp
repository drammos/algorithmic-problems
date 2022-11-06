#include "incremental.hpp"

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

//if KP and polygon have different orientation, KP is reversed
void orientation(Polygon_2& KP, Polygon_2& pol){
    if((pol.is_clockwise_oriented() && !KP.is_clockwise_oriented()) || (!pol.is_clockwise_oriented() && KP.is_clockwise_oriented())){
        KP.reverse_orientation();
    }
}

void sorting(Points& points, string init){
    if(!init.compare("1a")){
        sort(points.begin(), points.end(), compare_1a);
    }
    else if(!init.compare("1b")){
        sort(points.begin(), points.end(), compare_1b);
    }
    else if(!init.compare("2a")){
        sort(points.begin(), points.end(), compare_2a);
    }
    else{
        sort(points.begin(), points.end(), compare_2b);
    }

    for(int i=0; i < points.size(); i++){
        cout << points.at(i) << endl;
    }
}

vector<Segment_2> red_edges(Points points, Polygon_2 pol){
    Polygon_2 old;
    //current convex hull
    CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(old));

    orientation(old,pol);

    vector<Segment_2> edges;
    for(const Segment_2& e  : old.edges())
        edges.push_back(e);
        
    Polygon_2 pol1 = pol;
    pol1.push_back(points.at(0));

    //convex hull after new vertice
    Polygon_2 newp;
    CGAL::convex_hull_2(pol1.begin(), pol1.end(), std::back_inserter(newp));

    orientation(newp,pol1);

    vector<Segment_2> edges_new;
    for(const Segment_2& e  : newp.edges())
        edges_new.push_back(e);

    //red edges are the edges that are included in the old convex hull but not in the new.
    std::vector<Segment_2>::iterator it;
    vector<Segment_2> red_edges;
    for(const Segment_2& e  : edges){
        it = find(edges_new.begin(), edges_new.end(), e);
        if(it == edges_new.end()){
            red_edges.push_back(e);
        }
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

    //if the red edge is an edge of the polygon
    if(it != pol_edges.end()){

        Point_2 to_add = points[0];
        Segment_2 seg1(to_add, it->point(0));
        Segment_2 seg2(to_add, it->point(1));

        //if the new point is on the same line as the start or the end point of the edge, this edge is not visible. 
        const auto result = CGAL::intersection(seg1, seg2);
        if (const Segment_2* s = boost::get<Segment_2>(&*result)) {
            return visible;
        }

        visible.push_back(red);
        return visible;
    }
    //if the red edge is not part of the polygon
    else{
        Point_2 first = red.point(0);
        Point_2 second = red.point(1);
        bool in_red = false;

        EdgeIterator it = pol.edges_begin();
        while( it != pol.edges_end()){
            //finding the first edge behind the red edge
            if(it->point(0) == first || in_red){

                in_red = true;
                Point_2 to_add = points[0];
                Segment_2 seg1(to_add, it->point(0));
                Segment_2 seg2(to_add, it->point(1));
                Point_2 midPoint = CGAL::midpoint(it->point(0), it->point(1)); 
                Segment_2 mid_seg(to_add, midPoint);
                

                EdgeIterator it1;
                for(it1 = pol.edges_begin(); it1 != pol.edges_end(); it1++){
                    //if the new point is on the same line as the start or the end point of the edge, this edge is not visible. 
                    const auto result = CGAL::intersection(seg1, seg2);
                    if (const Segment_2* s = boost::get<Segment_2>(&*result)) {
                        break;
                    }
                    
                    if(it1 != it){
                        //if seg1 intersects with any edge except the previous one, the the edge it is not visible;
                        if(it1 != it-1 && CGAL::do_intersect(seg1, *it1)){
                            const auto result = CGAL::intersection(seg1, *it1);
                            const Point_2* p = boost::get<Point_2 >(&*result);
                            if(p->x() != it->point(0).x() || p->y() != it->point(0).y()){
                                break;
                            }
                        }
                        //if seg2 intersects with any edge except the next one, the the edge it is not visible;
                        if(it1 != it+1 && CGAL::do_intersect(seg2, *it1)){
                            const auto result = CGAL::intersection(seg2, *it1);
                            const Point_2* p = boost::get<Point_2 >(&*result);
                            if(p->x() != it->point(1).x() || p->y() != it->point(1).y()){
                                break;
                            }
                        }
                        if(CGAL::do_intersect(mid_seg, *it1)){
                            break;
                        }   
                    }
                }
                if(it1 == pol.edges_end()){
                    visible.push_back(*it);

                }
            }
            //finding the last edge behind the red edge.
            if(it->point(1) == second && in_red){
                in_red = false;
                break;
            }
            it++;
            if(it == pol.edges_end() && in_red && it->point(1) != second){
                it = pol.edges_begin();
            }
        }
        return visible;
    }
}

//functions for edge selection

Segment_2 random_selection(vector<Segment_2> visible){
    int random = rand() % visible.size();
    Segment_2 edge = visible[random];
    return edge;
}

Segment_2 minimum_area(vector<Segment_2> visible, Polygon_2 pol, Points points){
    vector<double> areas;
    vector<Segment_2> edges;
    
    for(Segment_2 e: visible){
        Polygon_2 pol1 = pol;
        VertexIterator it;
        for(it = pol1.vertices_begin(); it != pol1.vertices_end(); it++){
            if(it->x() == e.point(1).x() && it->y() == e.point(1).y()){
                break;
            }
        }
        pol1.insert(it, points[0]);
        areas.push_back(pol1.area());
        edges.push_back(e);
    }
    double min = areas[0];
    Segment_2 min_edge = edges[0];
    for(int i = 1; i < areas.size(); i++){
        if(areas.at(i) < min){
            min = areas.at(i);
            min_edge = edges.at(i);
        }
    }
    return min_edge;
}

Segment_2 maximum_area(vector<Segment_2> visible, Polygon_2 pol, Points points){
    vector<double> areas;
    vector<Segment_2> edges;
    
    for(Segment_2 e: visible){
        Polygon_2 pol1 = pol;
        VertexIterator it;
        for(it = pol1.vertices_begin(); it != pol1.vertices_end(); it++){
            if(it->x() == e.point(1).x() && it->y() == e.point(1).y()){
                break;
            }
        }
        pol1.insert(it, points[0]);
        areas.push_back(pol1.area());
        edges.push_back(e);
    }
    double max = areas[0];
    Segment_2 max_edge = edges[0];
    for(int i = 1; i < areas.size(); i++){
        if(areas.at(i) > max){
            max = areas.at(i);
            max_edge = edges.at(i);
        }
    }
    return max_edge;
}

double incremental(Points points, int edge_selection, string initialization){
    srand(time(NULL));
    Polygon_2 pol;
    sorting(points, initialization);

    //Building initial triangle
    pol.push_back(points.at(0));
    pol.push_back(points.at(1));
    pol.push_back(points.at(2));

    points.erase(points.begin());
    points.erase(points.begin());
    points.erase(points.begin());

    while(points.size() > 0){
        //finding red edges
        vector<Segment_2> red = red_edges(points, pol);

        Polygon_2 KP;
        CGAL::convex_hull_2(pol.begin(), pol.end(), std::back_inserter(KP));

        orientation(KP,pol);

        //finding visible edges
        vector<Segment_2> visible;
        for(const Segment_2& e  : red){
            vector<Segment_2> visible1 = visible_edges(e, pol, points);
            for(const Segment_2& e  : visible1)
                visible.push_back(e); 
        }
        
        //edge selection
        Segment_2 edge;
        if(edge_selection == 1){
            edge = random_selection(visible);
        }
        else if(edge_selection == 2){
            edge = minimum_area(visible, pol, points);
        }
        else{
            edge = maximum_area(visible, pol, points);
        }
        
        //finding the selected visible edge
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

        points.erase(points.begin());
    }

    for(EdgeIterator it = pol.edges_begin(); it != pol.edges_end(); it++){
        cout<<*it<<endl;
    }
    cout<<pol.is_simple()<<endl;
    return pol.area();
}
