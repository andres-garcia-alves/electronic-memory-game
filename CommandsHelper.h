#include "CommandsManager.h"

#ifndef COMMANDS_HELPER_H
#define COMMANDS_HELPER_H

// functions declaration
stBuzzer buildSound(stInput, eWait);
stBuzzer buildSound(eColor, eWait);
stBuzzer buildSound(eTone, eWait);
stBuzzer buildSound(byte, byte);
stCommand buildCommand(eCmdType, eWait, eGameMode, byte, eColor, stBuzzer);


void createInitializeCommand() {

  enqueueCommand(buildCommand(eCmdType::RESET, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::SEQUENCE_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

void createGameModeCommand(eGameMode gameMode) {

  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, gameMode, emptyInput, eColor::NONE, emptyBuzzer));
}

void createSequenceCommands() {

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::BEGINNING, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));

  for (int i = 0; i <= currentLevel; i++) {
    stBuzzer buzzer = buildSound(colorSequence[i], eWait::ANIMATION);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIMATION, eGameMode::NONE, emptyInput, colorSequence[i], emptyBuzzer));
    enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIMATION, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  }

  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::PLAYER_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

void createDebounceCommand() {

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::DEBOUNCE, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::DEBOUNCE, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
}

void createProcessInputCommand(stInput input) {

  byte packedInput = packInput(input);
  stBuzzer buzzer = buildSound(input, eWait::ANIMATION);

  enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
  enqueueCommand(buildCommand(eCmdType::BUTTON, eWait::ANIMATION, eGameMode::NONE, packedInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::LED, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
}

void createEndingCommand() {

  stBuzzer buzzer = buildSound(eTone::WRONG, eWait::ENDING);
  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIMATION, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
  enqueueCommand(buildCommand(eCmdType::END, eWait::ENDING, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::SEQUENCE_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

/*void createBeepCommand(int frecuency, int duration) {

  stBuzzer buzzer = buildSound(frecuency, duration);
  enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
}*/


// auxiliar functions
stBuzzer buildSound(stInput input, eWait wait) {
  byte frecuency = 0;
  if (input.redButton)    { frecuency += (byte)eTone::RED; }
  if (input.blueButton)   { frecuency += (byte)eTone::BLUE; }
  if (input.yellowButton) { frecuency += (byte)eTone::YELLOW; }
  if (input.greenButton)  { frecuency += (byte)eTone::GREEN; }
  
  return buildSound(frecuency, (byte)wait);
}

stBuzzer buildSound(eColor color, eWait wait) {
  byte frecuency = 0;
  if (color == eColor::RED)    { frecuency += (byte)eTone::RED; }
  if (color == eColor::BLUE)   { frecuency += (byte)eTone::BLUE; }
  if (color == eColor::YELLOW) { frecuency += (byte)eTone::YELLOW; }
  if (color == eColor::GREEN)  { frecuency += (byte)eTone::GREEN; }
  
  return buildSound(frecuency, (byte)wait);
}

stBuzzer buildSound(eTone tone, eWait wait) {
  return buildSound((byte)tone, (byte)wait);
}

stBuzzer buildSound(byte frecuency, byte duration) {
  stBuzzer buzzer;
  buzzer.frecuency = frecuency;
  buzzer.duration = duration;
  return buzzer;
}

stCommand buildCommand(eCmdType cmdType, eWait wait, eGameMode gameMode, byte input, eColor color, stBuzzer buzzer) {
  stCommand command;
  command.cmdType = cmdType;
  command.input = input;
  command.color = color;
  command.wait = wait;
  command.gameMode = gameMode;
  command.buzzer = buzzer;
  return command;
}

#endif
