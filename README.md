Risk - Campus Domination - Boston University Edition
Developer Manual

Developers: 
    - Daniel Oved
    - Cole Johnson
    - Powell Vince
    
Overview:
    
    Our game is based on the classic board game of Risk. Our version is scaled down and
    simplified. There is no move function, and troops can be allocated to only one territory per
    turn. There are twelve territories represented by buildings chosen from Boston University's
    campus. There are also three continents; West, Central, and East. Each continent has three
    territories. There are troop bonuses for owning territories and continents; one troop per
    territory and three troops per continent. 
    
Classes:

    The base classes are Player and Territory. Troop bonuses give troops to a players .troops
    member while the number of troops on a territory is handled by that territory's .troops
    member. Based upon an attack outcome, a player can .gain_control() of a territory or
    .lose_control(). This modifies the .ter_controlled() member of the player and determines to
    where the player can allocate troops and from where the player can attack. Additionally, each
    player has a .color member that shows which territories he/she controls. This is coordinated
    with the .color member of each territory to display the gameboard and handle the outcomes of
    an attack.

Gameplay {
    
    Allocating Troops:

        At the start of a turn, the corresponding user can choose to put his/her troops on a single space he/she controls. Troops must be allocated before attacking commences.

    Attack Algorithm:

        The attack algorithm is based on a random distribution from one to six for each of the
        attacker and defenders' die. The attacker is given three die and the defender is given two.
        The highest of the attacker's rolled numbers is compared to the highest of the defender's
        rolled numbers, and the loser loses one troop. This repeats if the user chooses to continue
        attacking, until the defending territory has no troops. The user must choose to attack once
        more to take control of the territory, and subsequently can attack from that space. Also,
        every troop save one is transferred to the new territory.

    End Turn:

        Troop bonuses for the next player are calculated at the end of the previous player's turn.
}

Languages/Libraries/Platforms {
    
    C++:
        
        The game is coded in C++. Our team utilized many structures and libraries from C++. These include algorithm, string, vector, iostream, array, and random.
        
    Qt:
        
        The GUI is C++ based and constructed in Qt. Libraries from the Qt archive include QString, QProcess, QMedia, QMediaPlayer, QMediaPlaylist, and QProcess.
        
    Platform:
    
        The game is computer-based and playable only on this medium.
}

Files {

    riskplayer.hpp:
    
        This is the class definition for our Player class.
        
    riskplayer.cpp:
    
        This is the class implementation for our Player class.
        
    riskterritory.hpp:
        
        This is the class definition for our Territory class.
        
    riskterritory.cpp:
    
        This is the class implementation for our Territory class.
        
    Game.cpp:
    
        This is the original text-based version off of which the game logic is heavily based.
        
    Risk_it_all.pro:
    
        This is the Qt Creator file for the project.
        
    mainwindow.h:
    
        This is the header file for the Qt Creator project window.
        
    main.cpp:
    
        This is the execution of the application (displaying the GUI).
        
    mainwindow.cpp:
        
        This is the file that calculates everything and handles button clicks (the most important
        file).
        
    mainwindow.ui:
    
        This is the Qt Creator graphical user interface form for the project.
        
    README.md:
    
        This form.
        
    Others:
    
        The images and sound files for the game.
}

Project Build {
    
    App Flow:
    
        The app starts with a black background with the game images and music, and only the start
        button. The territory controls have already been calculated and the game will be ready to
        play when the button is pressed. The game map comes up with the appropriate buttons and
        the music continues. The music is looped to ensure that it lasts for the length of nearly
        any game. The end game button closes the window and ends the processes. Button presses are
        handled very carefully, with dropdown items being deleted and buttons/dropdowns being
        hidden accordingly. After the attack button is pressed in a turn, the allocate troops
        button disappears for the turn.
        
    Aesthetics:
    
        The game logo was crafted in Word and the game music was carefully chosen to engage the
        user. The gameplay map has pictures of the territories to make it more intuitive and the
        GUI presents very simply. Items in the GUI are carefully arranged to show that thought was
        given and present professionality.
}

Future Aspirations/Ideas {

    Gameplay:
        
        The game could be made to be less random so that there is no way for a player to have no
        territories at the beginning of the game. A move function could be added. Troop allocation
        to more than one space could be included. Faster attacking could be implemented (to take
        over a space, it sometimes takes a somewhat uncomfortable amount of time). The small bug
        of not taking over a space immediatly when the troop count goes to 0 but having to instead
        attack it once more should be fixed.
        
    User Input:
    
        The game could easily be modified to accept user input for the names of the players and
        territories. On a larger scale, multiple colleges could be loaded and the user could
        choose from which map to play.
        
    Aesthetics:
    
        It would be nice to have the map look like the actual campus, and the
        buttons/dropdowns/text could be spruced up to look more professional and appealing.
}
