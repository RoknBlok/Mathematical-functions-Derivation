class Maillon {
public:
    char data;
    Maillon* next;

    Maillon();

    Maillon(char n);

    Maillon(char n, Maillon* suivant);

    ~Maillon();

    void afficher();
};

class Pile {
    Maillon* tete;
public:
    Pile();
    void empiler(char n);
    void depiler();
    bool vide();
    int sommet();
};

class noeud
{
    public :
    char type; //‘o’ pour opérateur, ‘f’ pour valeur et ‘v’ pour variable
    char ope;
    float val;
    char var;
    noeud * fg, * fd;
    noeud(char type, char ope, float val, char var);
    noeud(char type, char ope, float val, char var, noeud * fg, noeud * fd);
    ~noeud();
};

class arbre
{
    noeud * racine ;
public:
    arbre();
    arbre(std::string expression);
    arbre(noeud * racine);
    arbre derivee(char var);
    ~arbre();
    void afficher();
    float evaluer();
    void afficherPrefixe();
};