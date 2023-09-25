#include <iostream>

using namespace std;

struct lista
{
  lista * next;
  char znaczek;
};

struct Rekord{
    //lista *biezacy;
    lista *head;
    lista *tail;
};

Rekord *zeruj(char index1, struct Rekord **tablicaRekordow);
void    wypisz(char index1, struct Rekord **tablicaRekordow);
Rekord *odwroc(char index1,struct Rekord**tablicaRekordow);
Rekord *ustaw(char index1, struct Rekord **tablicaRekordow, char *napis);
Rekord *usun(int ile, char index1, struct Rekord **tablicaRekordow);
Rekord *przesun(int ile, char index1,struct Rekord **tablicaRekordow);
Rekord *doklej(char index1, char index2, struct Rekord **tablicaRekordow);
Rekord *skopiuj(char index1, char index2, struct Rekord **tablicaRekordow);
Rekord  *mieszaj(char index1, char index2, struct Rekord **tablicaRekordow);

/********************************************************************************************************************************************************/
int main()
{
//tworze tablica 26 wskaznikow do struktur/rekordow i wsytawiam do nich puste wskazniki

    struct Rekord *tablicaRekordow[26];
    for (int i=0; i < 26 ; i++){
            tablicaRekordow[i] = new Rekord;
            tablicaRekordow[i]->tail = nullptr;
            tablicaRekordow[i]->head = nullptr;
    }
//ZMIENNE STATYCZNE
    char index1;
    char index2;
    int ile;
    char polecenie[15];
    char napis[700000];


//  GLOWNA PETLA WCZYTYWANIA

    while (cin >> polecenie) {
        switch(polecenie[0]) {

                case 'U':
//USUN
                    if (polecenie[2] == 'U'){
                        cin >> index1 >> ile;
                        index1 = (index1 - 'A');                                                   //zamien znak od A do Z na numer indeksu
                        tablicaRekordow[index1] = usun(ile, index1, tablicaRekordow);             //w wybrany rekord podstaw wynik funkcji
                     }
//USTAW
                    if (polecenie[2] == 'T'){
                        cin >> index1 >> napis;
                        index1 = (index1 - 'A');
                        tablicaRekordow[index1] = ustaw( index1, tablicaRekordow, napis);       //w wybrany rekord podstaw wynik funkcji
                    }
                    break;
//ZERUJ
                 case 'Z':
                            cin >> index1;
                            index1 = (index1 - 'A');
                            tablicaRekordow[index1] = zeruj(index1, tablicaRekordow);
                    break;
//ODWROC
                 case 'O':
                            cin >> index1;
                            index1 = (index1 - 'A');
                            tablicaRekordow[index1] = odwroc(index1, tablicaRekordow);
                    break;
//WYPISZ
                case 'W':
                            cin >> index1;
                            index1 = (index1 - 'A');
                            wypisz(index1, tablicaRekordow);
                    break;
//PRZESUN
                 case 'P':
                            cin >> index1 >> ile;
                            index1 = (index1 - 'A');
                            tablicaRekordow[index1] = przesun(ile, index1, tablicaRekordow);
                    break;
//DOKLEJ
                case 'D':
                            cin >> index1 >> index2;
                            index1 = (index1 - 'A');
                            index2 = (index2 - 'A');
                            tablicaRekordow[index1] = doklej(index1, index2, tablicaRekordow);
                    break;
//SKOPIUJ
                 case 'S':
                           cin >> index1 >> index2;
                           index1 = (index1 - 'A');
                           index2 = (index2 - 'A');
                           tablicaRekordow[index1] = skopiuj(index1, index2, tablicaRekordow);                           
                    break;
//MIESZAJ
                case 'M':
                           cin>>index1>>index2;
                           index1=(index1 -'A');
                           index2=(index2 -'A');
                           tablicaRekordow[index1] = mieszaj(index1, index2, tablicaRekordow);                          
                    break;
            }
        }
     for (int i=0; i < 26 ; i++){                                        //zwolnij cala pamiec
            tablicaRekordow[i] = zeruj(i, tablicaRekordow);
            delete tablicaRekordow[i];        }

    return 0;
}           //KONIEC MAINA

/**********************************************************************************************************************/
Rekord *ustaw(char index1, struct Rekord **tablicaRekordow, char *napis)
{

    lista *pierwszyE;
    lista *tempH=nullptr;
    lista *biezacy=nullptr;

    int rozmiar=0;
    while(napis[rozmiar++] != '\0') {};                                                 //zliczam rozmiar wczytanego ciagu znakow - tekstu (zwiekszaj o 1 rozmiar dopoki nie bedzie '\0';
    rozmiar = rozmiar - 2;                                                                  //ustawiam rozmiar na o 2 mniejszy po petli, czyli na ostatni znak przed '\0'

 //TWORZE PIERWSZY ELEMENT PRZYSZLEJ LISTY CYKLICZNEJ
    pierwszyE = new lista;
    pierwszyE->next = pierwszyE;
    pierwszyE->znaczek = napis[rozmiar];                                                //ostatni znak wisujemy do pierwszej glowy
    rozmiar--;                                                                          //po czym zmniejszamy rozmiar by wiedziec ile znakow pozostalo do przepisania

 //PIERWSZY ELEMENT STAJE SIE BIEZACYM ELEMENTEM, JEST GLOWA I OGONEM REKORDU
    biezacy = pierwszyE;
    tablicaRekordow[index1]->head = pierwszyE;
    tablicaRekordow[index1]->tail = pierwszyE;


//DLA KOLEJNYCH ZNAKOW TEKSTU

    for (int j = rozmiar; j >= 0; j--){
        tempH = new lista;                  //tworz nowe elementy - tymczasowe glowy - tempH
        tempH->znaczek = napis[j];          //wpisuj do nich znaki
        tempH->next = biezacy->next;        //nastepnikiem tempH zostaje nastepnik Biezacego Elementu
        biezacy->next = tempH;                //nastepnikiem  Biezacego Elementu zostaje nowo utworzony element
    }
    //JAK WIECEJ NIZ JEDEN ZNAK (inaczej juz znamy heada)
    if (tempH != nullptr){
        biezacy = tempH;
        tablicaRekordow[index1]->head = tempH;
    }
    //ZWROC WSKAZNIK NA REKORD
    return tablicaRekordow[index1];
}
/**********************************************************************************************************************/
void wypisz(char index1, struct Rekord **tablicaRekordow)
{
    //PRZEJEDZ PO LISCIE CYKLICZNEJ OD GLOWY DO ELEMENTU PRZED GLOWA

    Rekord *temp1 = tablicaRekordow[index1];
    if (temp1->head != nullptr){                                    //wypisuj tylko gdy rekord nie zawiera pustego napisu
        lista *temp2 = tablicaRekordow[index1]->head;
        do
        {
            cout << temp2->znaczek;
            temp2 = temp2->next;
        }
        while (temp2 != tablicaRekordow[index1]->head);
    }
    cout << "\n";
}
/**********************************************************************************************************************/
Rekord *usun(int ile, char index1, struct Rekord **tablicaRekordow)
{
    if (tablicaRekordow[index1]->head != nullptr){
        lista *nastepnik = nullptr;

        lista *biezacy = tablicaRekordow[index1]->head;                 //zapamietaj heada w biezacym
        //tablicaRekordow[index1]->head = nullptr;                        //ustaw heada na nullptr;

        for (int z=0; z<ile ; z++){                                     //petla kasujaca
            if ( biezacy != tablicaRekordow[index1]->tail){             //kasuj "ile" elementow, dopoki biezacy jest rozny od ogona i ustawiaj biezacy na nastepnik
                  nastepnik = biezacy->next;
                  delete biezacy;
                  biezacy = nastepnik;
            }
            else  {                                                     //na koniec jesli dotarles do ogona to skasuj ogon
                delete biezacy;
                biezacy = nullptr;
                tablicaRekordow[index1]->tail = nullptr;
                break;
            }
        }
        tablicaRekordow[index1]->head = biezacy;                                                                 //ustaw heada na biezacy;
        if (tablicaRekordow[index1]->tail != nullptr) 
                tablicaRekordow[index1]->tail->next = tablicaRekordow[index1]->head;                         //ustaw tail next na heada by dalej byl to rekord zawierajacy liste cykliczna;
    }
return tablicaRekordow[index1];
}
/***********************************************************************************************************************/
Rekord *zeruj(char index1, struct Rekord **tablicaRekordow)
{
    if (tablicaRekordow[index1]->head != nullptr){
            lista *biezacy = tablicaRekordow[index1]->head;
            lista *doUsuniecia;
            while (biezacy->next != tablicaRekordow[index1]->head) {        //kasuje wszystkie elementy (lacznie z headem)
                doUsuniecia = biezacy;
                biezacy = biezacy->next;
                delete doUsuniecia;
            }
            biezacy = nullptr;
            tablicaRekordow[index1]->head = nullptr;
            tablicaRekordow[index1]->tail = nullptr;
    }
return tablicaRekordow[index1];
}
/************************************************************************************************************************/
Rekord *przesun(int ile, char index1,struct Rekord **tablicaRekordow)
{
    if (tablicaRekordow[index1]->head != nullptr){
        for (int i = 0; i < ile; i++){
            tablicaRekordow[index1]->tail = tablicaRekordow[index1]->tail->next;            //najpierw przesun ogon
            tablicaRekordow[index1]->head = tablicaRekordow[index1]->head->next;            //potem heada
        }
    }
return tablicaRekordow[index1];
}
/***************************************************************************************************************************/
Rekord *doklej(char index1, char index2, struct Rekord **tablicaRekordow)
{
    if ((tablicaRekordow[index1]->head != nullptr) && (tablicaRekordow[index2]->head != nullptr)) {             //oba rekordy nie sa puste
        tablicaRekordow[index2]->tail->next  =  tablicaRekordow[index1]->head;
        tablicaRekordow[index1]->tail->next  =  tablicaRekordow[index2]->head;
        tablicaRekordow[index1]->tail        =  tablicaRekordow[index2]->tail;
        tablicaRekordow[index2]->tail = nullptr;                              //"zeruje" rekord o drugim indeksie - jego stare elementy naleza teraz do pierwszego rekordu
        tablicaRekordow[index2]->head = nullptr;
        lista *biezacy;
        biezacy = nullptr;
    }
    if ((tablicaRekordow[index1]->head == nullptr) && (tablicaRekordow[index2]->head != nullptr)){               //drugi rekord nie jest pusty a pierwszy jest
            tablicaRekordow[index1]->head = tablicaRekordow[index2]->head;
            tablicaRekordow[index1]->tail = tablicaRekordow[index2]->tail;
            tablicaRekordow[index2]->tail = nullptr;                              //"zeruje" rekord o drugim indeksie - jego stare elementy naleza teraz do pierwszego rekordu
            tablicaRekordow[index2]->head = nullptr;
    }

return tablicaRekordow[index1];

}
/******************************************************************************************************************************/
Rekord *skopiuj(char index1, char index2, struct Rekord **tablicaRekordow){
     if (tablicaRekordow[index2]->head != nullptr){                          //gdy jest co kopiowac

            lista* nowy;
            lista* biezacy2 = tablicaRekordow[index2]->head;
            lista* temp;

            if (tablicaRekordow[index1]->head == nullptr)                   //gdy rekord o 1 indexie zawiera pusty napis
            {
            //TWORZE JEDEN TYMCZASOWY NOWY OBIEKT
                temp = new lista;
                temp->next                      = temp;
                tablicaRekordow[index1]->head   = temp;
                tablicaRekordow[index1]->tail   = temp;

                //GDY JEST TYLKO JEDEN ELEMENT W DRUGIM REKORDZIE
                if (biezacy2   ==   biezacy2->next)
                        tablicaRekordow[index1]->head->znaczek  =  biezacy2->znaczek;               //od razu skopiuj znaczek

                //GDY W DRUGIM REKORDZIE JEST KILKA ELEMENTOW
                if (biezacy2   !=   biezacy2->next)
                {
                       do {                                                                         //Tworz nowe biekty i do nich kopiuj znaczki
                            nowy = new lista;
                            nowy->znaczek = biezacy2->znaczek;
                            tablicaRekordow[index1]->tail->next = nowy;                             //nastepnikiem ogona staje sie nowy
                            tablicaRekordow[index1]->tail = nowy;                                     //ustaw ogon jako nowy
                            biezacy2 = biezacy2->next;                                                //przeskocz dalej
                            }
                        while (biezacy2   !=   tablicaRekordow[index2]->head);                      //dopoki nie dojdziesz do glowy
                        //PO SKOPIOWANIU
                        lista *doUsuniecia = tablicaRekordow[index1]->head;
                        tablicaRekordow[index1]->tail->next   =   tablicaRekordow[index1]->head->next;    //na koniec zapetl liste jako cykliczna
                        tablicaRekordow[index1]->head = tablicaRekordow[index1]->head->next;
                        delete doUsuniecia;                                                             //zwolnij pamiec usuwajac TYMCZASOWY OBIEKT
                }
            }

            else {                                                                              //gdy rekord o 1 indexie nie zawiera pustego napisu
                biezacy2 = tablicaRekordow[index2]->head;
                do {
                    nowy = new lista;
                    nowy->znaczek = biezacy2->znaczek;
                    tablicaRekordow[index1]->tail->next = nowy;
                    tablicaRekordow[index1]->tail = nowy;
                    biezacy2 = biezacy2->next;
                    }
                while (biezacy2   !=   tablicaRekordow[index2]->head);
                tablicaRekordow[index1]->tail->next = tablicaRekordow[index1]->head;
            }
        }
return tablicaRekordow[index1];

}
/************************************************************************************************************************************/
Rekord  *mieszaj(char index1, char index2, struct Rekord **tablicaRekordow)
{
    lista *biezacy1 = tablicaRekordow[index1]->head;
    lista *biezacy2 = tablicaRekordow[index2]->head;

    if (    (tablicaRekordow[index1]->head != nullptr) && (tablicaRekordow[index2]->head != nullptr)  )  {          //mieszaj gdy masz co mieszac
        lista *temp = tablicaRekordow[index1]->head;
        tablicaRekordow[index1]->tail->next = nullptr;
        tablicaRekordow[index2]->tail->next = nullptr;
        biezacy1 = tablicaRekordow[index1]->head->next;
        biezacy2 = tablicaRekordow[index2]->head;

        while ((biezacy1 != nullptr) && (biezacy2 != nullptr)){         //najpierw mieszaj gdy zaden sie nie skonczyl jeszcze
            temp->next = biezacy2;
            biezacy2 = biezacy2->next;
            temp = temp->next;
            temp->next = biezacy1;
            biezacy1 = biezacy1->next;
            temp = temp->next;
        }
        if (biezacy1 == nullptr){                                       //gdy skonczy sie najpierw pierwszy
            while (biezacy2 != nullptr)
            {
                temp->next = biezacy2;
                biezacy2 = biezacy2->next;
                temp = temp->next;
            }
            tablicaRekordow[index1]->tail = temp;
            temp->next = tablicaRekordow[index1]->head;
        }
        else if (biezacy2 == nullptr){                                  //gdy skonczy sie najpierw drugi
            while (biezacy1 != nullptr)
                {
                temp->next = biezacy1;
                biezacy1 = biezacy1->next;
                temp = temp->next;
            }
            tablicaRekordow[index1]->tail = temp;
            temp->next = tablicaRekordow[index1]->head;
        }
        tablicaRekordow[index2]->head = nullptr;                        //"zeruj" drugi rekord
        tablicaRekordow[index2]->tail = nullptr;
        biezacy2 = nullptr;
    }
    if ( (tablicaRekordow[index1]->head == nullptr) && (tablicaRekordow[index2]->head != nullptr)  )  {                  //gdy 1 rekord pusty to zamiast mieszaj robi sie doklej
        tablicaRekordow[index1] = doklej(index1, index2, tablicaRekordow);
    }

    return tablicaRekordow[index1];
}
/************************************************************************************/
Rekord *odwroc(char index1, struct Rekord**tablicaRekordow)
{
  lista *temp, *pomoc, *zapamietajHeada;
  zapamietajHeada = tablicaRekordow[index1]->head;

  if(tablicaRekordow[index1]->head != nullptr){             //odwracaj gdy jest co odwracac
      tablicaRekordow[index1]->tail->next = nullptr;        //nie cykliczna od teraz
      pomoc = tablicaRekordow[index1]->head;                //uzyj pomocnika

      while  (pomoc->next != nullptr)                                             //od glowy do ogona
      {
          temp = pomoc->next;                                                       //rozrysuj by wytlumaczyc
          pomoc->next = temp->next;
          temp->next = tablicaRekordow[index1]->head;
          tablicaRekordow[index1]->head = temp;
      }
      tablicaRekordow[index1]->tail = zapamietajHeada;                                        //ustaw z powrotem jako cykliczna - uzyj zapamietanego poczatkowego heada
      tablicaRekordow[index1]->tail->next = tablicaRekordow[index1]->head;
    }
return tablicaRekordow[index1];
}
/************************************************************************************/
