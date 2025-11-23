/**
 * @file
 * @brief Defines the queen class
 * @author Carter Russell
 * @date 2025-11-22
 */

#ifndef QUEEN_H
#define QUEEN_H

#include "chess/Piece.h"

class Queen : public Piece { // Queen is a subclass of Piece
public:
    // Constructor to set the queen's color
    Queen(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) override;
};

#endif // QUEEN_H
