#include "chess/Bishop.h"
#include "chess/Board.h"
#include <cmath>
#include <iostream>

/**
 * @brief The Bishop constructor
 *
 * It uses a ternary operator to handle the image of the Bishop from its color
 * @param color Color of the Bishop 
 */
Bishop::Bishop(PieceColor color)
    : Piece(color, 'b', (color == PieceColor::LIGHT) ? "res/bishop_light.png" : "res/bishop_dark.png")
{
    // empty constructor body
}

bool Bishop::isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) {
    bool validMove = false;
    bool avoidCheck = !checkSafety; // if we don't check for checks, this will be true

    // general information about the move
    int deltaX = std::abs(toX - curX);
    int deltaY = std::abs(toY - curY);
    int dirX = (curX < toX) - (curX > toX);
    int dirY = (curY < toY) - (curY > toY);
    // check if the space is on a diagonal
    bool validSpace = (deltaX == deltaY);

    for (int i = 1; validSpace && i <= deltaX; i++) {
        // i represents the counter between the starting space and the ending space
        Piece* pieceAtSquare = board->getPieceAt(curX + (dirX * i), curY + (dirY * i));

        if (i == deltaX) {
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
