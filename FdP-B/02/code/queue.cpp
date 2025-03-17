#include <iostream>
using namespace std;

template <class T>
class Queue {
private:
    T* data;
    int size;
    int capacity;

    void enlarge() {
        int newCapacity = this->capacity * 2;
        T* newData = new T[newCapacity];

        for(int i = 0; i < this->size; i++)
            newData[i] = this->data[i];

        delete [] this->data;
        this->data = newData;
        this->capacity = newCapacity;

        cout << "Capacità raddoppiata" << endl;
    }

public:
    Queue() : Queue(5) { }
    Queue(int cap) {
        this->size = 0;
        this->capacity = cap;
        this->data = new T[cap];
    }

    Queue(const Queue& other) {
        this->size = other.size;
        this->capacity = other.capacity;
        this->data = new T[other.capacity];

        for(int i = 0; i < other.size; i++)
            this->data[i] = other.data[i];
    }

    Queue& operator=(const Queue& other) {
        if(this != &other) {
            delete [] this->data;
            this->size = other.size; 
            this->capacity = other.capacity;
            this->data = new T[other.capacity];

            for(int i = 0; i < other.size; i++)
                this->data[i] = other.data[i];
        }
        return *this;
    }

    ~Queue() {
        delete [] this->data;
        cout << "Queue distrutta" << endl;
    }

    void add(const T& item){
        if(this->size == this->capacity)
            enlarge();
        this->data[this->size++] = item;
    }

    bool remove(const T& item) {
        for(int i = 0; i < this->size; i++) {
            if(data[i] == item) {
                for (int j = i; j < this->size - 1; j++)
                    data[j] = data[j + 1];
                this->size--;
                return true;
            }
        }
        return false;
    }

    T pop(){
        if(this->size == 0)
            throw string("Errore: coda vuota");

        T result = this->data[0];

        for(int i = 0; i < this->size - 1; i++)
            this->data[i] = this->data[i + 1];
        this->size--;

        return result;
    }

    int getSize() const { return this->size; }
    int getCapacity() const { return this->capacity; }

};

void testQueue(){
    cout << endl << " ==== Test classe Queue ==== " << endl;
    
    Queue<int> q1;

    cout << endl << " ==== Test aggiungi elementi ==== " << endl;
    q1.add(10);
    q1.add(20);
    q1.add(30);
    q1.add(40);
    q1.add(50);
    q1.add(60);
    q1.add(70);
    q1.add(80);
    q1.add(90);
    q1.add(100);
    q1.add(110);

    cout << endl << " ==== Test rimuovi elementi ==== " << endl;
    cout << q1.remove(50) << endl;
    cout << q1.remove(110) << endl;
    cout << q1.remove(900) << endl;

    cout << endl << " ==== Test pop ==== " << endl;
    cout << "Dimensione prima della pop: " << q1.getSize() << endl; 
    cout << "Elemento della pop: " << q1.pop() << endl;
    cout << "Dimensione dopo la pop: " << q1.getSize() << endl;
    
    cout << endl << " ==== Test costruttore di copia ==== " << endl;
    Queue<int> q2 = q1;
    cout << "Dimensione q1: " << q1.getSize() << endl;
    cout << "Dimensione coda copiata: " << q2.getSize() << endl;

    cout << endl << " ==== Test operatore di assegnamento ==== " << endl;
    Queue <int> q3;
    q3 = q1;
    cout << "Dimensione q1: " << q1.getSize() << endl;
    cout << "Dimensione coda copiata: " << q3.getSize() << endl;

    cout << endl << " ==== Fine Test classe Queue<int> ==== " << endl;
}

int main() {
    testQueue();
    return 0;
}

