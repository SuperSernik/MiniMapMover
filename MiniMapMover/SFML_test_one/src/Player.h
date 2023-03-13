#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>

namespace game {

	class Player
	{

	private:
		sf::Texture _texture;
	public:
		sf::Sprite _sprite;
		sf::Vector2f _position;

	public:
		Player();
		void MovePlayer(sf::RenderWindow& window);
		void TransformPlayer(sf::Color color, sf::Vector2f posOfset, float rotationOfset, sf::Vector2f scale);
		void AlterColorOnFocus(sf::RenderWindow& window);
		void ControlPlayerWithMouse(sf::RenderWindow& window);
	};
}

