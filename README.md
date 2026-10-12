# countdownNumbers
Checks if there is a way to solve a numbers round of the game show Countdown (or the comedy version 8 Out Of 10 Cats Does Countdown).

After cloning repository, run 

```$ gcc ./countdownNumbers.c -o countdownNumbers```

to build the program. To then run the program, use

```$ ./countdownNumbers```

to be prompted to enter your numbers separated by spaces, and then your target.

## Example

```
$ gcc -Wall countdownNumbers.c -o countdownNumbers
$ ./countdownNumbers
Numbers: 6 10 1 25 50 75
Numbers chosen are 6 10 1 25 50 75
Target: 222
Target is 222
Solution found:
75 - 1 = 74
6 * 74 = 444
444 * 25 = 11100
11100 / 50 = 222
```
