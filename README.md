# LigueQuant Game

A Connect Four-like game implementation with a beautiful console interface.

## Features

- **Configurable Board Size**: Default 7x7, adjustable from 4x4 to 20x20
- **Configurable Win Condition**: Default Connect 4, adjustable based on board size
- **Two Player Game**: Player 1 (X) vs Player 2 (O)
- **Move Management**: Undo single or multiple moves
- **Game History**: View complete move history
- **Beautiful ASCII Interface**: Clean board display with borders and symbols

## Game Rules

1. Players take turns dropping pieces into columns
2. Pieces fall to the lowest available position in the column
3. Win by connecting the required number of pieces in a row (horizontally, vertically, or diagonally)
4. Game ends when someone wins or the board is full (draw)

## Building and Running

### Prerequisites
- GCC/G++ compiler
- Make utility

### Build
```bash
make
```

### Run
```bash
make run
# or
./liguequant
```

### Clean
```bash
make clean
```

## Game Interface

The game presents a menu-driven interface with the following options:

1. **Play a move**: Enter a column number (1-N) to drop your piece
2. **Undo last move**: Remove the most recent move
3. **Undo multiple moves**: Remove several moves at once
4. **Reset game**: Start a new game with current rules
5. **Change game rules**: Modify board size and win condition (only when no moves played)
6. **View game history**: See all moves played in the current game
7. **Quit game**: Exit the application

## Board Display

- **X**: Player 1 pieces
- **O**: Player 2 pieces
- **Empty spaces**: Available positions
- **Column numbers**: Displayed at the top for easy reference
- **Row numbers**: Displayed on the left side

## Example Gameplay

```
Current Board:
     1  2  3  4  5  6  7
  ┌──┬──┬──┬──┬──┬──┬──┐
 7│  │  │  │  │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 6│  │  │  │  │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 5│  │  │  │  │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 4│  │  │  │  │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 3│  │  │  │X │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 2│  │  │  │O │  │  │  │
  ├──┼──┼──┼──┼──┼──┼──┤
 1│  │  │  │X │  │  │  │
  └──┴──┴──┴──┴──┴──┴──┘

Round: 5
Current Player: Player 2 (O)
```

## File Structure

- `src/LigueQuant.h` - Main game interface header
- `src/LigueQuant_i.c` - Game logic implementation
- `src/LigueQuant_ctx.h` - Game context and constants
- `src/LigueQuant_ctx_i.c` - Context implementation
- `src/main.cpp` - Graphical user interface
- `Makefile` - Build configuration

## Technical Details

The game is implemented in C with a C++ interface layer:

- **Core Logic**: Written in C for efficiency and formal verification compatibility
- **User Interface**: Written in C++ for better string handling and I/O
- **Memory Management**: Static allocation for predictable behavior
- **Error Handling**: Comprehensive validation of all user inputs

## Customization

You can modify the default game settings by changing the game rules through the interface, or by modifying the constants in `LigueQuant_ctx.h`:

- `LigueQuant_ctx__minn`: Minimum board dimension (default: 4)
- `LigueQuant_ctx__maxx`: Maximum board dimension (default: 20)

## Contributing

This project is part of a formal methods implementation. Please ensure any changes maintain the formal specification compatibility.
