/************************************************
    Lambdamentes LL(1) elemző megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>

using namespace std;


vector<vector<string>> table_maker(int numberOfRules, int numberOfTerminals, string G[][3], string terminals[])
{
    vector<vector<string>> table;
    vector<string> temp;

    for (int i = 0; i < numberOfTerminals; i++)
    {
        string srch = terminals[i];
        do
        {
            for (int j = 0; j < numberOfRules; j++)
            {
                if(srch == string(1, G[j][1][0]))
                {   
                    srch = G[j][0];
                    temp.push_back(G[j][0]);
                    temp.push_back(terminals[i]);
                    temp.push_back(G[j][1]);
                    temp.push_back(G[j][2]);
                }
            }
            table.push_back(temp);
            temp.clear();
        } while (srch != "S");
    }

    return table;
}


bool LL_1_without_lambda(vector<vector<string>> parsing_table, string input, string s, string &rules_used)
{
    while (input.length() != 0 && s.length() != 0)
    {
        if(input[0] == s[0])
        {
            input.erase(0, 1);
            s.erase(0, 1);
        }
        else
        {
            bool reject = true;
            for (auto &&i : parsing_table)
            {
                if(i[0] == string(1, s[0]) && i[1] == string(1, input[0]))
                {
                    s.replace(0, 1, i[2]);
                    rules_used.append(i[3]);
                    reject = false;
                }
            }
            if(reject)
            {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    cout << "Nyelvtan" << endl << endl;
    cout << "1. S -> aS" << endl;
    cout << "2. A -> bAc" << endl;
    cout << "3. A -> bAc" << endl;
    cout << "4. A -> bAc" << endl;
    cout << "5. B -> bAc" << endl;
    cout << "6. B -> bAc" << endl;
    cout << "7. C -> bAc" << endl;
    cout << "8. C -> bAc" << endl;
    cout << "9. D -> e" << endl << endl;

    cout << "Terminalisok: a, b, c, d, e" << endl << endl;

    cout << "exit-el kilépés" << endl << endl;

    int numberOfRules = 9;
    int numberOfTerminals = 5;

    string G[numberOfRules][3] = {{"S", "ABC", "1"},
                                  {"A", "a", "2"},
                                  {"A", "Bbc", "3"},
                                  {"A", "Ccd", "4"},
                                  {"B", "bBb", "5"},
                                  {"B", "cCc", "6"},
                                  {"C", "dDd", "7"},
                                  {"C", "Dd", "8"},
                                  {"D", "e", "9"},};

    string terminals[numberOfTerminals] = {"a", "b", "c", "d", "e"};

    vector<vector<string>> parsing_table = table_maker(numberOfRules, numberOfTerminals, G, terminals);
    
    for (auto &&i : parsing_table)
    {
        cout << i[0] << " ";
        cout << i[1] << " ";
        cout << i[2] << " ";
        cout << i[3] << endl;
    }

    string input;
    string start = "S";
    string rules_used = "";

    while (input != "exit")
    {

        cout << "Adja meg a szót(pl: acedcded):  ";
        cin >> input;

        if (input != "exit")
        {
            if(LL_1_without_lambda(parsing_table, input, start, rules_used))
            {
                cout << "A szó elem a nyelvnek." << endl;
                cout << "A levezetés módja: " << rules_used << endl << endl;
            }
            else
            {
                cout << "A szó nem elem a nyelvnek." << endl << endl;
            }
        }
    }

    return 0;
}
