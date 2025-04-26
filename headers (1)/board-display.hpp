#include "constants.hpp"
#include "chip.hpp"

#define ROWS 6
#define COLUMNS 7

#define BOARD_X_MARGIN 168
#define BOARD_Y_MARGIN 71

class BoardDisplay {
    private:
        sf::Texture backgrounds[3];
        sf::RectangleShape background;

        sf::Texture boardTexture;
        sf::RectangleShape board;

        sf::Texture chipTextures[2];
        Chip displayGrid[ROWS][COLUMNS];

        sf::FloatRect columnRegions[COLUMNS];
    public:
        BoardDisplay();

        sf::RectangleShape renderBackground();
        sf::RectangleShape renderBoard();

        Chip getCell(int, int);
        void placeCell(int, int, int);
        void resetCells();

        void setTurn(int);

        bool isOnColumn(sf::Vector2i, int);

        void selectColumn(int);
        void unselectColumn(int);
};