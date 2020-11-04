#include "tools.hpp"

void printScreen(sf::RenderWindow &window) {
	//print screen
	sf::Texture prtscr;

	prtscr.create(window.getSize().x, window.getSize().y);
	prtscr.update(window);
#ifdef _WIN32
	if(!prtscr.copyToImage().saveToFile(std::string(getenv("Temp")) + "\\kr_screenshot.png")) {
		ShowWindow(windowHandle, SW_MINIMIZE);
		MessageBox(NULL, "Failed to take a screenshot", "Warning", MB_DEFAULT_DESKTOP_ONLY | MB_ICONWARNING | MB_TOPMOST);
		return;
	}
	system("explorer %Temp%\\kr_screenshot.png");
#elif defined __linux__ || defined linux || defined __linux
	if(!prtscr.copyToImage().saveToFile("/tmp/kr_screenshot.png")) {
		usingSystem = system("zenity --warning --text=\"Failed to take a screenshot.\" --title=\"Warning!\"&");
		return;
	}
	system("thunar /tmp/kr_screenshot.png");
#else
#error Unknown OS
#endif // _WIN32
	return;
}

bool isMouseCoveringShape(sf::Shape &shape) {
	if(sf::Mouse::getPosition().x >= shape.getPosition().x &&
	        sf::Mouse::getPosition().x <= shape.getPosition().x + shape.getLocalBounds().width &&
	        sf::Mouse::getPosition().y >= shape.getPosition().y &&
	        sf::Mouse::getPosition().y <= shape.getPosition().y + shape.getLocalBounds().height) {
		return true;
	}
	else {
		return false;
	}
}

