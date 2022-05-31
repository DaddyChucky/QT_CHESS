/**
* Projet final :: INF1015 :: Livrable 3.
* \file   Modele.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/

#include "Modele.h"
#include "IU.h"

#if __has_include("bibliotheque_cours.hpp")
#include "bibliotheque_cours.hpp"
#define BIBLIOTHEQUE_COURS_INCLUS
#endif

#if __has_include("verification_allocation.hpp")
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"
#endif

void initialiserBibliothequeCours([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
	#ifdef BIBLIOTHEQUE_COURS_INCLUS
	bibliotheque_cours::activerCouleursAnsi();
	bibliotheque_cours::executerGoogleTest(argc, argv);
	#endif
}

static const std::string LIGNE_SEPARATION_TITRE	= "\033[1m\n\033[30m═\033[31m═\033[32m═\033[33m═\033[34m═\033[35m═\033[36m═\033[37m═\033[90m═\033[91m═\033[92m═\033[93m═\033[94m═\033[95m═\033[96m═\033[97m═\033[30m═\033[31m═\033[32m═\033[33m═\033[34m═\033[35m═\033[36m═\033[37m═\033[90m═\033[91m═\033[92m═\033[93m═\033[94m═\033[95m═\033[96m═\033[97m═\033[30m═\033[31m═\033[32m═\033[33m═\033[34m═\033[35m═\033[36m═\033[37m═\033[90m═\033[91m═\033[92m═\033[93m═\033[94m═\033[95m═\033[96m═\033[97m═\033[30m═\033[0m\n";

int main(int argc, char *argv[])
{
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	initialiserBibliothequeCours(argc, argv);
	QApplication			app(argc, argv);
	vue::EchiquierWindow	echiquier;

	std::cout << LIGNE_SEPARATION_TITRE << "\n\033[35mProjet final INF1015 - Échecs :: Livrable 3\033[0m\n" << LIGNE_SEPARATION_TITRE << std::endl;

	echiquier.show();
	echiquier.addApp(&app);
	app.exec();
}
