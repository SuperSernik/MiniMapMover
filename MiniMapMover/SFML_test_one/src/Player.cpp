#include "Player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>
#include <iostream>
#include <conio.h>

#define LOG(x) std::cout<<x<<std::endl 
#define LOG_VECTOR(a, b) std::cout << a << "\t" << b << std::endl
#define LOG_V(a) std::cout << a.x << "\t" << a.y << std::endl



namespace game {
	Player::Player() {

		_position = sf::Vector2f(100.f, 100.f);


		if (!_texture.loadFromFile("assets\\ball.png"))
			LOG("Texture didnt load");

		//_texture.setSmooth(true);

		_sprite = sf::Sprite(_texture);
		

		// Set Values
		_sprite.setOrigin(sf::Vector2f(_texture.getSize().x / 2, _texture.getSize().y / 2));	//sets the origin
		_sprite.setPosition(sf::Vector2f(1600.f, 1600.f));										// absolute position
		_sprite.setRotation(0.f);																// absolute angle
		_sprite.setScale(sf::Vector2f(2.f, 2.f));												// absolute scale factor
		_sprite.setColor(sf::Color(255, 255, 255, 255));										// sets color RGBA
		//_sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));									// Source Rect from texture atlas
	}


	void Player::MovePlayer(sf::RenderWindow& window) {

		float vel = 1.5f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			_sprite.move(0, -vel);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			_sprite.move(0, vel);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			_sprite.move(-vel, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			_sprite.move(vel, 0);
		}




		//LOG_VECTOR(_sprite.getPosition().x, _sprite.getPosition().y);
		LOG_V(_sprite.getPosition());

	}

	void Player::ControlPlayerWithMouse(sf::RenderWindow& window) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			_sprite.setPosition(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			sf::Mouse::setPosition(sf::Vector2i(50, 50), window);
		}
	}

	void Player::TransformPlayer(sf::Color color, sf::Vector2f posOfset, float rotationOfset, sf::Vector2f scale) {

		_sprite.setColor(color);			// RGBA
		_sprite.move(posOfset);				// offset relative to the current position
		_sprite.rotate(rotationOfset);		// offset relative to the current angle
		_sprite.scale(sf::Vector2f(scale));	// factor relative to the current scale
	}

	void Player::AlterColorOnFocus(sf::RenderWindow& window) {

		if (!window.hasFocus()) {
			_sprite.setColor(sf::Color::Red);
		}
		else {
			_sprite.setColor(sf::Color::White);
		}

	}
}







