
#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
using namespace std;
enum enLevel { easy = 1, medium = 2, hard = 3, Lmix = 4 };
enum enMathArt { Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5 };

struct stQustionInfo
{
	enMathArt MathArt;
	short QustionNumber = 0;
	short a = 0;
	short b = 0;
	int UserAnswer = 0;
	bool isAnswerCorrect = 0;
};

struct stGameResult
{
	stQustionInfo QuestionInfoListe[100];
	enMathArt MathArt;
	enLevel Level;
	short HowManyRounds = 0;
	short RightAnswers = 0;
	short FalesAnswers = 0;
	string HasQuesSuccess;
};

bool QuesSuccess(short RightAnswers, short FalesAnswers)
{
	return RightAnswers >= FalesAnswers;
}

string PrintSuccesOrNot(short RightAnswers, short FalesAnswers)
{
	string  Arrstring[2] = { "not Success\a\n"," Success\n" };
	return Arrstring[QuesSuccess(RightAnswers, FalesAnswers)];
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short RechnenLevel(enLevel Level)
{
	short Number = 0;
	if (Level == enLevel::Lmix)
	{
		Level = enLevel(RandomNumber(1, 3));
	}
	switch (Level)
	{
	case enLevel::easy:
		return Number = RandomNumber(1, 9);
		break;
	case enLevel::medium:
		return Number = RandomNumber(10, 25);
		break;
	case enLevel::hard:
		return Number = RandomNumber(25, 50);
		break;
	}

}

string PrintMathArt(enMathArt MathArt)
{
	string ArrMathArt[4] = { " +"," -"," *"," /" };
	return ArrMathArt[MathArt - 1];
}

string PrintMathLevelInEnd(enLevel MathArt)
{
	string ArrMathArt[4] = { "Easy","Middel","Hard","Mix" };
	return ArrMathArt[MathArt - 1];
}

string PrintMathArtInEnd(enMathArt MathArt)
{
	string ArrMathArt[5] = { "Add","Sub","Mult","Div","Mix" };
	return ArrMathArt[MathArt - 1];
}

int Rechnen(enMathArt MathArt, short a, short b)
{

	switch (MathArt)
	{
	case Add:
		return a + b;
		break;
	case Sub:
		return a - b;
		break;
	case Mul:
		return a * b;
		break;
	case Div:
		return a / b;
		break;
	default:
		break;
	}
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

enMathArt MathArtRechnen(enMathArt MathArt)
{
	if (MathArt == 5)
		return enMathArt(RandomNumber(1, 4));
	else return enMathArt(MathArt);
}

short ReadHowManyQuestion()
{
	short num = 0;
	do {
		cout << "How many rounds do you want to play ?\nfrom 1 to 10 \n";
		cin >> num;
	} while (num < 0 || num>10);
	return num;
}

int ReadUserAnswer()
{
	int num = 0;
	cin >> num;
	return num;
}

short ReadMathArt()
{
	short num = 0;
	do {
		cout << " Wich Math Art do you wnat to play ?\n (1)Add,(2)Sub,(3)Maul,(4)Div,(5)Mix. ?\n";
		cin >> num;
	} while (num < 1 || num>5);
	return num;
}

short ReadMathLevel()
{
	short num = 0;
	do {
		cout << "Wich Level do you like to play ?\n (1)Easy,(2)Middel,(3)Hard,(4)Mix ? \n";
		cin >> num;
	} while (num < 0 || num>10);
	return num;
}

stQustionInfo GenerateQuestion(stGameResult& Qinfo)
{
	stQustionInfo Qustioninfo;
	Qustioninfo.MathArt = MathArtRechnen(Qinfo.MathArt);
	Qustioninfo.a = RechnenLevel(Qinfo.Level);
	Qustioninfo.b = RechnenLevel(Qinfo.Level);

	cout << Qustioninfo.a << endl << Qustioninfo.b << PrintMathArt(Qustioninfo.MathArt) << endl << "_________\n";
	Qustioninfo.UserAnswer = ReadUserAnswer();

	Qustioninfo.isAnswerCorrect = (Qustioninfo.UserAnswer == Rechnen(Qustioninfo.MathArt, Qustioninfo.a, Qustioninfo.b));
	if (Qustioninfo.isAnswerCorrect == 1)
	{
		Qinfo.RightAnswers++;
		system("Color 2F");
	}
	else
	{
		Qinfo.FalesAnswers++;
		system("Color 4F");
	}
	cout << " Computer Answer is : " << Rechnen(Qustioninfo.MathArt, Qustioninfo.a, Qustioninfo.b) << endl;
	return Qustioninfo;

}

void GenerateQuestionListe(stGameResult& GameInfo)
{
	for (short Question = 0; Question < GameInfo.HowManyRounds; Question++)
	{
		cout << "Question Number " << Question + 1 << endl;
		GameInfo.QuestionInfoListe[Question] = GenerateQuestion(GameInfo);


	}GameInfo.HasQuesSuccess = PrintSuccesOrNot(GameInfo.RightAnswers, GameInfo.FalesAnswers);
}

stGameResult PlayGame()
{

	stGameResult GameResult;

	GameResult.HowManyRounds = ReadHowManyQuestion();
	GameResult.Level = enLevel(ReadMathLevel());
	GameResult.MathArt = enMathArt(ReadMathArt());
	GenerateQuestionListe(GameResult);
	return GameResult;


}
string Tabs()
{
	string t = "\t";
	for (short num = 0; num < 3; num++)
	{
		t = t + "\t";
	}return t;
}

void GameOverScreen()
{
	cout << Tabs() << "_______G a m e  O v e r _____________" << Tabs() << endl;
	cout << Tabs() << "___________________________________________\n";

}

void PrintGameResult(stGameResult GameResult)
{

	GameOverScreen();
	cout << " Game Level    : " << PrintMathLevelInEnd(GameResult.Level) << endl;
	cout << " Math Art      : " << PrintMathArtInEnd(GameResult.MathArt) << endl;
	cout << " Rounds were    : " << GameResult.HowManyRounds << endl;
	cout << " Right Answer  : " << GameResult.RightAnswers << endl;
	cout << " False Answer  : " << GameResult.FalesAnswers << endl;
	cout << " you have      : " << GameResult.HasQuesSuccess << endl;
	if (QuesSuccess(GameResult.RightAnswers, GameResult.FalesAnswers) == true)
		system("Color 2F");
	else
		system("Color 4F");
	cout << "\n\n________________************_____________\n\n\n";
}

void StartQuez()
{
	char newstart = 'y';

	do {
		ResetScreen();


		PrintGameResult(PlayGame());
		cout << "Do you want to play again ?\n";
		cin >> newstart;

	} while (newstart == 'y' || newstart == 'Y');
}


int main()
{
	srand((unsigned)time(NULL));
	StartQuez();


}
