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
    m["impr"] = 100;
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
        string arbre, arbre2, element, element2;
        RBST aux,aux2,nou;
        cin >> arbre;
        cout << "> " << command << " " << arbre;

        switch ( command_num ) 
        {
            case INIT:
                cout << endl;
                arbres[arbre] = nou;
                cout << "OK" << endl;
            break;

            case INS:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (!aux.contains(element))
                    {
                        aux.insert(element);
                        arbres[arbre] = aux;
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
                    aux = arbres[arbre];
                    if (aux.contains(element))
                    {
                        aux.deleteN(element);
                        arbres[arbre] = aux;
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
                    aux = arbres[arbre];
                    if (aux.contains(element))
                        cout << "true";
                    else cout << "false";
                    cout << endl;
                    
                }
            break;

            case MERGE:
                cin >> arbre2;
                cout << " " << arbre2 << endl;

                // cout << "arbre1 es: " << arbre << " arbre2 es: " << arbre2 << endl;
                if(arbres.find(arbre) == arbres.end() || arbres.find(arbre2) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    aux2 = arbres[arbre2];
                    aux.merge(aux2);
                    aux2 = nou;
                    arbres[arbre] = aux;
                    arbres[arbre2] = aux2;
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

                cin >> number;
                cout << " " << number << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

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
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.leq(element) << endl;
                }

            break;

            case GT:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.gt(element) << endl;
                }
                
            break;

            case BETWEEN:
                cin >> element >> element2;
                cout << " " << element << " " << element2 << endl;


                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;
                else
                {
                    aux = arbres[arbre];
                    aux.between(element,element2);
                }

            break;

            case MIN:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << aux.treeMin() << endl;
                    }
                }
            break;

            case MAX:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << aux.treeMax() << endl;
                    }
                }
                
            break;

            case ALL:
                cout << endl;
                arbres[arbre].inOrdre();
            break;
        }
    }
}