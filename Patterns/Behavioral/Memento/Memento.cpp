#include "Memento.h"

#include <vector>


namespace memento_pattern {

	class ProfileData {
	protected:
		int best_score = 0,
			money = 100,
			level = 0,
			experience = 0,
			games_played = 0;

	public:
		int get_money() { return money; }
		void modify_money(int val) { money += val; }
		void update_best_score(int val) { if(val > best_score) best_score = val; }
		void modify_experience(int exp) { experience = exp; games_played++; }

		std::shared_ptr<ProfileData> copy() {
			return std::make_shared<ProfileData>(*this);
		}
	};

	class GameProfile : public ProfileData {
	public:
		void print_stats() {
			std::cout << "\n" << "best_score = " << best_score << "\n"
						<< "money = "		<< money		<< "\n"
						<< "level = "		<< level		<< "\n"
						<< "games_played = "<< games_played << "\n"
						<< "expirience = "	<< experience << std::endl;
		}
		GameProfile() {}
		GameProfile(std::shared_ptr<ProfileData> data) : ProfileData(*data) { }
	};

	class GameManager {
	private:
		const int ROUND_PRICE = 10;

		std::shared_ptr<GameProfile> profile;
		std::vector<std::shared_ptr<ProfileData>> saves;
	public:
		GameManager() : profile(std::make_shared<GameProfile>()){
			save();
		}
		void save() {
			saves.push_back(profile->copy());
		}
		void reload() {
			if (!saves.empty()) profile = std::make_shared<GameProfile>(saves.back());
		}
		void undo() {
			if (saves.size() > 1) {
				saves.pop_back();
				reload();
			}
		}
		
		bool play() {

			if (profile->get_money() < ROUND_PRICE) {
				std::cout << "Sorry, you have no money to play(" << std::endl;
				return false;
			}
			else profile->modify_money(-ROUND_PRICE);

			int dice = rand() % 101;
			bool win = dice > 50;

			profile->update_best_score(dice);
			profile->modify_money(win ? (int)(ROUND_PRICE * 1.5f) : ROUND_PRICE / 2);
			profile->modify_experience(dice / 2);
			return win;
		}
		bool is_game_over() { return profile->get_money() < ROUND_PRICE; }
		void print_game_stats() { profile->print_stats(); }

	};
}


std::string MementoPattern::get_info() {
	return "Name: Memento Pattern.\nType: Behavioral.\nDescription: The Memento pattern allows capturing and storing an object's state so it can be restored to that state at a later time without violating encapsulation.";
}

int MementoPattern::run() {

	using namespace memento_pattern;

	std::srand(std::time(nullptr));

	//Simple player
	std::cout << "\n" << "Fair player: " << std::endl;
	{
		std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();
		int game_cnt = 0;
		while (game_cnt < 20) { 
			if (game_manager->is_game_over()) break;
			if (game_manager->play()) {
				game_manager->save();
			}
			game_cnt++;
		}
		game_manager->print_game_stats();

		game_manager->undo();
		game_manager->undo();

		game_cnt = 0;
		while (game_cnt < 20) {
			if (game_manager->is_game_over()) break;
			if (game_manager->play()) {
				game_manager->save();
			}
			game_cnt++;
		}
		game_manager->print_game_stats();
	}

	//Save scam player
	std::cout << "\n" << "Unfair player: ";
	{
		std::shared_ptr<GameManager> game_manager = std::make_shared<GameManager>();
		int game_cnt = 0;
		while (game_cnt < 40) {

			if (game_manager->play()) { game_manager->save(); game_cnt++; }
			else game_manager->reload();
		}

		game_manager->print_game_stats();
	}

	return 0;
}