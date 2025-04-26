#include "board-display.hpp"
#include <stdlib.h>

BoardDisplay::BoardDisplay() {

    // Background
    for (int i = 0; i < 3; i++) {
       backgrounds[i].loadFromFile("assets/BGs/gamebg-" + std::to_string(i) + ".png", sf::IntRect());
    }

    background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setTexture(&backgrounds[1], true);
    background.setPosition(0, 0);

    // Board
    boardTexture.loadFromFile("assets/Board/board.png");
    board.setSize(static_cast<sf::Vector2f>(boardTexture.getSize()));
    board.setTexture(&boardTexture);
    board.setPosition(BOARD_X_MARGIN, BOARD_Y_MARGIN);

    // Chips
    for (int i = 0; i < 2; i++) {
        chipTextures[i].loadFromFile("assets/Board/disk-" + std::to_string(i) + ".png");
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            sf::Vector2f pos(CHIP_FIRST_X + (CHIP_DIAMETER + CHIP_X_GAP) * j, 
                             CHIP_FIRST_Y + (CHIP_DIAMETER + CHIP_Y_GAP) * i);
            displayGrid[i][j].setPos(pos);

        }
    }

    // Column Regions
    sf::Vector2f colSize(CHIP_DIAMETER, (CHIP_DIAMETER + CHIP_Y_GAP) * ROWS);

    for (int i = 0; i < COLUMNS; i++) {
        columnRegions[i] = sf::FloatRect(displayGrid[0][i].getPos(), colSize);
    }
}


sf::RectangleShape BoardDisplay::renderBackground() {
    return background;
}

sf::RectangleShape BoardDisplay::renderBoard() {
    return board;
}

Chip BoardDisplay::getCell(int row, int col) {
    return displayGrid[row][col];
}

void BoardDisplay::placeCell(int row, int col, int chipType) {
    displayGrid[row][col].place();
    displayGrid[row][col].setColor(sf::Color::White);
    displayGrid[row][col].setTexture(chipTextures[chipType]);
}

void BoardDisplay::resetCells() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            displayGrid[i][j] = Chip();
            sf::Vector2f pos(CHIP_FIRST_X + (CHIP_DIAMETER + CHIP_X_GAP) * j, 
                             CHIP_FIRST_Y + (CHIP_DIAMETER + CHIP_Y_GAP) * i);
            displayGrid[i][j].setPos(pos);

        }
    }
}


void BoardDisplay::setTurn(int player) {
    background.setTexture(&backgrounds[player], true);
}


bool BoardDisplay::isOnColumn(sf::Vector2i mousePos, int col) {
    return columnRegions[col].contains(static_cast<sf::Vector2f>(mousePos));
}

void BoardDisplay::selectColumn(int col) {
    for (int i = 0; i < ROWS; i++) {

        if (!displayGrid[i][col].isPlaced())
            displayGrid[i][col].setColor(sf::Color::Green);

    }
}
        
void BoardDisplay::unselectColumn(int col) {
    for (int i = 0; i < ROWS; i++) {

        if (!displayGrid[i][col].isPlaced())
            displayGrid[i][col].setColor(sf::Color::Transparent);
            
    }
}