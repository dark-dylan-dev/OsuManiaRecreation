#include "Game.h"
#include "Notes.h"

class FileHandler {
    std::ifstream file;
    std::string content;
public:
    FileHandler(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
    }
    ~FileHandler() {
        if (file.is_open()) {
            file.close(); // Fermeture automatique
        }
    }
    std::string read() {
        std::getline(file, content);
        return content;
    }
};

void loadLevel(const std::string& filename, std::vector<std::unique_ptr<LevelNotes>>& allLevelNotes) {
    Factory noteFactory;
    FileHandler LevelFile(filename);
    std::string lineContent;
    bool isReadingEnded = false;
    int cycleLevel = 0;
    while (!isReadingEnded) {
        lineContent = LevelFile.read();
        // Level ending
        if (lineContent == "END") {
            isReadingEnded = true;
        }
        // Commentaire
        else if(lineContent[0] == '#') {
            std::cout << "Comment : " << lineContent.substr(1, lineContent.length() - 1) << '\n';
        }
        // Level's speed
        else if (lineContent.substr(0, 5) == "SPEED" && lineContent.length() > 6) {
            std::cout << "Vitesse du niveau " << lineContent.substr(6, lineContent.length() - 6) << " BPM" << '\n';
        }
        // Slider
        else if (lineContent.substr(0, 6) == "SLIDER" && lineContent.length() >= 10) {
            std::cout << "Slider sur la touche " << lineContent[7] << " pour " << lineContent.substr(9, lineContent.length() - 9) << " cycles" << '\n';
        }
        // Wait
        else if (lineContent.substr(0, 4) == "WAIT" && lineContent.length() >= 6) {
            std::cout << "Aucune note pendant " << lineContent.substr(5, lineContent.length() - 5) << " cycles" << '\n';
        }
        // D or F or J or K
        else {
            for (int i = 0; i < lineContent.length(); ++i) {
                if (lineContent[i] == 'D') {
                    std::cout << "D";
                    allLevelNotes.push_back(noteFactory.createNote("singleNote", DHitCircle, cycleLevel, 'D'));
                }
                else if (lineContent[i] == 'F') {
                    std::cout << "F";
                    allLevelNotes.push_back(noteFactory.createNote("singleNote", FHitCircle, cycleLevel, 'F'));
                }
                else if (lineContent[i] == 'J') {
                    std::cout << "J";
                    allLevelNotes.push_back(noteFactory.createNote("singleNote", JHitCircle, cycleLevel, 'J'));
                }
                else if (lineContent[i] == 'K') {
                    std::cout << "K";
                    allLevelNotes.push_back(noteFactory.createNote("singleNote", KHitCircle, cycleLevel, 'K'));
                }
            }
            std::cout << '\n';
        }
        cycleLevel++;
    }
}