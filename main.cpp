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
void exercice3()
{
    //test dérivation de l'expression 2*x+3
    noeud * n1 = new noeud('f', ' ', 2, ' ');
    noeud * n2 = new noeud('f', ' ', 1, ' ');
    noeud * n3 = new noeud('o', '*', 0, ' ', n1, n2);
    noeud * n4 = new noeud('f', ' ', 3, ' ');
    noeud * n5 = new noeud('o', '+', 0, ' ', n3, n4);
    arbre a(n5);

    //test dérivation de l'expression 2x+3
    //arbre a("23+");
    
    cout<<"Expression : ";
    a.afficher();


    
    cout<<endl;

    cout<<"Execution de la fonction evaluer() :";
    cout<<a.evaluer();
    /*
    cout<<endl;
    cout<<"Dérivée : ";
    //deriver par rapport à x
    a.deriver('x').afficher();
    cout<<endl;
*/
    /*
    cout<<"Expression dérivée par rapport à x : ";
    a.deriver('x').afficher();
    cout<<endl;*/
    
}

//fonction de démonstration dérivation d'arbre binaire
void exercice4()
{
    //test dérivation de l'expression 2*x+3
    noeud * n1 = new noeud('2');
    noeud * n2 = new noeud('x');
    noeud * n3 = new noeud('*', n1, n2);
    noeud * n4 = new noeud('3');
    noeud * n5 = new noeud('+', n3, n4);
    arbre a(n5);

    //test dérivation de l'expression 2x+3
    //arbre a("23+");
    
    cout<<"Expression : ";
    a.afficher();
    
    cout<<endl;

    cout<<"Construction de l'arbre de dérivation : \n \n";
    arbre deriveDea(a.deriver(a.racine, 'x'));

    cout<<"Dérivée de l'expression :";
    //affiche la dérivée de l'expression
    deriveDea.afficher();

    //a.deriver(a.racine,'x')
    /*
    cout<<endl;
    cout<<"Dérivée : ";
    //deriver par rapport à x
    a.deriver('x').afficher();
    cout<<endl;
*/
    /*
    cout<<"Expression dérivée par rapport à x : ";
    a.deriver('x').afficher();
    cout<<endl;*/
    
}

int main() {
    /*cout<<R"(
  __  __ _       _   _____           _      _     _____   ____   ____  _____
 |  \/  (_)     (_) |  __ \         (_)    | |   |  __ \ / __ \ / __ \|  __ \
 | \  / |_ _ __  _  | |__) | __ ___  _  ___| |_  | |__) | |  | | |  | | |__) |
 | |\/| | | '_ \| | |  ___/ '__/ _ \| |/ _ \ __| |  ___/| |  | | |  | |  ___/
 | |  | | | | | | | | |   | | | (_) | |  __/ |_  | |    | |__| | |__| | |
 |_|  |_|_|_| |_|_| |_|   |_|  \___/| |\___|\__| |_|     \____/ \____/|_|
                                   _/ |
                                  |__/
    )"<<endl;
     */
    cout<<R"(
  __  __ _       _   _____           _      _     _____   ____   ____
 |  \/  (_)     (_) |  __ \         (_)    | |   |  __ \ / __ \ / __ \
 | \  / |_ _ __  _  | |__) | __ ___  _  ___| |_  | |__) | |  | | |  | |
 | |\/| | | '_ \| | |  ___/ '__/ _ \| |/ _ \ __| |  ___/| |  | | |  | |
 | |  | | | | | | | | |   | | | (_) | |  __/ |_  | |    | |__| | |__| |
 |_|  |_|_|_| |_|_| |_|   |_|  \___/| |\___|\__| |_|     \____/ \____/
                                   _/ |
                                  |__/
    )"<<endl;


    cout<<"séléctionnez un programme :"<<endl;
    cout<<"[1] : évaluer une expression suffixée"<<endl;
    cout<<"[2] : évaluer une expression infixée"<<endl;
    cout<<"[3] : démonstration évaluation d'arbre binaire"<<endl;
    cout<<"[4] : démonstration dérivation d'arbre binaire"<<endl;
    int prog;
    cin>>prog;
    switch (prog)
    {
    case 1:
        exercice1();
        break;
    case 2:
        exercice2();
        break;
    case 3:
        exercice3();
        break;
    case 4:
        exercice4();
        break;
    default:
        cout<<"aucun programme séléctionné, fin."<<endl;
            return 0;
        break;
    }


    return 0;
}