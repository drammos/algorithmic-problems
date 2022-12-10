#include "subdivision.hpp"
#include "simulated_annealing.hpp"

using namespace std;

struct Spal{
    Point_2 left;
    Point_2 right;
    Segment_2 edge_left;
    Segment_2 edge_right;
    vector<Point_2> points;
    int number; 
    int first_in_spal;
    bool is_last;
    bool is_first;
};


bool check_for_lowers(int i, int start, vector<Point_2> points){

    bool find = false;
    Point_2 point = points.at(i);
    
    // Check for left side
    for(int num = start + 1; num < i; num++){
        Point_2 p = points.at(num);
        if(p.y() < point.y()){
            find = true;
            break;
        }
    }
    if(!find){
        return false;
    }
    
    find = false;
    // Check for right side
    for(int num = i + 1; num < points.size(); i++){
        Point_2 p = points.at(num);
        if(p.y() < point.y()){
            find = true;
            break;
        }
    }

    return find;
}


/// @brief
/// @param points 
/// @param L 
/// @param min_max 
/// @param threshold 
/// @return 
Polygon_2D subdivision(vector<Point_2> points, int L, string min_max, double threshold){
    // After with rand
    int m = 10;
    
    // Sort the points
    sort(points.begin(), points.end(), check_the_x);
    // Gia arxi
    // xorizo se temaxia
    // opou prepei to aristero x na xei aristera&deksia ena x pio xamilo toulaxtstion
    // an m dn to ikanopoiei m, m+1, m+...
    //apothikeuo to struct mou me akmes

    vector<struct Spal> spals;
    int vertices_size = points.size();
    int i_vertices = 0;
    int num = 0;
    int num_from_spal = 0;
    

    // oraia as poume oti exoyme 3 se ena vert=30
    // m = 10
    //diavazo ta x=m prota
    //gia x = m elegxo an plitountai kapoia kritiria
    //an x = m dn ikanopoiei ta kritiria tote to apothikeuso san simeio kai sunexizo sto epomeno
    //otan to vro to spao kai kratao to prev lower gia ekei pou vriskomai
    // kai to next lower with point for next
    bool last = false;
    while(true){
        
        Spal spal;
        spal.number = num_from_spal;
        int num  = 1;
        
        Point_2 middle_point;
        Point_2 next_lower;
        
        for(int i = i_vertices; i < points.size(); i++){
            
            // Add point in points for spal
            Point_2 point = points.at(i);
            spal.points.push_back(point);

            // Check is first and save it
            if(num == 1){
                spal.first_in_spal = i;
                if(i == 0){
                    spal.left = point;
                    spal.is_first = true;
                }
                else{
                    // is the first from new spal
                    spal.left = point;
                    // spal.edge_left = Segment_2(point, next_lower);
                    spal.is_first = false;
                }
            }
            //an den exoume gemisei me ta m pou prepei
            if(num >= m){
               // elegxo an to x auto pou mai tora
               //plirei ta kritiria
               //0...29
               //0..9 - 10
               //9..21 - 12
                    // periseoun 9 mazi me to koino
               //21..29
               //30
                // CHECK FOR THE OTHE POINTS IN LIST 
                int difference_from_end = points.size() - i;
                if (difference_from_end < m){
                    // an isxuei auto eimaste sto telos
                    //ara ola mesa kai break;
                    spal.is_last = true;
                    for( int start_is = i + 1; start_is < points.size(); start_is++){
                        Point_2 the_point = points.at(start_is);
                        spal.points.push_back(the_point);
                    }                 
                    last = true;
                    break;
                }

            
                bool find_lowers =  check_for_lowers(i, spal.first_in_spal, points);
                if(find_lowers){
                    // spal.edge_right = Segment_2(find_points.previous, point);
                    spal.right = point;
                    i_vertices = i;
                    break;
                }
               // an nai
                        // kratao to next_lower
                        // kratao to prev_lower
                        // sozo akmes kai point
                        // i_vertices = i auto pou mai tora
                        // spaw to break
                // an oxi
                        // sunexizo sto epomeno apla
                        // an omos dn uparxei epomeno efarmozo edo to the last

            }
            num++;
        }   

        if(last){
            break;
        }


    }

    Polygon_2D polygon;

    return polygon;
}

