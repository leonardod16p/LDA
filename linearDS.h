#include <iostream>
#include <malloc.h>
#include <initializer_list>
#include <vector>


size_t portable_ish_malloced_size(const void* p) {
    return malloc_usable_size((void*)p);
}

using namespace std;

enum t_Direcao_de_percurso {DO_INICIO_PARA_O_FIM, DO_FIM_PARA_O_INICIO};



class LinearDataStructure{
    public:

};

class c_array: public LinearDataStructure{
    int m;
    double* array_address;                  //Defining a pointer to the first element of the array

public:

    double* get_address();
    //array is constructed allocating memory at the array_addres
    //It has some cout lines that gives me information of the memory allocation
    c_array(int size){
        m = size;

        //calculate the memory allocation
        unsigned int byte_size_vec = m*sizeof(double);
        if(!(array_address=(double*)malloc(byte_size_vec))){
            cout << "No memory" << endl;
            exit(1);
        }
        cout << "First Element Address: " << array_address << endl;
        cout << "Last Element Address: " << array_address + m << endl;
        cout << "Sizeof: " << byte_size_vec << endl;
        size_t true_length = portable_ish_malloced_size(array_address);
        printf("%zu\n", true_length);
    }

    //c_array& operator=(double value);

    //Basic [] overload to implement direct acess in the array
    double operator[](int index){return array_address[index];}

    //Values defined by the user input
    void define_values();
    //Helps to solve some problems
    void put_values(int, int);
};

class c_list;

class c_node_singly_linked_list {
    double data;
    c_node_singly_linked_list * next;
    friend class c_list;

public:
    c_node_singly_linked_list(double p_data) { data = p_data; next = nullptr; }
};

class c_list: public LinearDataStructure{
    c_node_singly_linked_list * start;
    friend class c_stack;        //stack is implemented using singly_linked_lists
public:
    c_list(void) {start = nullptr; }
    c_list(initializer_list<double> l);

    double ith_item(int index);
    void push(int p_data);
    void scroll_through_list(void);        //It output the list elements
    double pop();
};

template<class T>
class c_doubly_linked_list;
template<class T>
class c_node_doubly_linked_list {
    T data;
    c_node_doubly_linked_list * next;
    c_node_doubly_linked_list * previous;
    friend class c_doubly_linked_list<T>;

public:
    c_node_doubly_linked_list(T p_data) { data = p_data; previous = next = nullptr;};
};
template<class T>
class c_doubly_linked_list: public LinearDataStructure{
    c_node_doubly_linked_list<T>* start;
    c_node_doubly_linked_list<T>* end;
    int size = 0;
    friend class c_node_doubly_linked_list<T>;
    public:
        c_doubly_linked_list(void){start = end = nullptr;}
        c_doubly_linked_list(initializer_list<T>);
        
        T ith_item(int index);
        T pop_ith_item(int index);
        void push(T p_data);
        void push_back(T p_data);
        T pop();
        void scroll_through_list(t_Direcao_de_percurso);
        void swap(int index){
            if (start->next != nullptr){
                T data1;
                T data2;
                c_node_doubly_linked_list<T> * aux = start;

                int i = 0;
                while (i < index){
                    start = start->next;
                    i++;
                }
                data1 = start->data;
                data2 = start->next->data;

                start->data = data2;
                start->next->data = data1;

                while (start != aux){
                    start = start->previous;
                    i++;
                }
            }

            else{
                cout << "You are trying to swap the last element with the next, which does not exists" << endl;
            }
        }

        //It serves me to solve lunch_line problem
        void modifying_data(int index, T data);
        c_doubly_linked_list<T> bubblesort(void);
        void going_to_ith_item(int index);
};



template <class T>
class circular_singly_linked_list;
template <class T>
class c_node_circular_singly_linked_list {
    T data;
    c_node_circular_singly_linked_list * next;
    friend class circular_singly_linked_list<T>;

public:
    c_node_circular_singly_linked_list(T p_data) { data = p_data; next = nullptr; }
};

template <class T>
class circular_singly_linked_list: public LinearDataStructure{
    c_node_circular_singly_linked_list<T>* current;

public:

    circular_singly_linked_list(void){current= nullptr;}
    void insert_data(T data){
        if (current == nullptr){
            current = new c_node_circular_singly_linked_list(data); 
            current->next = current;
        }
        else{
            c_node_circular_singly_linked_list<T>* aux;
            aux = new c_node_circular_singly_linked_list(data); 
            aux->next = current->next;
            current->next = aux;
            current = current->next;
        }
    };
    T pop(){
        T data = 0;
        data = current->data;
        c_node_circular_singly_linked_list<T> * aux = current->next;
        
        while (true){
            aux = aux->next;
            if (current == aux->next)
                break;
        }
        
        aux->next = aux->next->next;
        current = aux;
        return data;
};
    T ith_item(int index){
        T data = 0;
        int i = 0;

        c_node_circular_singly_linked_list<T> * aux = current;
        while (i < index){
            aux = aux->next;
            i++;
        }
        data = aux->data;
        return data;
    }
    void swap(int index){
        T data1 = 0;
        T data2 = 0;
        c_node_circular_singly_linked_list<T> * aux = current;


        int i = 0;
        while (i < index){
            current = current->next;
            i++;
        }
        data1 = current->data;
        data2 = current->next->data;

        current->data = data2;
        current->next->data = data1;

        while (current != aux){
            current = current->next;
            i++;
        }
    }

};


class c_stack: public LinearDataStructure{
    c_list lst;
public:
    void push(double data){
        lst.push(data);
    }

    double pop(void){
        double data = 0;
        data = lst.pop();
        return data;
    }

    bool it_is_empty(void){return lst.start;}

    void representation(){
        lst.scroll_through_list();
    }
};


template<class T>
class queue: public LinearDataStructure{
    c_doubly_linked_list<T> lst;

public:

    void push(T data){
        lst.push_back(data);
    };
    T pop(void){
        T data = lst.pop();
        return data;
    }

    T pop_ith_item(int index){
        return lst.pop_ith_item(index);
    }
    


    bool it_is_empty(void){return lst.start;}

    void show_queue(t_Direcao_de_percurso orientation){
        lst.scroll_through_list(orientation);
    }
};


/*
Array Methods
*/

double* c_array :: get_address(){
    return array_address;
};

void c_array :: define_values(){
    cout << "To enter an element, type the number you want and press enter: " << endl;
    int i = 0;
    while (i < m) {
        cin >> *(array_address + i);
        ++i;
    }
};

void c_array :: put_values(int a, int b){
    int i = 0;
    *(array_address + i) = a;
    ++i;
    *(array_address + i) = b;
};

/*
Lists Methods
*/

c_list::c_list(initializer_list<double> l){
    start = nullptr;
    std::vector<double> myvector = l;
    std::vector<double>::reverse_iterator rit = myvector.rbegin();
    for (int i = 0; rit!= myvector.rend(); ++rit){
        cout << *rit << endl; 
        push(*rit);
    }
}

void c_list::push(int p_data)
{
    c_node_singly_linked_list * new_node; // ponteiro para o novo NO

    new_node = new c_node_singly_linked_list(p_data); // cria o novo NO na memoria com o dado
    if (start != nullptr) // if the list is not empty
        new_node->next  = start;
    start = new_node;
}

double c_list::pop(){
    double data = 0;
    c_node_singly_linked_list * aux = start->next;
    data = start->data;
    delete start;
    start = aux;
    return data;
}

double c_list::ith_item(int index){
    c_node_singly_linked_list * aux = start; // Points to the first node on the list
    cout << "Address: " << start << endl;
    int i = 0;
    double data = 0;
    while (i < index){        //iterate over the list till the element associated with the index
        aux = aux->next;
        i++;
    }
    data =  aux->data;
    return data;
}

void c_list::scroll_through_list(void)
{
    c_node_singly_linked_list * aux = start; //Points to the first node on the list
    cout << "Address: " << start << endl;
    while (aux) // while is not the end of the list (It test if the list is empty as well)
    {
        cout << "aux: " << aux << endl;
        cout << aux->data << endl;
        aux = aux->next;
    }
}

/*
Doubly Linked Lists Methods
*/
template<class T>
void c_doubly_linked_list<T>::scroll_through_list(t_Direcao_de_percurso direcao_de_percurso){
    c_node_doubly_linked_list<T>* aux;

    if (direcao_de_percurso == DO_INICIO_PARA_O_FIM)
        aux = start;
    else
        aux = end;

    while (aux){
        cout << aux->data << endl;
        aux = (direcao_de_percurso == DO_INICIO_PARA_O_FIM) ? aux->next : aux->previous;
    }
}
template<class T>
void c_doubly_linked_list<T>::push(T p_data){
    this->size++;
    c_node_doubly_linked_list<T> * new_node; //Points to the new node

    new_node = new c_node_doubly_linked_list(p_data); // create the new node on the memory with the new data
    if (start != nullptr) {  //if the list is not empty
        new_node->next  = start;
        start->previous = new_node;
    }
    start = new_node; 
    if (end == nullptr) // if the list is empty
        end = new_node;
}
template<class T>
void c_doubly_linked_list<T>::push_back(T p_data){
    this->size++;
    c_node_doubly_linked_list<T>* new_node;

    new_node = new c_node_doubly_linked_list(p_data);

    if (end != nullptr) {// if the list is not empty
        new_node->previous  = end;
        end->next = new_node;
    }
    end = new_node; // vale tanto se a lista estiver vazia ou nao
    if (start == nullptr) // if the list is empty
        start = new_node;
}
template<class T>
T c_doubly_linked_list<T>::pop(){
    this->size--;
    double data = 0;
    c_node_doubly_linked_list<T> * aux = start->next;
    data = start->data;
    delete start;
    start = aux;
    return data;
}
template<class T>
T c_doubly_linked_list<T>::ith_item(int index){
    c_node_doubly_linked_list<T> * aux = start; //Points to the first node on the list
    int i = 0;
    T data = start->data;
    while (i < index){ //iterate over the list till the element associated with the index
        aux = aux->next;
        i++;
    }
    data = aux->data;
    return data;
    }

template<class T>
T c_doubly_linked_list<T>::pop_ith_item(int index){
    this->size--;
    c_node_doubly_linked_list<T> * aux = start; //Points to the first node on the list
    int i = 0;
    T data = start->data;
    while (i < index){ //iterate over the list till the element associated with the index
        start = start->next;
        i++;
    }
    start->previous->next = start->next;
    data =  start->data;
    delete start;
    while (start != aux){ // while is not the end of the list (It test if the list is empty as well)
        start = start->previous;
    }
    
    return data;
}
template<class T>
c_doubly_linked_list<T>::c_doubly_linked_list(initializer_list<T> items){
    start = nullptr;
    std::vector<T> myvector = items;

    typename std::vector<T>::reverse_iterator rit = myvector.rbegin();
    for (int i = 0; rit!= myvector.rend(); ++rit){
        push(*rit);
    }
}

template<class T>
void c_doubly_linked_list<T>::modifying_data(int index, T data){
    c_node_doubly_linked_list<T> * aux = start; //Points to the first node on the list
    cout << "Address: " << start << endl;
    int i = 0;
    while (i < index){ 
        start = start->next;
        i++;
    }

    start -> data = data;
    while (start != aux){ 
        start = start->previous;
    }
}

template<class T>
c_doubly_linked_list<T> c_doubly_linked_list<T> :: bubblesort(){
    c_doubly_linked_list<T> aux = *this;
    int n = this->size;
    bool swapped = false;
    do{
        swapped = false;
        for (int i = 0; i < n-1; i++){
            T data1 = aux.ith_item(i);
            T data2 = aux.ith_item(i+1);
            if (data1 > data2){
                aux.swap(i);
                swapped = true;
                i = 0;
            }
        }
    }while(!swapped);
    
    return aux;
}



