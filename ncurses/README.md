# Maze Generator/Solver (ncurses)

Simple maze generator and solver with a live ncurses visualisation.

## Build & run
- Build: `make`
- Run: `./generator [loops] [speed_us] [flags]`
  - `loops`: how many mazes to run (default 999)
  - `speed_us`: microseconds between draw steps (default 1000)
  - `--stats` to start with the state panel visible (hidden by default)

## Ncurses features
- **State panel (right side):** seed, maze size, gen/solve steps, backtracks, depth, timings, stack depth, history index. Hidden by default; toggle with `h` while stepping (or start visible via `--stats`). Maze width shrinks only when panel is visible.
- **Step mode (`--step`):** pause after each solver action.
  - `space`/`n`: next step
  - `b`: step back through recorded history (rewind view only)
  - `c`: toggle run/step
  - `f`: fast-forward to end of solve, then wait for a key before next maze
  - `h`: hide/show state panel
- **Backtracking stack view:** last entries displayed in the panel to follow recursion depth.
- **History rewind:** solver draws are logged; rewinding replays from a snapshot.
- **Seeded runs:** each maze uses a recorded seed shown in the panel.
- **Visual generation:** colorized carve/backtrack animation with speed control.

Flags can be combined (e.g., `./generator 1 20000 --step`). Press `Ctrl+C` to quit early.
