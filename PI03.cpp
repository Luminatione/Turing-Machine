#include <iostream>
#include <vector>
#include <string>

enum symbol { zero = 0, one = 1, blank = 2 };

class Move
{
public:
	int state;
	symbol symbol;
	bool rightDirection;
};
std::vector<std::vector<Move>> moves
{
{{1, blank, true}, {5, blank, true} },
	{{1, zero, true}, {2, one, true}},
	{{3, one, false}, {2, one, true}, {4, blank, false}},
	{{3,zero, false}, {3, one, false}, {0, blank, true}},
	{{4, zero, false}, {4, blank, false}, {6, zero, true}},
	{{5, blank, true}, {5, blank, true}, {6, blank, true}},
	{}
};
class AutoExpandableTapeVector
{
public:
	std::vector<symbol> values;

	symbol& operator [](int index)
	{
		if (index >= values.size())
		{
			values.resize(index + 1, blank);
		}
		return values[index];
	}

};

//int to unary
std::vector<symbol> itou(int a)
{
	return std::vector<symbol>(a, zero);
}
void insertNMIntoTape(AutoExpandableTapeVector& tape, int m, int n)
{
	std::vector<symbol> mU = itou(m);
	std::vector<symbol> nU = itou(n);
	tape.values.insert(tape.values.end(), mU.begin(), mU.end());
	tape.values.push_back(one);
	tape.values.insert(tape.values.end(), nU.begin(), nU.end());
}
char symbolToChar(symbol symbol)
{
	return symbol != blank ? symbol + 48 : 'B';
}
char boolToDirectionIdentifier(bool isRight)
{
	return isRight ? 'P' : 'L';
}
void printTape(AutoExpandableTapeVector tape)
{
	for (int i = 0; i < tape.values.size(); i++)
	{
		std::string buf;
		buf += symbolToChar(tape[i]);
		if(tape[i] == one || tape[i] == zero)
		{
			std::cout << buf;
			buf = "";
		}

	}
	std::cout << "\n";
}
void printTape(AutoExpandableTapeVector tape, Move currentMove, int tapeIndex)
{
	int i = 0;
	while(tape[i] != blank || i <= tapeIndex)
	{
		if (i == tapeIndex)
		{
			std::cout << "[q" << currentMove.state << "]";
		}
		if(i != tapeIndex || tape[i] != blank)
		{
			std::cout << symbolToChar(tape[i]);
		}
		++i;
	}
	/*for (int i = 0; i < tape.values.size(); i++)
	{
		std::string buf;
		buf += symbolToChar(tape[i]);
		if(i == tapeIndex)
		{
			std::cout << "[q" << currentMove.symbol << "]";
		}
		if (tape.values[i] == one || tape.values[i] == zero)
		{
			std::cout << buf;
			buf = "";
		}

	}*/
	std::cout << "\n";
}
int main()
{
	std::cout << "M=({q0, q1, q2, q3, q4, q5, q6}, {0,1}, {0,1,B}, g, q0, B, 0)\n gdzie g to delta\n";
	int n, m;
	std::cout << "Podaj m:";
	std::cin >> m;
	std::cout << "Podaj n:";
	std::cin >> n;
	AutoExpandableTapeVector tape;
	insertNMIntoTape(tape, m, n);
	std::cout << "Tasma wejscowa: ";
	printTape(tape);
	int state = 0, tapeIndex = 0;
	Move currentMove{0, blank, true};
	while (state != 6)
	{
		printTape(tape, currentMove, tapeIndex);
		currentMove = moves[state][tape[tapeIndex]];
		tape[tapeIndex] = currentMove.symbol;
		state = currentMove.state;
		tapeIndex += int(2 * (float(currentMove.rightDirection) - 0.5f));
	}
	printTape(tape, currentMove, tapeIndex);
	int result = 0;
	for (int i = 0; i < tape.values.size(); i++)
	{
		result += tape[i] != blank && tape[i] != one;
	}
	std::cout << "Wynik to " << result;
	return 0;
}