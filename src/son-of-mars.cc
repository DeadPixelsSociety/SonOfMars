/*
 * Copyright (c) 2015 OFNI
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "local/Character.h"
#include "local/SFMLDebugDraw.h"

int main(void) {
	sf::RenderWindow window({800, 600}, "Son of Mars");

	// Create the world physic
	b2World b2_world(b2Vec2(0.0f, 0.0f));

	// Debug Box2D
	SFMLDebugDraw debugDraw(window);
	b2_world.SetDebugDraw(&debugDraw);
	debugDraw.SetFlags(b2Draw::e_shapeBit);

	sf::Clock clock;
	float dt = 0.0f;

	Character player(b2_world);

	while (window.isOpen()) {
	sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// update
		dt = clock.restart().asSeconds();
		b2_world.Step(dt, 8, 3);
		player.update(dt);

		// render
		window.clear(sf::Color::Black);
		player.render(window);
		b2_world.DrawDebugData();

		window.display();
	}

	return 0;
}
