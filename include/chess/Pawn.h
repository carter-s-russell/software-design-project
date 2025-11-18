/**
 * @file
 * @brief Defines the pawn class
 * @author Carter Russell
 * @date 2025-11-17
 */

#ifndef PAWN_H
#define PAWN_H

#include "chess/Piece.h"

class Pawn : public Piece { // Pawn is a subclass of Piece
private:
    /**
     * @brief Tracks if the pawn has made its first move
     * (might be helpful in the future for enpassant)
     */
    bool m_hasMoved;

public:
    // Constructor to set the pawn's color
    Pawn(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, Board* board) override;
};

#endif // PAWN_H
