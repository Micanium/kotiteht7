#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QTimer>
#include <QMessageBox>

ChessClock::ChessClock(QWidget* parent) : QMainWindow(parent),
    player1Time(0), player2Time(0), currentPlayer(1), gameRunning(false) {
    ui.setupUi(this);

    ui.progressBarPlayer1->setRange(0, 100);
    ui.progressBar_2->setRange(0, 100);
    ui.progressBarPlayer1->setValue(100);
    ui.progressBar_2->setValue(100);
    ui.label->setText("Start game");

    connect(ui.pushButton_1, &QPushButton::clicked, this, [this] { setGameTime(120); });
    connect(ui.pushButton_2, &QPushButton::clicked, this, [this] { setGameTime(300); });
    connect(ui.pushButton_3, &QPushButton::clicked, this, &ChessClock::startGame);
    connect(ui.pushButton_4, &QPushButton::clicked, this, [this] { stopGame(); });
    connect(ui.pushButton_5, &QPushButton::clicked, this, &ChessClock::switchPlayer);
    connect(ui.pushButton_6, &QPushButton::clicked, this, &ChessClock::switchPlayer);
    connect(ui.pushButton_7, &QPushButton::clicked, this, &ChessClock::Fasttimer);
}

void ChessClock::setGameTime(int seconds) {
    if (!gameRunning) {
        player1Time = seconds;
        player2Time = seconds;
        ui.progressBarPlayer1->setValue(100);
        ui.progressBar_2->setValue(100);
    }
}

void ChessClock::startGame() {
    if (player1Time > 0 && !gameRunning) {
        gameRunning = true;
        countdown();
        ui.label->setText("Game Running");
    }
}

void ChessClock::stopGame() {
    // This function will be called when button 4 (presumably a "Stop" button) is clicked.
    // It will pause the game and display "Game Paused."
    gameRunning = false;
    ui.label->setText("Game Paused");
}
void ChessClock::switchPlayer() {
    if (gameRunning) {
        resetTimer(); // Stop the current player's turn
        if (currentPlayer == 1) {
            currentPlayer = 2;
            ui.label->setText("Player 2 making moves");
        } else {
            currentPlayer = 1;
            ui.label->setText("Player 1 making moves");
        }
        startGame(); // Start the new player's turn
    }
}
void ChessClock::Fasttimer(){
    if (gameRunning) {
        if (currentPlayer == 1) {
            if (player1Time > 1) {
                player1Time--;
                ui.progressBarPlayer1->setValue(player1Time);
                QTimer::singleShot(1000, this, &ChessClock::countdown);
            } else if (player2Time == 0) {
                endGame(0); // Game over
            }
        } else {
            if (player2Time > 1) {
                player2Time--;
                ui.progressBar_2->setValue(player2Time);
                QTimer::singleShot(1000, this, &ChessClock::countdown);
            } else if (player1Time == 0) {
                endGame(0); // Game over
            }
        }
    } else if (player1Time == 0 || player2Time == 0) {
        endGame(0); // Game over when gameRunning is false and one of the progress bars is at 0
    }

}

void ChessClock::resetTimer() {
    // Reset the timer when switching players.
    // This function is currently empty because you mentioned not resetting progress bars when switching players.
}

void ChessClock::countdown() {
    if (gameRunning) {
        if (currentPlayer == 1) {
            if (player1Time > 0) {
                player1Time--;
                ui.progressBarPlayer1->setValue(player1Time);
                QTimer::singleShot(1000, this, &ChessClock::countdown);
            } else if (player2Time == 0) {
                endGame(0); // Game over
            }
        } else {
            if (player2Time > 0) {
                player2Time--;
                ui.progressBar_2->setValue(player2Time);
                QTimer::singleShot(1000, this, &ChessClock::countdown);
            } else if (player1Time == 0) {
                endGame(0); // Game over
            }
        }
    } else if (player1Time == 0 || player2Time == 0) {
        endGame(0); // Game over when gameRunning is false and one of the progress bars is at 0
    }
}

void ChessClock::endGame(int winner) {
    gameRunning = false;
    if (winner == 1) {
        ui.label->setText("Player 1 wins!");
    } else if (winner == 2) {
        ui.label->setText("Player 2 wins!");
    } else {
        ui.label->setText("Game Over");
    }
}
