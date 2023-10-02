#include <iostream>
#include <string>
#include <vector>

class Entity
{
public:
    virtual ~Entity() {}
    virtual Entity* clone() = 0;

    virtual void displayInfo() {};
};

class Monster : public Entity {
public:
    Monster(int health, int speed)
        : health_(health),
          speed_(speed)
        {
            std::cout << "Monster was created (health = " << health << ", speed = " << speed << ")" << std::endl;
        }

    virtual Entity* clone()
        {
            std::cout << "Monster is being cloned..." << std::endl;
            return new Monster(health_, speed_);
        }

    void displayInfo() {
        std::cout << "Info on monster: name = " << name << ", weapon = " << weapon << std::endl;
    }

    std::string name;
    std::string weapon;
private:
    int health_;
    int speed_;
};

// Prototype pattern
class Spawner
{
public:
    Spawner(Entity* prototype)
        : prototype_(prototype)
        {}

    Entity* spawnEntity()
        {
            return prototype_->clone();
        }

private:
    Entity* prototype_;
};


// Builder pattern
class MonsterBuilder {
public:
    virtual void buildName() = 0;
    virtual void buildWeapon() = 0;
    virtual Monster* getResult() = 0;
};

class ZombieBuilder : public MonsterBuilder {
private:
    Monster* monster;

public:
    ZombieBuilder() {
        monster = new Monster(10, 2);
    }

    void buildName() override {
        monster->name = "Zombie";
    }

    void buildWeapon() override {
        monster->weapon = "Shovel";
    }

    Monster* getResult() override {
        std::cout << "Zombie was built." << std::endl;
        return monster;
    }
};

class VampireBuilder : public MonsterBuilder {
private:
    Monster* monster;

public:
    VampireBuilder() {
        monster = new Monster(8, 5);
    }

    void buildName() override {
        monster->name = "Vampire";
    }

    void buildWeapon() override {
        monster->weapon = "Fangs";
    }

    Monster* getResult() override {
        std::cout << "Vampire was built." << std::endl;
        return monster;
    }
};

class MonsterDirector {
public:
    Monster* createMonster(MonsterBuilder* builder) {
        builder->buildName();
        builder->buildWeapon();
        return builder->getResult();
    }
};


// Factory method pattern
class ILevel {
public:
    virtual void spawnMonsters() = 0;
    virtual ~ILevel() {}
};

class EasyLevel : public ILevel {
public:
    void spawnMonsters() override {
        std::cout << "There are no monsters on the Easy difficulty.\n\n" ;
    }
};

class MediumLevel : public ILevel {
public:
    void spawnMonsters() override {
        std::cout << "Spawning monsters for Medium difficulty.\n\n" ;

        // Builder pattern
        MonsterDirector director;

        MonsterBuilder* zombieBuilder = new ZombieBuilder();
        Monster* zombie = director.createMonster(zombieBuilder);
        zombie->displayInfo();
        std::cout << std::endl;

        MonsterBuilder* vampireBuilder = new VampireBuilder();
        Monster* vampire = director.createMonster(vampireBuilder);
        vampire->displayInfo();
        std::cout << std::endl;

        // Prototype pattern
        Entity* monsterPrototype = zombie;
        Spawner* monsterSpawner = new Spawner(monsterPrototype);
        Entity* monsterClone = monsterSpawner->spawnEntity();
        monsterClone->displayInfo();
        std::cout << std::endl;
    }
};

enum class Difficulty {
    Easy,
    Medium
};

class LevelFactory {
public:
    ILevel* getLevel(Difficulty type) {
        switch (type) {
        case Difficulty::Easy:
            return new EasyLevel();
        case Difficulty::Medium:
            return new MediumLevel();
        default:
            throw std::invalid_argument("Unsupported Difficulty");
        }
    }
};


// Singleton Pattern
class GameManager {
public:
    static GameManager& getInstance() {
        static GameManager instance;
        return instance;
    }

    void startGame(Difficulty difficulty) {
        std::cout << "Game started!\n" << std::endl;

        LevelFactory factory;
        ILevel* level = factory.getLevel(difficulty);
        level->spawnMonsters();
    }

    void endGame() {
        std::cout << "Game ended!\n" << std::endl;
    }

private:
    GameManager() {} // Private constructor to prevent external instantiation
    GameManager(const GameManager&) = delete; // Disallow copying
    GameManager& operator=(const GameManager&) = delete; // Disallow assignment
};


int main() {
    // Singleton Pattern
    GameManager& gameManager = GameManager::getInstance();

    gameManager.startGame(Difficulty::Easy);
    gameManager.endGame();

    gameManager.startGame(Difficulty::Medium);
    gameManager.endGame();
    return 0;
}
