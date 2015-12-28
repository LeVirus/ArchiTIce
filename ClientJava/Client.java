import java.util.Scanner;

public class Client {
	public static void
		main(String[] args)
		{
			int status = 0;
			Ice.Communicator ic = null;
			try {
				ic = Ice.Util.initialize(args);
				Ice.ObjectPrx base = ic.stringToProxy("SimplePrinter:default -p 10000");
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
							//bool bSuprMorceau(string sNomMorc );

							System.out.println("Suppression");
							System.out.println("Nom morceau?");
							String nmm = scan.nextLine();
							printer.bSuprMorceau( nmm );

							break;
						case 4:
							//mvectRecherche getMorceaux( string sNomArt);
							System.out.println("Recherche par artiste.");
							System.out.println("Artiste?");
							String naa = scan.nextLine();
							biblAudio.Morceau[] vect = printer.getMorceaux( naa );

							break;
						case 5:
							System.out.println("Quitter.");
							finall=true;
							break;
						default:
							System.out.println("Erreur commande.");
							break;
					}
				}while( finall );


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
		System.out.println("5::Quitter.");

	}
	public static void afficherVect(biblAudio.Morceau[] v){
	  for(int i = 0;i<v.size() ;i++){
	  System.out.println("Artiste::"+v[i].msNomArtiste);
	  System.out.println("Morceau::"+v[i].msFichier);
	//msNomArtiste, msFichier
	}

	}
}
