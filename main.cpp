#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <boost/date_time.hpp>
#include <boost/foreach.hpp>

#include <iostream>
#include <vector>

int main() {
	boost::posix_time::ptime current_date = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration current_time = current_date.time_of_day();

	std::vector <boost::posix_time::time_duration> break_times;
	break_times.push_back(boost::posix_time::time_duration(7,45,0));
	break_times.push_back(boost::posix_time::time_duration(8,30,0));
	break_times.push_back(boost::posix_time::time_duration(8,35,0));
	break_times.push_back(boost::posix_time::time_duration(9,20,0));
	break_times.push_back(boost::posix_time::time_duration(9,35,0));
	break_times.push_back(boost::posix_time::time_duration(10,20,0));
	break_times.push_back(boost::posix_time::time_duration(10,25,0));
	break_times.push_back(boost::posix_time::time_duration(11,10,0));
	break_times.push_back(boost::posix_time::time_duration(11,25,0));
	break_times.push_back(boost::posix_time::time_duration(12,10,0));
	break_times.push_back(boost::posix_time::time_duration(12,15,0));
	break_times.push_back(boost::posix_time::time_duration(13,00,0));
	break_times.push_back(boost::posix_time::time_duration(13,20,0));
	break_times.push_back(boost::posix_time::time_duration(14,05,0));
	break_times.push_back(boost::posix_time::time_duration(14,10,0));
	break_times.push_back(boost::posix_time::time_duration(14,55,0));

	float time_since_last_play = 100.f;

//	sf::RenderWindow RenderWin(sf::VideoMode::GetDesktopMode(), "MegaGong", sf::Style::Fullscreen);
	sf::RenderWindow RenderWin(sf::VideoMode::GetDesktopMode(), "MegaGong");

	sf::Font MonoFont;
	if(!MonoFont.LoadFromFile("DejaVuSansMono.ttf", 100)) {
		std::cerr << "Error while loading font, aborting..." << std::endl;
		return 1;
	}
	sf::String TimeText("time", MonoFont, 100);
	TimeText.SetCenter(TimeText.GetRect().GetWidth() / 2, TimeText.GetRect().GetHeight() / 2);
	TimeText.SetPosition(RenderWin.GetWidth() / 4, RenderWin.GetHeight() / 2);

	sf::SoundBuffer Ring;
	if(!Ring.LoadFromFile("train.wav")) {
		std::cerr << "Error while loading sound, aborting..." << std::endl;
		return 1;
	}
	sf::Sound RingSound(Ring);

	// Main loop.
	while(RenderWin.IsOpened()) {
		sf::Event Event;
		while(RenderWin.GetEvent(Event)) {
			if(Event.Type == sf::Event::Closed)
				RenderWin.Close();
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)
				RenderWin.Close();
		}

		time_since_last_play += RenderWin.GetFrameTime();

		current_time = boost::posix_time::microsec_clock::local_time().time_of_day();
		TimeText.SetText(boost::posix_time::to_simple_string(current_time));

		if(time_since_last_play <= 5.f) {
			TimeText.SetColor(sf::Color(255, time_since_last_play * 50, time_since_last_play * 50));
			RenderWin.Clear(sf::Color(sf::Randomizer::Random(0, 255), sf::Randomizer::Random(0, 255), sf::Randomizer::Random(0, 255)));
		}
		else {
			TimeText.SetColor(sf::Color(255, 255, 255));
			RenderWin.Clear();
		}

		BOOST_FOREACH(auto break_time, break_times) {
			if (break_time.hours() == current_time.hours() && break_time.minutes() == current_time.minutes() && time_since_last_play > 60.f) {
				RingSound.Play();
				std::cout << "GONG! at " << current_time << std::endl;
				TimeText.SetColor(sf::Color::Red);
				time_since_last_play = 0.f;
			}
		}
		
		RenderWin.Draw(TimeText);

		RenderWin.Display();
	}
}
