#include "chess/Board.h"
#include "chess/Piece.h"
#include "chess/Pawn.h" // We need this to check m_hasMoved
#include <cassert>       // For the assert() function
#include <iostream>      // For printing test status

/**
 * @file
 * @brief Unit tests for the Pawn::isValidMove logic.
 */
int main() {
    std::cout << "--- Running Pawn Move Tests ---" << std::endl;

    // --- LIGHT PAWN TESTS ---
    // The LIGHT pawns start on rank 6 (y=6)
    
    // Test 1: LIGHT 1-step forward (e.g., e2->e3)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6); //
        assert(pawn != nullptr); // Sanity check
        
        bool canMove = pawn->isValidMove(4, 6, 4, 5, &testBoard); //
        assert(canMove == true);
        std::cout << "PASSED: LIGHT Pawn 1-step forward." << std::endl;
    }

    // Test 2: LIGHT 2-step forward (e.g., e2->e4)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6);
        
        bool canMove = pawn->isValidMove(4, 6, 4, 4, &testBoard);
        assert(canMove == true);
        std::cout << "PASSED: LIGHT Pawn 2-step forward." << std::endl;
    }

    // Test 3: LIGHT invalid diagonal (empty square) (e.g., e2->f3)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6);
        
        bool canMove = pawn->isValidMove(4, 6, 5, 5, &testBoard);
        assert(canMove == false);
        std::cout << "PASSED: LIGHT Pawn invalid diagonal (empty)." << std::endl;
    }

    // Test 4: LIGHT invalid sideways (e.g., e2->f2)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6);
        
        bool canMove = pawn->isValidMove(4, 6, 5, 6, &testBoard);
        assert(canMove == false);
        std::cout << "PASSED: LIGHT Pawn invalid sideways." << std::endl;
    }

    // Test 5: LIGHT invalid backwards (e.g., e2->e1)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6);
        
        bool canMove = pawn->isValidMove(4, 6, 4, 7, &testBoard);
        assert(canMove == false);
        std::cout << "PASSED: LIGHT Pawn invalid backwards." << std::endl;
    }


    // --- DARK PAWN TESTS ---
    // The DARK pawns start on rank 1 (y=1)

    // Test 6: DARK 1-step forward (e.g., e7->e6)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 1);
        assert(pawn != nullptr);
        assert(pawn->getColor() == PieceColor::DARK); //
        
        bool canMove = pawn->isValidMove(4, 1, 4, 2, &testBoard);
        assert(canMove == true);
        std::cout << "PASSED: DARK Pawn 1-step forward." << std::endl;
    }

    // Test 7: DARK 2-step forward (e.g., e7->e5)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 1);
        
        bool canMove = pawn->isValidMove(4, 1, 4, 3, &testBoard);
        assert(canMove == true);
        std::cout << "PASSED: DARK Pawn 2-step forward." << std::endl;
    }

    // Test 8: DARK invalid diagonal (empty square) (e.g., e7->f6)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 1);
        
        bool canMove = pawn->isValidMove(4, 1, 5, 2, &testBoard);
        assert(canMove == false);
        std::cout << "PASSED: DARK Pawn invalid diagonal (empty)." << std::endl;
    }

    // Test 9: LIGHT diagonal CAPTURE (e.g., e2->f3)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6); // Get LIGHT pawn at e2
        
        // Manually place an enemy (DARK) pawn at f3 (5, 5)
        testBoard.setPieceAt(5, 5, std::make_unique<Pawn>(PieceColor::DARK));
        
        bool canMove = pawn->isValidMove(4, 6, 5, 5, &testBoard);
        assert(canMove == true);
        std::cout << "PASSED: LIGHT Pawn valid diagonal (Capture)." << std::endl;
    }

    // Test 10: LIGHT 2-step BLOCKED (e.g., e2->e4)
    {
        Board testBoard;
        Piece* pawn = testBoard.getPieceAt(4, 6); // Get LIGHT pawn at e2
        
        // Manually place a friendly (LIGHT) pawn at e3 (4, 5)
        testBoard.setPieceAt(4, 5, std::make_unique<Pawn>(PieceColor::LIGHT));
        
        bool canMove = pawn->isValidMove(4, 6, 4, 4, &testBoard);
        assert(canMove == false);
        std::cout << "PASSED: LIGHT Pawn invalid 2-step (Blocked)." << std::endl;
    }
    std::cout << "--- All Pawn tests passed! ---" << std::endl;

    return 0;
}
