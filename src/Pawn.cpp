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
    : Piece(color, (color == PieceColor::LIGHT) ? "res/pawn_light.png" : "res/pawn_dark.png"),
      m_hasMoved(false)
{
    // empty constructor body
}

bool Pawn::isValidMove(int curX, int curY, int toX, int toY, Board* board) {
    bool sameFile = (curX == toX);
    bool adjFile = (std::abs(curX - toX) == 1);
    int deltaRank = curY - toY;
    Piece* pieceAtTarget = board->getPieceAt(toX, toY);
    int direction = (m_color == PieceColor::LIGHT) ? 1 : -1;

    // check for 1 rank forward
    if (sameFile && (deltaRank == direction) && (pieceAtTarget == nullptr)) {
        return true;
    }

    // check for 2 rank forward
    if (sameFile && (deltaRank == 2 * direction) && (pieceAtTarget == nullptr) && !m_hasMoved) {
        // check for square between
        // LIGHT is toY+1, and vice versa, so direction works perfectly
        return (board->getPieceAt(toX, toY + direction) == nullptr);
    }

    // check for diagonal capture
    if (adjFile && (deltaRank == direction) && (pieceAtTarget != nullptr)) {
        return (pieceAtTarget->getColor() != m_color);
    }

    // TODO: check for enpassant
    if ( false ) {
        return true;
    }

    // base case, move is not valid
    return false;
}
