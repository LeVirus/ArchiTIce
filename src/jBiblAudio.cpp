#include "../include/jBiblAudio.h"
#include <iostream>

BiblAudio::BiblAudio(){
     instVLC = libvlc_new (0, NULL);
}


biblAudio::Morceau BiblAudio::bRechercherMorceau( const std::string &sNomMusique, const Ice::Current&)
{
    biblAudio::Morceau a;
    std::map< std::string, biblAudio::Morceau >::const_iterator it;
    it = mmapMorceaux.find( sNomMusique );
    if( it != mmapMorceaux.end() )
    {

        return (*it).second;
    }
    return a;
}

 /*std::vector< Morceau>*/ biblAudio::mvectRecherche BiblAudio::getMorceaux( const std::string &sNomArtiste, const Ice::Current& )
{
    mvectRecherche.clear();
    for( /*std::map< std::string, Morceau >*/biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
        if( ( (*it) . second ).msNomMorceau == sNomArtiste )
        {
            mvectRecherche.push_back( (*it) . second );
            //faire une fonction copie dans Morceau
        }
    }
    return mvectRecherche;
}


void BiblAudio::afficherMorceaux(const Ice::Current&)
{
    for( /*std::map< std::string, Morceau >*/biblAudio::mmapMorceaux::const_iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
        std::cout << (*it) .first <<"\n";
    }
}

/*erreur dans les parametres nomMorceau non traiter
regenerer l'interface a l'inclusion vlc*/
bool BiblAudio::bAjoutMorceau(const std::string &sNomArt, const  std::string &sNomMorc, const  std::string &sFic,  int uiDureeMorc , int uiDateSortie, const Ice::Current&){
    biblAudio::Morceau morceau;
    morceau.msFichier = sFic;
    morceau.msNomMorceau = sNomArt;
    morceau.muiDateSortie = uiDateSortie;
    morceau.muiDureeMorceau = uiDureeMorc;
    mmapMorceaux . insert( std::pair< std::string, biblAudio::Morceau > ( sNomArt, morceau ) );
    return true;
}

bool BiblAudio::bSuprMorceau( const std::string &sNomMorc , const Ice::Current&){
    /*std::map< std::string, Morceau >*/biblAudio::mmapMorceaux::iterator it;
    it = mmapMorceaux.find( sNomMorc );
    if( it != mmapMorceaux.end() )
    {
        mmapMorceaux.erase(it);
        return true;
    }
    return false;
}

