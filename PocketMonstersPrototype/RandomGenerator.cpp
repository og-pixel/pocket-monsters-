#include "RandomGenerator.h"

std::vector<std::string> RandomGenerator::monsterNames;

RandomGenerator::RandomGenerator(){}

/**
 * Creates names for the monsters to the monsterNames vector
 * This vector has to be filled with names first to be used later
 * @return true if loaded successfully
 */
bool RandomGenerator::getMonsterName() {
    std::ifstream inClientFile("RandomGeneratorFile/MonsterNames.txt", std::ios::in);
    if (!inClientFile) {
        std::cerr << "File could not be opened" << std::endl;
        return false;
    }
    std::string monsterName;
    std::cout << monsterName << std::endl;

    while (inClientFile >> monsterName) {
        monsterNames.push_back(monsterName);
    }
    return true;
}

/**
 * Method returns a name from the monsterNames vector
 * It has to be loaded first by using getMonsterName method.
 * @return A random name from the monsterNames list
 */
std::string RandomGenerator::getRandomMonsterName() {
    if (monsterNames.empty()) {
        std::cout << "List of monsters is empty" << std::endl; //Maybe that should be an exception
    } else {
        return monsterNames[randomValue(0, monsterNames.size())];
    }
}

/**
 * Method generates a random number between minValue and maxValue
 * @param minValue Minimum value for generator
 * @param maxValue Maximum value for generator
 * @return A random number between minValue and maxValue
 */
int RandomGenerator::randomValue(int minValue, int maxValue) {
    std::random_device generator;                               //Random Number Engine
    std::uniform_int_distribution<int> distribution(minValue, maxValue); //Create distribution between min and max Value

    return distribution(generator);                                     //Return that Random
}

/**
 * Creates Random description for monster by loading various
 * description parts, shuffles them together for pseudo random description.
 * @return fullDescription randomly generated description for monster
 */
std::string RandomGenerator::createRandomDescription() {
    std::ifstream colourFile("DescriptionGenerator/Colour.txt", std::ios::in);
    std::ifstream colourPrefixFile("DescriptionGenerator/ColourPrefix.txt", std::ios::in);
    std::ifstream heightFile("DescriptionGenerator/Height.txt", std::ios::in);
    std::ifstream moodFile("DescriptionGenerator/Mood.txt", std::ios::in);
    std::ifstream otherFile("DescriptionGenerator/Other.txt", std::ios::in);
    std::ifstream similarityFile("DescriptionGenerator/Similarity.txt", std::ios::in);
    std::ifstream typeRelatedFile("DescriptionGenerator/TypeRelated.txt", std::ios::in);


    if (!colourFile || !colourPrefixFile || !heightFile || !moodFile || !otherFile || !similarityFile ||
        !typeRelatedFile) {
        std::cerr << "File could not be opened" << std::endl;
        return nullptr;
    }

    std::vector<std::string> colourList;
    std::vector<std::string> colourPrefixList;
    std::vector<std::string> heightList;
    std::vector<std::string> moodList;
    std::vector<std::string> otherList;
    std::vector<std::string> similarityList;
    std::vector<std::string> typeRelatedList;

    std::string colour;
    std::string colourPrefix;
    std::string height;
    std::string mood;
    std::string other;
    std::string similarity;
    std::string typeRelated;


    while (std::getline(colourFile, colour)) {
        colourList.push_back(colour);
    }
    while (std::getline(colourPrefixFile, colourPrefix)) {
        colourPrefixList.push_back(colourPrefix);
    }
    while (std::getline(heightFile, height)) {
        heightList.push_back(height);
    }
    while (std::getline(moodFile, mood)) {
        moodList.push_back(mood);
    }
    while (std::getline(otherFile, other)) {
        otherList.push_back(other);
    }
    while (std::getline(similarityFile, similarity)) {
        similarityList.push_back(similarity);
    }
    while (std::getline(typeRelatedFile, typeRelated)) {
        typeRelatedList.push_back(typeRelated);
    }

    std::string fullDescription;


    //About 40% chance for a monster to have "extra" colour description
    if (randomValue(0, 10) > 6) {
        fullDescription = heightList[randomValue(0, heightList.size() - 1)] +
                          colourPrefixList[randomValue(0, colourPrefixList.size() - 1)] +
                          colourList[randomValue(0, colourList.size() - 1)] +
                            "and " + colourList[randomValue(0, colourList.size() - 1)] +
                          similarityList[randomValue(0, similarityList.size() - 1)] +
                          otherList[randomValue(0, otherList.size() - 1)] +
                          typeRelatedList[randomValue(0, typeRelatedList.size() - 1)] +
                          moodList[randomValue(0, moodList.size() - 1)];
    }else{
        fullDescription = heightList[randomValue(0, heightList.size() - 1)] +
                          colourPrefixList[randomValue(0, colourPrefixList.size() - 1)] +
                          colourList[randomValue(0, colourList.size() - 1)] +
                          similarityList[randomValue(0, similarityList.size() - 1)] +
                          otherList[randomValue(0, otherList.size() - 1)] +
                          typeRelatedList[randomValue(0, typeRelatedList.size() - 1)] +
                          moodList[randomValue(0, moodList.size() - 1)];
    }
    return fullDescription;
}
