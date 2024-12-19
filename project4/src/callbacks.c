#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include <string.h>
#include <gtk/gtk.h>
#include "aycem.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"
int camion = 0;
int moto = 0;
int voiture = 0;
int acces = 0;
parking p1;
parking p;

service s1;
 Reservation r1 ;
int carte; 
int heure;
int confirm;
int espece;
 Reservation1 res ;

void
on_treeviewparking_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

    GtkTreeIter iter;
    gchar *nom;
    gchar *adresse;
    gchar *id;
    gchar *etat;
    gchar *capacite;
    gchar *bloc;
    gchar *tarif;
    gchar *abonnement;
    gchar *vehicule;
    gchar *acces;
    gint *jd;
    gint *md;
    gint *ad;
    gint *jf;
    gint *mf;
    gint *af;


   parking p;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &nom, 1, &adresse, 2, &id, 3, &etat, 4, &capacite, 5, &bloc, 6, &tarif, 7, &abonnement,8,&vehicule,  9, &acces, 10, &jd,11, &md, 12, &ad,13, &jf, 14, &mf, 15, &af, -1);

        strcpy(p.nom, nom);
        strcpy(p.adresse, adresse);

        strcpy(p.id,id);
        strcpy(p.etat, etat);
        strcpy(p.capacite,capacite);
        strcpy(p.bloc,bloc);
        strcpy(p.tarif,tarif);
strcpy(p.abonnement,abonnement);
        strcpy(p.vehicule,vehicule);
        strcpy(p.acces,acces);
        jd=p.jd;
        md=p.md;
        ad=p.ad;
        jf=p.jf;
        mf=p.mf;
        af=p.af;
        p1=p;
    }
}


void
on_ajotaff_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_Chercher_Parking_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{ parking p;
    char text[100];
    GtkWidget *treeviewparking;
    GtkWidget *input;

 
    input = lookup_widget(button, "trouverparkingp");
    strcpy(text, gtk_entry_get_text(GTK_ENTRY(input)));

 
    if (strlen(text) == 0) {
        printf("Erreur : Aucun texte saisi pour la recherche.\n");
        return;
    }

 
    treeviewparking = lookup_widget(button, "treeviewparking");
    chercher_Parking(p, text);

 
    afficher_Parking(treeviewparking, "rechparking.txt");
}



void
on_actualiseraff_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeviewparking;
    treeviewparking = lookup_widget(button, "treeviewparking");

 
    afficher_Parking(treeviewparking, "parking.txt");
}


void
on_affecteraff_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
/*gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "idpagentry20")), p.id);*/
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_suppaff_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
/*gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "idsuppentry12")), p1.id);*/
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_modifaff_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
/*gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "entry4")), p1.id);*/
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        camion = 2;
    }
}


void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        moto = 3;
    }
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{parking p;
if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(p.acces, "oui");
    }
}


void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(togglebutton)) {
        voiture = 1;
    }
}


void
on_annulerajoutp_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *nompentry2, *adrpentry3, *entry4, *capacitepaentry5, *tarifpaentry6;
    GtkWidget *etatpcomboboxentry1, *blocpacomboboxentry2, *abonpacomboboxentry3;
    GtkWidget *spin1, *spin2, *spin3, *spin4, *spin5, *spin6;


    nompentry2 = lookup_widget(GTK_WIDGET(button), "nompentry2");
    adrpentry3 = lookup_widget(GTK_WIDGET(button), "adrpentry3");
    entry4 = lookup_widget(GTK_WIDGET(button), "entry4");
    capacitepaentry5 = lookup_widget(GTK_WIDGET(button), "capacitepaentry5");
    tarifpaentry6 = lookup_widget(GTK_WIDGET(button), "tarifpaentry6");

    spin1 = lookup_widget(GTK_WIDGET(button), "spin1");
    spin2 = lookup_widget(GTK_WIDGET(button), "spin2");
    spin3 = lookup_widget(GTK_WIDGET(button), "spin3");
    spin4 = lookup_widget(GTK_WIDGET(button), "spin4");
    spin5 = lookup_widget(GTK_WIDGET(button), "spin5");
    spin6 = lookup_widget(GTK_WIDGET(button), "spin6");

    etatpcomboboxentry1 = lookup_widget(GTK_WIDGET(button), "etatpcomboboxentry1");
    blocpacomboboxentry2 = lookup_widget(GTK_WIDGET(button), "blocpacomboboxentry2");
    abonpacomboboxentry3 = lookup_widget(GTK_WIDGET(button), "abonpacomboboxentry3");


    gtk_entry_set_text(GTK_ENTRY(nompentry2), "");
    gtk_entry_set_text(GTK_ENTRY(adrpentry3), "");
    gtk_entry_set_text(GTK_ENTRY(entry4), "");
    gtk_entry_set_text(GTK_ENTRY(capacitepaentry5), "");
    gtk_entry_set_text(GTK_ENTRY(tarifpaentry6), "");

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin1), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin2), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin3), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin4), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin5), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin6), 0);

    gtk_combo_box_set_active(GTK_COMBO_BOX(etatpcomboboxentry1), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(blocpacomboboxentry2), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(abonpacomboboxentry3), -1);

    g_print("Ajout annulé et formulaire réinitialisé.\n");
}


void
on_ajouterp_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
  parking p;
    GtkWidget *nompentry2, *adrpentry3, *entry4, *capacitepaentry5, *tarifpaentry6;
    GtkWidget *etatpcomboboxentry1, *blocpacomboboxentry2, *abonpacomboboxentry3;
    GtkWidget *spin1, *spin2, *spin3, *spin4, *spin5, *spin6;
    GtkWidget *radiobutton1, *radiobutton2, *radiobutton3;
    GtkWidget *checkbutton1;

    // Récupération des widgets
    nompentry2 = lookup_widget(GTK_WIDGET(button), "nompentry2");
    adrpentry3 = lookup_widget(GTK_WIDGET(button), "adrpentry3");
    entry4 = lookup_widget(GTK_WIDGET(button), "entry4");
    capacitepaentry5 = lookup_widget(GTK_WIDGET(button), "capacitepaentry5");
    tarifpaentry6 = lookup_widget(GTK_WIDGET(button), "tarifpaentry6");

    spin1 = lookup_widget(GTK_WIDGET(button), "spin1");
    spin2 = lookup_widget(GTK_WIDGET(button), "spin2");
    spin3 = lookup_widget(GTK_WIDGET(button), "spin3");
    spin4 = lookup_widget(GTK_WIDGET(button), "spin4");
    spin5 = lookup_widget(GTK_WIDGET(button), "spin5");
    spin6 = lookup_widget(GTK_WIDGET(button), "spin6");

    etatpcomboboxentry1 = lookup_widget(GTK_WIDGET(button), "etatpcomboboxentry1");
    blocpacomboboxentry2 = lookup_widget(GTK_WIDGET(button), "blocpacomboboxentry2");
    abonpacomboboxentry3 = lookup_widget(GTK_WIDGET(button), "abonpacomboboxentry3");

    radiobutton1 = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radiobutton2 = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    radiobutton3 = lookup_widget(GTK_WIDGET(button), "radiobutton3");

    checkbutton1 = lookup_widget(GTK_WIDGET(button), "checkbutton1");

    // Vérification des champs vides
    if (strlen(gtk_entry_get_text(GTK_ENTRY(nompentry2))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(adrpentry3))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(entry4))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(capacitepaentry5))) == 0 ||
        strlen(gtk_entry_get_text(GTK_ENTRY(tarifpaentry6))) == 0 ||
        gtk_combo_box_get_active(GTK_COMBO_BOX(etatpcomboboxentry1)) == -1 ||
        gtk_combo_box_get_active(GTK_COMBO_BOX(blocpacomboboxentry2)) == -1 ||
        gtk_combo_box_get_active(GTK_COMBO_BOX(abonpacomboboxentry3)) == -1) {
       
        // Affichage du message d'erreur
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                         GTK_DIALOG_MODAL,
                                                         GTK_MESSAGE_ERROR,
                                                         GTK_BUTTONS_OK,
                                                         "Veuillez remplir tous les champs !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return; // Sortir de la fonction si un champ est vide
    }

    // Remplissage de la structure parking
    strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(nompentry2)));
    strcpy(p.adresse, gtk_entry_get_text(GTK_ENTRY(adrpentry3)));
    strcpy(p.id, gtk_entry_get_text(GTK_ENTRY(entry4)));
    strcpy(p.capacite, gtk_entry_get_text(GTK_ENTRY(capacitepaentry5)));
    strcpy(p.tarif, gtk_entry_get_text(GTK_ENTRY(tarifpaentry6)));

    strcpy(p.etat, gtk_combo_box_get_active_text(GTK_COMBO_BOX(etatpcomboboxentry1)));
    strcpy(p.bloc, gtk_combo_box_get_active_text(GTK_COMBO_BOX(blocpacomboboxentry2)));
    strcpy(p.abonnement, gtk_combo_box_get_active_text(GTK_COMBO_BOX(abonpacomboboxentry3)));

    p.jd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin1));
    p.md = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin2));
    p.ad = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin3));
    p.jf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin4));
    p.mf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin5));
    p.af = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin6));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1))) {
        strcpy(p.vehicule, "voiture");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2))) {
        strcpy(p.vehicule, "camion");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton3))) {
        strcpy(p.vehicule, "moto");
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton1))) {
        strcpy(p.acces, "oui");
    } else {
        strcpy(p.acces, "non");
    }

    // Ajouter le parking
    if (ajouter("parking.txt", p)) {
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Parking ajouté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de l'ajout du parking !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        voiture = 1;
    }
}


void
on_radiobutton5_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        camion = 2;
    }
}


void
on_radiobutton6_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton)) {
        moto = 3;
    }
}


void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
parking p;
 if (gtk_toggle_button_get_active(togglebutton)) {
        strcpy(p.acces, "oui");
    }
}


void
on_modifiermp_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
    parking p;
    GtkWidget *nompdentry7, *adressempentry8, *idmpdentry9, *capacitempdentry10, *tarifmpdentry11;
    GtkWidget *etatmpdcomboboxentry4, *blocmpdcomboboxentry5, *abonmpdcomboboxentry6;
    GtkWidget *spin7, *spin8, *spin9, *spin10, *spin11, *spin12;
    GtkWidget *radiobutton4, *radiobutton5, *radiobutton6, *checkbutton2;

 
    nompdentry7 = lookup_widget(GTK_WIDGET(button), "nompdentry7");
    adressempentry8 = lookup_widget(GTK_WIDGET(button), "adressempentry8");
    idmpdentry9 = lookup_widget(GTK_WIDGET(button), "idmpdentry9");
    capacitempdentry10 = lookup_widget(GTK_WIDGET(button), "capacitempdentry10");
    tarifmpdentry11 = lookup_widget(GTK_WIDGET(button), "tarifmpdentry11");

    spin7 = lookup_widget(GTK_WIDGET(button), "spin7");
    spin8 = lookup_widget(GTK_WIDGET(button), "spin8");
    spin9 = lookup_widget(GTK_WIDGET(button), "spin9");
    spin10 = lookup_widget(GTK_WIDGET(button), "spin10");
    spin11 = lookup_widget(GTK_WIDGET(button), "spin11");
    spin12 = lookup_widget(GTK_WIDGET(button), "spin12");

    etatmpdcomboboxentry4 = lookup_widget(GTK_WIDGET(button), "etatmpdcomboboxentry4");
    blocmpdcomboboxentry5 = lookup_widget(GTK_WIDGET(button), "blocmpdcomboboxentry5");
    abonmpdcomboboxentry6 = lookup_widget(GTK_WIDGET(button), "abonmpdcomboboxentry6");

    radiobutton4 = lookup_widget(GTK_WIDGET(button), "radiobutton4");
    radiobutton5 = lookup_widget(GTK_WIDGET(button), "radiobutton5");
    radiobutton6 = lookup_widget(GTK_WIDGET(button), "radiobutton6");
    checkbutton2 = lookup_widget(GTK_WIDGET(button), "checkbutton2");

 
    strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(nompdentry7)));
    strcpy(p.adresse, gtk_entry_get_text(GTK_ENTRY(adressempentry8)));
    strcpy(p.id, gtk_entry_get_text(GTK_ENTRY(idmpdentry9)));
    strcpy(p.capacite, gtk_entry_get_text(GTK_ENTRY(capacitempdentry10)));
    strcpy(p.tarif, gtk_entry_get_text(GTK_ENTRY(tarifmpdentry11)));

    strcpy(p.etat, gtk_combo_box_get_active_text(GTK_COMBO_BOX(etatmpdcomboboxentry4)));
    strcpy(p.bloc, gtk_combo_box_get_active_text(GTK_COMBO_BOX(blocmpdcomboboxentry5)));
    strcpy(p.abonnement, gtk_combo_box_get_active_text(GTK_COMBO_BOX(abonmpdcomboboxentry6)));

    p.jd = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin7));
    p.md = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin8));
    p.ad = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin9));
    p.jf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin10));
    p.mf = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin11));
    p.af = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin12));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton4))) {
        strcpy(p.vehicule, "voiture");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton5))) {
        strcpy(p.vehicule, "camion");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton6))) {
        strcpy(p.vehicule, "moto");
    } else {
        strcpy(p.vehicule, "inconnu");
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton2))) {
        strcpy(p.acces, "oui");
    } else {
        strcpy(p.acces, "non");
    }

 
    if (modifier("parking.txt", p.id, p)) {
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Parking modifié avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de la modification du parking ou ID non trouvé !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}



void
on_annulermp_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *nompdentry7, *adressempentry8, *idmpdentry9, *capacitempdentry10, *tarifmpdentry11;
    GtkWidget *etatmpdcomboboxentry4, *blocmpdcomboboxentry5, *abonmpdcomboboxentry6;
    GtkWidget *spin7, *spin8, *spin9, *spin10, *spin11, *spin12;


    nompdentry7 = lookup_widget(GTK_WIDGET(button), "nompdentry7");
    adressempentry8 = lookup_widget(GTK_WIDGET(button), "adressempentry8");  
    idmpdentry9 = lookup_widget(GTK_WIDGET(button), "idmpdentry9");
    capacitempdentry10 = lookup_widget(GTK_WIDGET(button), "capacitempdentry10");
    tarifmpdentry11 = lookup_widget(GTK_WIDGET(button), "tarifmpdentry11");

    spin7 = lookup_widget(GTK_WIDGET(button), "spin7");
    spin8 = lookup_widget(GTK_WIDGET(button), "spin8");
    spin9 = lookup_widget(GTK_WIDGET(button), "spin9");
    spin10 = lookup_widget(GTK_WIDGET(button), "spin10");
    spin11 = lookup_widget(GTK_WIDGET(button), "spin11");
    spin12 = lookup_widget(GTK_WIDGET(button), "spin12");

    etatmpdcomboboxentry4 = lookup_widget(GTK_WIDGET(button), "etatmpdcomboboxentry4");
    blocmpdcomboboxentry5 = lookup_widget(GTK_WIDGET(button), "blocmpdcomboboxentry5");
    abonmpdcomboboxentry6 = lookup_widget(GTK_WIDGET(button), "abonmpdcomboboxentry6");


    gtk_entry_set_text(GTK_ENTRY(nompdentry7), "");
    gtk_entry_set_text(GTK_ENTRY(adressempentry8), "");
    gtk_entry_set_text(GTK_ENTRY(idmpdentry9), "");
    gtk_entry_set_text(GTK_ENTRY(capacitempdentry10), "");
    gtk_entry_set_text(GTK_ENTRY(tarifmpdentry11), "");

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin7), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin8), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin9), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin10), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin11), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin12), 0);

    gtk_combo_box_set_active(GTK_COMBO_BOX(etatmpdcomboboxentry4), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(blocmpdcomboboxentry5), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(abonmpdcomboboxentry6), -1);

    g_print("Modification annulée et formulaire réinitialisé.\n");
}

void
on_supprimersup_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *idsuppentry12;
    char id[50];

 
    idsuppentry12 = lookup_widget(GTK_WIDGET(button), "idsuppentry12");
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idsuppentry12)));

 
    if (strlen(id) == 0) {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_WARNING,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Veuillez entrer un ID valide.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
    }
 
    if (supprimer_parking("parking.txt", id)) {
 
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Parking supprimé avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
 
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Parking avec l'ID %s introuvable.", id);
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}

void
on_annulersup_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *idsuppentry12;

    idsuppentry12 = lookup_widget(GTK_WIDGET(button), "idsuppentry12");

    gtk_entry_set_text(GTK_ENTRY(idsuppentry12), "");
}

void
on_affectag_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *pragentry15, *cinagentry16, *resultaffectentry9;
    const char *id_parking;
    const char *cin_agent;
    char result_message[256];

 
    pragentry15 = lookup_widget(GTK_WIDGET(button), "pragentry15");
    cinagentry16 = lookup_widget(GTK_WIDGET(button), "cinagentry16");
    resultaffectentry9 = lookup_widget(GTK_WIDGET(button), "resultaffectentry9");

 
    id_parking = gtk_entry_get_text(GTK_ENTRY(pragentry15));
    cin_agent = gtk_entry_get_text(GTK_ENTRY(cinagentry16));

 
    if (strlen(id_parking) == 0 || strlen(cin_agent) == 0) {
        gtk_entry_set_text(GTK_ENTRY(resultaffectentry9), "Erreur : Veuillez remplir tous les champs.");

        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_WARNING,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Veuillez remplir tous les champs.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);

        return;
    }

 
    if (affecter_agent("parking.txt", "agent.txt", id_parking, cin_agent)) {
        snprintf(result_message, sizeof(result_message),
                 "Agent avec CIN %s affecté au parking ID %s avec succès.",
                 cin_agent, id_parking);

        gtk_entry_set_text(GTK_ENTRY(resultaffectentry9), result_message);

        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Agent affecté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        snprintf(result_message, sizeof(result_message),
                 "Erreur : Échec de l'affectation. Vérifiez l'ID ou le CIN.");

        gtk_entry_set_text(GTK_ENTRY(resultaffectentry9), result_message);

        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Échec de l'affectation. Vérifiez l'ID ou le CIN.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}

void
on_annuleraffag_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *pragentry15, *cinagentry16, *resultaffectentry9;

    pragentry15 = lookup_widget(GTK_WIDGET(button), "pragentry15");
    cinagentry16 = lookup_widget(GTK_WIDGET(button), "cinagentry16");
    resultaffectentry9 = lookup_widget(GTK_WIDGET(button), "resultaffectentry9");

    gtk_entry_set_text(GTK_ENTRY(pragentry15), "");
    gtk_entry_set_text(GTK_ENTRY(cinagentry16), "");
    gtk_entry_set_text(GTK_ENTRY(resultaffectentry9), "");
}


void
on_treeviewaffecteragent_row_activated (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{

GtkTreeModel *model;
    GtkTreeIter iter;
    gchar *parking_id;
    gchar *agent_cin;


 
    model = gtk_tree_view_get_model(treeview);

 
    if (gtk_tree_model_get_iter(model, &iter, path)) {
 
        gtk_tree_model_get(model, &iter,
                           0, &parking_id,
                           1, &agent_cin,
                           -1);
 
        printf("Parking ID: %s\n", parking_id);
        printf("CIN Agent: %s\n", agent_cin);


        g_free(parking_id);
        g_free(agent_cin);

    }
}

void
on_actualiseraffecte_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkTreeView *treeview;


    treeview = GTK_TREE_VIEW(lookup_widget(GTK_WIDGET(button), "treeviewaffecteragent"));


 
   afficher_affectations(treeview);

    printf("Affectations actualisées.\n");
}



void on_verifier_clicked(GtkButton *button, gpointer user_data) {
    parking p;
    GtkWidget *nompdentry7, *adressempentry8, *idmpdentry9, *capacitempdentry10, *tarifmpdentry11;
    GtkWidget *etatmpdcomboboxentry4, *blocmpdcomboboxentry5, *abonmpdcomboboxentry6;
    GtkWidget *spin7, *spin8, *spin9, *spin10, *spin11, *spin12;
    GtkWidget *radiobutton4, *radiobutton5, *radiobutton6, *checkbutton2;
    GtkWidget *dialog;
    char id[50];
    int found;

 
    idmpdentry9 = lookup_widget(GTK_WIDGET(button), "idmpdentry9");
    nompdentry7 = lookup_widget(GTK_WIDGET(button), "nompdentry7");
    adressempentry8 = lookup_widget(GTK_WIDGET(button), "adressempentry8");
    capacitempdentry10 = lookup_widget(GTK_WIDGET(button), "capacitempdentry10");
    tarifmpdentry11 = lookup_widget(GTK_WIDGET(button), "tarifmpdentry11");

    spin7 = lookup_widget(GTK_WIDGET(button), "spin7");
    spin8 = lookup_widget(GTK_WIDGET(button), "spin8");
    spin9 = lookup_widget(GTK_WIDGET(button), "spin9");
    spin10 = lookup_widget(GTK_WIDGET(button), "spin10");
    spin11 = lookup_widget(GTK_WIDGET(button), "spin11");
    spin12 = lookup_widget(GTK_WIDGET(button), "spin12");
    checkbutton2 = lookup_widget(GTK_WIDGET(button), "checkbutton2");

    etatmpdcomboboxentry4 = lookup_widget(GTK_WIDGET(button), "etatmpdcomboboxentry4");
    blocmpdcomboboxentry5 = lookup_widget(GTK_WIDGET(button), "blocmpdcomboboxentry5");
    abonmpdcomboboxentry6 = lookup_widget(GTK_WIDGET(button), "abonmpdcomboboxentry6");

    radiobutton4 = lookup_widget(GTK_WIDGET(button), "radiobutton4");
    radiobutton5 = lookup_widget(GTK_WIDGET(button), "radiobutton5");
    radiobutton6 = lookup_widget(GTK_WIDGET(button), "radiobutton6");

 
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idmpdentry9)));
    g_strstrip(id);

 
    found = verifier("parking.txt", id, &p);
    if (found) {
 
        gtk_entry_set_text(GTK_ENTRY(nompdentry7), p.nom);
        gtk_entry_set_text(GTK_ENTRY(adressempentry8), p.adresse);
        gtk_entry_set_text(GTK_ENTRY(capacitempdentry10), p.capacite);
        gtk_entry_set_text(GTK_ENTRY(tarifmpdentry11), p.tarif);

        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin7), p.jd);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin8), p.md);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin9), p.ad);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin10), p.jf);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin11), p.mf);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin12), p.af);

        gtk_combo_box_set_active(GTK_COMBO_BOX(etatmpdcomboboxentry4), 
                                 (strcmp(p.etat, "vide") == 0) ? 0 : 1);
        gtk_combo_box_set_active(GTK_COMBO_BOX(blocmpdcomboboxentry5), 
                                 p.bloc[0] - 'A'); 
        gtk_combo_box_set_active(GTK_COMBO_BOX(abonmpdcomboboxentry6), 
                                 (strcmp(p.abonnement, "mensuelle") == 0) ? 0 :
                                 (strcmp(p.abonnement, "parjour") == 0) ? 1 : 2);

        if (strcmp(p.vehicule, "voiture") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton4), TRUE);
        } else if (strcmp(p.vehicule, "camion") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton5), TRUE);
        } else if (strcmp(p.vehicule, "moto") == 0) {
            gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton6), TRUE);
        }

        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), 
                                     (strcmp(p.acces, "oui") == 0));
    } else {
        // Si le parking n'existe pas, afficher une boîte de dialogue d'erreur
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Parking introuvable !");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), 
                                                 "Le parking avec l'ID \"%s\" n'existe pas.", id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Réinitialiser les champs
        gtk_entry_set_text(GTK_ENTRY(nompdentry7), "");
        gtk_entry_set_text(GTK_ENTRY(adressempentry8), "");
        gtk_entry_set_text(GTK_ENTRY(capacitempdentry10), "");
        gtk_entry_set_text(GTK_ENTRY(tarifmpdentry11), "");
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin7), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin8), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin9), 2023);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin10), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin11), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin12), 2023);
        gtk_combo_box_set_active(GTK_COMBO_BOX(etatmpdcomboboxentry4), -1);
        gtk_combo_box_set_active(GTK_COMBO_BOX(blocmpdcomboboxentry5), -1);
        gtk_combo_box_set_active(GTK_COMBO_BOX(abonmpdcomboboxentry6), -1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton4), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton5), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton6), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), FALSE);
    }
}




void
on_menuajout_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_menumodif_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_menusupp_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_menuaffect_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_annulertrvp_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{

 
    GtkWidget *idtrvprk = lookup_widget(GTK_WIDGET(button), "idtrvprk");  
    GtkWidget *resulttrvprk = lookup_widget(GTK_WIDGET(button), "resulttrvprk");  

 
    gtk_entry_set_text(GTK_ENTRY(idtrvprk), ""); 

 
    if (GTK_IS_LABEL(resulttrvprk)) {
        gtk_label_set_text(GTK_LABEL(resulttrvprk), ""); 
    } else if (GTK_IS_ENTRY(resulttrvprk)) {
        gtk_entry_set_text(GTK_ENTRY(resulttrvprk), "");  
    }


}



void
on_chercherprk_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    parking p;
    GtkWidget *idtrvprk, *resulttrvprk;
    GtkWidget *dialog;
    const char *id_parking;
    char result_message[512];  

    // Récupérer les widgets nécessaires
    idtrvprk = lookup_widget(GTK_WIDGET(button), "idtrvprk");        
    resulttrvprk = lookup_widget(GTK_WIDGET(button), "resulttrvprk");  

    // Récupérer l'ID du champ d'entrée
    id_parking = gtk_entry_get_text(GTK_ENTRY(idtrvprk));

    // Vérifier si l'ID est vide
    if (strlen(id_parking) == 0) {
        gtk_label_set_text(GTK_LABEL(resulttrvprk), "Erreur : Veuillez entrer un ID.");
        return;
    }

    // Rechercher le parking
    chercher_Parking(p, id_parking);

    // Ouvrir le fichier pour lire les résultats de la recherche
    FILE *rech_file = fopen("rechparking.txt", "r");
    if (rech_file != NULL) {
        if (fscanf(rech_file, "%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%99[^;];%d;%d;%d;%d;%d;%d;\n",
                   p.nom, p.adresse, p.id, p.capacite, p.tarif, p.etat, p.bloc, p.abonnement, p.vehicule, p.acces,
                   &p.jd, &p.md, &p.ad, &p.jf, &p.mf, &p.af) == 16) {

            // Construire le message de résultat
            snprintf(result_message, sizeof(result_message),
                     "Parking trouvé :\n"
                     "Nom : %s\nAdresse : %s\nID : %s\nCapacité : %s\nTarif : %s\nÉtat : %s\n"
                     "Bloc : %s\nAbonnement : %s\nVéhicule : %s\nAccès : %s\n"
                     "Date début : %d/%d/%d\nDate fin : %d/%d/%d",
                     p.nom, p.adresse, p.id, p.capacite, p.tarif, p.etat,
                     p.bloc, p.abonnement, p.vehicule, p.acces,
                     p.jd, p.md, p.ad, p.jf, p.mf, p.af);

            // Afficher un message de succès
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "Parking trouvé avec succès !");
            gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), "%s", result_message);
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

        } else {
            // Afficher un message d'erreur si le parking n'est pas trouvé
            dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_OK,
                                            "Parking introuvable !");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        fclose(rech_file);
    } else {
        // Afficher un message si le fichier ne peut pas être ouvert
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Erreur : Impossible d'ouvrir le fichier de recherche !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    // Mettre à jour le widget résultat si applicable
    if (GTK_IS_LABEL(resulttrvprk)) {
        gtk_label_set_text(GTK_LABEL(resulttrvprk), result_message);
    } else if (GTK_IS_ENTRY(resulttrvprk)) {
        gtk_entry_set_text(GTK_ENTRY(resulttrvprk), result_message);
    }
}


void
on_mntrvp_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}




void
on_chercherchertrv_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
      
}


void on_accederlogin_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *id_entry = GTK_WIDGET(lookup_widget(GTK_WIDGET(button), "id_entry"));
    GtkWidget *password_entry = GTK_WIDGET(lookup_widget(GTK_WIDGET(button), "password_entry"));
    GtkWidget *dialog;

    if (!id_entry || !password_entry) {
        fprintf(stderr, "Error: Unable to find required widgets.\n");
        return;
    }

    // Récupérer les valeurs des champs d'entrée
    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id_entry));
    const char *password = gtk_entry_get_text(GTK_ENTRY(password_entry));

    // Vérifier si les champs sont remplis
    if (strlen(id_text) == 0 || strlen(password) == 0) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_WARNING,
                                        GTK_BUTTONS_OK,
                                        "Erreur : Champs vides !");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), 
                                                 "Veuillez remplir les deux champs : ID et mot de passe.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Vérifier si l'ID est valide (entier numérique)
    int id = atoi(id_text);
    if (id == 0 && strcmp(id_text, "0") != 0) {
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Erreur : ID invalide !");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), 
                                                 "L'ID doit être un nombre entier.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Appel à la fonction de vérification des identifiants
    int login_status = loginUser(id, (char *)password);
    if (login_status > 0) {
        // Succès de la connexion
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Connexion réussie !");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), 
                                                 "Bienvenue, utilisateur avec ID : %d", id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Naviguer vers la page suivante
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
    } else {
        // Échec de la connexion
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Connexion échouée !");
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog), 
                                                 "Identifiants invalides pour l'ID : %d. Veuillez réessayer.", id);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void on_retauloginbutton1_clicked(GtkButton *button, gpointer user_data) {
    // Naviguer vers la page précédente
    gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


//***********************************************************************************************************


void
on_treeview1_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
    gchar *id;
    gchar *type;
    gchar *prix;
    gchar *payment;
    gchar *heure;
    gchar *jj;
    gchar *mm;
    gchar *aa;
    gchar *confirmed;

    service s ;

    GtkTreeModel *model = gtk_tree_view_get_model(treeview);

    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        gtk_tree_model_get(GTK_TREE_MODEL(model), &iter, 0, &id, 1, &type, 2, &prix, 3, &payment,  4,&heure, 5, &jj, 6, &mm, 7, &aa, 8, &confirmed, -1);

        strcpy(s.id, id);
        strcpy(s.type, type);

        strcpy(s.prix, prix);
        strcpy(s.payment, payment);
        strcpy(s.heure, heure);
        strcpy(s.jj, jj);
        strcpy(s.mm, mm);
        strcpy(s.aa, aa);
	strcpy(s.confirmed, confirmed);
        s1 = s;
    }

}


void
on_ajouter_button1__clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_modifier_button2_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_entry_set_text(GTK_ENTRY(lookup_widget(button, "idmod_entry3")), s1.id);
gtk_entry_set_text(GTK_ENTRY(lookup_widget(button,"comboboxentry1")), s1.type);

    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_supprimer_button3_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{

gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_actualiser_button4_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview1;
    treeview1 = lookup_widget(button, "treeview1");
    afficher_service(treeview1, "service.txt");
}


void
on_rechercher_button5_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
service s ;
    char text[100];
    GtkWidget *treeview1;
    GtkWidget *input;

    input = lookup_widget(button, "idrechercher_entry1");
    strcpy(text, gtk_entry_get_text(GTK_ENTRY(input)));
    treeview1 = lookup_widget(button, "treeview1");
    chercher_service(s, text);
    afficher_service(treeview1, "rechservice.txt");

}


void
on_carte_radiobutton1_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))

        carte = 1;

}


void
on_carte_radiobutton2_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))

        carte = 2;

}


void
on_matin_radiobutton3_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))

        heure = 3;

}


void
on_apresmidi_radiobutton10_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

if (gtk_toggle_button_get_active(togglebutton))

        heure = 4;

}


void
on_checkbutton003_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_ajouter_button6_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

service s;
int   jj, mm, aa , id, prix  ;
GtkWidget *idservices_entry2, *typesajou_comboboxentry1, *prix_spinbutton1, *carte_radiobutton1, *carte_radiobutton2, *jj_spinbutton2,*mm_spinbutton3,*aa_spinbutton4,*matin_radiobutton3,*apresmidi_radiobutton10,*checkbutton003;


      idservices_entry2  = lookup_widget(button, "idservices_entry2");
   typesajou_comboboxentry1 = lookup_widget(button, "typesajou_comboboxentry1");
    jj_spinbutton2 = lookup_widget(button, "jj_spinbutton2");
    mm_spinbutton3 = lookup_widget(button, "mm_spinbutton3");
    aa_spinbutton4 = lookup_widget(button, "aa_spinbutton4");
prix_spinbutton1 = lookup_widget(button, "prix_spinbutton1");
    jj = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jj_spinbutton2));
    mm = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mm_spinbutton3));
    aa = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(aa_spinbutton4));   
    prix=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(prix_spinbutton1));
	
strcpy(s.id, gtk_entry_get_text(GTK_ENTRY(idservices_entry2)));

strcpy(s.type, gtk_combo_box_get_active_text(GTK_COMBO_BOX(typesajou_comboboxentry1)));
sprintf(s.jj, "%d", jj);
sprintf(s.mm, "%d", mm);
sprintf(s.aa, "%d", aa);
sprintf(s.prix, "%d", prix);
if (carte == 1)
strcpy(s.payment, "carte");
else
strcpy(s.payment, "espece");

if (heure == 3)
strcpy(s.heure, "matin");
else
strcpy(s.heure, "apres-midi");
if (confirm == 5)
strcpy(s.confirmed, "No");
else
strcpy(s.confirmed, "YEs");

 if (ajouterservice("service.txt", s)) {
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service ajouté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de l'ajout du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
    }
}



void
on_annuler_button7_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_acceuiservicebutton2_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
  
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_verifieridservice__clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *idmod_entry3, *typemod_comboboxentry2, *prixmod_spinbutton5;
    GtkWidget *jj_spinbutton6, *mm_spinbutton7, *aa_spinbutton8;
    GtkWidget *cartemod_radiobutton5, *especesmod_radiobutton6;
    GtkWidget *matinmod_radiobutton7, *apresmidi_radiobutton8, *checkbutton2;
    char id[100];
    service s;

    // Récupération des widgets
    idmod_entry3 = lookup_widget(GTK_WIDGET(button), "idmod_entry3");
    typemod_comboboxentry2 = lookup_widget(GTK_WIDGET(button), "typemod_comboboxentry2");
    prixmod_spinbutton5 = lookup_widget(GTK_WIDGET(button), "prixmod_spinbutton5");
    jj_spinbutton6 = lookup_widget(GTK_WIDGET(button), "jj_spinbutton6");
    mm_spinbutton7 = lookup_widget(GTK_WIDGET(button), "mm_spinbutton7");
    aa_spinbutton8 = lookup_widget(GTK_WIDGET(button), "aa_spinbutton8");
    cartemod_radiobutton5 = lookup_widget(GTK_WIDGET(button), "cartemod_radiobutton5");
    especesmod_radiobutton6 = lookup_widget(GTK_WIDGET(button), "especesmod_radiobutton6");
    matinmod_radiobutton7 = lookup_widget(GTK_WIDGET(button), "matinmod_radiobutton7");
    apresmidi_radiobutton8 = lookup_widget(GTK_WIDGET(button), "apresmidi_radiobutton8");
    checkbutton2 = lookup_widget(GTK_WIDGET(button), "checkbutton2");

    // Récupérer l'ID entré par l'utilisateur
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idmod_entry3)));

    // Vérification de l'existence de l'ID dans le fichier
    if (!verifier_modif("service.txt", id, &s)) {
        
    }

    // Pré-remplir le champ ID
    gtk_entry_set_text(GTK_ENTRY(idmod_entry3), s.id);

    // Pré-remplir le type dans le combobox
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(typemod_comboboxentry2));
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);

    while (valid) {
        gchar *current_text;
        gtk_tree_model_get(model, &iter, 0, &current_text, -1);

        // Comparaison du type
        if (g_strcmp0(g_strstrip(current_text), g_strstrip(s.type)) == 0) {
            gtk_combo_box_set_active_iter(GTK_COMBO_BOX(typemod_comboboxentry2), &iter);
            g_free(current_text);
            break;
        }
        g_free(current_text);
        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Remplir les autres champs
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(prixmod_spinbutton5), atof(s.prix));  // Prix
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(jj_spinbutton6), atoi(s.jj)); // Jour
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(mm_spinbutton7), atoi(s.mm)); // Mois
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(aa_spinbutton8), atoi(s.aa)); // Année

    // Mettre à jour les boutons radio pour le mode de paiement
    if (strcmp(s.payment, "carte") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(especesmod_radiobutton6), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(especesmod_radiobutton6), TRUE);
    }

    // Mettre à jour les boutons radio pour l'heure
    if (strcmp(s.heure, "matin") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7), TRUE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(apresmidi_radiobutton8), FALSE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7), FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(apresmidi_radiobutton8), TRUE);
    }

    // Mettre à jour la case de confirmation (checkbutton)
    g_strstrip(s.confirmed);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), strcmp(s.confirmed, "YEs") == 0);

    printf("Données pré-remplies pour l'ID : %s\n", s.id);

}


void
on_cartemod_radiobutton5_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_especesmod_radiobutton6_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        carte = 5;
}


void
on_matinmod_radiobutton7_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        heure = 6;

}


void
on_apresmidi_radiobutton8_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if (gtk_toggle_button_get_active(togglebutton))

        heure = 7;
}


void
on_checkbutton004_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_modifier_button8_clicked            (GtkButton       *button,
                                        gpointer         user_data){
    GtkWidget *idmod_entry3, *typemod_comboboxentry2, *prixmod_spinbutton5;
    GtkWidget *jj_spinbutton6, *mm_spinbutton7, *aa_spinbutton8;
    GtkWidget *cartemod_radiobutton5, *especesmod_radiobutton6;
    GtkWidget *matinmod_radiobutton7, *apresmidi_radiobutton8, *checkbutton2;

    char id[100];
    service s;

    // Récupération des widgets
    idmod_entry3 = lookup_widget(GTK_WIDGET(button), "idmod_entry3");
    typemod_comboboxentry2 = lookup_widget(GTK_WIDGET(button), "typemod_comboboxentry2");
    prixmod_spinbutton5 = lookup_widget(GTK_WIDGET(button), "prixmod_spinbutton5");
    jj_spinbutton6 = lookup_widget(GTK_WIDGET(button), "jj_spinbutton6");
    mm_spinbutton7 = lookup_widget(GTK_WIDGET(button), "mm_spinbutton7");
    aa_spinbutton8 = lookup_widget(GTK_WIDGET(button), "aa_spinbutton8");
    cartemod_radiobutton5 = lookup_widget(GTK_WIDGET(button), "cartemod_radiobutton5");
    especesmod_radiobutton6 = lookup_widget(GTK_WIDGET(button), "especesmod_radiobutton6");
    matinmod_radiobutton7 = lookup_widget(GTK_WIDGET(button), "matinmod_radiobutton7");
    apresmidi_radiobutton8 = lookup_widget(GTK_WIDGET(button), "apresmidi_radiobutton8");
    checkbutton2 = lookup_widget(GTK_WIDGET(button), "checkbutton2");

    // Récupérer l'ID entré par l'utilisateur
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idmod_entry3)));

    // Vérification de l'existence de l'ID dans le fichier
    if (!verifier_modif("service.txt", id, &s)) {
        // Afficher un message d'erreur si l'ID n'existe pas
        GtkWidget *error_dialog = gtk_message_dialog_new(
            GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_OK,
            "Erreur : L'ID spécifié n'a pas été trouvé !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return; // Arrêter l'exécution
    }

    // Si l'ID existe, pré-remplir les champs
    gtk_entry_set_text(GTK_ENTRY(idmod_entry3), s.id);

    // Pré-remplir le type dans le combobox
    GtkTreeModel *model = gtk_combo_box_get_model(GTK_COMBO_BOX(typemod_comboboxentry2));
    GtkTreeIter iter;
    gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
    while (valid) {
        gchar *current_text;
        gtk_tree_model_get(model, &iter, 0, &current_text, -1);
        if (g_strcmp0(g_strstrip(current_text), g_strstrip(s.type)) == 0) {
            gtk_combo_box_set_active_iter(GTK_COMBO_BOX(typemod_comboboxentry2), &iter);
            g_free(current_text);
            break;
        }
        g_free(current_text);
        valid = gtk_tree_model_iter_next(model, &iter);
    }

    // Remplir les autres champs
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(prixmod_spinbutton5), atof(s.prix));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(jj_spinbutton6), atoi(s.jj));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(mm_spinbutton7), atoi(s.mm));
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(aa_spinbutton8), atoi(s.aa));

    // Mettre à jour les boutons radio pour le mode de paiement
    if (strcmp(s.payment, "carte") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cartemod_radiobutton5), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(especesmod_radiobutton6), TRUE);
    }

    // Mettre à jour les boutons radio pour l'heure
    if (strcmp(s.heure, "matin") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(matinmod_radiobutton7), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(apresmidi_radiobutton8), TRUE);
    }

    // Mettre à jour la case de confirmation (checkbutton)
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton2), strcmp(s.confirmed, "Yes") == 0);

    printf("Service trouvé et champs pré-remplis pour l'ID : %s\n", s.id);
}


void
on_anuller_button9_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_modfierservicebutton3_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_anuller_button11_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_supprimer_button10_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *idservicessup_entry4;
    char id[50];

    // Récupérer le champ de saisie pour l'ID
    idservicessup_entry4 = lookup_widget(GTK_WIDGET(button), "idservicessup_entry4");
    strcpy(id, gtk_entry_get_text(GTK_ENTRY(idservicessup_entry4)));

    // Vérifier si l'ID est vide
    if (strlen(id) == 0) {
        g_print("Erreur : Veuillez entrer un ID valide.\n");
        return;
    }

    // Appeler la fonction de suppression et vérifier le résultat
    if (supprimer_Service("service.txt", id)) {
     GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service supprimer  avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);

    } else {
 GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de  supprimer du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);

      
    }
}


void
on_accssbutton15_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_treeviewaffecter_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)

{                                
  GtkTreeModel *model;
    GtkTreeIter iter;
    int service_id, reservation_id;  // Service ID et Reservation ID doivent être de type int

    // Récupérer le modèle de données du TreeView
    model = gtk_tree_view_get_model(treeview);

    // Accéder à l'itérateur de la ligne activée
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Extraire les données des colonnes
        gtk_tree_model_get(model, &iter, &service_id, 0, &reservation_id , 1, -1);

        // Afficher les informations dans la console
        printf("Service ID: %d\n", service_id);
        printf("Reservation ID: %d\n", reservation_id);

        // Afficher les informations dans une boîte de dialogue
        char message[256];
        snprintf(message, sizeof(message), "Service  d ' id %d affecté à la réservation  d 'id %d", service_id, reservation_id);
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

}


void
on_affecter_button12_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
service s;
    Reservation r;

    // Récupérer les valeurs des champs de texte GTK
    GtkWidget *idaffecter_entry5, *idparking_entry6;
    idaffecter_entry5 = lookup_widget(button, "idaffecter_entry5");
    idparking_entry6 = lookup_widget(button, "idparking_entry6");

    // Vérifier si les widgets sont valides avant de récupérer les textes
    if (idaffecter_entry5 != NULL && idparking_entry6 != NULL) {
        // Récupérer l'ID du service (chaîne de caractères)
        const char *service_id_text = gtk_entry_get_text(GTK_ENTRY(idaffecter_entry5));
        if (service_id_text != NULL && strlen(service_id_text) > 0) {
            strcpy(s.id, service_id_text);  // Assurez-vous que s.id est un tableau de caractères
            printf("ID du service : %s\n", s.id);
        } else {
            printf("Erreur : L'ID du service est vide ou invalide\n");
            return;  // Quitter si l'ID du service est invalide
        }

        // Récupérer l'ID de la réservation (convertir en entier)
        const char *reservation_id_text = gtk_entry_get_text(GTK_ENTRY(idparking_entry6));
        r.id = atoi(reservation_id_text);  // Assurez-vous que r.id est un entier valide
        printf("ID de la réservation : %d\n", r.id);

        // Appeler la fonction d'affectation
    if (affecter(s.id, r.id, "service.txt", "reservation.txt", "affectation.txt")) {
  GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "service affecté avec succès !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    } else {
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_ERROR,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur lors de l'affecté du service !");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
         gtk_widget_destroy(error_dialog);
    }
}

}


void
on_annuleraff_button13_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_accaff_button19_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeviewaffecter;
    treeviewaffecter = lookup_widget(button, "treeviewaffecter");
    afficher_affectationsservice(treeviewaffecter, "affectation.txt");  
}


void
on_buttonseconnecteradmn_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
                Login l;
char mdp[20];
GtkWidget *entrymdpadmn;

 entrymdpadmn=lookup_widget(GTK_WIDGET(button),"entrymdpadmn");
     strcpy(mdp,gtk_entry_get_text(GTK_ENTRY(entrymdpadmn)));
    int X=verifier_mdp_fichier("login.txt", mdp);
        if(X==1){
                printf("ajout avec succes\n");
              gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
                
                            }
    if(X==0){
        GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_WARNING,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Veuillez entrer un ID valide.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
                                  }
           
}


void
on_buttonarriereseconnectadmn_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonoffrehz_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
      gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonprecedentajouthz_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonannulerhz_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entryNomparking , *entryid_parking,*entryadresseparking,*spinbuttonjourhz_,*_spinbuttonMoishz,*spinbuttonAnneehz,*spinbuttonheuredebhz_,*spinbuttonminutedebhz,*heurefin,*minutefin,*checkbuttonvoiture,
*checkbuttoncamion,*checkbuttonmoto,*entrymatricule,*comboboxservices ;

GtkWidget *radiobutton1a;
 
  GtkWidget *radiobutton2a;
  GtkWidget *radiobutton3a;
 
  GtkWidget *radiobutton4a;
  GtkWidget *radiobutton5a;
  GtkWidget *radiobutton6a;
  
  GtkWidget *radiobutton7a;



entryNomparking=lookup_widget(GTK_WIDGET(button),"entryNomparking");
entryid_parking=lookup_widget(GTK_WIDGET(button),"entryid_parking");
entryadresseparking=lookup_widget(GTK_WIDGET(button),"entryadresseparking");
spinbuttonjourhz_=lookup_widget(GTK_WIDGET(button),"spinbuttonjourhz_");
_spinbuttonMoishz=lookup_widget(GTK_WIDGET(button),"_spinbuttonMoishz");
spinbuttonAnneehz=lookup_widget(GTK_WIDGET(button),"spinbuttonAnneehz");
spinbuttonheuredebhz_=lookup_widget(GTK_WIDGET(button),"spinbuttonheuredebhz_");
spinbuttonminutedebhz=lookup_widget(GTK_WIDGET(button),"spinbuttonminutedebhz");
heurefin=lookup_widget(GTK_WIDGET(button),"heurefin");
minutefin=lookup_widget(GTK_WIDGET(button),"minutefin");
checkbuttonvoiture=lookup_widget(GTK_WIDGET(button),"checkbuttonvoiture");
checkbuttoncamion=lookup_widget(GTK_WIDGET(button),"checkbuttoncamion");
checkbuttonmoto=lookup_widget(GTK_WIDGET(button),"checkbuttonmoto");
entrymatricule=lookup_widget(GTK_WIDGET(button),"entrymatricule");
radiobutton1a=lookup_widget(GTK_WIDGET(button),"radiobutton1a");
radiobutton2a=lookup_widget(GTK_WIDGET(button),"radiobutton2a");
radiobutton3a=lookup_widget(GTK_WIDGET(button),"radiobutton3a");
radiobutton4a=lookup_widget(GTK_WIDGET(button),"radiobutton4a");
radiobutton5a=lookup_widget(GTK_WIDGET(button),"radiobutton5a");
radiobutton6a=lookup_widget(GTK_WIDGET(button),"radiobutton6a");
radiobutton7a=lookup_widget(GTK_WIDGET(button),"radiobutton7a");
comboboxservices=lookup_widget(GTK_WIDGET(button),"comboboxservices");
gtk_entry_set_text(GTK_ENTRY(entryNomparking), "");
    gtk_entry_set_text(GTK_ENTRY(entryid_parking), "");
    gtk_entry_set_text(GTK_ENTRY(entryadresseparking), "");
    gtk_entry_set_text(GTK_ENTRY(entrymatricule), "");
 gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonjourhz_), 1);  // Premier jour du mois
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(_spinbuttonMoishz), 1);  // Premier mois (janvier)
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonAnneehz), 2024); // Année actuelle
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonheuredebhz_), 0); // Heure par défaut
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonminutedebhz), 0); // Minute par défaut
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(heurefin), 0);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(minutefin), 0);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonvoiture), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttoncamion), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonmoto), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1a), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2a), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton3a), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton5a), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton6a), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton7a), FALSE);

gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxservices), -1);
}

void
on_buttonconfirmhz_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
Reservation1 res;
    GtkWidget *entryNomparking , *entryid_parking,*entryadresseparking,*spinbuttonjourhz_,*_spinbuttonMoishz,*spinbuttonAnneehz,*spinbuttonheuredebhz_,*spinbuttonminutedebhz,*heurefin,*minutefin,*checkbuttonvoiture,
*checkbuttoncamion,*checkbuttonmoto,*entrymatricule,*comboboxservices ;
 GtkWidget *radiobutton1a;
 
  GtkWidget *radiobutton2a;
  GtkWidget *radiobutton3a;
 
  GtkWidget *radiobutton4a;
  GtkWidget *radiobutton5a;
  GtkWidget *radiobutton6a;
  
  GtkWidget *radiobutton7a;




entryNomparking=lookup_widget(GTK_WIDGET(button),"entryNomparking");
entryid_parking=lookup_widget(GTK_WIDGET(button),"entryid_parking");
entryadresseparking=lookup_widget(GTK_WIDGET(button),"entryadresseparking");
spinbuttonjourhz_=lookup_widget(GTK_WIDGET(button),"spinbuttonjourhz_");                         
_spinbuttonMoishz=lookup_widget(GTK_WIDGET(button),"_spinbuttonMoishz");
spinbuttonAnneehz=lookup_widget(GTK_WIDGET(button),"spinbuttonAnneehz");
spinbuttonheuredebhz_=lookup_widget(GTK_WIDGET(button),"spinbuttonheuredebhz_");
spinbuttonminutedebhz=lookup_widget(GTK_WIDGET(button),"spinbuttonminutedebhz");
heurefin=lookup_widget(GTK_WIDGET(button),"heurefin");
minutefin=lookup_widget(GTK_WIDGET(button),"minutefin");
checkbuttonvoiture=lookup_widget(GTK_WIDGET(button),"checkbuttonvoiture");
checkbuttoncamion=lookup_widget(GTK_WIDGET(button),"checkbuttoncamion");
checkbuttonmoto=lookup_widget(GTK_WIDGET(button),"checkbuttonmoto");
entrymatricule=lookup_widget(GTK_WIDGET(button),"entrymatricule");
comboboxservices=lookup_widget(GTK_WIDGET(button),"comboboxservices");
radiobutton1a=lookup_widget(GTK_WIDGET(button),"radiobutton1a");
radiobutton2a=lookup_widget(GTK_WIDGET(button),"radiobutton2a");
radiobutton3a=lookup_widget(GTK_WIDGET(button),"radiobutton3a");
radiobutton4a=lookup_widget(GTK_WIDGET(button),"radiobutton4a");
radiobutton5a=lookup_widget(GTK_WIDGET(button),"radiobutton5a");
radiobutton6a=lookup_widget(GTK_WIDGET(button),"radiobutton6a");
radiobutton7a=lookup_widget(GTK_WIDGET(button),"radiobutton7a");
strcpy(res.parking.nom,gtk_entry_get_text(GTK_ENTRY(entryNomparking)));
strcpy(res.id_reservation,gtk_entry_get_text(GTK_ENTRY(entryid_parking)));
strcpy(res.parking.adresse,gtk_entry_get_text(GTK_ENTRY(entryadresseparking)));
strcpy(res.vehicule.matricule,gtk_entry_get_text(GTK_ENTRY(entrymatricule)));
 res.date_reservation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonjourhz_));
  res.date_reservation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(_spinbuttonMoishz));
 res.date_reservation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonAnneehz));
 res.heure_debut.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonheuredebhz_));
 res.heure_debut.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonminutedebhz));
 res.heure_fin.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(heurefin));
  res.heure_fin.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minutefin)); 
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonvoiture))){
  strcpy(res.vehicule.type,"voiture");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttoncamion))){
        strcpy(res.vehicule.type,"camion");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonmoto))){
        strcpy(res.vehicule.type,"moto");}


if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton3a))){
  strcpy(res.place.bloc,"A");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton4a))){
        strcpy(res.place.bloc,"B");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton5a))){
        strcpy(res.place.bloc,"C");}



if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1a))){
  strcpy( res.place.type,"standart");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2a))){
  strcpy( res.place.type,"handicape");
}
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton6a))){
  strcpy( res.service.paiement,"sur place");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton7a))){
        strcpy( res.service.paiement,"en ligne");}

strcpy(res.service.demande_service,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxservices)));

int X=ajouter_reserv("Rese.txt" , res);
               if( X==1){
                    printf("ajout avec succes");
                       GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Ajout  avec success !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
}
                 else{
                      printf("erreur");}

 
}


void
on_buttonsuivajouthz_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
       gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonannulereservationhz_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entryidres;
char Id[20];
Reservation nouvelleres;
     entryidres=lookup_widget(GTK_WIDGET(button),"entryidres");
     strcpy(Id,gtk_entry_get_text(GTK_ENTRY(entryidres)));
GtkWidget *entrynomparking1 ,*entryadresseparking1,*spinbuttonj,*spinbuttonm,*spinbuttona,*spinbuttonhdeb_,*spinbuttonmindeb,*spinbuttonhfin,*_spinbuttonminfin,*checkbuttonvoituree__,
*_checkbuttoncamionn,*_checkbuttonmotoo,*entrymatriculee,*comboboxservice,*radiobuttonstandart,*radiobuttonhandicape,*radiobuttonA,*radiobuttonB,*radiobuttonC ,*_radiobuttonsurplaceee,*radiobuttonligneee;



entrynomparking1=lookup_widget(GTK_WIDGET(button),"entrynomparking1");

entryadresseparking1=lookup_widget(GTK_WIDGET(button),"entryadresseparking1");
spinbuttonj=lookup_widget(GTK_WIDGET(button),"spinbuttonj");
spinbuttonm=lookup_widget(GTK_WIDGET(button),"spinbuttonm");
spinbuttona=lookup_widget(GTK_WIDGET(button),"spinbuttona");
spinbuttonhdeb_=lookup_widget(GTK_WIDGET(button),"spinbuttonhdeb_");
spinbuttonmindeb=lookup_widget(GTK_WIDGET(button),"spinbuttonmindeb");
spinbuttonhfin=lookup_widget(GTK_WIDGET(button),"spinbuttonhfin");
_spinbuttonminfin=lookup_widget(GTK_WIDGET(button),"_spinbuttonminfin");
checkbuttonvoituree__=lookup_widget(GTK_WIDGET(button),"checkbuttonvoituree__");
_checkbuttoncamionn=lookup_widget(GTK_WIDGET(button),"_checkbuttoncamionn");
_checkbuttonmotoo=lookup_widget(GTK_WIDGET(button),"_checkbuttonmotoo");
entrymatriculee=lookup_widget(GTK_WIDGET(button),"entrymatriculee");
comboboxservice=lookup_widget(GTK_WIDGET(button),"comboboxservice");
radiobuttonstandart=lookup_widget(GTK_WIDGET(button),"radiobuttonstandart");
radiobuttonhandicape=lookup_widget(GTK_WIDGET(button),"radiobuttonhandicape");
radiobuttonA=lookup_widget(GTK_WIDGET(button),"radiobuttonA");
radiobuttonB=lookup_widget(GTK_WIDGET(button),"radiobuttonB");
radiobuttonC=lookup_widget(GTK_WIDGET(button),"radiobuttonC");
_radiobuttonsurplaceee=lookup_widget(GTK_WIDGET(button),"_radiobuttonsurplaceee");
radiobuttonligneee=lookup_widget(GTK_WIDGET(button),"radiobuttonligneee");





gtk_entry_set_text(GTK_ENTRY(entrynomparking1), "");
    
    gtk_entry_set_text(GTK_ENTRY(entryadresseparking1), "");
    gtk_entry_set_text(GTK_ENTRY(entrymatriculee), "");
 gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonj), 1);  // Premier jour du mois
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonm), 1);  // Premier mois (janvier)
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttona), 2024); // Année actuelle
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonhdeb_), 0); // Heure par défaut
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonmindeb), 0); // Minute par défaut
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(_spinbuttonminfin), 0);
   
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonvoituree__), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_checkbuttoncamionn), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_checkbuttonmotoo), FALSE);
gtk_combo_box_set_active(GTK_COMBO_BOX(comboboxservice), -1);
 gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonstandart), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonhandicape), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonA), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonB), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonC), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_radiobuttonsurplaceee), FALSE);
gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonligneee), FALSE);
}


void
on_buttonsuivantmodifierhz_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *notebook = lookup_widget(GTK_WIDGET(button), "notebook1"); 
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonconfirmerreservationhz_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{GtkWidget *entryidres;

 char Id[20];
Reservation1 nouvelleres;
Reservation1 res;
     entryidres=lookup_widget(GTK_WIDGET(button),"entryidres");
     strcpy(Id,gtk_entry_get_text(GTK_ENTRY(entryidres)));
GtkWidget *entrynomparking1 ,*entryadresseparking1,*spinbuttonj,*spinbuttonm,*spinbuttona,*spinbuttonhdeb_,*spinbuttonmindeb,*spinbuttonhfin,*_spinbuttonminfin,*checkbuttonvoituree__,
*_checkbuttoncamionn,*_checkbuttonmotoo,*entrymatriculee,*comboboxservice,*radiobuttonstandart,*radiobuttonhandicape,*radiobuttonA,*radiobuttonB,*radiobuttonC ,*_radiobuttonsurplaceee,*radiobuttonligneee;



entrynomparking1=lookup_widget(GTK_WIDGET(button),"entrynomparking1");

entryadresseparking1=lookup_widget(GTK_WIDGET(button),"entryadresseparking1");
spinbuttonj=lookup_widget(GTK_WIDGET(button),"spinbuttonj");
spinbuttonm=lookup_widget(GTK_WIDGET(button),"spinbuttonm");
spinbuttona=lookup_widget(GTK_WIDGET(button),"spinbuttona");
spinbuttonhdeb_=lookup_widget(GTK_WIDGET(button),"spinbuttonhdeb_");
spinbuttonmindeb=lookup_widget(GTK_WIDGET(button),"spinbuttonmindeb");
spinbuttonhfin=lookup_widget(GTK_WIDGET(button),"spinbuttonhfin");
_spinbuttonminfin=lookup_widget(GTK_WIDGET(button),"_spinbuttonminfin");
checkbuttonvoituree__=lookup_widget(GTK_WIDGET(button),"checkbuttonvoituree__");
_checkbuttoncamionn=lookup_widget(GTK_WIDGET(button),"_checkbuttoncamionn");
_checkbuttonmotoo=lookup_widget(GTK_WIDGET(button),"_checkbuttonmotoo");
entrymatriculee=lookup_widget(GTK_WIDGET(button),"entrymatriculee");
comboboxservice=lookup_widget(GTK_WIDGET(button),"comboboxservice");
radiobuttonstandart=lookup_widget(GTK_WIDGET(button),"radiobuttonstandart");
radiobuttonhandicape=lookup_widget(GTK_WIDGET(button),"radiobuttonhandicape");
radiobuttonA=lookup_widget(GTK_WIDGET(button),"radiobuttonA");
radiobuttonB=lookup_widget(GTK_WIDGET(button),"radiobuttonB");
radiobuttonC=lookup_widget(GTK_WIDGET(button),"radiobuttonC");
_radiobuttonsurplaceee=lookup_widget(GTK_WIDGET(button),"_radiobuttonsurplaceee");
radiobuttonligneee=lookup_widget(GTK_WIDGET(button),"radiobuttonligneee");



strcpy(nouvelleres.parking.nom,gtk_entry_get_text(GTK_ENTRY(entrynomparking1)));

strcpy(nouvelleres.parking.adresse,gtk_entry_get_text(GTK_ENTRY(entryadresseparking1)));
strcpy(nouvelleres.vehicule.matricule,gtk_entry_get_text(GTK_ENTRY(entrymatriculee)));
 nouvelleres.date_reservation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonj));
  nouvelleres.date_reservation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonm));
 nouvelleres.date_reservation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttona));
 nouvelleres.heure_debut.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonhdeb_));
 nouvelleres.heure_debut.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonmindeb));
 nouvelleres.heure_fin.heure=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonhfin));
  nouvelleres.heure_fin.minute=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(_spinbuttonminfin)); 
strcpy(nouvelleres.service.demande_service,gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboboxservice)));
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbuttonvoituree__))){
  strcpy(nouvelleres.vehicule.type,"voiture");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_checkbuttoncamionn))){
        strcpy(nouvelleres.vehicule.type,"camion");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_checkbuttonmotoo))){
        strcpy(nouvelleres.vehicule.type,"moto");  }


if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonA))){
  strcpy(nouvelleres.place.bloc,"A");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonB))){
        strcpy(nouvelleres.place.bloc,"B");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonC))){
        strcpy(nouvelleres.place.bloc,"C");}



if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonstandart))){
  strcpy( nouvelleres.place.type,"standart");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonhandicape))){
  strcpy( nouvelleres.place.type,"handicape");
}
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(_radiobuttonsurplaceee))){
  strcpy( nouvelleres.service.paiement,"sur place");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonligneee))){
        strcpy( nouvelleres.service.paiement,"en ligne");}
 modifier_reserv("Rese.txt", Id, nouvelleres);
    
 GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Modification effectuee avec succes !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
    


    

}


void
on_buttonprecedentmodifierhz_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_treeview3_row_activated             (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
   GtkTreeModel *model;
           GtkTreeIter iter;
            gchar *id_reservation; // Variable pour l'ID de la réservation

    // Récupérer le modèle du TreeView
              model = gtk_tree_view_get_model(treeview);

    // Récupérer l'itérateur de la ligne sélectionnée
              if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Supposons que l'ID de la réservation est dans la première colonne (index 0)
                 gtk_tree_model_get(model, &iter, 0, &id_reservation, -1);

        // Afficher l'ID pour débogage
                 printf("ID sélectionné pour suppression : '%s'\n", id_reservation);

        // Appeler la fonction de suppression avec l'ID
               supprimer_reserv("Rese.txt", id_reservation);

        // Libérer la mémoire allouée pour l'ID
              g_free(id_reservation);
    }
}


void
on_buttonaffichage_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *treeview;

    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview3"); // Remplacez "treeview1" par l'ID de votre TreeView


    // Appeler la fonction pour lire les données et les afficher dans le TreeView
   affichage_reservation(GTK_TREE_VIEW(treeview), "Rese.txt");
}


void
on_buttonchercher_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *entryid_reservation;
     char Id[20];
     entryid_reservation=lookup_widget(GTK_WIDGET(button),"entryid_reservation");
     strcpy(Id,gtk_entry_get_text(GTK_ENTRY(entryid_reservation)));
    chercher("Rese.txt",Id);

}


void
on_buttonannuler_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entryid_reservation;
     char Id[20];
     entryid_reservation=lookup_widget(GTK_WIDGET(button),"entryid_reservation");
     gtk_entry_set_text(GTK_ENTRY(entryid_reservation), "");
}


void
on_buttonsupprimer_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
         
  GtkWidget *entryid_reservation;
     char Id[20];

     entryid_reservation=lookup_widget(GTK_WIDGET(button),"entryid_reservation");
     strcpy(Id,gtk_entry_get_text(GTK_ENTRY(entryid_reservation)));

     supprimer_reserv("Rese.txt", Id);
        GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "suppression avec success !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
}


void
on_buttonaffichement_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview;


    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview4"); // Remplacez "treeview1" par l'ID de votre TreeView

    // Appeler la fonction pour lire les données et les afficher dans le TreeView
   affichage_reservation(GTK_TREE_VIEW(treeview), "Rese.txt");
}


void
on_buttonprecedaffich_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
            gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonhome_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
                gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));    
}


void
on_buttontarif_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
              GtkWidget   *radiobuttonmensuel,*radiobuttontrimestriel,*radiobuttonannuel,*label;
   radiobuttonmensuel=lookup_widget(GTK_WIDGET(button),"radiobuttonmensuel");
radiobuttontrimestriel=lookup_widget(GTK_WIDGET(button),"radiobuttontrimestriel");
radiobuttonannuel=lookup_widget(GTK_WIDGET(button),"radiobuttonannuel");
label=lookup_widget(GTK_WIDGET(button),"label");
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonmensuel))){
  strcpy( res.type_abnmt,"Mensuel");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttontrimestriel))){
        strcpy( res.type_abnmt,"Trimestriel");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonannuel))){
        strcpy( res.type_abnmt,"Annuel");}
     char resultat[50];
      sprintf(resultat, "Le tarif est: %d ",calcul_abonnement(  res));
     gtk_label_set_text(GTK_LABEL(label),resultat);
}


void
on_buttonconfabonnmt_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
      GtkWidget *spinbutton1,*spinbutton2,*spinbutton3,*radiobuttonmensuel,*radiobuttontrimestriel,*radiobuttonannuel,*radiobuttonAb,*radiobuttonBa,*combobox3,*label ;




spinbutton1=lookup_widget(GTK_WIDGET(button),"spinbutton1");
spinbutton2=lookup_widget(GTK_WIDGET(button),"spinbutton2");
spinbutton3=lookup_widget(GTK_WIDGET(button),"spinbutton3");
radiobuttonmensuel=lookup_widget(GTK_WIDGET(button),"radiobuttonmensuel");
radiobuttontrimestriel=lookup_widget(GTK_WIDGET(button),"radiobuttontrimestriel");
radiobuttonannuel=lookup_widget(GTK_WIDGET(button),"radiobuttonannuel");
radiobuttonAb=lookup_widget(GTK_WIDGET(button),"radiobuttonAb");
radiobuttonBa=lookup_widget(GTK_WIDGET(button),"radiobuttonBa");
combobox3=lookup_widget(GTK_WIDGET(button),"combobox3");
res.date_reservation.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));
  res.date_reservation.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
 res.date_reservation.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton3));
if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonmensuel))){
  strcpy( res.type_abnmt,"Mensuel");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttontrimestriel))){
        strcpy( res.type_abnmt,"Trimestriel");}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonannuel))){
        strcpy( res.type_abnmt,"Annuel");}



if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonAb))){
  strcpy( res.service.paiement,"en ligne");

}
else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobuttonBa))){
  strcpy(res.service.paiement,"sur place");
}
strcpy( res.service.demande_service,gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox3)));

  int X= ajouter_abonnement("abonne.txt" , res);
                            if(X==1){
                                printf("ajout avec succes\n");
                              GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Votre abonnement a ete effectuee avec success !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
                                  
 
                                                                 
}
}


void
on_buttonannulerabonnement_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *spinbutton1,*spinbutton2,*spinbutton3,*radiobuttonmensuel,*radiobuttontrimestriel,*radiobuttonannuel,*radiobuttonAb,*radiobuttonBa,*combobox3 ;
spinbutton1=lookup_widget(GTK_WIDGET(button),"spinbutton1");
spinbutton2=lookup_widget(GTK_WIDGET(button),"spinbutton2");
spinbutton3=lookup_widget(GTK_WIDGET(button),"spinbutton3");
radiobuttonmensuel=lookup_widget(GTK_WIDGET(button),"radiobuttonmensuel");
radiobuttontrimestriel=lookup_widget(GTK_WIDGET(button),"radiobuttontrimestriel");
radiobuttonannuel=lookup_widget(GTK_WIDGET(button),"radiobuttonannuel");
radiobuttonAb=lookup_widget(GTK_WIDGET(button),"radiobuttonAb");
radiobuttonBa=lookup_widget(GTK_WIDGET(button),"radiobuttonBa");
combobox3=lookup_widget(GTK_WIDGET(button),"combobox3");







    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton1), 1);  // Premier jour du mois
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2), 1);  // Premier mois (janvier)
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton3), 2024); // Année actuelle
    if(strcmp( res.service.paiement,"en ligne")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonAb),TRUE);

}
else if(strcmp( res.service.paiement,"sur place")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonBa),TRUE);

}
if(strcmp(res.type_abnmt,"Mensuel")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonmensuel),TRUE);

}else if(strcmp(  res.type_abnmt,"Trimestriel")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttontrimestriel),TRUE);

}else if(strcmp(res.type_abnmt,"Annuel")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonannuel),TRUE);
}
gtk_combo_box_set_active(GTK_COMBO_BOX(combobox3), -1);
   
}


void
on_buttonprecedoffre_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));        
}


void
on_buttonajouter_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_buttonsupp_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonmodifi_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonaffich_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
       gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonprecedoption_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_buttoncreeruncompteclient_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonarriereseconnectclient_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{          gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));      

                
}


void
on_buttonseconnecterclient_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
      Login l;
char mdp[20];
GtkWidget *dialog , *entry23;


 entry23=lookup_widget(GTK_WIDGET(button),"entry23");
     strcpy(mdp,gtk_entry_get_text(GTK_ENTRY(entry23)));
    int X=verifier_mdp_fichier("/home/hassan/Projects/projectreservation/login.txt", mdp);
        if(X==1){
                printf("ajout avec succes\n");
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
                
                            }
    if(X==0){
         GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                        GTK_DIALOG_MODAL,
                                                        GTK_MESSAGE_WARNING,
                                                        GTK_BUTTONS_OK,
                                                        "Erreur : Veuillez entrer un ID valide.");
        gtk_dialog_run(GTK_DIALOG(error_dialog));
        gtk_widget_destroy(error_dialog);
        return;
                                  }
           
}


void
on_buttonloginclient_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
          GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Votre compte a ete cree avec success !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
      gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
            gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
      gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

         
}


void
on_button23_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_button24_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}


void
on_buttonloginadmn_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
          GtkWidget *success_dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_INFO,
                                                          GTK_BUTTONS_OK,
                                                          "Votre compte a ete cree avec success !");
        gtk_dialog_run(GTK_DIALOG(success_dialog));
        gtk_widget_destroy(success_dialog);
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));


}


void
on_buttonadminis_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
      gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttonclient_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
       gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
        gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttongererreservation_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
          gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
            gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
   gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
            gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_geravi_clicked                      (GtkButton       *button,
                                        gpointer         user_data)
{
}


void
on_buttonprecedespclient_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
     
       GtkWidget *notebook = lookup_widget(GTK_WIDGET(button), "notebook1");
   if (!notebook) {
       printf("Erreur : Widget 'notebook1' introuvable.\n");
       return;
   }

   GtkNotebook *notebook_widget = GTK_NOTEBOOK(notebook);
   int current_page = gtk_notebook_get_current_page(notebook_widget);

   if (current_page <= 0) {
       printf("Vous êtes déjà à la première page.\n");
       return;
   }

   // Aller quatre pages en arrière ou à la première page si pas assez de pages.
   int target_page = current_page - 4;
   if (target_page < 0) {
       target_page = 0;
   }
   gtk_notebook_set_current_page(notebook_widget, target_page); 
}


void
on_button14_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
                  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
                     gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_button13_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button12_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
     gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
    gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
     gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));

}
void
on_buttonpreceespadmns_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
 gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}


void
on_buttoncherche1_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
       Reservation1 res;
     
     GtkWidget *entryidres;
     char Id[20];
     entryidres=lookup_widget(GTK_WIDGET(button),"entryidres");
     strcpy(Id,gtk_entry_get_text(GTK_ENTRY(entryidres)));
    res = cherche("Rese.txt",Id);

GtkWidget *entrynomparking1 ,*entryadresseparking1,*spinbuttonj,*spinbuttonm,*spinbuttona,*spinbuttonhdeb_,*spinbuttonmindeb,*spinbuttonhfin,*_spinbuttonminfin,*checkbuttonvoituree__,
*_checkbuttoncamionn,*_checkbuttonmotoo,*entrymatriculee,*comboboxservice,*radiobuttonstandart,*radiobuttonhandicape,*radiobuttonA,*radiobuttonB,*radiobuttonC ,*_radiobuttonsurplaceee,*radiobuttonligneee;



entrynomparking1=lookup_widget(GTK_WIDGET(button),"entrynomparking1");

entryadresseparking1=lookup_widget(GTK_WIDGET(button),"entryadresseparking1");
spinbuttonj=lookup_widget(GTK_WIDGET(button),"spinbuttonj");
spinbuttonm=lookup_widget(GTK_WIDGET(button),"spinbuttonm");
spinbuttona=lookup_widget(GTK_WIDGET(button),"spinbuttona");
spinbuttonhdeb_=lookup_widget(GTK_WIDGET(button),"spinbuttonhdeb_");
spinbuttonmindeb=lookup_widget(GTK_WIDGET(button),"spinbuttonmindeb");
spinbuttonhfin=lookup_widget(GTK_WIDGET(button),"spinbuttonhfin");
_spinbuttonminfin=lookup_widget(GTK_WIDGET(button),"_spinbuttonminfin");
checkbuttonvoituree__=lookup_widget(GTK_WIDGET(button),"checkbuttonvoituree__");
_checkbuttoncamionn=lookup_widget(GTK_WIDGET(button),"_checkbuttoncamionn");
_checkbuttonmotoo=lookup_widget(GTK_WIDGET(button),"_checkbuttonmotoo");
entrymatriculee=lookup_widget(GTK_WIDGET(button),"entrymatriculee");
comboboxservice=lookup_widget(GTK_WIDGET(button),"comboboxservice");
radiobuttonstandart=lookup_widget(GTK_WIDGET(button),"radiobuttonstandart");
radiobuttonhandicape=lookup_widget(GTK_WIDGET(button),"radiobuttonhandicape");
radiobuttonA=lookup_widget(GTK_WIDGET(button),"radiobuttonA");
radiobuttonB=lookup_widget(GTK_WIDGET(button),"radiobuttonB");
radiobuttonC=lookup_widget(GTK_WIDGET(button),"radiobuttonC");
_radiobuttonsurplaceee=lookup_widget(GTK_WIDGET(button),"_radiobuttonsurplaceee");
radiobuttonligneee=lookup_widget(GTK_WIDGET(button),"radiobuttonligneee");


if(strcmp( res.place.type,"standart")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonstandart),TRUE);

}
else if(strcmp( res.place.type,"handicape")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonhandicape),TRUE);

}
if(strcmp( res.place.bloc,"A")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonA),TRUE);

}else if(strcmp( res.place.bloc,"B")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonB),TRUE);

}else if(strcmp( res.place.bloc,"C")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonC),TRUE);
}
      if(strcmp(res.vehicule.type,"voiture")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbuttonvoituree__),TRUE);

}else if(strcmp(res.vehicule.type,"camion")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_checkbuttoncamionn),TRUE);

}else if(strcmp( res.vehicule.type,"moto")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_checkbuttonmotoo),TRUE);
}



if(strcmp( res.service.paiement,"sur place")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(_radiobuttonsurplaceee),TRUE);

}
 if(strcmp( res.service.paiement,"en ligne")==0){
   gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobuttonligneee),TRUE);

}
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonj), res.date_reservation.jour);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonm), res.date_reservation.mois);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttona), res.date_reservation.annee);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonhdeb_), res.heure_debut.heure);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonmindeb), res.heure_debut.minute);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbuttonhfin), res.heure_fin.heure);
gtk_spin_button_set_value(GTK_SPIN_BUTTON(_spinbuttonminfin), res.heure_fin.minute);
gtk_entry_set_text(GTK_ENTRY(entrynomparking1),res.parking.nom);

gtk_entry_set_text(GTK_ENTRY(entryadresseparking1), res.parking.adresse);
gtk_entry_set_text(GTK_ENTRY(entrymatriculee), res.vehicule.matricule);
gtk_combo_box_append_text(GTK_COMBO_BOX(comboboxservice),  res.service.demande_service);  






}


void
on_button19_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *treeview;

    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview2"); // Remplacez "treeview1" par l'ID de votre TreeView

    // Appeler la fonction pour lire les données et les afficher dans le TreeView
   affichage_reservation(GTK_TREE_VIEW(treeview), "Rese.txt");
}


void
on_buttoncreercompteadmn_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
  gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
 gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook1")));
}

