/**
* Projet final :: INF1015 :: Livrable 3. Interface de l'échiquier.
* \file   EchiquierIU.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/


#include "IU.h"

/**
*  Permet d'inverser l'état du bouton-poussoir. Sélectionner la pièce <--> placer la pièce.
*/
void vue::EchiquierWindow::inverserEtatBouton()
{
	switch (etatBouton_) {
		case EtatBouton::selectionner:
			etatBouton_ = EtatBouton::placer;
			break;
		case EtatBouton::placer:
			etatBouton_ = EtatBouton::selectionner;
			break;
		}
}


/**
*  Permet de récolter l'état du bouton lors de la sélection de pièce.
*  \return	[EtatBouton]	<L'état du bouton.>
*/
vue::EtatBouton vue::EchiquierWindow::getEtatBouton() const
{
	return etatBouton_;
}


/**
*  Permet de récolter le pointeur vers le tour courant (le texte en haut de l'échiquier).
*  \return	[QLabel*]	<Un pointeur vers le libellé du haut indiquant le tour à jouer.>
*/
QLabel* vue::EchiquierWindow::getTourCourant() const
{
	return tourCourant_;
}


/**
*  Permet de sauvegarder la position du click de souris lors de la sélection d'une pièce.
*  \return	[pair<int, int>]	<La position du click sauvegardée.>
*/
std::pair<int, int> vue::EchiquierWindow::getPositionClickTampon() const
{
	return positionClickTampon_;
}


/**
*  Permet de définir la position une position tampon du click de souris lors de la sélection.
*  \param	[const pair<int, int>&]		nouveauTampon	<La position du click de souris comme nouveau tampon.>
*/
void vue::EchiquierWindow::setPositionClickTampon(const std::pair<int, int>& nouveauTampon)
{
	positionClickTampon_ = nouveauTampon;
}


/**
*  Permet de récolter un pointeur vers un bouton tampon.
*  \return	[PiecesBouton*]		<Un pointeur vers un bouton tampon.>
*/
vue::PiecesBouton* vue::EchiquierWindow::getBoutonTampon() const
{
	return boutonTampon_;
}


/**
*  Permet de définir un bouton tampon.
*  \param	[PiecesBouton*]		boutonTampon	<Le nouveau bouton tampon.>
*/
void vue::EchiquierWindow::setBoutonTampon(PiecesBouton* boutonTampon)
{
	boutonTampon_ = boutonTampon;
}


/**
*  Permet de récolter le plateau d'échec.
*  \return	[Plateau*]		<Un pointeur vers le plateau d'échecs.>
*/
modele::Plateau* vue::EchiquierWindow::getPlateau() const
{
	return plateauGraphique_.get();
}


/**
*  Permet d'afficher à l'écran un message d'erreur comme quoi le mouvement n'est pas accepté.
*/
void vue::EchiquierWindow::erreurMessage() {
	QMessageBox::critical(this, TITRE_ERREUR, MESSAGE_ERREUR);
}


/**
*  Permet d'afficher à l'écran un message comme quoi un roi est en échec.
*/
void vue::EchiquierWindow::Echec() {
	if (getPlateau()->getTour() == modele::Couleur::Blanc)
		QMessageBox::warning(this, TITRE_ECHEC, "Le roi " + TOUR_BLANC + " est en échec");
	else
		QMessageBox::warning(this, TITRE_ECHEC, "Le roi " + TOUR_NOIR + " est en échec");
}


/**
*  Permet de quitter le programme.
*/
void vue::EchiquierWindow::terminerProgramme() const
{
	app_->quit();
}


/**
*  Permet de réinitialiser le plateau.
*  \param	[const string&]		configuration		<La nouvelle configuration à réinitialiser.>
*/
void vue::EchiquierWindow::reinitialiserProgramme()
{
	using namespace iter;

	plateauGraphique_->reinitialiserNRois();
	
	
	if (layoutPrincipalEchiquier_ != nullptr) {
		QLayoutItem* item;
		while ((item = layoutPrincipalEchiquier_->takeAt(0)) != nullptr) {
			delete item->widget();
			delete item;
		}
	}

	//? Récupérer l'index courant du combo box pour avoir la position désirée à la réinitialisation
	const int indexCombo = comboPositionsInitiales_->currentIndex();

	switch (indexCombo) {
		case POSITION_UN:
			plateauGraphique_->creer(POSITION_BOURDONNAIS_MCDONNELL_1834);
			break;
		case POSITION_DEUX:
			plateauGraphique_->creer(POSITION_POLGAR_KASPAROV_1996);
			break;
		case POSITION_TROIS:
			plateauGraphique_->creer(POSITION_ALEKHINE_CAPABLANCA_1927);
			break;
		case POSITION_QUATRE:
			plateauGraphique_->creer(POSITION_KARPOV_FTACNIK_1988);
			break;
	}
	
	ajouterCasesEchiquier(layoutPrincipalEchiquier_);
	plateauGraphique_->setTour(modele::Couleur::Blanc);
	initialiserLibelle(modele::Couleur::Blanc);
}


/**
*  Permet d'ajouter une image à une pièce (un bouton).
*  \param	[PiecesBouton*]		bouton		<Le bouton dont l'image est à modifier (out).>
*  \param	[const char]		caractere	<Le caractère indiquant le chemin de l'image.>
*/
void vue::EchiquierWindow::ajouterImage(PiecesBouton* bouton, const char caractere) const
{
	using namespace std;

	map<const char, const QString> cheminsImages {
		{ CARACTERE_ROI_NOIR,		CHEMIN_ROI_NOIR },
		{ CARACTERE_ROI_BLANC,		CHEMIN_ROI_BLANC },
		{ CARACTERE_TOUR_NOIRE,		CHEMIN_TOUR_NOIRE },
		{ CARACTERE_TOUR_BLANCHE,	CHEMIN_TOUR_BLANCHE },
		{ CARACTERE_CAVALIER_NOIR,	CHEMIN_CAVALIER_NOIR },
		{ CARACTERE_CAVALIER_BLANC, CHEMIN_CAVALIER_BLANC }
	};

	QPixmap pixmap(cheminsImages[caractere]);
	QIcon BoutonPiece(pixmap);

	bouton->setIcon(BoutonPiece);
	bouton->setIconSize(QSize(TAILLE_ICONE, TAILLE_ICONE));
}


/**
*  Permet d'ajouter un nouveau bouton sur l'échiquier Qt.
*  \param	[const string&]		Couleur		<La couleur du bouton.>
*  \param	[int]				positionY	<La position Y du bouton sur l'échiquier.>
*  \param	[int]				positionX	<La position X du bouton sur l'échiquier.>
*  \return	[QPushButton*]					<Le nouveau bouton créé.>
*/
QPushButton* vue::EchiquierWindow::nouveauBouton(modele::Couleur couleur, int positionY, int positionX)
{
	PiecesBouton* bouton = new PiecesBouton(positionY, positionX, couleur, this);

	if (plateauGraphique_->getCase(positionY, positionX)->getOccupation())
		switch (plateauGraphique_->getCase(positionY, positionX)->getPieceOccupante()->getCaractere()) {
			case CARACTERE_ROI_NOIR:
				ajouterImage(bouton, CARACTERE_ROI_NOIR);
				break;

			case CARACTERE_ROI_BLANC:
				ajouterImage(bouton, CARACTERE_ROI_BLANC);
				break;

			case CARACTERE_TOUR_NOIRE:
				ajouterImage(bouton, CARACTERE_TOUR_NOIRE);
				break;

			case CARACTERE_TOUR_BLANCHE:
				ajouterImage(bouton, CARACTERE_TOUR_BLANCHE);
				break;

			case CARACTERE_CAVALIER_NOIR:
				ajouterImage(bouton, CARACTERE_CAVALIER_NOIR);
				break;

			case CARACTERE_CAVALIER_BLANC:
				ajouterImage(bouton, CARACTERE_CAVALIER_BLANC);
				break;
		}
	
	return bouton;
}


/**
*  Permet d'ajouter un pointeur vers l'application pour éviter les fuites de mémoire.
*  \param	[QApplication*]		app		<Le pointeur vers l'application.>
*/
void vue::EchiquierWindow::addApp(QApplication* app) 
{
	app_ = app;
}


/**
*  Permet d'initialiser le libellé en haut pour savoir le tour du joueur.
*  \param	[const Couleur&]	couleur		<La couleur du libellé.>
*/
void vue::EchiquierWindow::initialiserLibelle(const modele::Couleur& couleur) const
{
	switch (couleur) {
		case modele::Couleur::Blanc:
			getTourCourant()->setText(TEXTE_LIBELLE_BLANC);
			getTourCourant()->setStyleSheet(COULEUR_LIBELLE_BLANC);
			break;

		case modele::Couleur::Noir:
			getTourCourant()->setText(TEXTE_LIBELLE_NOIR);
			getTourCourant()->setStyleSheet(COULEUR_LIBELLE_NOIR);
			break;
		}
}


/**
*  Permet d'ajouter les cases à l'échiquier visuel.
*/
void vue::EchiquierWindow::ajouterCasesEchiquier(QGridLayout* layout)
{
	using namespace iter;
	for (int i : range(modele::DIMENSION_PLATEAU_Y))
		for (int j : range(modele::DIMENSION_PLATEAU_X)) {
			if ((i + j) % EST_PAIR)
				layout->addWidget(nouveauBouton(modele::Couleur::Blanc, j, i), i, j);
			else
				layout->addWidget(nouveauBouton(modele::Couleur::Noir, j, i), i, j);
		}
}


/**
*  Permet d'initialiser un layout avec les marges et l'espacement (padding) correspondants.
*  \param	[T*]			layout					<Le layout pour lequel nous souhaitons initialiser ses marges et son espacement.>
*  \param	[const int]		margeGauche				<La valeur d'espacement (margin) pour la marge de gauche.>
*  \param	[const int]		margeHaut				<La valeur d'espacement (margin) pour la marge du haut.>
*  \param	[const int]		margeDroite				<La valeur d'espacement (margin) pour la marge de droite.>
*  \param	[const int]		margeBas				<La valeur d'espacement (margin) pour la marge du bas.>
*  \param	[const int]		espacementGlobal		<La valeur d'espacement (padding) général.>
*/
template <typename T>
void vue::EchiquierWindow::initialiserEspacementsObjets(T* layout, const int margeGauche, const int margeHaut, const int margeDroite, const int margeBas, const int espacementGlobal) const
{
	//? Limitons l'accès à cette fonction
	Expects(dynamic_cast<QGridLayout*>(layout) != nullptr || 
			dynamic_cast<QVBoxLayout*>(layout) != nullptr ||
			dynamic_cast<QHBoxLayout*>(layout) != nullptr);

	layout->setContentsMargins(margeGauche, margeHaut, margeDroite, margeBas);
	layout->setSpacing(espacementGlobal);
}


/**
*  Permet d'initialiser un objet avec son texte, son style et ses dimensions.
*  \param	[T*]					objet						<L'objet pour lequel nous souhaitons initialiser son texte, son style et ses dimensions.>
*  \param	[const QString&]		texteLibelle				<Le texte de l'objet.>
*  \param	[const QString&]		style						<Le style de l'objet.>
*  \param	[const int]				dimensionHorizontaleMin		<La dimension horizontale minimale de l'objet.>
*  \param	[const int]				dimensionVerticaleMin		<La dimension verticale minimale de l'objet.>
*/
template <typename T>
void vue::EchiquierWindow::initialiserObjet(T* objet, const QString& style, const int dimensionHorizontaleMin, const int dimensionVerticaleMin) const
{
	//? Limitons l'accès à cette fonction
	Expects(dynamic_cast<QComboBox*>(objet)		!= nullptr ||
			dynamic_cast<QPushButton*>(objet)	!= nullptr);

	objet->setStyleSheet(style);
	objet->setMinimumWidth(dimensionHorizontaleMin);
	objet->setMinimumHeight(dimensionVerticaleMin);
}


/**
*  Permet de construire l'échiquier Window.
*  \param	[QWidget*]		parent		<Le parent auquel l'échiquier Window est connecté.>
*/
vue::EchiquierWindow::EchiquierWindow(QWidget* parent)
{
	using namespace iter;
	using namespace std;

	QWidget*		widgetPrincipal				= new QWidget(this);
	QWidget*		echiquier					= new QWidget;
	QGridLayout*	layoutPrincipalEchiquier	= new QGridLayout(echiquier);
	QVBoxLayout*	alignementVertical			= new QVBoxLayout;
	QLabel*			indiquerTourPartie			= new QLabel;
	QHBoxLayout*	echiquierEtBoutons			= new QHBoxLayout;
	QVBoxLayout*	panneauxBouton				= new QVBoxLayout;
	QComboBox*		comboPositionsInitiales		= new QComboBox;
	QPushButton*	reinitialiser				= new QPushButton;
	QPushButton*	terminerPartie				= new QPushButton;

	layoutPrincipalEchiquier_ = layoutPrincipalEchiquier;

	/* TD 6 -- EXCEPTION */
	try {
		plateauGraphique_->creer(CHAMP_ERRONE);
	}

	catch (modele::NombreRoisExact& exception) {
		//? Nous attrapons l'exception et l'envoyons via la console, en plus de réinitialiser le plateau graphique avec une combinaison valide
		cout << TEXTE_EXCEPTION_N_ROIS << exception.what() << endl;
		plateauGraphique_->reinitialiserNRois();
		plateauGraphique_->creer(POSITION_BOURDONNAIS_MCDONNELL_1834);
	}

	ajouterCasesEchiquier(layoutPrincipalEchiquier);

	setWindowTitle(NOM_FENETRE);
	setWindowIcon(QIcon(CHEMIN_ICONE_FENETRE));
	initialiserEspacementsObjets(layoutPrincipalEchiquier, 0, 0, 0, 0, 0);
	
	initialiserEspacementsObjets(alignementVertical, 0, 0, 0, 0, 0);
	
	indiquerTourPartie->setContentsMargins(MARGES_TOUR_PARTIE, MARGES_TOUR_PARTIE, MARGES_TOUR_PARTIE, MARGES_TOUR_PARTIE);

	tourCourant_ = indiquerTourPartie;
	initialiserLibelle(modele::Couleur::Blanc);
	
	alignementVertical->addWidget(indiquerTourPartie);

	initialiserObjet(comboPositionsInitiales, STYLE_COMBO_POSITIONS_INIT, DIMENSION_H_COMBO_POSIITIONS_INIT, DIMENSION_V_COMBO_POSIITIONS_INIT);

	comboPositionsInitiales->addItems(POSITIONS_INITIALES_POSSIBLES);
	comboPositionsInitiales_ = comboPositionsInitiales;

	initialiserObjet(reinitialiser, STYLE_REINITIALISER, DIMENSION_H_REINITIALISER, DIMENSION_V_REINITIALISER);
	reinitialiser->setText(TEXTE_REINITIALISER);

	connect(reinitialiser, SIGNAL(clicked()), this, SLOT(reinitialiserProgramme()));

	initialiserObjet(terminerPartie, STYLE_TERMINER, DIMENSION_H_TERMINER, DIMENSION_V_TERMINER);
	terminerPartie->setText(TEXTE_TERMINER);

	connect(terminerPartie, SIGNAL(clicked()), this, SLOT(terminerProgramme()));

	panneauxBouton->addWidget(comboPositionsInitiales);
	panneauxBouton->addWidget(reinitialiser);
	panneauxBouton->addWidget(terminerPartie);

	echiquierEtBoutons->addWidget(echiquier);
	echiquierEtBoutons->addLayout(panneauxBouton);
	initialiserEspacementsObjets(echiquierEtBoutons, 0, 0, 0, 0, ESPACEMENT_ECHIQUIER_ET_BOUTONS);

	for (int espacement : VALEURS_ESPACEMENT)
		echiquierEtBoutons->insertStretch(espacement);
	
	alignementVertical->addLayout(echiquierEtBoutons);
	widgetPrincipal->setLayout(alignementVertical);

	setCentralWidget(widgetPrincipal);
}
