/*O firmă de IT gestionează salariile angajaților. Implementează:
- o clasă ExceptieSalariu, derivată din exception, care primește un mesaj și îl întoarce prin what();
- o clasă abstractă Angajat cu membri protected: un id constant, numele și salariul de bază. Clasa are:
  - o constantă static const SALARIU_MINIM (4050 lei). Constructorul cu parametri aruncă ExceptieSalariu dacă salariul este sub acest minim;
  - o metodă virtual afisare();
  - o metodă virtuală pură calculeazaBonus();
  - un destructor virtual;
- două clase derivate, fiecare cu un constructor care apelează constructorul clasei de bază, o variantă proprie a lui afisare() (care apelează și Angajat::afisare()) și propria formulă pentru bonus:
  - Programator, cu numărul de proiecte livrate (bonus: 500 lei pe proiect);
  - Manager, cu numărul de subordonați (bonus: 10% din salariu, plus 200 lei pe subordonat);
- o interfață IConvertor cu metodele pur virtuale leiInEuro(float) și euroInLei(float), implementată de clasa ConvertorBNR.

În main:
1. Testează excepția cu un angajat care are salariul prea mic.
2. Construiește un vector de pointeri Angajat* cu angajați de ambele tipuri și afișează-i polimorfic. Afișează și bonusul total.
3. Convertește bonusul total în euro printr-un pointer IConvertor*.
*/

#include<iostream>
#include<string>
using namespace std;

class ExceptieSalariu : public exception {
private:
    string mesaj;
public:
    ExceptieSalariu(const char* mesaj) : mesaj(mesaj) {}
    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

// clasa abstracta
class Angajat {
protected:
    const int id;
    string nume;
    float salariuBaza;
public:
    static const float SALARIU_MINIM;

    Angajat() : id(0), nume("Anonim"), salariuBaza(SALARIU_MINIM) {}

    Angajat(int id, string nume, float salariu) : id(id), nume(nume), salariuBaza(salariu) {
        if (salariu < SALARIU_MINIM)
            throw ExceptieSalariu("Salariul este sub minimul pe economie!");
    }

    virtual void afisare() {
        cout << endl << "Id: " << this->id;
        cout << endl << "Nume: " << this->nume;
        cout << endl << "Salariu baza: " << this->salariuBaza << " lei";
    }

    virtual float calculeazaBonus() = 0;   // virtuala pura

    virtual ~Angajat() {}                 // virtual -> delete prin Angajat* e corect
};

const float Angajat::SALARIU_MINIM = 4050;

class Programator : public Angajat {
private:
    int nrProiecte;
public:
    Programator() : Angajat() {
        this->nrProiecte = 0;
    }

    Programator(int id, string nume, float salariu, int nrProiecte)
        : Angajat(id, nume, salariu) {
        this->nrProiecte = nrProiecte;
    }

    void afisare() override {
        this->Angajat::afisare();
        cout << endl << "Rol: Programator";
        cout << endl << "Proiecte livrate: " << this->nrProiecte;
        cout << endl << "Bonus: " << this->calculeazaBonus() << " lei" << endl;
    }

    float calculeazaBonus() override {
        return this->nrProiecte * 500.0f;
    }
};

class Manager : public Angajat {
private:
    int nrSubordonati;
public:
    Manager() : Angajat() {
        this->nrSubordonati = 0;
    }

    Manager(int id, string nume, float salariu, int nrSubordonati)
        : Angajat(id, nume, salariu) {
        this->nrSubordonati = nrSubordonati;
    }

    void afisare() override {
        this->Angajat::afisare();
        cout << endl << "Rol: Manager";
        cout << endl << "Subordonati: " << this->nrSubordonati;
        cout << endl << "Bonus: " << this->calculeazaBonus() << " lei" << endl;
    }

    float calculeazaBonus() override {
        return this->salariuBaza * 0.1f + this->nrSubordonati * 200;
    }
};

// interfata = clasa doar cu metode virtuale pure
class IConvertor {
public:
    virtual float leiInEuro(float lei) = 0;
    virtual float euroInLei(float euro) = 0;
    virtual ~IConvertor() {}
};

class ConvertorBNR : public IConvertor {
private:
    float curs;
public:
    ConvertorBNR(float curs) : curs(curs) {}

    float leiInEuro(float lei) override { return lei / curs; }
    float euroInLei(float euro) override { return euro * curs; }
};

int main() {
    // 1. exceptie custom
    try {
        Programator stagiar(99, "Ionut", 2000, 1);
        stagiar.afisare();
    }
    catch (ExceptieSalariu& e) {
        cout << endl << "Eroare: " << e.what();
    }
    catch (exception& e) {
        cout << endl << "Alta eroare: " << e.what();
    }
    cout << endl;

    // 2. polimorfism prin vector de pointeri la clasa de baza
    const int N = 4;
    Angajat* echipa[N];
    echipa[0] = new Programator(1, "Ana", 9000, 3);
    echipa[1] = new Programator(2, "Mihai", 7500, 1);
    echipa[2] = new Manager(3, "Elena", 15000, 6);
    echipa[3] = new Programator();     // constructorul implicit

    float bonusTotal = 0;
    for (int i = 0; i < N; i++) {
        echipa[i]->afisare();          // se apeleaza versiunea din clasa derivata
        bonusTotal += echipa[i]->calculeazaBonus();
    }
    cout << endl << "Bonus total: " << bonusTotal << " lei";

    for (int i = 0; i < N; i++)
        delete echipa[i];

    // 3. interfata
    IConvertor* conv = new ConvertorBNR(4.97f);
    cout << endl << "Bonus total in euro: " << conv->leiInEuro(bonusTotal);
    cout << endl << "100 euro = " << conv->euroInLei(100) << " lei";
    delete conv;

    return 0;
}
