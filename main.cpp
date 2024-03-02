#include <core/Core.hpp>

//  Todo:                                                                                                                                               (non ordonnée)
//
// !--> Mettre en compatibilité le système de threading quand il sera fait, pendant 42
// !--> Système de décompression : 'inflate' (pour la compression DEFLATE)      {petra_images.h}
// !--> Système pour convertir BGR à RGB & BGRA à RGBA                          {petra_images.h}
// !--> Changer la façon dont la fonction 'DrawThisScene()' fonctionne, individuellement et spécifiquement si nécessaire
//  1 - Modifier l'allocation dynamique de mémoire dans 'Cube.hpp/cpp'
//  2 - Ne faire le rendu des objets avec des listes entières et complètes mais avec des indices de listes/de valeurs
//  3 - Trouver de bonnes coordonnées (U, V) pour les textures sur un simple cube entier
//  4 - Finir de coder le fichier petra_images.h (JPEG, JPG, TIFF, TIF, PNG, décompression, compression, écriture)
//  5 - Une classe Mesh qui aura pour utiliter de contenir tous les buffers destinés à effectuer le rendu du produit demandé
//  6 - Dans la fonction 'PutMultiplesTextures()' mettre en place le code erreur IMAGE_NOT_FOUND (qui est pour l'instant inutilisé)
// ??? A - Potentiellement mettre en commun dans une liste les uvsBufferID pour les objets identiques utilisant les mêmes (types de) textures. Pour les objets identiques.
// ??? B - Quand un nouvel objet apparaît sur la scène vérifier si cela freeze quelques millisecondes le jeu ou non. Si oui empêcher cela par un envoie de signal que cet objet
// ?      viens tout juste d'être créée, et donc ne pas faire le rendu instantanément, attendre un tick.

int main()
{
        // Initialisation du moteur
    int errorCode = Core::InitEngine();
    if (errorCode < 0)      return_error("Initialisation du moteur échouée", errorCode)

        // Charge les informations contenus dans le JSON "to_load.json" et les utilise par la suite
    ArrayForJSON* jsonLoader = new ArrayForJSON();
    if ((errorCode = Core::JSONLoader(jsonLoader)) < 0)
        return_error("Erreur lors de la récupération des informations du fichier 'to_load.json'", errorCode);
    if ((errorCode = Core::CompileAllShaders(*jsonLoader)) < 0)
        return_error("Erreur lors de la compilation des shaders", errorCode);
    Core::CreateAllImportedTextures(*jsonLoader);
    Core::FreeJSON(jsonLoader);

        // Boucle principale
    return (Core::Loop());
}

// glissement sémentique