# Quoridor Game for LandTiger Board

## Overview

This project is an implementation of the Quoridor board game on the LandTiger Board, developed using Keil µVision. Quoridor is an abstract strategy game originally published in 1997 by Gigamic. The goal of this project is to bring the strategic challenge of Quoridor to the LandTiger Board, allowing users to play against each other using a 7x7 wooden square grid displayed on the board's screen. The game has been programmed to utilize the board's input controls, such as the joystick and buttons, to facilitate game interactions.

## Game Rules

### Objective
Each player starts with a token and 8 barriers. The objective is to move your token from your starting position on the perimeter to the opposite side of the board before your opponent does. The first player to reach the opposite perimeter wins the game.

### Gameplay
- **Move Your Token:** On your turn, you can move your token one square horizontally or vertically.
- **Place a Barrier:** Alternatively, you can place a barrier between squares to block your opponent. Barriers can only be placed along the grooves on the board and cannot completely block a player’s path to their goal.

### Additional Rules
- **Jumping Over Tokens:** If your token faces your opponent’s token directly, you may jump over them to the next square if there is no barrier behind them.
- **No Complete Blocking:** You cannot place barriers in a way that traps your opponent entirely; they must always have a path to their goal.
- **Time Limit:** You have 20 seconds to make your move; otherwise, you lose your turn.

## Features

### Game Board
The game board is a 7x7 grid displayed on the LandTiger Board. Players' tokens and barriers are represented in different colors:
- **Player 1:** White token
- **Player 2:** Red token
- **Barriers:** Displayed in a distinctive color, with options to rotate and place them between squares.

### Controls
- **Joystick:** 
  - Use to move your token or navigate the board when placing barriers.
  - **JOY UP/DOWN/LEFT/RIGHT:** Move token or position barrier.
  - **JOY SELECT:** Confirm your move or the placement of a barrier.
- **Buttons:**
  - **KEY1:** Enter barrier placement mode.
  - **KEY2:** Rotate the barrier by 90 degrees.

### Game Flow
- The game starts when you press `INT0`.
- Players alternate turns, choosing either to move their token or place a barrier.
- The game ends when a player successfully moves their token to the opposite side of the board.

## Installation and Setup

### Requirements
- **Keil µVision**: The project is developed using the Keil µVision IDE. Make sure you have this installed on your system.
- **LandTiger Board or Emulator**: You can run the game on an actual LandTiger board or use the LandTiger emulator within Keil µVision.

### How to Run the Game
1. **Download the Project**: Clone or download the project from the repository.
2. **Open in Keil µVision**: Load the project into Keil µVision.
3. **Compile and Load**: Compile the code and load it onto the LandTiger board or run it using the emulator.
4. **Start the Game**: Press `INT0` on the LandTiger board to start the game.

## Screenshots

Below are images illustrating key gameplay elements:

1. **Initial Game Board Setup:**
   ![Initial Game Board](image1.png)
   
2. **Token Movement:**
   ![Token Movement](image2.png)

3. **Barrier Placement:**
   ![Barrier Placement](image3.png)
   
4. **Barrier Rotation:**
   ![Barrier Rotation](image4.png)

  
Enjoy the game and may the best strategist win!
