/**
* Projet final :: INF1015 :: Livrable 3. Structures pour le main.
* \file   Modele.h
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/

#pragma once
#include <QApplication>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <gsl/span>
#include <cppitertools/range.hpp>
#include <cppitertools/enumerate.hpp>

namespace modele 
{
	constexpr int		DIMENSION_PLATEAU_X			= 8;
	constexpr int		DIMENSION_PLATEAU_Y			= 8;
	constexpr int		NB_CASES					= 64;
	constexpr int		LIMITE_CONFRONTATIONS_ROIS	= 2;
	constexpr int		POSITION_PIECE_INITIALE		= 0;
	constexpr int		FACTEUR_RACINE				= 2;
	constexpr char		CASE_VIDE					= 'X';
	constexpr char		CARACTERE_ROI_NOIR			= 'k';
	constexpr char		CARACTERE_ROI_BLANC			= 'K';
	constexpr char		CARACTERE_CAVALIER_NOIR		= 'n';
	constexpr char		CARACTERE_CAVALIER_BLANC	= 'N';
	constexpr char		CARACTERE_TOUR_NOIRE		= 'r';
	constexpr char		CARACTERE_TOUR_BLANCHE		= 'R';
	constexpr char		CARACTERE_SEPARATION		= '/';
	constexpr char		CARACTERE_PIECE_VIDE		= 'x';
	constexpr char		CARACTERE_LIGNE_VIDE		= '8';
	constexpr char		CARACTERE_ESPACE			= ' ';
	constexpr char		DEBUTER_NOIR				= 'b';
	const std::string	ERREUR_TROP_DE_ROIS			= "Le nombre de rois dépasse le seuil autorisé.";

	class Plateau;

	//? La transparence est utile pour calculer si le roi est à découvert si la pièce se fait déplacer (Livrable 2)
	const enum class Couleur { Noir, Blanc };

	class Piece
	{
	public:
		Piece(const Couleur&);

		void								ajouterMouvement(const std::pair<int, int>&);
		void								effacerMouvements();
		std::vector<std::pair<int, int>>	getMouvementsPossibles() const;
		Couleur								getCouleur() const;
		bool								estInterieurBornes(const std::pair<int, int>&) const;
		void								setCouleur(const Couleur&);
		virtual char						getNom() const = 0;
		virtual void						calculerMouvementsPossibles(const std::pair<int, int>&, Plateau*) = 0;
		virtual void						calculerMouvementsPossiblesSimples(const std::pair<int, int>&, Plateau*) = 0;
		virtual char						getCaractere() const = 0;

		virtual	~Piece() = default;

	private:
		Couleur								couleur_;
		std::vector<std::pair<int, int>>	mouvementsPossibles_;
	};


	class Roi : public Piece
	{
	public:
		Roi(const Couleur&);

		bool estConfrontationRoiAdverse(const std::pair<int, int>&, const std::pair<int, int>&) const;
		void calculerMouvementsPossibles(const std::pair<int, int>&, Plateau*) override;
		void calculerMouvementsPossiblesSimples(const std::pair<int, int>&, Plateau*) override;
		char getNom()		const override;
		char getCaractere() const override;

	private:
		char caracterePiece_;
	};


	class Cavalier : public Piece
	{
	public:
		Cavalier(const Couleur&);

		void calculerMouvementsPossibles(const std::pair<int, int>&, Plateau*) override;
		void calculerMouvementsPossiblesSimples(const std::pair<int, int>&, Plateau*) override;
		char getNom()		const override;
		char getCaractere() const override;

	private:
		char caracterePiece_;
	};


	class Tour : public Piece
	{
	public:
		Tour(const Couleur&);

		void calculerMouvementsPossibles(const std::pair<int, int>&, Plateau*) override;
		void calculerMouvementsPossiblesSimples(const std::pair<int, int>&, Plateau*) override;
		char getNom()		const override;
		char getCaractere() const override;

	private:
		char caracterePiece_;
		bool verificationEchec_ = false;
	};


	class Case
	{
	public:
		Case(const std::string&, bool);

		void					setPieceOccupante(std::unique_ptr<Piece>);
		std::string				getNomCase()		const;
		bool					getOccupation()		const;
		Piece*					getPieceOccupante() const;
		void					detruirePieceOccupante();
		std::unique_ptr<Piece>	changerPossessionPiece();
		void					inverserOccupation();


	private:
		std::string				nom_;
		bool					estOccupee_;
		std::unique_ptr<Piece>	pieceOccupante_;
	};

	class Plateau
	{
	public:
		Plateau(const Couleur&);

		std::unique_ptr<Case>					creerCase(const std::string&, bool) const;
		std::unique_ptr<Piece>					creerPiece(char) const;
		void									reinitialiserNRois();
		void									creer(const std::string&);
		std::pair<Case*, std::pair<int, int>>	trouverCase(const char, bool) const;
		Case*									trouverCase(const std::pair<int, int>&) const;
		void									calculerMouvementsPossibles(Piece*, const std::pair<int, int>&);
		void									reinitialiserPositionsValidesPieces();
		void									inverserTour();
		void									setTour(const Couleur&);
		Couleur									getTour() const;
		void									effectuerChangementPosition(Case*, Case*);
		Case*									getCase(const int, const int) const;
		void									inverserEchec();
		bool									testEchecApresDeplacement(Case*);
		bool									testEchecProtection(const std::pair<int, int>&, const std::pair<int, int>&);
		bool									getEtatEchec() const;
		std::pair<int, int>						getPositionCase(Case*) const;
		bool									testEchecApresDeplacementAdversaire(Case* caseFinale);
		bool									testEchecADecouvert(const std::pair<int, int>&, const std::pair<int, int>& mouvement);
		bool									testEchecAuRoi(const std::pair<int, int>&, const std::pair<int, int>&);

	private:
		Couleur					tour_;
		bool					echec_ = false;
		std::unique_ptr<Case>	plateau_[DIMENSION_PLATEAU_X][DIMENSION_PLATEAU_Y];
		const char*				nomCases_[NB_CASES] = {
			"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8",
			"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
			"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
			"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
			"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
			"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
			"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
			"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1"
		};
		inline static int		nRois_ = 0;
	};

	class NombreRoisExact : public std::invalid_argument
	{
	public:
		using invalid_argument::invalid_argument;
	};
};
