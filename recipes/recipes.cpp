#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>

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
    std::string name;

    int ID{};
};

const std::string RECIPES_FILE_PATH = "recipes.txt";

int getMeasurementType();
std::string getIngredientName();
float getQuantity();
void addIngredient(Recipe& userRecipe, bool editMode = false, int index = -1);
void getIngredients(Recipe& userRecipe);
void getDirections(Recipe& userRecipe);
void addDirectionToRecipe(Recipe& userRecipe, bool editMode = false, int index = -1);
void debriefUser(Recipe userRecipe);
void printRecipe(Recipe userRecipe);
void printIngredient(Ingredient currentIngredient);
std::string getIngredientString(Ingredient::Measurement ingredientType, int ingredientTotal);
float getIngredientUnit(int ingredientTotal, std::string ingredientString);
float getIngredientTotal(float ammount, Ingredient::Measurement type);
void printDirections(Recipe& userRecipe);
void printInstruction(std::string currentInstruction, int currentIndex);
void validateQuantity(float &result);
void validateUserInput(int &response, int numberOfOptions);

void newRecipe(std::vector<Recipe> &cookBook);
std::string getRecipeName();
void runCookbook(std::vector<Recipe>& cookBook);
bool displayCookbookMenu(std::vector<Recipe>& cookBook);
void saveRecipes(std::vector<Recipe> cookBook, std::string filePath);
Recipe randomRecipe(std::vector<Recipe> cookBook);
int findRecipe(std::vector<Recipe> cookBook);
void editRecipe(Recipe& recipe);
void printEditOptions(Recipe recipe);
void editIngredient(Recipe &recipe, int index);
void editInstruction(Recipe &recipe, int index);
int generateRandomNumber(int minValue, int maxValue);

int main()
{
    Recipe Cookies;
    Cookies.ingredientList.push_back(Ingredient{ .75, Ingredient::Measurement::cup, "Egg" });
    Cookies.ingredientList.push_back(Ingredient{ 2, Ingredient::Measurement::count, "Peanut Butter" });
    Cookies.ingredientList.push_back(Ingredient{ 1, Ingredient::Measurement::tablespoon, "Sugar" });

    Cookies.stepByStepInstructions.push_back("Mix all of the ingredients together in a bowl");
    Cookies.stepByStepInstructions.push_back("Roll up dough into small balls and put them on a cookie sheet");
    Cookies.stepByStepInstructions.push_back("Bake for 12-15 minutes on 365 degrees");

    Cookies.ID = 0;
    Cookies.name = "Cookies";

    std::vector<Recipe> cookBook{Cookies};
    runCookbook(cookBook);

}

//new code
//=============================================================

void runCookbook(std::vector<Recipe> &cookBook)
{
    while (displayCookbookMenu(cookBook))
    {
    }

    std::cout << "Thank you!";
}

bool displayCookbookMenu(std::vector<Recipe> &cookBook)
{
    int userInput{};

    std::cout
        << "What would you like to do?\n"
        << "1. Add Recipe\n"
        << "2. Print Recipe\n"
        << "3. Edit Recipe\n"
        << "4. Random Recipe\n"
        << "5. Save Recipes\n"
        << "6. Load Recipes\n"
        << "7. Exit The Program\n";

    std::cin.clear();
    std::cin >> userInput;

    validateUserInput(userInput, 5);
    int recipeIndex{};

    switch (userInput)
    {
    case 1:
        newRecipe(cookBook);
        return true;
    case 2:
        recipeIndex = findRecipe(cookBook);
        printRecipe(cookBook[recipeIndex]);
        return true;
    case 3:
        recipeIndex = findRecipe(cookBook);
        editRecipe(cookBook[recipeIndex]);
        return true;
    case 4:
        printRecipe(randomRecipe(cookBook));
        return true;
    case 5:
        saveRecipes(cookBook, RECIPES_FILE_PATH);
        return true;
    case 6:
        //loadRecipes(cookBook, RECIPES_FILE_PATH);
        return true;
    case 7:
        return false;
    }
}

void saveRecipes(std::vector<Recipe> cookBook, std::string filePath)
{
    std::ofstream recipiesFile(filePath, std::ios_base::app);

    for (Recipe recipe : cookBook)
    {
        recipiesFile << recipe.ID << std::endl;
        recipiesFile << recipe.name << std::endl;
        recipiesFile << recipe.ingredientList.size() << std::endl;
        
        for (Ingredient currentIngredient : recipe.ingredientList)
        {
            recipiesFile << currentIngredient.number << " ";
            recipiesFile << (int)currentIngredient.type << " ";
            recipiesFile << currentIngredient.ingredient << std::endl;
        }
        
        recipiesFile << recipe.ingredientList.size() << std::endl;
        for (std::string instruction : recipe.stepByStepInstructions)
        {
            recipiesFile << instruction << std::endl;
        }
    }
}

Recipe randomRecipe(std::vector<Recipe> cookBook)
{
    int minValue{ 0 };
    int maxValue = (cookBook.size() - 1);
    int index{ generateRandomNumber(minValue,maxValue) };

    return cookBook[index];

}

int generateRandomNumber(int minValue, int maxValue)
{
    std::random_device rdev;
    static std::default_random_engine e(rdev());
    static std::uniform_int_distribution<int> num(minValue, maxValue);
    
    return num(e);
}

void editRecipe(Recipe& recipe)
{
    int userResponse{};
    printEditOptions(recipe);
    std::cin >> userResponse;
    int index{ userResponse - 1 };

    if (userResponse > recipe.ingredientList.size())
    {
        index -= recipe.ingredientList.size();
        editInstruction(recipe, index);
    }
    else
    {
        editIngredient(recipe,index);
    }
}

void editIngredient(Recipe &recipe, int index)
{
    Ingredient currentIngredient{ recipe.ingredientList[index] };
    addIngredient(recipe, true, index);
    printIngredient(recipe.ingredientList[index]);
}

void editInstruction(Recipe &recipe, int index)
{
    addDirectionToRecipe(recipe, true, index);
}

void printEditOptions(Recipe recipe)
{
    std::cout << "Which item would you like to edit?\n";

    std::cout << "\nIngredients: \n";
    for (int i = 0; i < recipe.ingredientList.size(); i++)
    {
        std::cout << i + 1 << ". ";
        printIngredient(recipe.ingredientList[i]);
    }

    std::cout << "\nInstructions: \n";
    for (int i = 0; i < recipe.stepByStepInstructions.size(); i++)
    {
        int currentNumber = i + recipe.ingredientList.size() + 1;
        std::cout << currentNumber << "." << recipe.stepByStepInstructions[i] << '\n';
    }
}

int findRecipe(std::vector<Recipe> cookBook)
{
    if (cookBook.size() < 0)
    {
        return -1;
    }

    int cookBookID{};
    std::cout << "Please enter the cook book ID: ";
    std::cin >> cookBookID;

    for (int i = 0; i < cookBook.size(); i++)
    {
        if (cookBook[i].ID == cookBookID)
        {
            return i;
        }
    }

    return -1;
}

void newRecipe(std::vector<Recipe> &cookBook)
{
    Recipe UserRecipe;
    std::string recipeName = getRecipeName();
    UserRecipe.name = recipeName;

    getIngredients(UserRecipe);
    getDirections(UserRecipe);

    int newID = cookBook.size() + 1;
    UserRecipe.ID = newID;

    cookBook.push_back(UserRecipe);
    debriefUser(UserRecipe);
}

std::string getRecipeName()
{
    std::cin.clear();
    std::string result;
    std::cout << "What is the name of this recipe: ";
    std::cin.ignore();

    std::getline(std::cin, result);

    return result;
}

void loadRecipes()
{
    //loads all recipes from a file
        //once loaded in, it updates the IDs of the cookbook vector so there are no clashing IDs
}

//new code end
//=============================================================

void printRecipe(Recipe userRecipe)
{
    std::cout << "Ingredients: \n";

    for (int i = 0; i < userRecipe.ingredientList.size(); i++)
    {
        Ingredient currentIngredient{ userRecipe.ingredientList[i] };
        printIngredient(currentIngredient);
    }
    
    std::cout << "\nInstructions: \n";
    for (int i = 0; i < userRecipe.stepByStepInstructions.size(); i++)
    {
        int currentNumber = i + 1;
        std::cout << currentNumber << "." << userRecipe.stepByStepInstructions[i] << '\n';
    }

    std::cout << '\n';
}

void printIngredient(Ingredient currentIngredient)
{
    std::string ingredientName = currentIngredient.ingredient;
    float ingredientTotal = getIngredientTotal(currentIngredient.number, currentIngredient.type);
    std::string ingredientString = getIngredientString(currentIngredient.type, ingredientTotal);
    float ingredientUnit = getIngredientUnit(ingredientTotal, ingredientString);

    std::cout.precision(3);

    if (ingredientString == "Count")
    {
        std::cout << ingredientTotal << " " << ingredientName << std::endl;
    }
    else
    {
        std::cout << ingredientUnit << " " << ingredientString << " " << ingredientName << '\n';
    }

}

void debriefUser(Recipe userRecipe)
{
    std::cout << "Recipe added successfully!\n";
}

void printDirections(Recipe& userRecipe)
{
    std::cout << "Instructions: \n";

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

        validateUserInput(response, 2);

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
        addIngredient(userRecipe);

        std::cout
            << "Add another ingredient?\n"
            << "1. Yes please\n"
            << "2. All done\n";
        std::cin >> response;

        validateUserInput(response, 2);

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

void validateUserInput(int &response, int numberOfOptions)
{
    while (!std::cin.good() || response < 1 || response > numberOfOptions)
    {
        std::cout << "Error, please select a number between " << 1 << " and " << numberOfOptions << ": ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> response;
    }
}

void addDirectionToRecipe(Recipe& userRecipe, bool editMode, int index)
{
    std::string direction{};
    std::cout << "Direction: ";
    std::cin.ignore();

    std::getline(std::cin, direction);

    if (editMode)
    {
        userRecipe.stepByStepInstructions[index] = direction;
    }
    else
    {
        userRecipe.stepByStepInstructions.push_back(direction);
    }
}

void addIngredient(Recipe& userRecipe, bool editMode, int index)
{
    std::cin.clear();
    std::string ingredientName{ getIngredientName() };
    Ingredient::Measurement measurementType{ (Ingredient::Measurement)getMeasurementType() };
    float quantity{ getQuantity() };

    float ingredientTotal = getIngredientTotal(quantity, measurementType);
    std::string ingredientString = getIngredientString(measurementType, ingredientTotal);
    float ingredientUnit = getIngredientUnit(ingredientTotal, ingredientString);

    Ingredient userIngredient{
                ingredientTotal,
                (Ingredient::Measurement)ingredientUnit,
                ingredientName
    };

    if (editMode)
    {
        userRecipe.ingredientList[index] = userIngredient;
    }
    else
    {
        userRecipe.ingredientList.push_back(userIngredient);
    }
}

float getQuantity()
{
    float result{};
    std::cout << "Quantity: ";
    std::cin.clear();
    std::cin >> result;

    validateQuantity(result);

    return result;
}

void validateQuantity(float &result)
{
    while (!std::cin.good())
    {
        std::cout << "Enter a valid quantity (Integer or decimal value): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> result;
    }
}

std::string getIngredientName()
{
    std::cin.clear();
    std::string result;
    std::cout << "Ingredient Name: ";

    std::getline(std::cin, result);

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

    validateUserInput(userInput, 4);

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

std::string getIngredientString(Ingredient::Measurement ingredientType, int ingredientTotal)
{
    if (ingredientType == Ingredient::Measurement::count)
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
        result = (float)Ingredient::Measurement::count;
    }

    return result;

}