#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

#include <windows.h>

#include "curses.h"

#include "command.h"
#include "serial.h"
#include "ui.h"

uint8_t speed = 0;
/*
 * 0: forward
 * 1: backward
 */
unsigned int dir = 0;
 
bool isValidChoice(char c) {
  const char validChoices[] = {' ', 'R', 'r', 'W', 'w', 'M',
				 'm', 'S', 's', 'E', 'e', 'x', 'X'};
  for (unsigned int i = 0; i < sizeof(validChoices); i++) {
    if (c == validChoices[i])
      return true;
  }
  return false;
}

char getChoice() {
  printw("Space: Start/Stop the train\n");
  printw("R    : Ring the bell\n");
  printw("W    : Accelerate the train\n");
  printw("M    : Change direction of the train\n");
  printw("S    : Decelerate the train\n");
  printw("E    : End program\n");
  printw("Speed: %u\n", speed);
  printw("Direction: %s\n", ((!dir) ? "forward" : "backward"));
  
  char c = getch();
  if (!isValidChoice(c)) {
    return 0;
  }
  return tolower(c);
}

void executeChoice(char choice, bool* engineStarted, uint8_t engineAddr) {
  if (choice != ' ' && !*engineStarted) {
    printw("Error: Train not yet started\n\n");
    return;
  }
  switch (choice) {
  case ' ':
    //Check if engine is already started
    if (!(*engineStarted)) {
      printw("Starting engine..\n");
      engineSetAbsSpeed(engineAddr, speed);
    }
    else {
      sysHalt();
      printw("Stopping engine..\n");
    }
    *engineStarted = !(*engineStarted);
    break;
  case 'r':
    engineBlowHorn1(engineAddr);
    printw("Ringing the bell..\n");
    break;
  case 'w':
    if (speed < 15) {
      speed++;
      engineSetAbsSpeed(engineAddr, speed);
      printw("Accelerating the engine..\n");
    }
    break;
  case 'm':
    dir = ~dir;
    if (dir) {
        engineRevDir(engineAddr);
    } else {
        engineFwdDir(engineAddr);
    }
    printw("Changing direction..\n");
    break;
  case 's':
    if (speed > 0) {
      speed--;
      engineSetAbsSpeed(engineAddr, speed);
      printw("Decelerating the engine..\n");
    }
    break;
  case 'e':
    sysHalt();
    printw("Exiting program and stopping engine..");
    break;
  case 'x':
      engineSetAbsSpeed(engineAddr, 20);
      break;
  }
  printw("\n");
}

void runTrain() {
  printw("Starting program..\n\n");
  char choice = '\0';
  choice = (!init_serial()) ? 0 : 'e';
  bool trainStarted = false;
  uint8_t trainAddr = 23;
  speed = 5;
  while (choice != 'e') {
    choice = getChoice();
    clear();
    if (!choice) {
      printw("Error: Invalid choice\n\n");
      continue;
    }
    executeChoice(choice, &trainStarted, trainAddr);
  }
  close_serial();
}

void startTrain() {
  initscr();
  cbreak();
  runTrain();
  endwin();
}
