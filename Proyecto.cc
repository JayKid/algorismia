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
                if(arbres.find(element) != arbres.end())
                {
                    aux = arbres[arbre];
                    if (!aux.contains(element))
                    {
                        aux.insert(element);
                        arbres[arbre] = aux;
                    }
                }
                else
                {
                    cout << "El conjunto no ha sido inicializado previamente" << endl;
                }
            break;
            case DEL:
                // cin >> element;
                // aux = arbres[arbre];
                // aux.deleteN(element);
                // arbres[arbre] = aux;
            break;

            case CONT:
                
            break;

            case MERGE:
                
            break;

            case CARD:
                
            break;

            case NTH:
                
            break;

            case LEQ:
                
            break;

            case GT:
                
            break;

            case BETWEEN:
                
            break;

            case MIN:
                
            break;

            case MAX:
                
            break;

            case ALL:
                arbres[arbre].inOrdre();                
            break;
        }
    }
}