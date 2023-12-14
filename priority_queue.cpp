#include "linearDS.h"
#include <algorithm>

using namespace std;

struct Thread{
    unsigned int priority;
    unsigned id;
    unsigned int memory_allocated;
    bool operator==(Thread A){
        return this->priority == A.priority;
    }
    Thread(unsigned int p_priority, unsigned p_id, unsigned int p_memory_allocated){
        priority = p_priority;
        id = p_id;
        memory_allocated = p_memory_allocated;
    };
    Thread(){
        priority = 0;
        id = 0;
        memory_allocated = 0;
    };


};


bool operator<(Thread A, Thread B){
    return A.priority < B.priority;
}

bool operator>(Thread A, Thread B){
    return A.priority > B.priority;
}



template <class T>
class priority_queue{
    public:
        priority_queue<T>(initializer_list<T>);
        void insert(T);
        priority_queue bubblesort(){
            (this->lst).bubblesort();
            return *this;
        }

    private:
        c_doubly_linked_list<T> lst;
};



template <class T>
priority_queue<T>::priority_queue(initializer_list<T> lst_input){
    std::vector<T> myvector = lst_input;

    c_doubly_linked_list<T> aux;
    for (int i = 0; i < myvector.size(); ++i){
        aux.push_back(myvector[i]);
    }
    aux.bubblesort();
    lst = aux;
}

template <class T>
void priority_queue<T>::insert(T data){

}


int main(){
    Thread A(3, 0, 300);
    Thread B(1, 1, 300);
    Thread C(5, 2, 300);
    Thread D(5, 3, 300);
    Thread E(5, 4, 300);
    Thread F(3, 5, 300);
    priority_queue<Thread> Firefox({A,B,C,D,E,F});
}