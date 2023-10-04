#include <iostream>
// #include <gtest/gtest.h>
#include "GamePiece.hpp"
#include "GameState.hpp"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

template<typename T>
void ASSERT_EQ(T thing1, T thing2){
    bool test = (thing1 == thing2);
    cout << std::boolalpha;
    cout << thing1 << " == " << thing2 << " " << test << endl;
}

template<typename T, typename T2>
void ASSERT_EQ(T thing1, T2 thing2){
    bool test = (thing1 == thing2);
    cout << std::boolalpha;
    cout << thing1 << " == " << thing2 << " " << test << endl;
}


int main(){
     GameState state;

    const std::vector<std::string> players =
      { "Bonesagus", "Criamon", "Diedne", "Mercere", "Tremere", "Tytalus"};

    std::vector<GamePiece*> pieces;

    // Create ten of each type for each group.
    for (const std::string & name : players) {
        for (int count = 0; count < 10; ++count) {
            pieces.push_back( new GamePiece(name,"Warrior",&state) );
            pieces.push_back( new GamePiece(name,"Scout",&state) );
            pieces.push_back( new GamePiece(name,"Wizard",&state) );
        }
    }

    ASSERT_EQ(state.NumPieces(), 180) ;// "Incorrect total piece count in state.";
    ASSERT_EQ(state.NumPieces("Bonesagus"), 30) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Mercere"), 30) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Tytalus"), 30) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Criamon", "Warrior"), 10) ;// "Incorrect Warrior count for individual player.";
    ASSERT_EQ(state.NumPieces("Diedne", "Scout"), 10) ;// "Incorrect Scout count for individual player.";
    ASSERT_EQ(state.NumPieces("Tremere", "Wizard"), 10) ;// "Incorrect Wizard count for individual player.";
    ASSERT_EQ(state.NumPieces("Unknown"), 0) ;// "Non-zero total piece count for unknown player.";
    ASSERT_EQ(state.NumPieces("Nobody","Scout"), 0) ;// "Non-zero total piece count for unknown player.";
    ASSERT_EQ(state.NumPieces("Mercere","NotAPiece"), 0) ;// "Non-zero total piece count for unknown piece type.";

    // Remove some arbitrary pieces.
    int remove_ids[] = {   8, 10, 22, 32, 40, 44, 45, 62, 68, 69,
                          72, 73, 78, 79, 84, 91, 92, 94,106,107,
                         121,126,127,130,140,142,147,158,164,172 };

    for (int id : remove_ids) {
        delete pieces.at(id);
        pieces.at(id) = nullptr;
    }

    ASSERT_EQ(state.NumPieces(), 150) ;// "Incorrect total piece count in state.";
    ASSERT_EQ(state.NumPieces("Bonesagus"), 27) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Mercere"), 25) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Tytalus"), 27) ;// "Incorrect total piece count for individual player.";
    ASSERT_EQ(state.NumPieces("Criamon", "Warrior"), 9) ;// "Incorrect Warrior count for individual player.";
    ASSERT_EQ(state.NumPieces("Diedne", "Scout"), 8) ;// "Incorrect Scout count for individual player.";
    ASSERT_EQ(state.NumPieces("Tremere", "Wizard"), 9) ;// "Incorrect Wizard count for individual player.";

    ASSERT_EQ(state.NumPieces("Unknown"), 0) ;// "Non-zero total piece count for unknown player.";
    ASSERT_EQ(state.NumPieces("Nobody","Scout"), 0) ;// "Non-zero total piece count for unknown player.";
    ASSERT_EQ(state.NumPieces("Mercere","NotAPiece"), 0) ;// "Non-zero total piece count for unknown piece type.";


    // Final cleanup
    for (auto ptr : pieces) delete ptr;
}

// int main(){
//  GameState state;

// GamePiece base_warrior("Base", "Warrior", &state);
// GamePiece base_scout("Base", "Scout", &state);
// GamePiece base_wizard("Base", "Wizard", &state);

// GamePiece extra1(base_warrior);
// GamePiece extra2(base_scout);
// GamePiece extra3(base_wizard);

// std::stringstream ss;
// ss ;// base_warrior;
// ASSERT_EQ(ss.str(), "(Base,Warrior,5,2)") ;// "Printing a Warrior's info.";

// ss.str(""); ss ;// base_scout;
// ASSERT_EQ(ss.str(), "(Base,Scout,1,8)") ;// "Printing a Scout's info.";

// ss.str(""); ss ;// base_wizard;
// ASSERT_EQ(ss.str(), "(Base,Wizard,2,12)") ;// "Printing a Wizard's info (2 friendly, no enemies).";

// extra1 = GamePiece("Enemy", "Wizard", &state);

// ss.str(""); ss ;// base_wizard;
// ASSERT_EQ(ss.str(), "(Base,Wizard,2,11)") ;// "Printing a Wizard's info (2 friendly, 1 enemy).";

// extra2 = extra1;
// extra3 = GamePiece("Enemy", "Wizard", &state);

// ss.str(""); ss ;// base_wizard;
// ASSERT_EQ(ss.str(), "(Base,Wizard,1,9)") ;// "Printing a Wizard's info (1 friendly, 3 enemies).";

// ss.str(""); ss ;// extra3;
// ASSERT_EQ(ss.str(), "(Enemy,Wizard,3,11)") ;// "Printing an enemy Wizard's info (1 friendly, 3 enemies).";

// ss.str(""); ss ;// "BEFORE" ;// extra3 ;// "AFTER";
// ASSERT_EQ(ss.str(), "BEFORE(Enemy,Wizard,3,11)AFTER") ;// "OStreams operator;// needs to return a reference to itself.";
// }
// int main(){
//      GameState state;

//     // Parameterized constructors
//     GamePiece piece1("Charles", "Warrior", &state);
//     GamePiece piece2("Josh", "Scout", &state);
//     GamePiece piece3("Sparty", "Wizard", &state);

//     ASSERT_EQ(piece1.GetPlayer(), "Charles") ;// "Incorrect player name in piece";
//     ASSERT_EQ(piece2.GetPlayer(), "Josh") ;// "Incorrect player name in piece";
//     ASSERT_EQ(piece3.GetPlayer(), "Sparty") ;// "Incorrect player name in piece";
//     ASSERT_EQ(piece1.GetType(), "Warrior") ;// "Incorrect piece type returned";
//     ASSERT_EQ(piece2.GetType(), "Scout") ;// "Incorrect piece type returned";
//     ASSERT_EQ(piece3.GetType(), "Wizard") ;// "Incorrect piece type returned";

//     // Copy constructors
//     GamePiece piece4(piece1);
//     GamePiece piece5(piece2);
//     GamePiece piece6(piece3);

//     ASSERT_EQ(piece4.GetPlayer(), "Charles") ;// "Incorrect player name copied into piece";
//     ASSERT_EQ(piece5.GetPlayer(), "Josh") ;// "Incorrect player name copied into piece";
//     ASSERT_EQ(piece6.GetPlayer(), "Sparty") ;// "Incorrect player name copied into piece";
//     ASSERT_EQ(piece4.GetType(), "Warrior") ;// "Incorrect piece type returned for copied piece";
//     ASSERT_EQ(piece5.GetType(), "Scout") ;// "Incorrect piece type returned for copied piece";
//     ASSERT_EQ(piece6.GetType(), "Wizard") ;// "Incorrect piece type returned for copied piece";

//     ASSERT_EQ(piece1.GetPlayer(), "Charles") ;// "Incorrect player name in original piece after copy";
//     ASSERT_EQ(piece2.GetPlayer(), "Josh") ;// "Incorrect player name in original piece after copy";
//     ASSERT_EQ(piece3.GetPlayer(), "Sparty") ;// "Incorrect player name in original piece after copy";
//     ASSERT_EQ(piece1.GetType(), "Warrior") ;// "Incorrect piece type in original piece after copy";
//     ASSERT_EQ(piece2.GetType(), "Scout") ;// "Incorrect piece type in original piece after copy";
//     ASSERT_EQ(piece3.GetType(), "Wizard") ;// "Incorrect piece type in original piece after copy";
// }

// int main(){
//  GameState state;

//     GamePiece piece1("Hufflepuff", "Wizard", &state);
//     ASSERT_EQ(piece1.GetPower(), 1) ;// "Incorrect wizard power; one wizard";

//     GamePiece piece2(piece1);
//     ASSERT_EQ(piece2.GetPower(), 2) ;// "Incorrect wizard power for new wizard; two wizards";
//     ASSERT_EQ(piece1.GetPower(), 2) ;// "Incorrect wizard power for original wizard; two wizards";

//     GamePiece piece3("Hufflepuff", "Wizard", &state);
//     ASSERT_EQ(piece3.GetPower(), 3) ;// "Incorrect wizard power for third wizard (created with parameterized constructor";
//     ASSERT_EQ(piece2.GetPower(), 3) ;// "Incorrect wizard power for second wizard; three wizards";
//     ASSERT_EQ(piece1.GetPower(), 3) ;// "Incorrect wizard power for original wizard; three wizards";

//     {
//         GamePiece piece4(piece2);
//         GamePiece piece5(piece3);

//         ASSERT_EQ(piece5.GetPower(), 5) ;// "Incorrect wizard power with five wizards.";
//         ASSERT_EQ(piece4.GetPower(), 5) ;// "Incorrect wizard power with five wizards.";
//         ASSERT_EQ(piece3.GetPower(), 5) ;// "Incorrect wizard power with five wizards.";
//         ASSERT_EQ(piece2.GetPower(), 5) ;// "Incorrect wizard power with five wizards.";
//         ASSERT_EQ(piece1.GetPower(), 5) ;// "Incorrect wizard power with five wizards.";
//     }

//     ASSERT_EQ(piece3.GetPower(), 3) ;// "Incorrect wizard power for three wizards (after two removed; likely problem with destructor)";
//     ASSERT_EQ(piece2.GetPower(), 3) ;// "Incorrect wizard power for three wizards (after two removed; likely problem with destructor)";
//     ASSERT_EQ(piece1.GetPower(), 3) ;// "Incorrect wizard power for three wizards (after two removed; likely problem with destructor)";

//     GamePiece piece6("Hufflepuff", "Scout", &state);

//     ASSERT_EQ(piece3.GetPower(), 3) ;// "Non-wizard pieces should not affect wizard power.";
//     ASSERT_EQ(piece2.GetPower(), 3) ;// "Non-wizard pieces should not affect wizard power.";
//     ASSERT_EQ(piece1.GetPower(), 3) ;// "Non-wizard pieces should not affect wizard power.";
    

// int main(){
//     GameState state;

//     GamePiece thor("Heroes", "Warrior", &state);
//     GamePiece hulk("Heroes", "Warrior", &state);
//     GamePiece s_witch("Heroes", "Wizard", &state);
//     GamePiece hawkeye("Heroes", "Scout", &state);

//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;

//     ASSERT_EQ(thor, hulk) ;// "Comparison test";

//     ASSERT_EQ(thor == hulk, true) ;// "Comparison test";
//     ASSERT_EQ(thor <= hulk, true) ;// "Comparison test";
//     ASSERT_EQ(thor >= hulk, true) ;// "Comparison test";
//     cout ;// 1 ;// endl;
//     ASSERT_EQ(thor != hulk, false) ;// "Comparison test";
//     ASSERT_EQ(thor < hulk, false) ;// "Comparison test";
//     ASSERT_EQ(thor > hulk, false) ;// "Comparison test";

//     cout ;// 2 ;// endl;
//     ASSERT_EQ(thor == s_witch, false) ;// "Comparison test";
//     ASSERT_EQ(thor < s_witch, false) ;// "Comparison test";
//     ASSERT_EQ(thor <= s_witch, false) ;// "Comparison test";
//     cout ;//3;//endl;

//     ASSERT_EQ(thor != s_witch, true) ;// "Comparison test";
//     ASSERT_EQ(thor > s_witch, true) ;// "Comparison test";
//     ASSERT_EQ(thor >= s_witch, true) ;// "Comparison test";
//     cout ;//4;//endl;

//     //check
//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;
//     ASSERT_EQ(hawkeye == s_witch, false) ;// "Scout and sole wizard have same power, but wizard is faster.";
//     ASSERT_EQ(hawkeye > s_witch, false) ;// "Scout and sole wizard have same power, but wizard is faster.";
//     ASSERT_EQ(hawkeye >= s_witch, false) ;// "Scout and sole wizard have same power, but wizard is faster.";
//     cout ;// 5;//endl;

//     //check
//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;
//     ASSERT_EQ(hawkeye < s_witch, true) ;// "Scout and sole wizard have same power, but wizard is faster.";
//     ASSERT_EQ(hawkeye <= s_witch, true) ;// "Scout and sole wizard have same power, but wizard is faster.";
//     ASSERT_EQ(hawkeye != s_witch, true) ;// "Scout and sole wizard have same power, but wizard is faster.";

//     //s_witch speed should be 12
//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;
//     GamePiece agatha("Villains", "Wizard", &state);
//     GamePiece loki("Gods", "Wizard", &state);
//     GamePiece mordo("Villains", "Wizard", &state);
//     GamePiece dormammu("Villains", "Wizard", &state);
//     cout ;// 6;//endl;

//     //check
//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;
//     ASSERT_EQ(hawkeye == s_witch, true) ;// "Scout and wizard opposed by four others are tied";
    
//     ASSERT_EQ(hawkeye > s_witch, false) ;// "Scout and wizard opposed by four others are tied";
//     //check
//     ASSERT_EQ(hawkeye >= s_witch, true) ;// "Scout and wizard opposed by four others are tied";
    
//     cout ;// 7;//endl;
//     //check

//     cout ;// hawkeye ;// " vs " ;// s_witch ;// endl;
//     ASSERT_EQ(hawkeye < s_witch, false) ;// "Scout and wizard opposed by four others are tied";
//     ASSERT_EQ(hawkeye <= s_witch, true) ;// "Scout and wizard opposed by four others are tied";
//     //check
//     ASSERT_EQ(hawkeye != s_witch, false) ;// "Scout and wizard opposed by four others are tied";
    
//     cout ;//8;// endl;
//     {
//         GamePiece strange("Heroes", "Wizard", &state);

//         ASSERT_EQ(hawkeye == s_witch, false) ;// "Supported wizard always more powerful than scout.";
//         ASSERT_EQ(hawkeye > s_witch, false) ;// "Supported wizard always more powerful than scout.";
//         ASSERT_EQ(hawkeye >= s_witch, false) ;// "Supported wizard always more powerful than scout.";
//         cout ;//9;// endl;
//         ASSERT_EQ(hawkeye < s_witch, true) ;// "Supported wizard always more powerful than scout.";
//         ASSERT_EQ(hawkeye <= s_witch, true) ;// "Supported wizard always more powerful than scout.";
//         ASSERT_EQ(hawkeye != s_witch, true) ;// "Supported wizard always more powerful than scout.";

//         GamePiece nico("Heroes", "Wizard", &state);
//         GamePiece magick("Heroes", "Wizard", &state);
//         GamePiece wiccan("Heroes", "Wizard", &state);

//         ASSERT_EQ(hulk == s_witch, false) ;// "Warrior loses to Wizard supported by four others";
//         ASSERT_EQ(hulk > s_witch, false) ;// "Warrior loses to Wizard supported by four others";
//         ASSERT_EQ(hulk >= s_witch, false) ;// "Warrior loses to Wizard supported by four others";
//         cout ;// 10;//endl;
//         ASSERT_EQ(hulk < s_witch, true) ;// "Warrior loses to Wizard supported by four others";
//         ASSERT_EQ(hulk <= s_witch, true) ;// "Warrior loses to Wizard supported by four others";
//         ASSERT_EQ(hulk != s_witch, true) ;// "Warrior loses to Wizard supported by four others";

//         GamePiece pryor("Villains", "Wizard", &state);
//         GamePiece amora("Gods", "Wizard", &state);
//         GamePiece bast("Gods", "Wizard", &state);
//         GamePiece hellstrom("Villains", "Wizard", &state);
//         GamePiece blake("Villains", "Wizard", &state);
//         GamePiece cyttorak("Villains", "Wizard", &state);

//         //check
//         ASSERT_EQ(hulk == s_witch, true) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//         ASSERT_EQ(hulk > s_witch, false) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//         //check
//         ASSERT_EQ(hulk >= s_witch, true) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//         cout ;//11;//endl;

//         ASSERT_EQ(hulk < s_witch, false) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//         ASSERT_EQ(hulk <= s_witch, true) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//         ASSERT_EQ(hulk != s_witch, false) ;// "Warrior tied with Wizard supported by four and opposed by 10";
//     }

//     ASSERT_EQ(hawkeye == s_witch, true) ;// "Scout and wizard opposed by four others are tied";
//     ASSERT_EQ(hawkeye > s_witch, false) ;// "Scout and wizard opposed by four others are tied";
//     ASSERT_EQ(hawkeye >= s_witch, true) ;// "Scout and wizard opposed by four others are tied";
//     cout ;// 12;//endl;

//     ASSERT_EQ(hawkeye < s_witch, false) ;// "Scout and wizard opposed by four others are tied";
//     ASSERT_EQ(hawkeye <= s_witch, true) ;// "Scout and wizard opposed by four others are tied";
//     ASSERT_EQ(hawkeye != s_witch, false) ;// "Scout and wizard opposed by four others are tied";}

// }