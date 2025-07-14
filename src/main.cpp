#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <climits>
#include <cstdlib>

extern "C" {
    #include "LigueQuant.h"
    #include "LigueQuant_ctx.h"
}

class LigQuantUI {
private:
    int32_t board_lines;
    int32_t board_cols;
    int32_t lig_quantity;
    LigueQuant_ctx__PLAYERS board[20][20]; // Max size based on constants
    
public:
    LigQuantUI() {
        // Initialize the game
        LigueQuant_ctx__INITIALISATION();
        LigueQuant__INITIALISATION();
        updateGameState();
    }
    
    void updateGameState() {
        LigueQuant__query_lin(&board_lines);
        LigueQuant__query_col(&board_cols);
        LigueQuant__query_lig_qnt(&lig_quantity);
        LigueQuant__query_board((LigueQuant_ctx__PLAYERS*)board, &board_cols, &board_lines);
    }
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            if (system("clear") != 0) {
                // Fallback if clear command fails
                std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            }
        #endif
    }
    
    void displayHeader() {
        std::cout << "╔══════════════════════════════════════╗\n";
        std::cout << "║            LIGUE QUANT GAME          ║\n";
        std::cout << "║       Connect " << lig_quantity << " Game (" << board_cols << "x" << board_lines << ")       ║\n";
        std::cout << "╚══════════════════════════════════════╝\n\n";
    }
    
    void displayBoard() {
        std::cout << "Current Board:\n";
        
        // Column numbers header
        std::cout << "  ";
        for (int c = 0; c < board_cols; c++) {
            std::cout << std::setw(3) << c;
            std::cout << " ";
        }
        std::cout << "\n";
        
        // Top border
        std::cout << "  ┌";
        for (int c = 0; c < board_cols; c++) {
            std::cout << "───";
            if (c < board_cols-1) std::cout << "┬";
        }
        std::cout << "┐\n";
        
        // Board rows (from top to bottom, but array is indexed bottom to top)
        for (int l = board_lines - 1; l >= 0; l--) {
            std::cout << std::setw(2) << (l) << "│";
            for (int c = 0; c < board_cols; c++) {
                char symbol;
                switch (board[c][l]) {
                    case LigueQuant_ctx__j1:
                        symbol = 'X';
                        break;
                    case LigueQuant_ctx__j2:
                        symbol = 'O';
                        break;
                    default:
                        symbol = ' ';
                        break;
                }
                std::cout << " " << symbol << " ";
                if (c < board_cols-1) std::cout << "│";
            }
            std::cout << "│\n";
            
            // Middle borders (except for last row)
            if (l > 0) {
                std::cout << "  ├";
                for (int c = 0; c < board_cols; c++) {
                    std::cout << "───";
                    if (c < board_cols-1) std::cout << "┼";
                }
                std::cout << "┤\n";
            }
        }
        
        // Bottom border
        std::cout << "  └";
        for (int c = 0; c < board_cols; c++) {
            std::cout << "───";
            if (c < board_cols-1) std::cout << "┴";
        }
        std::cout << "┘\n\n";
    }
    
    void displayGameStatus() {
        int32_t round;
        LigueQuant_ctx__PLAYERS current_player;
        bool game_ended;
        LigueQuant_ctx__PLAYERS winner;
        
        LigueQuant__query_round(&round);
        LigueQuant__query_player(&current_player);
        LigueQuant__query_game_end(&game_ended, &winner);
        
        std::cout << "Round: " << round << "\n";
        
        if (game_ended) {
            if (winner == LigueQuant_ctx__emp) {
                std::cout << "🎮 GAME ENDED - IT'S A DRAW! 🎮\n";
            } else {
                std::cout << "🎉 GAME ENDED - PLAYER " 
                         << (winner == LigueQuant_ctx__j1 ? "1 (X)" : "2 (O)") 
                         << " WINS! 🎉\n";
            }
        } else {
            std::cout << "Current Player: " 
                     << (current_player == LigueQuant_ctx__j1 ? "Player 1 (X)" : "Player 2 (O)") 
                     << "\n";
        }
        std::cout << "\n";
    }
    
    void displayMenu() {
        std::cout << "Available Actions:\n";
        std::cout << "1. Play a move (enter column number)\n";
        std::cout << "2. Undo last move\n";
        std::cout << "3. Undo multiple moves\n";
        std::cout << "4. Reset game\n";
        std::cout << "5. Change game rules\n";
        std::cout << "6. View game history\n";
        std::cout << "7. Quit game\n";
        std::cout << "\nChoice: ";
    }
    
    void playMove() {
        int32_t column;
        std::cout << "Enter column number (0-" + std::to_string(board_cols-1) + "): "; 
        std::cin >> column;
        std::cin.ignore();
        
        bool success;
        LigueQuant__play(column, &success);
        
        if (success) {
            // std::cout << "✓ Move played successfully!\n";
        } else {
            std::cout << "✗ Invalid move! Column might be full or game has ended.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        
    }
    
    void undoMove() {
        bool success;
        LigueQuant__undo_move(&success);
        
        if (success) {
            // std::cout << "✓ Last move undone successfully!\n";
        } else {
            std::cout << "✗ Cannot undo move! No moves to undo or game has ended.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        
    }
    
    void undoMultipleMoves() {
        int32_t num_moves;
        std::cout << "How many moves to undo? ";
        std::cin >> num_moves;
        std::cin.ignore();
        
        bool success;
        LigueQuant__undo_moves(num_moves, &success);
        
        if (success) {
            // std::cout << "✓ " << num_moves << " moves undone successfully!\n";
        } else {
            std::cout << "✗ Cannot undo " << num_moves << " moves! Not enough moves or game has ended.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
        
    }
    
    void resetGame() {
        LigueQuant__reset();
        // std::cout << "✓ Game reset successfully!\n";
        // std::cout << "Press Enter to continue...";
        // std::cin.get();
    }
    
    void changeGameRules() {
        std::cout << "Current game rules:\n";
        std::cout << "- Board size: " << board_cols << " x " << board_lines << "\n";
        std::cout << "- Connect: " << lig_quantity << "\n\n";
        
        int32_t new_lines; 
        std::cout <<"Enter new number of lines (" + std::to_string(LigueQuant_ctx__minn) + "-" + std::to_string(LigueQuant_ctx__maxx) + "):";
        std::cin >> new_lines;
        int32_t new_cols; 
        std::cout <<"Enter new number of columns (" + std::to_string(LigueQuant_ctx__minn) + "-" + std::to_string(LigueQuant_ctx__maxx) + "):";
        std::cin >> new_cols;
        int32_t new_connect; 
        std::cout <<"Enter new connect quantity (" + std::to_string(LigueQuant_ctx__ligue_quantos_min) + "-" + std::to_string(LigueQuant_ctx__ligue_quantos_max) + "):";
        std::cin >> new_connect;
        std::cin.ignore();
        
        bool success;
        LigueQuant__change_game_rules(new_lines, new_cols, new_connect, &success);
        
        if (success) {
            std::cout << "✓ Game rules changed successfully!\n";
            std::cout << "New game: " << new_cols << "x" << new_lines << ", Connect " << new_connect << "\n";
        } else {
            std::cout << "✗ Cannot change rules! Game might be in progress or invalid parameters.\n";
        }
        std::cout << "Press Enter to continue...";
        std::cin.get();
        
    }
    
    void viewGameHistory() {
        int32_t col_history[401]; // mm = 20*20 = 400
        int32_t lin_history[401];
        int32_t move_count;
        
        LigueQuant__query_history(col_history, lin_history, &move_count);
        
        std::cout << "Game History (" << move_count << " moves):\n";
        std::cout << "Move | Player | Column | Line\n";
        std::cout << "-----|--------|--------|------\n";
        
        for (int i = 1; i <= move_count; i++) {
            LigueQuant_ctx__PLAYERS player = (i % 2 == 1) ? LigueQuant_ctx__j1 : LigueQuant_ctx__j2;
            std::cout << std::setw(4) << i << " | "
                     << (player == LigueQuant_ctx__j1 ? "  X   " : "  O   ") << " | "
                     << std::setw(6) << col_history[i] << " | "
                     << std::setw(4) << lin_history[i] << "\n";
        }
        
        if (move_count == 0) {
            std::cout << "No moves played yet.\n";
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
    }
    
    void run() {
        while (true) {
            updateGameState();
            clearScreen();
            displayHeader();
            displayBoard();
            displayGameStatus();
            
            bool game_ended;
            LigueQuant_ctx__PLAYERS winner;
            LigueQuant__query_game_end(&game_ended, &winner);
            
            if (game_ended) {
                std::cout << "Game has ended! Choose an action:\n";
                std::cout << "1. Play a move (enter column number)\n";
                std::cout << "2. Undo last move\n";
                std::cout << "3. Undo multiple moves\n";
                std::cout << "4. Reset game\n";
                std::cout << "5. Change game rules\n";
                std::cout << "6. View game history\n";
                std::cout << "7. Quit game\n";
                std::cout << "\nChoice: ";
            } else {
                displayMenu();
            }
            
            int choice;
            std::cin >> choice;
            std::cin.ignore(); // Clear the newline
            
            switch (choice) {
                case 1:
                    playMove();
                    break;
                case 2:
                    undoMove();
                    break;
                case 3:
                    undoMultipleMoves();
                    break;
                case 4:
                    resetGame();
                    break;
                case 5:
                    changeGameRules();
                    break;
                case 6:
                    viewGameHistory();
                    break;
                case 7:
                    std::cout << "Thanks for playing LigueQuant! Goodbye!\n";
                    return;
                default:
                    std::cout << "Invalid choice! Please try again.\n";
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
            }
        }
    }
};

int main() {
    try {
        LigQuantUI game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}