import java.util.Scanner;

public class Client {
    public static void
	main(String[] args)
	{
	    int status = 0;
	    Ice.Communicator ic = null;
	    try {
		ic = Ice.Util.initialize(args);
		Ice.ObjectPrx base = ic.stringToProxy("BiblAudio:default -p 10000");
		biblAudio.ServeurIcePrx printer = biblAudio.ServeurIcePrxHelper.checkedCast(base);
		if (printer == null)
		    throw new Error("Invalid proxy");
		Scanner scan = new Scanner(System.in);
		int choix;
		boolean finall = false;
		do{
		    choix = 10;
		    System.out.println("Taper 0 pour afficher l'aide.");
		    choix = scan.nextInt();
		    switch( choix ){
			case 0:
			    afficherMenu();
			    break;
			case 1:
			    System.out.println("Affichage morceaux.");

			    printer.afficherMorceaux();
			    break;
			case 2:
			    System.out.println("Ajout morceau.");
			    //bool bAjoutMorceau(string sNomArt,  string sNomMorc,  string sFic,  int uiDureeMorc ,  int uiDateSortie);

			    System.out.println("Artiste?");
			    String na = scan.nextLine();
			    System.out.println("Nom morceau?");
			    String nm = scan.nextLine();
			    System.out.println("Chemin fichier?");
			    String cf = scan.nextLine();
			    System.out.println("Duree?");
			    int d = scan.nextInt();
			    System.out.println("Date sortie?");
			    int ds= scan.nextInt();
			    printer.bAjoutMorceau(na,  nm,  cf,  d ,  ds);
			    break;
			case 3:

			    System.out.println("Suppression");
			    System.out.println("Nom morceau?");
			    String nmm = scan.nextLine();
			    System.out.println("Nom artiste?");
			    String nma = scan.nextLine();
			    printer.bSuprMorceau( nmm, nma );

			    break;
			case 4:
			    System.out.println("Recherche par artiste.");
			    System.out.println("Artiste?");
			    String naa = scan.nextLine();
			    biblAudio.Morceau[] vect = printer.getMorceauxArt( naa );
			    break;
			case 5:
			    System.out.println("Recherche par nom.");
			    System.out.println("Nom morceau?");
			    String nab = scan.nextLine();
			    biblAudio.Morceau[] vectt = printer.getMorceauxMorc( nab );
			    break;
			case 6:
			    System.out.println("Jouer morceau par fichier.");
			    System.out.println("Entrer le chemin d'acces au fichier.");
			    String nac = scan.nextLine();
			     nac = scan.nextLine();
			    printer.readSoundFic(nac);
			    break;
			case 7:
			    System.out.println("Jouer morceau recherché.");
			    System.out.println("Nom morceau?");
			    String nmt = scan.nextLine();
			    System.out.println("Nom artiste?");
			    String nmy = scan.nextLine();
			    printer.readSound(nmt,nmy);
			    break;
			case 8:
			    System.out.println("Arréter lecture en cour.");
			    printer.stopSound();
			    break;
			case 9:
			    System.out.println("Quitter.");
			    finall=true;
			    break;
			default:
			    System.out.println("Erreur commande.");
			    break;
		    }
		}while( !finall );


	    } catch (Ice.LocalException e) {
		e.printStackTrace();
		status = 1;
	    } catch (Exception e) {
		System.err.println(e.getMessage());
		status = 1;
	    }
	    if (ic != null) {
		// Clean up
		//
		try {
		    ic.destroy();
		} catch (Exception e) {
		    System.err.println(e.getMessage());
		    status = 1;
		}
	    }
	    System.exit(status);
	}

    public static void afficherMenu(){
	System.out.println("0::Afficher ce menu.");
	System.out.println("1::Afficher morceaux.");
	System.out.println("2::Ajouter morceau.");
	System.out.println("3::Supprimer morceau");
	System.out.println("4::Rechercher morceaux par artiste.");
	System.out.println("5::Rechercher morceaux par nom.");
	System.out.println("6::Jouer morceau par fichier.");
	System.out.println("7::Jouer morceau recherchée.");
	System.out.println("8::Arréter la lecture en cour..");
	System.out.println("9::Quitter.");

    }
    public static void afficherVect(biblAudio.Morceau[] v){
	for(int i = 0;i<v.length ;i++){
	    System.out.println("Artiste::"+v[i].msNomArtiste);
	    System.out.println("Morceau::"+v[i].msFichier);
	    //msNomArtiste, msFichier
	}

    }
}
