#ifndef UTILITIES_H
#define UTILITIES_H

void buildRandomColorSequence() {
  
  for (byte i = 0; i < GAME_LEVELS; i++)
    colorSequence[i] = (eColor)random(1, 5);
}

byte getPlayerSequencePosition() {

  for (byte i = 0; i < GAME_LEVELS; i++)
    if (playerSequence[i] == eColor::NONE) { return i; }
  return 0;
}

void clearPlayerSequence() {

  for (byte i = 0; i < GAME_LEVELS; i++) {
    playerSequence[i] = eColor::NONE;
  }
}

byte packInput(stInput input) {

  byte packedInput;
  packedInput += (input.hasData)      ? 0b10000000 : 0b00000000;
  packedInput += (input.redButton)    ? 0b00001000 : 0b00000000;
  packedInput += (input.blueButton)   ? 0b00000100 : 0b00000000;
  packedInput += (input.yellowButton) ? 0b00000010 : 0b00000000;
  packedInput += (input.greenButton)  ? 0b00000001 : 0b00000000;
  
  return packedInput;
}

stInput unpackInput(byte packedInput) {

  stInput input;
  input.hasData       = packedInput & 0b10000000;
  input.redButton     = packedInput & 0b00001000;
  input.blueButton    = packedInput & 0b00000100;
  input.yellowButton  = packedInput & 0b00000010;
  input.greenButton   = packedInput & 0b00000001;
  
  return input;
}

void debugColorArrays() {

  Serial.print("colorSequence: ");
  for (byte i = 0; i < GAME_LEVELS - 1; i++) {
    Serial.print((byte)colorSequence[i]);
    Serial.print(", ");
  }
  Serial.println((byte)colorSequence[GAME_LEVELS-1]);

  Serial.print("playerSequence: ");
  for (byte i = 0; i < GAME_LEVELS - 1; i++) {
    Serial.print((byte)playerSequence[i]);
    Serial.print(", ");
  }
  Serial.println((byte)playerSequence[GAME_LEVELS-1]);
}

void sizeofCommandStruct() {
  Serial.print("sizeof(stCommand): ");
  Serial.println(sizeof(stCommand));
}

#endif
