// include important libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type by using "using namespace"
using namespace sf;

// This is where our game starts from
int main()
{
	//Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber !!!", Style::Fullscreen);

	/*
	* Background
	*/

	//Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	//Load a graphic into the texture
	textureBackground.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\background.png");

	//Create a sprite
	Sprite spriteBackground;

	//Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	//Set the sprite Background to cover the screen
	spriteBackground.setPosition(0, 0);

	/*
	* Tree
	*/

	//Make a tree sprite
	Texture textureTree;

	//Load the tree graphic into the texture
	textureTree.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\tree.png");

	//Create a sprite for the tree
	Sprite spriteTree;

	//Attach the tree sprite to the tree texture
	spriteTree.setTexture(textureTree);

	//Set the position for the tree sprite
	spriteTree.setPosition(810, 0);

	/*
	* Bee
	*/

	// Prepare the Bee
	Texture textureBee;

	//Load Bee graphic into the texture
	textureBee.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\bee.png");

	//Create a Sprite for the Bee
	Sprite spriteBee;

	//Associate the sprite bee with bee texture
	spriteBee.setTexture(textureBee);

	//Set position for the sprite Bee
	spriteBee.setPosition(0, 800);

	// Is the Bee currently moving?
	bool beeActive = false; //True if bee is moving
	 
	// How fast can the bee fly
	float beeSpeed = 0.0f; //speed in pixels per second

	/*
	* Clouds
	*/

	// Making 3 clouds from one texture
	Texture textureCloud;

	// Load graphic to the texture
	textureCloud.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\cloud.png");

	// 3 New sprites for 3 new clouds from the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);

	//Position the clouds on the left of the screen at different heights
	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	//Are the clouds currenlty on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	//How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variable to control time itself
	Clock clock;
	//Main Game Loop
	while (window.isOpen()) {
		/*
		* *****Handle the players input*****
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		* *****Update the scene*****
		*/
		// Measure Time
		Time dt = clock.restart();
		
		// Set up the bee
		if (!beeActive)
		{
			// How fast is the bee
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			// How High is the bee
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		{
			// Move the Bee
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

			// Has the Bee Reached the left-hand edge of the screen?
			if (spriteBee.getPosition().x < -100)
			{
				// Set it up ready to be a whole new bee next frame
				beeActive = false;
			}
		}

		// Manage the Clouds
		// Cloud 1
		if (!cloud1Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}
		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?

			if (spriteCloud1.getPosition().x > 1920);
			{
				// Set it up ready to be a whole new cloud next frame
				cloud1Active = false;
			}
		}

		// Cloud 2
		if (!cloud2Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		}
		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?

			if (spriteCloud2.getPosition().x > 1920);
			{
				// Set it up ready to be a whole new cloud next frame
				cloud2Active = false;
			}
		}
		// Cloud 3
		if (!cloud3Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		}
		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?

			if (spriteCloud3.getPosition().x > 1920);
			{
				// Set it up ready to be a whole new cloud next frame
				cloud3Active = false;
			}
		}
		/*
		* *****Draw the scene*****
		*/
		//Clear everything from the last frame
		window.clear();

		//Draw our game scene here
		window.draw(spriteBackground);

		//Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the Tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

		//Show everything we just drew
		window.display();
	}
	return 0;
}
