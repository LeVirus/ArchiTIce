#include "../include/jBiblAudio.h"
#include <iostream>
#include <Ice/Ice.h>


BiblAudio::BiblAudio(){

    Ice::CommunicatorPtr ic;
            /*try {
                    ic = Ice::initialize();
                    Ice::ObjectPrx obj = ic->stringToProxy("IceStorm/TopicManager:tcp -p 9999");
                    IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(obj);
                    IceStorm::TopicPrx topic;
                    while (!topic) {
                            try {
                                    topic = topicManager->retrieve("StreamPlayerNotifs");
                                    std::cout << "Retrieving topic...\n";
                            } catch (const IceStorm::NoSuchTopic&) {
                                    std::cout << "No topic!\n";
                                    try {
                                            topic = topicManager->create("StreamPlayerNotifs");
                                            std::cout << "Creating topic...\n";
                                    } catch(const IceStorm::TopicExists&) {
                                    }
                            }
                    }
                    std::cout << "Topic active!\n";
                    Ice::ObjectPrx pub = topic->getPublisher()->ice_twoway();
                    monitor = Monitor ::uncheckedCast(pub);
                    std::cout << "Monitor active!\n";
            } catch (const Ice::Exception& e) {
                    std::cerr << e << '\n';
            }*/

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

    for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it ){
	if((*it).first == sNomMorc && (*it).second.msNomArtiste == sNomArt)
	{
	    mmapMorceaux.erase(it);
	    return true;
	}
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

void BiblAudio::readSoundFic(const std::string &pathToFic,const Ice::Current&)
{
    pathToLemmy = pathToFic;
    prepareSong();
    libvlc_media_player_play (mediaPlayerVLC);
}

void BiblAudio::readSound(const std::string &sNomMorceau,const std::string &sNomArtiste,const Ice::Current& iceCurrent)
{
    mvectRecherche = getMorceauxArt( sNomArtiste, iceCurrent );
    biblAudio::Morceau morc = rechercherMorceauVect( mvectRecherche , sNomMorceau);
    if(morc.msNomMorceau == "erreur")return; 
    pathToLemmy = morc.msFichier;
    prepareSong();
    libvlc_media_player_play (mediaPlayerVLC);
}

biblAudio::Morceau BiblAudio::rechercherMorceauVect( biblAudio::mvectRecherche mvectMorc,const std::string &nomMorc )
{
    for(unsigned int i = 0;i<mvectMorc.size();i++)
    {
	if(mvectMorc[i].msNomMorceau == nomMorc)
	    return mvectMorc[i];
    }
    biblAudio::Morceau a;
    a.msNomMorceau = "erreur";
    return a;
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
