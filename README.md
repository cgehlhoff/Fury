# Fury

Fury is a C++ chess engine written from scratch. I’m building it as a personal project to learn engine development. It uses bitboards, supports the UCI protocol, and works with chess GUIs such as En Croissant.

## Features

- Bitboard-based board representation with make/unmake move
- Legal move generation: castling, en passant, and promotions
- FEN parsing
- Negamax search with material-only evaluation
- UCI protocol support

## Correctness

Move generation is verified with perft against the published node counts.

| Position | Depth | Nodes |
|----------|-------|-------|
| Start position | 1 | 20 |
| Start position | 2 | 400 |
| Start position | 3 | 8,902 |
| Start position | 4 | 197,281 |
| Start position | 5 | 4,865,609 |
| Start position | 6 | 119,060,324 |
| Kiwipete | 1 | 48 |
| Kiwipete | 2 | 2,039 |
| Kiwipete | 3 | 97,862 |
| Kiwipete | 4 | 4,085,603 |

## Build

Requires Git, CMake, and a C++ compiler. Tested on Windows with MSVC.

```
git clone https://github.com/cgehlhoff/Fury.git
cd Fury
cmake -B build
cmake --build build --config Release
```

The executable is built at `build\Release\Fury.exe`.

Visual Studio project files are also included if you prefer to open `Fury.slnx` directly.

## Usage

Fury speaks UCI, so you can add it to any UCI-compatible GUI. In En Croissant: Engines → Add new → select `Fury.exe`. Search depth is currently fixed at 4 plies; the go parameters (depth, time controls) are ignored.

## Roadmap

- [ ] Alpha-beta pruning and move ordering
- [ ] Quiescence search
- [ ] Better evaluation (piece-square tables, then possibly NNUE)
- [ ] Time management and `go` clock handling
- [ ] Lichess bot integration

## About

Built by Craig Gehlhoff while learning C++ and chess engine development.

## License

MIT. See [LICENSE](LICENSE).
