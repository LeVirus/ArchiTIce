#include "../include/jBiblAudio.h"
//#include <chrono>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <Ice/Ice.h>


BiblAudio::BiblAudio(){
	Ice::CommunicatorPtr ic;
	try {
		ic = Ice::initialize(/*argc, argv*/);


		Ice::ObjectPrx obj = ic->stringToProxy("IceStorm/TopicManager:tcp -h 127.0.0.1 -p 9999");

		IceStorm::TopicManagerPrx topicManager = IceStorm::TopicManagerPrx::checkedCast(obj);


		//Ice::ObjectAdapterPtr adapter = ic->createObjectAdapter("MonitorAdapter");
		//biblAudio::MonitorPtr monitor = new MonitorI;

		/*	Ice::ObjectPrx proxy = adapter->addWithUUID(monitor)->ice_oneway();
			adapter->activate();
		 */

		IceStorm::TopicPrx topic;
		while (!topic) {
			std::cerr << "recuperation du topic\n";
			try {
				topic = topicManager->retrieve("MusicTopic");
				IceStorm::QoS qos;
				//topic->subscribeAndGetPublisher(qos, proxy);
			} catch (const IceStorm::NoSuchTopic&) {
				std::cerr << "pas de topic\n";
				try {
					topic = topicManager->create("MusicTopic");
					std::cerr << "creation du topic\n";
				} catch (const IceStorm::TopicExists&) {
					std::cerr << "another client create the topic\n";
					// Another client created the topic.
				}
			}
		}



		Ice::ObjectPrx pub = topic->getPublisher()->ice_twoway();
		monitor = biblAudio::MonitorPrx::uncheckedCast(pub);

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

	std::cerr << "Affichage morceaux serveur\n";
	for( biblAudio::mmapMorceaux::const_iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it )
	{
		std::cerr << (*it) .first <<"\n";
		std::cerr << "Chemin fichier::"<< (*it) .second.msFichier <<"\n";
		std::cerr << "Nom artiste::"<< (*it) .second.msNomArtiste <<"\n";
		std::cerr << "Nom morceau::"<< (*it) .second.msNomMorceau <<"\n";
		std::cerr << "Date de sortie::"<< (*it) .second.muiDateSortie <<"\n";
		std::cerr << "Durée::"<< (*it) .second.muiDureeMorceau <<"\n";
	}
	std::cerr << "Fin morceaux serveur\n";
}

bool BiblAudio::bAjoutMorceau(const std::string &sNomArt, const  std::string &sNomMorc, const  std::string &sFic,  int uiDureeMorc , int uiDateSortie, const Ice::Current& c){
	biblAudio::Morceau morceau;
	morceau.msFichier = sFic;
	morceau.msNomArtiste = sNomMorc;
	morceau.msNomMorceau = sNomArt;
	morceau.muiDateSortie = uiDateSortie;
	morceau.muiDureeMorceau = uiDureeMorc;
	mmapMorceaux . insert( std::pair< std::string, biblAudio::Morceau > ( sNomArt, morceau ) );
	monitor->report("add", morceau);
	std::cerr << "Morceau ajouté"<<sNomMorc<<"\n";
	return true;
}

bool BiblAudio::bSuprMorceau( const std::string &sNomArt,const std::string &sNomMorc , const Ice::Current&){
	biblAudio::mmapMorceaux::iterator it;
	it = mmapMorceaux.find( sNomMorc );

	for( biblAudio::mmapMorceaux::iterator it = mmapMorceaux.begin(); it != mmapMorceaux.end(); ++it ){
		if((*it).first == sNomMorc && (*it).second.msNomArtiste == sNomArt)
		{
			monitor->report("del", (*it).second);
			mmapMorceaux.erase(it);
			std::cerr << "Morceau supprimé::"<<sNomMorc<<"\n";
			return true;
		}
	}
	std::cerr << "Morceau non trouvé.\n";
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

void BiblAudio::readSoundFic(const std::string &pathToFic,const Ice::Current& curIce)
{

	Ice::IPConnectionInfo* ipCoInfo = dynamic_cast<Ice::IPConnectionInfo*>(curIce.con->getInfo().get());
	//auto duration = std::chrono::system_clock::now().time_since_epoch();


	std::string Result;          // string which will contain the result

	std::ostringstream convert;   // stream used for the conversion

	convert << ipCoInfo->remotePort;      // insert the textual representation of 'Number' in the characters in the stream

	Result = convert.str();


	std::string token = ipCoInfo->remoteAddress.substr(7) + "." + Result/*std::to_string(ipCoInfo->remotePort)*/ + "." + "100000"/*std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count())*/;
	/*std::string ssout = "#transcode{acodec=mp3,ab=128,channels=2," \
			     "samplerate=44100}:http{dst=:8090/"+token+".mp3}";*/
	std::string ssout = "#transcode{vcodec=h264,fps=25,venc=x264{preset=ultrafast,"\
		"profile=baseline,tune=zerolatency},vb=512,"                              \
		"acodec=mpga,ab=64,channels=2}"                                           \
		":duplicate{dst=display,dst=standard{access=udp,mux=ts,dst=127.0.0.1:"+Result+"}}";
	const char* sout = ssout.c_str();

	std::cerr<<ipCoInfo->remotePort<<"   \n"<<token<<"\n"<<pathToFic<<"\n";;

	//std::string path = "songs/"+s.path;
	libvlc_vlm_add_broadcast(instVLC, token.c_str(), pathToFic.c_str(), sout, 0, NULL, true, false);

	//libvlc_vlm_add_broadcast(instVLC, media_name, url, sout, 0, NULL, true, false);
	pathToLemmy = pathToFic;
	//prepareSong();
	libvlc_vlm_play_media(instVLC, token.c_str());
	//libvlc_media_player_play (mediaPlayerVLC);
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
	std::cerr<<"Affichage morceaux recherchés\n";
	for( unsigned int i=0;i<mvectMorc.size();++i)
	{
		std::cerr << "Chemin fichier::"<< mvectMorc[i].msFichier <<"\n";
		std::cerr << "Nom artiste::"<< mvectMorc[i].msNomArtiste <<"\n";
		std::cerr << "Nom morceau::"<< mvectMorc[i].msNomMorceau <<"\n";
		std::cerr << "Date de sortie::"<< mvectMorc[i].muiDateSortie <<"\n";
		std::cerr << "Durée::"<< mvectMorc[i].muiDureeMorceau <<"\n";

	}
	std::cerr<<"Fin affichage\n";
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
