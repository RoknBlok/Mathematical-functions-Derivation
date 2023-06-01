#include <iostream>
#include <string>
#include <cmath>
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
    string sortie;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            pile.empiler(expression[i]);
        } else if (expression[i] == ')') {
            while (pile.sommet() != '(') {
                sortie += pile.sommet();
                pile.depiler();
            }
            pile.depiler();
        } else if (isdigit(expression[i])) {
            sortie += expression[i];
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
    //test dérivation de l'expression 2*x+3
    /*
    noeud * n1 = new noeud('f', ' ', 2, ' ');
    noeud * n2 = new noeud('v', ' ', 0, 'x');
    noeud * n3 = new noeud('o', '*', 0, ' ', n1, n2);
    noeud * n4 = new noeud('f', ' ', 3, ' ');
    noeud * n5 = new noeud('o', '+', 0, ' ', n3, n4);
    arbre a(n5);
    */

    //test dérivation de l'expression 2x+3
    arbre a("(3*X)/ 2");

    cout<<"Expression : ";
    a.afficher();
    cout<<endl;
    cout<<"Dérivée : ";
    //deriver par rapport à x
    a.deriver('x').afficher();
    cout<<endl;

    /*
    cout<<"Expression dérivée par rapport à x : ";
    a.deriver('x').afficher();
    cout<<endl;*/
    
}

int main() {
    cout<<"séléctionnez un programme :"<<endl;
    cout<<"[1] : prog 1"<<endl;
    cout<<"[2] : prog 2"<<endl;
    cout<<"[3] : prog 3"<<endl;
    int prog;
    cin>>prog;
    switch (prog)
    {
    case 1:
        cout<<"prog 1 "<<endl;
        exercice1();
        break;
    case 2:
        cout<<"prog 2"<<endl;
        exercice2();
        break;
    case 3:
        cout<<"prog 3"<<endl;
        exercice4();
        break;
    default:
        cout<<"aucun programme séléctionné, fin."<<endl;
            return 0;
        break;
    }


    return 0;
}