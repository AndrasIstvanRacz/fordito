/************************************************
    Bottom-Up elemzés megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>

using namespace std;


void f(string word, string parent_element){

    bool reduce = true;            
    int numberOfRules = 4;
    int numberOfLetters = 3;
    string G[numberOfRules][2] ={ {"S", "S+T"},
                                  {"S", "T"},
                                  {"T", "a"},
                                  {"T", "b"} }; 
    char letters[numberOfLetters] = {'a', 'b', '+'};

    string child_element;
    
    cout << parent_element << endl;

    for (int i = 0; i < numberOfRules; i++)
    {
        if(G[i][1] == parent_element)
        {
            child_element = G[i][0]; 
        }
    }
    
    if(!child_element.empty())
    {
        
        f(word, child_element);
    }
    else
    {
        for (int i = 0; i < numberOfRules; i++)
        {
            if(G[i][1] == string(1, parent_element.back()))
            {
                child_element = regex_replace(parent_element, regex(string(1, parent_element.back())), G[i][0]);
                
                reduce = false; 
            }
        }
        if(reduce)
        {
            if(word.empty() && parent_element == "S")
            {
                cout << endl << "A szó része a nyelvnek." << endl << endl;
                return;
            }
            else if(word.empty() && parent_element != "S")
            {
                cout << endl << "A szó nem elem a nyelvnek." << endl << endl;
                return;
            }
            else
            {
                f(word.erase(0,1), parent_element.append(string(1, word[0])));
            }
        }
        else
        {
            f(word, child_element);
        }
    }
}

int main()
{   
    int index = 0;
    string input ;

    cout << "Nyelvtan" << endl << endl;
    cout << "S -> S + T" << endl;
    cout << "S -> T" << endl;
    cout << "T -> a" << endl;
    cout << "T -> b" << endl << endl;
    cout << "exit-el kilépés" << endl << endl;

    while(input != "exit"){

        cout << "Adja meg a szót(pl: b+a):  ";
        cin >> input;

        if (input != "exit")
        {
            f(input.erase(0,1), string(1, input[0]));
        }
       
    }
    return 0;
}