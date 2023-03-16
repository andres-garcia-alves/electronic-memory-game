#ifndef COMMANDS_H
#define COMMANDS_H

// functions declaration
// void clearCommands();
// void createGameModeCommand(eGameMode);


void initializeCommand() {

  currentLevel = 0;           // zero based
  clearPlayerSequence();      // clear player sequence
  buildRandomColorSequence(); // build a new random colore sequence
  // clearCommands();         // clear commands queue

  #if DEBUG
  sizeofCommandStruct();
  debugColorArrays();
  #endif 
}

void gameModeCommand(eGameMode newGameMode) {
  gameMode = newGameMode;
}

void waitOperationCommand() {
  // the delay part is done by CommandsManager
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void debounceFlagCommand() {
  debounced = true;
}

void buttonPressedCommand(byte packedInput) { // stInput input
  debounced = false;
  stInput input = unpackInput(packedInput);

  // display pressed button
  digitalWrite(LED_RED, input.redButton);
  digitalWrite(LED_BLUE, input.blueButton);
  digitalWrite(LED_YELLOW, input.yellowButton);
  digitalWrite(LED_GREEN, input.greenButton);

  // basic validations
  byte sumButtons = input.redButton + input.blueButton + input.yellowButton + input.greenButton;
  if (sumButtons == 0) { return; }  // no buttom pressed (teorically unreachable)
  if (sumButtons >= 2) { gameMode = eGameMode::FINISH; return; }  // more that a single buttom pressed

  // wrong buttom pressed validation
  byte playerPosition = getPlayerSequencePosition();
  eColor currentColor = (eColor)colorSequence[playerPosition];

  if (input.redButton && currentColor != eColor::RED || input.blueButton && currentColor != eColor::BLUE ||
      input.yellowButton && currentColor != eColor::YELLOW || input.greenButton && currentColor != eColor::GREEN) {
    gameMode = eGameMode::FINISH; return;
  }

  // save color on player sequence
  playerSequence[playerPosition] = currentColor;

  // check increment of current level & change to sequence mode
  if (playerPosition == currentLevel) {
    clearPlayerSequence();
    currentLevel++;
    gameMode = eGameMode::SEQUENCE_MODE;
  }
}

void showColorCommand(eColor color) {

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  switch(color) {
    case eColor::RED:     digitalWrite(LED_RED, HIGH);    break;
    case eColor::BLUE:    digitalWrite(LED_BLUE, HIGH);   break;
    case eColor::YELLOW:  digitalWrite(LED_YELLOW, HIGH); break;
    case eColor::GREEN:   digitalWrite(LED_GREEN, HIGH);  break;
  }
}

void beepCommand(byte frecuency, byte duration) {

  tone(BUZZER, frecuency * FRECUENCY_MULTIPLIER, duration * DURATION_MULTIPLIER);
}

void endingCommand() {

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

#endif
