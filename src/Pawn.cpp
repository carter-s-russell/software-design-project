#include "chess/Pawn.h"
#include "chess/Board.h"
#include <cmath>

/**
 * @brief The Pawn constructor
 *
 * It uses a ternary operator to handle the image of the Pawn from its color
 * @param color Color of the Pawn 
 */
Pawn::Pawn(PieceColor color)
    : Piece(color, 'p', (color == PieceColor::LIGHT) ? "res/pawn_light.png" : "res/pawn_dark.png"),
      m_hasMoved(false)
{
    // empty constructor body
}

bool Pawn::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // general information about the move
    bool sameFile = (curX == toX);
    bool adjFile = (std::abs(curX - toX) == 1);
    int deltaRank = curY - toY;
    Piece* pieceAtTarget = board->getPieceAt(toX, toY);
    int direction = (m_color == PieceColor::LIGHT) ? 1 : -1;

    // check for 1 rank forward
    if (sameFile && (deltaRank == direction) && !pieceAtTarget) {
        validMove = true;
    }

    // check for 2 rank forward
    if (sameFile && (deltaRank == 2 * direction) && !pieceAtTarget && !m_hasMoved) {
        // check for square between
        // LIGHT is toY+1, and DARK is toY-1, so direction works perfectly
        validMove = !board->getPieceAt(toX, toY + direction);
    }

    // check for diagonal capture
    if (adjFile && (deltaRank == direction) && pieceAtTarget) {
        validMove = (pieceAtTarget->getColor() != m_color);
    }

    // check for enpassant
    int enPassantRank = (m_color == PieceColor::LIGHT) ? 3 : 4;
    if (adjFile && (deltaRank == direction) && (curY == enPassantRank) && !pieceAtTarget) {
        validMove = board->canEnPassant(toX, m_color);
    }

    // make sure move does not cause a check
    if (checkSafety && validMove) {
        avoidCheck = board->avoidsCheck(curX, curY, toX, toY);
    }

    // must be a valid psuedo-move and avoid any checks to be a valid move
    return validMove && avoidCheck;
}

void Pawn::setHasMoved() {
    m_hasMoved = true;
}

bool Pawn::getHasMoved() {
    return m_hasMoved;
}
