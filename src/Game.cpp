#include "raylib.h"
#include "Assets.hpp"
#include "Game.hpp"
#include "Circle.hpp"
#include "Player.hpp"
#include "CircleButton.hpp"
#include "Leaderboard.hpp"
#include "Text.hpp"
#include "TextField.hpp"
#include <vector>
#include <string>

std::random_device rd;
std::mt19937 gen(rd());

CircleButton trophyButton;


enum class GameState {Menu, Leaderboard, Game, HighScore, End};
GameState state = GameState::Menu;

std::vector<Circle> circles;

Player* player = nullptr;
Leaderboard* leaderboard = nullptr;
TextField* textField = nullptr;

int score = 0;
bool isPaused = false;

Text startText, restartText, highScoreText, pausedText;




int randInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

float randFloat() {
    std::uniform_real_distribution<> dist(0.0, 1.0);
    return dist(gen);
}

void drawScore() {
    std::string scoreText = std::to_string(score);
    Vector2 dim = MeasureTextEx(Assets::helvetica, scoreText.c_str(), 64, 0);
    DrawTextEx(Assets::helvetica, std::to_string(score).c_str(), Vector2{Game::screenWidth - dim.x - 24+1, 24+1}, 64, 0, Color{85,98,112,255});
    DrawTextEx(Assets::helvetica, std::to_string(score).c_str(), Vector2{Game::screenWidth - dim.x - 24, 24}, 64, 0, WHITE);
}

void detectCollision() {
    for(int i = circles.size() - 1; i >= 0; --i) {
        Circle c = circles[i];
        int dist = pow(pow(c.x - player->x, 2) + pow(c.y - player->y, 2), 0.5);
        if(dist < c.radius + player->radius) {
            // collision
            if(c.radius > player->radius) {     // death
                Game::death();
                return;
            }
            else {
                // gain point
                score++;
                player->radius++;
                circles.erase(circles.begin() + i);
                continue;
            }
        }
    }
}

void Game::init() {

    trophyButton = CircleButton(Assets::trophy, Game::screenWidth - Assets::trophy.width - 12, 12, 40, Color{127,127,127,255});

    leaderboard = new Leaderboard();
    textField = new TextField();

    startText = Text(Assets::font, "Click to Start", 108);
    restartText = Text(Assets::font, "Ouch! Play Again?", 108);
    highScoreText = Text(Assets::font, "Great Score!", 108);
    pausedText = Text(Assets::font, "Paused", 108);

    circles.clear();

    for(int i = 0; i < Game::maxCircles(); ++i) {
        circles.push_back(Circle(true, player));
    }
}

void Game::start() {
    player = new Player();
    state = GameState::Game;

    score = 0;

    circles.clear();
}

void Game::death() {
    delete player;
    player = nullptr;
    state = GameState::End;

    if(leaderboard->isNewHighScore(score) != -1) {
        state = GameState::HighScore;
    }
}

void Game::update(float dt) {

    Game::screenWidth = GetScreenWidth();
    Game::screenHeight = GetScreenHeight();

    mousePos = GetMousePosition();

    if(isPaused == false) {
        // restore circle count
        if(circles.size() < Game::maxCircles() && randFloat() < 0.25) {
            circles.push_back(Circle(false, player));
        }

        // process circles
        for(int i = circles.size() - 1; i >= 0; --i) {
            if(!circles[i].inBounds()) {
                circles.erase(circles.begin() + i);
            }
            circles[i].update(dt);
        }
    }

    switch(state) {
        case GameState::Menu: {
            if(trophyButton.isClicked()) {
                state = GameState::Leaderboard;
            }
            else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                start();

            trophyButton.x = Game::screenWidth - Assets::trophy.width - 12;
			leaderboard->update();
        } break;
        case GameState::Leaderboard: {
            if(IsKeyPressed(KEY_ESCAPE)) {
                state = GameState::Menu;
            }
			
			leaderboard->update();
        } break;
        case GameState::Game: {

            if(IsKeyPressed(KEY_ESCAPE)) {
                isPaused = !isPaused;
            }

            if(isPaused) {
                pausedText.draw((Game::screenWidth - pausedText.width) / 2+1, (Game::screenHeight - pausedText.height) / 2+1, Color{85, 98, 112, 255});
                pausedText.draw((Game::screenWidth - pausedText.width) / 2, (Game::screenHeight - pausedText.height) / 2, WHITE);
            }
            else {
                if(player)
                    player->update(dt);
            }

            detectCollision();
        } break;
        case GameState::HighScore: {
            textField->update();

            if(textField->submit.isClicked()) {
                leaderboard->saveHighScore(score, textField->input);
                start();
            }
        } break;
        case GameState::End: {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                start();
            if(IsKeyPressed(KEY_ESCAPE)) {
                state = GameState::Menu;
            }
        } break;
        default:
            break;
    }
}

void Game::draw() {
    ClearBackground(Color{234, 234, 234, 255});

    for(int i = 0; i < circles.size(); ++i) {
        circles[i].draw();
    }

    switch(state) {
        case GameState::Menu: {

            trophyButton.draw();

            startText.draw((Game::screenWidth - startText.width) / 2+1, (Game::screenHeight - startText.height) / 2+1, Color{85, 98, 112, 255});
            startText.draw((Game::screenWidth - startText.width) / 2, (Game::screenHeight - startText.height) / 2, WHITE);
        } break;
        case GameState::Leaderboard: {
            leaderboard->draw();
        } break;
        case GameState::Game: {
            if(player)
                player->draw();

            drawScore();
        } break;
        case GameState::HighScore: {
            highScoreText.draw((Game::screenWidth - highScoreText.width) / 2+1, (Game::screenHeight - highScoreText.height) / 2+1 - 40, Color{85, 98, 112, 255});
            highScoreText.draw((Game::screenWidth - highScoreText.width) / 2, (Game::screenHeight - highScoreText.height) / 2 - 40, WHITE);
            textField->draw();

            drawScore();
        } break;
        case GameState::End: {
            restartText.draw((Game::screenWidth - restartText.width) / 2+1, (Game::screenHeight - restartText.height) / 2+1, Color{85, 98, 112, 255});
            restartText.draw((Game::screenWidth - restartText.width) / 2, (Game::screenHeight - restartText.height) / 2, WHITE);

            drawScore();
        } break;
        default:
            break;
    }
}