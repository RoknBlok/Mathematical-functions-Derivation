#include <iostream>
#include <string>
#include <cmath>
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

int Pile::priorite(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

void Pile::infixeVersSuffixe(string expression) {
    string sortie;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '(') {
            empiler(expression[i]);
        } else if (expression[i] == ')') {
            while (sommet() != '(') {
                sortie += sommet();
                depiler();
            }
            depiler();
        } else if (isdigit(expression[i])) {
            sortie += expression[i];
        } else {
            while (!vide() && priorite(sommet()) >= priorite(expression[i])) {
                sortie += sommet();
                depiler();
            }
            empiler(expression[i]);
        }
    }
    while (!vide()) {
        sortie += sommet();
        depiler();
    }
    cout << sortie << endl;
}

noeud::noeud() {
    fg = NULL;
    fd = NULL;
}

noeud * Pile::depiler_noeud() {
    if (tete == NULL) {
        cout << "La pile est vide" << endl;
        return NULL;
    }
    Maillon* temp = tete;
    tete = tete->next;
    temp->next = NULL;
    noeud* n = temp->n;
    delete temp;
    return n;
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






//tutur
arbre::arbre(string a){
    Pile pile1;
    Pile pile2;
    pile1.infixeVersSuffixe(a);
    cout << a << endl;
    noeud *current = racine;

    for(int i=0;i<a.size();i++){
        if(a[i]==' '){
            continue;
        }
        if(a[i]>='0' && a[i]<='9'){
            int valeur = 0;
            while(a[i]>='0' && a[i]<='9'){
                valeur = valeur*10 + (a[i]-'0');
                i++;
            }
            noeud *n = new noeud;
            n->type = 'f';
            n->val = valeur;
            pile2.empiler(n);
        }
        else if(a[i]=='+' || a[i]=='-' || a[i]=='*' || a[i]=='/' || a[i]=='^'){
            noeud *n = new noeud;
            n->type = 'o';
            n->ope = a[i];
            n->fg = pile2.depiler_noeud();
            n->fd = pile2.depiler_noeud();
            pile2.empiler(n);
        }else if(a[i]=='X' || a[i]=='Y' || a[i]=='Z'){
            noeud *n = new noeud;
            n->type = 'v';
            n->ope = a[i];
            pile2.empiler(n);
        }
    }
    (*this).racine = pile2.depiler_noeud();
}

arbre::~arbre() {
    delete racine;
}


float arbre::evaluer(noeud *n) {
    if (n->type == 'f') {
        return n->val;
    }else if(n->type == 'v'){
        return n->ope;
    }

    int gauche = evaluer(n->fg);
    int droite = evaluer(n->fd);

    switch (n->ope) {
        case '+':
            return gauche + droite;
        case '-':
            return gauche - droite;
        case '*':
            return gauche * droite;
        case '/':
            return gauche / droite;
        case '^':
            return pow(gauche, droite);
        default:
            return 0;
    }
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

void arbre::afficher(noeud *n) { // /!\ NE PAS OUBLIER DE METTRE DES ESPACES ENTRE CHAQUES VALEURS ET OPERATEURS !!!
    if (n == nullptr) {
        return;
    }

    if (n->type == 'o') {
        cout << "( ";
        afficher(n->fg);
        cout << n->ope << " ";
        afficher(n->fd);
        cout << ") ";
    } else if(n->type == 'f'){
        cout << n->val << " ";
    }else if(n->type == 'v'){
        cout << n->ope << " ";
    }
}

void arbre::afficher() {
    afficher((*this).racine);
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