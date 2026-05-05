#include <iostream>
#include <string>

using namespace std;

template<class T>
class Queue{

    private:

    T* A;
    int size;
    int capacity;

    void enlarge(){
        T* B = new T[this->capacity * 2];
        for(int i = 0; i < this->size; i++){
            B[i] = this->A[i];
        }
        this->capacity = this->capacity * 2;
        delete[] A;
        A = B;
    }

    public:

    Queue(){
        this->size = 0;
        this->capacity = 5;
        this->A = new T[capacity];
    }

    Queue(const Queue<T>& other){
        A = new T[other.capacity];
        for(int i = 0; i < other.size; i++){
            this->A[i] = other.A[i]; 
        }
        this->capacity = other.capacity;
        this->size = other.size;
    }

    ~Queue(){
        delete[] A;
    }

    void push(T elem){
        if(this->size == this->capacity){
            enlarge();
        }
        this->A[size] = elem;
        this->size++;
    }

    T pop(){
        if(this->size == 0){
            throw out_of_range("Coda vuota!!");
        }
        T res = this->A[0];

        T* B = new T[this->capacity];
        for(int i = 1; i < this->size; i++){
            B[i - 1] = A[i];
        }
        delete[] A;
        A = B;
        this->size--;

        return res;
    }

    const Queue& operator=(const Queue<T>& other){
        if(*this != &other){
            delete[] this->A;
            T B = new T[other.capacity];
            for(int i = 0; i < other.size; i++){
                B[i] = other.A[i];
            }
            A = B;
            this->size = other->size;
            this->capacity = other->capacity;
            return *this;
        }
        return *this;
    }

    T getElem(int n){
        if(n >= this->size){
            throw out_of_range("Elemento non esiste!!");
        }
        return A[n];
    }

    int getSize(){
        return size;
    }

    int getCapacity(){
        return capacity;
    }

};

template<typename T>
ostream& operator<<(ostream& dest, Queue<T>& other){

    dest << "{";
    for(int i = 0; i < other.getSize(); i++){
        dest << other.getElem(i);
        if( i != other.getSize() - 1){
            dest << ", ";
        }
    }

    dest << "}" << endl;
    
    return dest;
}


int main(){

    Queue<int> a;

    a.push(4);
    a.push(5);
    a.push(6);

    Queue<int> d(a);

    cout << a;

    cout << d;

    Queue<double> b;

    b.push(3.5);
    b.push(5.7);

    cout << b;

}