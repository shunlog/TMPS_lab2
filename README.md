# SOLID Principles

## Author: Balan Artiom

----

## Objectives:

1. Get familiar with the creational Design Patterns;
2. Choose a specific domain;
3. Implement at least 2 CDPs for the specific domain (or 4 for a 10);

## Used design patterns

1. Factory method pattern,
2. Prototype pattern,
3. Singleton pattern, 
4. Builder pattern.

## Implementation

I've designed an RPG game using the four design patterns.

Running it starts two games on different difficulties.
The number of monsters spawned depends on the difficulty.

```
$ make run                                                                                                                        2 ↵
g++ -Wall -fdiagnostics-color -g main.cpp -o main
./main
Game started!

There are no monsters on the Easy difficulty.

Game ended!

Game started!

Spawning monsters for Medium difficulty.

Monster was created (health = 10, speed = 2)
Zombie was built.
Info on monster: name = Zombie, weapon = Shovel

Monster was created (health = 8, speed = 5)
Vampire was built.
Info on monster: name = Vampire, weapon = Fangs

Monster is being cloned...
Monster was created (health = 10, speed = 2)
Info on monster: name = , weapon = 

Game ended!
```


## Conclusions

