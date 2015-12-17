#include "../include/jBiblAudio.h"
#include <iostream>

BiblAudio::BiblAudio(){

}


 Morceau BiblAudio::bRechercherMorceau( std::string sNomMusique, const Ice::Current&)
{
    Morceau a;
    std::map< std::string, Morceau >::const_iterator it;
    it = mmapMorceaux.find( sNomMusique );
    if( it != mmapMorceaux.end() )
    {

        return (*it).second;
    }
    return a;
}

 std::vector< Morceau > BiblAudio::bRechercherMorceauxArtiste( std::string sNomArtiste, const Ice::Current& )
{
    mvectRecherche.clear();
    for( std::map< std::string, Morceau >::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
        if( ( (*it) . second ).msNomArtiste == sNomArtiste )
        {
            mvectRecherche.push_back( (*it) . second );
            //faire une fonction copie dans Morceau
        }
    }
    return mvectRecherche;
}


void BiblAudio::afficherMorceaux(const Ice::Current&)
{
    for( std::map< std::string, Morceau >::const_iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
        std::cout << (*it) .first <<"\n";
    }
}

bool BiblAudio::bAjoutMorceau(std::string sNomArt,  std::string sNomMorc,  std::string sFic, int uiDureeMorc , int uiDateSortie, const Ice::Current&){
    Morceau morceau;
    morceau.msFichier = sFic;
    morceau.msNomArtiste = sNomArt;
    morceau.muiDateSortie = uiDateSortie;
    morceau.muiDureeMorceau = uiDureeMorc;
    mmapMorceaux . insert( std::pair< std::string, Morceau > ( sNomArt, morceau ) );
    return true;
}

bool BiblAudio::bSuprMorceau( std::string sNomMorc , const Ice::Current&){
    std::map< std::string, Morceau >::iterator it;
    it = mmapMorceaux.find( sNomMorc );
    if( it != mmapMorceaux.end() )
    {
        mmapMorceaux.erase(it);
        return true;
    }
    return false;
}

