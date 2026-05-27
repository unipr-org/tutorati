#include <iostream>

using namespace std;

template<typename T>
class Multiset{

    private:

    T* container;
    int size;
    int capacity;

    void enlarge(){
        capacity = this->capacity * 2;
        T* aux = new T[capacity];
        for(int i = 0; i < size; i++){
            aux[i] = container[i];
        }
        delete[] container;
        container = aux;
    }

    public:

    Multiset(){
        size = 0;
        capacity = 5;
        container = new T[capacity];
    }

    Multiset(const Multiset& other){
        container = new T[other.capacity];
        this->capacity = other.capacity;
        this->size = other.size;

        for(int i = 0; i < size; i++){
            container[i] = other.container[i];
        }
    } 


    Multiset& operator=(const Multiset& other){
        if(this != &other){
            delete[] container;
            capacity = other.capacity;
            size = other.size;
            T* aux = new T[capacity];
            for(int i = 0; i < size; i++){
                aux[i] = other.container[i];
            }
            container = aux;
        }
        return *this;
    }

    ~Multiset(){
        delete[] container;
    }

    void add(const T& elem){
        if(capacity == size){
            enlarge();
        }
        container[size++] = elem;
    }

    void remove(const T& elem){
        if(size == 0){
            throw runtime_error();
        }

        T* aux = new T[capacity];
        int aux_size = 0;

        for(int i = 0; i < size; i++){
            if(container[i] != elem){
                aux[aux_size++] = container[i];
            }
        }

        size = aux_size;
        delete[] container;
        container = aux;

    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        return size == 0;
    }

    int cardinality(const T& elem) const{
        int res = 0;
        for(int i = 0; i < size; i++){
            if(container[i] == elem){
                res++;
            }
        }
        return res;
    }

    T& getElem(int i) const{
        if(i >= size){
            throw out_of_range();
        }
        return container[i];
    }

};

template<typename T>
ostream& operator<<(const ostream& fout, const Multiset<T>& other){
    fout << "[";
    for(int i = 0; i < other.getSize(); i++){
        fout << other.getElem(i);
        if( i < other.getSize() - 1){
            fout << ", ";
        }
    }
    fout << "]" << endl;
    return fout;
}
