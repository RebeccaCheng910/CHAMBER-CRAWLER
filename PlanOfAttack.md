Due Date 1: Friday, November 25

Member : Ariel Ji, Rebecca Cheng, Paul Zhao

Breakdown of Project :
1. Write header files for all classes Estimate: 8h, Nov. 25, 2016 Member: All

Implement the basic display of the game Initializing the floor by reading in from a file Output default layout of the floor (including cells & passage & stairs & chambers) Implement Floor, Chamber and Object Class Implement Textdisplay Class Implement main.cc which provides commands to print the floor Estimate: 8h, Nov. 26, 2016 Member: All

Create general purpose player character, enemies and items Generate PC, Enemies, Items and display on the floor Implement PC, Enemy, Items class with no special type Add methods to Floor class which randomly places a PC, enemies and items on the floor Using Observer Pattern, display the generated objects on the floor Implement main.cc to provide comand asking users to choose a player character Estimate: 5h, Nov. 26, 2016 Member: Ariel Ji, Rebecca Cheng

Get movement for these generalized versions Implement move functionalities for PC (player directed) and Enemy (randomly assigned)
Add move() method to Floor and Object class Using Observer Pattern, display movements of PC and Enemies and display hints when there exist enemies or items within 1 radius block of the PC Estimate: 5h, Nov. 27, 2016 Member: Paul Zhao & Ariel Ji

Design interactions between generalized versions Implement movement such as pick up items Implement attack() and overload attackedBy() methods using Visitor Pattern Allows enemies to auto-attack when PC is within 1 block radius of an enemy Implement methods to add functionality to change PC’s attributes when picking up items Implememt main.cc to provide commands for the PC to attck Create main loop and breaks the loop when the PC reaches 5th floor or the PC dies Estimate: 5h, Nov. 27, 2016 Member: Rebecca Cheng, Ariel Ji

Introduce different races and enemies Implement PC and Enemy’s subclasses Override virtual method and add additional features and functionalities Implement virtual methods to achieve special effects when attacking Estimate: 5h, Nov. 28, 2016 Member: Ariel Ji & Paul Zhao

Introduce different types of items Implement Gold and Potion class Implement Potion’s subclasses Add Decorator Pattern to model the effect of Potions that PC consumed
Estimate: 5h, Nov. 29, 2016 Member: Paul Zhao & Rebecca Cheng

Testing & Have fun Estimate: Nov. 25, 2016 - Due Date Member: All

Introduce Downloadable Content (Bonus Enhancements) Introduce an inventory system so that the player character can hold multiple potion Estimate: Nov. 30, 2016 - Due Date Member: All

2.1 Player Character

How could you design your system so that each race could be easily generated?

There will be a base class (player character) that has basic fields (HP, atk, def, etc) and defines default methods so that each race can act as subclass, inheriting base class’s default behaviour and only implement extra functionalities if needed. This results in polymorphism which allows implementation for different behaviours based on the type of race, and thus easy generation of all races.

Additionally, how difficult does such a solution make adding additional races?

It will be easy to add additional races since only new functionalities about the race need to be added while overload basic methods from base class.

2.2 Enemy

Question : How does your system handle generating different enemies?

Since factory method pattern allows subclass to determine which class to instantiate and return existing instance multiple times, we use that in our system to generate multiple enemies.

Question : Is it different from how you generate the player character? Why or why not?

It is different from generating player character because by using factory method pattern, multiple enemies can be generated randomly at run time, while only one player character can be generated and is chosen by game player.

Question : How could you implement the various abilities for the enemy characters?

We will implement visitor pattern because we want different actions to occur with enemies that have different attack and defense abilities, and actions can be determined at runtime according to the type of enemy (overloaded parameter).

Question : Do you use the same techniques as for the player character races? Explain. Yes, player character races also have different abilities, hence double dispatch is also required.

2.3 Items

Question : The Decorator and Strategy patterns are possible candidates to model the effects of potions, so that we do not need to explicitly tract which potions the player character has consumed on any particular floor. In you opinion, which pattern would work better? Explain in detail, by weighing the advantages/disadvantages of the two patterns.

We believe that the decorator pattern would work better because it can be used to add functionality at runtime. In CC3K, each portion is a decorator and can be added to the PC when the player chooses to use a potion. In terms of strategy pattern, it is often used to swap behaviour at run-time, which is not the case for CC3K.