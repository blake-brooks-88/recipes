#include <iostream>
#include <vector>
#include <string>


struct Ingredient
{
    enum class Measurement { count, teaspoon, tablespoon = 3, cup = 48 };
    float number;
    Measurement type;
    std::string ingredient;
};

struct Recipe
{
    std::vector<Ingredient> ingredientList;
    std::vector<std::string> stepByStepInstructions;
};

int getMeasurementType();
std::string getIngredientName();
float getQuantity();
void addIngredientToRecipe(Recipe& userRecipe);
void getIngredients(Recipe& userRecipe);
void getDirections(Recipe& userRecipe);
void addDirectionToRecipe(Recipe& userRecipe);
void debriefUser(Recipe userRecipe);
void printRecipe(Recipe userRecipe);
void printIngredient(Ingredient currentIngredient);
std::string getIngredientString(Ingredient currentIngredient, int ingredientTotal);
float getIngredientUnit(int ingredientTotal, std::string ingredientString);
float getIngredientTotal(float ammount, Ingredient::Measurement type);
void printDirections(Recipe& userRecipe);
void printInstruction(std::string currentInstruction, int currentIndex);

int main()
{
    Recipe Cookies;
    Cookies.ingredientList.push_back(Ingredient{ .75, Ingredient::Measurement::cup, "Egg" });
    Cookies.ingredientList.push_back(Ingredient{ 2, Ingredient::Measurement::cup, "Peanut Butter" });
    Cookies.ingredientList.push_back(Ingredient{ 1, Ingredient::Measurement::tablespoon, "Sugar" });

    Cookies.stepByStepInstructions.push_back("Mix all of the ingredients together in a bowl");
    Cookies.stepByStepInstructions.push_back("Roll up dough into small balls and put them on a cookie sheet");
    Cookies.stepByStepInstructions.push_back("Bake for 12-15 minutes on 365 degrees");

    Recipe userRecipe;
    getIngredients(userRecipe);
    getDirections(userRecipe);
    debriefUser(userRecipe);

}

void printRecipe(Recipe userRecipe)
{
    for (int i = 0; i < userRecipe.ingredientList.size(); i++)
    {
        Ingredient currentIngredient{ userRecipe.ingredientList[i] };
        printIngredient(currentIngredient);
    }
}

void printIngredient(Ingredient currentIngredient)
{
    std::string ingredientName = currentIngredient.ingredient;
    float ingredientTotal = getIngredientTotal(currentIngredient.number, currentIngredient.type);
    std::string ingredientString = getIngredientString(currentIngredient, ingredientTotal);
    float ingredientUnit = getIngredientUnit(ingredientTotal, ingredientString);

    std::cout.precision(3);

    if (ingredientString == "Count")
    {
        std::cout << ingredientUnit << " " << ingredientName << std::endl;
    }
    else
    {
        std::cout << ingredientUnit << " " << ingredientString << " " << ingredientName << '\n';
    }

}

void debriefUser(Recipe userRecipe)
{
    std::cout << "Thanks for adding a recipe. Would you like to see it? (Y/N): ";
    char response{};
    std::cin.clear();
    std::cin >> response;

    if (response == 'Y' || response == 'y')
    {
        printRecipe(userRecipe);
        printDirections(userRecipe);
    }
    else
    {
        std::cout << "Thanks! Have a great day :-)";
    }
}

void printDirections(Recipe& userRecipe)
{
    for (int i = 0; i < userRecipe.stepByStepInstructions.size(); i++)
    {
        std::string currentInstruction{ userRecipe.stepByStepInstructions[i] };
        printInstruction(currentInstruction, i);
    }
}

void printInstruction(std::string currentInstruction, int currentIndex)
{
    std::cout << currentIndex + 1 << ". " << currentInstruction << std::endl;
}

void getDirections(Recipe& userRecipe)
{
    bool isRunning{ true };
    int response{};

    while (isRunning)
    {
        std::cin.clear();
        std::cout << "Add a direction to your recipe\n";
        addDirectionToRecipe(userRecipe);

        std::cout
            << "Add another direction?\n"
            << "1. Yes please\n"
            << "2. All done\n";
        std::cin >> response;

        switch (response)
        {
        case 1:
            break;
        case 2:
            isRunning = false;
        default:
            break;
        }
    }
}

void getIngredients(Recipe& userRecipe)
{
    bool isRunning{ true };
    int response{};

    while (isRunning)
    {
        std::cin.clear();
        std::cout << "Add an ingredient to your recipe\n";
        addIngredientToRecipe(userRecipe);

        std::cout
            << "Add another ingredient?\n"
            << "1. Yes please\n"
            << "2. All done\n";
        std::cin >> response;

        switch (response)
        {
        case 1:
            break;
        case 2:
            isRunning = false;
        default:
            break;
        }
    }
}

void addDirectionToRecipe(Recipe& userRecipe)
{
    std::string direction{};
    std::cout << "Direction: ";
    std::cin.ignore();

    std::getline(std::cin, direction);
    userRecipe.stepByStepInstructions.push_back(direction);
}

void addIngredientToRecipe(Recipe& userRecipe)
{
    std::string ingredientName{ getIngredientName() };
    Ingredient::Measurement measurementType{ (Ingredient::Measurement)getMeasurementType() };
    float quantity{ getQuantity() };

    userRecipe.ingredientList.push_back(Ingredient{ quantity, measurementType, ingredientName });

}

float getQuantity()
{
    float result{};
    std::cout << "Quantity: ";
    std::cin.clear();
    std::cin >> result;

    return result;
}

std::string getIngredientName()
{
    std::string result{};
    std::cout << "Ingredient Name: ";
    std::cin >> result;

    return result;

}

int getMeasurementType()
{
    int result{};
    int userInput{};

    std::cout
        << "Select the measurement type\n"
        << "1. Teaspoon\n"
        << "2. Tablespoon\n"
        << "3. Cup\n"
        << "4. Count\n";

    std::cin.clear();
    std::cin >> userInput;

    switch (userInput)
    {
    case 1:
        result = (int)Ingredient::Measurement::teaspoon;
        break;
    case 2:
        result = (int)Ingredient::Measurement::tablespoon;
        break;
    case 3:
        result = (int)Ingredient::Measurement::cup;
        break;
    case 4:
        result = (int)Ingredient::Measurement::count;
        break;
    }

    return result;
}

float getIngredientTotal(float ammount, Ingredient::Measurement type)
{
    if (type == Ingredient::Measurement::count)
    {
        return ammount;
    }
    else
    {
        return ammount * (int)type;
    }
}

std::string getIngredientString(Ingredient currentIngredient, int ingredientTotal)
{

    if (currentIngredient.type == Ingredient::Measurement::count)
    {
        return "Count";
    }

    std::string result{};

    if (ingredientTotal < 3)
    {
        result = "Teaspoon";
    }
    else if (ingredientTotal >= 3 && ingredientTotal < 48)
    {
        result = "Tablespoon";
    }

    else if (ingredientTotal >= 48)
    {
        result = "Cup";
    }

    return result;
}

float getIngredientUnit(int ingredientTotal, std::string ingredientString)
{
    float result{};

    if (ingredientString == "Teaspoon")
    {
        result = (float)ingredientTotal / (float)Ingredient::Measurement::teaspoon;
    }
    else if (ingredientString == "Tablespoon")
    {
        result = (float)ingredientTotal / (float)Ingredient::Measurement::tablespoon;
    }
    else if (ingredientString == "Cup")
    {
        result = (float)ingredientTotal / (float)Ingredient::Measurement::cup;
    }
    else if (ingredientString == "Count")
    {
        result = (float)ingredientTotal;
    }

    return result;

}