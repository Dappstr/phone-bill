/*
 * Created by Lane Beals
 * Creation Date: Jan 11, 2022
 * CS 161B, Nicholas Insalata
 *
 * Phone Bill program
 * Will take in input from the user to get phone plan and gigabytes of data used.
 * Will then calculate phone bill according to user input and predefined values.
 */

#include <iostream>
#include <cmath> //For ceil()
#include <algorithm> //For std::find() MUST HAVE C++17 SUPPORT
#include <vector>
#include <map>

class PlanTypes
{
private:

    //Numbers are the amount of GB allotted per plan
    const int planS = 2;
    const int planM = 4;
    const int planL = 8;
    const int planU = 75; //75 dollars since GB is unlimited.

public:

    //Create our std::map which will hold the various plan types(keys)
    // to their corresponding value.
    template <typename T>
    auto createPlans(T& plans)
    {
        using std::make_pair;

        std::vector<char> acceptedInputs =
                {'s', 'S', 'm', 'M', 'l', 'L', 'u', 'U'};

        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[0], (int)planS) );
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[1], (int)planS) );
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[2], (int)planM));
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[3], (int)planM));
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[4], (int)planL));
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[5], (int)planL));
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[6], (int)planU));
        plans.insert(make_pair<char, int>
                             ((char)acceptedInputs[7], (int)planU));

        return plans;
    }
};

//Simply print the intro message to the user.
void printMsg()
{
    std::cout << "***** Welcome to Mint Mobile! *****\n"
                 "\n"
                 "Let's calculate your monthly bill!\n"
                 "\n"
                 "S: 2GB $35/mo*\n"
                 "M: 4GB $50/mo*\n"
                 "L: 8GB $70/mo*\n"
                 "U: Unlimited $75/mo\n"
                 "\n"
                 "*Overage charges $15 per GB\n";

}

//Will grab the plan our user chooses from input using a string
//And then will return an implied char (first letter) from our string.
template <typename S>
char getPlan(S& planChoiceStr)
{
    char finalPlanChoice {};

    bool looper (true);

    //This block will perform error checking in the event the user enters more than one character.
    while(looper)
    {
        std::cout << "Which plan are you on? (S/M/L/U): ";
        std::getline(std::cin, planChoiceStr);

        if(std::size(planChoiceStr) > 1)
        {

            std::cout << "You entered more than one character!\n";
        }

        else
        {
            finalPlanChoice = planChoiceStr[0];
            looper = false;
        }
    }

    return finalPlanChoice;
}

/* More archaic method of checking the user input for plan type
 * against all those in our vector which holds valid plan types
 * Will be used if C++17 support is not detected*/
[[nodiscard]] constexpr bool isCharCorrect(const char& c, const std::vector<char>& vec)
{
    bool isFound {};

    for(auto it: vec)
    {
        if(c == it)
            return true;
        else
            isFound = false;
    }
    return isFound;
}

//Grab the amount of gigabytes the user enters.
template <typename D>
double getGB(D& usedGB)
{
    bool loop (true);

    //Will check if user enters a valid number.
    while(loop)
    {
        std::cout << "How many GB did you use last month? ";
        std::cin >> usedGB;

        if (usedGB < 0)
        {
            std::cout << "Invalid number!\n";
        }
        else
        {
            loop = false;
        }
    }
    return usedGB;
}

int main()
{
    printMsg();

    std::string planChoiceStr {};
    char planChoice { getPlan(planChoiceStr) };

    std::vector<char> acceptedInputs =
            {'s', 'S', 'm', 'M', 'l', 'L', 'u', 'U'};

// If compiling with C++17 or greater detected, run this block
#if __cplusplus >= 201703L
    {
        while (std::find(acceptedInputs.begin(), acceptedInputs.end(), planChoice)
               == acceptedInputs.end())
        {
            planChoice = getPlan(planChoiceStr);
        }
    }
    // Other-wise use the older form
#else
    while(!isCharCorrect(planChoice, acceptedInputs))
        planChoice = getPlan(planChoiceStr);
#endif

    PlanTypes planObject;
    std::map<char, int> plans{};
    planObject.createPlans(plans);

    double usedGB{ getGB(usedGB) };
    int totalGB = static_cast<int>(std::ceil(usedGB));

    double overDraft (15.00);
    double planFee = 0.00;
    double grandTotal = 0.00;

    //Will decide the cost of the plan.
    switch(planChoice)
    {
        case 's': case 'S':
            planFee = 35.00;
            break;

        case 'm': case 'M':
            planFee = 50.00;
            break;

        case 'l': case 'L':
            planFee = 70.00;
            break;

        case 'u': case 'U':
            planFee = 75.00;
            break;

        default:
            std::cout << "Error when grabbing plan price.\n\n";
            return 1;
    }

    if(totalGB == plans[planChoice] || totalGB < plans[planChoice])
    {
        std::cout <<
                  "Plan charges: $"    << planFee <<
                  "\nNo overage fees!" <<
                  "\nTotal charges: $" << planFee <<
                  "\nThank you for choosing Mint Mobile.\n"
                  "Goodbye!";
    }

    else if (totalGB > plans[planChoice])
    {
        overDraft = overDraft * (totalGB - plans[planChoice]);
        grandTotal = overDraft + planFee;

        printf("Plan charges: $%.2f", planFee);
        printf("\nOverage charges: $%.2f", overDraft);
        printf("\nGrand total: $%.2f", grandTotal);

        if(grandTotal > 75)
        {
            std::cout << "\nConsider upgrading to the unlimited plan!\n";
        }

        std::cout <<
                  "\nThank you for choosing Mint Mobile.\n"
                  "Goodbye!\n";

    }

    return 0;
}

