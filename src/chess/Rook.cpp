#include "chess/Rook.h"
#include "chess/Board.h"
#include <cmath>
#include <iostream>

/**
 * @brief The Rook constructor
 *
 * It uses a ternary operator to handle the image of the Rook from its color
 * @param color Color of the Rook 
 */
Rook::Rook(PieceColor color)
    : Piece(color, 'r', (color == PieceColor::LIGHT) ? "res/rook_light.png" : "res/rook_dark.png"),
      m_hasMoved(false)
{
    // empty constructor body
}

bool Rook::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // general information about the move
    int deltaX = std::abs(toX - curX);
    int deltaY = std::abs(toY - curY);
    int dirX = (curX < toX) - (curX > toX);
    int dirY = (curY < toY) - (curY > toY);
    // check if the space is on a straight line
    bool validSpace = (deltaX == 0) || (deltaY == 0);

    for (int i = 1; validSpace && i <= std::max(deltaX, deltaY); i++) {
        // i represents the counter between the starting space and the ending space
        Piece* pieceAtSquare = board->getPieceAt(curX + (dirX * i), curY + (dirY * i));

        if (i == std::max(deltaX, deltaY)) {
            // valid move is true if the target square is either empty or has a square of the opposite color
            validMove = (!pieceAtSquare) || (pieceAtSquare->getColor() != m_color);
        } else if (pieceAtSquare) {
            // if a space between the piece and the target square is not empty, break out of the for loop
            // as it is not a valid move
            break;
        }
    }

    // make sure move does not cause a check
    if (checkSafety && validMove) {
        avoidCheck = board->avoidsCheck(curX, curY, toX, toY);
    }

    // must be a valid psuedo-move and avoid any checks to be a valid move
    return validMove && avoidCheck;
}

void Rook::setHasMoved() {
    m_hasMoved = true;
}

bool Rook::getHasMoved() {
    return m_hasMoved;
}
