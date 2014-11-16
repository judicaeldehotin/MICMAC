#include "GpGpu/GpGpu_ParamCorrelation.cuh"
#include "GpGpu/GpGpu_TextureTools.cuh"
#include "GpGpu/GpGpu_TextureCorrelation.cuh"
#include "GpGpu/SData2Correl.h"


// Algorithme Correlation multi echelle sur ligne epipolaire

// Donn�es :
//  - 2 images avec diff�rents niveaux de floutage

// Pr�-calcul et param�tres
// - Tableau de parcours des vignettes
// - Tableau du ZMin et ZMax de chaque coordonn�es terrain
// - les offsets Terrain <--> Image Epi
// - le masque erod� de l'image 1

// Inconnu
// Phase??? mNbByPix


/*  CPU
 *
 *  pour chaque
 *      - calcul des images interpol�es pour l'image 1
 *      - mise en vecteur des images interpol�es
 *      - Precalcul somme et somme quad
 *      - Parcour du terrain
 *      - Calcul de la projection image 0
 *      - Parcours des Z
 *          - Calcul de la projection image 1
 *          - Calcul de la correlation Quick_MS_CorrelBasic_Center
 *              - pour chaque echelle
 *                  - Calcul de correlation
 *
 *      - set cost dans la matrice de regularisation
 */
