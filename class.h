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
    char type; //‘o’ pour opérateur et ‘f’ pour valeur.
    char ope;
    float val;
    noeud * fg, * fd;
};

//class arbre binaire
class arbre
{
    noeud * racine ;
public:
    arbre() ;
    arbre(char type, char ope, float val) ;
    arbre(char type, char ope, float val, arbre fg, arbre fd) ;
    ~arbre() ;
    void afficher() ;
    float evaluer() ;
};