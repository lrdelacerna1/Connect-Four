#include "engine.hpp"

/* PRIMARY FUNCTIONS */

Engine::Engine() 
: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME)
{
    state = start;

    bgmusic.openFromFile("assets/Audios/background-music.mp3");
    bgmusic.setLoop(true);
    bgmusic.setVolume(50);
    bgmusic.play();

    click.setSound("assets/Audios/button.mp3", 50);
    chipDrop.setSound("assets/Audios/chip.mp3", 50);
    gameEnd.setSound("assets/Audios/winner.mp3", 50);
}

void Engine::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Engine::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
            break;
        }

        switch (state) {
            case start:
                handleStartInput(event);
                break;
            case how:
                handleHowInput(event);
                break;
            case game:
                handleGameInput(event);
                break;
            case end:
                handleEndInput(event);
                break;
        }

    }
}

void Engine::update() {
    // Logic Here!
    if (state == game) {
        // Update board
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                int cellVal = boardLogic.getCell(i, j);

                if (cellVal != 0) 
                    board.placeCell(i, j, cellVal - 1);
                
            }
        }

        board.setTurn(boardLogic.getCurrentPlayer());


        // End game
        if (boardLogic.getWinner() != 0) {
            state = end;
            gameEnd.play();
            endMenu.setResult(boardLogic.getWinner());
        }
    }

}

void Engine::render() {
    window.clear(sf::Color::Cyan);

    switch (state) {
        case start:
            renderStart();
            break;
        case how:
            renderHow();
            break;
        case game:
            renderGame();
            break;
        case end:
            renderEnd();
            break;
    }
    
    window.display();
}

void Engine::resetBoard() {
    boardLogic = Board();
    board.resetCells();
}

/* EVENT HANDLERS */
void Engine::handleStartInput(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (startMenu.isOnStartButton(sf::Mouse::getPosition(window))) {
            state = game;
            click.play();
        }
        else if (startMenu.isOnHowButton(sf::Mouse::getPosition(window))) {
            state = how;
            click.play();
        }
    } else {
        // Mouse Hover
        if (startMenu.isOnStartButton(sf::Mouse::getPosition(window))) {
            startMenu.selectStart();
        } else {
            startMenu.unselectStart();
        }

        if (startMenu.isOnHowButton(sf::Mouse::getPosition(window))) {
            startMenu.selectHow();
        } else {
            startMenu.unselectHow();
        }
    }
}

void Engine::handleHowInput(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (howMenu.isOnReturn(sf::Mouse::getPosition(window))) {
            state = start;
            click.play();
        }
        
    } else {
        // Mouse Hover
        if (howMenu.isOnReturn(sf::Mouse::getPosition(window))) {
            howMenu.selectReturn();
        } else {
            howMenu.unselectReturn();
        }

    }
}    

void Engine::handleGameInput(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < COLUMNS; i++) {
            if (board.isOnColumn(sf::Mouse::getPosition(window), i)) {
                // Give column to input to board
                printf("%i\n", i);
                if (boardLogic.playTurn(i))
                    chipDrop.play();
            }
        }
    } else {
        // Mouse Hover
        for (int i = 0; i < COLUMNS; i++) {
            if (board.isOnColumn(sf::Mouse::getPosition(window), i)) {
                board.selectColumn(i);
            } else {
                board.unselectColumn(i);
            }

        }
    }
}

void Engine::handleEndInput(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (endMenu.isOnReturn(sf::Mouse::getPosition(window))) {
            state = start;
            click.play();
        }
        
    } else {
        // Mouse Hover
        if (endMenu.isOnReturn(sf::Mouse::getPosition(window))) {
            endMenu.selectReturn();
            resetBoard();
        } else {
            endMenu.unselectReturn();
        }

    }
}



/* SUB-RENDER FUNCTIONS */

void Engine::renderStart() {
    window.draw(startMenu.renderTitle());
    window.draw(startMenu.renderStartButton());
    window.draw(startMenu.renderHowButton());
}

void Engine::renderHow() {
    window.draw(howMenu.renderHow());
    window.draw(howMenu.renderReturnButton());
}

void Engine::renderGame() {
    window.draw(board.renderBackground());
    window.draw(board.renderBoard());

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            window.draw(board.getCell(i,j).render());

        }
    }
}

void Engine::renderEnd() {
   window.draw(endMenu.renderResult());
   window.draw(endMenu.renderReturnButton());
}