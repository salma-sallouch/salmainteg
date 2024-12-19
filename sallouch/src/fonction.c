#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"fonction.h"
#include <gtk/gtk.h>
int is_valid_cin(const char *cin) {
    int length = strlen(cin);

    if (length != 8) {
        return 0;
    }

    for (int i = 0; i < length; i++) {
        if (!isdigit(cin[i])) {
            return 0;
        }
    }

    return 1;
}
enum
{ 
	EID,
	ENOM,
	EPRENOM,
	EJOUR,
	EMOIS,
	EANNEE,
	ESEXE,
        EADRESSE,
        EMDP,
        EEMAIL,
	COLUMNS,
};

//Ajouter


void ajouter_cit(citoyen b,char *cit){
FILE * f;
f=fopen(cit,"a");

  fprintf(f,"%s %s %s %d %s %d %s %s %s %s  \n ",b.id,b.nom,b.prenom,b.jour,b.mois,b.annee,b.sexe, b.adresse,b.mdp , b.email);
  fclose(f);
}


//Afficher

void afficher_cit(GtkWidget *liste){
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char nom[30];
	
	char prenom[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char sexe[30];
        char adresse[50];
        char mdp[50];
        char email[50];

	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);




	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text",EADRESSE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("email", renderer, "text",EEMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,    G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING , G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("citoyen.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("citoyen.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s   %s %s  %s\n",id,prenom,nom,jour,mois,annee,sexe,adresse,mdp,email)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID,id, EPRENOM, prenom, ENOM, nom, EJOUR, jour, EMOIS, mois ,EANNEE ,annee,  ESEXE, sexe , EADRESSE ,adresse , EMDP , mdp ,EEMAIL, email,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
}

//Modifier

void modifier_cit(char id[],citoyen b1,char *cit)
{
citoyen b;
  FILE* f=fopen(cit, "r");
  FILE* f2=fopen("citmod.txt", "w");
  
  if((f!=NULL) ||( f2!=NULL))
 {
while(fscanf(f,"%s %s %s %d %s %d %s  %s %s %s \n ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe,b.adresse,b.mdp,b.email)!=EOF)
{
if(strcmp(b.id,b1.id)==0)
  fprintf(f2,"%s %s %s %d %s %d %s %s %s %s \n ",b1.id,b1.nom,b1.prenom,&b1.jour,b1.mois,&b1.annee,b1.sexe,b1.adresse , b1.mdp , b1.email);
else
 fprintf(f2,"%s %s %s %d %s %d %s \n ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe,b.adresse,b.mdp,b.email);
}
   fclose(f);
   fclose(f2);
remove(cit);
rename("citmod.txt",cit);
 }
}

//supprimer

void supprimer_cit(char id[],char *cit)
{
citoyen b;     
FILE * f=fopen(cit,"r");
FILE * f2=fopen("citsupp.txt","w");

while (fscanf(f,"%s %s %s %d %s %d %s %s %s %s\n  ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe , b.adresse , b.mdp , b.email )!=EOF)
{

if(strcmp(b.id,id)!=0)

  fprintf(f2,"%s %s %s %d %s %d %s %s %s %s\n  ",b.id,b.nom,b.prenom,&b.jour,b.mois,&b.annee,b.sexe ,b.adresse , b.mdp , b.email );
}
  fclose(f);

  fclose(f2);

remove(cit);
rename("citsupp.txt",cit);

 
}
//fonction remplir tab
// Function to fill the array with citizen data from file
int remplirtabRech(citoyen tab[], int nb)
{
    char nom[20], prenom[20], id[20], mois[20], sexe[30], adresse[50], mdp[50], email[50];
    int jour, annee;
    FILE* fichier;
    int i = 0;

    fichier = fopen("citoyen.txt", "r");  // Use read mode

    if (fichier == NULL) {
        printf("Error: Could not open file 'citoyen.txt'.\n");
        return nb;
    }

    // Read data from the file and fill the array
    while (fscanf(fichier, "%s %s %s %d %s %d %s %s %s %s\n", id, nom, prenom, &jour, mois, &annee, sexe, adresse, mdp, email) != EOF)
    {
        if (i >= 100) break;  // Prevent overflow

        strcpy(tab[i].id, id);
        strcpy(tab[i].nom, nom);
        strcpy(tab[i].prenom, prenom);
        tab[i].jour = jour;
        strcpy(tab[i].mois, mois);
        tab[i].annee = annee;
        strcpy(tab[i].sexe, sexe);
        strcpy(tab[i].adresse, adresse);
        strcpy(tab[i].mdp, mdp);
        strcpy(tab[i].email, email);

        nb++;
        i++;
    }

    fclose(fichier);
    return nb;
}

// Function to search for a citizen by id
int rechercher_cit(char id[])
{
    citoyen tab[100];
    int nb = 0;
    int ce = 0, i;
    FILE *f;

    nb = remplirtabRech(tab, nb);

    for (i = 0; i < nb; i++) {
        if (strcmp(id, tab[i].id) == 0 || strcmp(id, tab[i].nom) == 0 || strcmp(id, tab[i].prenom) == 0) {
            ce = 1;
            f = fopen("rechcit.txt", "w+");

            if (f != NULL) {
                fprintf(f, "%s %s %s %d %s %d %s %s %s %s\n", tab[i].id, tab[i].nom, tab[i].prenom, tab[i].jour, tab[i].mois,
                        tab[i].annee, tab[i].sexe, tab[i].adresse, tab[i].mdp, tab[i].email);
                fclose(f);
            } else {
                printf("Error: Could not open file 'rechcit.txt'.\n");
            }
        }
    }

    return ce;
}

//AFF RECH
void afficher_rechercher_cit(GtkWidget *liste)
{
GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	
	GtkTreeIter iter;
	GtkListStore *store;
	char id[10];
	char nom[30];
	
	char prenom[10];
	char jour[10];
	char mois[30];
	char annee[30];
	char sexe[30];
        char adresse[50];
        char mdp[50];
        char email[50];   
	
	store=NULL;
	FILE *f;
	store=gtk_tree_view_get_model (liste);
	if (store==NULL)
	{


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("id", renderer, "text",EID,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);




	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("prenom", renderer, "text",EPRENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("nom", renderer, "text",ENOM,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	

	

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("jour", renderer, "text",EJOUR,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);


	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mois", renderer, "text",EMOIS,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("annee", renderer, "text",EANNEE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

	renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("sexe", renderer, "text",ESEXE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("adresse", renderer, "text",EADRESSE,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("mdp", renderer, "text",EMDP,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);

        renderer = gtk_cell_renderer_text_new();
	column = gtk_tree_view_column_new_with_attributes("email", renderer, "text",EEMAIL,NULL);
	gtk_tree_view_append_column (GTK_TREE_VIEW (liste),column);
	

	}
	store=gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,   G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING,G_TYPE_STRING, G_TYPE_STRING,  G_TYPE_STRING);
	f=fopen("rechcit.txt","r");
	if(f==NULL)
	{
		return;
	}
	else
	{
		f= fopen("rechcit.txt","a+");
		while(fscanf(f,"%s %s %s %s %s %s %s %s %s %s  \n",id,nom,prenom,jour,mois,annee,sexe,adresse , mdp ,email)!=EOF)
		{
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store,&iter, EID, id, ENOM,nom, EPRENOM, prenom, EJOUR, jour, EMOIS,  mois,EANNEE ,annee,  ESEXE,sexe,EADRESSE,adresse,EMDP,mdp ,EEMAIL, email ,-1);
		}
		fclose(f);
		gtk_tree_view_set_model (GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
		g_object_unref (store);
	}
	
}
        

float calculer_facture(char *filename, char *idd) {
    Facture c;
    float tot = 0.0; // Initialize tot to avoid returning an uninitialized value
    int found = 0;

    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        perror("Failed to open file");
        return -1; // Return a negative value for errors
    }

    // Correct fscanf statement: expecting 6 fields (2 strings, 1 int, 2 floats, 1 float)
    while (fscanf(f, "%99s %99s %d %f %f %f", 
                  c.id_citoyen, c.id_parking, &c.nb_jours, &c.tarif_par_jour, 
                  &c.services, &c.reduction) == 6) {
        if (strcmp(c.id_citoyen, idd) == 0) {
            tot = ((c.nb_jours * c.tarif_par_jour) - c.reduction) + c.services;
            found = 1;
            break;
        }
    }

    fclose(f);  // Properly close the file after usage

    if (!found) {
        fprintf(stderr, "Citizen ID %s not found in the file.\n", idd);
        return -1; // Return a negative value to indicate not found
    }

    return tot;
}
int search_user(const char *filename, const char *cin, citoyen *result) {
    citoyen p;
    FILE *f = fopen(filename, "r");

    if (f == NULL) {
        return 0; // File not found
    }

    // Read the file and compare each citizen's cin
    while (fscanf(f, "%s %s %s %d %s %d %s %s %s %s \n", 
                  p.id, p.prenom, p.nom, p.mois, p.annee, 
                  p.sexe, p.adresse , p.mdp, p.email) != EOF) {
        // Check if the current citizen's cin matches the input
        if (strcmp(p.id, cin) == 0) {
            // Copy the matched data into the result structure
            *result = p;
            fclose(f);
            return 1; // ID found
        }
    }

    fclose(f);
    return 0; // ID not found
}




