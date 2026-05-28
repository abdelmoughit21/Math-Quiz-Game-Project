#include <iostream>
using namespace std;

enum enQuestionsLevel { Easy = 1 , Med = 2 , Hard = 3 , Mix1 = 4 };
enum enOperationType { Add = 1 , Sub = 2 , Mult = 3 , Div = 4 , Mix = 5};

struct stGameResult {

    short NumberOfQuestions = 0;
    string QuestionsLevel;
    string OpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;

};

void ResetScreen() {

    system("cls");
    system("color 0F");

}

int HowManyQuestions() {

    int Questions = 0;

    cout << "How many questions do you want to answer ? ";
    cin >> Questions;

    while (Questions <= 0) {

        cout << "Please enter how many questions do you want to answer ? ";
        cin >> Questions;

    }

    return Questions;

}

int ReadNumber() {

    int num = 0;

    cin >> num;

    return num;

}

int GetRandomNumber(int from, int to) {

    int randNum = rand() % (to - from + 1) + from;

    return randNum;

}

enQuestionsLevel ReadQuestionLevel(string message) {

    int num = 0;

    do {

        cout << message;
        cin >> num;

    } while (num < 1 || num > 4);

    return (enQuestionsLevel)num;

}

enOperationType ReadOperationType(string message) {

    int num = 0;

    do {

        cout << message;
        cin >> num;

    } while (num < 1 || num > 5);

    return (enOperationType)num;

}

int GetNumberByQuestionLevel(enQuestionsLevel QuestionLevel) {

    switch (QuestionLevel) {

    case enQuestionsLevel::Easy:
        return GetRandomNumber(1, 10);
    case enQuestionsLevel::Med:
        return GetRandomNumber(10, 100);
    case enQuestionsLevel::Hard:
        return GetRandomNumber(100, 500);
    case enQuestionsLevel::Mix1:
        return GetRandomNumber(1, 500);
     
    }

}

char GetOperationTypeSymbol(enOperationType OpType) {

    if (OpType == enOperationType::Mix) {

        OpType = (enOperationType)GetRandomNumber(1, 4);

    }

    switch (OpType) {

    case enOperationType::Add:
        return '+';
        break;
    case enOperationType::Sub:
        return '-';
        break;
    case enOperationType::Mult:
        return '*';
        break;
    case enOperationType::Div:
        return '/';
        break;

    }

}

int GetCorrectResult(int Num1, int Num2, char OpType ) {

   switch(OpType) {

   case '+':
       return Num1 + Num2;
       break;
   case '-':
       return Num1 - Num2;
       break;
   case '*':
       return Num1 * Num2;
       break;
   case '/':
       return int(Num1 / Num2);
       break;

    }

}

string GetQuestionLevelName(enQuestionsLevel QuestionLevel) {

    string arr[] = { "Easy", "Med",  "Hard" , "Mix" };

    return arr[QuestionLevel - 1];

}

string GetOperationTypeName(enOperationType OpType) {

    string arr[] = { "Add", "Sub",  "Mult" , "Div" , "Mix"};

    return arr[OpType - 1];

}

bool CheckWhetherTheUserAnswerIsCorrect(int UserResult, int CorrectResult) {

    return UserResult == CorrectResult;

}

stGameResult FillStGameResult(short NumberOfQuestions, enQuestionsLevel QuestionLevel, enOperationType OpType, short NumberOfRightAnswers, short NumberOfWrongAnswers) {

    stGameResult GameResult;

    GameResult.NumberOfQuestions = NumberOfQuestions;
    GameResult.QuestionsLevel = GetQuestionLevelName(QuestionLevel);
    GameResult.OpType = GetOperationTypeName(OpType);
    GameResult.NumberOfRightAnswers = NumberOfRightAnswers;
    GameResult.NumberOfWrongAnswers = NumberOfWrongAnswers;

    return GameResult;

}

stGameResult PlayGame(enOperationType OpType , enQuestionsLevel QuestionLevel, int Questions) {

    short  NumberOfRightAnswers = 0, NumberOfWrongAnswers = 0;

    for (int Question = 1; Question <= Questions; Question++) {

        cout << endl << "Question [" << Question << "/" << Questions << "]\n";

        int Num1 = GetNumberByQuestionLevel(QuestionLevel);
        cout << endl << Num1 << endl;

        int Num2 = GetNumberByQuestionLevel(QuestionLevel);
        cout << Num2;

        char OpType1 = GetOperationTypeSymbol(OpType);

        cout << " " << OpType1 << endl;
        cout << "--------------" << endl;

        int UserResult = ReadNumber();

        int CorrectResult = GetCorrectResult(Num1, Num2, OpType1);

        if (CheckWhetherTheUserAnswerIsCorrect(UserResult, CorrectResult)) {

            cout << "\nRight Answer :-)\n";
            system("color 2F");
            NumberOfRightAnswers++;

        }
        else {

            cout << "\nWrong Answer :-(\n";
            cout << "The right answer is : " << CorrectResult << endl;
            system("color 4F");
            NumberOfWrongAnswers++;

        }

    }

    return FillStGameResult(Questions, QuestionLevel, OpType ,NumberOfRightAnswers, NumberOfWrongAnswers);

}

string GetFinalResult(stGameResult GameResult) {

    if (GameResult.NumberOfRightAnswers > GameResult.NumberOfWrongAnswers) {

        system("color 2F");
        return "Final Result is Pass :-)";

    }
    else if (GameResult.NumberOfRightAnswers < GameResult.NumberOfWrongAnswers) {

        system("color 4F");
        return "Final Result is Failed :-(";

    }
    else {
        
        system("color 6F");
        return "Final Result is Draw";

    }

}

void FinalResult(stGameResult GameResult) {

    cout << "\n------------------------------------------------------------------\n\n";
    cout << " " << GetFinalResult(GameResult) << endl << endl;
    cout << "------------------------------------------------------------------\n\n";

}

void GameOver(stGameResult GameResult) {

    cout << "Number of Questions         : " << GameResult.NumberOfQuestions << endl;
    cout << "Questions Level             : " << GameResult.QuestionsLevel << endl;
    cout << "OpType                      : " << GameResult.OpType << endl;
    cout << "Number of Right Answers     : " << GameResult.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers     : " << GameResult.NumberOfWrongAnswers << endl;

    cout << "------------------------------------------------------------------\n\n";

}

void StartGame() {

    char PlayAgain;

    do {

        ResetScreen();

        stGameResult GameResult = PlayGame(ReadOperationType("\nEnter Operation Type [1] Add, [2] Sub , [3] Mul , [4] Div , [5] Mix ? ") ,
                                           ReadQuestionLevel("\nEnter Questions Level [1] Easy, [2] Med , [3] Hard , [4] Mix ? ") ,
                                           HowManyQuestions()
                                           );

        FinalResult(GameResult);
        GameOver(GameResult);


        cout << "Do you want to play again Y/N ? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'y' || PlayAgain == 'Y');

}

int main()
{

    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}


