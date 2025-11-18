/**
 * @file
 * @brief Defines the main chess Board class.
 * @author Carter Russell
 * @date 2025-11-17
 */

#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include "chess/Piece.h"

class Board {
private:
    /**
     * @brief An 8x8 grid of smart pointers to Piece objects
     * std::unique_ptr prevents memory leaks from pieces not being deleted in memory after they exit scope
     * a nullptr indicates the square is empty
     */
    std::unique_ptr<Piece> m_grid[8][8];

    /**
     * @brief Sets all the pieces to their starting position
     */
    void setupBoard();
public:
    /**
     * @brief Construct a new Board object and set up the pieces 
     */
    Board();

    /**
     * @brief Gets the piece at a specific coordinate
     * @return A pointer to the Piece or nullptr if the square is empty 
     */
    Piece* getPieceAt(int x, int y) {
        return m_grid[y][x].get();
    }

    /**
     * @brief Manually sets a piece on the board.
     * @param x The x-coordinate (0-7).
     * @param y The y-coordinate (0-7).
     * @param piece The std::unique_ptr<Piece> to place.
     */
    void setPieceAt(int x, int y, std::unique_ptr<Piece> piece) {
        m_grid[y][x] = std::move(piece);
    }

    /**
     * @brief Draws the board and its pieces
     */
    void draw();
};

#endif // BOARD_H
