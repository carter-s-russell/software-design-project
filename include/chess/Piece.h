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
    char m_type;

public:
    // Constructor to set the piece's color
    Piece(PieceColor color, char type, const char* filename);

    // Virtual destructor so actual piece's destructor is used
    virtual ~Piece() {}

    // -- Virtual functions -- To be implemented by subclasses
    
    /**
     * @brief Checks if the move is valid and avoids moving into any checks
     * @param curX The current X position of the piece 
     * @param curY The current Y position of the piece 
     * @param toX The X position of the desired move
     * @param toY The Y position of the desired move
     * @param checkSafety If the function should check if the move avoids check or not 
     * @param board A pointer to the chess board 
     * @return True if the move is valid, false otherwise 
     */
    virtual bool isValidMove(int curX, int curY, int toX, int toY, bool checkSafety, Board* board) = 0;

    /**
     * @brief Change the boolean for hasMoved for a Piece, if it has said boolean
     */
    virtual void setHasMoved() {
        // do nothing by default
    }

    // -- Regular functions --

    /**
     * @brief Draws the Piece's image at the coordinates
     * @param x The X coordinate for the top left of the image 
     * @param y The Y coordinate for the top left of the image 
     */
    void draw(int x, int y) {
        m_image.Draw(x, y);
    }


    /**
     * @brief Get the color of the piece
     * @return The color of the piece as a PieceColor enum member
     */
    PieceColor getColor() const { return m_color; }

    /**
     * @brief Get the type of piece
     * @return The type of the piece as a lowercase char
     */
    char getType() const { return m_type; }
};

#endif // PIECE_H
