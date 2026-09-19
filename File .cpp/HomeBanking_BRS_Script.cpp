//Questo script e' stato realizzato da Francesco Bivona. Il codice simula il funzionamento di una home banking con funzioni basiche.

#include <iostream> //Queste righe (da 3 a 6) sono le librerie che servono per il funzionamento del codice, come ad esempio i/o, stringhe ecc. 
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std; //Questa riga (8) serve per comodità, così per quasi ogni termine non bisogna scrivere std::example

#define fine "\033[0m"     //Queste righe (da 10 a 19) sono per colorare i cout
#define rosso "\033[31m"
#define verde "\033[32m"
#define giallo "\033[33m"
#define blu "\033[34m"
#define magenta "\033[35m"
#define bianco "\033[30m"
#define rosa_chiaro "\033[91m"
#define arancione "\033[38;5;208m"
#define rosa "\033[95m"

void login();                                                  //Queste righe (da 21 a 29) sono delle funzioni e procedure globali
void registrarsi();
void menu_1();
void menu_2(string &iban, double saldo_utente);
string genera_iban();
double saldo_utente();
void prelievo(double &saldo_utente);
void deposito(double &saldo_utente, double depositi[]);
void bonifico(double &saldo_utente, string iban_destinatario);

void login()                                           //Queste righe (da 31 a 49) è in complesso una procedura per il login; si potrebbe pensare un implementazione con database
{
    string email="", password="";                    

    cout<<""<<endl;

    cout<<rosso<<"Inserisca l'email: ";
    cin>>email;
    while(email.find("@")==string::npos||(email.find("gmail.com")==string::npos&&email.find("outlook.com")==string::npos&&email.find("yahoo.com")==string::npos))
    {
        cout<<"L'email non e' corretta, riprovi: ";
        cin>>email;
    }

    cout<<"Inserisca la password: ";
    cin>>password;

    cout<<"Login avvenuto con successo, sta entrando automaticamente in un menu' successivo per le operazioni"<<fine<<endl;
}

void registrarsi()                                                                          //Queste righe (da 51 a 97) è in complesso una procedura per registrarsi
{
    string nome="", cognome="", comune_di_nascita="", domicilio="", email="", password="";
    int giorno_di_nascita=0, mese_di_nascita=0, anno_di_nascita=0;

    cout<<""<<endl;

    cout<<verde<<"Inserisca il nome: ";
    cin>>nome;

    cout<<"Inserisca il cognome: ";
    cin>>cognome;

    cout<<"Inserisca il comune di nascita: ";
    cin>>comune_di_nascita;

    cout<<"Inserisca la data di nascita in formato GG MM AAAA: ";
    cin>>giorno_di_nascita>>mese_di_nascita>>anno_di_nascita;
    if(anno_di_nascita>=2007)
    {
        cout<<"Deve essere maggiorenne per registrarsi, riprovi: ";
        cin>>giorno_di_nascita>>mese_di_nascita>>anno_di_nascita;
    }

    cin.ignore(); 

    cout<<"Inserisca il domicilio: ";
    getline(cin, domicilio);

    cout<<"Inserisca l'email: ";
    cin>>email;
    while(email.find("@")==string::npos||(email.find("gmail.com")==string::npos&&email.find("outlook.com")==string::npos&&email.find("yahoo.com")==string::npos))
    {
        cout<<"L'email non e' corretta, riprovi: ";
        cin>>email;
    }

    cout<<"Inserisca la password: ";
    cin>>password;
    while(password.length()<8)
    {
        cout<<"La password deve essere lunga almeno 8 caratteri, riprovi: ";
        cin>>password;
    }

    cout<<"Registrazione avvenuta con successo, sta entrando automaticamente in un menu' successivo per le operazioni"<<fine<<endl;
}

void menu_1()                                              //Queste righe (da 99 a 137) è in complesso una procedura per il menù principale
{
    cout<<giallo<<"\033[1m";
    cout<<"Benvenuto nell'home banking BRS"<<endl;
    cout<<"\033[0m"<<fine;
    cout<<""<<endl;

    int scelta_1=0;
    string email_utente;
    do
    {
        cout<<giallo<<"Ecco cosa puo' fare:"<<endl;
        cout<<"1 per il login all'area personale"<<endl;
        cout<<"2 per registrarsi"<<endl;
        cout<<"3 per uscire"<<endl;
        cout<<"Scelga l'opzione desiderata: ";
        cin>>scelta_1;
        switch(scelta_1)
        {
            case 1:
            login();
            break;

            case 2:
            registrarsi();
            break;

            case 3:
            cout<<""<<endl;
            cout<<rosso<<"La stiamo reindirizzando all'uscita, grazie per aver utilizzato l'home banking BRS"<<fine<<endl;
            exit(0);
            break;

            default:
            cout<<"Errore nella scelta, riprovi"<<fine<<endl;
        }
    }
    while(scelta_1!=1&&scelta_1!=2&&scelta_1!=3);
}

void menu_2(string &iban, double saldo_utente, double depositi[])        //Queste righe (da 139 a 199) è in complesso una procedura per il menù successivo al principale
{
    int scelta_2=0;

    do
    {
        cout<<""<<endl;
        
        cout<<blu<<"Ecco le operazioni che puo' fare:"<<endl;
        cout<<"1 per visualizzare il suo IBAN"<<endl;
        cout<<"2 per controllare il saldo"<<endl;
        cout<<"3 per prelevare"<<endl;
        cout<<"4 per depositare"<<endl;
        cout<<"5 per fare un bonifico"<<endl;
        cout<<"6 per uscire"<<endl;
        cout<<"Scelga l'operazione desiderata: ";
        cin>>scelta_2;
        switch(scelta_2)
        {
            case 1:
            cout<<""<<endl;
            cout<<rosso<<"Ecco il suo IBAN: "<<iban<<fine<<endl;
            break;

            case 2:
            cout<<""<<endl;
            cout<<giallo<<"Il suo saldo e' di euro: "<<saldo_utente<<fine<<endl;
            break;

            case 3:
            prelievo(saldo_utente);
            break;

            case 4:
            deposito(saldo_utente, depositi);
            break;

            case 5:
            {
                string iban_destinatario;
                cout<<""<<endl;

                cout<<rosa_chiaro<<"Inserisci l'IBAN del destinatario: ";
                cin>>iban_destinatario;
                cout<<fine;
                bonifico(saldo_utente, iban_destinatario);
            }
            break;

            case 6:
            cout<<""<<endl;
            cout<<rosa<<"La stiamo reindirizzando all'uscita, grazie per aver utilizzato l'home banking BRS"<<fine<<endl;
            exit(0);
            break;

            default:
            cout<<"Errore nell'immissione, riprovi"<<fine<<endl;
        }
    }
    while(scelta_2!=6);
}

string genera_iban()                  //Queste righe (da 201 a 213) è in complesso una funzione che serve per generare l'IBAN
{
    string iban="IT";

    srand(time(NULL));

    for(int i=0;i<26;i++)
    {
        iban+=to_string(rand()%10);    
    }

    return iban;
}

double saldo_utente()                                  //Queste righe (da 215 a 222) è in complesso una funzione che serve per generare randomicamente il saldo dell'utente
{
    srand(static_cast<unsigned int>(time(nullptr)));

    double saldo_casuale=100+(rand()%9901);

    return saldo_casuale;
}

void prelievo(double &saldo_utente)                                               //Queste righe (da 224 a 262) è in complesso una procedura che serve per far funzionare la modalità prelievo
{
    double importo_prelievo=0;

    do
    {
        cout<<""<<endl;

        cout<<magenta<<"Inserisca l'importo da prelevare: ";
        cin>>importo_prelievo;

        if(importo_prelievo<=0)
        {
            cout<<"L'importo deve essere maggiore di 0, riprovi"<<endl;
        }
    }
    while(importo_prelievo<=0);

    if(saldo_utente>=importo_prelievo)
    {
        saldo_utente-=importo_prelievo;
        cout<<"Prelievo avvenuto con successo"<<endl;
        cout<<"Saldo rimanente: euro "<<saldo_utente<<endl;
    }
    else
    {
        do
        {
            cout<<"Saldo insufficiente per effettuare il prelievo, riprovi: ";
            cin>>importo_prelievo;
        }
        while(importo_prelievo>saldo_utente);

        saldo_utente-=importo_prelievo;

        cout<<"Prelievo avvenuto con successo"<<endl;
        cout<<"Saldo rimanente: euro "<<saldo_utente<<fine<<endl;
    }
}

void deposito(double &saldo_utente, double depositi[])                                              //Queste righe (da 264 a 289) è in complesso una procedura che serve per depositare i soldi nel proprio conto
{
    double importo_deposito=0;

    do
    {
        cout<<""<<endl;

        cout<<arancione<<"Inserisca l'importo da depositare: ";
        cin>>importo_deposito;
        if(importo_deposito<=0)
        {
            cout<<"L'importo deve essere maggiore di 0, riprovi"<<endl;
        }
        else if(importo_deposito>5000)
        {
            cout<<"L'importo massimo consentito per il deposito e' di 5000 euro, riprovi"<<endl;
        }
    }
    while(importo_deposito<=0||importo_deposito>5000);

    saldo_utente+=importo_deposito;
    
    cout<<"Deposito avvenuto con successo"<<endl;
    cout<<"Saldo disponibile: euro "<<saldo_utente<<fine<<endl;
}

void bonifico(double &saldo_utente, string iban_destinatario)                                                           //Queste righe (da 291 a 312) è in complesso una procedura che serve a fare bonifici ad altri IBAN
{
    double importo_bonifico=0;

    do
    {
        cout<<rosa_chiaro<<"Inserisca l'importo del bonifico: ";
        cin>>importo_bonifico;
        if(importo_bonifico<=0)
        {
            cout<<"L'importo del bonifico deve essere maggiore di 0, riprovi"<<endl;
        }
        else if(importo_bonifico>saldo_utente)
        {
            cout<<"Saldo insufficiente per effettuare il bonifico, ha disponibile: euro "<<saldo_utente<<", riprovi"<<endl;
        }
    }
    while(importo_bonifico<=0||importo_bonifico>saldo_utente);

    saldo_utente -= importo_bonifico;
    cout<<"Bonifico di euro "<<importo_bonifico<<" verso l'IBAN "<<iban_destinatario<<" avvenuto con successo, ha disponibile: euro "<<saldo_utente<<rosa_chiaro<<endl;
}

int main()                                             //Queste righe (da 314 a 325) è l'int main che richiama tutte le funzioni e procedure al fine di stamparle nel prompt
{
    menu_1();

    string iban_generato=genera_iban();
    double saldo_utente_m=saldo_utente();
    double depositi[100];

    menu_2(iban_generato, saldo_utente_m, depositi);
    
    return 0;
}
