/*
 * Header pour la traitement des points
 *
*/
//Définition du type de point en coordonnées carthésiennes
typedef struct {
  int x, y;
} Point_carth;

//Définition du type de point en coodonnées polaires
typedef struct{
  int theta, d;
} Point_polaire;

//Nouveau point Carthésien
Point_carth point_new_C(int x, int y);
//Nouveau point Polaire
Point_polaire point_new_P(int theta, int d);

//Conversion Polaire vers Carthésien.
Point_carth PolaireToCarth(Point_polaire point);
