/*O companie de transport vrea să țină evidența autobuzelor. Implementează clasa Autobuz cu:
- un id constant, numele liniei (string), numărul de stații și un vector alocat dinamic (float*) cu durata în minute dintre stații;
- un membru static care numără câte autobuze au fost create;
- un constructor fără parametri, care generează id-ul din contorul static, și un constructor cu parametri, care copiază vectorul în profunzime (deep copy);
- o metodă care afișează toate datele autobuzului;
- getter și setter pentru numărul de stații. Setter-ul aruncă excepția "Numar de statii negativ!" (const char*) pentru o valoare negativă și codul 400 (int) pentru mai mult de 50 de stații;
- getter și setter pentru vectorul de durate. Getter-ul întoarce o copie a vectorului, nu adresa internă. Setter-ul preia un vector alocat dinamic și îl eliberează după copiere;
- o metodă care calculează durata totală a traseului;
- un destructor.

În main: testează excepțiile cu try/catch (cu mai multe blocuri catch), apoi lucrează cu un obiect alocat dinamic (new/delete) și afișează câte autobuze au fost create.
*/

#include<iostream>
#include<string>
using namespace std;

class Autobuz {
private:
    const int id;
    string linie;
    int nrStatii;
    float* durate;
public:
    static int nrAutobuze;

    Autobuz() : id(++nrAutobuze) {
        this->linie = "Necunoscuta";
        this->nrStatii = 0;
        this->durate = nullptr;
    }

    Autobuz(int id, string linie, int nrStatii, float* durate) : id(id) {
        this->linie = linie;
        this->nrStatii = nrStatii;
        this->durate = new float[nrStatii];
        for (int i = 0; i < nrStatii; i++)
            this->durate[i] = durate[i];
        nrAutobuze++;
    }

    void afisareAutobuz() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Linia: " << this->linie;
        cout << endl << "Nr statii: " << this->nrStatii;
        if (this->nrStatii > 0 && this->durate != nullptr) {
            cout << endl << "Durate intre statii: ";
            for (int i = 0; i < this->nrStatii - 1; i++)
                cout << this->durate[i] << ", ";
            cout << this->durate[this->nrStatii - 1] << " min.";
        }
    }

    int getNrStatii() { return this->nrStatii; }

    void setNrStatii(int nrNou) {
        if (nrNou < 0) throw "Numar de statii negativ!";
        if (nrNou > 50) throw 400;
        this->nrStatii = nrNou;
    }

    float* getDurate() {
        if (this->durate == nullptr) return nullptr;
        float* copie = new float[this->nrStatii];
        for (int i = 0; i < this->nrStatii; i++)
            copie[i] = this->durate[i];
        return copie;               // apelantul face delete[]
    }

    void setDurate(float* vector, int n) {
        setNrStatii(n);             // poate arunca exceptie
        if (this->durate != nullptr)
            delete[] this->durate;
        this->durate = new float[this->nrStatii];
        for (int i = 0; i < this->nrStatii; i++)
            this->durate[i] = vector[i];
        delete[] vector;
    }

    float durataTotala() {
        float s = 0;
        for (int i = 0; i < this->nrStatii; i++)
            s += this->durate[i];
        return s;
    }

    ~Autobuz() {
        if (this->durate != nullptr)
            delete[] this->durate;
    }
};

int Autobuz::nrAutobuze = 0;

int main() {
    Autobuz a1;
    a1.afisareAutobuz();

    try {
        a1.setNrStatii(-3);
    }
    catch (int cod) { cout << endl << "Cod eroare: " << cod; }
    catch (const char* mesaj) { cout << endl << mesaj; }
    catch (...) { cout << endl << "Eroare necunoscuta!"; }

    try {
        a1.setNrStatii(70);
    }
    catch (int cod) { cout << endl << "Cod eroare: " << cod << " (prea multe statii)"; }
    catch (const char* mesaj) { cout << endl << mesaj; }

    a1.setDurate(new float[4] {3.5, 4, 2.5, 6}, 4);
    float* copie = a1.getDurate();
    cout << endl << "Durate primite prin getter: ";
    for (int i = 0; i < a1.getNrStatii(); i++)
        cout << copie[i] << " ";
    delete[] copie;

    a1.afisareAutobuz();
    cout << endl << "Durata totala: " << a1.durataTotala() << " min";

    float* d = new float[3] {5, 7.5, 4};
    Autobuz* pA = new Autobuz(100, "Linia 336", 3, d);
    pA->afisareAutobuz();
    delete pA;
    delete[] d;

    cout << endl << "Am creat " << Autobuz::nrAutobuze << " autobuze!";
    return 0;
}
