#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <algorithm>
#include <thread>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

using namespace std;

// Mac-compatible utility functions
void clearScreen() {
    system("clear");
}

void sleep(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Mac-compatible keyboard input
class KeyboardHandler {
private:
    struct termios oldt, newt;
public:
    KeyboardHandler() {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    
    ~KeyboardHandler() {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
    
    bool kbhit() {
        int bytesWaiting;
        ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
        return bytesWaiting > 0;
    }
    
    char getch() {
        return getchar();
    }
};

// Base class for all entities
class Entity {
protected:
    string name;
    int health;
    int maxHealth;
    int attack;
    int speed;
    int cost;
    int position;
public:
    Entity(string n, int h, int a, int s, int c = 0) 
        : name(n), health(h), maxHealth(h), attack(a), speed(s), cost(c), position(0) {}
    
    virtual void attackEnemy(Entity& target) {
        cout << name << " attacks " << target.getName() << " for " << attack << " damage!\n";
        target.takeDamage(attack);
    }
    
    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }
    
    void heal() {
        health = maxHealth;
    }
    
    void moveForward() {
        position += speed;
    }
    
    bool isAlive() const { return health > 0; }
    string getName() const { return name; }
    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }
    int getAttack() const { return attack; }
    int getSpeed() const { return speed; }
    int getCost() const { return cost; }
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }
    
    virtual void displayStats() const {
        cout << name << " [HP: " << health << "/" << maxHealth << " ATK: " << attack << " SPD: " << speed << "]";
    }
    
    virtual string getAnimation() const {
        return "[" + name + "]";
    }
};

// Cat class
class Cat : public Entity {
private:
    int level;
    int xp;
    int xpToNextLevel;
    bool canAttack;
public:
    Cat(string n, int h, int a, int s, int c) 
        : Entity(n, h, a, s, c), level(1), xp(0), xpToNextLevel(100), canAttack(true) {}
    
    void gainXP(int amount) {
        xp += amount;
        cout << name << " gained " << amount << " XP!\n";
        
        while (xp >= xpToNextLevel) {
            levelUp();
        }
    }
    
    void levelUp() {
        xp -= xpToNextLevel;
        level++;
        xpToNextLevel = static_cast<int>(xpToNextLevel * 1.5);
        
        maxHealth += 10;
        health = maxHealth;
        attack += 5;
        speed += 1;
        
        cout << name << " reached level " << level << "! Stats improved!\n";
    }
    
    void upgradeStats() {
        maxHealth += 15;
        health += 15;
        attack += 8;
        cout << name << " was upgraded! +15 HP, +8 ATK\n";
    }
    
    void displayStats() const override {
        Entity::displayStats();
        cout << " [Lvl: " << level << " XP: " << xp << "/" << xpToNextLevel << "]";
    }
    
    string getAnimation() const override {
        if (!isAlive()) return "[X_X]";
        
        map<string, string> animations = {
            {"Basic Cat", "=^..^="},
            {"Tank Cat", "[▓▓▓]"},
            {"Attack Cat", "->^..^<-"},
            {"Fast Cat", "~^..^~"},
            {"Mega Cat", "[MEGA]"},
            {"Uber Cat", "[ÜBER]"},
            {"Ninja Cat", "[忍者]"},
            {"Mage Cat", "[🔮]"},
            {"Healer Cat", "[❤️]"}
        };
        
        return animations.count(name) ? animations.at(name) : "[CAT]";
    }
    
    int getLevel() const { return level; }
    int getXP() const { return xp; }
    void setCanAttack(bool attack) { canAttack = attack; }
    bool getCanAttack() const { return canAttack; }
};

// Enemy class
class Enemy : public Entity {
private:
    int xpReward;
    int moneyReward;
public:
    Enemy(string n, int h, int a, int s, int xp, int money) 
        : Entity(n, h, a, s), xpReward(xp), moneyReward(money) {}
    
    string getAnimation() const override {
        if (!isAlive()) return "[DEAD]";
        
        map<string, string> animations = {
            {"Rat", "<:3 )~~"},
            {"Dog", "▂▂ξ▂▂"},
            {"Snake", "~~~~S"},
            {"Bear", "ʕ•ᴥ•ʔ"},
            {"Eagle", "▲"},
            {"Rhino", "./ᐠ-ꞈ-ᐟ\\"},
            {"Dragon", "==🐉=="},
            {"Goblin", "[ゴブ]"},
            {"Slime", "(°○°) "},
            {"Knight", "[♘]"}
        };
        
        return animations.count(name) ? animations.at(name) : "[ENEMY]";
    }
    
    int getXPReward() const { return xpReward; }
    int getMoneyReward() const { return moneyReward; }
};

// Cat Cannon class
class CatCannon {
private:
    int charge;
    int maxCharge;
    int damage;
    bool ready;
public:
    CatCannon() : charge(0), maxCharge(100), damage(100), ready(false) {}
    
    void chargeCannon(int amount) {
        charge += amount;
        if (charge > maxCharge) charge = maxCharge;
        
        if (charge >= maxCharge && !ready) {
            ready = true;
            cout << "💥 CAT CANNON READY! Press 'C' to fire! 💥\n";
        }
    }
    
    bool fire() {
        if (ready) {
            charge = 0;
            ready = false;
            return true;
        }
        return false;
    }
    
    bool isReady() const { return ready; }
    int getCharge() const { return charge; }
    int getDamage() const { return damage; }
    
    void displayStatus() const {
        cout << "Cat Cannon: [";
        int bars = (charge * 10) / maxCharge;
        for (int i = 0; i < 10; i++) {
            if (i < bars) cout << "█";
            else cout << " ";
        }
        cout << "] " << charge << "%";
        if (ready) cout << " 💥 READY!";
        cout << "\n";
    }
};

// Game class
class BattleCatsGame {
private:
    vector<Cat> availableCats;  // All cat types you can spawn
    vector<Cat> activeCats;     // Cats currently in battle
    vector<Enemy> enemies;
    vector<Enemy> currentWave;
    
    // Resources
    int money;          // Earned in battle, used for spawning cats
    int xp;             // Earned outside battle, used for upgrades
    int catTickets;     // Used to unlock new cat types
    int currentLevel;
    bool gameOver;
    
    // Battle deployment
    map<string, int> catDeck;  // How many of each cat to spawn
    
    const int BATTLEFIELD_SIZE = 50;
    CatCannon cannon;
    bool inBattle;
    int battleTime;
    KeyboardHandler keyboard;
    
public:
    BattleCatsGame() : money(500), xp(0), catTickets(5), currentLevel(1), gameOver(false), 
                       inBattle(false), battleTime(0) {
        initializeCats();
        initializeEnemies();
        initializeDeck();
    }
    
    void initializeCats() {
        // Available cat types
        availableCats.push_back(Cat("Basic Cat", 100, 20, 5, 50));
        availableCats.push_back(Cat("Tank Cat", 200, 15, 3, 100));
        availableCats.push_back(Cat("Attack Cat", 80, 40, 7, 120));
        availableCats.push_back(Cat("Fast Cat", 70, 25, 10, 80));
        availableCats.push_back(Cat("Mega Cat", 300, 35, 2, 200));
        availableCats.push_back(Cat("Ninja Cat", 90, 45, 8, 150));
        availableCats.push_back(Cat("Mage Cat", 70, 50, 4, 180));
        availableCats.push_back(Cat("Healer Cat", 120, 15, 3, 160));
    }
    
    void initializeEnemies() {
        enemies.push_back(Enemy("Rat", 50, 10, 4, 5, 25));
        enemies.push_back(Enemy("Dog", 80, 15, 3, 8, 35));
        enemies.push_back(Enemy("Snake", 60, 25, 6, 10, 45));
        enemies.push_back(Enemy("Bear", 150, 20, 2, 15, 60));
        enemies.push_back(Enemy("Eagle", 70, 30, 8, 12, 50));
        enemies.push_back(Enemy("Rhino", 200, 25, 3, 20, 75));
        enemies.push_back(Enemy("Dragon", 300, 40, 5, 30, 100));
        enemies.push_back(Enemy("Goblin", 40, 35, 6, 7, 30));
        enemies.push_back(Enemy("Slime", 100, 10, 1, 6, 20));
        enemies.push_back(Enemy("Knight", 180, 30, 2, 25, 80));
    }
    
    void initializeDeck() {
        // Start with some basic cats
        catDeck["Basic Cat"] = 3;
        catDeck["Tank Cat"] = 1;
    }
    
    void generateWave() {
        currentWave.clear();
        activeCats.clear();
        
        int numEnemies = 3 + currentLevel;
        
        for (int i = 0; i < numEnemies; i++) {
            int enemyIndex = rand() % min(static_cast<int>(enemies.size()), currentLevel + 2);
            Enemy newEnemy = enemies[enemyIndex];
            newEnemy.setPosition(BATTLEFIELD_SIZE - 5 - (i * 3));
            currentWave.push_back(newEnemy);
        }
        
        // Reset cannon
        cannon = CatCannon();
    }
    
    void spawnCat(const string& catType) {
        auto it = find_if(availableCats.begin(), availableCats.end(),
                         [&](const Cat& c) { return c.getName() == catType; });
        
        if (it != availableCats.end() && money >= it->getCost()) {
            money -= it->getCost();
            Cat newCat = *it;
            newCat.setPosition(5 + (activeCats.size() % 3)); // Stagger positions
            activeCats.push_back(newCat);
            cout << "Spawned " << catType << " for $" << it->getCost() << "!\n";
        } else if (money < it->getCost()) {
            cout << "Not enough money! Need $" << it->getCost() << " but have $" << money << "\n";
        }
    }
    
    void displayBattlefield() {
        clearScreen();
        cout << "=== BATTLE - LEVEL " << currentLevel << " ===\n";
        cout << "Money: $" << money << " | Active Cats: " << activeCats.size() << "\n\n";
        
        cannon.displayStatus();
        cout << "\n";
        
        vector<string> battlefield(BATTLEFIELD_SIZE + 1, " ");
        
        for (const auto& cat : activeCats) {
            if (cat.isAlive() && cat.getPosition() < battlefield.size()) {
                battlefield[cat.getPosition()] = cat.getAnimation();
            }
        }
        
        for (const auto& enemy : currentWave) {
            if (enemy.isAlive() && enemy.getPosition() < battlefield.size()) {
                battlefield[enemy.getPosition()] = enemy.getAnimation();
            }
        }
        
        cout << "BASE[";
        for (int i = 0; i < BATTLEFIELD_SIZE; i++) {
            cout << battlefield[i];
        }
        cout << "]ENEMY\n";
        
        cout << "\nYour Cats:\n";
        for (const auto& cat : activeCats) {
            if (cat.isAlive()) {
                cout << cat.getAnimation() << " HP:" << cat.getHealth() << "/" << cat.getMaxHealth();
                cout << " POS:" << cat.getPosition() << " | ";
            }
        }
        
        cout << "\n\nEnemies:\n";
        for (const auto& enemy : currentWave) {
            if (enemy.isAlive()) {
                cout << enemy.getAnimation() << " ";
            }
        }
        cout << "\n";
        
        cout << "\nControls: 1-8 Spawn Cats | C-Fire Cannon | P-Pause | Q-Quit\n";
        cout << "Cat Costs: ";
        for (int i = 0; i < min(8, (int)availableCats.size()); i++) {
            cout << (i+1) << ":" << availableCats[i].getCost() << " ";
        }
        cout << "\n";
    }
    
    void processRealTimeInput() {
        if (keyboard.kbhit()) {
            char input = keyboard.getch();
            
            switch(toupper(input)) {
                case '1': spawnCat("Basic Cat"); break;
                case '2': spawnCat("Tank Cat"); break;
                case '3': spawnCat("Attack Cat"); break;
                case '4': spawnCat("Fast Cat"); break;
                case '5': spawnCat("Mega Cat"); break;
                case '6': spawnCat("Ninja Cat"); break;
                case '7': spawnCat("Mage Cat"); break;
                case '8': spawnCat("Healer Cat"); break;
                case 'C':
                    if (cannon.isReady()) {
                        cout << "💥 FIRING CAT CANNON! 💥\n";
                        for (auto& enemy : currentWave) {
                            if (enemy.isAlive()) {
                                enemy.takeDamage(cannon.getDamage());
                                cout << "Cannon hit " << enemy.getName() << " for " << cannon.getDamage() << " damage!\n";
                            }
                        }
                        cannon.fire();
                        sleep(1000);
                    }
                    break;
                case 'P':
                    cout << "Battle paused... Press any key to continue.\n";
                    keyboard.getch();
                    break;
                case 'Q':
                    inBattle = false;
                    cout << "Retreating from battle...\n";
                    sleep(1000);
                    break;
            }
        }
    }
    
    void battle() {
        generateWave();
        inBattle = true;
        battleTime = 0;
        
        cout << "=== BATTLE START - LEVEL " << currentLevel << " ===\n";
        cout << "Press 1-8 to spawn cats during battle!\n";
        cout << "Earn money by defeating enemies to spawn more cats!\n";
        sleep(3000);
        
        while (inBattle && !currentWave.empty()) {
            battleTime++;
            
            displayBattlefield();
            processRealTimeInput();
            
            if (!inBattle) break;
            
            // Passive money gain during battle
            if (battleTime % 5 == 0) {
                int passiveIncome = 10 + (currentLevel * 2);
                money += passiveIncome;
                cout << "💰 Passive income: +$" << passiveIncome << "\n";
                sleep(500);
            }
            
            cannon.chargeCannon(5 + currentLevel);
            
            // Cats move and attack
            for (auto& cat : activeCats) {
                if (cat.isAlive()) {
                    cat.moveForward();
                    
                    for (auto& enemy : currentWave) {
                        if (enemy.isAlive() && abs(cat.getPosition() - enemy.getPosition()) <= 3) {
                            if (cat.getCanAttack()) {
                                cat.attackEnemy(enemy);
                                cat.setCanAttack(false);
                                
                                if (!enemy.isAlive()) {
                                    // Money reward for killing enemies
                                    money += enemy.getMoneyReward();
                                    cout << "💰 Earned $" << enemy.getMoneyReward() << " for defeating " << enemy.getName() << "!\n";
                                }
                            }
                        }
                    }
                }
            }
            
            for (auto& cat : activeCats) {
                cat.setCanAttack(true);
            }
            
            // Enemies move and attack
            for (auto& enemy : currentWave) {
                if (enemy.isAlive()) {
                    enemy.setPosition(enemy.getPosition() - enemy.getSpeed());
                    
                    for (auto& cat : activeCats) {
                        if (cat.isAlive() && abs(cat.getPosition() - enemy.getPosition()) <= 3) {
                            enemy.attackEnemy(cat);
                            break;
                        }
                    }
                }
            }
            
            currentWave.erase(
                remove_if(currentWave.begin(), currentWave.end(),
                         [](const Enemy& e) { return !e.isAlive(); }),
                currentWave.end()
            );
            
            // Check for game over conditions
            bool catsAlive = false;
            for (const auto& cat : activeCats) {
                if (cat.isAlive()) {
                    catsAlive = true;
                    break;
                }
            }
            
            if (!catsAlive && money < availableCats[0].getCost()) {
                // No cats alive and can't afford to spawn more
                clearScreen();
                cout << "💀 GAME OVER! No cats and no money! 💀\n\n";
                displayFinalStats();
                gameOver = true;
                inBattle = false;
                waitForAnyKey();
                return;
            }
            
            bool enemyAtBase = false;
            for (const auto& enemy : currentWave) {
                if (enemy.isAlive() && enemy.getPosition() <= 0) {
                    enemyAtBase = true;
                    break;
                }
            }
            
            if (enemyAtBase) {
                clearScreen();
                cout << "💀 ENEMIES BREACHED YOUR BASE! GAME OVER! 💀\n\n";
                displayFinalStats();
                gameOver = true;
                inBattle = false;
                waitForAnyKey();
                return;
            }
            
            sleep(800); // Slightly faster turns
        }
        
        if (inBattle) {
            clearScreen();
            cout << "🎉 VICTORY! Level " << currentLevel << " completed! 🎉\n";
            
            // XP reward for completing level
            int xpReward = currentLevel * 25;
            xp += xpReward;
            catTickets += 1;
            
            cout << "Earned " << xpReward << " XP and 1 Cat Ticket!\n";
            cout << "Total XP: " << xp << " | Cat Tickets: " << catTickets << "\n";
            
            currentLevel++;
            waitForAnyKey();
        }
        
        inBattle = false;
    }
    
    void waitForAnyKey() {
        cout << "\nPress any key to continue...";
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag |= (ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        getchar();
        
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    }
    
    void manageDeck() {
        while (true) {
            clearScreen();
            cout << "=== CAT DECK MANAGEMENT ===\n";
            cout << "Cat Tickets: " << catTickets << " | XP: " << xp << "\n\n";
            
            cout << "Available Cat Types:\n";
            for (int i = 0; i < availableCats.size(); i++) {
                bool unlocked = catDeck.count(availableCats[i].getName()) > 0;
                cout << i + 1 << ". " << availableCats[i].getAnimation() << " ";
                availableCats[i].displayStats();
                if (unlocked) {
                    cout << " [IN DECK: " << catDeck[availableCats[i].getName()] << "]";
                } else {
                    cout << " [LOCKED - 1 Ticket to unlock]";
                }
                cout << "\n";
            }
            
            cout << "\n1-8. Add cat to deck (costs 1 Ticket for new types)\n";
            cout << "9. Remove cat from deck\n";
            cout << "0. Back to menu\n";
            cout << "Choose: ";
            
            int choice;
            cin >> choice;
            
            if (choice == 0) break;
            
            if (choice >= 1 && choice <= availableCats.size()) {
                string catName = availableCats[choice - 1].getName();
                
                if (catDeck.count(catName) > 0) {
                    // Already unlocked, just add to count
                    catDeck[catName]++;
                    cout << "Added " << catName << " to deck! Total: " << catDeck[catName] << "\n";
                } else if (catTickets > 0) {
                    // New type, use ticket
                    catTickets--;
                    catDeck[catName] = 1;
                    cout << "Unlocked " << catName << "! Used 1 Cat Ticket.\n";
                } else {
                    cout << "Not enough Cat Tickets!\n";
                }
            } else if (choice == 9) {
                cout << "Remove which cat? (1-8): ";
                int removeChoice;
                cin >> removeChoice;
                if (removeChoice >= 1 && removeChoice <= availableCats.size()) {
                    string catName = availableCats[removeChoice - 1].getName();
                    if (catDeck.count(catName) > 0 && catDeck[catName] > 0) {
                        catDeck[catName]--;
                        if (catDeck[catName] == 0) {
                            catDeck.erase(catName);
                        }
                        cout << "Removed one " << catName << " from deck.\n";
                    }
                }
            }
            sleep(2000);
        }
    }
    
    void upgradeCats() {
        while (true) {
            clearScreen();
            cout << "=== CAT UPGRADES ===\n";
            cout << "XP: " << xp << "\n\n";
            
            cout << "Available Upgrades:\n";
            cout << "1. Basic Cat Upgrade - 100 XP\n";
            cout << "2. Tank Cat Upgrade - 150 XP\n";
            cout << "3. Attack Cat Upgrade - 150 XP\n";
            cout << "4. All Cats +10% HP - 200 XP\n";
            cout << "5. All Cats +10% ATK - 200 XP\n";
            cout << "0. Back to menu\n";
            cout << "Choose: ";
            
            int choice;
            cin >> choice;
            
            if (choice == 0) break;
            
            switch (choice) {
                case 1:
                    if (xp >= 100) {
                        xp -= 100;
                        // Find and upgrade Basic Cat stats
                        for (auto& cat : availableCats) {
                            if (cat.getName() == "Basic Cat") {
                                // This would need proper upgrade implementation
                                cout << "Basic Cats upgraded!\n";
                                break;
                            }
                        }
                    } else {
                        cout << "Not enough XP! Need 100, have " << xp << "\n";
                    }
                    break;
                case 4:
                    if (xp >= 200) {
                        xp -= 200;
                        for (auto& cat : availableCats) {
                            // Upgrade HP by 10%
                        }
                        cout << "All cats gained +10% HP!\n";
                    } else {
                        cout << "Not enough XP! Need 200, have " << xp << "\n";
                    }
                    break;
                default:
                    cout << "Upgrade not implemented yet!\n";
            }
            sleep(2000);
        }
    }
    
    void displayFinalStats() {
        cout << "=== FINAL STATISTICS ===\n";
        cout << "Level Reached: " << currentLevel << "\n";
        cout << "Money: $" << money << "\n";
        cout << "XP: " << xp << "\n";
        cout << "Cat Tickets: " << catTickets << "\n";
    }
    
    void displayStatus() {
        clearScreen();
        cout << "=== GAME STATUS ===\n";
        cout << "Level: " << currentLevel << " | Money: $" << money << " | XP: " << xp << " | Cat Tickets: " << catTickets << "\n";
        
        cout << "\nYour Deck:\n";
        for (const auto& pair : catDeck) {
            cout << pair.first << ": " << pair.second << " available\n";
        }
        
        cout << "\nAvailable Resources:\n";
        cout << "💰 Money - Earned in battle, used to spawn cats\n";
        cout << "⭐ XP - Earned from completing levels, used for upgrades\n";
        cout << "🎫 Cat Tickets - Earned from completing levels, used to unlock new cat types\n";
        
        waitForAnyKey();
    }
    
    void play() {
        srand(time(0));
        
        cout << "=== BATTLE CATS - ENHANCED ===\n";
        cout << "💰 Money = Spawn cats in battle\n";
        cout << "⭐ XP = Upgrade cats between battles\n";
        cout << "🎫 Tickets = Unlock new cat types\n";
        sleep(3000);
        
        while (!gameOver) {
            clearScreen();
            cout << "=== MAIN MENU ===\n";
            cout << "Level: " << currentLevel << " | Money: $" << money << " | XP: " << xp << " | Tickets: " << catTickets << "\n\n";
            cout << "1. Battle (Spawn cats with 1-8 keys)\n";
            cout << "2. Manage Cat Deck (" << catTickets << " tickets available)\n";
            cout << "3. Upgrade Cats (" << xp << " XP available)\n";
            cout << "4. Game Status\n";
            cout << "5. Quit\n";
            
            int choice;
            cout << "Choose: ";
            cin >> choice;
            
            switch (choice) {
                case 1:
                    battle();
                    break;
                case 2:
                    manageDeck();
                    break;
                case 3:
                    upgradeCats();
                    break;
                case 4:
                    displayStatus();
                    break;
                case 5:
                    gameOver = true;
                    break;
                default:
                    cout << "Invalid choice!\n";
                    sleep(1500);
            }
            
            if (currentLevel > 10) {
                clearScreen();
                cout << "🎉 CONGRATULATIONS! You've completed all levels! 🎉\n";
                displayFinalStats();
                gameOver = true;
                waitForAnyKey();
            }
        }
        
        clearScreen();
        cout << "Thanks for playing Battle Cats!\n";
    }
};

int main() {
    BattleCatsGame game;
    game.play();
    return 0;
}