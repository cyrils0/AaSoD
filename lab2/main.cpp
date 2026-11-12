import std;
import LinkedList;
using namespace std;

template <typename U>
void DeleteElmEnd(LinkedList<U>& list, int index){
    if(list.head == nullptr){
        throw invalid_argument("list is empty");
    }
    if(index <= 0){
        throw invalid_argument("index must be positive");
    }
    Node<U>* current = list.head;
    int count = 0;
    do{
        count++;
        current = current->next;
    }while(current != list.head);
    if (index > count) {
        throw invalid_argument("index greater than list size");
    }

    list.reverse();
    Node<U>* current2 = list.head;
    Node<U>* prev = nullptr;
    for(int i = 0; i < index - 1; i++){
        prev = current2;
        current2 = current2->next;
    }

    if(index == 1){
        list.pop_head();
    }
    else if(index == count){
        list.pop_tail();
    }
    else{
        prev->next = current2->next;
        delete current2;
    }
    list.reverse();
}

int main(){
    try{
        LinkedList<int> list;

        list.push_tail(10);
        list.push_tail(20);
        list.push_tail(30);
        list.push_tail(40);
        list.push_tail(50);
        list.push_tail(60);
        list.push_tail(70);


        cout << list << '\n';
        cout << "after deletion: " << '\n';
        DeleteElmEnd(list, 4);
        cout << list << '\n';
    }catch(exception& e){
        cout << "Error: " << e.what() << '\n';
    }
}
