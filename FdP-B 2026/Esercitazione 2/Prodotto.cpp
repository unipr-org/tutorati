#include <iostream>
#include <string>  
#include <exception>

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
            throw invalid_argument("Quantita' negativa!!");
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

        try{
            if(quantita_valida(quantita)){
                this->quantita = quantita;
            } 
        } catch (exception e){
            cout << e.what();
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
            throw invalid_argument("Id negativo!!");
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
            throw invalid_argument("Prezzo non positivo!!");
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
                throw exception();
            }
        }
    }

    // Operatori

    Prodotto operator+ (const Prodotto& p){
        if(this->id == p.getId()){
            Prodotto res(this->id, this->nome, this->prezzo, this->quantita + p.getQuantita());
            return res;

            // return Prodotto(this->id, this->nome, this->prezzo, this->quantita + p.getQuantita());
        } else {
            cout << "Id diverso!!" << endl;
            Prodotto res;
            return res;
            // return Prodotto();
        }
    }

    bool operator== (const Prodotto& p){
        if(this->id == p.getId()){
            return true;
        } else {
            return false;
        }

        //return this->id == p.getId();
    }

    bool operator!= (const Prodotto& p){
        if(this->id != p.getId()){
            return true;
        } else {
            return false;
        }

        // return this->id != p.getId();

        // return !(this->operator==(p));
    }

};

ostream& operator<< (ostream& dest, const Prodotto& p) {
    dest << "Prodotto = " << p.getId() << endl << "Nome = " << p.getNome() << endl;
    dest << "Quantita' = " << p.getQuantita() << endl << "Prezzo all'unita' = " << p.getPrezzo() << endl;
    dest << endl;
    return dest;
}

int main(){

    Prodotto e(3, "quaderno", 2, 10);
   
    Prodotto a(1, "sveglia");
    Prodotto b(2,"penne", 1.5, 100);
    Prodotto c(2,"penne", 1.5, 200);

    cout << a << b;

    Prodotto d = b + c;
    cout << d;

    cout << (a == b) << endl;
    cout << (a != b) << endl;

    try{
        a.rimuoviQuantita(2);
    } catch (invalid_argument e){
        cout << e.what();
    } catch (exception e){
        cout << e.what() << endl;
    }

    // Esegue perchè ho gestito le eccezzioni
    cout << "Eseguito blocco try/catch" << endl;

    a.rimuoviQuantita(-2);

    // Non è detto che esegua perchè non ho gestito le eccezioni
    cout << "Istruzione successiva" << endl;
}