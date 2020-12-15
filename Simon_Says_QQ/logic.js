function startNew() {
    if(!isGamePlayed) {
        isGamePlayed = true
        score = 0.0
        combo = 1.0
        attempts = 0
        aiTurn()
    }
}

function aiTurn() {
    aiSequence.push(Math.floor(Math.random() * panelSize * panelSize))

    for(var i = 0; i < aiSequence.length; i++)
        buttonsPanel.itemAt(aiSequence[i]).animation()

    isPlayerTurn = true
}

function playerTurn(i) {
    var flag = true
    if(isPlayerTurn) {
        playerSequence.push(i)

        for(var j = 0; j < playerSequence.length; j++) {
            if(playerSequence[j] !== aiSequence[j])
                flag = false
        }

        if((playerSequence.length === aiSequence.length) && flag) {
            playerSequence.length = 0
            score += (5.0 * combo)
            combo += 0.2

            isPlayerTurn = false
            aiTurn()
        }

        if(!flag) {
            attempts += 1
            combo = 1.0
            aiSequence.length = 0
            playerSequence.length = 0

            if(lives == attempts) {
                attempts = 0
                gameOverDialog.open()
                stopGame()
            }
            else {
                isPlayerTurn = false
                aiTurn()
            }
        }
    }
}

function stopGame() {
    aiSequence.length = 0
    playerSequence.length = 0
    isPlayerTurn = false
    isGamePlayed = false
}
