/*

Autores: Josep Lopez y Roger De Moreta

Ultima practica de Algorismia, implementada con RBST's

*/


#include "RBST.h"
#include <map>

const int INIT = 1;const int INS = 2;
const int DEL = 3;const int CONT = 4;
const int MERGE = 5;const int CARD = 6;
const int NTH = 7;const int LEQ = 8;
const int GT = 9;const int BETWEEN = 10;
const int MIN = 11;const int MAX = 12;
const int ALL = 13;


/* Funcion auxiliar que se usa para que el switch 
siga trabajando con enteros mientras lee strings 
como comando por la entrada */

map<string,int> getSwitchMap() 
{
    map<string,int> m;
    m["init"] = INIT;
    m["ins"] = INS;
    m["del"] = DEL;
    m["cont"] = CONT;
    m["merge"] = MERGE;
    m["card"] = CARD;
    m["nth"] = NTH;
    m["leq"] = LEQ;
    m["gt"] = GT;
    m["between"] = BETWEEN;
    m["min"] = MIN;
    m["max"] = MAX;
    m["all"] = ALL;
    m["impr"] = 14;  //Este lo usamos para hacer pruebas.
    m["alt"] = 15;   //Este tambien.
    return m;
}

int main() {

    map<string,int> switchmap = getSwitchMap();

    srand (time(NULL));
    
    string arbre, arbre2, element2, element;
    int command_num;
    string command;
    map<string,RBST> arbres;
    while (cin >> command) 
    {
        command_num = switchmap[command];
        cin >> arbre;
        cout << "> " << command << " " << arbre;

        switch ( command_num ) 
        {
            case INIT:
                cout << endl;
                arbres[arbre] = RBST();
                cout << "OK" << endl;
            break;

            case INS:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    if (!arbres[arbre].contains(element))
                    {
                        arbres[arbre].insert(element);
                    }
                    cout << "OK" << endl;
                }
            break;
            case DEL:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    if (arbres[arbre].contains(element))
                    {
                        arbres[arbre].deleteN(element);
                    }
                    cout << "OK" << endl;
                }
            break;

            case CONT:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    if (arbres[arbre].contains(element))
                        cout << "true";
                    else cout << "false";
                    cout << endl;
                    
                }
            break;

            case MERGE:
                cin >> arbre2;
                cout << " " << arbre2 << endl;

                if(arbres.find(arbre) == arbres.end() || arbres.find(arbre2) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    arbres[arbre].merge(arbres[arbre2]);
                    cout << "OK" << endl;
                }

            break;

            case CARD:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    cout << arbres[arbre].getSize() << endl;
                }
                
            break;

            case NTH:
                int number;
                cin >> number;
                cout << " " << number << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else if (number < 1 || number > arbres[arbre].getSize())
                    cout << "ERROR";

                else
                {
                    cout << arbres[arbre].nth(number) << endl;
                }

            break;

            case LEQ:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    cout << arbres[arbre].leq(element) << endl;
                }

            break;

            case GT:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    cout << arbres[arbre].gt(element) << endl;
                }
                
            break;

            case BETWEEN:
                cin >> element >> element2;
                cout << " " << element << " " << element2 << endl;


                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;
                else
                {
                    arbres[arbre].between(element,element2);
                }

            break;

            case MIN:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    if (arbres[arbre].getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << arbres[arbre].treeMin() << endl;
                    }
                }
            break;

            case MAX:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    if (arbres[arbre].getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << arbres[arbre].treeMax() << endl;
                    }
                }
                
            break;

            case ALL:
                cout << endl;
                arbres[arbre].inOrdre();
            break;

            case 14: //impr
                cout << " IMPR" << endl;
                arbres[arbre].imprimir();
            break;

            case 15: //alturas
                cout << " ALT" << endl;
                arbres[arbre].altura();
            break;
        }
    }
}