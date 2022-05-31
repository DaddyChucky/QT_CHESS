/**
* Projet final :: INF1015 :: Livrable 3. Test des fonctions implémentées dans le main.
* \file   TestEchecs.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/

#pragma once
#include "Modele.h"
#include "IU.h"

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST


/**
*  Vérification des positions lors de la création du plateau initialement.
*/
TEST(Plateau, verificationsPositionsPieces) {
	constexpr int		X_CAVALIER_BLANC										= 2;
	constexpr int		Y_CAVALIER_BLANC										= 0;
	constexpr int		X_CAVALIER_NOIR											= 6;
	constexpr int		Y_CAVALIER_NOIR											= 7;
	constexpr int		X_ROI_BLANC												= 4;
	constexpr int		Y_ROI_BLANC												= 0;
	constexpr int		X_ROI_NOIR												= 3;
	constexpr int		Y_ROI_NOIR												= 7;
	constexpr int		X_TOUR_BLANCHE											= 7;
	constexpr int		Y_TOUR_BLANCHE											= 0;
	constexpr int		X_TOUR_NOIRE											= 0;
	constexpr int		Y_TOUR_NOIRE											= 7;
	constexpr char		CAVALIER_BLANC											= 'N';
	constexpr char		ROI_BLANC												= 'K';
	constexpr char		TOUR_BLANCHE											= 'R';
	constexpr char		CAVALIER_NOIR											= 'n';
	constexpr char		ROI_NOIR												= 'k';
	constexpr char		TOUR_NOIRE												= 'r';
	const std::string	PLATEAU_CONFIGURATION_VERIFICATIONS_POSITIONS_PIECES	= "xxNxKxxR/8/8/8/8/8/8/rxxkxxnx w";

	modele::Plateau plateau{ modele::Couleur::Blanc };
	plateau.creer(PLATEAU_CONFIGURATION_VERIFICATIONS_POSITIONS_PIECES);
	plateau.reinitialiserNRois();

	//? Le plateau doit être occupé
	EXPECT_EQ(plateau.getCase(X_CAVALIER_BLANC, Y_CAVALIER_BLANC)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(X_ROI_BLANC, Y_ROI_BLANC)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(X_TOUR_BLANCHE, Y_TOUR_BLANCHE)->getOccupation(), true);

	EXPECT_EQ(plateau.getCase(X_CAVALIER_NOIR, Y_CAVALIER_NOIR)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(X_ROI_NOIR, Y_ROI_NOIR)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getOccupation(), true);

	//? Le plateau doit être occupé par des pièces valides
	EXPECT_EQ(plateau.getCase(X_CAVALIER_BLANC, Y_CAVALIER_BLANC)->getPieceOccupante()->getCaractere(), CAVALIER_BLANC);
	EXPECT_EQ(plateau.getCase(X_ROI_BLANC, Y_ROI_BLANC)->getPieceOccupante()->getCaractere(), ROI_BLANC);
	EXPECT_EQ(plateau.getCase(X_TOUR_BLANCHE, Y_TOUR_BLANCHE)->getPieceOccupante()->getCaractere(), TOUR_BLANCHE);

	EXPECT_EQ(plateau.getCase(X_CAVALIER_NOIR, Y_CAVALIER_NOIR)->getPieceOccupante()->getCaractere(), CAVALIER_NOIR);
	EXPECT_EQ(plateau.getCase(X_ROI_NOIR, Y_ROI_NOIR)->getPieceOccupante()->getCaractere(), ROI_NOIR);
	EXPECT_EQ(plateau.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getPieceOccupante()->getCaractere(), TOUR_NOIRE);
}


/**
*  Vérification des positions générales valides des pièces et de l'échange.
*/ 
TEST(Plateau, verificationsMouvementsSimplesPieces) {
	constexpr int				X_CAVALIER_BLANC										= 2;
	constexpr int				Y_CAVALIER_BLANC										= 0;
	constexpr int				X_ROI_NOIR												= 3;
	constexpr int				Y_ROI_NOIR												= 7;
	constexpr int				X_TOUR_NOIRE											= 0;
	constexpr int				Y_TOUR_NOIRE											= 7;
	constexpr size_t			MOUVEMENTS_POSSIBLES_CAVALIER_BLANC						= 4;
	constexpr size_t			MOUVEMENTS_POSSIBLES_ROI_NOIR							= 5;
	constexpr size_t			MOUVEMENTS_POSSIBLES_TOUR_NOIRE							= 9;
	const std::string			PLATEAU_CONFIGURATION_VERIFICATIONS_MOUVEMENTS_SIMPLES	= "xxNxKxxR/8/8/8/8/8/8/rxxkxxnx w";
	const std::pair<int, int>	MOUVEMENT_POSSIBLE_CAVALIER_BLANC						= { 4, 1 };
	const std::pair<int, int>	MOUVEMENT_POSSIBLE_ROI_NOIR								= { 1, 6 };
	const std::pair<int, int>	MOUVEMENT_POSSIBLE_TOUR_NOIRE							= { 0, 0 };
	constexpr char				CAVALIER_BLANC											= 'N';
	constexpr char				ROI_NOIR												= 'k';
	constexpr char				TOUR_NOIRE												= 'r';

	modele::Plateau plateau{ modele::Couleur::Blanc };

	plateau.creer(PLATEAU_CONFIGURATION_VERIFICATIONS_MOUVEMENTS_SIMPLES);
	plateau.reinitialiserNRois();
	plateau.reinitialiserPositionsValidesPieces();


	//? Vérification des positions valides des différentes pièces du plateau
	//? Pour le cavalier blanc
	EXPECT_EQ(plateau.getCase(X_CAVALIER_BLANC, Y_CAVALIER_BLANC)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_CAVALIER_BLANC);

	//? Nous inversons le tour et recalculons les positions valides pour les pièces noires
	plateau.inverserTour();
	plateau.reinitialiserPositionsValidesPieces();

	//? Pour le roi noir
	EXPECT_EQ(plateau.getCase(X_ROI_NOIR, Y_ROI_NOIR)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_ROI_NOIR);

	//? Pour la tour noire
	EXPECT_EQ(plateau.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_TOUR_NOIRE);


	//? Ensuite, vérifions que le jeu continue suite au mouvement des pièces
	//? Pour le cavalier blanc
	plateau.effectuerChangementPosition(plateau.getCase(X_CAVALIER_BLANC, Y_CAVALIER_BLANC), plateau.getCase(MOUVEMENT_POSSIBLE_CAVALIER_BLANC.first, MOUVEMENT_POSSIBLE_CAVALIER_BLANC.second));

	//? Vérifions qu'il n'y a plus aucune occupation à l'ancienne case du cavalier
	EXPECT_EQ(plateau.getCase(X_CAVALIER_BLANC, Y_CAVALIER_BLANC)->getOccupation(), false);

	//? Vérifions que le tour a bien été inversé (initialement noir)
	EXPECT_EQ(plateau.getTour(), modele::Couleur::Blanc);

	//? Vérifions que le cavalier occupe maintenant la nouvelle case
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_CAVALIER_BLANC.first, MOUVEMENT_POSSIBLE_CAVALIER_BLANC.second)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_CAVALIER_BLANC.first, MOUVEMENT_POSSIBLE_CAVALIER_BLANC.second)->getPieceOccupante()->getCaractere(), CAVALIER_BLANC);


	//? Pour le roi noir
	plateau.effectuerChangementPosition(plateau.getCase(X_ROI_NOIR, Y_ROI_NOIR),
		plateau.getCase(MOUVEMENT_POSSIBLE_ROI_NOIR.first, MOUVEMENT_POSSIBLE_ROI_NOIR.second));

	//? Vérifions qu'il n'y a plus aucune occupation à l'ancienne case du roi
	EXPECT_EQ(plateau.getCase(X_ROI_NOIR, Y_ROI_NOIR)->getOccupation(), false);

	//? Vérifions que le tour a bien été inversé (initialement blanc)
	EXPECT_EQ(plateau.getTour(), modele::Couleur::Noir);

	//? Vérifions que le roi occupe maintenant la nouvelle case
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_ROI_NOIR.first, MOUVEMENT_POSSIBLE_ROI_NOIR.second)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_ROI_NOIR.first, MOUVEMENT_POSSIBLE_ROI_NOIR.second)->getPieceOccupante()->getCaractere(), ROI_NOIR);

	//? Pour la tour noire
	plateau.effectuerChangementPosition(plateau.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE), plateau.getCase(MOUVEMENT_POSSIBLE_TOUR_NOIRE.first, MOUVEMENT_POSSIBLE_TOUR_NOIRE.second));

	//? Vérifions qu'il n'y a plus aucune occupation à l'ancienne case du roi
	EXPECT_EQ(plateau.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getOccupation(), false);

	//? Vérifions que le tour a bien été inversé (initialement noir)
	EXPECT_EQ(plateau.getTour(), modele::Couleur::Blanc);

	//? Vérifions que le roi occupe maintenant la nouvelle case
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_TOUR_NOIRE.first, MOUVEMENT_POSSIBLE_TOUR_NOIRE.second)->getOccupation(), true);
	EXPECT_EQ(plateau.getCase(MOUVEMENT_POSSIBLE_TOUR_NOIRE.first, MOUVEMENT_POSSIBLE_TOUR_NOIRE.second)->getPieceOccupante()->getCaractere(), TOUR_NOIRE);
}


/**
*  Vérification des positions valides des rois lorsqu'ils sont face à face.
*/
TEST(Plateau, verificationsRoisFaceAFace) {
	//? Pour les rois face à face
	constexpr int		X_ROI_NOIR												= 1;
	constexpr int		Y_ROI_NOIR												= 0;
	constexpr int		X_ROI_BLANC												= 1;
	constexpr int		Y_ROI_BLANC												= 2;
	constexpr size_t	nbMOUVEMENTS_POSSIBLES_ROI_NOIR							= 2;
	constexpr size_t	nbMouvementsPossiblesROI_BLANC							= 5;
	const std::string	PLATEAU_CONFIGURATION_VERIFICATIONS_ROIS_FACE_A_FACE	= "xkxxxxxx/8/xKxxxxxx/8/8/8/8/8 b";
	
	modele::Plateau plateauRoisFaceAFace{ modele::Couleur::Blanc };

	plateauRoisFaceAFace.creer(PLATEAU_CONFIGURATION_VERIFICATIONS_ROIS_FACE_A_FACE);
	plateauRoisFaceAFace.reinitialiserNRois();
	plateauRoisFaceAFace.reinitialiserPositionsValidesPieces();

	//? Vérifions que le roi noir ne peut pas avancer pour être face à face au roi blanc
	EXPECT_EQ(plateauRoisFaceAFace.getCase(X_ROI_NOIR, Y_ROI_NOIR)->getPieceOccupante()->getMouvementsPossibles().size(), nbMOUVEMENTS_POSSIBLES_ROI_NOIR);

	plateauRoisFaceAFace.inverserTour();
	plateauRoisFaceAFace.reinitialiserPositionsValidesPieces();

	//? Vérifions que le roi blanc ne peut pas avancer pour être face à face au roi noir
	EXPECT_EQ(plateauRoisFaceAFace.getCase(X_ROI_BLANC, Y_ROI_BLANC)->getPieceOccupante()->getMouvementsPossibles().size(), nbMouvementsPossiblesROI_BLANC);
}


/**
*  Vérification de la suppression des pièces.
*/
TEST(Plateau, verificationsSuppressionPieces) {
	constexpr int		X_TOUR_NOIRE											= 0;
	constexpr int		Y_TOUR_NOIRE											= 0;
	constexpr int		X_TOUR_BLANCHE											= 0;
	constexpr int		Y_TOUR_BLANCHE											= 7;
	constexpr char		TOUR_BLANCHE											= 'R';
	const std::string	PLATEAU_CONFIGURATION_VERIFICATIONS_ROIS_FACE_A_FACE	= "rxxxxxxx/8/8/8/8/8/8/RxxxkxxK b";

	modele::Plateau plateauSuppression{ modele::Couleur::Blanc };
	plateauSuppression.creer(PLATEAU_CONFIGURATION_VERIFICATIONS_ROIS_FACE_A_FACE);
	plateauSuppression.reinitialiserNRois();
	plateauSuppression.effectuerChangementPosition(plateauSuppression.getCase(X_TOUR_BLANCHE, Y_TOUR_BLANCHE), plateauSuppression.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE));

	//? Vérifier que la tour blanche n'est plus à son endroit initial
	EXPECT_EQ(plateauSuppression.getCase(X_TOUR_BLANCHE, Y_TOUR_BLANCHE)->getOccupation(), false);

	//? Vérifier que la tour blanche est maintenant à l'ancienne position de la tour noire et que cette dernière n'existe plus
	EXPECT_EQ(plateauSuppression.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getOccupation(), true);
	EXPECT_EQ(plateauSuppression.getCase(X_TOUR_NOIRE, Y_TOUR_NOIRE)->getPieceOccupante()->getCaractere(), TOUR_BLANCHE);
}


/**
*  Teste l'initialisation des noms des cases.
*/
TEST(Plateau, verificationsNomsCases) {
	const std::string	PLATEAU_CONFIGURATION		= "8/8/8/8/8/8/8/8 w";
	constexpr int		POSITION_PREMIERE_CASE_X	= 0;
	constexpr int		POSITION_PREMIERE_CASE_Y	= 0;
	constexpr int		POSITION_DERNIERE_CASE_X	= 7;
	constexpr int		POSITION_DERNIERE_CASE_Y	= 7;
	const std::string	NOM_PREMIERE_CASE			= "A8";
	const std::string	NOM_DERNIERE_CASE			= "H1";

	modele::Plateau plateau{ modele::Couleur::Blanc };

	try {
		plateau.creer(PLATEAU_CONFIGURATION);
	}

	//? Nous créons un plateau sans roi, nous devons gérer l'exception
	catch (modele::NombreRoisExact&) {
		EXPECT_EQ(plateau.getCase(POSITION_PREMIERE_CASE_X, POSITION_PREMIERE_CASE_Y)->getNomCase(), NOM_PREMIERE_CASE);
		EXPECT_EQ(plateau.getCase(POSITION_DERNIERE_CASE_X, POSITION_DERNIERE_CASE_Y)->getNomCase(), NOM_DERNIERE_CASE);
	}
}


/**
*  Teste l'initialisation des noms des cases.
*/
TEST(Plateau, verificationMouvementsTours) {
	constexpr int		TOUR_BLANCHE_POSITION_X					= 4;
	constexpr int		TOUR_BLANCHE_POSITION_Y					= 5;
	constexpr size_t	MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE	= 4;
	const std::string	CONFIGURATION_PLATEAU					= "xxxxxxxK/8/8/8/xxxxrxxx/xxxrRnxx/xxxxrxxx/kxxxxxxx w";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(TOUR_BLANCHE_POSITION_X, TOUR_BLANCHE_POSITION_Y)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE);
}


/**
*  Teste les mouvements reliés à l'échec de la tour.
*/
TEST(Plateau, verificationMouvementEchecTour) {
	constexpr int		TOUR_BLANCHE_POSITION_XInitiale			= 7;
	constexpr int		TOUR_BLANCHE_POSITION_YInitiale			= 0;
	constexpr int		TOUR_BLANCHE_POSITION_XEchec			= 6;
	constexpr int		TOUR_BLANCHE_POSITION_YEchec			= 0;
	constexpr size_t	MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE	= 1;
	constexpr int		TOUR_NOIRE_POSITION_X					= 4;
	constexpr int		TOUR_NOIRE_POSITION_Y					= 4;
	const std::string	CONFIGURATION_PLATEAU					= "KxxxxxxR/8/8/8/xxxxrxxx/8/8/xxxxxxkx w";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();
	plateauEchec.effectuerChangementPosition(plateauEchec.getCase(TOUR_BLANCHE_POSITION_XInitiale, TOUR_BLANCHE_POSITION_YInitiale),
	plateauEchec.getCase(TOUR_BLANCHE_POSITION_XEchec, TOUR_BLANCHE_POSITION_YEchec));
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(TOUR_NOIRE_POSITION_X, TOUR_NOIRE_POSITION_Y)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE);
}


/**
*  Teste les mouvements reliés à l'échec du cavalier.
*/
TEST(Plateau, verificationMouvementEchecCavalier) {
	constexpr size_t	MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE	= 1;
	constexpr int		CAVALIER_BLANC_POS_INITIALE_X			= 3;
	constexpr int		CAVALIER_BLANC_POS_INITIALE_Y			= 4;
	constexpr int		CAVALIER_BLANC_POS_ECHEC_X				= 1;
	constexpr int		CAVALIER_BLANC_POS_ECHEC_Y				= 5;
	constexpr int		TOUR_NOIRE_POSITION_X					= 4;
	constexpr int		TOUR_NOIRE_POSITION_Y					= 5;
	const std::string	CONFIGURATION_PLATEAU					= "xxxxxxxK/8/8/8/xxxNxxxx/xxxxrxxx/8/kxxxxxxx w";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();
	plateauEchec.effectuerChangementPosition(plateauEchec.getCase(CAVALIER_BLANC_POS_INITIALE_X, CAVALIER_BLANC_POS_INITIALE_Y),
	plateauEchec.getCase(CAVALIER_BLANC_POS_ECHEC_X, CAVALIER_BLANC_POS_ECHEC_Y));
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(TOUR_NOIRE_POSITION_X, TOUR_NOIRE_POSITION_Y)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE);
}


/**
*  Teste les mouvements qui empêchent l'échec par le cavalier (protection du roi).
*/
TEST(Plateau, verificationMouvementCavalierEmpecheEchec) {
	constexpr size_t	MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE	= 1;
	constexpr int		TOUR_NOIRE_POSITION_XInitiale			= 4;
	constexpr int		TOUR_NOIRE_POSITION_YInitiale			= 5;
	constexpr int		TOUR_NOIRE_POSITION_XEchec				= 4;
	constexpr int		TOUR_NOIRE_POSITION_YEchec				= 0;
	constexpr int		CAVALIER_BLANC_POS_X					= 2;
	constexpr int		CAVALIER_BLANC_POS_Y					= 1;
	const std::string	CONFIGURATION_PLATEAU					= "xxxxxxxK/xxNxxxxx/8/8/8/xxxxrxxx/8/kxxxxxxx b";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();
	plateauEchec.effectuerChangementPosition(plateauEchec.getCase(TOUR_NOIRE_POSITION_XInitiale, TOUR_NOIRE_POSITION_YInitiale),
	plateauEchec.getCase(TOUR_NOIRE_POSITION_XEchec, TOUR_NOIRE_POSITION_YEchec));
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(CAVALIER_BLANC_POS_X, CAVALIER_BLANC_POS_Y)->getPieceOccupante()->getMouvementsPossibles().size(), MOUVEMENTS_POSSIBLES_TOUR_NOIR_TAILLE);
}


/**
*  Teste les mouvements du roi entouré de pièces ennemies.
*/
TEST(Plateau, verificationMouvementRoiPieceEnnemie) {
	constexpr size_t	NOMBRE_MOUVEMENTS_POSSIBLES = 1;
	constexpr int		POSITION_ROI_X				= 4;
	constexpr int		POSITION_ROI_Y				= 5;
	const std::string	CONFIGURATION_PLATEAU		= "8/xxkxxxxx/8/8/xxxNNNxx/xxxNKRxx/xxxNNrxx/8 w";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(POSITION_ROI_X, POSITION_ROI_Y)->getPieceOccupante()->getMouvementsPossibles().size(), NOMBRE_MOUVEMENTS_POSSIBLES);
}


/**
*  Teste les mouvements de la tour en regardant les options lorsque le roi est en échec.
*/
TEST(Plateau, verificationMouvementTourPermetEnleverEchec) {
	constexpr size_t	NOMBRE_MOUVEMENTS_POSSIBLES		= 1;
	constexpr int		POSITION_INITIALE_TOUR_NOIRE_X	= 4;
	constexpr int		POSITION_INITIALE_TOUR_NOIRE_Y	= 5;
	constexpr int		POSITION_ECHEC_TOUR_NOIRE_X		= 4;
	constexpr int		POSITION_ECHEC_TOUR_NOIRE_Y		= 0;
	constexpr int		POSITION_TOUR_BLANCHE_X			= 0;
	constexpr int		POSITION_TOUR_BLANCHE_Y			= 0;
	const std::string	CONFIGURATION_PLATEAU			= "RxxxxxxK/8/8/8/8/xxxxrxxx/8/xxxxxxxk b";

	modele::Plateau plateauEchec{ modele::Couleur::Blanc };
	plateauEchec.reinitialiserNRois();
	plateauEchec.creer(CONFIGURATION_PLATEAU);
	plateauEchec.reinitialiserPositionsValidesPieces();
	plateauEchec.effectuerChangementPosition(plateauEchec.getCase(POSITION_INITIALE_TOUR_NOIRE_X, POSITION_INITIALE_TOUR_NOIRE_Y),
	plateauEchec.getCase(POSITION_ECHEC_TOUR_NOIRE_X, POSITION_ECHEC_TOUR_NOIRE_Y));
	plateauEchec.inverserEchec();
	plateauEchec.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateauEchec.getCase(POSITION_TOUR_BLANCHE_X, POSITION_TOUR_BLANCHE_Y)->getPieceOccupante()->getMouvementsPossibles().size(), NOMBRE_MOUVEMENTS_POSSIBLES);
}


/**
*  Teste la fonction qui permet de changer les tours des joueurs.
*/
TEST(Plateau, verificationSetTour) {
	modele::Plateau plateau{ modele::Couleur::Blanc };
	plateau.setTour(modele::Couleur::Noir);

	EXPECT_EQ(plateau.getTour(), modele::Couleur::Noir);
}


/**
*  Teste une instanciation d'un plateau qui possède trop de rois.
*/
TEST(Plateau, verificationPlateauTropDeRois) {
	try {
		const std::string CONFIGURATION_PLATEAU_INVALIDE = "kKkKkKkK/8/8/8/8/8/8/8 w";
		modele::Plateau plateau{ modele::Couleur::Blanc };
		plateau.creer(CONFIGURATION_PLATEAU_INVALIDE);
	}

	catch (modele::NombreRoisExact&) {
		//? L'exception a bien été captée
		EXPECT_EQ(true, true);
	}
}


/**
*  Teste les vérifications des mouvements pour un roi en échec.
*/
TEST(Plateau, verificationMouvementsRoiEnEchec) {
	constexpr size_t	NOMBRE_MOUVEMENTS_POSSIBLES		= 8;
	constexpr int       POSITION_ROI_NOIRE_X_INITIAL	= 0;
	constexpr int       POSITION_ROI_NOIRE_Y_INITIAL	= 2;
	constexpr int       POSITION_INITIAL_TOUR_BLANCHE_X = 1;
	constexpr int       POSITION_INITIAL_TOUR_BLANCHE_Y = 1;
	constexpr int       POSITION_ECHEC_TOUR_BLANCHE_X	= 1;
	constexpr int       POSITION_ECHEC_TOUR_BLANCHE_Y	= 2;
	constexpr int       POSITION_ROI_NOIR_DEPLACEMENT_X = 0;
	constexpr int       POSITION_ROI_NOIR_DEPLACEMENT_Y = 1;
	const std::string	CONFIGURATION_PLATEAU_VALIDE	= "nxxxxxxx/xRxxxxxx/kxKxxxxx/8/8/8/8/8 w";

	modele::Plateau plateau{ modele::Couleur::Blanc };
	plateau.reinitialiserNRois();
	plateau.creer(CONFIGURATION_PLATEAU_VALIDE);

	plateau.reinitialiserPositionsValidesPieces();

	plateau.effectuerChangementPosition(plateau.getCase(POSITION_INITIAL_TOUR_BLANCHE_X, POSITION_INITIAL_TOUR_BLANCHE_Y),
		plateau.getCase(POSITION_ECHEC_TOUR_BLANCHE_X, POSITION_ECHEC_TOUR_BLANCHE_Y));

	plateau.reinitialiserPositionsValidesPieces();

	plateau.effectuerChangementPosition(plateau.getCase(POSITION_ROI_NOIRE_X_INITIAL, POSITION_ROI_NOIRE_Y_INITIAL),
		plateau.getCase(POSITION_ROI_NOIR_DEPLACEMENT_X, POSITION_ROI_NOIR_DEPLACEMENT_Y));

	plateau.reinitialiserPositionsValidesPieces();

	EXPECT_EQ(plateau.getCase(POSITION_ECHEC_TOUR_BLANCHE_X, POSITION_ECHEC_TOUR_BLANCHE_Y)->getPieceOccupante()->getMouvementsPossibles().size(), NOMBRE_MOUVEMENTS_POSSIBLES);
}

#endif
