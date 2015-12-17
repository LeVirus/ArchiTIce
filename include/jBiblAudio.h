#ifndef BIBLAUDIO_H
#define BIBLAUDIO_H

#include <string>
#include <map>
#include <vector>


struct Morceau
{
    std::string msNomArtiste, msFichier;
    unsigned int muiDureeMorceau, muiDateSortie;
};

class BiblAudio : public Serveur
{
private:
    std::vector< Morceau > mvectRecherche;

    //conteneur de morceau avec le nom de l'artiste comme cle primaire
    std::map< std::string, Morceau > mmapMorceaux;
public:
    BiblAudio();
    std::vector< Morceau > bRechercherMorceauxArtiste( std::string sNomArtiste, , const Ice::Current& );
    void afficherMorceaux(const Ice::Current&);
    Morceau bRechercherMorceau(std::string sNomMusique, const Ice::Current&);
    bool bAjoutMorceau(std::string sNomArt, std::string sNomMorc, std::string sFic, int uiDureeMorc , int uiDateSortie, const Ice::Current&);
    bool bSuprMorceau(std::string sNomMorc, const Ice::Current&);
};

#endif // BIBLAUDIO_H
