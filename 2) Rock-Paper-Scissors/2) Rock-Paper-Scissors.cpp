#include <iostream>
#include <algorithm>
#include <array>
#include <cctype>
#include <random>
#include <string>
#include <string_view>
#include <unordered_map>
using std::cout, std::cin, std::string;



// GLOBALS //
class custom_messages {

public:

    inline static constexpr std::array<std::string_view, 4> input_messages = {
        "\033[32mIt's time for your choice! Rock, Paper, or Scissors? \033[0m",
        "\033[32mNo time to waste! Rock, Paper, or Scissors?! \033[0m",
        "\033[32mThis is not a waiting game, quick! Rock, Paper, or Scissors? \033[0m",
        "\033[32mTime to gamble! Rock, Paper, or Scissors? \033[0m"

    };

    inline static constexpr std::array<std::string_view, 4> loser_messages = {
        "\033[31mStupid ass, follow the inputs! Try again. \033[0m",
        "\033[31mYou can't even follow simple instructions? Try again. \033[0m",
        "\033[31mA toddler can figure it the third time. What are you, a fetus? \033[0m",
        "\033[31mRagebait or low IQ? You call it. \033[0m"
    };

};

std::vector<string> game_elements = {"ROCK", "PAPER", "SCISSORS"};
std::unordered_map<string, string> win_conditions = { // Ex. You can only win as rock if opponent is scissors.
    {"ROCK", "SCISSORS"},
    {"PAPER", "ROCK"},
    {"SCISSORS", "PAPER"}
};

bool game_ongoing = true;
string player_name;

const int winningpoint_condition = 3; // Point system
int player_points = 0;
int opponent_points = 0; 





size_t random_choice(int arr_size) {
    std::random_device rd;
    std::mt19937 generator(rd()); // This is how they generate a seed
    std::uniform_int_distribution<size_t> distribution(0, game_elements.size() - 1); // Distribution of range

    size_t random_index = distribution(generator); // Here's the random index.

    return random_index;
}

int game_loop() 
{
	cout << "\n" << custom_messages::input_messages[random_choice(custom_messages::input_messages.size())] << "\n"
         << "(INPUT: ROCK, PAPER, SCISSORS)\n";

    string user_input; cin >> user_input;
    std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper); // Convert to Uppercase

    if (!(std::find(game_elements.begin(), game_elements.end(), user_input) != game_elements.end())) {
        cout << custom_messages::loser_messages[random_choice(custom_messages::loser_messages.size())] << "\n\n";
        return game_loop();
    }

    string robot_input = game_elements[random_choice(game_elements.size())];

    // Here is the output of everything.
    cout << "You picked " << user_input << ". "
         << "Your opponent picked..." << robot_input << "!\n";
    
    // Check who won.
    if (user_input == robot_input) 
    {
        cout << "\033[33mIt's a tie! No points awarded! \033[0m\n";
    }
    else if (win_conditions[user_input] == robot_input) // You win the match.
    { 
        cout << "\033[32mYou have won! One point awarded to the player, " + player_name + "! \033[0m\n";
        player_points += 1;
    }
    else 
    {
        cout << "\033[31mOpponent has won! One point awarded to opponent. \033[0m\n";
        opponent_points += 1;
    }

    cout << "\n------- CURRENT SCORE -------"
         << "\nPLAYER SCORE: " << player_points
         << "\nOPPONENT SCORE: " << opponent_points << "\n";


    if (player_points == winningpoint_condition) {
        cout << "\nPlayer has reached three points. You win, " + player_name + "!";
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

    // Initial Configurations
	cout << "\nWhat is your name, player?";
    std::getline(cin, player_name);
    cout << "\nOkay, " + player_name + ", let's play!";

    while (game_ongoing) 
    {
        game_loop();
    }

    cout << "\nThank you for playing, " + player_name + "!";
}