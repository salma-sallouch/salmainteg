#ifndef aycem_h
#define aycem_h
#include<stdio.h>
#include <stdlib.h>


typedef struct {
   int vehicule[12][31];  // 12 mois et 31 jours
} parkingv;



float calculer_moyenne_par_jour(parkingv pv, int mois);
float calculer_moyenne_par_mois(parkingv pv);
float calculer_moyenne_par_annee(parkingv pv);
#endif
