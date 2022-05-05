/*******************************************************
    Általános LL(1) elemző megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
********************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>

using namespace std;


bool ll1(string word, string &rules_used)
{
    bool run = true;
    string s = "S";
    rules_used.clear();
    while (run)
    {   
        run = false;
        if(word[0] == ')' && s.substr(0, 2) == "E'")
        {
            rules_used += '3';
            s.replace(0,2, "");
            run = true;
        }
        else if(word[0] == '+' && s.substr(0, 2) == "E'")
        {
            rules_used += '2';
            s.replace(0,2, "+TE'");
            run = true;
        }
        else if(word.empty() && s.substr(0, 2) == "E'")
        {
            rules_used += '3';
            s.replace(0,2, "");
            run = true;
        }


        else if(word[0] == ')' && s.substr(0, 2) == "T'")
        {
            rules_used += '6';
            s.replace(0,2, "");
            run = true;
        }
        else if(word[0] == '*' && s.substr(0, 2) == "T'")
        {
            rules_used += '5';
            s.replace(0,2, "*FT'");
            run = true;
        }
        else if(word[0] == '+' && s.substr(0, 2) == "T'")
        {
            rules_used += '6';
            s.replace(0,2, "");
            run = true;
        }
        else if(word.empty() && s.substr(0, 2) == "T'")
        {
            rules_used += '6';
            s.replace(0,2, "");
            run = true;
        }


        else if(word[0] == '(' && s[0] == 'S')
        {
            rules_used += '1';
            s.replace(0,1, "TE'");
            run = true;
        }
        else if(word[0] == 'i' && s[0] == 'S')
        {
            rules_used += '1';
            s.replace(0,1, "TE'");
            run = true;
        }


        else if(word[0] == '(' && s[0] == 'T')
        {
            rules_used += '4';
            s.replace(0,1, "FT'");
            run = true;
        }
        else if(word[0] == 'i' && s[0] == 'T')
        {
            rules_used += '4';
            s.replace(0,1, "FT'");
            run = true;
        }


        else if(word[0] == '(' && s[0] == 'F')
        {
            rules_used += '7';
            s.replace(0,1, "(S)");
            run = true;
        }

        else if(word[0] == 'i' && s[0] == 'F')
        {
            rules_used += '8';
            s.replace(0,1, "i");
            run = true;
        }

        else if(word[0] == s[0] && !(word.empty() && s.empty()))
        {
            word.erase(0,1);
            s.erase(0,1);
            run = true;
        }
    }
    if(word.empty() && s.empty())
    {
        return true;
    }
    return false;
    
}


int main()
{
    string input;
    string rules_used;

    cout << "Nyelvtan" << endl << endl;
    cout << "1. S -> TE'" << endl;
    cout << "2. E' -> +TE'" << endl;
    cout << "3. E' -> λ" << endl;
    cout << "4. T -> FT'" << endl;
    cout << "5. T' -> *FT'" << endl;
    cout << "6. T' -> λ" << endl;
    cout << "7. F -> (S)" << endl;
    cout << "8. F -> i" << endl << endl;

    cout << "Terminalisok: (, ), +, *, i" << endl << endl;

    cout << "exit-el kilépés" << endl << endl;


    while (input != "exit")
    {

        cout << "Adja meg a szót(pl: i+i*i):  ";
        cin >> input;

        if (input != "exit")
        {
            if(ll1(input, rules_used))
            {
                cout << "\nA szó elem a nyelvnek." << endl;
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