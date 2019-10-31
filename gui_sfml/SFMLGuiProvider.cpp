#include "SFMLGuiProvider.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

extern "C" {
	IGuiProvider *GetProvider() {
		static SFMLGuiProvider lib;
		return &lib;
	}
}

bool SFMLGuiProvider::Init(IVec2 WindowSize, const char *WindowName) {
	Window.create(sf::VideoMode(WindowSize.x, WindowSize.y), WindowName);
	Window.setVerticalSyncEnabled(true);
	if (!Font.loadFromFile("resources/future.ttf"))
		return false;
    return true;
}


Image *SFMLGuiProvider::LoadImage(const char *ImagePath)
{
	sf::Texture *result = new sf::Texture();
	
	if (result->loadFromFile(ImagePath))
		return (Image *)result;
	delete result;
	return nullptr;
}
void SFMLGuiProvider::FreeImage(Image *Image) {
	sf::Texture *target = (sf::Texture*)Image;
	delete target;
}

bool SFMLGuiProvider::IsKeyDown(EKey K) {
	switch (K)
	{
	case EKey1:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
	case EKey2:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
	case EKey3:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
	case EKeySPACE:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
	case EKeyUP:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
	case EKeyDOWN:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	case EKeyLEFT:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
	case EKeyRIGHT:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
	case EKeyESC:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	default:
		break;
	}
    return false;
}
bool SFMLGuiProvider::ShouldExit() {
    return !Window.isOpen();
}
void SFMLGuiProvider::Tick() {
	sf::Event event;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			Window.close();
	}
}
void SFMLGuiProvider::FillBackground(Color C) {
	Window.clear(sf::Color(C.r, C.g, C.b, C.a));
}
void SFMLGuiProvider::DrawRectangle(FVec2 Origin, FVec2 Size, Color C) {
	sf::RectangleShape Rectangle(sf::Vector2f(Size.x, Size.y));
	Rectangle.setFillColor(sf::Color(C.r, C.g, C.b, C.a));
	Rectangle.move(sf::Vector2f(Origin.x, Origin.y));
	Window.draw(Rectangle);
}
void SFMLGuiProvider::DrawImage(FVec2 Origin, FVec2 Size, struct Image *I) {
	sf::Sprite sprite;
	sf::Texture *texture = (sf::Texture*)I;
	sf::Vector2u size = texture->getSize();
	sf::Vector2f scale(Size.x / size.x, Size.y / size.y);

	sprite.setTexture(*texture);
	sprite.setPosition(sf::Vector2f(Origin.x, Origin.y));
	sprite.setScale(scale);
	Window.draw(sprite);
}
void SFMLGuiProvider::DrawText(FVec2 Origin, const char* Text, Color C) {
}
void SFMLGuiProvider::EndFrame() {
	Window.display();
}
void SFMLGuiProvider::Deinit() {
	Window.close();
}
SFMLGuiProvider::~SFMLGuiProvider() {
}