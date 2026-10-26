import std;
using namespace std;


template <typename T>
struct Node{
    T data;
    Node<T>* next;

    Node(const T& value, Node<T>* next_node) : data(value), next(next_node) {} 
};

template <typename T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_tail(const T& value) {
        Node<T>* new_node = new Node<T>(value, nullptr);
        if (head == nullptr){
            head = new_node;
            tail = new_node;
            tail->next = head;
        }
        else{
            tail->next = new_node;
            tail = new_node;
            tail->next = head;
        }
    }
    void push_head(const T& value){
        Node<T>* new_node = new Node<T>(value, nullptr);
        if(head == nullptr){
            head = new_node;
            tail = new_node;
            tail->next = head;
        }
        else{
            new_node->next = head;
            head = new_node;
            tail->next = head;
        }
    }
    friend ostream& operator<<(ostream& out, const LinkedList<T>& list){
        Node<T>* current = list.head;
        if(current == nullptr){
            out << "List is empty";
            return out;
        }
        else{
            do{
                out << current->data << " ";
                current = current->next;
            }while(current != list.head);
            return out;
        }
    }

};



int main(){
    LinkedList<int> list;

    list.push_tail(10);
    list.push_tail(20);
    list.push_tail(30);
    cout << list << endl;
}
