#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
using namespace std;

#define width 1280
#define height 720
#define  max_number_of_items  5

//Global Variable
bool un_mute = true;
//Functions
void Window1();
int Window2();
int Window3();
int Window4();
int Window5();
int Window6();

int Window6() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescue", sf::Style::Resize | sf::Style::Close);

	window.setFramerateLimit(180);
	int score = 0;

	sf::CircleShape projectile;
	projectile.setRadius(2.f);
	projectile.setFillColor(sf::Color::White);
	projectile.setPointCount(100);
	vector<sf::CircleShape>projectiles;
	projectiles.push_back(sf::CircleShape(projectile));
	int projectileSpwnTime = 0;

	//Text are loaded
	//Text loaded
	sf::Font font;
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString("Score : ");
	text.setPosition(sf::Vector2f(0.f, 20.f));
	text.setCharacterSize(27);

	sf::Font font_score;
	if (!font_score.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}

	sf::Text text_score;
	text_score.setFont(font);
	text_score.setFillColor(sf::Color::White);
	text_score.setString(to_string(score));
	text_score.setPosition(sf::Vector2f(60.f, 20.f));
	text_score.setCharacterSize(27);
	//text loaded is finished

	//Player health
	sf::RectangleShape border;
	border.setFillColor(sf::Color::White);
	border.setSize(sf::Vector2f(100.f, 8.f));
	border.setPosition(sf::Vector2f(0.f, 10.f));

	sf::RectangleShape health;
	health.setFillColor(sf::Color::Green);
	health.setPosition(sf::Vector2f(0.f, 10.f));
	health.setSize(sf::Vector2f(100.f, 8.f));

	//Play background is loaded here
	sf::Texture playBackground;
	if (!playBackground.loadFromFile("back2.png")) {
		std::cout << "this playbackground is not loaded" << std::endl;
	}

	sf::Sprite sprite_playBackground;
	sprite_playBackground.setTexture(playBackground);

	sf::Texture aircraft;
	if (!aircraft.loadFromFile("air2.png")) {
		std::cout << "The aircraft is not loaded" << std::endl;
	}

	sf::Sprite sprite_aircraft;
	sprite_aircraft.setTexture(aircraft);
	sprite_aircraft.setPosition(sf::Vector2f(600, 600));
	sf::Vector2f sprite_aircraft_center;

	sf::Texture bullet_picture;
	if (!bullet_picture.loadFromFile("bull2.png")) {
		std::cout << "This bullet is not loaded" << std::endl;
	}

	sf::Sprite sprite_bullet_picture;
	sprite_bullet_picture.setTexture(bullet_picture);
	vector<sf::Sprite>sprite_bullet_pictures;

	//Enemies Texture and Sprite is here
	sf::Texture enemy;
	if (!enemy.loadFromFile("enemy2.png")) {
		std::cout << "Enemy can not loaded" << std::endl;
	}
	sf::Sprite sprite_enemy;
	sprite_enemy.setTexture(enemy);
	sprite_enemy.setColor(sf::Color::Green);
	vector<sf::Sprite>sprite_enemies;
	//sprite_enemies.push_back(sprite_enemy);

	sf::Texture enemy_bullet;
	if (!enemy_bullet.loadFromFile("bullet7.png")) {
		std::cout << "Enemy's bullet can not loaded" << std::endl;
	}
	sf::Sprite sprite_enemy_bullet;
	sprite_enemy_bullet.setTexture(enemy_bullet);
	vector<sf::Sprite>sprite_enemy_bullets;
	//sprite_enemy_bullets.push_back(sprite_enemy_bullet);
	int enemySpwnTimer = 0;

	//Explosion Texture and Sprite
	sf::Texture explosion;
	if (!explosion.loadFromFile("explosion1.png")) {
		std::cout << "Explosion is not loaded" << std::endl;
	}
	sf::Sprite sprite_explosion;
	sprite_explosion.setTexture(explosion);
	vector<sf::Sprite>explosions;
	explosions.push_back(sf::Sprite(sprite_explosion));

	//sprite_bullet_pictures.push_back(sf::Sprite(sprite_bullet_picture));

	//Play background is loaded finish here

	// Bullet Vector is here
	vector<pair<double, double>>bullet;

	// Bullet Vector is clear

	//Sound file is loaded here
	sf::SoundBuffer aircraft_sound;
	if (!aircraft_sound.loadFromFile("upgrade.wav")) {
		std::cout << "aircraft_sound is not loaded" << std::endl;
	}
	sf::Sound sound_aircraft_sound;
	sound_aircraft_sound.setBuffer(aircraft_sound);
	sound_aircraft_sound.setVolume(30);


	sf::SoundBuffer explosionwav;
	if (!explosionwav.loadFromFile("explosion.wav")) {
		std::cout << "Explosion sound is not loaded" << std::endl;
	}

	sf::Sound sound_explosion;
	sound_explosion.setBuffer(explosionwav);
	//Sound file is loaded finished here

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { // Close Event
				window.close();
			}

			//if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) { //Bullet Push_Back Event
			//	std::cout << "Mouse button has been release just now" << std::endl;
			//	bullet.push_back(make_pair(sprite_aircraft.getPosition().x, sprite_aircraft.getPosition().y));
			//	if(un_mute)
			//	bullet_sound.play();
			//}

			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				std::cout << "Mouse button has beeb relased just now" << std::endl;
				sprite_aircraft_center = sf::Vector2f(sprite_aircraft.getPosition().x + 47.f+0.5, sprite_aircraft.getPosition().y-10.f);
				sprite_bullet_picture.setPosition(sf::Vector2f(sprite_aircraft_center));
				sprite_bullet_pictures.push_back(sf::Sprite(sprite_bullet_picture));
				if (un_mute)
					sound_aircraft_sound.play();
				//bullet_sound.setLoop(true);
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			std::cout << "A has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().x >= -38) {
				sprite_aircraft.move(sf::Vector2f(-4, 0));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			std::cout << "D has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().x <= 1210) {
				sprite_aircraft.move(sf::Vector2f(4, 0));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			std::cout << "W has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().y >= 0) {
				sprite_aircraft.move(sf::Vector2f(0, -4));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			std::cout << "S has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().y <= 605) {
				sprite_aircraft.move(sf::Vector2f(0, 4));
				//std::cout << sprite_aircraft.getPosition().y << std::endl;
			}
		}

		//Set projectile randowmly
		if (projectileSpwnTime < 10) {
			projectileSpwnTime++;
		}
		if (projectileSpwnTime >= 10) {
			projectileSpwnTime = 0;
			projectile.setPosition(sf::Vector2f(rand() % (int)window.getSize().x, 0.f));
			projectiles.push_back(sf::CircleShape(projectile));
		}

		//Update projectile
		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].move(sf::Vector2f(0.f, 2.f));
		}

		//Update sprite_bullet_pictures
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			sprite_bullet_pictures[i].move(sf::Vector2f(0.f, -4.f));
			if (sprite_bullet_pictures[i].getPosition().y <= -100.f)
				sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
		}

		//Update enemise
		if (enemySpwnTimer < 200) {
			enemySpwnTimer++;
		}
		if (enemySpwnTimer >= 200) {
			enemySpwnTimer = 0;
			int random = rand() % (int)window.getSize().x;
			//if ((float)random <= 50.f) random = 50.f;
			if ((float)random >= 1153.f) random = 1153.f;
			sprite_enemy.setPosition(sf::Vector2f(random % (int)window.getSize().x - 10.f, -10.f));
			sprite_enemies.push_back(sf::Sprite(sprite_enemy));
			sprite_enemy_bullet.setPosition(sf::Vector2f(sprite_enemy.getPosition().x + 40.f, sprite_enemy.getPosition().y + 190.f / 2.f));
			sprite_enemy_bullets.push_back(sf::Sprite(sprite_enemy_bullet));
		}
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			sprite_enemies[i].move(sf::Vector2f(0.f, 1 / 2.f));
		}

		//Update Sprite_enemy_bullets
		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			sprite_enemy_bullets[i].move(sf::Vector2f(0.f, 1.f));
		}

		//Colisio whith sprite_bullet_picture and airCraft_bullets
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			for (size_t k = 0; k < sprite_enemy_bullets.size(); k++) {
				if (sprite_bullet_pictures[i].getGlobalBounds().intersects(sprite_enemy_bullets[k].getGlobalBounds())) {
					sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
					sprite_enemy_bullets.erase(sprite_enemy_bullets.begin() + k);
					break;
				}
			}
		}

		//Colision with airCraft_bullets and sprite_enemy_bullets
		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			if (sprite_aircraft.getGlobalBounds().intersects(sprite_enemy_bullets[i].getGlobalBounds())) {
				sprite_enemy_bullets.erase(sprite_enemy_bullets.begin() + i);
				health.setSize(sf::Vector2f(health.getSize().x - 10.f, 8.f));
			}
		}
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			for (size_t k = 0; k < sprite_enemies.size(); k++) {
				if (sprite_bullet_pictures[i].getGlobalBounds().intersects(sprite_enemies[k].getGlobalBounds())) {
					sprite_enemies.erase(sprite_enemies.begin() + k);
					sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
					score++;
					text_score.setString(to_string(score));
					health.setSize(sf::Vector2f(health.getSize().x + 2.f, 8.f));
					if(un_mute)
					sound_explosion.play();
					break;
				}
			}
		}

		//Colision with airCraft and enemies
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			if (sprite_aircraft.getGlobalBounds().intersects(sprite_enemies[i].getGlobalBounds())) {
				sprite_enemies.erase(sprite_enemies.begin() + i);
				health.setSize(sf::Vector2f(health.getSize().x - 10.f, 8.f));
			}
		}
		// Return our Value and finish our level
		if (health.getSize().x <= 0) {
			return score;
			break;
		}

		window.draw(sprite_explosion);
		window.clear();
		window.draw(sprite_playBackground);
		window.draw(sprite_aircraft);

		/*if (!bullet.empty()) {
			for (int i = 0; i < bullet.size(); i++) {
				bullet[i].second -= 2;

				if (bullet[i].second < -10) {
					continue;
				}
				sprite_bullet_picture.setPosition(sf::Vector2f(bullet[i].first, bullet[i].second));

				sprite_bullet_picture.move(sf::Vector2f(0, -2));

				window.draw(sprite_bullet_picture);
			}
		}*/
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			window.draw(sprite_bullet_pictures[i]);
		}

		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			window.draw(sprite_enemy_bullets[i]);
		}
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			window.draw(sprite_enemies[i]);
		}
		window.draw(border);
		window.draw(health);
		window.draw(text);
		window.draw(text_score);

		/*for (size_t i = 0; i < projectiles.size(); i++) {
			window.draw(projectiles[i]);
		}*/


		window.display();
	}
}

int Window5() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescue", sf::Style::Resize | sf::Style::Close);
	int selectedIndexItem = 0;
	window.setFramerateLimit(100);

	sf::CircleShape projectile;
	projectile.setRadius(2.f);
	projectile.setFillColor(sf::Color::White);
	projectile.setPointCount(100);
	vector<sf::CircleShape>projectiles;
	projectiles.push_back(sf::CircleShape(projectile));
	int projectileSpwnTime = 0;

	sf::Texture died;
	if (!died.loadFromFile("levelup.png")) {
		std::cout << "Died and Score picture is not loaded" << std::endl;
	}
	sf::Sprite sprite_died;
	sprite_died.setTexture(died);

	sf::Font font;
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}
	sf::Text score;
	score.setFont(font);
	score.setString(to_string(0));
	score.setFillColor(sf::Color::White);
	score.setCharacterSize(25);
	score.setPosition(sf::Vector2f(603.f, 106.f));

	sf::Text menu[2];
	menu[0].setFont(font);
	menu[0].setString("Next Level");
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setCharacterSize(36);
	menu[0].setPosition(sf::Vector2f(1120, 610));
	menu[0].setStyle(sf::Text::Bold);

	menu[1].setFont(font);
	menu[1].setString("Menu");
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setCharacterSize(36);
	menu[1].setPosition(sf::Vector2f(1120, 660));
	menu[1].setStyle(sf::Text::Bold);

	sf::Music levelup;
	if (!levelup.openFromFile("levelup.wav")) {
		std::cout << "Game over sound is not loaded" << std::endl;
	}
	if (un_mute) {
		levelup.play();
		levelup.setLoop(true);
	}

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { // Close Event
				window.close();
			}

			if (event.type == sf::Event::KeyReleased) {
				std::cout << "Mouse ButtonReleased" << std::endl;
				if (event.key.code == sf::Keyboard::Down) {
					std::cout << "Down Button is pressed" << std::endl;

					if (selectedIndexItem + 1 < 2) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem++;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					std::cout << "Up button is preesed" << std::endl;

					if (selectedIndexItem - 1 >= 0) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem--;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}
				if (event.key.code == sf::Keyboard::Return) {
					if (selectedIndexItem == 0) {
						return 0;
					}
				}
			}

		}
		//Set projectile randowmly
		if (projectileSpwnTime < 10) {
			projectileSpwnTime++;
		}
		if (projectileSpwnTime >= 10) {
			projectileSpwnTime = 0;
			projectile.setPosition(sf::Vector2f(rand() % (int)window.getSize().x, 0.f));
			projectiles.push_back(sf::CircleShape(projectile));
		}

		//Update projectile
		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].move(sf::Vector2f(0.f, 2.f));
		}

		window.clear();
		window.draw(sprite_died);
		//window.draw(score);
		for (size_t i = 0; i < projectiles.size(); i++) {
			window.draw(projectiles[i]);
		}
		for (size_t i = 0; i < 2; i++) {
			window.draw(menu[i]);
		}
		window.display();
	}

}

int Window4(int score_player) {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescue", sf::Style::Resize | sf::Style::Close);
	int selectedIndexItem = 0;
	window.setFramerateLimit(100);

	sf::CircleShape projectile;
	projectile.setRadius(2.f);
	projectile.setFillColor(sf::Color::White);
	projectile.setPointCount(100);
	vector<sf::CircleShape>projectiles;
	projectiles.push_back(sf::CircleShape(projectile));
	int projectileSpwnTime = 0;

	sf::Texture died;
	if (!died.loadFromFile("die.png")) {
		std::cout << "Died and Score picture is not loaded" << std::endl;
	}
	sf::Sprite sprite_died;
	sprite_died.setTexture(died);

	sf::Font font;
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}
	sf::Text score;
	score.setFont(font);
	score.setString(to_string(score_player));
	score.setFillColor(sf::Color::White);
	score.setCharacterSize(25);
	score.setPosition(sf::Vector2f(603.f, 106.f));

	sf::Text menu[2];
	menu[0].setFont(font);
	menu[0].setString("Try again");
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setCharacterSize(36);
	menu[0].setPosition(sf::Vector2f(1120, 610));
	menu[0].setStyle(sf::Text::Bold);

	menu[1].setFont(font);
	menu[1].setString("Menu");
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setCharacterSize(36);
	menu[1].setPosition(sf::Vector2f(1120, 660));
	menu[1].setStyle(sf::Text::Bold);

	sf::Music game_over;
	if (!game_over.openFromFile("gameover.wav")) {
		std::cout << "Game over sound is not loaded" << std::endl;
	}
	if (un_mute) {
		game_over.play();
		game_over.setLoop(true);
	}


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) { // Close Event
				window.close();
			}

			if (event.type == sf::Event::KeyReleased) {
				std::cout << "Mouse ButtonReleased" << std::endl;
				if (event.key.code == sf::Keyboard::Down) {
					std::cout << "Down Button is pressed" << std::endl;

					if (selectedIndexItem + 1 < 2) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem++;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					std::cout << "Up button is preesed" << std::endl;

					if (selectedIndexItem - 1 >= 0) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem--;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}
				if (event.key.code == sf::Keyboard::Return) {
					std::cout << "Enter button pressed" << std::endl;

					if (selectedIndexItem == 0) {
						return 0;
					}
					if (selectedIndexItem) return 1;
				}
			}

		}
		//Set projectile randowmly
		if (projectileSpwnTime < 10) {
			projectileSpwnTime++;
		}
		if (projectileSpwnTime >= 10) {
			projectileSpwnTime = 0;
			projectile.setPosition(sf::Vector2f(rand() % (int)window.getSize().x, 0.f));
			projectiles.push_back(sf::CircleShape(projectile));
		}

		//Update projectile
		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].move(sf::Vector2f(0.f, 2.f));
		}

			window.clear();
			window.draw(sprite_died);
			window.draw(score);
			for (size_t i = 0; i < projectiles.size(); i++) {
				window.draw(projectiles[i]);
			}
			for (size_t i = 0; i < 2; i++) {
				window.draw(menu[i]);
			}
			window.display();
		}

	}

int Window3() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescue", sf::Style::Resize | sf::Style::Close);

	window.setFramerateLimit(150);
	int score = 0;

	//Text are loaded
	//Text loaded
	sf::Font font;
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString("Score : ");
	text.setPosition(sf::Vector2f(0.f, 20.f));
	text.setCharacterSize(27);

	sf::Font font_score;
	if (!font_score.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std::endl;
	}

	sf::Text text_score;
	text_score.setFont(font);
	text_score.setFillColor(sf::Color::White);
	text_score.setString(to_string(score));
	text_score.setPosition(sf::Vector2f(60.f, 20.f));
	text_score.setCharacterSize(27);
	//text loaded is finished

	//Player health
	sf::RectangleShape border;
	border.setFillColor(sf::Color::White);
	border.setSize(sf::Vector2f(100.f, 8.f));
	border.setPosition(sf::Vector2f(0.f, 10.f));

	sf::RectangleShape health;
	health.setFillColor(sf::Color::Green);
	health.setPosition(sf::Vector2f(0.f, 10.f));
	health.setSize(sf::Vector2f(100.f, 8.f));

	//Play background is loaded here
	sf::Texture playBackground;
	if (!playBackground.loadFromFile("gameplaybackground1.png")) {
		std::cout << "this playbackground is not loaded" << std::endl;
	}

	sf::Sprite sprite_playBackground;
	sprite_playBackground.setTexture(playBackground);

	sf::Texture aircraft;
	if (!aircraft.loadFromFile("aircraft6.png")) {
		std::cout << "The aircraft is not loaded" << std::endl;
	}

	sf::Sprite sprite_aircraft;
	sprite_aircraft.setTexture(aircraft);
	sprite_aircraft.setPosition(sf::Vector2f(600, 600));
	sf::Vector2f sprite_aircraft_center;

	sf::Texture bullet_picture;
	if (!bullet_picture.loadFromFile("bullet5.png")) {
		std::cout << "This bullet is not loaded" << std::endl;
	}

	sf::Sprite sprite_bullet_picture;
	sprite_bullet_picture.setTexture(bullet_picture);
	vector<sf::Sprite>sprite_bullet_pictures;

	//Enemies Texture and Sprite is here
	sf::Texture enemy;
	if (!enemy.loadFromFile("enemy.png")) {
		std::cout << "Enemy can not loaded" << std::endl;
	}
	sf::Sprite sprite_enemy;
	sprite_enemy.setTexture(enemy);
	sprite_enemy.setColor(sf::Color::Green);
	vector<sf::Sprite>sprite_enemies;
	//sprite_enemies.push_back(sprite_enemy);

	sf::Texture enemy_bullet;
	if (!enemy_bullet.loadFromFile("bullet7.png")) {
		std::cout << "Enemy's bullet can not loaded" << std::endl;
	}
	sf::Sprite sprite_enemy_bullet;
	sprite_enemy_bullet.setTexture(enemy_bullet);
	vector<sf::Sprite>sprite_enemy_bullets;
	//sprite_enemy_bullets.push_back(sprite_enemy_bullet);
	int enemySpwnTimer = 0;

	//Explosion Texture and Sprite
	sf::Texture explosion;
	if (!explosion.loadFromFile("explosion1.png")) {
		std::cout << "Explosion is not loaded" << std::endl;
	}
	sf::Sprite sprite_explosion;
	sprite_explosion.setTexture(explosion);
	vector<sf::Sprite>explosions;
	explosions.push_back(sf::Sprite(sprite_explosion));

	//sprite_bullet_pictures.push_back(sf::Sprite(sprite_bullet_picture));

	//Play background is loaded finish here

	// Bullet Vector is here
	vector<pair<double, double>>bullet;

	// Bullet Vector is clear

	//Sound file is loaded here
	sf::SoundBuffer aircraft_sound;
	if (!aircraft_sound.loadFromFile("upgrade.wav")) {
		std::cout << "aircraft_sound is not loaded" << std::endl;
	}
	sf::Sound sound_aircraft_sound;
	sound_aircraft_sound.setBuffer(aircraft_sound);
	sound_aircraft_sound.setVolume(30);

	sf::SoundBuffer explosionwav;
	if (!explosionwav.loadFromFile("explosion.wav")) {
		std::cout << "Explosion sound is not loaded" << std::endl;
	}

	sf::Sound sound_explosion;
	sound_explosion.setBuffer(explosionwav);
	//Sound file is loaded finished here

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			
			if(event.type==sf::Event::Closed){ // Close Event
				window.close();
			}

			//if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) { //Bullet Push_Back Event
			//	std::cout << "Mouse button has been release just now" << std::endl;
			//	bullet.push_back(make_pair(sprite_aircraft.getPosition().x, sprite_aircraft.getPosition().y));
			//	if(un_mute)
			//	bullet_sound.play();
			//}

			if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
				std::cout << "Mouse button has beeb relased just now" << std::endl;
				sprite_aircraft_center = sf::Vector2f(sprite_aircraft.getPosition().x+52.f, sprite_aircraft.getPosition().y-5.8);
				sprite_bullet_picture.setPosition(sf::Vector2f(sprite_aircraft_center));
				sprite_bullet_pictures.push_back(sf::Sprite(sprite_bullet_picture));
				if(un_mute)
					sound_aircraft_sound.play();
					//bullet_sound.setLoop(true);
			}
			
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			std::cout << "A has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().x >= -42) {
				sprite_aircraft.move(sf::Vector2f(-4, 0));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			std::cout << "D has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().x <= 1215) {
				sprite_aircraft.move(sf::Vector2f(4, 0));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			std::cout << "W has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().y >= 0) {
				sprite_aircraft.move(sf::Vector2f(0, -4));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			std::cout << "S has been pressed.." << std::endl;
			if (sprite_aircraft.getPosition().y <= 605) {
				sprite_aircraft.move(sf::Vector2f(0, 4));
				//std::cout << sprite_aircraft.getPosition().y << std::endl;
			}
		}

		//Update sprite_bullet_pictures
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			sprite_bullet_pictures[i].move(sf::Vector2f(0.f, -4.f));
			if (sprite_bullet_pictures[i].getPosition().y <=-100.f)
				sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
		}

		//Update enemise
		if (enemySpwnTimer <200) {
			enemySpwnTimer++;
		}
		if (enemySpwnTimer >= 200) {
			enemySpwnTimer = 0;
			int random = rand() %(int)window.getSize().x;
			//if ((float)random <= 50.f) random = 50.f;
			if ((float)random >= 1153.f) random = 1153.f;
			sprite_enemy.setPosition(sf::Vector2f(random % (int)window.getSize().x-10.f,-10.f));
			sprite_enemies.push_back(sf::Sprite(sprite_enemy));
			sprite_enemy_bullet.setPosition(sf::Vector2f(sprite_enemy.getPosition().x +38.f, sprite_enemy.getPosition().y + 190.f / 2.f));
			sprite_enemy_bullets.push_back(sf::Sprite(sprite_enemy_bullet));
		}
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			sprite_enemies[i].move(sf::Vector2f(0.f, 1/2.f));
		}

		//Update Sprite_enemy_bullets
		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			sprite_enemy_bullets[i].move(sf::Vector2f(0.f, 1.f));
		}

		//Colisio whith sprite_bullet_picture and airCraft_bullets
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			for (size_t k = 0; k < sprite_enemy_bullets.size(); k++) {
				if (sprite_bullet_pictures[i].getGlobalBounds().intersects(sprite_enemy_bullets[k].getGlobalBounds())) {
					sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
					sprite_enemy_bullets.erase(sprite_enemy_bullets.begin() + k);
					break;
				}
			}
		}

		//Colision with airCraft_bullets and sprite_enemy_bullets
		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			if (sprite_aircraft.getGlobalBounds().intersects(sprite_enemy_bullets[i].getGlobalBounds())) {
				sprite_enemy_bullets.erase(sprite_enemy_bullets.begin() + i);
				health.setSize(sf::Vector2f(health.getSize().x - 10.f, 8.f));
			}
		}
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			for (size_t k = 0; k < sprite_enemies.size(); k++) {
				if (sprite_bullet_pictures[i].getGlobalBounds().intersects(sprite_enemies[k].getGlobalBounds())) {
					sprite_enemies.erase(sprite_enemies.begin() + k);
					sprite_bullet_pictures.erase(sprite_bullet_pictures.begin() + i);
					score++;
					text_score.setString(to_string(score));
					health.setSize(sf::Vector2f(health.getSize().x +2.f, 8.f));
					if (un_mute) sound_explosion.play();
					break;
				}
			}
		}
		
		//Colision with airCraft and enemies
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			if (sprite_aircraft.getGlobalBounds().intersects(sprite_enemies[i].getGlobalBounds())) {
				sprite_enemies.erase(sprite_enemies.begin() + i);
				health.setSize(sf::Vector2f(health.getSize().x - 10.f, 8.f));
			}
		}
		// Return our Value and finish our level
		if (health.getSize().x <= 0) {
			return score;
			break;
		}

		window.draw(sprite_explosion);
		window.clear();
		window.draw(sprite_playBackground);
		window.draw(sprite_aircraft);
        
		/*if (!bullet.empty()) {
			for (int i = 0; i < bullet.size(); i++) {
				bullet[i].second -= 2;

				if (bullet[i].second < -10) {
					continue;
				}
				sprite_bullet_picture.setPosition(sf::Vector2f(bullet[i].first, bullet[i].second));

				sprite_bullet_picture.move(sf::Vector2f(0, -2));
				
				window.draw(sprite_bullet_picture);
			}
		}*/
		for (size_t i = 0; i < sprite_bullet_pictures.size(); i++) {
			window.draw(sprite_bullet_pictures[i]);
		}

		for (size_t i = 0; i < sprite_enemy_bullets.size(); i++) {
			window.draw(sprite_enemy_bullets[i]);
		}
		for (size_t i = 0; i < sprite_enemies.size(); i++) {
			window.draw(sprite_enemies[i]);
		}
		window.draw(border);
		window.draw(health);
		window.draw(text);
		window.draw(text_score);
		window.display();
	}
}
int Window2() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescue", sf::Style::Resize | sf::Style::Close);
	window.setFramerateLimit(100);

	sf::CircleShape projectile;
	projectile.setRadius(2.f);
	projectile.setFillColor(sf::Color::Magenta);
	projectile.setPointCount(100);
	vector<sf::CircleShape>projectiles;
	projectiles.push_back(sf::CircleShape(projectile));
	int projectileSpwnTime = 0;


	//All numerical varial is here
	int selectedIndexItem = 0;
	

	//All texture is loaded here
	sf::Texture ru;
	if (!ru.loadFromFile("ru.png")) {
		std::cout << "Rajshahi University  can not loaded" << std::endl;
	}


	//All texture is loaded finished here


	sf::Sprite spriteru;
	spriteru.setTexture(ru);

	//All sprite is setting finished here


	//All text is loaded here
	//Menu
	sf::Font font;
	
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "The arial.ttf font file can not loaded" << std:: endl; 
	}
	sf::Text menu[5];
	menu[0].setFont(font);
	menu[0].setString("Play");
	menu[0].setFillColor(sf::Color::Blue);
	menu[0].setCharacterSize(45);
	menu[0].setPosition(sf::Vector2f(95, 405));
	menu[0].setStyle(sf::Text::Bold);

	menu[1].setFont(font);
	menu[1].setString("Un Mute");
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setCharacterSize(45);
	menu[1].setPosition(sf::Vector2f(95, 469));
	menu[1].setStyle(sf::Text::Bold);

	menu[2].setFont(font);
	menu[2].setString("Mute");
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setCharacterSize(45);
	menu[2].setPosition(sf::Vector2f(95, 529));
	menu[2].setStyle(sf::Text::Bold);

	menu[3].setFont(font);
	menu[3].setString("Game Guide");
	menu[3].setFillColor(sf::Color::Black);
	menu[3].setCharacterSize(45);
	menu[3].setPosition(sf::Vector2f(95, 589));
	menu[3].setStyle(sf::Text::Bold);

	menu[4].setFont(font);
	menu[4].setString("Exit");
	menu[4].setFillColor(sf::Color::Black);
	menu[4].setCharacterSize(45);
	menu[4].setPosition(sf::Vector2f(95, 650));
	menu[4].setStyle(sf::Text::Bold);
	
	//All text is loaded finished here

	//All Sound is loaded here
	sf::Music music;
	if (!music.openFromFile("sound.wav")) {
		std::cout << "This game start sound is not loaded" << std::endl;
	}
	music.play();
	music.setVolume(20);
	music.setLoop(true);
	//All Sound is loadding finishe here


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyReleased) {
				std::cout << "key is released" << std::endl;

				if (event.key.code == sf::Keyboard::Down) {
					std::cout << "Down" << std::endl;

					if (selectedIndexItem + 1<5 ) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem++;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}

				if (event.key.code == sf::Keyboard::Up) {
					std::cout << "Down" << std::endl;

					if (selectedIndexItem - 1>=0) {
						menu[selectedIndexItem].setFillColor(sf::Color::Black);
						selectedIndexItem--;
						menu[selectedIndexItem].setFillColor(sf::Color::Blue);
					}
				}

				if (event.key.code == sf::Keyboard::Return) {
					
					if (selectedIndexItem == 0) {
						std::cout << "Play the game" << std::endl;
						//Third Window
						window.close();
						return 0;
						
					}

					else if (selectedIndexItem == 1) {
						std::cout << "Un Mute" << std::endl;
						if (un_mute == 0) {
							un_mute = 1;
							music.play();
						}

					}

					else if (selectedIndexItem == 2) {
						std::cout << "Mute" << std::endl;
						music.stop();
						un_mute = 0;
					}

					else if (selectedIndexItem == 3) {
						std::cout << "Game Guide" << std::endl;
					}

					else {
						std::cout << "Exit" << std::endl;
						exit(1);
					}
				}
			}

		}
		//Set projectile randowmly
		if (projectileSpwnTime < 10) {
			projectileSpwnTime++;
		}
		if (projectileSpwnTime >= 10) {
			projectileSpwnTime = 0;
			projectile.setPosition(sf::Vector2f(rand() % (int)window.getSize().x, 0.f));
			projectiles.push_back(sf::CircleShape(projectile));
		}

		//Update projectile
		for (size_t i = 0; i < projectiles.size(); i++) {
			projectiles[i].move(sf::Vector2f(0.f, 2.f));
		}

		window.clear();
		window.draw(spriteru);

		for (int i = 0; i < 5; i++) window.draw(menu[i]);
		for (size_t i = 0; i < projectiles.size(); i++) {
			window.draw(projectiles[i]);
		}

		window.display();


	}
}

void Window1() {
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Battle Rescu", sf::Style::Resize | sf::Style::Close);


	//All texture is loaded here
	sf::Texture background2;
	if (!background2.loadFromFile("background2.png")) {
		std::cout << "background1 can not loaded" << std::endl;
	}


	//All texture is loaded finished here


	sf::Sprite spritebackground2;
	spritebackground2.setTexture(background2);

	//All sprite is setting finished here


	//All text is loaded here
	sf::Font font;
	if (!font.loadFromFile("agency.ttf")) {
		std::cout << "this font is not loaded" << std::endl;
	}
	sf::Text text[4];
	text[0].setFont(font);
	text[0].setString("Loadding");
	text[0].setCharacterSize(40);
	text[0].setFillColor(sf::Color::White);
	text[0].setPosition(sf::Vector2f(5, 665));
	text[0].setStyle(sf::Text::Bold);

	text[1].setFont(font);
	text[1].setString("Loadding.");
	text[1].setCharacterSize(40);
	text[1].setFillColor(sf::Color::White);
	text[1].setPosition(sf::Vector2f(5, 665));
	text[1].setStyle(sf::Text::Bold);

	text[2].setFont(font);
	text[2].setString("Loadding..");
	text[2].setCharacterSize(40);
	text[2].setFillColor(sf::Color::White);
	text[2].setPosition(sf::Vector2f(5, 665));
	text[2].setStyle(sf::Text::Bold);

	text[3].setFont(font);
	text[3].setString("Loadding...");
	text[3].setCharacterSize(40);
	text[3].setFillColor(sf::Color::White);
	text[3].setPosition(sf::Vector2f(5, 665));
	text[3].setStyle(sf::Text::Bold);
	//All text is loaded finished here

	sf::Clock clock;

	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				//window.close();
				exit(1);
				break;
			}
			break;
		}

		if (event.type == sf::Event::KeyPressed)
			window.close();

		sf::Time time = clock.getElapsedTime();
		int i = time.asSeconds();

		window.clear();

		window.draw(spritebackground2);
		window.draw(text[i%4]);
		if (i == 16) {
			break;
		}

		window.display();
	}
}
int main()
{
	Window1();
	while (1) {
		int w = Window2();
		if (w == 0) {
			while (1) {
				int score = Window3();
				if (score >= 30) {
					break;
				}
				else {
					int w1 = Window4(score);
					if (w1 == 0) continue;
				}
			}
		}
		int w2 = Window5();
		if (w2 == 0) {
			int score1 = Window6();
			int w3 = Window4(score1);
			if (w3 == 1)
				Window2();
		}
	}
	return 0;
}