#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

void add(node* &lst, int value){
    if(lst == nullptr) {
        node* new_node = new node;
        new_node->data = value;
        new_node->next = lst;
        lst = new_node;
    } else {
        node* new_node = new node;
        new_node->data = value;
        new_node->next = nullptr;

        node* cursor = lst;
        while(cursor->next != nullptr){
            cursor = cursor->next;
        }
        cursor->next = new_node;
    }
}

void print(node* lst){
    node* cursor = lst;
    while (cursor != nullptr){
        cout << cursor->data << " ";
        cursor = cursor->next;
    }
    cout << endl;
}

int len(node* lst){
    if(lst == nullptr)
        return 0;
    return 1 + len(lst->next);
}

void free(node* lst) {
    if(lst == nullptr)
        return;
    free(lst->next);
    delete lst;
}

int getValue(node* lst, int i) {
    if(lst == nullptr)
        return -1;
    if(i > len(lst))
        return -1;
    
    node* cursor = lst;
    int indiceCorrente = 0;
    while (cursor != nullptr && indiceCorrente < i) {
        cursor = cursor->next;
        indiceCorrente++;
    }

    return cursor->data;
}

bool simmetrica(node* lst) {
    int lunghezza = len(lst);
    for(int i = 0; i < lunghezza / 2; i++){
        if(getValue(lst, i) != getValue(lst, lunghezza - 1 - i))
            return false;
    }
    return true;
}

bool contains(node* lst, int value){
    int lunghezza = len(lst);
    for(int i = 0; i < lunghezza; i++){
        if(getValue(lst, i) == value)
            return true;
    }
    return false;
}

node* sommaVicini(node* lst) {
    int lunghezza = len(lst);
    node* new_lst = nullptr;

    add(new_lst, getValue(lst, 0));

    for(int i = 1; i < lunghezza - 1; i++) {
        int somma = getValue(lst, i - 1) + getValue(lst, i + 1);
        add(new_lst, somma); 
    }

    add(new_lst, getValue(lst, lunghezza - 1));
    return new_lst;
}

node* listeIntervallate(node* lst1, node* lst2) {
    node* new_list = nullptr;

    while(lst1 != nullptr || lst2 != nullptr) {
        if(lst1 != nullptr) {
            add(new_list, lst1->data);
            lst1 = lst1->next;
        }
        if(lst2 != nullptr) {
            add(new_list, lst2->data);
            lst2 = lst2->next;
        }
    }

    return new_list;
}

node* intersect(node* lst1, node* lst2) {
    node* new_list = nullptr;
    int len1 = len(lst1);
    int len2 = len(lst2);

    for(int i = 0; i < len1; i++){
        for(int j = 0; j < len2; j++){
            if(getValue(lst1, i) == getValue(lst2, j) 
                    && !contains(new_list, getValue(lst1, i))) {
                add(new_list, getValue(lst1, i));
            }
        }
    }

    return new_list;
}

void rimuoviNegativi(node* &lst){
    // rimuovi eventuali nodi iniziali con valore < 0
    while (lst != nullptr && lst->data < 0) {
        node* temp = lst;
        lst = lst->next;
        delete temp;
    }

    // se la lista è ora vuota, ritorna
    if (lst == nullptr) 
        return;
    
    // gestisci i nodi rimanenti
    node* curr = lst;

    while (curr->next != nullptr) {
        if (curr->next->data < 0) {
            // rimuovi il nodo successivo
            node* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        } else {
            // passa al nodo successivo
            curr = curr->next;
        }
    }
}

int main(){
    node* lst = nullptr;
    add(lst, 10);
    add(lst, 20);
    add(lst, 30);
    add(lst, 40);
    add(lst, 50);
    add(lst, 10);

    cout << getValue(lst, 2) << endl;
    if(simmetrica(lst))
        cout << "Lista simmetrica" << endl;
    else
        cout << "Lista non simmetrica" << endl;

    print(lst);

    node* lst2 = sommaVicini(lst);
    print(lst2);

    node* lstIntervallata = listeIntervallate(lst, lst2);
    print(lstIntervallata);

    node* lstIntersect = intersect(lst, lst2);
    print(lstIntersect);


    node* lst3 = nullptr;
    add(lst3, 10);
    add(lst3, -20);
    add(lst3, 30);
    add(lst3, -40);
    add(lst3, 50);
    add(lst3, -10);
    print(lst3);
    rimuoviNegativi(lst3);
    print(lst3);
    




    free(lst);
    free(lst2);
    free(lstIntervallata);
    free(lstIntersect);
    free(lst3);
    

    return 0;
}