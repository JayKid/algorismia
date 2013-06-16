#include "RBST.h"
#include <map>

const int INIT = 1;const int INS = 2;
const int DEL = 3;const int CONT = 4;
const int MERGE = 5;const int CARD = 6;
const int NTH = 7;const int LEQ = 8;
const int GT = 9;const int BETWEEN = 10;
const int MIN = 11;const int MAX = 12;
const int ALL = 13;

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
    return m;
}

int main() {

    map<string,int> switchmap = getSwitchMap();

    string command;
    map<string,RBST> arbres;
    while (cin >> command) 
    {
        int command_num = switchmap[command];
        int number;
        string arbre, element;
        RBST aux,nou;
        cin >> arbre;
        switch ( command_num ) 
        {
            case INIT:
                arbres[arbre] = nou;
            break;

            case INS:
                cin >> element;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (!aux.contains(element))
                    {
                        aux.insert(element);
                        arbres[arbre] = aux;
                    }
                }
            break;
            case DEL:
                cin >> element;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (!aux.contains(element))
                    {
                        aux.deleteN(element);
                        arbres[arbre] = aux;
                    }
                }
            break;

            case CONT:
                cin >> element;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.contains(element))
                        cout << "true";
                    else cout << "false";
                    cout << endl;
                    
                }
            break;

            case MERGE:
                
            break;

            case CARD:

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                    cout << arbres[arbre].getSize() << endl;
                
            break;

            case NTH:

                cin >> number;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else if (number < 1 || number > arbres[arbre].getSize())
                    cout << "ERROR";

                else
                {
                    aux = arbres[arbre];
                    cout << aux.nth(number) << endl;
                }

            break;

            case LEQ:
                cin >> element;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.leq(element) << endl;
                }

            break;

            case GT:
                cin >> element;

                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.gt(element) << endl;
                }
                
            break;

            case BETWEEN:
                
            break;

            case MIN:
                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                {
                    aux = arbres[arbre];
                    cout << aux.treeMin() << endl;
                }
            break;

            case MAX:
                if(arbres.find(arbre) == arbres.end())
                    cout << "El conjunto no ha sido inicializado previamente" << endl;

                else
                {
                    aux = arbres[arbre];
                    cout << aux.treeMax() << endl;
                }
                
            break;

            case ALL:
                arbres[arbre].inOrdre();                
            break;
        }
    }
}