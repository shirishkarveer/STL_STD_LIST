// Project 2 - Solution
//  Lists

#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <iomanip>
#include <limits>

class Song {
    friend std::ostream& operator<<(std::ostream& os, const Song& s);

    std::string name;
    std::string artist;
    int rating;
public:
    Song() = default;
    Song(std::string name, std::string artist, int rating)
        : name{ name }, artist{ artist }, rating{ rating } {}

    std::string get_name() const {
        return name;
    }

    std::string get_artist() const {
        return artist;
    }

    int get_rating() const {
        return rating;
    }

    bool operator<(const Song& rhs) const {
        return this->name < rhs.name;
    }

    bool operator==(const Song& rhs) const {
        return this->name == rhs.name;
    }
};

std::ostream& operator<<(std::ostream& os, const Song& s) {
    os << std::setw(20) << std::left << s.name
        << std::setw(30) << std::left << s.artist
        << std::setw(2) << std::left << s.rating;
    return os;
}

void display_menu() {
    std::cout << "\nF - Play First Song" << std::endl;
    std::cout << "N - Play Next song" << std::endl;
    std::cout << "P - Play Previous song" << std::endl;
    std::cout << "A - Add and play a new Song at current location" << std::endl;
    std::cout << "L - List the current playlist" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << "Enter a selection (Q to quit): ";
}

void play_current_song(const Song& song) {//song class overloads stream insertion optr
    std::cout << "Playing: " << std::endl;//one liner 
    std::cout << song << std::endl;
}

void display_playlist(const std::list<Song>& playlist, const Song& current_song) {//get play list
    for (const Song& song : playlist) {//range based for over the PL
        std::cout << song << std::endl;//grab and disp the song,overload the insertion optr
    }
    std::cout << "Current song: " << std::endl;
    std::cout << current_song << std::endl;
}

int main() { 

    std::list<Song> playlist{//define PL, INIT THE 6 SONGS
            {"God's Plan",        "Drake",                     5},
            {"Never Be The Same", "Camila Cabello",            5},
            {"Pray For Me",       "The Weekend and K. Lamar",  4},
            {"The Middle",        "Zedd, Maren Morris & Grey", 5},
            {"Wait",              "Maroone 5",                 4},
            {"Whatever It Takes", "Imagine Dragons",           3}
    };

    std::list<Song>::iterator current_song = playlist.begin();//V.IMP don't forget, curr song is ITER to song in a std::list
    display_playlist(playlist, *current_song);//DISP THE PL,curr song is iter so need to de=ref the iter
    //*current_song/iterator shud ptr to list not off- defensive programming

    char selection{};
    do {//loop
        display_menu();
        std::cin >> selection;
        selection = std::toupper(selection);//make selection UC so not use OR
        if (selection == 'F') {
            std::cout << "Playing first song" << std::endl;
            current_song = playlist.begin();//set iter current_song = playlist.begin()
            play_current_song(*current_song);//call play current_song
        }
        else if (selection == 'N') {//N = next song
            std::cout << "Playing next song" << std::endl;
            current_song++;//increment iter
            if (current_song == playlist.end()) {//cud be off list, as I was on last song
                std::cout << "Wrapping to start of playlist" << std::endl;
                current_song = playlist.begin();//set iter to begin, 
            }
            play_current_song(*current_song);
        }
        else if (selection == 'P') {
            std::cout << "Playing previous song" << std::endl;//disp 
            if (current_song == playlist.begin()) {//check if curr song = first song
                std::cout << "Wrapping to end of playlist" << std::endl;//then wrap around
                current_song = playlist.end();//
            }
            current_song--;//dec song
            play_current_song(*current_song);//if I am at begin of list play the last song
        }
        else if (selection == 'A') {
            std::string name, artist;
            int rating;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//clear out unwanted stuff
            std::cout << "Adding and playing new song" << std::endl;
            std::cout << "Enter song name:";
            getline(std::cin, name);
            std::cout << "Enter song artist: ";
            getline(std::cin, artist);
            std::cout << "Enter your rating (1-5): ";
            std::cin >> rating;
            playlist.insert(current_song, Song{ name, artist, rating });//create new song with info
            current_song--;
            play_current_song(*current_song);//my iter, insert before can use emplace.back()
        }
        else if (selection == 'L') {
            std::cout << std::endl;
            display_playlist(playlist, *current_song);
        }
        else if (selection == 'Q')
            std::cout << "Quitting" << std::endl;
        else
            std::cout << "Illegal choice, try again...";
    } while (selection != 'Q');

    std::cout << "Thanks for listening!" << std::endl;
    return 0;
}
