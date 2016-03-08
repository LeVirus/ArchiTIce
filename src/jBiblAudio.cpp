#include "../include/jBiblAudio.h"
#include <iostream>
#include <Ice/Ice.h>


BiblAudio::BiblAudio(){
    Ice::CommunicatorPtr ic;
    try {
	ic = Ice::initialize(/*argc, argv*/);


	Ice::ObjectPrx obj = ic->stringToProxy("IceStorm/TopicManager:tcp -p 9999");
	IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(obj);
	IceStorm::TopicPrx topic;

	while (!topic) {
	    try {
		topic = topicManager->retrieve("Weather");
	    } catch (const IceStorm::NoSuchTopic&) {
		try {
		    topic = topicManager->create("Weather");
		} catch (const IceStorm::TopicExists&) {
		    // Another client created the topic.
		}
	    }
	}
    } catch (const Ice::Exception& e) {
	std::cerr << e << std::endl;
	//status = 1;
    } catch (const char* msg) {
	std::cerr << msg << std::endl;
	//status = 1;
    }

	instVLC = libvlc_new (0, NULL);
        pathToLemmy="../music/";

}


biblAudio::Morceau BiblAudio::bRechercherMorceau( const std::string &sNomMusique, const Ice::Current&)
{
	biblAudio::Morceau a;
        //std::map< std::string, biblAudio::Morceau >::const_iterator it;
        //it = mmapMorceaux.find( sNomMusique );

        for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
        {
                if(  (*it) . first  == sNomMusique )
                {
                        mvectRecherche.push_back( (*it) . second );
                }
        }

        /*if( it != mmapMorceaux.end() )
	{

		return (*it).second;
        }*/
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
        afficherMorceauVect(mvectRecherche);

	return mvectRecherche;
}


biblAudio::mvectRecherche BiblAudio::getMorceauxArt( const std::string &sNomArtiste, const Ice::Current& )
{
	mvectRecherche.clear();
	for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
	{
                if(  (*it) . first  == sNomArtiste )
		{
			mvectRecherche.push_back( (*it) . second );
		}
	}

        afficherMorceauVect(mvectRecherche);

	return mvectRecherche;
}


void BiblAudio::afficherMorceaux(const Ice::Current&)
{

    std::cout << "Affichage morceaux serveur\n";
	for( biblAudio::mmapMorceaux::const_iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
	{
		std::cout << (*it) .first <<"\n";
                std::cout << "Chemin fichier::"<< (*it) .second.msFichier <<"\n";
                std::cout << "Nom artiste::"<< (*it) .second.msNomArtiste <<"\n";
                std::cout << "Nom morceau::"<< (*it) .second.msNomMorceau <<"\n";
                std::cout << "Date de sortie::"<< (*it) .second.muiDateSortie <<"\n";
                std::cout << "Durée::"<< (*it) .second.muiDureeMorceau <<"\n";
	}
        std::cout << "Fin morceaux serveur\n";
}

bool BiblAudio::bAjoutMorceau(const std::string &sNomArt, const  std::string &sNomMorc, const  std::string &sFic,  int uiDureeMorc , int uiDateSortie, const Ice::Current& c){
	biblAudio::Morceau morceau;
	morceau.msFichier = sFic;
	morceau.msNomArtiste = sNomMorc;
	morceau.msNomMorceau = sNomArt;
	morceau.muiDateSortie = uiDateSortie;
	morceau.muiDureeMorceau = uiDureeMorc;
         mmapMorceaux . insert( std::pair< std::string, biblAudio::Morceau > ( sNomArt, morceau ) );

        std::cout << "Morceau ajouté"<<sNomMorc<<"\n";
	return true;
}

bool BiblAudio::bSuprMorceau( const std::string &sNomArt,const std::string &sNomMorc , const Ice::Current&){
	biblAudio::mmapMorceaux::iterator it;
	it = mmapMorceaux.find( sNomMorc );

	for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it ){
		if((*it).first == sNomMorc && (*it).second.msNomArtiste == sNomArt)
		{
			mmapMorceaux.erase(it);
                        std::cout << "Morceau supprimé::"<<sNomMorc<<"\n";
			return true;
		}
	}
        std::cout << "Morceau non trouvé.\n";
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
        if(morc.msNomMorceau == "erreur"){
            std::cerr<<"erreur lecture morceau "<<sNomMorceau<<"\n";
            return;
        }
	pathToLemmy = morc.msFichier;
	prepareSong();
	libvlc_media_player_play (mediaPlayerVLC);
}

biblAudio::Morceau BiblAudio::rechercherMorceauVect( biblAudio::mvectRecherche mvectMorc,const std::string &nomMorc )
{
	for(unsigned int i = 0;i<mvectMorc.size();i++)
	{
            std::cerr<<mvectMorc[i].msNomMorceau<<"    "<<nomMorc<<"\n";
		if(mvectMorc[i].msNomMorceau == nomMorc)
			return mvectMorc[i];
	}
	biblAudio::Morceau a;
	a.msNomMorceau = "erreur";
	return a;
}

void BiblAudio::afficherMorceauVect( const biblAudio::mvectRecherche &mvectMorc )const
{
    std::cout<<"Affichage morceaux recherchés\n";
    for( unsigned int i=0;i<mvectMorc.size();++i)
    {
            std::cout << "Chemin fichier::"<< mvectMorc[i].msFichier <<"\n";
            std::cout << "Nom artiste::"<< mvectMorc[i].msNomArtiste <<"\n";
            std::cout << "Nom morceau::"<< mvectMorc[i].msNomMorceau <<"\n";
            std::cout << "Date de sortie::"<< mvectMorc[i].muiDateSortie <<"\n";
            std::cout << "Durée::"<< mvectMorc[i].muiDureeMorceau <<"\n";

    }
    std::cout<<"Fin affichage\n";
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
