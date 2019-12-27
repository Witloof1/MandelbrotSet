#include <iostream>
#include <SFML/Graphics.hpp>

const int WIDTH = 700;
const int HEIGHT = 700;
sf::Uint8* pixels = nullptr;

const int nWidthJulia = 250;
const int nHeightJulia = 250;

float map(float value, float istart, float istop, float ostart, float ostop) 
{
	return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
}

void mandelbrot()
{
	for (int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
		{
			float a = map(x, 0, WIDTH, -2, 	2);
			float b = map(y, 0, HEIGHT, 2, -2);

			float ca = a; float cb = b;

			int n;
			for (n = 0; n < 32; n++)
			{
				float ta = a*a - b*b + ca;
				b = 2*a*b + cb;
				a = ta;

				if (a*a + b*b > 4)
					break;
			}
			
			sf::Uint8 color = n*8;

			pixels[(y * WIDTH + x) * 4 + 0] = color;
			pixels[(y * WIDTH + x) * 4 + 1] = 0;
			pixels[(y * WIDTH + x) * 4 + 2] = 0;
			pixels[(y * WIDTH + x) * 4 + 3] = 255;
		}
}

void julia(float aa, float bb)
{
	for (int x = 0; x < nWidthJulia; x++)
		for (int y = 0; y < nHeightJulia; y++)
		{
			float a = map(x, 0, nWidthJulia, -2,  2);
			float b = map(y, 0, nHeightJulia, 2, -2);

			int n;
			for (n = 0; n < 32; n++)
			{
				float ta = a*a - b*b + aa;
				b = 2*a*b + bb;
				a = ta;

				if (a*a + b*b > 4)
					break;
			}
		
			sf::Uint8 color = n*8;

			pixels[(y * WIDTH + x) * 4 + 0] = color;
			pixels[(y * WIDTH + x) * 4 + 1] = 0;
			pixels[(y * WIDTH + x) * 4 + 2] = 0;
			pixels[(y * WIDTH + x) * 4 + 3] = 255;
		}
}


int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "The Mandelbrot Set");
	window.setFramerateLimit(30);

	pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
	sf::Texture texture;
	texture.create(WIDTH, HEIGHT);
	sf::Sprite sprite(texture);

	mandelbrot();
	texture.update(pixels);

	sf::Vector2i mouse(0, 0);
	sf::Vector2i prevMouse(0, 0);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed: 
					window.close();
					break;
				default:
					break;
			}
		}

		mouse = sf::Mouse::getPosition(window);

		if (mouse.x != prevMouse.x || mouse.y != prevMouse.y)
		{
			float aa = map(mouse.x, 0, WIDTH, -2,  2);
			float bb = map(mouse.y, 0, HEIGHT, 2, -2);

			julia(aa, bb);
			texture.update(pixels);
			sprite.setTexture(texture);
		}

		prevMouse = mouse;

		window.clear();
		window.draw(sprite);
		window.display();
	}
}
