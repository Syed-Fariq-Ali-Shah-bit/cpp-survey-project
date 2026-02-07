#include <iostream>
#include <string>
using namespace std;

// ---------- FUNCTION DECLARATIONS ----------
void printWelcome();
void inputTopic(string &topic);
void inputQuestions(string questions[], int &totalQuestions);
void inputParticipantsAnswers(string questions[], string answers[][50],
                              int totalQuestions, int &totalParticipants);
void displaySurvey(string topic, string questions[], string answers[][50],
                   int totalQuestions, int totalParticipants);
void analyzeSurvey(string questions[], string answers[][50],
                   int totalQuestions, int totalParticipants);

// ---------- MAIN FUNCTION ----------
int main()
{
    string topic;
    int totalQuestions, totalParticipants;

    string questions[50];
    string answers[50][50];

    printWelcome();
    inputTopic(topic);
    inputQuestions(questions, totalQuestions);
    inputParticipantsAnswers(questions, answers, totalQuestions, totalParticipants);
    displaySurvey(topic, questions, answers, totalQuestions, totalParticipants);
    analyzeSurvey(questions, answers, totalQuestions, totalParticipants);

    return 0;
}

// ---------- FUNCTION DEFINITIONS ----------

void printWelcome()
{
    cout << "==============================" << endl;
    cout << "   Welcome to Survey Program  " << endl;
    cout << "==============================" << endl;
}

void inputTopic(string &topic)
{
    cout << "Please enter survey topic: ";
    getline(cin, topic);
}

void inputQuestions(string questions[], int &totalQuestions)
{
    cout << "How many questions you want to add in this survey? ";
    cin >> totalQuestions;
    cin.ignore();

    for (int i = 0; i < totalQuestions; i++)
    {
        cout << "Enter Question " << i + 1 << ": ";
        getline(cin, questions[i]);
    }
}

void inputParticipantsAnswers(string questions[], string answers[][50],
                              int totalQuestions, int &totalParticipants)
{
    cout << "How many participants will take this survey? ";
    cin >> totalParticipants;
    cin.ignore();

    for (int p = 0; p < totalParticipants; p++)
    {
        cout << "\nParticipant " << p + 1 << " answers:\n";
        for (int q = 0; q < totalQuestions; q++)
        {
            cout << questions[q] << ": ";
            getline(cin, answers[p][q]);
        }
    }
}

void displaySurvey(string topic, string questions[], string answers[][50],
                   int totalQuestions, int totalParticipants)
{
    cout << "\nSurvey Completed!\n";
    cout << "Topic: " << topic << endl;
    cout << "==============================\n";

    for (int p = 0; p < totalParticipants; p++)
    {
        cout << "Participant " << p + 1 << " Answers:\n";
        for (int q = 0; q < totalQuestions; q++)
        {
            cout << q + 1 << ". " << questions[q]
                 << " -> " << answers[p][q] << endl;
        }
        cout << "------------------------------\n";
    }
}

void analyzeSurvey(string questions[], string answers[][50],
                   int totalQuestions, int totalParticipants)
{
    cout << "\n========== SURVEY ANALYSIS ==========\n";

    for (int q = 0; q < totalQuestions; q++)
    {
        cout << "\nQuestion: " << questions[q] << endl;

        bool isNumber = true;
        int numbers[50];
        int numCount = 0;

        for (int p = 0; p < totalParticipants; p++)
        {
            string a = answers[p][q];

            for (int i = 0; i < a.length(); i++)
            {
                if (a[i] < '0' || a[i] > '9')
                {
                    isNumber = false;
                    break;
                }
            }

            if (!isNumber)
                break;

            numbers[numCount] = 0;
            for (int i = 0; i < a.length(); i++)
            {
                numbers[numCount] = numbers[numCount] * 10 + (a[i] - '0');
            }
            numCount++;
        }

        if (isNumber)
        {
            int max = numbers[0];
            int min = numbers[0];
            int sum = 0;

            for (int i = 0; i < numCount; i++)
            {
                if (numbers[i] > max) max = numbers[i];
                if (numbers[i] < min) min = numbers[i];
                sum += numbers[i];
            }

            float average = (float)sum / numCount;

            cout << "Type: Numeric\n";
            cout << "Maximum: " << max << endl;
            cout << "Minimum: " << min << endl;
            cout << "Average: " << average << endl;
        }
        else
        {
            string words[50];
            int count[50] = {0};
            int unique = 0;

            for (int p = 0; p < totalParticipants; p++)
            {
                string a = answers[p][q];
                bool found = false;

                for (int i = 0; i < unique; i++)
                {
                    if (words[i] == a)
                    {
                        count[i]++;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    words[unique] = a;
                    count[unique] = 1;
                    unique++;
                }
            }

            int maxIndex = 0;
            for (int i = 1; i < unique; i++)
            {
                if (count[i] > count[maxIndex])
                    maxIndex = i;
            }

            cout << "Type: Text\n";
            cout << "Most Frequent Answer: " << words[maxIndex]
                 << " (Entered " << count[maxIndex] << " times)\n";
        }
    }
}