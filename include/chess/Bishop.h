/**
 * @file
 * @brief Defines the bishop class
 * @author Carter Russell
 * @date 2025-11-22
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "chess/Piece.h"

class Bishop : public Piece { // Bishop is a subclass of Piece
public:
    // Constructor to set the bishop's color
    Bishop(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) override;
};

#endif // BISHOP_H
