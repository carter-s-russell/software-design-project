#include "chess/Board.h"
#include "chess/Piece.h"
#include "chess/Pawn.h"
#include <cassert>
#include <iostream>

void runTest(bool condition, const char* testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << std::endl;
    } else {
        std::cout << "[FAIL] " << testName << std::endl;
    }
}

// -------------------------------------------------------------
// TESTS:
// -------------------------------------------------------------
void testWhitePawnMoves() {
    std::cout << "\n--- Testing White Pawn ---" << std::endl;
    Board board;
    
    board.setupBoard("8/8/8/8/8/8/4P3/8 w - - 0 1");
    Piece* pawn = board.getPieceAt(4,6);

    // Test 1
    runTest(pawn->isValidMove(4, 6, 4, 5, true, &board), "Single Step Forward");

    // Test 2
    runTest(pawn->isValidMove(4, 6, 4, 4, true, &board), "Double Step Forward");

    // Test 3 (Invalid)
    runTest(pawn->isValidMove(4, 6, 5, 6, true, &board) == false, "Invalid Sideways Move");
}

void testPawnCaptures() {
    std::cout << "\n--- Testing White Pawn ---" << std::endl;
    Board board;
    
    board.setupBoard("8/8/8/8/8/8/4P3/8 w - - 0 1");
    Piece* pawn = board.getPieceAt(4,6);

    // Test 1
    runTest(pawn->isValidMove(4, 6, 3, 5, true, &board), "Capture left");

    // Test 2
    runTest(pawn->isValidMove(4, 6, 5, 5, true, &board), "Capture right");

    // Test 3 (Invalid)
    runTest(pawn->isValidMove(4, 6, 4, 5, true, &board) == false, "try to move foreward into pawn");

    board.setupBoard("8/8/8/8/8/8/4P3/8 w - - 0 1");
    // Test 4 (Invalid)
    runTest(pawn->isValidMove(4, 6, 4, 4, true, &board) == false, "try to move move two squares over pawn");
}

// 3. Run them all in main
int main() {
    testWhitePawnMoves();
    testPawnCaptures();
    
    return 0;
}
