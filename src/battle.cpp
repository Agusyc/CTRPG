#include "battle.h"

using namespace std;

Battle::Battle(Enemy enm, Player ply) {
  enemy = enm;
  player = ply;
}

void Battle::start(string message) {
  // Start the battle

  printMessage(message);

  printMessage(enemy.name + string(" wants to fight!"));

  // Seed the random number generator.
  srand(time(NULL));

  loop();
}

void Battle::loop() {
  // Run this loop until the user loses or wins
  while (!over) {
    if (playerTurn) {
      // Checks the user response from the menu
      switch(showMenu()) {
      case 1:
	attack();
	break;
      case 2:
	defending = true;
	printMessage("You use your shield to, like, defend yourself.");
	break;
      case 3:
	// TODO: Show items menu
	printMessage("You wanna use your stuff?");
	break;
      case 4:
	// TODO: See if player can flee
	printMessage("Chicken!", QUICK_TEXT);
	break;
      default:
	printMessage("That is not a valid option...");
	continue;
      }
    } else {
      // The enemy attacks
      attack();
    }
    // Pass to the next turn
    playerTurn = !playerTurn;
  }

  clearScreen();
}

int Battle::showMenu() {
  cout << "1. Attack" << endl << "2. Defend" << endl << "3. Item" << endl << "4. Flee" << endl << "Your choice: ";

  int choice;
  cin >> choice;

  cout << endl;

  return choice;
}

void Battle::attack() {
  unsigned int choice;
  if (playerTurn) {
    // The player attacks.
    bool exitLoop = false;
    Attack attack;

    while (!exitLoop) {
      cout << "Attacks: " << endl;

      for (unsigned int i = 0; i < player.attacks.size(); i++) {
	cout << i+1 << ". " << player.attacks.at(i).name << endl;
      }

      cout << "Your choice: ";

      cin >> choice;

      cout << endl;

      if (choice > player.attacks.size() || choice < 0) {
	printMessage("That's not a valid choice...");
	cout << endl;
	continue;
      }

      attack = player.attacks.at(choice - 1);

      if (player.mana < attack.mana) {
	printMessage("You don't have enough mana to use that attack!");
	continue;
      }

      if (player.stamina < attack.stamina) {
	printMessage("You don't have enough stamina to use that attack!");
	continue;
      }

      exitLoop = true;
    }

    // Decrease the user mana and stamina
    player.mana -= attack.mana;
    player.stamina -= attack.stamina;

    // Calculate how much damage is dealt to the enemy
    int damage = (attack.damage + attack.magicDamage + player.attack) - enemy.defense;
    
    if (damage <= 0) {
      // The attack doesn't do anything
      printMessage("Man... That attack is so lame that it doesn't do anything.");
    } else {
      // The attack is powerful enough to do something
      bool critical = false;
      // 5 % chance of a critical hit
      int randNum = rand() % 100;
      if (randNum < 5) {
	critical = true;
	damage *= 2;
      }
      
      stringstream ss;
      if (critical)
	ss << "With a critical hit, ";
      ss << "You deal " << damage << " to " << enemy.name << " with " << attack.name  << "!" << endl << "It now has " << enemy.hp - damage << " HP." << endl;
      
      printMessage(ss.str(), QUICK_TEXT);
      
      enemy.hp -= damage;
    }
  } else {
    // The enemy attacks
    stringstream ss;
    ss << enemy.name << " has to attack!";
    
    printMessage(ss.str());
    
    bool enemyAttacks = rand() % 2;
    if (enemyAttacks) {
      int randNum;
      Attack attack;
      bool exitLoop = false;
      
      // This loop ensures that the enemy doesn't choose an attack that it can't use because of mana or stamina.
      while (!exitLoop) {
	randNum = rand()%(enemy.attacks.size()-0 + 1) + 0;
	attack = enemy.attacks.at(randNum);
	
	if (enemy.mana >= attack.mana && enemy.stamina >= attack.stamina)
	  exitLoop = true;
      }
      
      // Decrease enemy's mana and stamina
      enemy.mana -= attack.mana;
      enemy.stamina -= attack.stamina;
      
      // Calculate how much damage is dealt to the player
      int damage = (attack.damage + attack.magicDamage + enemy.attack) - player.defense;
      
      if (defending)
	damage -= player.shieldDefense;
      
      if (damage <= 0) {
	// The attack doesn't do anything
	ss << enemy.name << " tries to hurt you with " << attack.name <<  "... But it can't!";
	printMessage(ss.str());
      } else {
	// The attack is powerful enough...
	bool critical = false;
	// 5 % chance of a critical hit
	randNum = rand() % 100;
	if (randNum < 5) {
	  critical = true;
	  damage *= 2;
	}
	
	ss.str("");
	ss.clear();
	
	if (critical)
	  ss << "With a critical hit, ";
	ss << enemy.name << " deals you " << damage << " with " << attack.name << "!"  << endl << "You now have " << player.hp - damage << " HP.";
	
	printMessage(ss.str(), QUICK_TEXT);
	
	player.hp -= damage;
      }
    } else {
      // The enemy decides not to attack
      printMessage("But it is resting...");
    }
  }
  
  // When the player wins
  if (enemy.hp <= 0) {
    printMessage("You win!");
    over = true;
    if (player.xp + enemy.xp < player.goal) {
      player.xp += enemy.xp;
    } else if (player.xp + enemy.xp >= player.goal) {
      stringstream ss;

      ss << "You leveled up! You are on level " << player.level + 1 << " now!";

      player.xp = player.goal - player.xp;

      printMessage(ss.str());

      player.level++;
      player.goal *= 2;

      // To let the user choose what stats to improve
      showLevelUpMenu(parsePlayer());
    }

    player = parsePlayer();
  }

  // When the enemy wins
  if (player.hp <= 0) {
    printMessage("You lose!");
    over = true;
  }
}

void Battle::showLevelUpMenu(Player originalPlayer) {
  for (int points = player.level; points != 0; points--) {
    cout << "Points: " << points << endl << "1. HP" << endl << "2. Attack" << endl << "3. Defense" << endl << "4. Shield" << endl << "5. Mana" << endl << "6. Stamina" << endl << "Your choice: ";

    int choice;

    cin >> choice;

    switch (choice) {
    case 1:
      originalPlayer.hp++;
      break;
    case 2:
      originalPlayer.attack++;
      break;
    case 3:
      originalPlayer.defense++;
      break;
    case 4:
      originalPlayer.shieldDefense++;
      break;
    case 5:
      originalPlayer.mana++;
      break;
    case 6:
      originalPlayer.stamina++;
      break;
    }
  }

  Json::Value jPlayer = getJsonPlayer();

  jPlayer["hp"] = originalPlayer.hp;
  jPlayer["attack"] = originalPlayer.attack;
  jPlayer["defense"] = originalPlayer.defense;
  jPlayer["shieldDefense"] = originalPlayer.shieldDefense;
  jPlayer["mana"] = originalPlayer.mana;
  jPlayer["stamina"] = originalPlayer.stamina;
  jPlayer["goal"] = player.goal;
  jPlayer["xp"] = player.xp;
  jPlayer["level"] = player.level;

  Json::StyledWriter writer;
  ofstream jPlayerFile("./json/player.json");
  jPlayerFile << writer.write(jPlayer);
}
