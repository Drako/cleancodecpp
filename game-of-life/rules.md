Program usage is "program {width} {height}".

The world then consists of width*height cells, that can be either alive or dead.

At startup the world is populated at random with living cells.

For practicality the game world can not be smaller than 100 cells
and width and height cannot be less then 3 individually,
so a single line with 100 cells would also be invalid.

Also even though the starting population is chosen at random,
there must be a minimum of 10% living cells and a maximum of 90%.

After the initial start, the world progresses in steps.
At runtime a step is triggered by hitting Enter.

On each step, the world progress according to the following rules:
 * A dead cell with 3 living neighbors becomes alive.
 * A living cell with less than 2 living neighbors dies of loneliness.
 * A living cell with more than 3 living neighbors dies of overpopulation.
 * Other cells don't change their status.

After initialization and after each step
the world should be rendered to the console.
