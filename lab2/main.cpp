import std;
import LinkedList;
using namespace std;



int main(){
    try{
        LinkedList<int> list;

        list.push_tail(10);
        list.push_tail(20);
        list.push_tail(30);
        list.push_tail(40);

        list.reverse();

        cout << list << '\n';

    }catch(exception& e){
        cout << "Error: " << e.what() << '\n';
    }


}
