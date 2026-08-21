#include <iostream>
#include <algorithm>
#include <array>
#include <cctype>
#include <random>
#include <string>
#include <string_view>
#include <unordered_map>
using std::cout, std::cin, std::string;


class custom_messages {
private:
	std::unordered_map<string, string> color_codes = {
		{"RED", "\033[31m"},
		{"GREEN", "\033[32m"},
		{"YELLOW", "\033[33m"},
		{"BLUE", "\033[34m"}
	};

public:

    string colorize_text(string text, string color_code) {
        return color_codes[color_code] + text + "\033[0m";
    }

    std::vector<string> input_messages = {
        colorize_text("It's time for your choice! Rock, Paper, or Scissors?", "BLUE"),
        colorize_text("No time to waste! Rock, Paper, or Scissors?!", "BLUE"),
        colorize_text("This is not a waiting game, quick! Rock, Paper, or Scissors?", "BLUE"),
        colorize_text("Time to gamble! Rock, Paper, or Scissors?", "BLUE")
    };

    std::vector<string> loser_messages = {
        colorize_text("Stupid ass, follow the inputs! Try again.", "RED"),
        colorize_text("You can't even follow simple instructions? Try again.", "RED"),
        colorize_text("A toddler can figure it the third time. What are you, a fetus?", "RED"),
        colorize_text("Ragebait or low IQ? You call it.", "RED")
    };

};

custom_messages CUSTM_MSG;

std::vector<string> game_elements = {"ROCK", "PAPER", "SCISSORS"};
std::unordered_map<string, string> win_conditions = { // Ex. You can only win as rock if opponent is scissors.
    {"ROCK", "SCISSORS"},
    {"PAPER", "ROCK"},
    {"SCISSORS", "PAPER"}
};





static size_t random_choice(int arr_size) {
	static std::mt19937 generator(std::random_device{}()); // Random number generator. It's magic.
    std::uniform_int_distribution<size_t> distribution(0, arr_size - 1); // Distribution of range

    size_t random_index = distribution(generator); // Here's the random index.

    return random_index;
}


class Game {
private:
    string player_name;
    bool game_ongoing = true;
	int round_number = 0;
    int player_points = 0;
    int opponent_points = 0;
    static const int winningpoint_condition = 3;

public:
    void main_game()
    {
        round_number += 1;

		cout << "\n\n\n\n" << "------ " << CUSTM_MSG.colorize_text("ROUND " + std::to_string(round_number), "YELLOW") << " ------"
             << "\n" << CUSTM_MSG.input_messages[random_choice(CUSTM_MSG.input_messages.size())] << "\n"
             << "(INPUT: ROCK, PAPER, SCISSORS)\n";

        string user_input;

        while (true) {     
            std::getline(cin, user_input);
            std::transform(user_input.begin(), user_input.end(), user_input.begin(), ::toupper); // Convert to Uppercase

            auto it = std::find(game_elements.begin(), game_elements.end(), user_input);
            if (it != game_elements.end()) {
                break; // Means the input is valid.
            }

            cout << CUSTM_MSG.loser_messages[random_choice(CUSTM_MSG.loser_messages.size())] << "\n\n"; // An insulting message.
        }
        
        string robot_input = game_elements[random_choice(game_elements.size())];

        // Here is the output of everything.
        cout << "You picked " << user_input << ". "
            << "Your opponent picked..." << robot_input << "!\n";

        // Check who won.
        if (user_input == robot_input)
        {
            cout << CUSTM_MSG.colorize_text("It's a tie! No points awarded!", "YELLOW") << "\n";
        }
        else if (win_conditions[user_input] == robot_input) // You win the match.
        {
            cout << CUSTM_MSG.colorize_text("You have won! One point awarded to the player, " + player_name + "!", "GREEN") << "\n";
            player_points += 1;
        }
        else
        {
            cout << CUSTM_MSG.colorize_text("Opponent has won! One point awarded to opponent.", "RED") << "\n";
            opponent_points += 1;
        }

        cout << "------ " << CUSTM_MSG.colorize_text("CURRENT SCORE", "YELLOW") << " ------"
            << "\nPLAYER SCORE: " << player_points
            << "\nOPPONENT SCORE: " << opponent_points << "\n";


        if (player_points == winningpoint_condition) {
            cout << "\n" << CUSTM_MSG.colorize_text("Player has reached three points.You win, " + player_name + "!", "GREEN") << "\n";
            game_ongoing = false;
        }
        else if (opponent_points == winningpoint_condition) {
            cout << "\n" << CUSTM_MSG.colorize_text("Opponent has reached three points. Opponent wins!", "RED") << "\n";
            game_ongoing = false;
        }
    }

	void set_player_name(const string& name) {
		player_name = name;
	}

    void loop_game() {
		while (game_ongoing) {
			main_game();
		}
    }
};


int main()
{
    cout << CUSTM_MSG.colorize_text("------ ROCK, PAPER, SCISSORS! (FINAL VERSION) ------", "BLUE") << "\n"
         << CUSTM_MSG.colorize_text("          By Darileo Rafael R. Esplana", "YELLOW") << "\n\n";

    // Player Name and Initialization
	Game game; string player_name;
	cout << "\nWhat is your name, player?\n";
    std::getline(cin, player_name);
	game.set_player_name(player_name);
    cout << "\nOkay, " << player_name
        << ", let's play!\n\n";

	game.loop_game();

    cout << "\nThank you for playing, "
         << player_name << "!"
         << "\n\n\n";
}