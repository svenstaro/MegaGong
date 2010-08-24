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
	break_times.push_back(boost::posix_time::time_duration(11,15,0));
	break_times.push_back(boost::posix_time::time_duration(12,10,0));
	break_times.push_back(boost::posix_time::time_duration(13,00,0));
	break_times.push_back(boost::posix_time::time_duration(13,20,0));
	break_times.push_back(boost::posix_time::time_duration(14,05,0));
	break_times.push_back(boost::posix_time::time_duration(14,10,0));
	break_times.push_back(boost::posix_time::time_duration(14,55,0));

	sf::RenderWindow RenderWin(sf::VideoMode(800, 600, 32), "MegaGong");

	sf::Font MonoFont;
	if(!MonoFont.LoadFromFile("DejaVuSansMono.ttf")) {
		std::cerr << "Error while loading font, aborting..." << std::endl;
		return 1;
	}

	sf::String TimeText("time", MonoFont, 50);

	// Main loop.
	while(RenderWin.IsOpened()) {
		sf::Event Event;
		while(RenderWin.GetEvent(Event)) {
			if(Event.Type == sf::Event::Closed)
				RenderWin.Close();
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape)
				RenderWin.Close();
		}


		RenderWin.Clear();

		current_time = boost::posix_time::microsec_clock::local_time().time_of_day();
		TimeText.SetText(boost::posix_time::to_simple_string(current_time));
		
		RenderWin.Draw(TimeText);

		RenderWin.Display();
	}

	std::cout << current_time << std::endl;
	BOOST_FOREACH(auto break_time, break_times) {
		if (break_time.hours() == current_time.hours() && break_time.minutes() == current_time.minutes())
			std::cout << "lol" << std::endl;
	}
}
