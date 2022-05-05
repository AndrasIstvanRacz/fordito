/************************************************
    Lexikális elemző megoldás fordítoprogramokra
        Készítete: Rácz András István(CTOTLY)
*************************************************/

#include <iostream>

using namespace std;


void lexer(string expression, string &output){

    if(isalpha(expression[0])){

        while(isalpha(expression[0]) || isdigit(expression[0])){
            expression.erase(0,1);
        }

        output = output + "<azonosító>";
        lexer(expression, output);
    }

    else if (isdigit(expression[0])){

        while(isdigit(expression[0])){
            expression.erase(0,1);
        }

        output = output + "<konstans>";
        lexer(expression, output);
    }

    else if (expression[0] == ':' && expression[1] == '='){

        output = output + "<értékadás>";
        lexer(expression.erase(0,2), output);
    }

    else if (expression[0] == '<'){
        
        if(expression[1] == '='){
            output = output + "<<=token>";
            lexer(expression.erase(0,2), output);
        }
        else if (expression[1] == '>'){
            output = output + "<<>token>";
            lexer(expression.erase(0,2), output);
        }
            
    }

    else if (expression[0] == '>' && expression[1] == '='){
        
        output = output + "<>=token>";
        lexer(expression.erase(0,2), output);
    }

    else if (expression[0] == '{'){

        while(expression[0] != '}' && expression[0] != '$'){
            expression.erase(0,1);
        }
        if(expression[0] == '$'){
            output = output + "<hiba>";
            lexer(expression, output);
        }else{
            output = output + "<{}kommentár>";
            lexer(expression.erase(0,1), output);
        }
        
    }

    else if (expression[0] == '(' && expression[1] == '*'){
        expression.erase(0,2);

        while(!(expression[0] == '*' && expression[1] == ')') && expression[0] != '$'){
            expression.erase(0,1);
        }
        if(expression[0] == '$'){
            output = output + "<hiba>";
            lexer(expression, output);
        }else{
            output = output + "<(**)kommentár>";
            lexer(expression.erase(0,2), output);
        }
        
    }

    else if (expression[0] == '$'){
        output = output + "<eof>";
        cout << endl << output << endl;
    }

    else{
        output = output + "<hiba>";
        lexer(expression.erase(0,1), output);
    }
    
}

int main(){

    string input;
    string output;
    
    do{
        cout << "Adja meg a bemenetet:  " << endl;
        getline(cin, input);
    }while(input.empty() || input[input.length()-1] != '$');

    lexer(input, output);
    
}
