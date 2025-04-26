#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "game-states.hpp"
#include "start-display.hpp"
#include "how-display.hpp"
#include "board-display.hpp"
#include "end-display.hpp"
#include "board.hpp"
#include "sound-effect.hpp"

class Engine {
    private:
        sf::RenderWindow window;
        sf::Music bgmusic;
        SoundEffect click;
        SoundEffect chipDrop;
        SoundEffect gameEnd;

        GameState state;

        StartDisplay startMenu;
        HowDisplay howMenu;

        BoardDisplay board;
        Board boardLogic;

        EndDisplay endMenu;
    
        void processEvents();
        void update();
        void render();

        void resetBoard();

        void handleStartInput(sf::Event);
        void handleHowInput(sf::Event);
        void handleGameInput(sf::Event);
        void handleEndInput(sf::Event);

        void renderStart();
        void renderHow();
        void renderGame();
        void renderEnd();

    public:
        Engine();
        void run();
};