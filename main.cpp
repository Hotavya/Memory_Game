/* 10/03/2019
 This program simulates a memory game. It asks the user to enter
 coordinates of two cards and checks whether they match or not.
 It also writes data related to the user in a file.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

const int LENGTH = 4;
using namespace std;

// Function prototypes

void InitializeCards(int cards[][LENGTH]);
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH]);

// ======================
// InitializeCards
// It receives an array as an argument
// Places pairs of numbers in the 2D array and then
// randomly shuffles them.
// ======================

void InitializeCards(int cards[][LENGTH])
{
    srand(time(NULL));
    int x1, y1, x2, y2;
    int i;
    int temp;

    cards[0][0] = 1; cards[0][1] = 1;//   1  1  2  2
    cards[0][2] = 2; cards[0][3] = 2;
    cards[1][0] = 3; cards[1][1] = 3;//   3  3  4  4
    cards[1][2] = 4; cards[1][3] = 4;
    cards[2][0] = 5; cards[2][1] = 5;//   5  5  6   6
    cards[2][2] = 6; cards[2][3] = 6;
    cards[3][0] = 7; cards[3][1] = 7;//   7  7  8   8
    cards[3][2] = 8; cards[3][3] = 8;

    // Now that 2D has been initialized with 8 pairs, we want
    // to shuffle the board so
    // that the pairs aren't right next to each other
    for (int i = 0; i < 30; i++) {
        //Get set of random coordinates and swap
        //First random coordinate on our 2d "grid"
        y1 = rand() % LENGTH;
        x1 = rand() % LENGTH;
        //Second random coordinate of our 2d "grid"
        y2 = rand() % LENGTH;
        x2 = rand() % LENGTH;

        //Now we swap value at (x1, y1) with value at(x2, y2)
        temp = cards[x1][y1];
        cards[x1][y1] = cards[x2][y2];
        cards[x2][y2] = temp;
    }
}

// ======================
//     main function
// ======================
int main()
{
    ofstream outfile;
    outfile.open("output.txt");
    
    string name;
    cout << "Welcome to my game!" << endl
    << "Please enter your name:" << endl;
    
    getline (cin, name);
    
    cout << "Welcome " << name << endl
    << "Find all the matching pairs on the board!" << endl;
   
    int cards [4] [LENGTH];
    
    InitializeCards(cards);
    
    bool faceup [4] [LENGTH];
    for ( int i = 0; i < 4; i++)
    {
        for (int j = 0; j < LENGTH; j++)
        faceup [i][j] = 0;
        
    }
   
    ShowCards (cards, faceup);

    int x1, y1, x2, y2;
    
    cout <<"Please enter the coordinates of two cards:" << endl
    <<"Enter x and y position of first card:" << endl;
    
    cin >> x1;
    cin >> y1;
    
    while (  x1<0||x1>3 || y1<0||y1>3)
    {
        cout <<"Please enter valid coordinates:" << endl
        <<"Enter x and y position of first card" << endl;
        cin >> x1;
        cin >> y1;
    }
        
    cout <<"Enter x and y position of the second card: " << endl;
    
    cin >> x2;
    cin >> y2;
    
    while (  x2<0||x2>3 || y2<0||y2>3)
    {
        cout <<"Please enter valid coordinates:" << endl
        <<"Enter x and y position of second card" << endl;
        cin >> x2;
        cin >> y2;
    }
    
    faceup [x1][y1] = true;
    faceup [x2][y2] = true;
    ShowCards (cards, faceup);
    
    if ( cards [x1][y1] == cards [x2][y2])
    {
      cout <<"It is a match!" << endl;
    }

    else if (cards [x1][y1] != cards [x2][y2])
    {
        faceup [x1][y1] = false;
        faceup [x2][y2] = false;
        cout <<"No match." << endl
        <<"Flipping cards over again\n";
    }

    char input;
    int counter = 0;
    
    cout <<"Enter 'q' to quit or press any key to continue: ";
    cin >> input;
    
    while (input != 'q')
    {     cout <<"Please enter the coordinates of two cards:" << endl
          <<"Enter x and y position of first card:" << endl;
        
        cin >> x1;
        cin >> y1;
        
    while (x1<0||x1>3 || y1<0||y1>3)
    {
        cout <<"Please enter valid coordinates:" << endl
             <<"Enter x and y position of first card" << endl;
        cin >> x1;
        cin >> y1;
           }
        
        cout <<"Enter x and y position of the second card: " << endl;
        
        cin >> x2;
        cin >> y2;
        
    while ( x2<0||x2>3 || y2<0||y2>3)
       {
           cout <<"Please enter valid coordinates:" << endl
           <<"Enter x and y position of first card" << endl;
           cin >> x2;
           cin >> y2;
       }
        
        faceup [x1][y1] = true;
        faceup [x2][y2] = true;
        ShowCards (cards, faceup);
    
        if ( cards [x1][y1] == cards [x2][y2])
        {
            cout <<"It is a match!" << endl;
        }
        else if (cards [x1][y1] != cards [x2][y2])
        {
            faceup [x1][y1] = false;
            faceup [x2][y2] = false;
            cout <<"No match." << endl
            <<"Flipping cards over again\n";
        
            cout <<"Enter 'q' to quit or press any key to continue: ";
            cin >> input;
            
       
        }
        counter += 1;
    }
    
    int a = 0;
    for (int i = 0; i < LENGTH; i++)
    {   for (int j = 0; j < 4; j++)
        if ( faceup [i][j] == true)
            a++;
        
    }
    


    // 5) Save the user’s name and how many turns it
    //took to win the game into an output text file. If he quits
    // before winning save “Don’t give up” message in the file.

    
    if (outfile)
        
    {
      outfile <<"The user's name is " << name << endl;
      outfile <<"The user took " << counter <<"attempts"
              <<" to win the game" << endl;
        
      if(a != 16)
          outfile <<"Don't give up";
    }
    
    outfile.close();
}

// ======================
// ShowCards
// Receives two arrays as arguments.
// Generates a display on the screen. If faceup=false,
// an * is output, otherwise the card in that slot is output.
// ======================
void ShowCards(int cards[][LENGTH], bool faceup[][LENGTH])
{
    int num = 0;
    
    int format [] = {0,1,2,3};
    cout << "  ";
    for (int i = 0; i < 4; i++)
        cout  << format [i] << " ";
    
    cout << endl;
    cout <<"============" << endl;
    
    
    for (int i = 0; i < 4; i++)
    {
        cout << num << "|";
        for (int j = 0; j < LENGTH; j++)
        {
            if ( faceup [i][j] == 0)
                cout << '*' << " ";
            else
                cout << cards [i][j] << " ";
        }
        cout <<"|";
        cout << endl;
        num++;
    }
    cout <<"============" << endl;
   
}

/* Sample Run
 1.) Input with invalid value.
 
 Welcome to my game!
 Please enter your name:
 Hotavya
 Welcome Hotavya
 Find all the matching pairs on the board!
   0 1 2 3
 ============
 0|* * * * |
 1|* * * * |
 2|* * * * |
 3|* * * * |
 ============
 Please enter the coordinates of two cards:
 Enter x and y position of first card:
 2 5
 Please enter valid coordinates:
 Enter x and y position of first card
 
 
 2.)Three input with valid values
 
 Welcome to my game!
 Please enter your name:
 Hotavya
 Welcome Hotavya
 Find all the matching pairs on the board!
   0 1 2 3
 ============
 0|* * * * |
 1|* * * * |
 2|* * * * |
 3|* * * * |
 ============
 Please enter the coordinates of two cards:
 Enter x and y position of first card:
 1 2
 Enter x and y position of the second card:
 2 1
   0 1 2 3
 ============
 0|* * * * |
 1|* * 2 * |
 2|* 5 * * |
 3|* * * * |
 ============
 No match.
 Flipping cards over again
 Enter 'q' to quit or press any key to continue: f
 Please enter the coordinates of two cards:
 Enter x and y position of first card:
 0 0
 Enter x and y position of the second card:
 0 1
   0 1 2 3
 ============
 0|2 3 * * |
 1|* * * * |
 2|* * * * |
 3|* * * * |
 ============
 No match.
 Flipping cards over again
 Enter 'q' to quit or press any key to continue: f
 Please enter the coordinates of two cards:
 Enter x and y position of first card:
 1 2
 Enter x and y position of the second card:
 0 0
   0 1 2 3
 ============
 0|2 * * * |
 1|* * 2 * |
 2|* * * * |
 3|* * * * |
 ============
 It is a match!
 Please enter the coordinates of two cards:
 Enter x and y position of first card:

 
3.) One input with the quit choice
 
 Welcome to my game!
 Please enter your name:
 Hotavya
 Welcome Hotavya
 Find all the matching pairs on the board!
   0 1 2 3
 ============
 0|* * * * |
 1|* * * * |
 2|* * * * |
 3|* * * * |
 ============
 Please enter the coordinates of two cards:
 Enter x and y position of first card:
 1 2
 Enter x and y position of the second card:
 0 0
   0 1 2 3
 ============
 0|4 * * * |
 1|* * 4 * |
 2|* * * * |
 3|* * * * |
 ============
 It is a match!
 Enter 'q' to quit or press any key to continue: q
 Program ended with exit code: 0
 
 */
