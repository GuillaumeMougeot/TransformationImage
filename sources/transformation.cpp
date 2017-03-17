#include <Matrice.hpp>
#include <fstream>
#include <ctime>

const int nbPointsLeger = 208000;
const int nbPointsLourd = 208000;

int main()
{
	/* Trouver les bornes de l'espace dans le fichier "leger" */
	std::ifstream fichier("nuage_1000.txt");
	if(!fichier)
	{
		std::cout << "[Erreur] Impossible de lire le fichier." << std::endl;
		return 1;
	}
	
	std::cout << "[Processus] Calcul des bornes..." << std::endl;
	double xyz_min[3];
	double xyz_max[3];
	double dbl_crt;
	unsigned int i = 0;
	int chargement = 0;
	while(!fichier.eof())
	{
		for(i = 0; i < 3; i++)
		{
			fichier >> dbl_crt;
			if(dbl_crt > xyz_max[i])
			{
				xyz_max[i] = dbl_crt;
			}
			if(dbl_crt < xyz_min[i])
			{
				xyz_min[i] = dbl_crt;
			}
		}
		for(i = 0; i < 6; i++)
		{
			fichier >> dbl_crt;
		}
		
		chargement++;
		if(chargement%(nbPointsLeger/100)==0)
		{
			std::cout << chargement * 100/nbPointsLeger << "/100" << std::endl;
		}
	}
	std::cout << "[Processus] Fin du calcul des bornes." << std::endl;
	
	
	/* Transformation en image dans le fichier "lourd" */
	std::ifstream in("nuage_100.txt");
	std::ofstream out("nuage_out.txt");
	int tailleX = 500;
	int tailleY = (int)round((xyz_max[1]-xyz_min[1])*tailleX/(xyz_max[0]-xyz_min[0]));
	int maxCouleur = 255;
	
	Matrice<double> image(0, tailleX, tailleY);

	long int temps = std::time(NULL);
	
	std::cout << "[Processus] Transformation en image..." << std::endl;
	
	if(!in)
	{
		std::cout << "[Erreur] Impossible de lire le fichier." << std::endl;
		return 1;
	}
	
	chargement = 0;
	while(!in.eof())
	{
		for(i = 0; i < 3; i++)
		{
			in >> vect_crt[i];
		}
		for(i = 0; i < 6; i++)
		{
			in >> tab_crt[i];
		}
		
		vect_crt = (R*vect_crt);
		vect_crt += t;
		
		for(i = 0; i < 3; i++)
		{
			out << vect_crt[i] << " ";
		}
		for(i = 0; i < 6; i++)
		{
			out << tab_crt[i] << " ";
		}
		out << std::endl;
		chargement++;
		if(chargement%(nbPoints/100)==0)
		{
			std::cout << chargement * 100/nbPoints << "/100" << std::endl;
		}
	}
	std::cout << "Duree de l'execution : " << std::time(NULL) - temps << "s" << std::endl;
	
	/* Stockage dans une image PGM */
	
	return 0;
}