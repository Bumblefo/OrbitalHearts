#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <SFML/Graphics.hpp>

#define ZOOM_FACTOR 0.5

class WindowManager
{
public:
	//Singleton
	//Destructor/Constructors
	~WindowManager();
	static WindowManager& instance();

	//Queries
	sf::RenderWindow& getWindow() { return _window; };
	sf::FloatRect getWindowBounds() const;

	//Commands
	void setWindowCenter(sf::Vector2f center);
	void setZoom(float zoomFactor = 1);

private:
	WindowManager();

	static WindowManager* _instance;
	sf::RenderWindow _window;
};

WindowManager* WindowManager::_instance = nullptr;



WindowManager::~WindowManager()
{
	delete _instance;
}

WindowManager::WindowManager()
	: _window{ sf::VideoMode(1280, 720), "Orbital Hearts", sf::Style::Default }
{
	_window.setKeyRepeatEnabled(false);

	setZoom(ZOOM_FACTOR);
}

WindowManager& WindowManager::instance()
{
	if (_instance == nullptr)
		_instance = new WindowManager();
	return *_instance;
}

sf::FloatRect WindowManager::getWindowBounds() const
{
	sf::View view = _window.getView();
	return sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
}

void WindowManager::setWindowCenter(sf::Vector2f center)
{
	sf::View view = sf::View(_window.getDefaultView());
	view.setCenter(center);
	_window.setView(view);
}

void WindowManager::setZoom(float zoomFactor)
{
	const sf::View& oldView = _window.getDefaultView();
	sf::View view = sf::View(oldView);
	view.setSize(view.getSize().x * zoomFactor, view.getSize().y * zoomFactor);
	_window.setView(view);
}

#endif //WINDOWMANAGER_HPP