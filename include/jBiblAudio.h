#ifndef BIBLAUDIO_H
#define BIBLAUDIO_H

#include <string>
#include <map>
#include <vector>
#include "../include/interface.h"


struct Morceau
{
    std::string msNomArtiste, msFichier;
    int muiDureeMorceau, muiDateSortie;
};

class BiblAudio : public  biblAudio :: ServeurIce
{
private:
   /*std::vector< Morceau >*/ biblAudio::mvectRecherche mvectRecherche;

    //conteneur de morceau avec le nom de l'artiste comme cle primaire
    /*std::map< std::string, Morceau >*/biblAudio::mmapMorceaux  mmapMorceaux;
public:
    BiblAudio();
    /*std::vector< Morceau >*/biblAudio::mvectRecherche getMorceaux( const std::string &sNomArtiste, const Ice::Current& );
    void afficherMorceaux(const Ice::Current&);

    biblAudio::Morceau bRechercherMorceau(const std::string &sNomMusique, const Ice::Current&);

    bool bAjoutMorceau(const std::string &sNomArt, const std::string &sNomMorc,const  std::string &sFic, int uiDureeMorc , int uiDateSortie, const Ice::Current&);
    bool bSuprMorceau(const std::string &sNomMorc, const Ice::Current&);
};

#endif // BIBLAUDIO_H 
