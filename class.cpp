#include <iostream>
#include <string>
#include "class.h"

using namespace std;

Pile::Pile() {
    tete = NULL;
}

void Pile::empiler(char n) {
    Maillon* temp = new Maillon;
    temp->data = n;
    temp->next = tete;
    tete = temp;
}

void Pile::depiler() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return;
    }
    Maillon* temp = tete;
    tete = tete->next;
    delete temp;
}

bool Pile::vide() {
    return (tete == NULL);
}

int Pile::sommet() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return -1;
    }
    return tete->data;
}

Maillon::Maillon() {
    next = NULL;
}

Maillon::Maillon(char n) {
    data = n;
    next = NULL;
}

Maillon::Maillon(char n, Maillon* suivant) {
    data = n;
    next = suivant;
}

Maillon::~Maillon() {
    delete next;
}

void Maillon::afficher() {
    cout << data << endl;
}

arbre::arbre() {
    racine = NULL;
}

arbre::arbre(string expression)
{
    Pile pile;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            pile.empiler(expression[i]);
        } else if (expression[i] == ')') {
            while (pile.sommet() != '(') {
                noeud* temp = new noeud('o', pile.sommet(), 0, ' ');
                pile.depiler();
                temp->fd = racine;
                racine = temp;
            }
            pile.depiler();
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            pile.empiler(expression[i]);
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            noeud* temp = new noeud('f', ' ', expression[i] - '0', ' ');
            temp->fd = racine;
            racine = temp;
        } else if (expression[i] >= 'a' && expression[i] <= 'z') {
            noeud* temp = new noeud('v', ' ', 0, expression[i]);
            temp->fd = racine;
            racine = temp;
        }
    }
}

arbre::arbre(noeud* racine) {
    this->racine = racine;
}

arbre::~arbre() {
    delete racine;
}

void arbre::afficher() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return;
    }
    if (racine->type == 'f') {
        cout << racine->val << endl;
    } else {
        cout << racine->ope << endl;
        arbre fg;
        fg.racine = racine->fg;
        fg.afficher();
        arbre fd;
        fd.racine = racine->fd;
        fd.afficher();
    }
}

void arbre::afficherPrefixe() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return;
    }
    if (racine->type == 'f') {
        cout << racine->val << endl;
    } else {
        cout << racine->ope << endl;
        arbre fg;
        fg.racine = racine->fg;
        fg.afficherPrefixe();
        arbre fd;
        fd.racine = racine->fd;
        fd.afficherPrefixe();
    }
}

float arbre::evaluer() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return -1;
    }
    if (racine->type == 'f') {
        return racine->val;
    } else {
        arbre fg;
        fg.racine = racine->fg;
        float val1 = fg.evaluer();
        arbre fd;
        fd.racine = racine->fd;
        float val2 = fd.evaluer();
        switch (racine->ope) {
            case '+': return val1 + val2;
            case '-': return val1 - val2;
            case '*': return val1 * val2;
            case '/': return val1 / val2;
        }
    }
    return -1;
}

arbre arbre::derivee(char var) {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return arbre();
    }
    if (racine->type == 'f') {
        return arbre();
    } else {
        switch (racine->ope) {
            case '+': return arbre(new noeud('o', '+', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var)));
            case '-': return arbre(new noeud('o', '-', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var)));
            case '*': return arbre(new noeud('o', '+', 0, ' ', new noeud('o', '*', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var)), new noeud('o', '*', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var))));
            case '/': return arbre(new noeud('o', '/', 0, ' ', new noeud('o', '-', 0, ' ', new noeud('o', '*', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var)), new noeud('o', '*', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var))), new noeud('o', '*', 0, ' ', new noeud('v', ' ', 0, var), new noeud('v', ' ', 0, var))));
        }
    }
    return arbre();
}

noeud::noeud(char type, char ope, float val, char var) {
    this->type = type;
    this->ope = ope;
    this->val = val;
    this->var = var;
    this->fg = NULL;
    this->fd = NULL;
}

noeud::noeud(char type, char ope, float val, char var, noeud* fg, noeud* fd) {
    this->type = type;
    this->ope = ope;
    this->val = val;
    this->var = var;
    this->fg = fg;
    this->fd = fd;
}

noeud::~noeud() {
    delete fg;
    delete fd;
}

/*
float arbre::evaluer() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return -1;
    }
    if (racine->type == 'f') {
        return racine->val;
    } else {
        arbre fg;
        fg.racine = racine->fg;
        float val1 = fg.evaluer();
        arbre fd;
        fd.racine = racine->fd;
        float val2 = fd.evaluer();
        switch (racine->ope) {
            case '+': return val1 + val2;
            case '-': return val1 - val2;
            case '*': return val1 * val2;
            case '/': return val1 / val2;
        }
    }
    return -1;
}
 */