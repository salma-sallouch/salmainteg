#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "ajouter.h"


void on_Ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    printf("test");
    AvisReclamationDetails avis = {0};  // Initialisation complète de la structure

    GtkWidget *entry1;
    GtkWidget *entry6;
    GtkWidget *entry2;
    GtkWidget *RadioButton1, *reclamation;
    GtkWidget *entry_categorie;
    GtkWidget *spinbutton1;
    GtkWidget *spinbuttonjour;
    GtkWidget *spinbuttonmois;
    GtkWidget *spinbuttonannes;
    GtkWidget *CheckButton1;

    GtkWidget *dialog;  // Boîte de dialogue

    entry1 = lookup_widget(objet_graphique, "entry1");
    entry2 = lookup_widget(objet_graphique, "entry2");
    entry6 = lookup_widget(objet_graphique, "entry6");
    RadioButton1 = lookup_widget(objet_graphique, "RadioButton1");
    reclamation = lookup_widget(objet_graphique, "reclamation");
    entry_categorie = lookup_widget(objet_graphique, "entry_categorie");
    spinbutton1 = lookup_widget(objet_graphique, "spinbutton1");
    spinbuttonjour = lookup_widget(objet_graphique, "spinbuttonjour");
    spinbuttonmois = lookup_widget(objet_graphique, "spinbuttonmois");
    spinbuttonannes = lookup_widget(objet_graphique, "spinbuttonannes");
    CheckButton1 = lookup_widget(objet_graphique, "CheckButton1");

    if (entry1 == NULL) {
        g_print("Erreur : entry1 non trouvé\n");
        return;  // Quitter la fonction si le widget est introuvable
    }
    printf("test2");

    // Récupérer le texte de l'entry1 (id_client)
    const gchar *id_client_text = gtk_entry_get_text(GTK_ENTRY(entry1));
    if (id_client_text == NULL || strlen(id_client_text) == 0) {
        g_print("Erreur : l'ID client est vide\n");
        return;
    }
   
    // Convertir le texte en entier pour id_client
    avis.id_client = atoi(id_client_text);
    if (avis.id_client == 0 && strcmp(id_client_text, "0") != 0) {
        g_print("Erreur : ID client invalide\n");
        return;
    }

    // Récupérer les autres données
    strcpy(avis.contenu, gtk_entry_get_text(GTK_ENTRY(entry2)));
    avis.id_parking = atoi(gtk_entry_get_text(GTK_ENTRY(entry6)));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(RadioButton1))) {
        strcpy(avis.type_demande, "avis");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(reclamation))) {
        strcpy(avis.type_demande, "reclamation");
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(CheckButton1))) {
        strcpy(avis.urgent, "urgent");
    }  

    strcpy(avis.categorie, gtk_combo_box_get_active_text(GTK_COMBO_BOX(entry_categorie)));
    avis.date_reclamation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonjour));
    avis.date_reclamation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonmois));
    avis.date_reclamation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbuttonannes));
    avis.note_satisfaction = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton1));

    // Appeler la fonction d'ajout
    ajouterAvis(avis, "avis.txt");

    // Création d'une boîte de dialogue pour confirmer l'ajout
    dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(objet_graphique)),
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "L'avis a été ajouté avec succès !");
   
    gtk_window_set_title(GTK_WINDOW(dialog), "Succès");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);  // Détruire la boîte de dialogue après fermeture
}







void
on_button_afficher_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *treeview;

    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview1"); // Remplacez "treeview1" par l'ID réel de votre TreeView

    if (treeview == NULL) {
        g_print("Erreur : Impossible de trouver le widget TreeView.\n");
        return;
    }

    // Appeler la fonction pour lire les données et les afficher dans le TreeView
    afficher_avis(GTK_TREE_VIEW(treeview), "avis.txt");
}


void
on_button_precedent_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}


void on_button_modifier_clicked(GtkButton *button, gpointer user_data) {
    AvisReclamationDetails avis_temp;

    // Récupérer les widgets
    GtkWidget *entry3, *entry4, *entry7;
    GtkWidget *radiobutton1, *radiobutton2, *combobox1;
    GtkWidget *spinbutton2, *spinbutton3, *spinbutton4, *spinbutton5;
    GtkWidget *checkbutton1;

    entry3 = lookup_widget(GTK_WIDGET(button), "entry3");
    entry4 = lookup_widget(GTK_WIDGET(button), "entry4");
    entry7 = lookup_widget(GTK_WIDGET(button), "entry7");
    radiobutton1 = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radiobutton2 = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    combobox1 = lookup_widget(GTK_WIDGET(button), "combobox1");
    spinbutton2 = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    spinbutton3 = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    spinbutton4 = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    spinbutton5 = lookup_widget(GTK_WIDGET(button), "spinbutton5");
    checkbutton1 = lookup_widget(GTK_WIDGET(button), "checkbutton1");

    // Lire l'ID à modifier
    int Id = atoi(gtk_entry_get_text(GTK_ENTRY(entry3)));

    // Récupérer les nouvelles données à partir des widgets
    strcpy(avis_temp.contenu, gtk_entry_get_text(GTK_ENTRY(entry4)));
    avis_temp.id_parking = atoi(gtk_entry_get_text(GTK_ENTRY(entry7)));

    avis_temp.note_satisfaction = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton2));
    avis_temp.date_reclamation.jour = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton3));
    avis_temp.date_reclamation.mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton4));
    avis_temp.date_reclamation.annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinbutton5));

    strcpy(avis_temp.categorie, gtk_combo_box_get_active_text(GTK_COMBO_BOX(combobox1)));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbutton1))) {
        strcpy(avis_temp.urgent, "urgent");
    } else {
        strcpy(avis_temp.urgent, "");
    }

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton1))) {
        strcpy(avis_temp.type_demande, "avis");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radiobutton2))) {
        strcpy(avis_temp.type_demande, "reclamation");
    } else {
        strcpy(avis_temp.type_demande, "");  // Valeur par défaut
    }

    // Vérification : s'assurer que l'ID et les champs essentiels sont valides
    if (Id <= 0 || strlen(avis_temp.contenu) == 0 || strlen(avis_temp.type_demande) == 0) {
        GtkWidget *dialog_error = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
            "Erreur : Champs obligatoires manquants ou ID invalide !");
        gtk_dialog_run(GTK_DIALOG(dialog_error));
        gtk_widget_destroy(dialog_error);
        return;
    }

    // Boîte de dialogue pour confirmer la modification
    GtkWidget *dialog_confirm = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment modifier l'avis avec ID : %d ?", Id);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog_confirm));
    gtk_widget_destroy(dialog_confirm);

    if (response == GTK_RESPONSE_YES) {
        // Appeler la fonction de modification
        modifier_reserv("avis.txt", Id, avis_temp);

        // Afficher un message de succès
        GtkWidget *dialog_success = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            "L'avis avec ID %d a été modifié avec succès.", Id);
        gtk_dialog_run(GTK_DIALOG(dialog_success));
        gtk_widget_destroy(dialog_success);
    } else {
        // Annulation de la modification
        GtkWidget *dialog_cancel = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            "Modification annulée.");
        gtk_dialog_run(GTK_DIALOG(dialog_cancel));
        gtk_widget_destroy(dialog_cancel);
    }
}


void
on_button_suivant_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}




void on_button_cherche_clicked(GtkButton *button, gpointer user_data) {
    AvisReclamationDetails avis;

    GtkWidget *entry3;
    int Id;
    entry3 = lookup_widget(GTK_WIDGET(button), "entry3");

    // Convertir le texte de l'entrée en entier
    Id = atoi(gtk_entry_get_text(GTK_ENTRY(entry3)));

    // Appeler la fonction de recherche
    avis = cherche("avis.txt", Id);

    // Widgets pour afficher les résultats
    GtkWidget *entry4, *entry7;
    GtkWidget *radiobutton1, *radiobutton2;
    GtkWidget *combobox1;
    GtkWidget *spinbutton2, *spinbutton3, *spinbutton4, *spinbutton5;
    GtkWidget *checkbutton1;

    entry4 = lookup_widget(GTK_WIDGET(button), "entry4");
    entry7 = lookup_widget(GTK_WIDGET(button), "entry7");
    radiobutton1 = lookup_widget(GTK_WIDGET(button), "radiobutton1");
    radiobutton2 = lookup_widget(GTK_WIDGET(button), "radiobutton2");
    combobox1 = lookup_widget(GTK_WIDGET(button), "combobox1");
    spinbutton2 = lookup_widget(GTK_WIDGET(button), "spinbutton2");
    spinbutton3 = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    spinbutton4 = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    spinbutton5 = lookup_widget(GTK_WIDGET(button), "spinbutton5");
    checkbutton1 = lookup_widget(GTK_WIDGET(button), "checkbutton1");

    // Vérifier si l'ID existe
    if (avis.id_client == -1) {
        // Afficher un message si ID non trouvé
        gtk_entry_set_text(GTK_ENTRY(entry4), "Non trouvé");
        gtk_entry_set_text(GTK_ENTRY(entry7), "Non trouvé");
        return;
    }

    // Mettre à jour les widgets avec les données trouvées
    if (strcmp(avis.type_demande, "avis") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton1), TRUE);
    } else if (strcmp(avis.type_demande, "reclamation") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radiobutton2), TRUE);
    }

    if (strcmp(avis.urgent, "urgent") == 0) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton1), TRUE);
    } else {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbutton1), FALSE);
    }

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton2), avis.note_satisfaction);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton3), avis.date_reclamation.jour);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton4), avis.date_reclamation.mois);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spinbutton5), avis.date_reclamation.annee);

    char result[20];
    sprintf(result, "%d", avis.id_parking);
    gtk_entry_set_text(GTK_ENTRY(entry7), result);
    gtk_entry_set_text(GTK_ENTRY(entry4), avis.contenu);
    gtk_combo_box_append_text(GTK_COMBO_BOX(combobox1), avis.categorie);
}


void
on_button_suivant1_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));

}


void on_button_supprimer_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry5;
    int Id;

    // Récupérer l'entrée pour l'ID client
    entry5 = lookup_widget(GTK_WIDGET(button), "entry5");
    Id = atoi(gtk_entry_get_text(GTK_ENTRY(entry5)));

    // Vérifier si l'ID est valide
    if (Id <= 0) {
        GtkWidget *dialog = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK,
            "ID invalide. Veuillez entrer un ID correct !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return; // Quitter la fonction si l'ID est invalide
    }

    // Boîte de dialogue de confirmation
    GtkWidget *dialog_confirm = gtk_message_dialog_new(
        NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO, "Êtes-vous sûr de vouloir supprimer l'avis avec ID : %d ?", Id);

    gint response = gtk_dialog_run(GTK_DIALOG(dialog_confirm));
    gtk_widget_destroy(dialog_confirm);

    if (response == GTK_RESPONSE_YES) {
        // Appel de la fonction pour supprimer l'avis
        supprimerAvis(Id, "avis.txt");

        // Message de confirmation
        GtkWidget *dialog_success = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            "L'avis avec ID %d a été supprimé avec succès.", Id);
        gtk_dialog_run(GTK_DIALOG(dialog_success));
        gtk_widget_destroy(dialog_success);
    } else {
        // Annulation de la suppression
        GtkWidget *dialog_cancel = gtk_message_dialog_new(
            NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
            "Suppression annulée.");
        gtk_dialog_run(GTK_DIALOG(dialog_cancel));
        gtk_widget_destroy(dialog_cancel);
    }
}



void
on_button_precedent2_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}


void
on_button_suivant3_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}




void
on_button_trier_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview;

    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview3"); // Remplacez "treeview1" par l'ID réel de votre TreeView

    if (treeview == NULL) {
        g_print("Erreur : Impossible de trouver le widget TreeView.\n");
        return;
    }

    // Appeler la fonction pour lire les données et les afficher dans le TreeView
    affichage_trie(GTK_TREE_VIEW(treeview), "avis.txt");
}


void
on_button_affichagetous_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *treeview;

    // Trouver le TreeView par son ID ou son nom dans la fenêtre principale
    treeview = lookup_widget(GTK_WIDGET(button), "treeview2"); // Remplacez "treeview1" par l'ID réel de votre TreeView

    if (treeview == NULL) {
        g_print("Erreur : Impossible de trouver le widget TreeView.\n");
        return;
    }

    // Appeler la fonction pour lire les données et les afficher dans le TreeView
    afficher_avis(GTK_TREE_VIEW(treeview), "avis.txt");
}


void
on_button_precedent555_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}


void
on_button_suivant555_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_next_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}


void
on_button_precedent666_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(button, "notebook")));
}

