/**
 * @file
 * @brief Defines the abstract base class for all chess pieces. 
 * @author Carter Russell
 * @date 2025-11-17
 */

#ifndef PIECE_H
#define PIECE_H

#include "FEHImages.h"

/**
 * @brief Forward-declaration of Board class
 * Needed since Board includes Piece, but isValidMove needs some reference to Board
 */
class Board;

/**
 * @brief Describes the color of a chess piece.
 */
enum class PieceColor {
    LIGHT,
    DARK
};

class Piece {
protected:
    PieceColor m_color;
    FEHImage m_image;

public:
    // Constructor to set the piece's color
    Piece(PieceColor color, const char* filename);

    // Virtual destructor so actual piece's destructor is used
    virtual ~Piece() {}

    // -- Virtual functions -- To be implemented by subclasses
    
    /**
     * @brief Checks if a move is pseudo-legal (ignores check)
     * @return true if the move follows the piece's rules
     */
    virtual bool isValidMove(int curX, int curY, int toX, int toY, Board* board) = 0;

    /**
     * @brief Change the boolean for hasMoved for a Piece, if it has said boolean
     */
    virtual void setHasMoved() {
        // do nothing by default
    }

    // -- Regular functions --

    /**
     * @brief Tells the FEH library how to draw this piece
     * @param x The top-left corner X pos
     * @param y The top-left corner Y pos
     */
    void draw(int x, int y);

    PieceColor getColor() const { return m_color; }
};

#endif // PIECE_H
