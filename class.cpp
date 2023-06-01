#include <iostream>
#include <string>
#include "class.h"

using namespace std;

Pile::Pile() {
    tete = NULL;
}

void Pile::empiler(char n) {
    Maillon* temp = new Maillon(n, tete);
    tete = temp;
}

void Pile::depiler() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return;
    }
    Maillon* temp = tete;
    tete = tete->next;
    temp->next = NULL;
    delete temp;
}

bool Pile::vide() {
    return tete == NULL;
}

int Pile::sommet() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return -1;
    }
    return tete->data;
}

void Pile::empiler(noeud* n) {
    Maillon* temp = new Maillon(n, tete);
    tete = temp;
}

void Pile::depiler(noeud* n) {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return;
    }
    Maillon* temp = tete;
    tete = tete->next;
    temp->next = NULL;
    delete temp;
}

noeud* Pile::sommetNoeud() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return NULL;
    }
    return tete->n;
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

Maillon::Maillon(noeud* n, Maillon* suivant) {
    this->n = n;
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

//constructeur qui prend une expression en notation infixe et construit l'arbre correspondant


arbre::arbre(noeud* racine) {
    this->racine = racine;
}

arbre::arbre(string expression) {
    Pile pile;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue;
        }
        if (expression[i] == '(') {
            pile.empiler(expression[i]);
        } else if (expression[i] == ')') {
            while (pile.sommet() != '(') {
                char ope = pile.sommet();
                pile.depiler();
                noeud* fd = pile.sommetNoeud();
                pile.depiler(fd);
                noeud* fg = pile.sommetNoeud();
                pile.depiler(fg);
                noeud* temp = new noeud('o', ope, 0, ' ', fg, fd);
                pile.empiler(temp);
            }
            pile.depiler();
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            pile.empiler(expression[i]);
        } else if (expression[i] >= '0' && expression[i] <= '9') {
            float val = 0;
            while (expression[i] >= '0' && expression[i] <= '9') {
                val = val * 10 + expression[i] - '0';
                i++;
            }
            i--;
            noeud* temp = new noeud('f', ' ', val, ' ');
            pile.empiler(temp);
        } else {
            noeud* temp = new noeud('v', ' ', 0, expression[i]);
            pile.empiler(temp);
        }
    }
    racine = pile.sommetNoeud();
}

arbre::~arbre() {
    delete racine;
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

void noeud::afficher() {
    if (type == 'f') {
        cout << val << " ";
    } else if (type == 'v') {
        cout << var << " ";
    } else {
        cout << ope << " ";
    }
}

void arbre::afficherRec(noeud* n) {
    if (n == NULL) {
        return;
    }
    n->afficher();
    afficherRec(n->fg);
    afficherRec(n->fd);
}

void arbre::afficher() {
    afficherRec(racine);
    cout << endl;
}

//affichage arbre en notation préfixe
void arbre::afficherPrefixe() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return;
    }
    racine->afficher();
    arbre fg;
    fg.racine = racine->fg;
    fg.afficherPrefixe();
    arbre fd;
    fd.racine = racine->fd;
    fd.afficherPrefixe();
}



noeud * noeud::deriver(char var) {
    if (type == 'f') {
        return new noeud('f', ' ', 0, ' ');
    } else if (type == 'v') {
        if (var == this->var) {
            return new noeud('f', ' ', 1, ' ');
        } else {
            return new noeud('f', ' ', 0, ' ');
        }
    } else {
        noeud* temp = new noeud('o', ope, 0, ' ');
        temp->fg = fg->deriver(var);
        temp->fd = fd->deriver(var);
        return temp;
    }
}

arbre arbre::deriver(char var) {
    arbre temp;
    temp.racine = racine->deriver(var);
    return temp;
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