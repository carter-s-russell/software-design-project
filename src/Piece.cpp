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
