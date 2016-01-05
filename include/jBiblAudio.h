#ifndef BIBLAUDIO_H
#define BIBLAUDIO_H

#include <string>
#include <map>
#include <vector>
#include "vlc/vlc.h"
#include "../include/interface.h"


struct Morceau
{
    std::string msNomArtiste, msFichier;
    int muiDureeMorceau, muiDateSortie;
};

class BiblAudio : public  biblAudio :: ServeurIce
{
    private:
	biblAudio::mvectRecherche mvectRecherche;
	biblAudio::mmapMorceaux  mmapMorceaux;
	libvlc_instance_t * instVLC;
	libvlc_media_player_t *mediaPlayerVLC;
	libvlc_media_t *mediaVLC;
	std::string pathToLemmy;
    public:
	BiblAudio();
	biblAudio::mvectRecherche getMorceaux( const std::string &sNomArtiste, const Ice::Current& );
	void afficherMorceaux(const Ice::Current&);

	biblAudio::Morceau bRechercherMorceau(const std::string &sNomMusique, const Ice::Current&);

	bool bAjoutMorceau(const std::string &sNomArt, const std::string &sNomMorc,const  std::string &sFic, int uiDureeMorc , int uiDateSortie, const Ice::Current&);
	bool bSuprMorceau(const std::string &sNomMorc, const Ice::Current&);
	void prepareSong();
	void TESTLireAudio();
	void TESTStopAudio();
	~BiblAudio();
};

#endif // BIBLAUDIO_H 
