#include "Tools.h"
#include <fstream>

Tools::Tools()
{
}


Tools::~Tools()
{
}

/*genere les tableaux R en sortie standard*/
void Tools::generateRMatrix(int* tab, int taille, char* nomVariable, char* nomFichier, char* modeOuverture)
{
	int i;
	FILE* fichier = NULL;
	fichier = fopen(nomFichier, modeOuverture);

	if (fichier != NULL)
	{
		fprintf(fichier, "%s = [", nomVariable);
		for (i = 0; i < taille; ++i)
		{
			fprintf(fichier, "%d", tab[i]);
			if (i != taille - 1){
				fprintf(fichier, ", ");
			}
		}
		fprintf(fichier, "];\n");
	}
	else
	{
		printf("Erreur fichier");
		exit(EXIT_FAILURE);
	}
	fclose(fichier);
}


