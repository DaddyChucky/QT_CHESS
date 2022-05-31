/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui d�finit les fonctions pour le plateau de jeu.
* \file   Plateau.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "Modele.h"


/**
*  Le plateau (�chiquier).
*  \param	[const Couleur&]	tourInitial		<Le tour initial des joueurs.>
*/
modele::Plateau::Plateau(const Couleur& tourInitial) :
	tour_(tourInitial)
{}


/**
*  Cr�ation d'une case pour le plateau.
*  \param	[const string&]		nom			<Le nom de la case.>
*  \param	[bool]				estOccupee	<Indique si la case est occup�e par une pi�ce.>
*  \return	[unique_ptr<Case>]				<Le pointeur unique vers la case cr��e.>
*/
std::unique_ptr<modele::Case> modele::Plateau::creerCase(const std::string& nom, bool estOccupee) const
{
	return make_unique<Case>(nom, estOccupee);
}


/**
*  Cr�ation d'une pi�ce pour le plateau.
*  \param	[char]		caractere			<Le nom de la pi�ce � cr�er selon le caract�re �mis.>
*  \return	[unique_ptr<Piece>]				<Le pointeur unique vers la pi�ce cr��e.>
*/
std::unique_ptr<modele::Piece> modele::Plateau::creerPiece(char caractere) const
{
	using namespace std;

	if (caractere == CARACTERE_CAVALIER_NOIR)
		return make_unique<Cavalier>(Couleur::Noir);

	else if (caractere == CARACTERE_CAVALIER_BLANC)
		return make_unique<Cavalier>(Couleur::Blanc);

	else if (caractere == CARACTERE_TOUR_NOIRE)
		return make_unique<Tour>(Couleur::Noir);

	else if (caractere == CARACTERE_TOUR_BLANCHE)
		return make_unique<Tour>(Couleur::Blanc);

	else if (caractere == CARACTERE_ROI_NOIR) {
		++nRois_;
		return make_unique<Roi>(Couleur::Noir);
	}

	else {
		++nRois_;
		return make_unique<Roi>(Couleur::Blanc);
	}
}


/**
*  R�initialise le compte du nombre de rois sur l'�chiquier.
*/
void modele::Plateau::reinitialiserNRois()
{
	nRois_ = 0;
}


/**
*  Cr�e le plateau en appelant plusieurs fonctions d�finies plus haut.
*  \param	[const string&]		configuration	<Le jeu d'�checs que l'on souhaite obtenir sous forme d'une cha�ne de caract�res.>
*  \return	[bool]								<Indique si le plateau a �t� cr�� avec succ�s.>
*/
void modele::Plateau::creer(const std::string& configuration)
{
	using namespace iter;

	int x = 0, y = 0;

	for (size_t i : range(configuration.length())) {
		if (nRois_ > LIMITE_CONFRONTATIONS_ROIS)
			throw NombreRoisExact(ERREUR_TROP_DE_ROIS);

		if (configuration[i] == CARACTERE_ESPACE) {
			if (configuration[i + 1] == DEBUTER_NOIR)
				inverserTour();
			break;
		}

		else if (configuration[i] != CARACTERE_SEPARATION) {
			//? Mis � jour des positions
			if (configuration[i] == CARACTERE_LIGNE_VIDE) //? Si la configuration lue correspond au chiffre 8
				for ([[maybe_unused]] int k : range(DIMENSION_PLATEAU_X)) {
					plateau_[x][y] = move(creerCase(nomCases_[DIMENSION_PLATEAU_X * y + x], false));
					++x;
				}

			//? V�rification qu'une pi�ce doit �tre instanci�e
			else if (configuration[i] == CARACTERE_PIECE_VIDE) {
				plateau_[x][y] = move(creerCase(nomCases_[DIMENSION_PLATEAU_X * y + x], false));
				++x;
			}

			else {
				plateau_[x][y] = move(creerCase(nomCases_[DIMENSION_PLATEAU_X * y + x], true));
				plateau_[x][y]->setPieceOccupante(move(creerPiece(configuration[i])));
				++x;
			}

			if ((x + 1) % (DIMENSION_PLATEAU_X + 1) == 0) { //? + 1 pour �viter le modulo 0 (donnant toujours 0) -> (x+1) mod 9
				x = 0;
				++y;
			}
		}
	}

	if (nRois_ < LIMITE_CONFRONTATIONS_ROIS)
		throw NombreRoisExact("Le nombre de rois est inf�rieur au seuil autoris�.");
}


/**
*  Trouve une case (et sa position (x, y)) � partir du nom de la pi�ce.
*  \param	[const char]					nomPiece			<Le d�placement que l'on souhaite effectuer.>
*  \param	[const string&]					adverseSeulement	<Ne regarde que les cases adverses.>
*  \return	[pair<Case*, pair<int, int>>]						<Un pointeur vers la case trouv�e (si applicable), avec sa position (y, x) sur le plateau.>
*/
std::pair<modele::Case*, std::pair<int, int>> modele::Plateau::trouverCase(const char nomPiece, bool adverseSeulement) const
{
	using namespace iter;

	for (int y : range(DIMENSION_PLATEAU_Y))
		for (int x : range(DIMENSION_PLATEAU_X))
			if (plateau_[y][x]->getOccupation() && plateau_[y][x]->getPieceOccupante()->getNom() == static_cast<char>(tolower(nomPiece)))
				if (adverseSeulement && plateau_[y][x]->getPieceOccupante()->getCouleur() != tour_) //? Ne prendre que les cases adverses
					return { plateau_[y][x].get(), { y, x } };

	return { nullptr, { 0,0 } };
}


/**
*  Trouve une case � partir d'une position sur le plateau.
*  \param	[const pair<int, int>&]			position		<La position � rechercher.>
*  \return	[Case*]											<Un pointeur vers la case trouv�e (si applicable).>
*/
modele::Case* modele::Plateau::trouverCase(const std::pair<int, int>& position) const
{
	return plateau_[position.first][position.second].get();
}


/**
*  Calcule les mouvements pour une pi�ce en particulier sur le plateau.
*  \param	[Piece*]						piece				<La pi�ce � r�initialiser ses mouvements.>
*  \param	[const pair<int, int>&]			positionInitiale	<La position initiale de la pi�ce.>
*/
void modele::Plateau::calculerMouvementsPossibles(Piece* piece, const std::pair<int, int>& positionInitiale)
{
	piece->effacerMouvements(); //? Nous r�initialisons les mouvements de toutes les pi�ces
	piece->calculerMouvementsPossibles(positionInitiale, this);
}


/**
*  Parcours des pi�ces et r�initialisation de leurs positions valides.
*/
void modele::Plateau::reinitialiserPositionsValidesPieces()
{
	using namespace iter;

	for (int y : range(DIMENSION_PLATEAU_Y))
		for (int x : range(DIMENSION_PLATEAU_X))
			if (plateau_[y][x]->getOccupation()) //? Regarder seulement les cases occup�es par les pi�ces
				if (plateau_[y][x]->getPieceOccupante()->getCouleur() == tour_) //? Prendre seulement les pi�ces qui correspondent au tour du joueur
					calculerMouvementsPossibles(plateau_[y][x]->getPieceOccupante(), { y, x });
}


/**
*  Inverse le tour des joueurs.
*/
void modele::Plateau::inverserTour()
{
	if (tour_ == Couleur::Blanc)
		tour_ = Couleur::Noir;
	else
		tour_ = Couleur::Blanc;
}


/**
*  Permet d'initialiser le tour des joueurs.
*  \param	[const Couleur&]	couleur		<La couleur initiale qui peut jouer.>
*/
void modele::Plateau::setTour(const modele::Couleur& couleur)
{
	tour_ = couleur;
}


/**
*  Retourne le tour de la partie courante.
*  \return	[Couleur]	<La couleur du tour.>
*/
modele::Couleur modele::Plateau::getTour() const
{
	return tour_;
}


/**
*  Permet de retourner la position d'une case.
*  \param	[Case*]				caseATrouver		<La case pour laquelle nous devons trouver sa position.>
*  \return	[pair<int, int>]						<La position de la case (x, y).>
*/
std::pair<int, int> modele::Plateau::getPositionCase(Case* caseATrouver) const
{
	using namespace iter;

	for (int y : range(DIMENSION_PLATEAU_Y))
		for (int x : range(DIMENSION_PLATEAU_X))
			if (plateau_[y][x].get() == caseATrouver)
				return { y,x };

	return { 0, 0 };
}


/**
*  Permet de savoir si nous sommes en �chec apr�s le d�placement d'une pi�ce.
*  \param	[Case*]		caseFinale		<La case finale du d�placement.>
*  \return	[bool]						<Vrai si une pi�ce met en �chec le roi auquel est associ� la couleur du tour.>
*/
bool modele::Plateau::testEchecApresDeplacement(Case* caseFinale)
{
	using namespace std;

	caseFinale->getPieceOccupante()->effacerMouvements();
	caseFinale->getPieceOccupante()->calculerMouvementsPossiblesSimples(getPositionCase(caseFinale), this);

	const vector<pair<int, int>> MOUVEMENTS_POSSIBLES = caseFinale->getPieceOccupante()->getMouvementsPossibles();

	for (auto mouvement : MOUVEMENTS_POSSIBLES)
		if (trouverCase(mouvement)->getOccupation() && trouverCase(mouvement)->getPieceOccupante()->getNom() == CARACTERE_ROI_NOIR && trouverCase(mouvement)->getPieceOccupante()->getCouleur() != tour_)
			return true;

	return false;
}


/**
*  Teste si la case poss�de une pi�ce adverse qui met en �chec le roi.
*  \param	[Case*]		caseFinale		<La case finale du d�placement.>
*  \return	[bool]						<Vrai si une pi�ce met en �chec le roi auquel est associ� la couleur du tour.>
*/
bool modele::Plateau::testEchecApresDeplacementAdversaire(Case* caseFinale)
{
	using namespace std;

	inverserTour();
	caseFinale->getPieceOccupante()->effacerMouvements();
	caseFinale->getPieceOccupante()->calculerMouvementsPossiblesSimples(getPositionCase(caseFinale), this);

	const vector<pair<int, int>> MOUVEMENTS_POSSIBLES = caseFinale->getPieceOccupante()->getMouvementsPossibles();

	for (auto mouvement : MOUVEMENTS_POSSIBLES)
		if (trouverCase(mouvement)->getOccupation() && trouverCase(mouvement)->getPieceOccupante()->getNom() == CARACTERE_ROI_NOIR && trouverCase(mouvement)->getPieceOccupante()->getCouleur() != tour_) {
			inverserTour();
			return true;
		}

	inverserTour();

	return false;
}


/**
*  Permet d'inverser l'�chec.
*/
void modele::Plateau::inverserEchec()
{
	if (echec_ == true)
		echec_ = false;

	else
		echec_ = true;
}


/**
*  Retourne si le plateau est en �tat d'�chec.
*  \return	[bool]	<Vrai si le plateau est en �chec.>
*/
bool modele::Plateau::getEtatEchec() const
{
	return echec_;
}


/**
*  Effectue le changement de position d'une pi�ce.
*  \param	[Case*]		caseInitiale			<La case initiale pour laquelle se trouve la pi�ce.>
*  \param	[Case*]		caseFinale				<La case finale occup�e par la pi�ce.>
*/
void modele::Plateau::effectuerChangementPosition(Case* caseInitiale, Case* caseFinale)
{
	//? Si occupation ennemie � la case finale, on enl�ve la pi�ce du jeu
	if (caseFinale->getOccupation())
		caseFinale->detruirePieceOccupante();

	else
		caseFinale->inverserOccupation();

	//? On d�place la pi�ce � la nouvelle case
	caseFinale->setPieceOccupante(move(caseInitiale->changerPossessionPiece()));

	//? Nous enlevons la pi�ce de la case initiale
	caseInitiale->detruirePieceOccupante();
	caseInitiale->inverserOccupation();
	caseFinale->getPieceOccupante()->setCouleur(tour_);

	if (testEchecApresDeplacement(caseFinale))
		echec_ = true;

	else
		echec_ = false;

	inverserTour();
}


/**
*  Retourne un pointeur vers une case du plateau � partir d'une position (x, y).
*  \param	[const int]			x		<La position en x du plateau.>
*  \param	[const int]			y		<La position en y du plateau.>
*  \return	[Case*]						<Un pointeur vers la case trouv�e.>
*/
modele::Case* modele::Plateau::getCase(const int x, const int y) const
{
	return plateau_[x][y].get();
}


/**
*  Teste si l'�chec peut �tre prot�g� et d�vi� par le mouvement d'une pi�ce.
*  \param	[const pair<int, int>&]		positionInitiale		<La position initiale de la pi�ce.>
*  \param	[const pair<int, int>&]		mouvement				<Le mouvement de la pi�ce.>
*  \return	[bool]												<Vrai si le mouvement emp�che l'�chec.>
*/
bool modele::Plateau::testEchecProtection(const std::pair<int, int>& positionInitiale, const std::pair<int, int>& mouvement)
{
	using namespace iter;

	Case* caseSouhaitee = trouverCase(mouvement);
	Case* caseInitiale = trouverCase(positionInitiale);

	if (caseSouhaitee->getOccupation() && caseSouhaitee->getPieceOccupante()->getCouleur() != tour_)
		return true;

	else if (caseSouhaitee->getOccupation() && caseSouhaitee->getPieceOccupante()->getCouleur() == tour_)
		return false;

	caseSouhaitee->setPieceOccupante(caseInitiale->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();

	bool protection = true;

	inverserEchec();

	for (int y : range(DIMENSION_PLATEAU_Y)) {
		for (int x : range(DIMENSION_PLATEAU_X))
			if (plateau_[y][x]->getOccupation() && plateau_[y][x]->getPieceOccupante()->getCouleur() != tour_ && plateau_[y][x]->getPieceOccupante()->getNom() != CARACTERE_ROI_NOIR)
				if (testEchecApresDeplacementAdversaire(plateau_[y][x].get())) {
					protection = false;
					break;
				}

		if (!protection)
			break;
	}

	caseInitiale->setPieceOccupante(caseSouhaitee->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();
	inverserEchec();

	return protection;
}


/**
*  Teste si une pi�ce peut bouger sans causer l'�chec (le roi n'est pas � d�couvert suite au mouvement).
*  \param	[const pair<int, int>&]		positionInitiale		<La position initiale de la pi�ce.>
*  \param	[const pair<int, int>&]		mouvement				<Le mouvement de la pi�ce.>
*  \return	[bool]												<Vrai si le mouvement cause un �chec.>
*/
bool modele::Plateau::testEchecADecouvert(const std::pair<int, int>& positionInitiale, const std::pair<int, int>& mouvement)
{
	using namespace std;
	using namespace iter;

	Case* caseInitiale = trouverCase(positionInitiale);
	Case* caseSouhaitee = trouverCase(mouvement);
	bool				echecADecouvert = false;
	bool				pieceAttaquante = false;
	unique_ptr<Piece>	pieceAttaquanteTemp;

	if (caseSouhaitee->getOccupation()) {
		pieceAttaquanteTemp = caseSouhaitee->changerPossessionPiece();
		pieceAttaquante = true;
	}

	caseSouhaitee->setPieceOccupante(caseInitiale->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();

	for (int y : range(DIMENSION_PLATEAU_Y)) {
		for (int x : range(DIMENSION_PLATEAU_X)) {
			if (plateau_[y][x]->getOccupation() && plateau_[y][x]->getPieceOccupante()->getCouleur() != tour_ && plateau_[y][x]->getPieceOccupante()->getNom() != CARACTERE_ROI_NOIR) {
				if (testEchecApresDeplacementAdversaire(plateau_[y][x].get())) {
					echecADecouvert = true;
					break;
				}
			}
		}

		if (echecADecouvert)
			break;
	}

	caseInitiale->setPieceOccupante(caseSouhaitee->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();

	if (pieceAttaquante)
		caseSouhaitee->setPieceOccupante(move(pieceAttaquanteTemp));

	return echecADecouvert;
}


/**
*  Teste si une pi�ce cause un �chec au roi.
*  \param	[const pair<int, int>&]		positionInitiale		<La position initiale de la pi�ce.>
*  \param	[const pair<int, int>&]		mouvement				<Le mouvement de la pi�ce.>
*  \return	[bool]												<Vrai si le mouvement cause un �chec.>
*/
bool modele::Plateau::testEchecAuRoi(const std::pair<int, int>& positionInitiale, const std::pair<int, int>& mouvement)
{
	using namespace iter;

	Case* caseSouhaitee = trouverCase(mouvement);
	Case* caseInitiale = trouverCase(positionInitiale);

	if (caseSouhaitee->getOccupation() && caseSouhaitee->getPieceOccupante()->getCouleur() != tour_)
		return true;

	else if (caseSouhaitee->getOccupation() && caseSouhaitee->getPieceOccupante()->getCouleur() == tour_)
		return false;

	caseSouhaitee->setPieceOccupante(caseInitiale->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();

	bool protection = true;

	for (int y : range(DIMENSION_PLATEAU_Y))
		for (int x : range(DIMENSION_PLATEAU_X))
			if (plateau_[y][x]->getOccupation() && plateau_[y][x]->getPieceOccupante()->getCouleur() != tour_ && plateau_[y][x]->getPieceOccupante()->getNom() != CARACTERE_ROI_NOIR)
				if (testEchecApresDeplacementAdversaire(plateau_[y][x].get())) {
					protection = false;
					break;
				}

	caseInitiale->setPieceOccupante(caseSouhaitee->changerPossessionPiece());
	caseSouhaitee->inverserOccupation();
	caseInitiale->inverserOccupation();

	return protection;
}
