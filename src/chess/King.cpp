#include "chess/King.h"
#include "chess/Board.h"
#include <cmath>
#include <iostream>

/**
 * @brief The King constructor
 *
 * It uses a ternary operator to handle the image of the King from its color
 * @param color Color of the King 
 */
King::King(PieceColor color)
    : Piece(color, 'k', (color == PieceColor::LIGHT) ? "res/king_light.png" : "res/king_dark.png"),
      m_hasMoved(false)
{
    // empty constructor body
}

bool King::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // pointer to the piece at the target space
    Piece* pieceAtTarget = board->getPieceAt(toX, toY);

    // checks if the king is trying to move to a space within one around it
    // includes the same space, which should be filtered out later
    bool oneSpace = ((std::abs(curX-toX) <= 1) && (std::abs(curY-toY) <= 1));

    // if the king is trying to move to an empty space or a space with an opposite color piece
    if (oneSpace && ((pieceAtTarget == nullptr) || pieceAtTarget->getColor() != m_color)) {
        validMove = true;
    }

    // castling logic
    // find if the move to space is a space for castling
    bool castleSpace = !m_hasMoved && (std::abs(curX-toX) == 2) && (curY == toY);
    // get the piece that should be the rook on the side of the castling
    Piece* potentialRook = (toX-curX == 2) ? board->getPieceAt(7,curY) : board->getPieceAt(0,curY); 
    // test if the space is correct for caslting and the corner has a rook that hasnt moved
    if (castleSpace && potentialRook && potentialRook->getType() == 'r' && !potentialRook->getHasMoved()) {
        // find if all spaces are empty between the rook and king
        bool emptyBetween;
        if (toX - curX == 2) {
            emptyBetween = !board->getPieceAt(5,curY) && !board->getPieceAt(6,curY);
        } else {
            emptyBetween = !board->getPieceAt(1,curY) && !board->getPieceAt(2,curY) && !board->getPieceAt(3,curY);
        }

        // average of curX and toX gets the space between
        validMove = emptyBetween && board->avoidsCheck(curX, curY, (curX+toX)/2, toY);
    }

    // make sure move does not cause a check
    if (checkSafety && validMove) {
        avoidCheck = board->avoidsCheck(curX, curY, toX, toY);
    }

    // must be a valid psuedo-move and avoid any checks to be a valid move
    return validMove && avoidCheck;
}

void King::setHasMoved() {
    m_hasMoved = true;
}

bool King::getHasMoved() {
    return m_hasMoved;
}
