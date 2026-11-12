export module LinkedList;
import std;
using namespace std;

export template <typename T>
struct Node{
    T data;
    Node<T>* next;

    Node(const T& value, Node<T>* next_node) : data(value), next(next_node) {} 
};


export template <typename T>
class LinkedList{
private:
    Node<T>* head;
    Node<T>* tail;

public:
    template <typename U>
    friend void DeleteElmEnd(LinkedList<U>& list, int index);

    LinkedList() : head(nullptr), tail(nullptr) {}

    LinkedList(int count, int min_value, int max_value) : head(nullptr), tail(nullptr){
        if(count < 0){
            throw invalid_argument("count cannot be negative");
        }
        if(min_value > max_value){
            throw invalid_argument("min value cannot be greater than max value");
        }
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min_value, max_value);
        for(int i = 0; i < count; i++){
            push_tail(dis(gen));
        }
    }

    ~LinkedList(){
        clear();
    }

    LinkedList(const LinkedList<T>& other) : LinkedList() {
        if(other.head == nullptr){
            return;
        }
        Node<T>* current = other.head;
        do{
            push_tail(current->data);
            current = current->next;
        }while(current != other.head);
    }

    void clear(){
        if(head == nullptr){
            return;
        }
                tail->next = nullptr;
        Node<T>* current = head;
        while(current != nullptr){
            Node<T>* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = nullptr;
        tail = nullptr;
    }

    LinkedList<T>& operator=(const LinkedList<T>& other){
        if(this == &other){
            return *this;
        }
        if(other.head == nullptr){
            clear();
            return *this;
        }
        clear();
        Node<T>* current = other.head;
        do{
            push_tail(current->data);
            current = current->next;
        }while(current != other.head);
        return *this;
    }

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

    void push_tail(const LinkedList<T>& other){
        if(this == &other){
            return;
        }
        if(other.head == nullptr){
            return;
        }
        Node<T>* current = other.head;
        do{
            push_tail(current->data);
            current = current->next;
        }while(current != other.head);
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

    void push_head(const LinkedList<T>& other){
        if(this == &other){
            return;
        }
        if(other.head == nullptr){
            return;
        }
        LinkedList<T> tmp(other);
        tmp.reverse();
        Node<T>* current = tmp.head;
        do{
            push_head(current->data);
            current = current->next;
        }while(current != tmp.head);

    }

    void reverse(){
        if(head == nullptr || head == tail){
            return;
        }
        Node<T>* previous = nullptr;
        Node<T>* current = head;
        Node<T>* next_node = nullptr;
        Node<T>* old_head = head;
        do{
            next_node = current->next;
            current->next = previous;
            previous = current;
            current = next_node;
        }while(current != head);
        head = previous;
        tail = old_head;
        tail->next = head;
    }

    void pop_head(){
        if(head == nullptr){
            return;
        }
        if(head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        else{
            Node<T>* tmp = head;
            head = head->next;
            tail->next = head;
            delete tmp;
        }
    }

    void pop_tail(){
        if(head == nullptr){
            return;
        }
        if(head == tail){
            delete head;
            head = nullptr;
            tail = nullptr;
            return;
        }
        Node<T>* tmp = head;
        while(tmp->next != tail ){
            tmp = tmp->next;
        }
        delete tail;
        tail = tmp;
        tail->next = head;
    }

    void delete_node(const T& value){
        while(head != nullptr && head->data == value){
            pop_head();
        }
        if(head == nullptr){
            return;
        }
        Node<T>* previous = head;
        Node<T>* current = head->next;
        while(current != head){
            if(current->data == value){
                if(current == tail){
                    tail = previous;
                    tail->next = head;
                }else{
                    previous->next = current->next;
                }

                delete current;
                current = previous->next;
            }else{
                previous = current;
                current = current->next;
            }
        }

    }

    T& operator[](int index){
        if(index < 0){
            throw invalid_argument("index cannot be negative");
        }
        if(head == nullptr){
            throw invalid_argument("list is empty");
        }
        int count = 0;
        Node<T>* current = head;
        do{
            count++;
            current = current->next;
        }while(current != head);
        int new_index = index % count;
        for(int i = 0;i < new_index; i++){
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const{
        if(index < 0){
            throw invalid_argument("index cannot be negative");
        }
        if(head == nullptr){
            throw invalid_argument("list is empty");
        }
        int count = 0;
        const Node<T>* current = head;
        do{
            count++;
            current = current->next;
        }while(current != head);
        int new_index = index % count;
        for(int i = 0;i < new_index; i++){
            current = current->next;
        }
        return current->data;
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