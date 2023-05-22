#include <iostream>
#include "class.h"
#include <string>

using namespace std;

int priorite(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

string infixeVersSuffixe(string expression) {
    Pile pile;
    string sortie = "";
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            sortie += expression[i];
        } else if (expression[i] == '(') {
            pile.empiler(expression[i]);
        } else if (expression[i] == ')') {
            while (!pile.vide() && pile.sommet() != '(') {
                sortie += pile.sommet();
                pile.depiler();
            }
            pile.depiler();
        } else {
            while (!pile.vide() && priorite(pile.sommet()) >= priorite(expression[i])) {
                sortie += pile.sommet();
                pile.depiler();
            }
            pile.empiler(expression[i]);
        }
    }
    while (!pile.vide()) {
        sortie += pile.sommet();
        pile.depiler();
    }
    return sortie;
}

int evaluer(string expression) {
    Pile pile;
    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            pile.empiler(expression[i] - '0');
        } else {
            int val1 = pile.sommet();
            pile.depiler();
            int val2 = pile.sommet();
            pile.depiler();
            switch (expression[i]) {
                case '+': pile.empiler(val2 + val1); break;
                case '-': pile.empiler(val2 - val1); break;
                case '*': pile.empiler(val2 * val1); break;
                case '/': pile.empiler(val2 / val1); break;
            }
        }
    }
    return pile.sommet();
}

// Test
int main()
{
    string expression = "1+2*3";
    cout << infixeVersSuffixe(expression) << endl;
    cout << evaluer(infixeVersSuffixe(expression)) << endl;
    return 0;
}
