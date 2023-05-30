#include <iostream>
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

arbre::arbre(char type, char ope, float val) {
    racine = new noeud;
    racine->type = type;
    racine->ope = ope;
    racine->val = val;
    racine->fg = NULL;
    racine->fd = NULL;
}

arbre::arbre(char type, char ope, float val, arbre fg, arbre fd) {
    racine = new noeud;
    racine->type = type;
    racine->ope = ope;
    racine->val = val;
    racine->fg = fg.racine;
    racine->fd = fd.racine;
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