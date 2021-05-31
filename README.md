# howmuch - how much will this print weight?

Usage: `howmuch <filament diameter (milimeters)> <density of filament (g/cm³)> <gcode file path>`


### Build instructions

1. Clone the repository.
2. Create a directory called Release and cd into it
3. Run `cmake .. -DCMAKE_BUILD_TYPE=Release`
4. The executable is now built and called `howmuch`.


### Prerequisites

The `neo` library (you can easily replace these functions with STD stuff), g++ or clang++ and
cmake.