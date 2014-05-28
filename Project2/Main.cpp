#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

#include "Player.h"
#include "GameAsset.h"
#include "Md2Asset.h"
#include "TriangularPyramidAsset.h"
#include "BallisticInterpolator.h"
#include "Camera.h"
#include "Cube.h"




using namespace std;

#define RUN_GRAPHICS_DISPLAY 0x00;


string blue = "shaders/blue.glsl";
float cubeX = -38;
float cubeY = 50;
float cubeZ = 30;




int tarX = -50;
int tarY = 10;
int tarZ = 30;
int Spec = 0;


vector<shared_ptr<GameAsset> > player;
vector<shared_ptr<GameAsset> > assets;
vector<shared_ptr<GameAsset> > walls;
vector<shared_ptr<GameAsset> > player1;


bool horrible_global_go = false;






SDL_Window * window = nullptr;

/*
 * SDL timers run in separate threads.  In the timer thread
 * push an event onto the event queue.  This event signifies
 * to call display() from the thread in which the OpenGL 
 * context was created.
 */
Uint32 display(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black backround - maze 
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  // This O(n + n^2 + n) sequence of loops is written for clarity,
  // not efficiency

  for(auto pl : player) {
    if(horrible_global_go) {pl->update();}
  }

  for (auto pl : player){
	  pl->update();
  }


  for (auto as : assets){
	  as->update();
  }

  



  for(auto pl : player) {
	  for(auto as : player) {
		  if((pl != as) && as->collidesWith(*pl)) {	
		  SDL_Quit();
		  cout << "Congratulation you WIN!" << endl;
		
      }
    }
  }

  

  for (auto p : player) {
	  for (auto as : assets) {
		  if ((p != as) && as->collidesWith(*p)) {
			  SDL_Quit();
			  cout << "GAME OVER" << endl;
		  }
	  }
  }



 

  for (auto pl : player){
	  pl->draw();
  }


  for (auto as : assets){
	  as->draw();
  }

  



  
  // Don't forget to swap the buffers
  SDL_GL_SwapWindow(window);
}






int main(int argc, char ** argv) {
	Uint32 width = 1024;
	Uint32 height = 800;
	Uint32 delay = 1000/60; // in milliseconds

	// Initialise SDL - when using C/C++ it's common to have to
	// initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
			cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
			SDL_Quit();
	}

	// When we close a window quit the SDL application
	atexit(SDL_Quit);

	// Create a new window with an OpenGL surface
	window = SDL_CreateWindow("CI224 - Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (nullptr == window) {
		cout << "Failed to create SDL window: " << SDL_GetError() << endl;
		SDL_Quit();
	}
	else 
	{
		cout << "Reach the princess to win the game  " << endl;
		cout << "Press R to change between camera and move mode  " << endl;
		cout << "Press Space for default camera mode " << endl;
		cout << "Press Esc to exit  " << endl;
	}
	
	

	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (nullptr == glContext) {
			cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
			SDL_Quit();

	}

	// Initialise GLEW - an easy way to ensure OpenGl 2.0+
	// The *must* be done after we have set the video mode - otherwise we have no OpenGL context.
	glewInit();
	if (!glewIsSupported("GL_VERSION_2_0")) {
	  cerr<< "OpenGL 2.0 not available" << endl;
	  return 1;
	}

	/*
	//Ballistic shoot - doesn't work. When SDL window is loaded this appears and leaves wihtout giving the user the chance to press 'G'
	shared_ptr<TriangularPyramidAsset> p = shared_ptr<TriangularPyramidAsset>(new TriangularPyramidAsset(0, 0, 0));
	shared_ptr<IInterpolator> i = shared_ptr<IInterpolator>(new BallisticInterpolator(Vector3(7.0, 7.0, 0), 60));
	p->setInterpolator(i);
	assets.push_back(p);
	*/




	//top border:

	assets.push_back(shared_ptr<Cube>(new Cube(-0, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-3, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-6, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-9, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-12, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-15, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-18, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-20, 40, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(-24, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-27, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-30, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-33, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-36, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-39, 40, 30, blue)));



	assets.push_back(shared_ptr<Cube>(new Cube(0, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(3, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(6, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(9, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(12, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(15, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(18, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(21, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(24, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(27, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(30, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(33, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(36, 40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(39, 40, 30, blue)));

	//

	//bottom border:

	assets.push_back(shared_ptr<Cube>(new Cube(-0, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-3, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-6, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-9, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-12, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-15, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-18, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-21, -40, 30, blue)));

	assets.push_back(shared_ptr<Cube>(new Cube(-24, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-27, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-30, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-33, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-36, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-39, -40, 30, blue)));





	assets.push_back(shared_ptr<Cube>(new Cube(0, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(3, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(6, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(9, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(12, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(15, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(18, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(21, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(24, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(27, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(30, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(33, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(36, -40, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(39, -40, 30, blue)));
	//





	//left border:



	assets.push_back(shared_ptr<Cube>(new Cube(-40, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 36, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 39, 30, blue)));

	assets.push_back(shared_ptr<Cube>(new Cube(-40, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -36, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, -39, 30, blue)));

	//



	//right border:

	assets.push_back(shared_ptr<Cube>(new Cube(40, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 36, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 39, 30, blue)));

	assets.push_back(shared_ptr<Cube>(new Cube(40, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -36, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, -39, 30, blue)));


	//



	//cross borders

	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(3, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(6, 6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(9, 9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(12, 12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(15, 15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(18, 18, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(21, 21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(24, 24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(27, 27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(30, 30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(33, 33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(36, 36, 30, blue)));


	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(3, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(6, -6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(9, -9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(12, -12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(15, -15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(18, -18, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(21, -21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(24, -24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(27, -27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(30, -30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(33, -33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(36, -36, 30, blue)));


	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-3, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-6, -6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-9, -9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-12, -12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-15, -15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-18, -18, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(-21, -21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-24, -24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-27, -27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-30, -30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-33, -33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-36, -36, 30, blue)));

	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-3, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-6, 6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-9, 9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-12, 12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-15, 15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-18, 18, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(-21, 21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-24, 24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-27, 27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-30, 30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-33, 33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-36, 36, 30, blue)));

	//
	//Center Border



	assets.push_back(shared_ptr<Cube>(new Cube(5, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(6, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(9, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(12, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(15, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(18, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(20, 0, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(24, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(27, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(30, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(33, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(36, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(40, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(5, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-5, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(5, 3, 30, blue)));


	
	assets.push_back(shared_ptr<Cube>(new Cube(-5, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-6, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-9, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-12, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-15, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-18, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-20, 0, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(-24, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-27, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-30, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-33, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-36, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-40, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-5, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(-5, -3, 30, blue)));


	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 21, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, 36, 30, blue)));


	assets.push_back(shared_ptr<Cube>(new Cube(0, 0, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -3, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -6, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -9, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -12, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -15, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -18, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -20, 30, blue)));
	//assets.push_back(shared_ptr<Cube>(new Cube(0, -24, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -27, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -30, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -33, 30, blue)));
	assets.push_back(shared_ptr<Cube>(new Cube(0, -36, 30, blue)));



	/*assets.push_back(shared_ptr<WallAsset>(new WallAsset(0, -25, 30)));*/ //conflicts and wont work
	


	shared_ptr<GameAsset> player1 = shared_ptr<GameAsset>(new Cube(cubeX, cubeY, cubeZ, blue));
	player.push_back(player1);

	shared_ptr<GameAsset> goal = shared_ptr<GameAsset>(new TriangularPyramidAsset(10, 31, 30));
	player.push_back(goal);

	// Call the function "display" every delay milliseconds
	SDL_AddTimer(delay, display, NULL);

	// Add the main event loop
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
			  SDL_Quit();
			  break;
			case SDL_USEREVENT:
			  display();
			  break;
			case SDL_KEYDOWN:
			  Matrix4 Camera = Camera::getInstance().getCameraM();
			  switch(event.key.keysym.sym){
			  case SDLK_LEFT:
				  if (Spec == 0){
					  cubeX -= 3;
					  player[0] = shared_ptr<GameAsset>(new Cube(cubeX, cubeY, cubeZ, blue));
				  }
				  if (Spec == 1){
					  Camera::getInstance().setCamera((Camera * Matrix4::rotationX(10.0 / 360.0)));
					 // Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(-1.0, 0.0, 0.0)));
				  }
			    break;

			  case SDLK_RIGHT:
				  if (Spec == 0){
					  cubeX += 3;
					  player[0] = shared_ptr<GameAsset>(new Cube(cubeX, cubeY, cubeZ, blue));
				  }
				  if (Spec == 1){

					  Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(1.0, 0.0, 0.0)));
				  }
			    break;

			  case SDLK_r: // change mode - movement/camera
				  if (Spec == 0){
					  Spec = 1;
				  }
				  else {
					  Spec = 0;
				  }
				  break;
			  case SDLK_UP:
				  if (Spec == 0){
					  cubeY += 3;
					  player[0] = shared_ptr<GameAsset>(new Cube(cubeX, cubeY, cubeZ, blue));
				  }
				  if (Spec == 1){

					   Camera::getInstance().setCamera((Camera * Matrix4::rotationX(10.0 / 360.0)));
					   Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(0.0, 0.0, -1.0)) );
				  }
			    break;
			  case SDLK_DOWN:
				  if (Spec == 0){
					  cubeY -= 3;
					  player[0] = shared_ptr<GameAsset>(new Cube(cubeX, cubeY, cubeZ, blue));
				  }
				  if (Spec == 1){
					  Camera::getInstance().setCamera(Camera * Matrix4::translation(Vector3(0.0, 0.0, 1.0)));
				  }
			    break;
			  case SDLK_SPACE:
				  		  Camera::getInstance().setCamera(Matrix4::identity());

			  default:
			  
			    break;

			  case SDLK_ESCAPE:
				  SDL_Quit();
				  cout << "Have a good day " << endl;

				  break;


			  }
			  break;
			}
	}
}
