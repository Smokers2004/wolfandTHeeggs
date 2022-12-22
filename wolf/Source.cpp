#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

class WolfPlayer {
public:
	Sprite sprite, arm;
	bool left = true, up = true;
	int army = 0, coordinates = 0;
	WolfPlayer(Texture& p, Texture& p2) {
		sprite.setTexture(p);
		arm.setTexture(p2);
		arm.setOrigin(54, 47);
	}
	void wolfupdate() {
		if (left) {
			sprite.setTextureRect(IntRect(0, 0, 134, 201));
			sprite.setPosition(350, 200);
			if (up) {
				arm.setRotation(0);
				army = 0;
			}
			else {
				arm.setRotation(-30);
				army = 50;
			}
			arm.setTextureRect(IntRect(0, 0, 108, 93));
			arm.setPosition(334, 247 + army);
		}
		else {
			sprite.setTextureRect(IntRect(134, 0, -134, 201));
			sprite.setPosition(510, 200);
			if (up) {
				arm.setRotation(0);
				army = 0;
			}
			else {
				arm.setRotation(30);
				army = 50;
			}
			arm.setTextureRect(IntRect(108, 0, -108, 93));
			arm.setPosition(664, 247 + army);
		}
		if (left && up)
			coordinates = 0;
		else if (left && !up)
			coordinates = 1;
		else if (!left && up)
			coordinates = 2;
		else if (!left && !up)
			coordinates = 3;
	}
};
bool isNextEgg = false;
class Egg {
public:
	Sprite spriteEgg[5];
	IntRect rect[5];
	bool showable[5];
	int tick = 1000, next = 0;
	void set(Texture& image, int& eggposition) {
		showable[0] = true;
		for (int i = 1; i < 5; i++)
			showable[i] = false;
		for (int i = 0; i < 5; i++) {
			switch(eggposition){
			case 1:
				rect[i].left = 201 + i * 25;
				rect[i].top = 171 + i * 13;
				break;
			case 2:
				rect[i].left = 191 + i * 25;
				rect[i].top = 261 + i * 13;
				break;
			case 3:
				rect[i].left = 811 - (10 + i * 25);
				rect[i].top = 175 + i * 13;
				break;
			case 4:
				rect[i].left = 811 - (10 + i * 25);
				rect[i].top = 265 + i * 13;
				break;
			}
		}
		for (int i = 0; i < 5; i++) {
			spriteEgg[i].setTexture(image);
			spriteEgg[i].setOrigin(11, 9);
			if (eggposition < 3)
				spriteEgg[i].setRotation(30 * i);
			else
				spriteEgg[i].setRotation(-30 * i);
			spriteEgg[i].setPosition(rect[i].left, rect[i].top);
		}
	}

	void update_egg_location() {
		tick--;
		if (tick == 0) {
			showable[next] = false;
			next++;
			if (next < 5)
				showable[next] = true;
			else
				isNextEgg = true;
			tick = 2000;
		}
	}
};
class Score {
public:
	Sprite sprite[3];
	int points;
	int s[3];
	Score(Texture& image) {
		for (int i = 0; i < 3; i++) {
			sprite[i].setTexture(image);
			sprite[i].setPosition(670 + 30 * i, 70);
			s[i] = 0;
		}
		points = 0;
	}

	void update() {
		s[2] = points % 10;
		s[1] = (points % 100) / 10;
		s[0] = points / 100;
		for (int i = 0; i < 3; i++)
			sprite[i].setTextureRect(IntRect(25 * s[i], 0, 25, 46));

	}

};
class Falling {
public:
	Sprite Fallingsprite;
	bool unhidden;
	int fallinganimation = 1, tick = 1000;
	void set(Texture& image) {
		Fallingsprite.setTexture(image);
		unhidden = false;
	}
	void update(bool right) {
		tick--;
		if (tick == 0) {
			fallinganimation++;
			tick = 1000;
		}
		switch (fallinganimation) {
		case 1:
			if (right) {
				Fallingsprite.setTextureRect(IntRect(0, 0, 52, 66));
				Fallingsprite.setPosition(650, 350);
			}
			else {
				Fallingsprite.setTextureRect(IntRect(52, 0, -52, 66));
				Fallingsprite.setPosition(300, 350);
			}
			break;

		case 2:
			if (right) {
				Fallingsprite.setTextureRect(IntRect(0, 0, 87, 66));
				Fallingsprite.setPosition(650, 350);
			}
			else {
				Fallingsprite.setTextureRect(IntRect(87, 0, -87, 66));
				Fallingsprite.setPosition(265, 350);
				break;

		case 3:
			if (right) {
				Fallingsprite.setTextureRect(IntRect(87, 0, 22, 66));
				Fallingsprite.setPosition(750, 350);
			}
			else {
				Fallingsprite.setTextureRect(IntRect(109, 0, -22, 66));
				Fallingsprite.setPosition(230, 350);
			}
			break;
		case 4:
			if (right) {
				Fallingsprite.setTextureRect(IntRect(109, 0, 22, 66));
				Fallingsprite.setPosition(780, 350);
			}
			else {
				Fallingsprite.setTextureRect(IntRect(131, 0, -22, 66));
				Fallingsprite.setPosition(195, 350);
			}
			break;
		case 5:
			if (right) {
				Fallingsprite.setTextureRect(IntRect(131, 0, 22, 66));
				Fallingsprite.setPosition(802, 350);
			}
			else {
				Fallingsprite.setTextureRect(IntRect(153, 0, -22, 66));
				Fallingsprite.setPosition(160, 350);
			}
			break;
			}
		};
	}
};
int main()
	{
		srand(time(0));
		RenderWindow window(VideoMode(1000, 500), "The wolf and the eggs");
		Texture bg;
		bg.loadFromFile("fon.png");
		Sprite background(bg);

		Texture pl, ar;
		pl.loadFromFile("player.png");
		ar.loadFromFile("arm.png");
		WolfPlayer wolf(pl, ar);

		Texture eg;
		eg.loadFromFile("egg.png");
		int pos[4];
		Egg egg[4];
		for (int i = 0; i < 4; i++) {
			pos[i] = i + 1;
			egg[i].set(eg, pos[i]);
		}

		int setRandline = rand() % 4;

		Texture s;
		s.loadFromFile("score.png");
		Score score(s);

		Texture up;
		up.loadFromFile("fal.png");
		Falling upast;
		upast.set(up);

		Texture lives;
		lives.loadFromFile("lose.png");

		Sprite lose[3];

		for (int i = 0; i < 3; i++) {
			lose[i].setTexture(lives);
			lose[i].setPosition(400 + 70 * i, 70);
		}

		int prop = 0;

		Texture loose;
		loose.loadFromFile("game_over_PNG22.png");
		Sprite gameover(loose);
		gameover.setPosition(400, 100);

		bool game = true, right = true, over = false;

		while (window.isOpen())

		{
			Vector2i pos = Mouse::getPosition(window);

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			if (pos.x < 500)
				wolf.left = true;
			else
				wolf.left = false;

			if (pos.y > 250)
				wolf.up = false;

			else
				wolf.up = true;

			if (isNextEgg) {
				if (setRandline == wolf.coordinates) {
					score.points++;
				}

				else {
					upast.unhidden = true;
					game = false;
					if (setRandline > 1)
						right = true;
					else
						right = false;
				}

				setRandline = rand() % 4;

				for (int i = 0; i < 4; i++)

					egg[i].next = 0;

				isNextEgg = false;

			}

			if (!game && upast.fallinganimation == 6 && !over) {
				prop++;
				if (prop < 3) {
					game = true;
					upast.fallinganimation = 1;
				}
				else {
					over = true;
				}
			}

			if (game) {
				wolf.wolfupdate();
				for (int i = 0; i < 4; i++)
					if (setRandline == i)
						egg[i].update_egg_location();
			}
			else
				upast.update(right);
			score.update();
			window.clear(Color::White);
			window.draw(background);
			window.draw(wolf.sprite);
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 4; j++)
					if (egg[j].showable[i] && setRandline == j)
						window.draw(egg[j].spriteEgg[i]);
			window.draw(wolf.arm);
			for (int i = 0; i < 3; i++)
				window.draw(score.sprite[i]);
			
			for (int i = 0; i < prop; i++)
				window.draw(lose[i]);

			if (upast.unhidden && !game)
				window.draw(upast.Fallingsprite);

			if (over)
				window.draw(gameover);

			window.display();

		}
		return 0;
};
