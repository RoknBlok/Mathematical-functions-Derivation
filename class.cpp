#include <iostream>
#include <string>
#include <cmath>
#include "class.h"

using namespace std;

Pile::Pile() {
    tete = NULL;
}

Pile::~Pile() {
    delete tete;
}

/*
void Pile::empiler(char n) {
    Maillon* temp = new Maillon(n, tete);
    tete = temp;
}
*/

void Pile::empiler(char value) {
    Maillon *new_maillon = new Maillon;
    new_maillon->data = value;
    new_maillon->next = tete;
    tete = new_maillon;
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


/*
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

*/

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


/*
//constructeur d'arbre avec une expression en notation suffixe
arbre::arbre(string a) {
    Pile pile;
    for (int i = 0; i < a.length(); i++) {
        if (isdigit(a[i])) {
            noeud* n = new noeud;
            n->type = 'f';
            n->val = a[i] - '0';
            pile.empiler(n);
        } else {
            noeud* n = new noeud;
            n->type = 'o';
            n->ope = a[i];
            n->fd = pile.depiler_noeud();
            n->fg = pile.depiler_noeud();
            pile.empiler(n);
        }
    }
    racine = pile.depiler_noeud();
}

*/




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

float arbre::evaluer() {
    return evaluer(racine);
}

//constructeur de noeud qui détecte le type de noeud à créer
noeud::noeud(char v, noeud* fg, noeud* fd) {
    //detection du type de v
    if (v >= '0' && v <= '9') {
        type = 'f';
        val = v - '0';
    } else if (v == 'x' || v == 'y' || v == 'z') {
        type = 'v';
        var = v;
    } else {
        type = 'o';
        ope = v;
    }

    this->fg = fg;
    this->fd = fd;
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

void noeud::setfgauche(noeud* fg) {
    this->fg = fg;
}

void noeud::setfdroit(noeud* fd) {
    this->fd = fd;
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
        cout << n->var << " ";
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

void arbre::afficherInfixe() {
    if (racine == NULL) {
        cout << "L'arbre est vide" << endl;
        return;
    }
    arbre fg;
    fg.racine = racine->fg;
    fg.afficherInfixe();
    racine->afficher();
    arbre fd;
    fd.racine = racine->fd;
    fd.afficherInfixe();
}


noeud* noeud::deriver(char var) {
    noeud* n = new noeud;
    if (type == 'f') {
        n->type = 'f';
        n->val = 0;
    } else if (type == 'v') {
        if (var == this->var) {
            n->type = 'f';
            n->val = 1;
        } else {
            n->type = 'f';
            n->val = 0;
        }
    } else {
        n->type = 'o';
        n->ope = ope;
        n->fg = fg->deriver(var);
        n->fd = fd->deriver(var);
    }
    return n;
}
/*

arbre arbre::deriver(char var) {
    arbre temp;
    temp.racine = racine->deriver(var);
    return temp;
}
*/


//deriver tutur
noeud* arbre::deriver(noeud* n, char v) {
    noeud* current = n;
    cout << "on derive: ";
    (*this).afficher(current);
    cout << endl;

    if (current->type == 'f') {
        cout << "dérivée (ne prenez en compte que la première dérivée): " << current->val << endl;
        noeud* deriv = new noeud('f');
        deriv->val = 0;
        (*this).afficher(deriv); cout << endl;
        return deriv;
    }
    else if (current->type == 'v') {
        if (current->ope == v) {
            noeud* deriv = new noeud('f');
            deriv->val = 1;
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
        else {
            noeud* deriv = new noeud('f');
            deriv->val = 0;
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
    }
    else {
        if (current->ope == '+' || current->ope == '-') {
            noeud* deriv = new noeud(current->ope);
            deriv->fg = deriver(current->fg, v);
            deriv->fd = deriver(current->fd, v);
            (*this).afficher(deriv); cout << endl;
            return deriv;
        }else if (current->ope == '*') {
            noeud* deriv = new noeud('+');
            deriv->fg = new noeud('*');
            deriv->fg->fg = deriver(current->fg, v);
            deriv->fg->fd = current->fd;

            deriv->fd = new noeud('*');
            deriv->fd->fg = current->fg;
            deriv->fd->fd = deriver(current->fd, v);

            (*this).afficher(deriv); cout << endl;
            return deriv;
        }else if (current->ope == '/') {
            noeud* deriv = new noeud('/');
            deriv->fg = new noeud('-');
            deriv->fg->fg = new noeud('*');
            deriv->fg->fg->fg = deriver(current->fg, v);
            deriv->fg->fg->fd = current->fd;

            deriv->fg->fd = new noeud('*');
            deriv->fg->fd->fg = current->fg;
            deriv->fg->fd->fd = deriver(current->fd, v);

            deriv->fd = new noeud('*');
            deriv->fd->fg = current->fd;
            deriv->fd->fd = current->fd;

            (*this).afficher(deriv); cout << endl;
            return deriv;
        }
        else if (current->ope == '^') {
            int exponent = current->fd->val;
            noeud* derivateBase = deriver(current->fg, v);
            noeud* derivatefg = deriver(current->fg, v);

            if (exponent == 0) {
                noeud* deriv = new noeud('f');
                deriv->val = 0;
                return deriv;
            }
            else {
                noeud* deriv = new noeud('*');
                deriv->fg = new noeud('*');
                deriv->fg->fg = new noeud('f');
                deriv->fg->fg->val = exponent;
                deriv->fg->fd = new noeud('^');
                deriv->fg->fd->fg = current->fg;
                deriv->fg->fd->fd = new noeud('f');
                deriv->fg->fd->fd->val = exponent - 1;
                deriv->fd = new noeud('*');
                deriv->fd->fg = derivateBase;
                deriv->fd->fd = derivatefg;
                (*this).afficher(deriv); cout << endl;
                return deriv;
            }
        }
    }

    return nullptr; // Retourne nullptr si aucun cas ne correspond (retour par défaut)
}


void arbre::afficherDerivee(char var) {
    arbre temp;
    temp.racine = racine->deriver(var);
    temp.afficher();
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