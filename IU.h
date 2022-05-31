/**
* Projet final :: INF1015 :: Livrable 3. Structures pour l'interface utilisateur.
* \file   IU.h
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/

#pragma once
#include "Modele.h"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QApplication>
#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsWidget>
#include <QGraphicsGridLayout>
#include <QPalette>
#include <QMessageBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <QGridLayout>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QComboBox>
#pragma pop()
#include <iostream>
#include <type_traits>
#include <cppitertools/range.hpp>


#define PALETTE_NOIRE_SELECTION		"border: 7px groove rgb(40, 26, 13); background-color: rgb(141, 96, 59); font-size: 12px;"
#define PALETTE_BLANCHE_SELECTION	"border: 7px groove rgb(40, 26, 13); background-color: rgb(200, 177, 141); font-size: 12px;"
#define	NOM_CASES					"font-size: 12px; vertical-align: center; text-align: center;"
#define BOUTON_TAMPON_BLANC_STYLE	"border: none; background-color: rgb(240, 217, 181); font-size: 12px;"
#define BOUTON_TAMPON_NOIR_STYLE	"border: none; background-color: rgb(181, 136, 99); font-size: 12px;"
#define COULEUR_LIBELLE_BLANC		"margin: 5%; font-weight: bold; font-size: 24px; qproperty-alignment: AlignCenter; background: white; color: black; border: none;"
#define COULEUR_LIBELLE_NOIR		"margin: 5%; font-weight: bold; font-size: 24px; qproperty-alignment: AlignCenter; background: black; color: white; border: none;"
#define TEXTE_LIBELLE_BLANC			"Tour aux Blancs !"
#define TEXTE_LIBELLE_NOIR			"Tour aux Noirs !"


namespace vue 
{
	constexpr char		CARACTERE_ROI_NOIR					= 'k';
	constexpr char		CARACTERE_ROI_BLANC					= 'K';
	constexpr char		CARACTERE_CAVALIER_NOIR				= 'n';
	constexpr char		CARACTERE_CAVALIER_BLANC			= 'N';
	constexpr char		CARACTERE_TOUR_NOIRE				= 'r';
	constexpr char		CARACTERE_TOUR_BLANCHE				= 'R';
	const QString		TITRE_ECHEC							= "Échec";
	const QString		TITRE_ERREUR						= "Erreur";
	const QString		MESSAGE_ERREUR						= "Mouvement pas accepté.";
	const QString		CHEMIN_ROI_NOIR						= "img/RoiNoir.png";
	const QString		CHEMIN_ROI_BLANC					= "img/RoiBlanc.png";
	const QString		CHEMIN_TOUR_NOIRE					= "img/TourNoire.png";
	const QString		CHEMIN_TOUR_BLANCHE					= "img/TourBlanche.png";
	const QString		CHEMIN_CAVALIER_NOIR				= "img/CavalierNoir.png";
	const QString		CHEMIN_CAVALIER_BLANC				= "img/CavalierBlanc.png";
	const QString		CHEMIN_ICONE_FENETRE				= "img/windowIcon.png";
	const QString		TOUR_BLANC							= "Blanc";
	const QString		TOUR_NOIR							= "Noir";
	const QString		NOM_FENETRE							= "Échiquier";
	const QString		AUCUN_TEXTE							= "aucun";
	const QString		STYLE_COMBO_POSITIONS_INIT			= "background: white; font-size: 12px; font-weight: bold; color: black; border: 2px groove white;";
	const QString		STYLE_REINITIALISER					= "background: darkgreen; font-size: 12px; font-weight: bold; color: white; border: 2px groove white;";
	const QString		STYLE_TERMINER						= "background: indianred; font-size: 12px; font-weight: bold; color: white; border: 2px groove white;";
	const QString		TEXTE_TERMINER						= "Terminer partie";
	const QString		TEXTE_REINITIALISER					= "Réinitialiser partie";
	const std::string	CHAMP_ERRONE						= "NxxxKxxR/8/8/8/8/8/8/rxkkxnxx b";
	const std::string	POSITION_BOURDONNAIS_MCDONNELL_1834 = "xRxxxxxx/nxxxxxxx/8/kxKxxxxx/8/8/8/8 w";
	const std::string	POSITION_POLGAR_KASPAROV_1996		= "xxxxRxxx/8/8/8/xxxxxxxK/xxxxxkxx/xxxxnxxx/xxxxxxrx w";
	const std::string	POSITION_ALEKHINE_CAPABLANCA_1927	= "8/rxxnxxxx/xxxkxxxx/8/xxxKxxxx/8/xRxxxxxx/8 w";
	const std::string	POSITION_KARPOV_FTACNIK_1988		= "8/xxxxxRxx/xnxxKxxx/8/8/xxxxxxxk/8/8 w";
	const std::string	TEXTE_EXCEPTION_N_ROIS				= "Exception NombreRoisExact :: ";
	const QColor		PALETTE_NOIRE						= QColor::fromRgb(181, 136, 99);
	const QColor		PALETTE_BLANCHE						= QColor::fromRgb(240, 217, 181);
	constexpr int		MARGES_TOUR_PARTIE					= 10;
	constexpr int		EST_PAIR							= 2;
	constexpr int		TAILLE_ICONE						= 75;
	constexpr int		POSITION_UN							= 0;
	constexpr int		POSITION_DEUX						= 1;
	constexpr int		POSITION_TROIS						= 2;
	constexpr int		POSITION_QUATRE						= 3;
	constexpr int		DIMENSION_H_COMBO_POSIITIONS_INIT	= 100;
	constexpr int		DIMENSION_V_COMBO_POSIITIONS_INIT	= 50;
	constexpr int		DIMENSION_H_REINITIALISER			= 100;
	constexpr int		DIMENSION_V_REINITIALISER			= 50;
	constexpr int		DIMENSION_H_TERMINER				= 100;
	constexpr int		DIMENSION_V_TERMINER				= 50;
	constexpr int		ESPACEMENT_ECHIQUIER_ET_BOUTONS		= 20;
	const QStringList	POSITIONS_INITIALES_POSSIBLES		= 
	{
		{"Bourdonnais vs. McDonnell (1834)"},
		{"Polgar vs. Kasparov (1996)"},
		{"Alekhine vs. Capablanca (1927)"},
		{"Karpov vs. Ftáčnik (1988)"}
	};
	const std::vector<int> VALEURS_ESPACEMENT = { 0, 2, 4 };

	enum class	EtatBouton { selectionner, placer };
	class		PiecesBouton;


	class EchiquierWindow : public QMainWindow 
	{
		Q_OBJECT

	public slots:
		void erreurMessage();
		void Echec();
		void terminerProgramme() const;
		void reinitialiserProgramme();

	public:
		EchiquierWindow(QWidget* parent = nullptr);

		void				addApp(QApplication*);
		void				initialiserLibelle(const modele::Couleur&) const;
		void				inverserEtatBouton();
		EtatBouton			getEtatBouton() const;
		QLabel*				getTourCourant() const;
		std::pair<int, int> getPositionClickTampon() const;
		void				setPositionClickTampon(const std::pair<int, int>&);
		PiecesBouton*		getBoutonTampon() const;
		void				setBoutonTampon(PiecesBouton*);
		modele::Plateau*	getPlateau() const;
		void				ajouterImage(PiecesBouton*, const char) const;
		void				ajouterCasesEchiquier(QGridLayout*);
		template <typename T>
		void				initialiserEspacementsObjets(T*, const int, const int, const int, const int, const int) const;
		template <typename T>
		void				initialiserObjet(T*, const QString&, const int, const int) const;

		~EchiquierWindow() override = default;

	private:
		QPushButton*						nouveauBouton(modele::Couleur couleur, int, int);
		PiecesBouton*						boutonTampon_;
		QLabel*								tourCourant_				= nullptr;
		EtatBouton							etatBouton_					= EtatBouton::selectionner;
		std::pair<int, int>					positionClickTampon_		= { 0, 0 };
		std::unique_ptr<modele::Plateau>	plateauGraphique_			= std::make_unique<modele::Plateau>(modele::Couleur::Blanc);
		QApplication*						app_						= nullptr;
		QGridLayout*						layoutPrincipalEchiquier_	= nullptr;
		QComboBox*							comboPositionsInitiales_	= nullptr;
	};


	class PiecesBouton : public QPushButton
	{
	public:
		PiecesBouton(const int, const int, const modele::Couleur&, EchiquierWindow*);

		void				enleverPiece();
		void				rajouterPiece(const QString&);
		void				initialiserBouton();
		void				initialiserPalette(const modele::Couleur&);
		modele::Couleur		getCouleur() const;
		void				setCouleurLibelle(const modele::Couleur&) const;
		void				mousePressEvent(QMouseEvent* event) override;

	private:
		int					positionX_;
		int					positionY_;
		modele::Couleur		couleur_;
		QPalette			palette_;
		EchiquierWindow*	echiquier_;
		const int			dimension_ = 100;
		bool				changementPosition = true;
	};


	class ErreurWindow : QMessageBox
	{
		Q_OBJECT
	public:
		ErreurWindow();
	};
};
