#include "linearDS.h"
#include <vector>


class geometric_plane_shape{
public:
    geometric_plane_shape(initializer_list<c_list> list){
        std::vector<c_list> myvector = list;
        std::vector<c_list>::reverse_iterator rit = myvector.rbegin();
        for (int i = 0; rit!= myvector.rend(); ++rit){
            points.insert_data(*rit);
        }
    }

private:
    //Data Structure
    circular_singly_linked_list<c_list> points;
};

class geometric_plane_shapes{
public:
    geometric_plane_shapes(initializer_list<geometric_plane_shape> list_of_figures){
        std::vector<geometric_plane_shape> myvector = list_of_figures;
        std::vector<geometric_plane_shape>::reverse_iterator rit = myvector.rbegin();
        for (int i = 0; rit!= myvector.rend(); ++rit){
            figure_list.push(*rit);
        }
    }
private:
    //Data Structure
    c_doubly_linked_list<geometric_plane_shape> figure_list;
};

int main(){
    geometric_plane_shape A({{1,2}, {1,2}});
}
