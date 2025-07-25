#include<SFML/Graphics.hpp>
#include<sstream>
#include<SFML/Audio.hpp>
using namespace sf;
using namespace std;

enum class side{LEFT,RIGHT,NONE};//For constant Rotation
void updateBranches(int);
const int NUM_BRANCHES=6;
side branchPositions[NUM_BRANCHES];

int main(){
	
	//Style::Fullscreen
	VideoMode vm(1920,1080);
	RenderWindow window(vm,"Timber!!!",Style::Fullscreen); //Creates a window of videomode resolution
	
	//------------------------------------------------------------------------------------------------
	
	//
	Texture textureBackground;
	textureBackground.loadFromFile("graphics/background.png"); //Texture data converted to image data
	
	Sprite spriteBackground;//Sprite class helps in drawing the image or moving the image
	spriteBackground.setTexture(textureBackground);
	
	spriteBackground.setPosition(0,0);
	//------------------------------------------------------------------------------------------------
		
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png"); //Texture data converted to image data
	
	Sprite spriteTree;//Sprite class helps in drawing the image or moving the image
	spriteTree.setTexture(textureTree);
	
	spriteTree.setPosition(810,0);
	//-----------------------------------------------------------------------------------------------	
	
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png"); //Texture data converted to image data
	
	Sprite spriteCloud1;//Sprite class helps in drawing the image or moving the image  Sprite can hold one image
	spriteCloud1.setTexture(textureCloud);
	
	spriteCloud1.setPosition(0,100);
	//-----------------------------------------------------------------------------------------------
	
	
	Sprite spriteCloud2;//Sprite class helps in drawing the image or moving the image
	spriteCloud2.setTexture(textureCloud);
	
	spriteCloud2.setPosition(0,200);
	//-----------------------------------------------------------------------------------------------	
	
	Sprite spriteCloud3;//Sprite class helps in drawing the image or moving the image
	spriteCloud3.setTexture(textureCloud);
	
	spriteCloud3.setPosition(0,500);
	//----------------------------------------------------------------------------------------------------------------------------------------
		
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png"); //Texture data converted to image data
	
	Sprite spriteBee;//Sprite class helps in drawing the image or moving the image
	spriteBee.setTexture(textureBee);
	
	spriteBee.setPosition(0,800);	

	//-----------------------------------------------------------------------------------------------------------------------------------------
	
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png"); //Texture data converted to image data
	
	Sprite spriteBranches[NUM_BRANCHES];//Sprite class helps in drawing the image or moving the image,
	for(int i=0;i<NUM_BRANCHES;i++){
		spriteBranches[i].setTexture(textureBranch);
		spriteBranches[i].setPosition(2000,-2000);
		spriteBranches[i].setOrigin(220,20);
	}
	
	//---------------------------------------------------------------------------------------------------------------------------------
		

	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png"); //Texture data converted to image data
	
	Sprite spritePlayer;//Sprite class helps in drawing the image or moving the image
	spritePlayer.setTexture(texturePlayer);
	
	spritePlayer.setPosition(580,720);
	side playerSide=side::LEFT;
		
	//---------------------------------------------------------------------------------------------------------------------
	
	Texture textureRip;
	textureRip.loadFromFile("graphics/rip.png"); //Texture data converted to image data
	
	Sprite spriteRip;//Sprite class helps in drawing the image or moving the image
	spriteRip.setTexture(textureRip);
	
	spriteRip.setPosition(600,860);	
		
	//-------------------------------------------------------------------
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png"); //Texture data converted to image data
	
	Sprite spriteAxe;//Sprite class helps in drawing the image or moving the image
	spriteAxe.setTexture(textureAxe);
	
	spriteAxe.setPosition(700,830);	
	const float AXE_POSITION_LEFT=700;
	const float AXE_POSITION_RIGHT=1075;
	//-------------------------------------------------------------------------------------------------------------------------
	Texture textureLog;
	textureLog.loadFromFile("graphics/log.png"); //Texture data converted to image data
	
	Sprite spriteLog;//Sprite class helps in drawing the image or moving the image
	spriteLog.setTexture(textureLog);
	
	spriteLog.setPosition(810,720);
		
	bool logActive=false;
	float logSpeedx=1000;
	float logSpeedy=-1500;
	
	//Game Loop Declarations
	
	bool acceptInput=false;
	
	bool beeActive=false;
	float beeSpeed=0.0f;
	
	bool cloud1Active=false;
	float cloud1Speed=0.0f;

	bool cloud2Active=false;
	float cloud2Speed=0.0f;
	
	bool cloud3Active=false;
	float cloud3Speed=0.0f;

	bool paused=true;
	
	Clock clock;
	Font font;
	font.loadFromFile("font/KOMIKAP_.ttf");
	
	Text messageText;
	messageText.setFont(font);
	messageText.setString("Enter to Start");
	messageText.setCharacterSize(80);
	messageText.setFillColor(Color::White);
	
	messageText.setPosition(1920/2,1080/2);
	
	FloatRect rect = messageText.getLocalBounds();
	
	messageText.setOrigin(rect.left+rect.width/2.0f,rect.top+rect.height/2.0f);
	
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setString("Score :: 0");
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::White);
	
	scoreText.setPosition(20,20);
	//-------------------------------------------------------------------------------------------------------------------------
	
	RectangleShape timeBar;//creating a rectangle shape box named timeBar
	float timeBarStartWidth=400; //400
	float timeBarHeight=80;
	
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setPosition(1920/2.0-timeBarStartWidth/2.0,980);
	timeBar.setFillColor(Color::Red);
	float timeRemaining=6.0f;
	float timeBarStartWidthPerSec=timeBarStartWidth/timeRemaining;
	
	int score=0;
	
	// updateBranches(1);
	// updateBranches(2);
	// updateBranches(3);
	// updateBranches(4);
	// updateBranches(5);
//=========================================================================================================	
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	
	Sound death;
	death.setBuffer(deathBuffer);
//=========================================================================================================		

	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	
	Sound chop;
	chop.setBuffer(chopBuffer);	
	
//=========================================================================================================	
	SoundBuffer outOfTimeBuffer;
	outOfTimeBuffer.loadFromFile("sound/out_of_time.wav");
	
	Sound outOfTime;
	outOfTime.setBuffer(outOfTimeBuffer);	
	
//=========================================================================================================	


	
//Game Loop *******************************************************************************************************************************
	while(window.isOpen()){
		//score++;
		Event event;
		while(window.pollEvent(event)){
			if(event.type == Event::Closed)
			{
				window.close();
			}
		 	if(event.type==Event::KeyReleased && !paused){
		 		//Listen for key presses again
		 		acceptInput=true;
		 		spriteAxe.setPosition(2000,spriteAxe.getPosition().y);//hidden
		 	}
		}
		if(Keyboard::isKeyPressed(Keyboard::Return)){
			paused=false;
			score=0;
			timeRemaining=6.0f;
			for(int i=0;i<NUM_BRANCHES;i++)
			{
				branchPositions[i]=side::NONE;
			}
			spritePlayer.setPosition(580,720);
			spriteRip.setPosition(680,2000);
			acceptInput=true;
			}
			if(acceptInput){
				if(Keyboard::isKeyPressed(Keyboard::Right)){
					playerSide=side::RIGHT;
					score=score+1;
					timeRemaining=timeRemaining+0.15+2/score;
					spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
					spritePlayer.setPosition(1200,720);
					updateBranches(score);
					spriteLog.setPosition(810,720);
					logSpeedx=-5000;
					logActive=true;
					acceptInput=false;
					chop.play();
				}
			
				if(Keyboard::isKeyPressed(Keyboard::Left)){
					playerSide=side::LEFT;
					score=score+1;
					timeRemaining=timeRemaining+0.15+2/score;
					spriteAxe.setPosition(AXE_POSITION_LEFT,spriteAxe.getPosition().y);
					spritePlayer.setPosition(580,720);
					updateBranches(score);
					spriteLog.setPosition(810,720);
					logSpeedy=5000;
					logActive=true;
					acceptInput=false;
					chop.play();
				}
			}
		
	
		if(Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}		
		
		//-----------------------------------------------------------------------------------------------------------------------------------
		if(!paused){
			Time dt = clock.restart();//dt will give the elapsed time between frames
			timeRemaining=timeRemaining-dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarStartWidth*timeRemaining,timeBarHeight));
			if(timeRemaining<=0.0f){
				paused=true;
				messageText.setString("Out of Time");
				outOfTime.play();
				//close of time remaining
			}
			
		if(!beeActive){
			srand((int)time(0));
			beeSpeed=rand()%200+200;
			
			srand((int)time(0));
			float height=rand()%1350+500;
			
			spriteBee.setPosition(2000,height);
			beeActive=true;
		}
		else{
			spriteBee.setPosition(spriteBee.getPosition().x-beeSpeed*dt.asSeconds(),spriteBee.getPosition().y);
				if(spriteBee.getPosition().x<-100){
					beeActive=false;
				}
		}
		//----------------------------------------------------------------------------------------------------------
		if(!cloud1Active){
			srand((int)time(0)*10);
			cloud1Speed=rand()%150;
			
			srand((int)time(0));
			float height=rand()%150-20;
			
			spriteCloud1.setPosition(-300,height);
			
			cloud1Active=true;
			
		}
		else{			spriteCloud1.setPosition(spriteCloud1.getPosition().x+cloud1Speed*dt.asSeconds(),spriteCloud1.getPosition().y);
			if(spriteCloud1.getPosition().x>1920){
				cloud1Active=false;
			}
		}
		
		if(!cloud2Active){
			srand((int)time(0)*20);
			cloud2Speed=rand()%200;
			
			srand((int)time(0)*20);
			float height=rand()%300-150;
			
			spriteCloud2.setPosition(-300,height);
			cloud2Active=true;
		}
		else{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x+cloud2Speed*dt.asSeconds(),spriteCloud2.getPosition().y);
			if(spriteCloud2.getPosition().x>1920){
				cloud2Active=false;
			}
		}

		if(!cloud3Active){
			srand((int)time(0)*30);
			cloud3Speed=rand()%250;
			
			srand((int)time(0)*20);
			float height=rand()%500-150;
			
			spriteCloud3.setPosition(-300,height);
			cloud3Active=true;
		}
		else{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x+cloud3Speed*dt.asSeconds(),spriteCloud3.getPosition().y);
			if(spriteCloud3.getPosition().x>1920){
				cloud3Active=false;
			}
		}
		std::stringstream ss;
		ss<<"Score = "<<score;
		scoreText.setString(ss.str());
		
		//Update Branches
		for(int i=1;i<NUM_BRANCHES;i++)
		{
			float height=i*150;
			if(branchPositions[i]==side::LEFT){
				spriteBranches[i].setPosition(610,height);
				spriteBranches[i].setRotation(180);
			}
			else if(branchPositions[i]==side::RIGHT){
				spriteBranches[i].setPosition(1330,height);
				spriteBranches[i].setRotation(0);
			}
			else{
				spriteBranches[i].setPosition(3000,height);
			}
		}
		if(logActive){
			spriteLog.setPosition(spriteLog.getPosition().x+logSpeedx*dt.asSeconds(),spriteLog.getPosition().y+logSpeedy*dt.asSeconds());
			if(spriteLog.getPosition().x>2000 || spriteLog.getPosition().x<100){
				logActive=false;
				spriteLog.setPosition(800,600);
			}
		}//end of logactive if
		
		//Handle Player death
		if(branchPositions[5]==playerSide){
			paused=true;
			acceptInput=false;
			//Hide the player
			spritePlayer.setPosition(2000,720);
			//show rip
			spriteRip.setPosition(525,720);
			//display message text
			messageText.setString("SQUISHED!!!");
			
			messageText.setString("Enter to Start");
			messageText.setCharacterSize(80);
			messageText.setFillColor(Color::White);
	
			messageText.setPosition(1920/2,1080/2);
	
			FloatRect rect = messageText.getLocalBounds();
	
			messageText.setOrigin(rect.left+rect.width/2.0f,rect.top+rect.height/2.0f);
			
			//play sound
			death.play();
		}
		
		
		
		}//end of(!paused)		
		
		window.clear();
		window.draw(spriteBackground);
		window.draw(spriteTree);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);
		window.draw(spriteBee);
		for(int i=0;i<NUM_BRANCHES;i++){
			window.draw(spriteBranches[i]);
		}
		
		if(paused){
			window.draw(messageText);
		}
		window.draw(scoreText);
		window.draw(timeBar);
		window.draw(spriteAxe);
		window.draw(spritePlayer);
		window.draw(spriteRip);
		
		window.draw(spriteLog);
		
		
		window.display();
	}
	
	return 0;
}
void updateBranches(int seed){
	for(int j=NUM_BRANCHES-1;j>0;j--){
		branchPositions[j]=branchPositions[j-1];
		
	}
	srand((int)time(0)+seed);
	int r=rand()%5; //0:left,1:right,     3,4,5:none
	switch(r){
		case 0: branchPositions[0]=side::LEFT;
		break;
		case 1:branchPositions[0]=side::RIGHT;
		break;
		default:branchPositions[0]=side::NONE;
	}
}