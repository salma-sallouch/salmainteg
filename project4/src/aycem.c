#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <string.h>
#include "aycem.h"
#include <gtk/gtk.h>

#include <stdlib.h>
#include <string.h>
# define COLUMNS 16
#define FILE_PATH "administrateur.txt"

parking p;
#define COLUMNS 9 // Nombre total de colonnes
service s;
enum
{
  ENOMP,
  EADRESSEP,
  EIDP,
  ECAPACITE,
  EETAT,
  EBLOC,
  ETARIF,
  EABONNEMENT,
  EVEHICULE,
  EACCES,
  EJD,
  EMD,
  EAD,
  EJF,
  EMF,
  EAF,
  
};
//************************************//

enum {
    EID,
    ETYPE,
    EPRIX,
    EPAYMENT,
    EHEURE,
    EJJ,
    EMM,
    EAA,
    ECONFIRMED,
};    
enum {
    EID_SERVICE,
    EID_RESERVATION,
    N_COLUMNS
};



int ajouter(char *filename, parking p) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return 0;
    }
    fprintf(file, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d;\n",
            p.nom, p.adresse, p.id, p.capacite, p.tarif,
            p.etat, p.bloc, p.abonnement, p.vehicule, p.acces,
            p.jd, p.md, p.ad, p.jf, p.mf, p.af);
    fclose(file);
    return 1;
}
int modifier(const char *filename, const char *id, parking nouveau_parking) {
    int tr = 0; // Indicateur de modification
    parking temp_p;
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        perror("Erreur d'ouverture du fichier");
        return 0; // Échec
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        // Lecture des champs
        if (sscanf(buffer, "%49[^;];%49[^;];%19[^;];%9[^;];%9[^;];%19[^;];%19[^;];%19[^;];%19[^;];%9[^;];%d;%d;%d;%d;%d;%d",
                   temp_p.nom, temp_p.adresse, temp_p.id, temp_p.capacite, temp_p.tarif,
                   temp_p.etat, temp_p.bloc, temp_p.abonnement, temp_p.vehicule, temp_p.acces,
                   &temp_p.jd, &temp_p.md, &temp_p.ad, &temp_p.jf, &temp_p.mf, &temp_p.af) == 16) {

            // Comparaison des IDs
            if (strcmp(temp_p.id, id) == 0) {
                fprintf(temp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d\n",
                        nouveau_parking.nom, nouveau_parking.adresse, nouveau_parking.id,
                        nouveau_parking.capacite, nouveau_parking.tarif, nouveau_parking.etat,
                        nouveau_parking.bloc, nouveau_parking.abonnement, nouveau_parking.vehicule,
                        nouveau_parking.acces, nouveau_parking.jd, nouveau_parking.md, nouveau_parking.ad,
                        nouveau_parking.jf, nouveau_parking.mf, nouveau_parking.af);
                tr = 1; // Modification trouvée
            } else {
                fputs(buffer, temp); // Recopie de la ligne existante
            }
        }
    }

    fclose(file);
    fclose(temp);

    if (tr) {
        // Remplacement du fichier original
        if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
            perror("Erreur lors du remplacement du fichier");
            return 0;
        }
    } else {
        remove("temp.txt"); // Suppression du fichier temporaire
    }

    return tr;
}


int supprimer_parking(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (file == NULL || temp == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return 0;
    }

    parking p;
    int found = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file)) {
        sscanf(buffer, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d;%d;%d;",
               p.nom, p.adresse, p.id, p.capacite, p.tarif,
               p.etat, p.bloc, p.abonnement, p.vehicule, &p.acces,
               &p.jd, &p.md, &p.ad, &p.jf, &p.mf, &p.af);

        // Comparer l'ID
        if (strcmp(p.id, id) != 0) {
            fputs(buffer, temp);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
            perror("Erreur lors de la mise à jour du fichier");
            return 0;
        }
        printf("Parking supprimé avec succès.\n");
        return 1;
    } else {
        remove("temp.txt");
        printf("Parking non trouvé.\n");
        return 0;
    }
}
void afficher_Parking(GtkWidget *liste, char *nomp) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    // Variables for storing data
    char nom[100], adresse[100], id[100], capacite[100], tarif[100], etat[100], bloc[100], abonnement[100], vehicule[100];
    char acces[100];
    int jd, md, ad, jf, mf, af;
    char buffer[512];

    // Get the existing model
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {
        // Create a new model if none exists
        store = gtk_list_store_new(16,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_INT,
                                   G_TYPE_INT, G_TYPE_INT, G_TYPE_INT);

        // Add columns only once
        renderer = gtk_cell_renderer_text_new();

        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", ENOMP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Adresse", renderer, "text", EADRESSEP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", EIDP, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Capacité", renderer, "text", ECAPACITE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Tarif", renderer, "text", ETARIF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("État", renderer, "text", EETAT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Bloc", renderer, "text", EBLOC, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Abonnement", renderer, "text", EABONNEMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Véhicule", renderer, "text", EVEHICULE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Accès", renderer, "text", EACCES, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Jour Début", renderer, "text", EJD, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Mois Début", renderer, "text", EMD, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Année Début", renderer, "text", EAD, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Jour Fin", renderer, "text", EJF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Mois Fin", renderer, "text", EMF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        column = gtk_tree_view_column_new_with_attributes("Année Fin", renderer, "text", EAF, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    } else {
 
        gtk_list_store_clear(store);
    }

 
    FILE *f = fopen(nomp, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier : %s\n", nomp);
        return;
    }

 
    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%d;%d;%d;%d;%d;%d\n",
                   nom, adresse, id, capacite, tarif, etat, bloc, abonnement, vehicule, acces,
                   &jd, &md, &ad, &jf, &mf, &af) == 16) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               ENOMP, nom,
                               EADRESSEP, adresse,
                               EIDP, id,
                               ECAPACITE, capacite,
                               ETARIF, tarif,
                               EETAT, etat,
                               EBLOC, bloc,
                               EABONNEMENT, abonnement,
                               EVEHICULE, vehicule,
                               EACCES, acces,
                               EJD, jd,
                               EMD, md,
                               EAD, ad,
                               EJF, jf,
                               EMF, mf,
                               EAF, af,
                               -1);
        }
    }

    fclose(f);

 
    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));

    
}







void chercher_Parking(parking p, const char *text) {
    FILE *f4 = NULL;
    FILE *ff = NULL;
    char line[1024]; // Buffer pour lire les lignes du fichier
    char *token;     // Pointeur pour parcourir les champs
    int field_count; // Nombre de champs dans la ligne

    // Supprimer le fichier de recherche existant
    remove("rechparking.txt");

    // Ouvrir les fichiers
    f4 = fopen("parking.txt", "r");
    if (f4 == NULL) {
        printf("Erreur : Impossible d'ouvrir parking.txt\n");
        return;
    }

    ff = fopen("rechparking.txt", "a");
    if (ff == NULL) {
        printf("Erreur : Impossible de créer rechparking.txt\n");
        fclose(f4);
        return;
    }

    // Lire chaque ligne de parking.txt
    while (fgets(line, sizeof(line), f4) != NULL) {
        // Réinitialiser les champs et le compteur
        field_count = 0;

        // Découper la ligne en champs
        token = strtok(line, ";");
        while (token != NULL) {
            field_count++;

            // Assigner les champs au bon endroit
            switch (field_count) {
                case 1: strcpy(p.nom, token); break;
                case 2: strcpy(p.adresse, token); break;
                case 3: strcpy(p.id, token); break;
                case 4: strcpy(p.capacite, token); break;
                case 5: strcpy(p.tarif, token); break;
                case 6: strcpy(p.etat, token); break;
                case 7: strcpy(p.bloc, token); break;
                case 8: strcpy(p.abonnement, token); break;
                case 9: strcpy(p.vehicule, token); break;
                case 10: strcpy(p.acces, token); break;
                case 11: p.jd = atoi(token); break;
                case 12: p.md = atoi(token); break;
                case 13: p.ad = atoi(token); break;
                case 14: p.jf = atoi(token); break;
                case 15: p.mf = atoi(token); break;
                case 16: p.af = atoi(token); break;
            }

            token = strtok(NULL, ";");
        }

        // Si la ligne contient au moins 16 champs, vérifier l'ID
        if (field_count >= 16 && strcmp(p.id, text) == 0) {
            // Écrire la ligne trouvée dans rechparking.txt
            fprintf(ff, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d;%d;%d;%d;%d;%d;\n",
                    p.nom, p.adresse, p.id, p.capacite, p.tarif, p.etat, p.bloc,
                    p.abonnement, p.vehicule, p.acces,
                    p.jd, p.md, p.ad, p.jf, p.mf, p.af);
        }
    }

    // Fermer les fichiers
    fclose(f4);
    fclose(ff);

    printf("Recherche terminée. Vérifiez rechparking.txt pour les résultats.\n");
}



int verifier(const char *filename, const char *id, parking *result) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return 0; 
    }

    parking p;
    char line[512];

 
    while (fgets(line, sizeof(line), f)) {
 
        char *tokens[16] = {NULL};
        int i = 0;
        char *token = strtok(line, ";");
        while (token && i < 16) {
            tokens[i++] = token;
            token = strtok(NULL, ";");
        }

 
        if (i >= 16) {
            strncpy(p.nom, tokens[0], sizeof(p.nom) - 1);
            strncpy(p.adresse, tokens[1], sizeof(p.adresse) - 1);
            strncpy(p.id, tokens[2], sizeof(p.id) - 1);
            strncpy(p.capacite, tokens[3], sizeof(p.capacite) - 1);
            strncpy(p.tarif, tokens[4], sizeof(p.tarif) - 1);
            strncpy(p.etat, tokens[5], sizeof(p.etat) - 1);
            strncpy(p.bloc, tokens[6], sizeof(p.bloc) - 1);
            strncpy(p.abonnement, tokens[7], sizeof(p.abonnement) - 1);
            strncpy(p.vehicule, tokens[8], sizeof(p.vehicule) - 1);
            strncpy(p.acces, tokens[9], sizeof(p.acces) - 1);
            p.jd = atoi(tokens[10]);
            p.md = atoi(tokens[11]);
            p.ad = atoi(tokens[12]);
            p.jf = atoi(tokens[13]);
            p.mf = atoi(tokens[14]);
            p.af = atoi(tokens[15]);

 
            if (strcmp(p.id, id) == 0) {
                *result = p;
                fclose(f);
                return 1;  
            }
        }
    }

    fclose(f);
    return 0;  
}




int affecter_agent(const char *parking_file, const char *agent_file, const char *id_parking, const char *cin_agent) {
    FILE *f_parking = fopen(parking_file, "r");
    FILE *f_agent = fopen(agent_file, "r");
    FILE *temp_parking = fopen("temp_parking.txt", "w");
    char parking_line[512];
    char agent_line[512];
    int parking_found = 0, agent_found = 0;

 
    if (!f_parking || !f_agent || !temp_parking) {
        printf("Erreur : Impossible d'ouvrir un ou plusieurs fichiers.\n");
        if (f_parking) fclose(f_parking);
        if (f_agent) fclose(f_agent);
        if (temp_parking) fclose(temp_parking);
        return 0;
    }

 
    Agent a;
    while (fgets(agent_line, sizeof(agent_line), f_agent)) {
        sscanf(agent_line, "%s %s %s", a.nom, a.pren, a.cin);
        if (strcmp(a.cin, cin_agent) == 0) {
            agent_found = 1;
            break;
        }
    }
    fclose(f_agent);

    if (!agent_found) {
        printf("Erreur : Agent avec CIN %s introuvable.\n", cin_agent);
        fclose(f_parking);
        fclose(temp_parking);
        remove("temp_parking.txt");
        return 0;
    }

 
    while (fgets(parking_line, sizeof(parking_line), f_parking)) {
        char current_id[100];
        sscanf(parking_line, "%*[^;];%*[^;];%[^;]", current_id); 
        if (strcmp(current_id, id_parking) == 0) {
            parking_found = 1;

 
            char new_parking_line[512];
            snprintf(new_parking_line, sizeof(new_parking_line), "%s;%s;%s\n", 
                     strtok(parking_line, "\n"), a.nom, a.cin);
            fputs(new_parking_line, temp_parking);
        } else {
            fputs(parking_line, temp_parking);  
        }
    }
    fclose(f_parking);
    fclose(temp_parking);

 
    if (parking_found) {
        remove(parking_file);
        rename("temp_parking.txt", parking_file);
        printf("Agent avec CIN %s affecté au parking ID %s avec succès.\n", cin_agent, id_parking);
    } else {
        printf("Erreur : Parking avec ID %s introuvable.\n", id_parking);
        remove("temp_parking.txt");
    }

    return parking_found && agent_found;
}

void afficher_affectations(GtkWidget *ParkingTreeView) {
    FILE *f_parking;
    char line[512];
    char id_parking[50], agent_cin[50];

 
    GtkListStore *store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);  

 
    f_parking = fopen("parking.txt", "r");
    if (!f_parking) {
        printf("Erreur : Impossible d'ouvrir le fichier parking.txt\n");
        return;
    }

 
    while (fgets(line, sizeof(line), f_parking)) {
 
        memset(id_parking, 0, sizeof(id_parking));
        memset(agent_cin, 0, sizeof(agent_cin));

 
        char *tokens[20] = {NULL};
        int i = 0;
        char *token = strtok(line, ";");
        while (token && i < 20) {
            tokens[i++] = token;
            token = strtok(NULL, ";");
        }

 
        if (tokens[2]) strncpy(id_parking, tokens[2], sizeof(id_parking) - 1);  
        if (tokens[i - 1]) strncpy(agent_cin, tokens[i - 1], sizeof(agent_cin) - 1);  

 
        if (strlen(id_parking) > 0 && strlen(agent_cin) > 0) {
            GtkTreeIter iter;
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, id_parking,  
                               1, agent_cin,    
                               -1);
        }
    }

    fclose(f_parking);

 
    gtk_tree_view_set_model(GTK_TREE_VIEW(ParkingTreeView), GTK_TREE_MODEL(store));
    g_object_unref(store);

 
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(ParkingTreeView)) == NULL) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *column;

        column = gtk_tree_view_column_new_with_attributes("ID Parking", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(ParkingTreeView), column);

        column = gtk_tree_view_column_new_with_attributes("CIN Agent", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(ParkingTreeView), column);
    }
}

int loginUser(int id, char *password) {
    login admin;
    FILE *file = fopen("administrateur.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open administrateur.txt\n");
        return -1;
    }

    printf("Reading from administrateur.txt...\n");

    // Loop through the administrators in the file
    while (fscanf(file, "%d %49s", &admin.id_administ, admin.password) != EOF) {
        // Debug: Print the parsed admin
        printf("Parsed admin: ID=%d, Password=%s\n", admin.id_administ, admin.password);

        // Check if the ID and password match
        if (admin.id_administ == id && strcmp(admin.password, password) == 0) {
            fclose(file);  // Close the file before returning
            printf("Login successful for user ID %d\n", admin.id_administ);
            return 1; // Successful login
        }
    }

    // No match found
    fclose(file);
    printf("Login failed. No matching administrator found.\n");
    return 0; // Failed login
}


int ajouterservice(char *filename, service s) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, " %s %s %s %s %s %s %s %s '%s'\n", s.id, s.type, s.prix, s.payment, s.heure ,s.jj, s.mm, s.aa, s.confirmed);
        fclose(f);
        return 1;  
    } else {
        return 0; 
    }
}


void afficher_service(GtkWidget *liste, char *noms) {
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    char id[100];
    char type[100];
    char prix[100];
    char payment[100];
    char heure[100];
    char jj[100];
    char mm[100];
    char aa[100];
    char confirmed[100];

    store = gtk_tree_view_get_model(GTK_TREE_VIEW(liste));

    if (store == NULL) {
        // Configuration des colonnes du TreeView
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", EID, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", ETYPE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prix", renderer, "text", EPRIX, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Payment", renderer, "text", EPAYMENT, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Heure", renderer, "text", EHEURE, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("JJ", renderer, "text", EJJ, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("MM", renderer, "text", EMM, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("AA", renderer, "text", EAA, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Confirmed", renderer, "text", ECONFIRMED, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);
    }

    store = gtk_list_store_new(COLUMNS, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, 
                               G_TYPE_STRING);

    FILE *f = fopen(noms, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", noms);
        return;
    }

    // Lecture des données depuis le fichier
    while (fscanf(f, " %s %s %s %s %s %s %s %s %s",
                  id, type, prix, payment, heure, jj, mm, aa, confirmed) == 9) {
    
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           EID, id,
                           ETYPE, type,
                           EPRIX, prix,
                           EPAYMENT, payment,
                           EHEURE, heure,
                           EJJ, jj,
                           EMM, mm,
                           EAA, aa,
                           ECONFIRMED, confirmed,
                           -1);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}
void modifier_service(service s, int *resultat) {
    char id[100];
    char type[100];
    char prix[100];
    char payment[100];
    char heure[100];
    char jj[100];
    char mm[100];
    char aa[100];
    char confirmed[100];

    FILE *f1 = NULL, *f2 = NULL;
    int id_trouve = 0;  // Variable pour vérifier si l'ID a été trouvé

    // Ouvrir le fichier en lecture
    f1 = fopen("service.txt", "r");
    if (f1 == NULL) {
        perror("Error opening service.txt");
        *resultat = 2; // Échec d'ouverture du fichier service.txt
        return;
    }

    // Ouvrir le fichier en écriture
    f2 = fopen("nouvservice.txt", "w");
    if (f2 == NULL) {
        perror("Error opening nouvservice.txt");
        fclose(f1);
        *resultat = 3; // Échec d'ouverture du fichier nouvservice.txt
        return;
    }

    // Lire le fichier ligne par ligne et modifier si nécessaire
    while (fscanf(f1, "%s %s %s %s %s %s %s %s %s\n", id, type, prix, payment, heure, jj, mm, aa, confirmed) != EOF) {
        if (strcmp(s.id, id) == 0) {
            // Si l'ID correspond, on écrit la nouvelle ligne
            fprintf(f2, "%s %s %s %s %s %s %s %s %s\n", s.id, s.type, s.prix, s.payment, s.heure, s.jj, s.mm, s.aa, s.confirmed);
            id_trouve = 1; // Marquer l'ID comme trouvé
        } else {
            // Sinon, on écrit la ligne actuelle
            fprintf(f2, "%s %s %s %s %s %s %s %s %s\n", id, type, prix, payment, heure, jj, mm, aa, confirmed);
        }
    }

    // Si l'ID n'a pas été trouvé, signaler l'erreur
    if (!id_trouve) {
        fclose(f1);
        fclose(f2);
        remove("nouvservice.txt");  // Supprimer le fichier temporaire
        *resultat = 6; // L'ID n'a pas été trouvé
        return;
    }

    // Fermeture des fichiers
    fclose(f1);
    fclose(f2);

    // Remplacer le fichier original par le nouveau
    if (remove("service.txt") != 0) {
        perror("Error deleting old service.txt");
        *resultat = 4; // Erreur lors de la suppression du fichier original
        return;
    }

    if (rename("nouvservice.txt", "service.txt") != 0) {
        perror("Error renaming nouvservice.txt to service.txt");
        *resultat = 5; // Erreur lors du renommage
        return;
    }

    *resultat = 1; // Succès de la modification
}

int supprimer_Service(const char *filename, const char *id) {
    FILE *file = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    
    if (file == NULL || temp == NULL) {
        perror("Erreur lors de l'ouverture des fichiers");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return 0;
    }

    char id_buffer[100], type[100], prix[100], payment[100], heure[100];
    char jj[100], mm[100], aa[100], confirmed[100];
    int found = 0;

    while (fscanf(file, "%s %s %s %s %s %s %s %s %s\n", 
                  id_buffer, type, prix, payment, heure, 
                  jj, mm, aa, confirmed) != EOF) {
        if (strcmp(id_buffer, id) != 0) {
            // Écrire dans le fichier temporaire si l'ID ne correspond pas
            fprintf(temp, "%s %s %s %s %s %s %s %s %s\n", 
                    id_buffer, type, prix, payment, heure, 
                    jj, mm, aa, confirmed);
        } else {
            found = 1; // Indique que l'ID a été trouvé
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        // Remplacer le fichier d'origine
        if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
            perror("Erreur lors de la mise à jour du fichier");
            return 0;
        }
        printf("Service avec l'ID %s supprimé avec succès.\n", id);
        return 1;
    } else {
        remove("temp.txt"); // Supprimer le fichier temporaire inutile
        printf("Erreur : Service avec l'ID %s introuvable.\n", id);
        return 0;
    }
}





void chercher_service(service s , char text[100])
{
  FILE *f4 = NULL;
  FILE *ff = NULL;
  remove("rechservice.txt");
  f4 = fopen("service.txt", "r");
  ff = fopen("rechservice.txt", "a+");

  if (f4 == NULL || ff == NULL)
  {
    return;
  }

  else
  {

    while (fscanf(f4, "%s %s %s %s %s %s %s %s %s\n",
                s.id, s.type, s.prix, s.payment, s.heure,
                s.jj, s.mm, s.aa, s.confirmed) != EOF)
    {
      if (strcmp(text, s.id) == 0 || strcmp(text, s.type) == 0 )

        fprintf(ff,"%s %s %s %s %s %s %s %s %s\n",
                s.id, s.type, s.prix, s.payment, s.heure,
                s.jj, s.mm, s.aa, s.confirmed);
    }

    fclose(f4);
    fclose(ff);
  }
}

// Fonction pour vérifier si un ID existe dans un fichier
// Fonction pour vérifier si un ID existe dans un fichier
int verifier_id_existe(const char *id, const char *filename, char delimiter) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return 0;
    }

    char ligne[500];
    char id_lu[100];

    // Formater l'ID recherché pour qu'il ait toujours 4 chiffres
    char id_formate_recherche[100];
    sprintf(id_formate_recherche, "%04d", atoi(id)); // Ajoute des zéros si nécessaire

    // Lire chaque ligne du fichier
    while (fgets(ligne, sizeof(ligne), f)) {
        ligne[strcspn(ligne, "\n")] = 0; // Nettoyer la ligne

        // Diviser la ligne en fonction des espaces multiples
        char *token = strtok(ligne, " "); // Le premier mot de la ligne correspond à l'ID
        if (token != NULL) {
            // Formater l'ID extrait pour comparaison
            char id_formate_lu[100];
            sprintf(id_formate_lu, "%04d", atoi(token));

            // Débogage : Afficher l'ID extrait et formaté
            printf("ID extrait de la ligne : '%s', ID recherché : '%s'\n", id_formate_lu, id_formate_recherche);

            if (strcmp(id_formate_recherche, id_formate_lu) == 0) {
                fclose(f);
                return 1; // ID trouvé
            }
        }
    }

    fclose(f);
    return 0; // ID non trouvé
}


// Fonction pour vérifier et remplir la structure service
int verifier_modif(const char *filename, const char *id, service *s) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return 0;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char temp[256];
        strncpy(temp, line, sizeof(temp));

        // Vérification de l'ID
        char *token = strtok(temp, " ");
        if (token && strcmp(token, id) == 0) {
            // ID trouvé, remplir la structure 'service'
            sscanf(line, "%s %s %s %s %s %s %s %s %s",
                   s->id, s->type, s->prix, s->payment,
                   s->heure, s->jj, s->mm, s->aa, s->confirmed);

            // Nettoyage de 'confirmed' pour enlever les apostrophes et espaces
            g_strstrip(s->confirmed);

            fclose(file);
            return 1; // ID trouvé
        }
    }

    fclose(file);
    return 0; // ID non trouvé
}
int affecter(const char *id_service, int id_reservation, const char *service_file, const char *reservation_file, const char *affectation_file) {
    // Vérifier si l'ID du service existe dans service.txt
    if (!verifier_id_existe(id_service, service_file, ' ')) {
        printf("Erreur d'affectation : L'ID du service %s n'existe pas dans %s\n", id_service, service_file);
        return 0;
    }

    // Formater l'ID de réservation pour qu'il ait 4 chiffres
    char id_reservation_str[100];
    sprintf(id_reservation_str, "%04d", id_reservation); // Formater avec 4 chiffres

    // Vérifier si l'ID de la réservation existe dans reservation.txt
    if (!verifier_id_existe(id_reservation_str, reservation_file, '|')) {
        printf("Erreur d'affectation : L'ID de la réservation %s n'existe pas dans %s\n", id_reservation_str, reservation_file);
        return 0;
    }

    // Si les deux ID existent, effectuer l'affectation
    FILE *f = fopen(affectation_file, "a");
    if (f != NULL) {
        fprintf(f, "Service %s affecté à la réservation %s\n", id_service, id_reservation_str);
        fclose(f);
        printf("Affectation réussie : Service %s affecté à la réservation %s\n", id_service, id_reservation_str);
        return 1;
    } else {
        printf("Erreur d'ouverture du fichier %s pour l'affectation\n", affectation_file);
        return 0;
    }
}

void afficher_affectationsservice(GtkWidget *treeview, const char *filename) {
    FILE *file;
    char line[256];
    GtkListStore *store;
    GtkTreeIter iter;

    // Créer une nouvelle liste pour stocker les données
    store = gtk_list_store_new(1, G_TYPE_STRING); // Une seule colonne pour le texte complet

    // Ouvrir le fichier affectation.txt
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    // Lire chaque ligne du fichier et ajouter au TreeView
    while (fgets(line, sizeof(line), file)) {
        // Supprimer le retour à la ligne à la fin de chaque ligne
        line[strcspn(line, "\n")] = '\0'; // Remplacer le \n par \0 pour éviter l'affichage du retour à la ligne

        // Ajouter la ligne lue dans le modèle de liste
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, line, -1); // Ajouter la ligne dans la première colonne
    }

    // Fermer le fichier
    fclose(file);

    // Affecter le modèle de données au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));

    // Libérer la mémoire du modèle après l'utilisation
    g_object_unref(store);

    // Créer la colonne pour afficher le texte
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    // Vérifier si la colonne existe déjà avant de l'ajouter
    if (gtk_tree_view_get_column(GTK_TREE_VIEW(treeview), 0) == NULL) {
        // Colonne unique pour afficher le texte complet
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Affectation", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}
//...............................................................................................................

int ajouter_reserv(char *filename , Reservation1 res){
    FILE *fp = fopen(filename, "a");
    

    if (fp != NULL) {
        fprintf(fp, "%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
                res.id_reservation, res.parking.nom, res.parking.adresse,
                res.place.type,
                res.date_reservation.jour, res.date_reservation.mois, res.date_reservation.annee,
                res.heure_debut.heure, res.heure_debut.minute,
                res.heure_fin.heure, res.heure_fin.minute,
                res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                res.service.demande_service, res.service.paiement);
        fclose(fp);
        return 1;                                                                                                                                 
    } else {
        
        printf("Erreur d'ouverture du fichier");
    } return 0;
}

void afficher_reserv(char *filename){
    FILE *fp = fopen(filename, "r");
    Reservation1 res;
     
    
    if (fp != NULL) {
 while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                      res.id_reservation, res.parking.nom, res.parking.adresse,
                     res.place.type,
                     &res.date_reservation.jour, &res.date_reservation.mois,
                     &res.date_reservation.annee, &res.heure_debut.heure,
                     &res.heure_debut.minute, &res.heure_fin.heure, &res.heure_fin.minute,
                     res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                     res.service.demande_service, res.service.paiement) != EOF) {
printf("%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
             res.id_reservation, res.parking.nom,res.parking.adresse,
                res.place.type,
                res.date_reservation.jour, res.date_reservation.mois, res.date_reservation.annee,
                res.heure_debut.heure, res.heure_debut.minute,
                res.heure_fin.heure, res.heure_fin.minute,
                res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                res.service.demande_service, res.service.paiement);
           
        
     }
     fclose(fp);

 }
}
 void chercher(char *filename, char *id){
      FILE *fp = fopen(filename, "r");
       Reservation1 res;

         int tr = 0;

    if (fp != NULL) {
         while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                      res.id_reservation, res.parking.nom, res.parking.adresse,
                     res.place.type,
                     &res.date_reservation.jour, &res.date_reservation.mois,
                     &res.date_reservation.annee, &res.heure_debut.heure,
                     &res.heure_debut.minute, &res.heure_fin.heure, &res.heure_fin.minute,
                     res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                     res.service.demande_service, res.service.paiement) != EOF) {
           
            // Enlever les espaces et retours à la ligne potentiels
            res.id_reservation[strcspn(res.id_reservation, "\n")] = '\0';
            res.id_reservation[strcspn(res.id_reservation, " ")] = '\0';
           
            // Debug
            printf("ID lu: '%s'\n", res.id_reservation);
            printf("Résultat de strcmp: %d\n", strcmp(res.id_reservation, id));
             if(strcmp(res.id_reservation, id) == 0) {
                printf("Id trouvé \n");
                tr=1;   }
             else{ 
                   tr=0;
                    printf("Id na pas ete trouvé\n"); }
                                                      }
            fclose(fp);
                      }
        else{
            printf("erreur d'ouverture du fichier");
                                                   }
                                                   }
void supprimer_reserv(char *filename, char *id) {
    FILE *fp = fopen(filename, "r");
    FILE *fp2 = fopen("hass.txt", "w");
    Reservation1 res;
    int tr = 0;

    // Ajouter ces lignes de debug
    printf("ID à supprimer: '%s'\n", id);

    if (fp != NULL && fp2 != NULL) {
        while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                      res.id_reservation, res.parking.nom, res.parking.adresse,
                     res.place.type,
                     &res.date_reservation.jour, &res.date_reservation.mois,
                     &res.date_reservation.annee, &res.heure_debut.heure,
                     &res.heure_debut.minute, &res.heure_fin.heure, &res.heure_fin.minute,
                     res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                     res.service.demande_service, res.service.paiement) != EOF) {
           
            // Enlever les espaces et retours à la ligne potentiels
            res.id_reservation[strcspn(res.id_reservation, "\n")] = '\0';
            res.id_reservation[strcspn(res.id_reservation, " ")] = '\0';
           
            // Debug
            printf("ID lu: '%s'\n", res.id_reservation);
            printf("Résultat de strcmp: %d\n", strcmp(res.id_reservation, id));

            if (strcmp(res.id_reservation, id) != 0) {
                fprintf(fp2, "%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
                       res.id_reservation, res.parking.nom, res.parking.adresse,
                       res.place.type,
                       res.date_reservation.jour, res.date_reservation.mois,
                       res.date_reservation.annee, res.heure_debut.heure,
                       res.heure_debut.minute, res.heure_fin.heure, res.heure_fin.minute,
                       res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                       res.service.demande_service, res.service.paiement);
            } else {
                tr = 1;
                printf("Élément trouvé et sera supprimé\n");
            }
        }

        fclose(fp);
        fclose(fp2);

        if (tr == 1) {
            remove(filename);
            rename("hass.txt", filename);
            printf("Suppression effectuée avec succès\n");
        } else {
            remove("hass.txt");
            printf("ID non trouvé dans le fichier\n");
        }
    } else {
        printf("Erreur d'ouverture des fichiers\n");
    }
}

	




         Reservation1 cherche(char *filename, char *id) {
    FILE *fp = fopen(filename, "r");
    Reservation1 res ; 

    if (fp != NULL) {
          while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                      res.id_reservation, res.parking.nom, res.parking.adresse,
                     res.place.type,
                     &res.date_reservation.jour, &res.date_reservation.mois,
                     &res.date_reservation.annee, &res.heure_debut.heure,
                     &res.heure_debut.minute, &res.heure_fin.heure, &res.heure_fin.minute,
                     res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                     res.service.demande_service, res.service.paiement) != EOF) {
           
            // Enlever les espaces et retours à la ligne potentiels
            res.id_reservation[strcspn(res.id_reservation, "\n")] = '\0';
            res.id_reservation[strcspn(res.id_reservation, " ")] = '\0';
           
            // Debug
            printf("ID lu: '%s'\n", res.id_reservation);
            printf("Résultat de strcmp: %d\n", strcmp(res.id_reservation, id));
            if (strcmp(res.id_reservation,id) == 0) {
                printf("id trouvé :%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
                       res.id_reservation, res.parking.nom, res.parking.adresse,
                       res.place.type,
                       res.date_reservation.jour, res.date_reservation.mois,
                       res.date_reservation.annee, res.heure_debut.heure,
                       res.heure_debut.minute, res.heure_fin.heure, res.heure_fin.minute,
                       res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                       res.service.demande_service, res.service.paiement);
                fclose(fp);
                return res ; // Retour immédiat si le code est trouvé
            }
        }
        fclose(fp);
        printf("Id non trouvé dans le fichier.\n");
    } else {
        printf("Erreur d'ouverture du fichier : %s\n", filename);
    }

    return res  ; // Retourne un Film initialisé à des valeurs par défaut si non trouvé
}
    


   void modifier_reserv(char *filename, char *id, Reservation1 nouvelleres){
    FILE *fp = fopen(filename, "r");
    FILE *fp2 = fopen("m.txt", "w");
    Reservation1 res;
    
    int tr = 0;

    if (fp != NULL && fp2 != NULL) {
        while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                     res.id_reservation, res.parking.nom, res.parking.adresse,
                     res.place.type,
                     &res.date_reservation.jour, &res.date_reservation.mois,
                     &res.date_reservation.annee, &res.heure_debut.heure,
                     &res.heure_debut.minute, &res.heure_fin.heure, &res.heure_fin.minute,
                     res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                     res.service.demande_service, res.service.paiement) != EOF) {
           
            // Enlever les espaces et retours à la ligne potentiels
            res.id_reservation[strcspn(res.id_reservation, "\n")] = '\0';
            res.id_reservation[strcspn(res.id_reservation, " ")] = '\0';
           
            // Debug
            printf("ID lu: '%s'\n", res.id_reservation);
            printf("Résultat de strcmp: %d\n", strcmp(res.id_reservation, id));

            if (strcmp(res.id_reservation, id) == 0) {
                fprintf(fp2, "%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
                       res.id_reservation, nouvelleres.parking.nom, nouvelleres.parking.adresse,
                       nouvelleres.place.type,
                       nouvelleres.date_reservation.jour, nouvelleres.date_reservation.mois,
                       nouvelleres.date_reservation.annee, nouvelleres.heure_debut.heure,
                       nouvelleres.heure_debut.minute, nouvelleres.heure_fin.heure, nouvelleres.heure_fin.minute,
                       nouvelleres.place.bloc, nouvelleres.vehicule.type, nouvelleres.vehicule.matricule,
                       nouvelleres.service.demande_service, nouvelleres.service.paiement);
                        tr = 1;
            } else {
                // Garder la réservation inchangée
                fprintf(fp2, "%s|%s|%s|%s|%d/%d/%d|%d:%d|%d:%d|%s|%s|%s|%s|%s\n",
                       res.id_reservation, res.parking.nom, res.parking.adresse,
                       res.place.type,
                       res.date_reservation.jour, res.date_reservation.mois,
                       res.date_reservation.annee, res.heure_debut.heure,
                       res.heure_debut.minute, res.heure_fin.heure, res.heure_fin.minute,
                       res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                       res.service.demande_service, res.service.paiement);
            }
        }
         fclose(fp);
        fclose(fp2);

        if (tr == 1) {
            if (remove(filename) != 0) {
                perror("Erreur lors de la suppression du fichier original");
            } else if (rename("m.txt", filename) != 0) {
                perror("Erreur lors du renommage du fichier temporaire");
            } else {
                printf("Modification effectuée avec succès\n");
            }
        } else {
            remove("m.txt");
            printf("ID non trouvé dans le fichier\n");
        }
    } else {
        printf("Erreur d'ouverture des fichiers\n");
        if (fp != NULL) fclose(fp);
        if (fp2 != NULL) fclose(fp2);
    }
}

  void afficher_reservation(GtkTreeView *treeview, const char *filename) {
    // Ouverture du fichier
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        g_print("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    // Déclaration des variables
    Reservation1 res; // Structure contenant toutes les données nécessaires
    GtkListStore *list_store;
    GtkTreeIter iter;

    // Création d'un nouveau modèle avec quatre colonnes
    list_store = gtk_list_store_new(4, 
                                    G_TYPE_STRING,  // Colonne 1 : ID de réservation
                                    G_TYPE_STRING,  // Colonne 2 : Nom du parking
                                    G_TYPE_STRING,  // Colonne 3 : Date de réservation
                                    G_TYPE_STRING); // Colonne 4 : Statut

    // Lecture du fichier ligne par ligne et ajout au modèle
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  res.id_reservation, 
                  res.parking.nom, 
                 res.parking.adresse, 
                  res.place.bloc) != EOF) {
        gtk_list_store_append(list_store, &iter); // Ajout d'une nouvelle ligne
        gtk_list_store_set(list_store, &iter,
                           0, res.id_reservation,  // Colonne 0 : ID de réservation
                           1, res.parking.nom,     // Colonne 1 : Nom du parking
                           2,  res.parking.adresse, // Colonne 2 : Date
                           3, res.place.bloc,          // Colonne 3 : Statut
                           -1);
    }
    fclose(fp); // Fermeture du fichier

    // Nettoyage de l'ancien modèle (s'il existe déjà)
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (old_model) {
        g_object_unref(old_model);
    }

    // Associer le nouveau modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));

    // Ajouter les colonnes si elles n'existent pas déjà
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        // Colonne 1 : ID
        GtkTreeViewColumn *col_id = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col_id);

        // Colonne 2 : Nom
        GtkTreeViewColumn *col_nom = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col_nom);

        // Colonne 3 : Date
        GtkTreeViewColumn *col_adresse = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),col_adresse);

        // Colonne 4 : Statut
        GtkTreeViewColumn *col_bloc = gtk_tree_view_column_new_with_attributes("bloc", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview),col_bloc);
    }

    // Libérer le modèle local (pour éviter des fuites mémoire)
    g_object_unref(list_store);
}

    void affichage_reservation(GtkTreeView *treeview, const char *filename) {
    // Ouverture du fichier
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        g_print("Erreur : Impossible d'ouvrir le fichier %s.\n", filename);
        return;
    }

    // Déclaration des variables
    Reservation1 res; // Structure contenant toutes les données nécessaires
    GtkListStore *list_store;
    GtkTreeIter iter;

    // Création d'un nouveau modèle avec les colonnes nécessaires
    list_store = gtk_list_store_new(16,
                                    G_TYPE_STRING,  // Colonne 0 : ID réservation
                                    G_TYPE_STRING,  // Colonne 1 : Nom parking
                                    G_TYPE_STRING,  // Colonne 2 : Adresse parking
                                    G_TYPE_STRING,  // Colonne 3 : Type de place
                                    G_TYPE_INT,     // Colonne 4 : Jour de réservation
                                    G_TYPE_INT,     // Colonne 5 : Mois de réservation
                                    G_TYPE_INT,     // Colonne 6 : Année de réservation
                                    G_TYPE_INT,     // Colonne 7 : Heure début
                                    G_TYPE_INT,     // Colonne 8 : Minute début
                                    G_TYPE_INT,     // Colonne 9 : Heure fin
                                    G_TYPE_INT,     // Colonne 10 : Minute fin
                                    G_TYPE_STRING,  // Colonne 11 : Bloc
                                    G_TYPE_STRING,  // Colonne 12 : Type véhicule
                                    G_TYPE_STRING,  // Colonne 13 : Matricule
                                    G_TYPE_STRING,  // Colonne 14 : Demande service
                                    G_TYPE_STRING); // Colonne 15 : Paiement

    // Lecture du fichier ligne par ligne
    while (fscanf(fp, "%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%d:%d|%d:%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  res.id_reservation, res.parking.nom, res.parking.adresse,
                  res.place.type,
                  &res.date_reservation.jour, &res.date_reservation.mois, &res.date_reservation.annee,
                  &res.heure_debut.heure, &res.heure_debut.minute,
                  &res.heure_fin.heure, &res.heure_fin.minute,
                  res.place.bloc, res.vehicule.type, res.vehicule.matricule,
                  res.service.demande_service, res.service.paiement) != EOF) {
        gtk_list_store_append(list_store, &iter);
        gtk_list_store_set(list_store, &iter,
                           0, res.id_reservation,
                           1, res.parking.nom,
                           2, res.parking.adresse,
                           3, res.place.type,
                           4, res.date_reservation.jour,
                           5, res.date_reservation.mois,
                           6, res.date_reservation.annee,
                           7, res.heure_debut.heure,
                           8, res.heure_debut.minute,
                           9, res.heure_fin.heure,
                           10, res.heure_fin.minute,
                           11, res.place.bloc,
                           12, res.vehicule.type,
                           13, res.vehicule.matricule,
                           14, res.service.demande_service,
                           15, res.service.paiement,
                           -1);
    }

    fclose(fp); // Fermeture du fichier

    // Nettoyage de l'ancien modèle (s'il existe déjà)
    GtkTreeModel *old_model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));
    if (old_model) {
        g_object_unref(old_model);
    }

    // Associer le nouveau modèle au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));

    // Ajouter les colonnes si elles n'existent pas déjà
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        // Création et ajout des colonnes
        const char *column_titles[] = {
            "ID", "Nom", "Adresse", "Type de Place",
            "Jour", "Mois", "Année",
            "Heure Début", "Minute Début", "Heure Fin", "Minute Fin",
            "Bloc", "Type Véhicule", "Matricule", "Service", "Paiement"
        };

        for (int i = 0; i < 16; i++) {
            GtkTreeViewColumn *col = gtk_tree_view_column_new_with_attributes(column_titles[i], renderer, "text", i, NULL);
            gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), col);
        }
    }

    // Libération de la mémoire associée au modèle
    g_object_unref(list_store);
}




    
int ajouter_abonnement(char *filename , Reservation1 res){
    FILE *fp = fopen(filename, "a");
    

    if (fp != NULL) {
        fprintf(fp, "%s|%d/%d/%d|%s|%s\n",
                res.type_abnmt, 
                
                res.date_reservation.jour, res.date_reservation.mois, res.date_reservation.annee,
               
                
                res.service.demande_service, res.service.paiement);
        fclose(fp);
        return 1;                                                                                                                                 
    } else {
        
        printf("Erreur d'ouverture du fichier");
    } return 0;
}
   
   int calcul_abonnement( Reservation1 res){
int tarif=0;
       
     if (strcmp( res.type_abnmt, "Mensuel")==0){
        tarif=55; 
                                      }
       if (strcmp(res.type_abnmt, "Trimestriel")==0){
      tarif=150;
                                      }
        if (strcmp(res.type_abnmt, "Annuel")==0){
        tarif=550;
                                      }
         
   return tarif;
}
   


  int ajouter_client_admninistrateur(char *filename , Login l){
    FILE *fp = fopen(filename, "a");
    

    if (fp != NULL) {
        fprintf(fp, "%s|%s|%s\n",
                l.nom,l.prenom,l.mdp);
        fclose(fp);
        return 1;                                                                                                                                 
    } else {
        
        printf("Erreur d'ouverture du fichier");
    } return 0;
}







int verifier_mdp_fichier(char *filename,  char *mdp) {
     FILE *fp = fopen(filename, "r");
   Login l;

 
    if (fp == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n",filename);
        return 0;
    }

    while (fscanf(fp, "%[^|]|%[^|]|%[^\n]\n",
                l.nom,l.prenom,l.mdp) != EOF) {
        if (strcmp(mdp,l.mdp) == 0) {
            fclose(fp);
            return 1; // Mot de passe trouvé
        }
    }

    fclose(fp);
    return 0; // Mot de passe non trouvé
}



