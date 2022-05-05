/************************************************
    Egyszerű LL(1) elemző megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>

using namespace std;

void LL_1(string word, string s)
{
    int numberOfRules = 4;
    int numberOfTerminals = 4;

    string G[numberOfRules][3] = {{"S", "aS", "1"},
                                  {"S", "bAc", "2"},
                                  {"A", "bAc", "3"},
                                  {"A", "d", "4"}};

    char letters[numberOfTerminals] = {'a', 'b', 'c', 'd'};
    
    

    bool isTerminal = false;
    bool isRule = false;

    // cout << "----------------------" << endl;
    // cout << "Szó állapota: " << word << endl;
    // cout << "Levezetési lépés: " << s << endl;
    // cout << "----------------------" << endl << endl;
    for (int i = 0; i < numberOfTerminals; i++)
    {
        if (s[0] == letters[i])
        {
            isTerminal = true;
        }
    }
    
    for (int i = 0; i < numberOfRules; i++)
    {
        if (G[i][0] == string(1, s[0]) && G[i][1][0] == word[0])
        {
            
            s = regex_replace(s, regex(string(1, s[0])), G[i][1]);
            cout << G[i][2] << " => ";
            isRule = true;
        }
    }

    if (isTerminal)
    {
        LL_1(word.erase(0, 1), s.erase(0, 1));
    }
    else if (isRule)
    {
        LL_1(word, s);
    }
    else
    {
        if (word.empty() && s.empty())
        {
            cout << "A szó elem a nyelvnek." << endl;
            
            return;
        }
        else
        {
            cout << "A szó nem elem a nyelvnek." << endl;
            return;
        }
    }
}

int main()
{
    int index = 0;
    string input;
    string start = "S";

    cout << "Nyelvtan" << endl
         << endl;
    cout << "1. S -> aS" << endl;
    cout << "2. S -> bAc" << endl;
    cout << "3. A -> bAc" << endl;
    cout << "4. A -> d" << endl
         << endl;

    cout << "Terminalisok: a, b, c, d" << endl
         << endl;
    cout << "exit-el kilépés" << endl
         << endl;

    while (input != "exit")
    {

        cout << "Adja meg a szót(pl: aabbdcc):  ";
        cin >> input;

        if (input != "exit")
        {
            LL_1(input, start);
        }
    }
    return 0;
}