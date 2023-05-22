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