/*testtesttesttest01011
Enunț:
Primăria vrea un sistem de evidență pentru parcările din oraș. Implementează clasa Parcare cu:
- un enum TipParcare { SUPRATERANA = 1, SUBTERANA = 2 };
- un id constant, numele parcării, tariful pe oră (float), tipul parcării, numărul de niveluri și un vector dinamic (int*) cu numărul de locuri libere de pe fiecare nivel;
- un contor static, constructori (fără parametri, cu parametri și de copiere), operator=, destructor și metoda totalLocuriLibere();
- următorii operatori supraîncărcați:
  - += mărește tariful pe oră cu o valoare dată;
  - ! întoarce true dacă parcarea este gratuită (tariful este 0);
  - () (operatorul funcție) primește un număr de ore și întoarce costul staționării;
  - [] întoarce prin referință locurile libere de pe nivelul dat, deci valoarea se poate și modifica. Pentru un nivel inexistent aruncă excepție;
  - < compară două parcări după totalul locurilor libere;
  - ++ în ambele forme, pre și post incrementare, mărește tariful cu 1 leu;
  - cast explicit la int, care întoarce totalul locurilor libere;
  - << și >>, ca funcții friend, pentru afișare și citire.

În main folosește fiecare operator cel puțin o dată și arată prin afișări diferența dintre p++ și ++p.
*/

#include<iostream>
#include<string>
using namespace std;

enum TipParcare { SUPRATERANA = 1, SUBTERANA = 2 };

class Parcare {
private:
    const int id;
    string nume;
    float tarifOra;
    TipParcare tip;
    int nrNiveluri;
    int* locuriLibere;
public:
    static int nrParcari;

    Parcare() : id(++nrParcari) {
        this->nume = "Fara nume";
        this->tarifOra = 0;
        this->tip = SUPRATERANA;
        this->nrNiveluri = 0;
        this->locuriLibere = nullptr;
    }

    Parcare(int id, string nume, float tarif, TipParcare tip, int nrNiveluri, int* locuri) : id(id) {
        this->nume = nume;
        this->tarifOra = tarif;
        this->tip = tip;
        this->nrNiveluri = nrNiveluri;
        this->locuriLibere = new int[nrNiveluri];
        for (int i = 0; i < nrNiveluri; i++)
            this->locuriLibere[i] = locuri[i];
        nrParcari++;
    }

    Parcare(const Parcare& p) : id(++nrParcari) {
        this->nume = p.nume;
        this->tarifOra = p.tarifOra;
        this->tip = p.tip;
        this->nrNiveluri = p.nrNiveluri;
        if (p.locuriLibere != nullptr) {
            this->locuriLibere = new int[p.nrNiveluri];
            for (int i = 0; i < p.nrNiveluri; i++)
                this->locuriLibere[i] = p.locuriLibere[i];
        }
        else this->locuriLibere = nullptr;
    }

    Parcare& operator=(const Parcare& p) {
        if (this == &p) return *this;
        this->nume = p.nume;
        this->tarifOra = p.tarifOra;
        this->tip = p.tip;
        this->nrNiveluri = p.nrNiveluri;
        if (this->locuriLibere != nullptr) {
            delete[] this->locuriLibere;
            this->locuriLibere = nullptr;
        }
        if (p.locuriLibere != nullptr) {
            this->locuriLibere = new int[p.nrNiveluri];
            for (int i = 0; i < p.nrNiveluri; i++)
                this->locuriLibere[i] = p.locuriLibere[i];
        }
        return *this;
    }

    ~Parcare() {
        if (this->locuriLibere != nullptr)
            delete[] this->locuriLibere;
    }

    int totalLocuriLibere() const {
        int total = 0;
        for (int i = 0; i < this->nrNiveluri; i++)
            total += this->locuriLibere[i];
        return total;
    }

    // += : scumpeste parcarea
    void operator+=(float valoare) {
        this->tarifOra += valoare;
    }

    // ! : este gratuita?
    bool operator!() {
        return this->tarifOra == 0;
    }

    // operator functie: cost pentru un numar de ore
    float operator()(int ore) {
        return this->tarifOra * ore;
    }

    // operator index: returneaza referinta -> se poate modifica
    int& operator[](int nivel) {
        if (nivel >= 0 && nivel < this->nrNiveluri)
            return this->locuriLibere[nivel];
        throw exception();
    }

    bool operator<(const Parcare& p) const {
        return this->totalLocuriLibere() < p.totalLocuriLibere();
    }

    // post-incrementare: p++ -> intoarce starea VECHE
    Parcare operator++(int) {
        Parcare copie = *this;
        this->tarifOra++;
        return copie;
    }

    // pre-incrementare: ++p -> intoarce starea NOUA
    Parcare& operator++() {
        this->tarifOra++;
        return *this;
    }

    // cast explicit la int
    explicit operator int() {
        return this->totalLocuriLibere();
    }

    friend ostream& operator<<(ostream& out, const Parcare& p);
    friend istream& operator>>(istream& in, Parcare& p);
};

int Parcare::nrParcari = 0;

ostream& operator<<(ostream& out, const Parcare& p) {
    out << endl << "Id: " << p.id;
    out << endl << "Nume: " << p.nume;
    out << endl << "Tarif: " << p.tarifOra << " lei/ora";
    out << endl << "Tip: " << (p.tip == SUBTERANA ? "SUBTERANA" : "SUPRATERANA");
    out << endl << "Niveluri: " << p.nrNiveluri;
    if (p.locuriLibere != nullptr && p.nrNiveluri > 0) {
        out << endl << "Locuri libere pe niveluri: ";
        for (int i = 0; i < p.nrNiveluri - 1; i++)
            out << p.locuriLibere[i] << ", ";
        out << p.locuriLibere[p.nrNiveluri - 1] << ".";
        out << endl << "Total libere: " << p.totalLocuriLibere();
    }
    out << endl;
    return out;
}

istream& operator>>(istream& in, Parcare& p) {
    cout << "Nume: ";
    in >> p.nume;
    cout << "Tarif pe ora: ";
    in >> p.tarifOra;
    cout << "Tip (1 - supraterana, 2 - subterana): ";
    int t;
    in >> t;
    p.tip = (t == 2) ? SUBTERANA : SUPRATERANA;
    cout << "Nr niveluri: ";
    in >> p.nrNiveluri;

    if (p.locuriLibere != nullptr) {
        delete[] p.locuriLibere;
        p.locuriLibere = nullptr;
    }
    if (p.nrNiveluri > 0) {
        p.locuriLibere = new int[p.nrNiveluri];
        for (int i = 0; i < p.nrNiveluri; i++) {
            cout << "Locuri libere nivel " << i << ": ";
            in >> p.locuriLibere[i];
        }
    }
    return in;
}

int main() {
    Parcare p1;
    // cin >> p1;   // decomenteaza ca sa testezi citirea

    if (!p1) cout << endl << "Parcarea p1 este gratuita!";

    p1 += 5;                                  // operator+=
    if (!p1) cout << endl << "Gratuita!";
    else     cout << endl << "Parcarea p1 costa acum " << p1(1) << " lei/ora";

    cout << endl << "Cost pentru 3 ore: " << p1(3) << " lei";   // operator()

    cout << p1;                               // operator<<

    Parcare vechi = p1++;                     // post: vechi are tariful 5, p1 are 6
    cout << endl << "--- dupa p1++ ---";
    cout << vechi << p1;

    Parcare nou = ++p1;                       // pre: si nou si p1 au tariful 7
    cout << endl << "--- dupa ++p1 ---";
    cout << nou << p1;

    int* locuri = new int[3] {40, 25, 10};
    Parcare* pCentru = new Parcare(50, "Unirii", 8, SUBTERANA, 3, locuri);
    delete[] locuri;
    cout << *pCentru;

    (*pCentru)[2] = 0;                        // operator[] cu referinta
    cout << endl << "Nivelul 2 e acum plin: " << (*pCentru)[2] << " locuri";

    try {
        cout << (*pCentru)[7];
    }
    catch (exception&) {
        cout << endl << "Nivel inexistent!";
    }

    if (p1 < *pCentru)                        // operator<
        cout << endl << "Parcarea p1 are mai putine locuri libere.";
    else
        cout << endl << "Parcarea Unirii are mai putine locuri libere.";

    int total = (int)(*pCentru);              // cast explicit
    cout << endl << "Locuri libere in Unirii (cast la int): " << total;

    cout << endl << "Am creat " << Parcare::nrParcari << " parcari!";

    delete pCentru;
    return 0;
}
