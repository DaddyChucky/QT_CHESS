/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui d�finit les fonctions pour les cases du plateau.
* \file   Case.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Cr�� le 31 mars 2021
*/


#include "Modele.h"


/**
*  Une case du plateau.
*  \param	[const string&]		nom				<Le nom de la case.>
*  \param	[bool]				estOccupee		<Vrai si la case est occup�e, faux autrement.>
*/
modele::Case::Case(const std::string& nom, bool estOccupee) :
	nom_(nom), estOccupee_(estOccupee)
{}


/**
*  Remplace l'occupation d'une case par une nouvelle pi�ce.
*  \param	[unique_ptr<Piece>]		nouvellePiece	<La nouvelle pi�ce qui remplace.>
*/
void modele::Case::setPieceOccupante(std::unique_ptr<Piece> nouvellePiece)
{
	pieceOccupante_.reset();
	pieceOccupante_ = move(nouvellePiece);
}


/**
*  Retourne le nom de la case.
*  \return	[string]	<Le nom de la case.>
*/
std::string modele::Case::getNomCase() const
{
	return nom_;
}


/**
*  Retourne l'occupation d'une case par une pi�ce sous forme d'un bool�en.
*  \return	[bool]						<La case est-elle occup�e ? Oui / non.>
*/
bool modele::Case::getOccupation() const
{
	return estOccupee_;
}


/**
*  Retourne un pointeur vers la pi�ce qui occupe la case.
*  \return	[Piece*]	<Un pointeur brut vers la pi�ce qui occupe la case.>
*/
modele::Piece* modele::Case::getPieceOccupante() const
{
	return pieceOccupante_.get();
}


/**
*  D�truit la pi�ce qui occupe une case.
*/
void modele::Case::detruirePieceOccupante()
{
	pieceOccupante_.reset();
}


/**
*  D�l�gue la propri�t� unique � la pi�ce qui occupe une case.
*  \return	[unique_ptr<Piece>]		<Un pointeur unique de la pi�ce qui se fait d�l�guer.>
*/
std::unique_ptr<modele::Piece> modele::Case::changerPossessionPiece()
{
	return move(pieceOccupante_);
}


/**
*  Inverse l'occupation d'une case par une pi�ce.
*/
void modele::Case::inverserOccupation()
{
	if (estOccupee_)
		estOccupee_ = false;

	else
		estOccupee_ = true;
}
