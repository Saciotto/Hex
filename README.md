# Hex

Hex game implentation for CLI.
AI uses montecarlo algorithm to try to win.

The player always plays first.

## Build

```
cmake .
cmake --build .
```

## Game screen

```
   ##################
   ##   Hex game   ##
   ##################

The player tries to make a path from top to bottom, while the
AI tries to make a path from left to right.

   1   2   3   4   5   6   7
1  . - . - . - . - . - . - .
    \ / \ / \ / \ / \ / \ / \
2    . - . - . - . - . - . - .
      \ / \ / \ / \ / \ / \ / \
3      . - . - . - X - . - . - .
        \ / \ / \ / \ / \ / \ / \
4        . - . - X - . - . - . - .
          \ / \ / \ / \ / \ / \ / \
5          . - . - O - . - . - O - .
            \ / \ / \ / \ / \ / \ / \
6            . - . - . - . - . - . - .
              \ / \ / \ / \ / \ / \ / \
7              . - . - . - . - . - . - .

Type a row and a col (e.g.: 2 5):
```