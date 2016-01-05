#include "../include/jBiblAudio.h"
#include <iostream>

BiblAudio::BiblAudio(){
    instVLC = libvlc_new (0, NULL);
    pathToLemmy="../music/Lemmy.mp3";
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


biblAudio::mvectRecherche BiblAudio::getMorceauxMorc( const std::string &sNomMorc, const Ice::Current& )
{
    mvectRecherche.clear();
    for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
	if( ( (*it) . second ).msNomMorceau == sNomMorc )
	{
	    mvectRecherche.push_back( (*it) . second );
	    //faire une fonction copie dans Morceau
	}
    }
    return mvectRecherche;
}


biblAudio::mvectRecherche BiblAudio::getMorceauxArt( const std::string &sNomArtiste, const Ice::Current& )
{
    mvectRecherche.clear();
    for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
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
    for( biblAudio::mmapMorceaux::const_iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
    {
	std::cout << (*it) .first <<"\n";
    }
}

/*erreur dans les parametres nomMorceau non traiter
  regenerer l'interface a l'inclusion vlc*/
bool BiblAudio::bAjoutMorceau(const std::string &sNomArt, const  std::string &sNomMorc, const  std::string &sFic,  int uiDureeMorc , int uiDateSortie, const Ice::Current&){
    biblAudio::Morceau morceau;
    morceau.msFichier = sFic;
    morceau.msNomArtiste = sNomMorc;
    morceau.msNomMorceau = sNomArt;
    morceau.muiDateSortie = uiDateSortie;
    morceau.muiDureeMorceau = uiDureeMorc;
    mmapMorceaux . insert( std::pair< std::string, biblAudio::Morceau > ( sNomArt, morceau ) );
    return true;
}

bool BiblAudio::bSuprMorceau( const std::string &sNomArt,const std::string &sNomMorc , const Ice::Current&){
    biblAudio::mmapMorceaux::iterator it;
    it = mmapMorceaux.find( sNomMorc );
    if( it != mmapMorceaux.end() )
    {
	mmapMorceaux.erase(it);
	return true;
    }
    return false;
}

void BiblAudio::prepareSong()
{
    //recherche de la piste à jouer
    mediaVLC = libvlc_media_new_path (instVLC, pathToLemmy.c_str());
    //envoyer les informations au lecteur
    mediaPlayerVLC= libvlc_media_player_new_from_media (mediaVLC);
    //libérer le média
    libvlc_media_release (mediaVLC);
}
void BiblAudio::TESTLireAudio()
{
    libvlc_media_player_play (mediaPlayerVLC);
}
void BiblAudio::TESTStopAudio()
{
    libvlc_media_player_stop (mediaPlayerVLC);
}

void BiblAudio::readSoundFic(const std::string &pathToFic,const Ice::Current&)
{
    pathToLemmy = pathToFic;
prepareSong();
    libvlc_media_player_play (mediaPlayerVLC);
}

void BiblAudio::readSound(const std::string &sNomMorceau,const std::string &sNomArtiste,const Ice::Current&)
{
mvectRecherche = getMorceauxArt( sNomArtiste );
    pathToLemmy = pathToFic;
prepareSong();
    libvlc_media_player_play (mediaPlayerVLC);
}

void BiblAudio::stopSound(const Ice::Current&)
{
    if(mediaPlayerVLC)	    
	libvlc_media_player_stop (mediaPlayerVLC);
}

BiblAudio::~BiblAudio(){
    libvlc_release (instVLC);
    libvlc_media_player_release (mediaPlayerVLC);
}
