module biblAudio
{
    struct Morceau
    {
	string msNomMorceau;
	string msNomArtiste;
	string msFichier;
	int muiDateSortie;
	int muiDureeMorceau;
    };


    sequence<Morceau> mvectRecherche;
    dictionary<string, Morceau> mmapMorceaux;

    interface ServeurIce
    {
	void afficherMorceaux();
	Morceau bRechercherMorceau(string sNomMusique );
	bool bAjoutMorceau(string sNomArt,  string sNomMorc,  string sFic,  int uiDureeMorc ,  int uiDateSortie);
	bool bSuprMorceau(string sNomMorc, string sNomArt );
	mvectRecherche getMorceauxArt( string sNomArt);
	mvectRecherche getMorceauxMorc( string sNomMorc);
	void stopSound();
	void readSoundFic(string pathToFic);
	void readSound(string sNomMorceau, string sNomArtiste);
    };
};
