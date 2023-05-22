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