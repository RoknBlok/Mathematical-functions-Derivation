class noeud
{
    friend class arbre;
    public :
    char type; //‘o’ pour opérateur, ‘f’ pour valeur et ‘v’ pour variable
    char ope;
    float val;
    char var;
    noeud * fg, * fd;
    noeud(char type, char ope, float val, char var);
    noeud(char type, char ope, float val, char var, noeud * fg, noeud * fd);
    ~noeud();
    void afficher();
    noeud * deriver(char var);
};

class Maillon {
public:
    char data;
    Maillon* next;
    noeud * n;

    Maillon();
    Maillon(char n);
    Maillon(char n, Maillon* suivant);
    Maillon(noeud * n, Maillon* suivant);
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

    //empiler noeud
    void empiler(noeud * n);
    //depiler noeud
    void depiler(noeud * n);
    //sommet noeud
    noeud * sommetNoeud();
};

class arbre
{
    friend class noeud;
    noeud * racine ;
public:
    arbre();
    arbre(std::string expression);
    arbre(noeud * racine);
    ~arbre();
    void afficherRec(noeud * n);
    void afficher();
    float evaluer();
    void afficherPrefixe();
    //deriver
    arbre deriver(char var);
};