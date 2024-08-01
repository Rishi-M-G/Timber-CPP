// include important libraries here
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Make code easier to type by using "using namespace"
using namespace sf;

// Function Declaration
void updateBranches(int seed); // Function Prototype

const int NUM_BRANCHES = 6;

Sprite branches[NUM_BRANCHES];

// Where is the player / Branch ?
// Left or Right

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES]; // we will have an array called branchPositions with six values in it. Each of these values is of the side type and can be either LEFT, RIGHT, or NONE.


// This is where our game starts from
int main()
{
	//Create a video mode object
	VideoMode vm(960, 540);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber !!!");
	View view(sf::FloatRect(0, 0, 1920, 1080));
	window.setView(view);

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

	// Time Bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;

	// Draw Some Text
	int score = 0;
	Text messageText;
	Text scoreText;

	// Choosing the font
	Font font;
	font.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\fonts\\KOMIKAP_.ttf");

	// Updating font of messages
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assigning Message Strings
	messageText.setString("Press Enter to Start the Game..!!");
	scoreText.setString("Score = 0");

	// Changing the size of strings
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Setting colour
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the Text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	// Preparing 6 Branches
	Texture textureBranch;
	textureBranch.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\branch.png");

	// Setting the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000,2000);

		// Set the sprite's origin to dead centre
		// We can then spin it round without changing its position
		branches[i].setOrigin(220, 20);
	}

	// Preparing the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	spritePlayer.setPosition(580, 720);

	// The player starts on the LEFT
	side playerSide = side::LEFT;

	// Preparing the gravestone
	Texture textureRIP;
	textureRIP.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(600, 860);

	// Preparing the Axe
	Texture textureAxe;
	textureAxe.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line the axe up with the tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Prepare the flying log
	Texture textureLog;
	textureLog.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\graphics\\log.png");
	Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Log Related Variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Control the player input
	bool acceptInput = false;

	// Prepare the sounds

	// The player chopping sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\Sound\\chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	// The death sound
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\Sound\\death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	// Out of Time Sound
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("C:\\Users\\Admin\\source\\repos\\Timber\\Sound\\out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);



	//Main Game Loop
	while (window.isOpen()) {
		/*
		* *****Handle the players input*****
		*/

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				//Listen for key presses again
				acceptInput = true;

				// hide the axe
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Starting the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;
			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Make all the branches disappear
			// Starting in the second position
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Making sure that gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			//Moving the player into position
			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}

		// Wrap the player controls to
		// Making sure accepting player input
		if (acceptInput)
		{
			// Handling the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				// Update the branches
				updateBranches(score);

				// Set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;
				acceptInput = false;

				// Play a chop sound
				chop.play();
			}

			// Handling the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;
				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				// Update the branches
				updateBranches(score);

				// Set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;
				acceptInput = false;

				// Play a chop sound
				chop.play();
			}
		}

		/*
		* *****Update the scene*****
		*/

		if (!paused)
		{
			// Measure Time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();

			// Size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				// Pause the Game
				paused = true;

				// Changing the message show to the player
				messageText.setString("Out of Time!!!");

				// Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play the out of time sound
				outOfTime.play();
			}

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

				if (spriteCloud1.getPosition().x > 1920)
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

				if (spriteCloud2.getPosition().x > 1920)
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

				if (spriteCloud3.getPosition().x > 1920)
				{
					// Set it up ready to be a whole new cloud next frame
					cloud3Active = false;
				}
			}

			// Update the score text
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			// Update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite ro the left side
					branches[i].setPosition(610, height);

					// Flip the sprite round the other way
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setRotation(0);
				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			// Handle the flying log
			if (logActive)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()), spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the log reached the right or left edge?
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new log next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// Handling Death of the Player
			if (branchPositions[5] == playerSide)
			{
				//death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				spriteRIP.setPosition(525, 760);

				// Hide the player
				spritePlayer.setPosition(2000, 660);

				// Change the text of the message
				messageText.setString("SQUISHED ! !");
				// Center the messageText on the screen
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play Death Sound
				death.play();
			}



		} // End If (!paused)

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

		// Draw the Branches

		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		// Draw the Tree
		window.draw(spriteTree);

		// Draw the Player
		window.draw(spritePlayer);

		// Draw the Axe
		window.draw(spriteAxe);

		// Draw the flying log
		window.draw(spriteLog);

		// Draw the gravestone
		window.draw(spriteRIP);

		// Draw the insect
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);

		// Draw Time Bar
		window.draw(timeBar);

		// Draw the message if paused
		if (paused)
		{
			window.draw(messageText);
		}

		//Show everything we just drew
		window.display();
	}
	return 0;
}

// Function Definition

void updateBranches(int seed)
{
	// Move All branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}
}

