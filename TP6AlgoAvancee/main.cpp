//
//  main.cpp
//  TP6AlgoAvancee
//
//  Created by Hadrien Delobel on 15/03/2023.
//

#include <iostream>
#include <vector>
#include <chrono>
const int TAILLEDUGRAPHE = 6;
const int INFINI = 9999999;
const int MAX = 500;
using namespace::std;
std::vector<string> vecSommets;
vector<int> Distance;
int arcs[TAILLEDUGRAPHE][TAILLEDUGRAPHE];//Cette structure me fait penser à la matrice d'adjacence
int cheminCourt[TAILLEDUGRAPHE][TAILLEDUGRAPHE];
int pointChemin[TAILLEDUGRAPHE][TAILLEDUGRAPHE];

void afficherChemin (int sommet1, int sommet2, bool & premier) {
    int suivant = pointChemin[sommet1][sommet2];
    if (suivant==-1 || sommet1 == sommet2 || suivant == sommet1 || suivant == sommet2)
    return;
    afficherChemin (sommet1, suivant, premier);
    if (premier) {
        std::cout << " \t\t par ";
        premier = false;
        
    } else {
        std::cout << " et ";
    }
    std::cout << vecSommets[suivant];
    afficherChemin (suivant, sommet2, premier);
}
auto t1 = chrono::high_resolution_clock::now();
int main(int argc, const char * argv[]) {
    // insert code here...
    srand(static_cast<unsigned int>(time(NULL)));
    for(int i = 0;i < 6;i++){
        Distance.push_back(rand()%MAX);
    }
    Distance.push_back(INFINI);
    for(int i = 0;i<TAILLEDUGRAPHE;i++){
        for(int j=0;j<TAILLEDUGRAPHE;j++){
            if(i!=j){
                arcs[i][j] = INFINI;
            }else{
                arcs[i][j] = INFINI;
            }
        }
    }
    vecSommets.push_back("Lille");
    vecSommets.push_back("Lens");
    vecSommets.push_back("Paris");
    vecSommets.push_back("Bourges");
    vecSommets.push_back("Clermont-Ferrand");
    vecSommets.push_back("Montpellier");
    arcs[0][1] = 40;
    arcs[0][2] = 230;
    arcs[1][2] = 200;
    arcs[2][3] = 250;
    arcs[2][4] = 425;
    arcs[3][4] = 190;
    arcs[4][5] = 300;
    for(int i = 0;i < TAILLEDUGRAPHE; i++){
        for(int j = 0; j < TAILLEDUGRAPHE; j++){
            if(arcs[i][j] == INFINI || arcs[i][j] == 0){
                pointChemin[i][j] = -1;
            }else{
                pointChemin[i][j] = i;
            }
        }
    }
    
    for(int i = 0; i<TAILLEDUGRAPHE;i++){
        for(int j = 0;j<TAILLEDUGRAPHE;j++){
            cheminCourt[i][j] = arcs[i][j];
        }
    }
    /*
     L'algorithme de Floyd-Warshall est un algorithme de programmation dynamique utilisé pour trouver les chemins les plus courts entre tous les paires de sommets d'un graphe pondéré. Sa complexité en temps est de O(n^3), où n est le nombre de sommets du graphe.

     Le nombre d'instructions élémentaires maximales à réaliser dans l'algorithme de Floyd-Warshall est donc proportionnel à n^3. Si on note i, j et k les indices des boucles de l'algorithme, on peut estimer le nombre d'instructions élémentaires comme suit :

     Initialisation des tableaux de distances et de prédécesseurs : O(n^2)
     Boucle k : O(n)
     Boucles i et j imbriquées : O(n^2)
     Mise à jour des distances et des prédécesseurs : O(1)
     Le nombre total d'instructions élémentaires est donc :

     O(n^2) + O(n) * O(n^2) * O(1) = O(n^3)

     Ainsi, le nombre d'instructions élémentaires maximales à réaliser dans l'algorithme de Floyd-Warshall est de l'ordre de n^3, où n est le nombre de sommets du graphe.
     */
    
    for(int intermediaire = 0; intermediaire < TAILLEDUGRAPHE; intermediaire++){
        for(int origine = 0; origine < TAILLEDUGRAPHE; origine++){
            for(int destination=0; destination < TAILLEDUGRAPHE; destination++){
                if((cheminCourt[origine][intermediaire]+cheminCourt[intermediaire][destination]) < cheminCourt[origine][destination]){
                    cheminCourt[origine][destination] = cheminCourt[origine][intermediaire]  +cheminCourt[intermediaire][destination];
                    pointChemin[origine][destination] = intermediaire;
                }
            }
        }
    }
    for(int i = 0;i<TAILLEDUGRAPHE;i++){
        for(int j = i;j<TAILLEDUGRAPHE;j++){
            if( i != j){
                cout << "Sommets intermediares de PCCh de " << cheminCourt[i][j] << ",(s'ils existent) de " << vecSommets[i] << " vers " << vecSommets[j] << "." << endl;
                bool Premier = true;
                afficherChemin(i, j, Premier);
                cout << endl;
            }
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
    cout << endl << duree << " micros." << endl;
    cout << endl;
    return 0;
}
