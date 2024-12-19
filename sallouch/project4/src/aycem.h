#ifndef aycem_h
#define aycem_h
#include<stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
typedef struct {
int jour;
int mois;
int annee;
}date;
typedef struct {
    char nom[100];
    char adresse[100];
    char id[100];
    char etat[100];
    char capacite[100];
    char bloc[100];
    char tarif[100];
    char abonnement[100];
    char acces[100]; 
    char vehicule[100];
    int jd, md, ad; 
    int jf, mf, af;
} parking;

typedef struct {
    char nom[50];          
    char pren[50];        
    char cin[20];          
    date dn;
    char sexe[10];        
    char etatCiv[20];      
    char etatSan[20];    
    char tel[20];          
    char email[50];      
    char poste[50];        
    char nomAdmin[50];    
    char mdp[50];        
} Agent;
typedef struct{
 int id_administ;
 char password[100];
}login;

typedef struct {
    char id[100] ;                     
    char type[100];              
    char prix[100];                   
    char payment[100];           
    char heure[100];             
    char jj[100];                 
    char mm[100];                 
    char aa[100];                
    char confirmed[100]; 
     char id_reservation [100];  // Ajoutez ce champ pour stocker l'ID de la réservation
           
} service;
typedef struct {
    int id_reservation;       
    int id_service;
      int id;             
} Reservation;

//..............................................................................................................


           typedef struct {
    char type[20];
    char  bloc[5];
    int places_disponibles;
}Place;



 typedef struct{
      char nom[50];
      char id_parking[10];
      char adresse[100];
       Place place ;
       float tarif;

      }Parking1;


 typedef struct {
     char type[10];
    char matricule[10];
 }Vehicule1;
 typedef struct{
    char paiement[50];
    char demande_service[50];
 } Service1;
 typedef struct {
    int jour;
    int mois;
    int annee;
} Date;


typedef struct {
    int heure;
    int minute;
} Heure;
typedef struct{
    char id_reservation[10];
     Parking1 parking;
    Place place;
    Date date_reservation;
    Heure heure_debut;
    Heure heure_fin;
    Vehicule1 vehicule;
    Service1 service;
    char type_abnmt[20];

} Reservation1;
   typedef struct{
     char nom[50];
     char prenom[50];
char mdp[20];
 }Login;

int ajouter_reserv(char *filename , Reservation1 res);


void afficher_reserv(char *filename);
void modifier_reserv(char *filename, char *id, Reservation1 nouvelleres);
void supprimer_reserv(char *filename, char *id);
void chercher(char *filename, char *id);
 Reservation1 cherche(char *filename, char *id);
 
 void afficher_reservation(GtkTreeView *treeview, const char *filename);
 void affichage_reservation(GtkTreeView *treeview, const char *filename);
int ajouter_abonnement(char *filename , Reservation1 res);
int calcul_abonnement( Reservation1 res);
int ajouter_client_admninistrateur(char *filename , Login l);	
int verifier_mdp_fichier(char *filename,  char *mdp) ;







//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

char *nomp ;
int ajouter( char *filename, parking p);
int modifier(const char *filename, const char *id, parking nouveau_parking) ;
int supprimer_parking(const char *filename, const char *id) ;
void chercher_Parking(parking p, const  char *text); 
int affecter_agent(const char *parking_file, const char *agent_file, const char *id_parking, const char *cin_agent);
void afficher_Parking(GtkWidget *liste, char *nomp);
void afficher_affectations(GtkWidget *treeview);
void init_treeview(GtkTreeView *treeview) ;
int verifier(const char *filename, const char *id, parking *result);
int loginUser(int id, char *password);
/*************************************************************************************************************************************/


int ajouterservice(char *filename, service s) ;
void modifier_service(service s, int *resultat) ;
int supprimer_Service(const char *filename, const char *id) ;
void afficher_service(GtkWidget *liste, char *noms); // Afficher dans treeview les userss
void chercher_service(service s , char text[100]);
int verifier_existence(const char *id, const char *filename);
int affecter(const char *id_service, int id_reservation, const char *service_file, const char *reservation_file, const char *affectation_file) ;
void afficher_affectationsservice(GtkWidget *treeview, const char *filename);
int verifier_modif(const char *filename, const char *id, service *s);
#endif
