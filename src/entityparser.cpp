#include "entityparser.h"

using namespace std;

Attack parseAttack(int id) {
  Json::Value root; // The root element
  Json::Reader reader; // The reader... that reads

  bool parsingSuccessful = reader.parse("./json/attacks.json", root);
  if (!parsingSuccessful) {
    // Print error
    cout << "Failed to parse the attacks" << endl
	  << reader.getFormattedErrorMessages();
  }

  // Iterate trough the attacks
  for (unsigned int i = 0; i < root.size(); i++) {
    cout << "Debug: " << root[i].asString() << endl;
  }

  Attack attack;

  // TODO: Fill the data pls

  return attack;
}
