#include "chess/Piece.h"

/**
 * @brief The base Piece constructor
 *
 * @param color The piece's color (LIGHT or DARK)
 * @param filename Path to the image of the piece ("res/pawn_light.png") 
 */
Piece::Piece(PieceColor color, const char* filename) : m_color(color) {
    m_image.Open(filename);
}

/**
 * @brief Draws the Piece's image at the coordinates
 * @param x The X coordinate for the top left of the image 
 * @param y The Y coordinate for the top left of the image 
 */
void Piece::draw(int x, int y) {
    m_image.Draw(x, y);
}

