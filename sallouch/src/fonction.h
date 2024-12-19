#include <gtk/gtk.h>

typedef struct
{ 
    char id[20];
    char prenom[20];
    char nom[20];
    int  jour;
    char mois[20];
    int  annee;
    char sexe[30];
    char adresse[50];
    char mdp[50];
    char email[50];

}citoyen;
typedef struct {
    char id_citoyen[50];
    char id_parking[50];
    int nb_jours ;
    float tarif_par_jour ;
    float services ;
    float reduction;
    
} Facture;
int search_user(const char *filename, const char *cin, citoyen *result);
float calculer_facture(char *filename, char * idd);
int is_valid_cin(const char *cin);
void ajouter_cit(citoyen b,char *cit);
void afficher_cit(GtkWidget *liste);
void modifier_cit(char id[],citoyen b,char *cit);
void supprimer_cit(char id[],char *cit);
int rechercher_cit(char id[]);
void afficher_rechercher_cit(GtkWidget *liste);
int remplirtabRech (citoyen tab[],int nb) ;

