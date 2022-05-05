/************************************************
    Top-Down elemzés megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <regex>

using namespace std;


void f(string input, vector<string> parent_elements){

    bool isRule = true;                      
    int numberOfRules = 4;
    int numberOfLetters = 3;
    string G[numberOfRules][2] ={ {"S", "T+S"},
                                  {"S", "T"},
                                  {"T", "a"},
                                  {"T", "b"} }; 
    char letters[numberOfLetters] = {'a', 'b', '+'};

    vector<string>  child_elements;
    vector<string>  temp;

    for (auto &parent : parent_elements)
    {
        for(auto &rule : G)
        {
            if(parent == rule[0])
            {
                child_elements.push_back(rule[1]);
                isRule = false;
            }
        }
        if (isRule)
        {
            for (int i = 0; i < parent.length(); i++)
            {
                for(auto &rule : G)
                {
                    if(string(1, parent[i]) == rule[0])
                    {
                        child_elements.push_back(regex_replace(parent, regex(string(1, parent[i])), rule[1]));
                    }
                }
            }    
        }
        isRule = true;    
    }

    for (auto &child : child_elements)
    {
        if(child.length() <= input.length()){
            temp.push_back(child);
        }
    }

    child_elements = temp;
    
    for (auto &child : child_elements)
    {
        if(child == input){
            cout << endl << "A/Az " << input << " szó levezethető." << endl << endl;
            return;
        }
    }

    if(child_elements.size() == 0){
        cout << endl << "A/Az " << input << " szó nem levezethető." << endl << endl;
        return;
    }
    else
    {
        f(input, child_elements);
    }
    
}

int main()
{   
    int index = 0;
    string input ;
    vector<string> start ;
    cout << "Nyelvtan" << endl << endl;
    cout << "S -> T + S" << endl;
    cout << "S -> T" << endl;
    cout << "T -> a" << endl;
    cout << "T -> b" << endl << endl;
    cout << "exit-el kilépés" << endl << endl;

    while(input != "exit"){
        cout << "Adja meg a szót(pl: b+a):  ";
        cin >> input;
        start.push_back("S");
        if (input != "exit")
        {
            f(input, start);
        }
       
    }
    return 0;
}
