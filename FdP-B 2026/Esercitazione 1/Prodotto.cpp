#include <iostream>
#include <string>  

using namespace std;

class Prodotto{

    private:

    // Attributi

    int id;
    string nome;
    double prezzo;
    int quantita;
    bool disponibilita;

    // Funzioni ausiliarie

    bool quantita_valida(int quantita) const{
        if(quantita < 0){
            cout << "Errore, quantita negativa" << endl;
            return false;
        }
        return true;
    }

    void modificaDisponibilita() {
        if(this->quantita > 0){
            this->disponibilita = true;
        } else {
            this->disponibilita = false;
        }
    }

    public:

    // Costruttori

    Prodotto(){
        this->id = 0;
        this->prezzo = 0;
        this->quantita = 0;
        this->disponibilita = false;
        this->nome = "";
    }

    Prodotto(int id, string nome){
        this->id = id;
        this->nome = nome;
        this->prezzo = 0;
        this->quantita = 0;
        this->disponibilita = false;
    }

    Prodotto(int id, string nome, double prezzo, int quantita){
        this->id = id;
        this->nome = nome;
        this->prezzo = prezzo;

        if(quantita_valida(quantita)){
            this->quantita = quantita;
        } else {
            this->quantita = 0;
        }

        modificaDisponibilita();

        //this->disponibilita = (quantita > 0);
        /*
        if(quantita > 0){
            this->disponibilita = true;
        } else{
            this->disponibilita = false;
        }
        */
    }

    // Getter e Setter

    int getId() const{
        return this->id;
    }

    void setId(const int id){
        if(id >= 0){
            this->id = id;
        } else {
            cout << "Id negativo" << endl;
        }
    }

    string getNome() const{
        return this->nome;
    }

    void setNome(const string nome){
        this->nome = nome;
    }

    double getPrezzo() const{
        return this->prezzo;
    }

    void setPrezzo(const double prezzo){
        if(prezzo > 0){
            this->prezzo = prezzo;
        } else {
            cout << "Prezzo non positivo" << endl;
        }
    }

    int getQuantita() const{
        return this->quantita;
    }

    void setQuantita(const int quantita){
        if(quantita_valida(quantita)){
            this->quantita = quantita;
            modificaDisponibilita();
        }
    }

    bool getDisponibilita() const{
        return this->disponibilita;
    }

    // Metodi

    void aggiungiQuantita() {
        this->quantita += 1;
        modificaDisponibilita();
    }

    void aggiungiQuantita(int quantita){
        if(quantita_valida(quantita)){
            this->quantita += quantita;
            modificaDisponibilita();
        }
    }

    void rimuoviQuantita(){
        if(this->quantita == 0){
            cout << "Errore, quantita' zero" << endl;
        } else {
            this->quantita -= 1;
            modificaDisponibilita();
        }
    }

    void rimuoviQuantita(int quantita){
        if(quantita_valida(quantita)){
            if(this->quantita - quantita >= 0){
                this->quantita -= quantita;
                modificaDisponibilita();
            } else {
                cout << "Errore, quantita superiore a quella disponibile" << endl;          
            }
        }
    }

};

int main(){

    Prodotto a(1, "sveglia");
    Prodotto b(2,"penne", 1.5, -100);

}