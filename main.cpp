#include <iostream>
#include <string>
#include "class.h"

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

void exercice1() {
    string expression;
    cout << "Entrez une expression suffixée : ";
    cin >> expression;
    cout << "Résultat : " << evaluer(expression) << endl;
}

void exercice2() {
    string expression;
    cout << "Entrez une expression arithmétique : ";
    cin >> expression;
    cout << "Expression en notation suffixée : " << infixeVersSuffixe(expression) << endl;
    cout << "Résultat : " << evaluer(infixeVersSuffixe(expression)) << endl;
}

//arbre binaire qui dérive
void exercice4()
{
    // X + 3 création de de l'arbre A1 qui a pour racine + de type operateur et pour fils gauche X et pour fils droit 3
    arbre A1("X+3");
    //dérivee de A1 par rapport à X
    arbre A2 = A1.derivee('X');
    //affichage de l'arbre A2
    A2.afficher();


}

int main() {
    cout<<"séléctionnez un programme :"<<endl;
    cout<<"[1] : exercice 1"<<endl;
    cout<<"[2] : exercice 2"<<endl;
    cout<<"[3] : exercice 4"<<endl;
    int prog;
    cin>>prog;
    switch (prog)
    {
    case 1:
        cout<<"exercice 1 "<<endl;
        exercice1();
        break;
    case 2:
        cout<<"exercice 2"<<endl;
        exercice2();
        break;
    case 3:
        cout<<"exercice 3"<<endl;
        exercice4();
        break;
    default:
        cout<<"aucun programme séléctionné, fin."<<endl;
            return 0;
        break;
    }


    return 0;
}