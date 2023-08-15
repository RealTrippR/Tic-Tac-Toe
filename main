#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>

using namespace std;
// define global variables
bool AIvAI = false;
bool playing_AI = false;
bool playing_as_X = true;
bool x_won = false;
bool o_won = false;
int x_wins = 0;
int o_wins = 0;
int win_row_or_column;
string win_type = "Null";
vector<char> board_vector = {' ' , ' ', ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' '};
vector<char> ai_possible_turns = {};
vector<char> ai_turns_to_win = {};

int min_element_index(vector<int> matrix) { // returns the index of the lowest value in a int vector

    int lowest = matrix[0];
    int index = 0;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i] < lowest) {
            lowest = matrix[i];
            index = 0;
        }
    }

    return lowest;
}

int max_element_index(vector<int> matrix) { // returns the index of the highest value in a int vector

    int highest = matrix[0];
    int index = 0;
    for (int i = 0; i < matrix.size(); i++) {
        if (matrix[i] > highest) {
            highest = matrix[i];
            index = i;
        }
    }

    return index;

}


void print_vector(vector<int> matrix) {//(for debugging only)
    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i];
    }
}


int str_pos_to_int(string pos) { // converts POS (I.E. A,1) to an int
    int row;
    int column;
    if (pos.length() != 3) {
        return 10;
    }
    if (pos[2] - 48 < 1 || pos[2] - 48 > 3) {
        return 10;
    }
    if (tolower(pos[0]) == 'a' && pos[2] > 0 && pos[2] > 0 < 4) {
        row = 0;
    } else if (tolower(pos[0]) == 'b' && pos[2] > 0 && pos[2] > 0 < 4) {
        row = 1;
    } else if (tolower(pos[0]) == 'c' && pos[2] > 0 && pos[2] > 0 < 4) {
        row = 2;
    } else {
        return 10;
    }

    column = int(pos[2]) - 48;
    return (row * 3) + column - 1;
}

//checks if a player has won (takes either 'x' or 'y' as inputs)
bool check_for_win(char player_win, char opposite_player, vector<char> matrix, int matches_needed) {
    // checks horizontal
    for (int i = 0; i < 3; i++) {
        int matches = 0;
        for (int j = 0; j < 3; j++) {
            if (matrix[i*3+j] == player_win) {
                matches++;
            }
            if (matrix[i*3+j] == opposite_player) {
                matches = -3;
            }
        }
        if (matches == matches_needed) {
            win_type = "Horizontal";
            win_row_or_column = i;
            return true;
        }
    }
    // checks vertical
    for (int i = 0; i < 3; i++) {
        int matches = 0;
        for (int j = 0; j < 3; j++) {
            if (matrix[j*3+i] == player_win) {
                matches++;
            }
            if (matrix[j*3+i] == opposite_player) {
                matches = -3;
            }
            if (matches == matches_needed) {
                win_type = "Vertical";
                win_row_or_column = i;
                return true;
            } 
        }
    }
    // checks diagonal, left to right, top to bottom
    int matches = 0;
    for (int i = 0; i < 3; i++) {
        if (matrix[i * 3 + i] == player_win) {
            matches++;
        }
        if (matrix[i * 3 + i] == opposite_player) {
            matches = -3;
        }
    }
    if (matches == matches_needed) {
        win_type = "Diagonal-1";
        return true;
    }
    // checks diagonal, right to left, bottom to top
    matches = 0;
    for (int i = 2; i > -1; i--) {
        if (matrix[i * 3 + (3 - i) - 1] == player_win) {
            matches++;
        }
        if (matrix[i * 3 + (3 - i) - 1] == opposite_player) {
            matches = -3;
        }
    }
    if (matches == matches_needed) {
        win_type = "Diagonal-2";
        return true;
    }
    // Default return so that function does not end up throwing a void error
    return false;
}


void render_board() {
    cout << "   | 1 | 2 | 3\n";
    cout << "---|---|---|---\n";
    for (int i = 0; i < 3; i++) {
        if (i == 0) {
            cout << " A | ";
        } else if (i == 1) {
            cout << " B | ";
        } else {
            cout << " C | ";
        }
        for (int j = 0; j < 3; j++) {
            cout << board_vector[i * 3 + j];
            if (j < 2) {
                cout << " | ";
            }
        }
        if (i < 2) {
            cout << "\n---|---|---|---\n";
        }
    }
}

int generate_AI_Turns(char A_char, char B_char) {
    //A = AI
    //B = opponent
    
    int total_filled_spaces = 0;
    for (int i = 0; i < 9; i++) {
        if (board_vector[i] != ' ') {
            total_filled_spaces++;
        }
    }

    if (total_filled_spaces == 1 && board_vector[4] == ' ' && A_char == 'O') { // for first turn of 'O' ONLY
        return 4;
    }
    if (total_filled_spaces == 0 && board_vector[2] == ' ' && A_char == 'X') { // for first turn of 'X' ONLY
        return 2;
    }

    vector<int> filled_spaces_per_row_B = {0,0,0}; // calculates filled spaces for each row for X only
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_vector[i * 3 + j] == B_char) {
                filled_spaces_per_row_B[i]++;
            }
        }
    }

    vector<int> filled_spaces_per_row_A = {0,0,0}; // calculates filled spaces for each row for O only
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_vector[i * 3 + j] == A_char) {
                filled_spaces_per_row_A[i]++;
            }
        }
    }

    vector<int> filled_spaces_per_column_B = {0,0,0}; // calculates filled spaces for each column for X only
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_vector[j * 3 + i] == B_char) {
                filled_spaces_per_column_B[i]++;
            }
        }
    }

    vector<int> filled_spaces_per_column_A = {0,0,0}; // calculates filled spaces for each column for O only
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_vector[j * 3 + i] == A_char) {
                filled_spaces_per_column_A[i]++;
            }
        }
    }

    int filled_spaces_diagonally_1_A = 0; // calculates filled spaces diagonally-1 for O only
    for (int i = 0; i < 3; i++) {
        if (board_vector[i * 3 + i] == A_char) {
            filled_spaces_diagonally_1_A++;
        }
    }

    int filled_spaces_diagonally_1_B = 0; // calculates filled spaces diagonally-1 for X only
    for (int i = 0; i < 3; i++) {
        if (board_vector[i * 3 + i] == B_char) {
            filled_spaces_diagonally_1_B++;
        }
    }

    int filled_spaces_diagonally_2_A = 0; // calculates filled spaces diagonally-2 for O only
    for (int i = 2; i > -1; i--) {
        if (board_vector[i * 3 + (3 - i) - 1] == A_char) {
            filled_spaces_diagonally_2_A++;
        }
    }

    int filled_spaces_diagonally_2_B = 0; // calculates filled spaces diagonally-2 for X only
    for (int i = 2; i > -1; i--) {
        if (board_vector[i * 3 + (3 - i) - 1] == B_char) {
            filled_spaces_diagonally_2_B++;
        }
    }

    int best_diagonal = 0;
    if (filled_spaces_diagonally_1_B == 0 && filled_spaces_diagonally_1_A >= filled_spaces_diagonally_2_A) {
        best_diagonal = 1;
    } else if (filled_spaces_diagonally_2_B == 0 && filled_spaces_diagonally_2_A >= filled_spaces_diagonally_1_A) {
        best_diagonal = 2;
    }

    int best_row = 0;
    for (int i = 0; i < 3; i++) {
        if (filled_spaces_per_row_B[i] == 0 && max_element_index(filled_spaces_per_row_A) == i) {
            best_row = i;
        }
    }

    int best_column = 0;
    for (int i = 0; i < 3; i++) {
        if (filled_spaces_per_column_B[i] == 0 && max_element_index(filled_spaces_per_column_A) == i) {
            best_column = i;
        }
    }
    string best = "Diagonal"; // calculate which row, column, or diagonal shot has more filled x's
    int best_filled_spaces;
    if (best_diagonal == 1) {
        best_filled_spaces = filled_spaces_diagonally_1_A;
    } else {
        best_filled_spaces = filled_spaces_diagonally_2_A;
    }
    if (filled_spaces_per_row_A[best_row] >= best_filled_spaces && filled_spaces_per_row_B[best_row] == 0) {
        best_filled_spaces = filled_spaces_per_row_A[best_row];
        best = "Row";
    } else if (filled_spaces_per_column_A[best_column] >= best_filled_spaces && filled_spaces_per_column_B[best_column] == 0) {
        best_filled_spaces = filled_spaces_per_column_A[best_column];
        best = "Column";
    }

    // calculates wether the AI could win by making a move to complete a three in a row rather than go on the defensive
    bool attack_over_defensive = false;
    if (filled_spaces_per_row_A[best_row] == 2 && filled_spaces_per_row_B[best_row] == 0) {
        attack_over_defensive = true;
        best = "Row";
    } else if (filled_spaces_per_column_A[best_column] == 2 && filled_spaces_per_column_B[best_column] == 0) {
         attack_over_defensive = true;
         cout << "2";
         best = "Column";
    } else if (best_diagonal == 1 && filled_spaces_diagonally_1_A == 2 && filled_spaces_diagonally_1_B == 0) {
         attack_over_defensive = true;
         best = "Diagonal";
    } else if (best_diagonal == 2 && filled_spaces_diagonally_2_A == 2 && filled_spaces_diagonally_2_B == 0) {
         attack_over_defensive = true;
         best = "Diagonal";
    }

    // checks for near win, if so (matches == 2) it should go on the defensive
    /*cout << "\n Data: " << A_char << " Best: " << best << " Check for win: "<< check_for_win(A_char, B_char, board_vector, 2) << " " << win_type << " Win row or column: " << win_row_or_column << " Attack over defensive: " << attack_over_defensive << " Filled spaces per column A: ";
    print_vector(filled_spaces_per_column_A);
    cout << " filled spaces diag-1" << " " << filled_spaces_diagonally_1_A;
    cout << "\n";
    */
    
    if (check_for_win(B_char, A_char, board_vector, 2) && !attack_over_defensive) { // defensive moves
        if (win_type == "Horizontal") {
            for (int i = 0; i < 3; i++) {
                if (board_vector[(win_row_or_column) * 3 + i] == ' ') {
                    // check for empty space in near win column, if so fill it with an 'O'
                    return win_row_or_column * 3 + i;
                    //break;
                }
            }
        } else if (win_type == "Vertical") {
            for (int i = 0; i < 3; i++) {
                if (board_vector[i * 3 + win_row_or_column] == ' ') {
                    // check for empty space in near win row, if so fill it with an 'O'
                    return i * 3 + win_row_or_column;
                    //break;
                }
            }
        } else if (win_type == "Diagonal-1") { // left to right, top to bottom
            for (int i = 0; i < 3; i++) {
                if (board_vector[i * 3 + i] == ' ') {
                    return i * 3 + i;
                }
            }
        } else if (win_type == "Diagonal-2") { // right to left, bottom to top
            for (int i = 2; i > -1; i--) {
                if (board_vector[i * 3 + (3 - i) - 1] == ' ') {
                    return i * 3 + (3 - i) - 1;
                }
            }
        } else {
            //cout << "Opponent does not have two in a row horizontally, vertically, as well as diagonally. \n ";
        }
    }

    if (best == "Diagonal") { // AI makes its turn by returning a position for the board
        if (best_diagonal == 1) {
            for (int i = 0; i < 3; i++) {
                if (board_vector[i * 3 + i] == ' ') {
                    return i * 3 + i;
                }
            }
        } else {
            for (int i = 2; i > -1; i--) {
                if (board_vector[i * 3 + (3 - i) - 1] == ' ') {
                    return i * 3 + (3 - i) - 1;
                }
            }
        }
    } else if (best == "Row") {
        for (int i = 0; i < 3; i++) {
            if (board_vector[best_row * 3 + i] == ' ') {
                return best_row * 3 + i;
            }
        }
    } else if (best == "Column") {
        for (int i = 0; i < 3; i++) {
            if (board_vector[i * 3 + best_column] == ' ') {
                return i * 3 + best_column;
            }
        }
    }

    //returns an empty position to prevent a non-void error just in case of draw or in a scenario where the AI just can't win
    for (int i = 0; i < 9; i++) {
        if (board_vector[i] == ' ') {
            return i;
        }
    }

    return 0;
}

void display_win_message() {
    if (x_won) {
        cout << "\n\nX has won the game!\n";
    } else {
        cout << "\n\nO has won the game!\n";
    }
    if (x_wins > 1) { 
        cout << "\nX has won " << x_wins << " time.\n\n";
    } else {
        cout << "\nX has won " << x_wins << " times.\n\n";
    }
    if (o_wins > 1) {
        cout << "\nX has won " << x_wins << " time.\n\n";
    } else {
        cout << "\nO has won " << o_wins << " times.\n\n";
    }
    x_won = false;
    o_won = false;
}
int main() {

    string answer;

    while (!(answer == "1" || answer == "2" || answer == "3")) {
        cout << "How would you like to play? \n1] Player v. Player\n2] Player v. AI\n3] AI v. AI\n\n";
        cin >> answer;
        if (answer == "1") {
            playing_AI = false;
        } else if (answer == "2") {
            playing_AI = true;
        } else if (answer == "3") {
            AIvAI = true;
            playing_AI = true;
        } else {
            cout << "Answer Invalid. Please choose a valid input [1 or 2].\n";
        }
    }

    cout << "\n";

    answer = "";

    bool x_turn = true;

    if (!AIvAI && playing_AI) {
        while (!(answer == "1" || answer == "2")) {
            cout << "Would you like P1 to play as X or as O?\n1] X \n2] O\n";
            cin >> answer;
            if (answer == "1") {
                playing_as_X = true;
            } else if (answer == "2") {
                playing_as_X = false;
            } else {
                cout << "Answer Invalid. Please choose a valid input [1 or 2].\n";
            }
        }
    }

    if (!AIvAI) {
        render_board();
    }
    
    int turns = 0;

    while (true) {

        turns++;

        if (x_turn) {

            int target_pos = 0;
            
            string str_pos;

            if (AIvAI || (!playing_as_X && playing_AI)) {
                target_pos = generate_AI_Turns('X','O');
                cout << "\n\nAI:\n";
            } else {
                cout << "\n\n(X'S TURN) ENTER POS: (I.E. A,1)\n";
                cin >> str_pos;
                target_pos = str_pos_to_int(str_pos);
            }
                        
            if (target_pos == 10 || board_vector[target_pos] == 'X' || board_vector[target_pos] == 'O') {
                cout << "\nINVALID FORMAT, SPACE IS TAKEN OR OUT OF BOUNDS.\n\nPlease enter a valid input.\n\n";
            } else {
                board_vector[target_pos] = 'X'; // 'X' or 'O'
                x_turn = false;
            }
        
        } else {
            
            int target_pos = 0;
            
            string str_pos;
            
            if (AIvAI || (playing_as_X && playing_AI)) {
                target_pos = generate_AI_Turns('O','X');
                cout << "\n\nAI:\n";
            } else {
                cout << "\n\n(O'S TURN) ENTER POS: (I.E. A,1)\n";
                cin >> str_pos;
                target_pos = str_pos_to_int(str_pos);
            }

            if (target_pos == 10 || board_vector[target_pos] == 'X' || board_vector[target_pos] == 'O') {
                cout << "\nINVALID FORMAT, SPACE IS TAKEN OR OUT OF BOUNDS.\n\nPlease enter a valid input.\n\n";
            } else {
                board_vector[target_pos] = 'O';
                x_turn = true;
            }
        }
        
        if (turns > 1) {
            printf("\033c"); // clears board
        }
        
        if (check_for_win('X', 'O', board_vector, 3)) {
            render_board();
            x_won = true;
            x_wins++;
            display_win_message();
            sleep(3);
            board_vector = {' ' , ' ', ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' '}; // reset board
            x_turn = true;
        }
        if (check_for_win('O', 'X', board_vector, 3)) {
            render_board();
            o_won = true;
            o_wins++;
            display_win_message();
            sleep(3);
            board_vector = {' ' , ' ', ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' '}; // reset board
            x_turn = true;
        }

        int filled_positions = 0;
        for (int i = 0; i < 9; i++) {
            if (board_vector[i] != ' ') {
                filled_positions++;
            }
        }

        if (filled_positions == 9 ) { // if board is filled reset board and start anew
            board_vector = {' ' , ' ', ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' '};

            cout << "\nDraw!\n\n";

            x_turn = true;
            x_won = false;
            o_won = false;


        }

        render_board();

        if (AIvAI) {
            sleep(1); // Slight delay between AI v. AI turns to give user time to read and observe
        }
        /*if (x_won) { // print x won or o won down here to avoid it being printed above the board, and so that the board is not wiped before
            cout << "\n\nX has won the game!";
        } else if (o;_won) {
            cout << "\n\nO has won the game!";
        }
        */
    }
}
