/**
 * @file
 * @brief Defines the rook class
 * @author Carter Russell
 * @date 2025-11-22
 */

#ifndef ROOK_H
#define ROOK_H

#include "chess/Piece.h"

class Rook : public Piece { // Rook is a subclass of Piece
private:
    /**
     * @brief Tracks if the pawn has made its first move
     * (might be helpful in the future for enpassant)
     */
    bool m_hasMoved;

public:
    // Constructor to set the rook's color
    Rook(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) override;
    virtual void setHasMoved() override;
};

#endif // ROOK_H
