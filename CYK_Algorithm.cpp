/************************************************
    CYK algoritmus megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;


vector<vector<set<char>>> createMatrixOfSets(int size){
    vector<vector<set<char>>> matrix;

    matrix.resize(size);
    for (int i = 0; i < size; ++i) 
        matrix[i].resize(size);

    return matrix;
}

bool cykAlghorithm(string w, char non_terminal_non_terminal_rules[8][3], char non_terminal_terminal_rules[3][2]){
    int n = w.length();

    vector<vector<set<char>>> cyk_matrix = createMatrixOfSets(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(non_terminal_terminal_rules[j][1] == w[i]){

                cyk_matrix[0][i].insert(non_terminal_terminal_rules[j][0]);
                
            }
            
        }
    }
    

    for (int i = 1;  i < n; i++)
    {
        for (int j = i ; j < n; j++)
        {
            for (int d = 0; d < i; d++)
            {
                for (auto set1 = cyk_matrix[i - (i - d)][j - (i - d)].begin();
                        set1 != cyk_matrix[i - (i - d)][j - (i - d)].end();
                            ++set1)
                {
                    
                    for (auto set2 = cyk_matrix[i - (d + 1)][j].begin(); 
                            set2 != cyk_matrix[i - (d + 1)][j].end(); 
                                ++set2)
                    {  
                        
                        
                        for (int a = 0; a < 8; a++)
                        {
                            if (*set1 == non_terminal_non_terminal_rules[a][1] 
                                    && *set2 == non_terminal_non_terminal_rules[a][2])
                            {
                                cyk_matrix[i][j].insert(non_terminal_non_terminal_rules[a][0]);
                            }
                        }                 
                    }
                }
            }         
        }    
    }

    for (auto top = cyk_matrix[n-1][n-1].begin(); top != cyk_matrix[n-1][n-1].end(); ++top){

        if(*top == 'S'){
            return true;
            
        }
    }
    
    return false;

}


int main()
{
    string input;
    
    char non_terminal_non_terminal_rules[8][3] = {  {'S', 'A', 'B'}, 
                                                    {'S', 'C', 'D'}, 
                                                    {'S', 'C', 'B'},
                                                    {'S', 'S', 'S'},
                                                    {'A', 'B', 'C'}, 
                                                    {'B', 'S', 'C'}, 
                                                    {'C', 'D', 'D'}, 
                                                    {'D', 'B', 'A'} };

    char non_terminal_terminal_rules[3][2] = { {'A', 'a'}, 
                                               {'B', 'b'}, 
                                               {'C', 'b'}};

    cout << "Nyelvtan" << endl << endl;
    cout << "S -> AB" << endl;
    cout << "S -> CD" << endl;
    cout << "S -> CB" << endl;
    cout << "S -> SS" << endl;
    cout << "A -> BC" << endl;
    cout << "B -> SC" << endl;
    cout << "C -> DD" << endl;
    cout << "D -> BA" << endl;
    cout << "A -> a" << endl;
    cout << "B -> b" << endl;
    cout << "C -> b" << endl << endl;
    cout << "exit-el kilépés" << endl << endl;

    while(input != "exit"){
        cout << "Adja meg a szót(pl: aabbaba):  ";
        cin >> input;
        if (input != "exit")
        {
            if(cykAlghorithm(input, non_terminal_non_terminal_rules, non_terminal_terminal_rules))
            {
                cout << endl << "A/Az " << input << " szó levezethető." << endl << endl;
            }
            else
            {
                cout << endl << "A/Az " << input << " szó nem levezethető." << endl << endl;
            }
        }
       
    }
    return 0;
}