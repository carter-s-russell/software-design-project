/**
 * @file
 * @brief Defines the knight class
 * @author Carter Russell
 * @date 2025-11-22
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chess/Piece.h"

class Knight : public Piece { // Knight is a subclass of Piece
public:
    // Constructor to set the knight's color
    Knight(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) override;
};

#endif // KNIGHT_H
