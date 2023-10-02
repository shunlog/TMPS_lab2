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

To run the game, you need a `GameManager`, which is a **Singleton**,
then call its `startGame(diff)` method with the appropriate difficulty.
The number of monsters spawned depends on the difficulty.

For example, this code will start two games on different difficulties:

``` c++
GameManager& gameManager = GameManager::getInstance();

gameManager.startGame(Difficulty::Easy);
gameManager.endGame();

gameManager.startGame(Difficulty::Medium);
gameManager.endGame();
```

In the `Easy` difficulty, no monsters will spawn.
In the `Medium` difficulty, we will spawn a zombie and a vampire, who are simply instances of the `Monster` class, using the **Builder pattern**.
Then, we use the zombie to create a zombie spawner, which we then use to make an exact clone of it, but without its weapons.
This uses the **Prototype pattern**, the zombie being the prototype.

To handle the different behaviors depending on the game difficulty,
we use the **Factory method pattern**.
`ILevel` acts as the creator interface, which is implemented by `EasyLevel` and `MediumLevel`.
Instead of "creating a product" as the common example goes, here we're starting a level by calling `spawnMonsters()`.
The `GameManager` has the role of the "creator":
given a difficulty, it obtains the correct level class by calling `LevelFactory.getLevel(difficulty)`, then uses it to spawn the monsters.

Here's what the output for this program looks like:
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

I've used 4 creational patterns for a very contrived example of a game.
It wasn't fun at all.
