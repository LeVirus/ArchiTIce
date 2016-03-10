#ifndef BIBLAUDIO_H
#define BIBLAUDIO_H

#include <string>
#include <map>
#include <vector>
#include "vlc/vlc.h"
#include <IceStorm/IceStorm.h>
#include "../include/interface.h"
#include "../include/IceStorm/IceStorm.h"
#include "../include/IceUtil/Monitor.h"




struct Morceau
{
    std::string msNomArtiste, msFichier;
    int muiDureeMorceau, muiDateSortie;
};

/*class MonitorI : virtual public biblAudio::Monitor{
    public:
	virtual void report(const std::string& action, const Morceau &morceau, const Ice::Current&) {
	    std::cout<<action<<"\n";
	}
};*/

class BiblAudio : public  biblAudio :: ServeurIce
{
    private:
	biblAudio::mvectRecherche mvectRecherche;
	biblAudio::mmapMorceaux  mmapMorceaux;
	biblAudio::MonitorPrx monitor;
	libvlc_instance_t * instVLC;
	libvlc_media_player_t *mediaPlayerVLC;
	libvlc_media_t *mediaVLC;
	std::string pathToLemmy;
    public:
	BiblAudio();
	biblAudio::mvectRecherche getMorceauxArt( const std::string &sNomArtiste, const Ice::Current& );
	biblAudio::Morceau rechercherMorceauVect( biblAudio::mvectRecherche mvectMorc,const std::string &nomMorc );
	void afficherMorceauVect( const biblAudio::mvectRecherche &mvectMorc )const;
	biblAudio::mvectRecherche getMorceauxMorc( const std::string &sNomMorc, const Ice::Current& );
	void afficherMorceaux(const Ice::Current&);
	void stopSound(const Ice::Current&);

	biblAudio::Morceau bRechercherMorceau(const std::string &sNomMusique, const Ice::Current&);

	bool bAjoutMorceau(const std::string &sNomArt, const std::string &sNomMorc,const  std::string &sFic, int uiDureeMorc , int uiDateSortie, const Ice::Current&);
	bool bSuprMorceau(const std::string &sNomArt,const std::string &sNomMorc, const Ice::Current&);
	void readSoundFic(const std::string &pathToFic,const Ice::Current&);
	void readSound(const std::string &sNomMorceau,const std::string &sNomArtiste,const Ice::Current&);
	void prepareSong();
	~BiblAudio();
};

#endif // BIBLAUDIO_H 
