/**
 * @file
 * @brief Defines the king class
 * @author Carter Russell
 * @date 2025-11-18
 */

#ifndef KING_H
#define KING_H

#include "chess/Piece.h"

class King : public Piece { // King is a subclass of Piece
private:
    /**
     * @brief Tracks if the king has made its first move
     * (might be helpful in the future for castling)
     */
    bool m_hasMoved;

public:
    // Constructor to set the king's color
    King(PieceColor color);

    // function overrides
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) override;
    virtual void setHasMoved() override;
};

#endif // KING_H
