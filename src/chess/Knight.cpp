#include "chess/Knight.h"
#include "chess/Board.h"
#include <cmath>

/**
 * @brief The Knight constructor
 *
 * It uses a ternary operator to handle the image of the Knight from its color
 * @param color Color of the Knight 
 */
Knight::Knight(PieceColor color)
    : Piece(color, 'n', (color == PieceColor::LIGHT) ? "res/knight_light.png" : "res/knight_dark.png")
{
    // empty constructor body
}

bool Knight::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // general information about the move
    int deltaRank = std::abs(curY - toY);
    int deltaFile = std::abs(curX - toX);
    bool validSpace = (deltaRank + deltaFile == 3) && (deltaRank != 0) && (deltaFile != 0); 
    Piece* selectedPiece = board->getPieceAt(toX, toY);
    
    // check if the space is valid and if the space is empty or the other team
    validMove = validSpace && (!selectedPiece || selectedPiece->getColor() != m_color);

    // make sure move does not cause a check
    if (checkSafety && validMove) {
        avoidCheck = board->avoidsCheck(curX, curY, toX, toY);
    }

    // must be a valid psuedo-move and avoid any checks to be a valid move
    return validMove && avoidCheck;
}
