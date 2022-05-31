/**
* Projet final :: INF1015 :: Livrable 3. Boutons de l'interface (cases de l'�chiquier).
* \file   BoutonsIU.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "IU.h"


/**
*  Permet de visualiser les cases du jeu d'�chec sur Qt, chaque case pouvant poss�der une pi�ce.
*  \param	[const int]				positionX		<La position en X du bouton sur l'�chiquier.>
*  \param	[const int]				positionY		<La position en Y du bouton sur l'�chiquier.>
*  \param	[const Couleur&]		couleur			<La couleur du bouton.>
*  \param	[EchiquierWindow*]		echiquier		<Un pointeur vers l'�chiquier.>
*/
vue::PiecesBouton::PiecesBouton(const int positionX, const int positionY, const modele::Couleur& couleur, EchiquierWindow* echiquier) :
	positionX_(positionX), positionY_(positionY), couleur_(couleur), echiquier_(echiquier)
{
	static constexpr int		POSITION_LETTRE = 1, POSITION_CHIFFRE = 0;
	static const std::string	NOM_CASE_A1_INVERSE = "1A";

	if (positionX == 0 && positionY == modele::DIMENSION_PLATEAU_Y - 1)
		setText(QString::fromStdString(NOM_CASE_A1_INVERSE));

	else if (positionX == 0)
		setText(QString::fromStdString(std::string{ echiquier->getPlateau()->getCase(positionX, positionY)->getNomCase()[POSITION_LETTRE] }));
		
	else if (positionY == modele::DIMENSION_PLATEAU_Y - 1)
		setText(QString::fromStdString(std::string{ echiquier->getPlateau()->getCase(positionX, positionY)->getNomCase()[POSITION_CHIFFRE] }));

	setStyleSheet(NOM_CASES);

	palette_ = palette();
	initialiserBouton();
	initialiserPalette(couleur_);
}


/**
*  Permet d'enlever une pi�ce suite au d�placement.
*/
void vue::PiecesBouton::enleverPiece()
{
	setIcon(QIcon());
	setIconSize(QSize(TAILLE_ICONE, TAILLE_ICONE));
}


/**
*  Permet de rajouter une pi�ce imag�e sur le jeu d'�chec.
*  \param	[const QString&]		chemin		<Le chemin o� se trouve l'image de la pi�ce.>
*/
void vue::PiecesBouton::rajouterPiece(const QString& chemin)
{
	QPixmap pixmap(chemin);
	QIcon BoutonPiece(pixmap);
	setIcon(BoutonPiece);
	setIconSize(QSize(TAILLE_ICONE, TAILLE_ICONE));
}


/**
*  Permet d'initialiser les propri�t�s par d�faut des boutons.
*/
void vue::PiecesBouton::initialiserBouton()
{
	setFixedSize(dimension_, dimension_);
	setFlat(true);
	update();
}


/**
*  Initialise la palette des boutons selon leur couleur.
*  \param	[const Couleur&]	couleur		<La couleur du bouton.>
*/
void vue::PiecesBouton::initialiserPalette(const modele::Couleur& couleur)
{
	if (couleur == modele::Couleur::Noir)
		palette_.setColor(QPalette::Button, PALETTE_NOIRE);
	else
		palette_.setColor(QPalette::Button, PALETTE_BLANCHE);

	setAutoFillBackground(true);
	setPalette(palette_);
}


/**
*  R�cup�re la couleur d'un bouton.
*  \return	[Couleur]	couleur		<La couleur du bouton.>
*/
modele::Couleur vue::PiecesBouton::getCouleur() const
{
	return couleur_;
}


/**
*  Inverser la couleur du libell� en haut de l'�chiquier.
*  \param	[Couleur]	couleur		<La couleur de la pi�ce.>
*/
void vue::PiecesBouton::setCouleurLibelle(const modele::Couleur& couleur) const
{
	switch (couleur) {
		case modele::Couleur::Noir:
			echiquier_->getTourCourant()->setText(TEXTE_LIBELLE_BLANC);
			echiquier_->getTourCourant()->setStyleSheet(COULEUR_LIBELLE_BLANC);
			break;

		case modele::Couleur::Blanc:
			echiquier_->getTourCourant()->setText(TEXTE_LIBELLE_NOIR);
			echiquier_->getTourCourant()->setStyleSheet(COULEUR_LIBELLE_NOIR);
			break;
	}
}


/**
*  Effectuer des changements au plateau lorsqu'un joueur clique sur le plateau de jeu.
*  \param	[QMouseEvent*]		event	<L'�v�nement d�clench� par le click de souris.>
*/
void vue::PiecesBouton::mousePressEvent(QMouseEvent* event)
{
	using namespace std;

	//? R�cup�rer si l'utilisateur est en train de s�lectionner ou de poser la pi�ce
	if (echiquier_->getEtatBouton() == EtatBouton::selectionner) {
		if (echiquier_->getPlateau()->getCase(positionX_, positionY_)->getOccupation() &&
			echiquier_->getPlateau()->getTour() == echiquier_->getPlateau()->getCase(positionX_, positionY_)->getPieceOccupante()->getCouleur()) { //? Si la case est occup�e 

			switch (couleur_) {
				//? Style de la case lorsqu'elle est s�lectionn�e
				case modele::Couleur::Blanc:
					setStyleSheet(PALETTE_BLANCHE_SELECTION);
					break;

				case modele::Couleur::Noir:
					setStyleSheet(PALETTE_NOIRE_SELECTION);
					break;
			}

			echiquier_->setPositionClickTampon({ positionX_, positionY_ });
			echiquier_->setBoutonTampon(this);
			echiquier_->getPlateau()->getCase(positionX_, positionY_)->getPieceOccupante()->effacerMouvements();
			echiquier_->getPlateau()->getCase(positionX_, positionY_)->getPieceOccupante()->calculerMouvementsPossibles({ positionX_, positionY_ }, echiquier_->getPlateau());
			echiquier_->inverserEtatBouton();

			if (echiquier_->getPlateau()->getEtatEchec() == true && !changementPosition)
				echiquier_->getPlateau()->inverserEchec();

			changementPosition = true;
		}
	}

	else
	{
		pair<int, int> caseInitiale = { echiquier_->getPositionClickTampon().first, echiquier_->getPositionClickTampon().second };
		pair<int, int> mouvementDesire = { positionX_, positionY_ };

		switch (echiquier_->getBoutonTampon()->getCouleur()) {
			//? Au deuxi�me click, nous remettons le style des cases par d�faut
			case modele::Couleur::Blanc:
				echiquier_->getBoutonTampon()->setStyleSheet(BOUTON_TAMPON_BLANC_STYLE);
				break;
			case modele::Couleur::Noir:
				echiquier_->getBoutonTampon()->setStyleSheet(BOUTON_TAMPON_NOIR_STYLE);
				break;
		}

		bool mouvementAccepte = false;

		for (const pair<int, int>& mouvementPossible : echiquier_->getPlateau()->getCase(caseInitiale.first, caseInitiale.second)->getPieceOccupante()->getMouvementsPossibles()) {
			if (mouvementDesire == mouvementPossible) {
				setCouleurLibelle(echiquier_->getPlateau()->getCase(caseInitiale.first, caseInitiale.second)->getPieceOccupante()->getCouleur());

				echiquier_->getPlateau()->effectuerChangementPosition(echiquier_->getPlateau()->getCase(caseInitiale.first, caseInitiale.second),
					echiquier_->getPlateau()->getCase(mouvementDesire.first, mouvementDesire.second));

				switch (echiquier_->getPlateau()->getCase(mouvementDesire.first, mouvementDesire.second)->getPieceOccupante()->getCaractere()) {
				case CARACTERE_ROI_NOIR:
					rajouterPiece(CHEMIN_ROI_NOIR);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;

				case CARACTERE_ROI_BLANC:
					rajouterPiece(CHEMIN_ROI_BLANC);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;

				case CARACTERE_TOUR_NOIRE:
					rajouterPiece(CHEMIN_TOUR_NOIRE);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;

				case CARACTERE_TOUR_BLANCHE:
					rajouterPiece(CHEMIN_TOUR_BLANCHE);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;

				case CARACTERE_CAVALIER_NOIR:
					rajouterPiece(CHEMIN_CAVALIER_NOIR);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;

				case CARACTERE_CAVALIER_BLANC:
					rajouterPiece(CHEMIN_CAVALIER_BLANC);
					echiquier_->getBoutonTampon()->enleverPiece();
					break;
				}

				echiquier_->inverserEtatBouton();
				mouvementAccepte = true;

				if (echiquier_->getPlateau()->getEtatEchec() == true) {
					emit echiquier_->Echec();
				}

				break;
			}
		}

		if (!mouvementAccepte) {
			changementPosition = false;
			echiquier_->inverserEtatBouton();
			emit echiquier_->erreurMessage();
		}
	}
}
