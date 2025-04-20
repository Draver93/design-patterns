#include "Memento.h"

#include <vector>


namespace memento_pattern {

	class ProfileData {
	protected:
		int m_best_score = 0,
			m_money = 100,
			m_level = 0,
			m_experience = 0,
			m_games_played = 0;

	public:
		int get_money() { 
			return m_money; 
		}
		void modify_money(int money) { 
			m_money += money; 
		}
		void update_best_score(int best_score) { 
			if(best_score > m_best_score) 
				m_best_score = best_score; 
		}
		void modify_experience(int experience) { 
			m_experience = experience; 
			m_games_played++; 
		}

		std::shared_ptr<ProfileData> copy() {
			return std::make_shared<ProfileData>(*this);
		}
	};

	class GameProfile : public ProfileData {
	public:
		void print_stats() {
			std::cout << "\n" << "best_score = " << m_best_score << "\n"
						<< "money = "		<< m_money		<< "\n"
						<< "level = "		<< m_level		<< "\n"
						<< "games_played = "<< m_games_played << "\n"
						<< "expirience = "	<< m_experience << std::endl;
		}
		GameProfile() {}
		GameProfile(std::shared_ptr<ProfileData> data) : ProfileData(*data) { }
	};

	class GameManager {
	private:
		const int ROUND_PRICE = 10;

		std::shared_ptr<GameProfile> m_profile;
		std::vector<std::shared_ptr<ProfileData>> m_saves;
	public:
		GameManager() : m_profile(std::make_shared<GameProfile>()){
			save();
		}

		void save() {
			m_saves.push_back(m_profile->copy());
		}

		void reload() {
			if (!m_saves.empty()) m_profile = std::make_shared<GameProfile>(m_saves.back());
		}

		void undo() {
			if (m_saves.size() > 1) {
				m_saves.pop_back();
				reload();
			}
		}

		bool play() {

			if (m_profile->get_money() < ROUND_PRICE) {
				std::cout << "Sorry, you have no money to play(" << std::endl;
				return false;
			}
			else m_profile->modify_money(-ROUND_PRICE);

			int dice = rand() % 101;
			bool win = dice > 50;

			m_profile->update_best_score(dice);
			m_profile->modify_money(win ? (int)(ROUND_PRICE * 1.5f) : ROUND_PRICE / 2);
			m_profile->modify_experience(dice / 2);
			return win;
		}

		bool is_game_over() { 
			return m_profile->get_money() < ROUND_PRICE; 
		}

		void print_game_stats() { 
			m_profile->print_stats(); 
		}
	};
}


std::string MementoPattern::get_info() {
	return "Name: Memento Pattern.\nType: Behavioral.\nDescription: The Memento pattern allows capturing and storing an object's state so it can be restored to that state at a later time without violating encapsulation.";
}

int MementoPattern::run() {

	using namespace memento_pattern;

	std::srand((unsigned int)std::time(nullptr));

	//Simple player
	std::cout << "\n" << "Fair player: " << std::endl;
	{
		GameManager game_manager = GameManager();
		int game_cnt = 0;
		while (game_cnt < 20) { 
			if (game_manager.is_game_over()) break;
			if (game_manager.play())
				game_manager.save();

			game_cnt++;
		}
		game_manager.print_game_stats();

		game_manager.undo();
		game_manager.undo();

		game_cnt = 0;
		while (game_cnt < 20) {
			if (game_manager.is_game_over()) break;
			if (game_manager.play()) 
				game_manager.save();

			game_cnt++;
		}
		game_manager.print_game_stats();
	}

	//Save scam player
	std::cout << "\n" << "Unfair player: ";
	{
		GameManager game_manager = GameManager();
		int game_cnt = 0;
		while (game_cnt < 40) {
			if (game_manager.play()) { 
				game_manager.save();
				game_cnt++; 
			}
			else 
				game_manager.reload();
		}

		game_manager.print_game_stats();
	}

	return 0;
}