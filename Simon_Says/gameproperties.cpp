#include "gameproperties.h"

GameProperties::GameProperties()
{
    AiButtons = new PanelButtons(false, boardSize);
    PlayerButtons = new PanelButtons(true, boardSize);
    for(int i = 0; i < boardSize * boardSize; i++) {
        connect(PlayerButtons->getButton(i), &Button::buttonPressed, this, &GameProperties::playerTurn);
    }

    connect(&anim, &QSequentialAnimationGroup::finished, this, &GameProperties::setPlayerTurn);
}

void GameProperties::animationClear()
{
    anim.clear();
    for(int i = 0; i < boardSize * boardSize; i++) {
        AiButtons->getButton(i)->graphicsEffect()->setProperty("opacity", 0.0);
    }
}

void GameProperties::setGamePlayed()
{
    isGamePlayed = !isGamePlayed;

    if(isGamePlayed) {
        emit scoreUpdate(QString("%1").arg(score));
        emit comboUpdate(QString("%1").arg(combo));
        emit attemptsUpdate(QString("%1").arg(attempts));
        aiTurn();
    }
}

void GameProperties::setPlayerTurn()
{
    isPlayerTurn = !isPlayerTurn;
    emit enablePlayerPanel(isPlayerTurn);
}

void GameProperties::aiTurn()
{
    anim.clear();
    AISequence.append(qrand() % (boardSize * boardSize));

    for(int i = 0; i < AISequence.length(); i++)
    {
        Button *currButton = AiButtons->getButton(AISequence[i]);
        anim.addAnimation(currButton->animateDiode(diodeLightUpTime));
    }
    anim.start();
}

void GameProperties::playerTurn(int i)
{
    bool flag = true;
    if(isPlayerTurn)
    {
        PlayerSequence.append(i - 1);
        for(int i = 0; i < PlayerSequence.length(); i++) {
            if(PlayerSequence[i] != AISequence[i])
                flag = false;
        }

        if(PlayerSequence.length() == AISequence.length() && flag) {
            PlayerSequence.clear();
            score += 5.0 * combo;
            combo += 0.2;
            emit scoreUpdate(QString("%1").arg(score));
            emit comboUpdate(QString("%1").arg(combo));

            setPlayerTurn();
            aiTurn();
        }

        if(!flag) {
            attemptsTaken++;
            combo = 1.0;
            AISequence.clear();
            PlayerSequence.clear();
            emit attemptsUpdate(QString("%1").arg(attempts - attemptsTaken));
            emit comboUpdate(QString("%1").arg(combo));

            if(attemptsTaken == attempts) {
                QMessageBox *gameOver = new QMessageBox();
                gameOver->setText("Game over! You did your best!");
                gameOver->exec();
                resetGame();
                emit gameEnded(true);
            }
            else {
                setPlayerTurn();
                aiTurn();
            }
        }
    }
}

void GameProperties::resetGame()
{
    animationClear();
    isGamePlayed = false;
    isPlayerTurn = false;
    score = 0.0;
    combo = 1.0;
    attemptsTaken = 0;
    AISequence.clear();
    PlayerSequence.clear();
}

void GameProperties::settingsChange(QVector<int> settings)
{
    if(boardSize != settings[0]) {
        for(int i = 0; i < boardSize * boardSize; i++) {
            disconnect(PlayerButtons->getButton(i), &Button::buttonPressed, this, &GameProperties::playerTurn);
            delete PlayerButtons->getButton(i);
            delete AiButtons->getButton(i);
        }

        boardSize = settings[0];
        delete AiButtons;
        delete PlayerButtons;

        AiButtons = new PanelButtons(false, boardSize);
        PlayerButtons = new PanelButtons(true, boardSize);

        for(int i = 0; i < boardSize * boardSize; i++) {
            connect(PlayerButtons->getButton(i), &Button::buttonPressed, this, &GameProperties::playerTurn);
        }

        emit panelsChanged();
    }

    if(diodeLightUpTime != settings[1]) {
        diodeLightUpTime = settings[1];
    }

    if(attempts != settings[2]) {
        attempts = settings[2];
        emit attemptsUpdate(QString("%1").arg(attempts));
    }
}
