#include <iostream>
#include <algorithm>
#include <array>
#include <cctype>
#include <random>
#include <string_view>
#include <unordered_map>
using std::cout, std::cin, std::string;




// GLOBALS //
class custom_messsages {

public:

    inline static constexpr std::array<std::string_view, 4> input_messages = {
        "It's time for your choice! Rock, Paper, or Scissors?",
        "No time to waste! Rock, Paper, or Scissors?!",
        "This is not a waiting game, quick! Rock, Paper, or Scissors?",
        "Time to gamble! Rock, Paper, or Scissors?"

    };

    inline static constexpr std::array<std::string_view, 4> loser_messages = {
        "Stupid ass, follow the inputs! Try again.",
		"You can't even follow simple instructions? Try again.",
        "A toddler can figure it the third time. What are you, a fetus?",
        "Ragebait or low IQ? You call it."
    };

}
std::vector<string> game_elements = {"ROCK", "PAPER", "SCISSORS"};
std::unordered_map<string, string> win_conditions = { // Ex. You can only win as rock if opponent is scissors.
    {"ROCK", "SCISSORS"},
    {"PAPER", "ROCK"},
    {"SCISSORS", "PAPER"}
};

bool game_ongoing = true;
const int winningpoint_condition = 3; // Point system
int player_points = 0; 
int opponent_points = 0; 



string random_choice() {
    std::random_device rd;
    std::mt19937 generator(rd()); // This is how they generate a seed
    std::uniform_int_distribution<size_t> distribution(0, game_elements.size() - 1); // Distribution of range

    size_t random_index = distribution(generator); // Here's the random index.
    std::string choice = game_elements[random_index];

    return choice;
}

int game_loop() 
{
    // Optimize the random choice to be more broad for other RNGs.

    cout << "\nIt's time for your choice! Rock, Paper, or Scissors?\n"
         << "(INPUT: ROCK, PAPER, SCISSORS)\n";

    string user_input; cin >> user_input;
    std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper); // Convert to Uppercase

    if (!(std::find(game_elements.begin(), game_elements.end(), user_input) != game_elements.end())) {
        cout << "Stupid ass, follow the inputs! Try again.\n\n"; // (TODO: Funny idea, make this more unhinged with more errors.)
        return game_loop();
    }

    string robot_input = random_choice();

    // Here is the output of everything.
    cout << "You picked " << user_input << ". "
         << "Your opponent picked..." << robot_input << "!\n";
    
    // Check who won.
    if (user_input == robot_input) 
    {
        cout << "It's a tie! No points awarded! \n";
    }
    else if (win_conditions[user_input] == robot_input) // You win the match.
    { 
        cout << "You have won! One point awarded to the player. \n";
        player_points += 1;
    }
    else 
    {
        cout << "Opponent has won! One point awarded to opponent. \n";
        opponent_points += 1;
    }

    cout << "\n------- CURRENT SCORE -------"
         << "\nPLAYER SCORE: " << player_points
         << "\nOPPONENT SCORE: " << opponent_points << "\n";


    if (player_points == winningpoint_condition) {
        cout << "\nPlayer has reached three points. Player wins!";
        game_ongoing = false;
        return 0;
    }
    else if (opponent_points == winningpoint_condition) {
        cout << "\nOpponent has reached three points. Opponent wins!";
        game_ongoing = false;
        return 0;
    }

    return 0;
}

int main()
{
    cout << "------ ROCK, PAPER, SCISSORS! (Ver Prototype) ------\n"
         << "          By Darileo Rafael R. Esplana\n\n";

    while (game_ongoing) 
    {
        game_loop();
    }

    cout << "\nThank you for playing!";
}