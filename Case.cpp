/**
* Projet final :: INF1015 :: Livrable 3. Fichier qui définit les fonctions pour les cases du plateau.
* \file   Case.cpp
* \author Charles De Lafontaine & Benoit Dambrine & al.
* \date   9 mai 2021
* Créé le 31 mars 2021
*/


#include "Modele.h"


/**
*  Une case du plateau.
*  \param	[const string&]		nom				<Le nom de la case.>
*  \param	[bool]				estOccupee		<Vrai si la case est occupée, faux autrement.>
*/
modele::Case::Case(const std::string& nom, bool estOccupee) :
	nom_(nom), estOccupee_(estOccupee)
{}


/**
*  Remplace l'occupation d'une case par une nouvelle pièce.
*  \param	[unique_ptr<Piece>]		nouvellePiece	<La nouvelle pièce qui remplace.>
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
*  Retourne l'occupation d'une case par une pièce sous forme d'un booléen.
*  \return	[bool]						<La case est-elle occupée ? Oui / non.>
*/
bool modele::Case::getOccupation() const
{
	return estOccupee_;
}


/**
*  Retourne un pointeur vers la pièce qui occupe la case.
*  \return	[Piece*]	<Un pointeur brut vers la pièce qui occupe la case.>
*/
modele::Piece* modele::Case::getPieceOccupante() const
{
	return pieceOccupante_.get();
}


/**
*  Détruit la pièce qui occupe une case.
*/
void modele::Case::detruirePieceOccupante()
{
	pieceOccupante_.reset();
}


/**
*  Délègue la propriété unique à la pièce qui occupe une case.
*  \return	[unique_ptr<Piece>]		<Un pointeur unique de la pièce qui se fait déléguer.>
*/
std::unique_ptr<modele::Piece> modele::Case::changerPossessionPiece()
{
	return move(pieceOccupante_);
}


/**
*  Inverse l'occupation d'une case par une pièce.
*/
void modele::Case::inverserOccupation()
{
	if (estOccupee_)
		estOccupee_ = false;

	else
		estOccupee_ = true;
}
