/*



*/

#include "linearDS.h"


class lunch_line{
    int id = 0;
    int pos = 0;
    /*Using a doubly_linked list of type doubly_linked_list of type integers
    It represents a list of elements that holds two integers, id and pos, respectively.
    */
    c_doubly_linked_list<c_doubly_linked_list<int>> object_queue;        
    int current_queue_size = 0;
    int const average_service_time = 1; /* Minutes */

public:


    
    void show_remaining_time_at_the_end(){
        cout << "Waiting time: ";
        cout << average_service_time*current_queue_size << "min" << endl;
    }
    void request_to_join_the_queue(){
        c_doubly_linked_list id_and_pos({id,pos});
        //The program is going to give your id
        cout << "Your id is going to be: " << id << endl;
        object_queue.push_back(id_and_pos);
        id++;
        pos++;
        current_queue_size++;
    }
    //Function that return the person position based on the id
    //It helps to make the next function to work
    int person_position(int person_id){
        int id_to_be_found = person_id;
        int id_aux = 0;
        bool find_it = false;
        int pos_aux = 0;

        while(pos_aux < current_queue_size){
            id_aux = object_queue.ith_item(pos_aux).ith_item(0);
            if (id_aux == id_to_be_found){
                break;
            }
            pos_aux++;
        }
        return pos_aux;
    }

    void show_remaining_time(int person_id){
        int waiting_time_to_be_served = average_service_time*person_position(person_id);
        cout << "You will be attended to in: ";
        cout << waiting_time_to_be_served << "min" << endl;
    }
    //If someone leaves the queue at position n, you need to update the position on the queue of the persons after him
    void refresh_position_in_queue_after_request_to_leave(int index){
        int pos = index;
        int id = 0;
        while(index < current_queue_size){
            c_doubly_linked_list id_and_pos({object_queue.ith_item(index).ith_item(0), pos});
            object_queue.modifying_data(pos, id_and_pos);
            index++;
            pos++;
        }
        

    }

    void request_to_leave_the_queue(){
        //pedir o id e com base no id fornecer a pos
        int id_to_be_found = 0;
        int id_aux = 0;
        bool find_it = false;
        int pos_aux = 0;
        cout << "What is your id?" << endl;
        cin >> id_to_be_found;

        while(pos_aux < current_queue_size){
            id_aux = object_queue.ith_item(pos_aux).ith_item(0);
            if (id_aux == id_to_be_found){
                break;
            }
            pos_aux++;
        }
        object_queue.pop_ith_item(pos_aux);
        current_queue_size--;
        refresh_position_in_queue_after_request_to_leave(pos_aux);
    }

};

void show_main_menu(void){

    cout << "Enter the key: " << endl;
    cout << "|--------------------------------------|"       <<endl;
    cout << "| " << "1 to request to join the queue       "<<"|"<<endl;
    cout << "|--------------------------------------|"          <<endl;
    cout << "| " << "2 to request to leave the queue      "<<"|"<<endl;
    cout << "|--------------------------------------|"          <<endl;
    cout << "| " << "3 to show your remaining time        "<<"|"<<endl;
    cout << "|--------------------------------------|"          <<endl;

    cout << endl;
}


int main(){

    lunch_line CT;

    char keys;

    int id;
    do{
        CT.show_remaining_time_at_the_end();
        show_main_menu();
        cin >> keys;
        switch (keys)
        {

        case '1':
            CT.request_to_join_the_queue();
            cout << endl;
            break;
        case '2':
            CT.request_to_leave_the_queue();
            cout << endl;
            break;
        case '3':
            cout << "Enter your identification: " << endl;
            cin >> id;
            CT.show_remaining_time(id);
            cout << endl;
            char aux;
            cout << "Enter any key to go back" << endl;
            cin >> aux;
            break;

        }
            
        //std::system("clear");
    }while(keys != 'q');
    
}
