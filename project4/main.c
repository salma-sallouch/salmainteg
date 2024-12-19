#include <stdio.h>
#include <string.h>
#include "aycem.h"

// Menu principal
void afficher_menu() {
    printf("\n=== Menu de gestion des parkings ===\n");
    printf("1. Ajouter un parking\n");
    printf("2. Modifier un parking\n");
    printf("3. Supprimer un parking\n");
    printf("4. Afficher tous les parkings\n");
    printf("5. Affecter un agent à un parking\n");
    printf("6. Trouver un parking par ID\n");
    printf("7. Supprimer un agent par CIN\n");
    printf("8. Quitter\n");
    printf("====================================\n");
    printf("Choisissez une option : ");
}

// Saisie des informations d'un parking
void saisir_parking(parking *p) {
    printf("\nSaisir les informations du parking :\n");
    printf("Nom du parking : ");
    scanf("%s", p->nom);
    printf("Adresse du parking : ");
    scanf("%s", p->adresse);
    printf("ID du parking : ");
    scanf("%s", &p->id);
    printf("État du parking (ex: 'vide' ou 'non vide') : ");
    scanf("%s", p->etat);
    printf("Capacité du parking : ");
    scanf("%s", &p->capacite);
    printf("Bloc du parking : ");
    scanf("%s", p->bloc);
    printf("Tarif du parking : ");
    scanf("%s", &p->tarif);
    printf("Abonnement du parking (ex: 'annuelle', 'mensuelle', 'par jour') : ");
    scanf("%s", p->abonnement);
    printf("Accès au parking ('O' pour oui, 'N' pour non) : ");
    scanf(" %s", &p->acces);
    printf("Type de véhicule autorisé (ex: 'voiture', 'moto') : ");
    scanf("%s", p->vehicule);
    printf("Date de début de validité du parking (ex: '01/01/2024') : ");
    scanf("%s", p->date_debut);
    printf("Date de fin de validité du parking (ex: '01/01/2025') : ");
    scanf("%s", p->date_fin);
}

// Saisie des informations d'un agent
void saisir_agent(agent *a) {
    printf("\nSaisir les informations de l'agent :\n");
    printf("Numéro de CIN de l'agent : ");
    scanf("%s", &a->numCIN);
    printf("Nom de l'agent : ");
    scanf("%s", a->nom);
    printf("Prénom de l'agent : ");
    scanf("%s", a->prenom);
    a->id_parking = 0; // Initialisation par défaut
    printf("Adresse e-mail de l'agent : ");
    scanf("%s", a->adresse_mail);
    printf("Numéro de téléphone de l'agent : ");
    scanf("%d", &a->numero_tel);
    printf("Sexe de l'agent (ex: 'Homme' ou 'Femme') : ");
    scanf("%s", a->sexe);
    printf("Année de naissance de l'agent : ");
    scanf("%s", &a->annee_naissance);
}

int main() {
    int choix;
    parking p1;
    agent a;
    char id, cin;

    do {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                saisir_parking(&p1);
                if (ajouter("parking.txt", p1)) {
                    printf("Ajout réussi.\n");
                } else {
                    printf("Erreur d'ajout.\n");
                }
                break;

            case 2:
                printf("Entrez l'ID du parking à modifier : ");
                scanf("%s", &id);
                printf("Saisissez les nouvelles informations du parking :\n");
                saisir_parking(&p1);
                p1.id = id;
                if (modifier("parking.txt", id, p1)) {
                    printf("Modification réussie.\n");
                } else {
                    printf("Erreur de modification.\n");
                }
                break;

            case 3:
                printf("Entrez l'ID du parking à supprimer : ");
                scanf("%s", &id);
                if (supprimer("parking.txt", id)) {
                    printf("Suppression réussie.\n");
                } else {
                    printf("Erreur de suppression.\n");
                }
                break;

            case 4:
                afficher("parking.txt");
                break;

            case 5:
                saisir_agent(&a);
                printf("Entrez l'ID du parking auquel affecter l'agent : ");
                scanf("%s", &id);
                if (affecter_agent("parking.txt", id, a)) {
                    printf("Affectation réussie.\n");
                } else {
                    printf("Erreur d'affectation.\n");
                }
                break;

            case 6:
                printf("Entrez l'ID du parking à trouver : ");
                scanf("%s", &id);
                if (trouver_parking("parking.txt", id, &p1)) {
                    printf("Parking trouvé :\n");
                    printf("ID : %s, Nom : %s, Adresse : %s, État : %s, Capacité : %s, Bloc : %s, Tarif : %s, Abonnement : %s, Accès : %s, Véhicule : %s, Date début : %s, Date fin : %s\n",
                           p1.id, p1.nom, p1.adresse, p1.etat, p1.capacite, p1.bloc, p1.tarif, p1.abonnement, p1.acces, p1.vehicule, p1.date_debut, p1.date_fin);
                } else {
                    printf("Aucun parking trouvé avec cet ID.\n");
                }
                break;

            case 7:
                printf("Entrez le CIN de l'agent à supprimer : ");
                scanf("%s", &cin);
                if (supprimer_agent_par_CIN("agents.txt", cin)) {
                    printf("Agent supprimé avec succès.\n");
                } else {
                    printf("Agent introuvable.\n");
                }
                break;

            case 8:
                printf("Au revoir !\n");
                break;

            default:
                printf("Option invalide, veuillez réessayer.\n");
                break;
        }
    } while (choix != 8);

    return 0;
}

