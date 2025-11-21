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

const int SQUARE_SIZE = 30;

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

    /**
     * @brief Member variables to keep track of the position of each king
     * Initialized to the starting square of the king
     */
    int m_lightKingPosX;
    int m_lightKingPosY;
    int m_darkKingPosX;
    int m_darkKingPosY;

    /**
     * @brief Member vairables for images of move indicators
     */
    FEHImage m_indicatorFreeSpace = "res/move_indicator.png";
    FEHImage m_indicatorCapture = "res/capture_indicator.png";
public:
    /**
     * @brief Construct a new Board object and set up the pieces 
     */
    Board();

    /**
     * @brief Sets up all the pieces according to a given FEN position
     * @param fen A Forsyth–Edwards Notation for the desired position
     */
    void setupBoard(const std::string& fen);

    /**
     * @brief Gets the piece at a specific coordinate
     * @return A pointer to the Piece or nullptr if the square is empty 
     */
    Piece* getPieceAt(int x, int y) {
        return m_grid[y][x].get();
    }

    /**
     * @brief Manually sets a piece on the board
     * @param x The x-coordinate (0-7)
     * @param y The y-coordinate (0-7)
     * @param piece The std::unique_ptr<Piece> to place
     */
    void setPieceAt(int x, int y, std::unique_ptr<Piece> piece) {
        m_grid[y][x] = std::move(piece);
    }

    /**
     * @brief Moves a piece from one square to another
     * @param curX X position of the piece to be moved
     * @param curY Y position of the piece to be moved
     * @param toX X position of the square to be moved to
     * @param toY Y position of the square to be moved to
     */
    void move(int curX, int curY, int toX, int toY);

    /**
     * @brief Draws the board and its pieces
     */
    void draw();

    /**
     * @brief Draws the available move indicators after the pieces have been drawn
     * @param x X position of selected piece
     * @param y Y position of selected piece
     */
    void drawAvailableMoves(int x, int y);

    /**
     * @brief Intended to be called after a move is made, checks if there is a check present on the current board
     * @param currentTurn The color of the piece that just moved
     * @return true if there is a check present, false otherwise
     */
    bool isCheck(PieceColor currentTurn);

    /**
     * @brief Checks if a valid move avoids moving into check 
     * uses the same params as isValidMove, because only that function will call it
     * @param curX The current X position of the piece
     * @param curY The current Y position of the piece
     * @param toX The desired X position of the piece
     * @param toY The desired Y position of the piece
     * @return true if the move does avoid check, false otherwise
     */
    bool avoidsCheck(int curX, int curY, int toX, int toY);

    /**
     * @brief Checks if position of king needs to be updated by giving the current and
     * to positions of the latest move
     * @param curX The current X position of the piece
     * @param curY The current Y position of the piece
     * @param toX The desired X position of the piece
     * @param toY The desired Y position of the piece
     */
    void updateKingPos(int curX, int curY, int toX, int toY);
};

#endif // BOARD_H
