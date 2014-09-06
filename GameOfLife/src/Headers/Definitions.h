#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream> 
#include <math.h>
#include <stdlib.h>
#include <QPoint>
#include <QLinearGradient>
#include <memory>

typedef std::pair<unsigned int, unsigned int> coord;
typedef coord* coordPtr;
typedef std::shared_ptr<coord> shCoord;

/*
typedef bool (*ComparatorFunctionType)(Cell&, Cell&);
*/
// RENDER_BOARD DEFINTIONS
#define DEFAULT_BOARD_SIZE 200
#define DEFAULT_CELL_SIZE 2
#define MAX_DISTANCE 1000


// PREY DEFINITIONS
#define MAX_NUMBER_OF_NEIGHBOURHOODS_FOR_LIVE 6 // DON"T CHANGE !!!
#define MIN_NUMBER_OF_NEIGHBOURHOODS_TO_REPRODUCE 3 // DON"T CHANGE !!!
#define MAX_NUMBER_OF_NEIGHBOURHOODS_TO_REPRODUCE 3	// we take into account that who initiate
													// reproduction; really prey need to reproduce
													// only 3 neighbourhoods // DON"T CHANGE !!!
// PREDATOR DEFINITIONS
#define MAX_HUNGER_EXTENTION 6
#define DOESNT_HUNGRY 3
#define MAX_WITHOUT_REPRODUCTION 3
#define MAX_SINGELNESS 36

// CHARACTERISTIC DEFINITIONS
#define PREY_LIFE_CYCLE_EXTENTION 8 // DON"T CHANGE !!! (the best is 6)
#define PREDATOR_LIFE_CYCLE_EXTENTION 18
	
#define PREY_SPEED 2 // DON"T CHANGE !!!
#define PREDATOR_SPEED 6

#define DEFAULT_VISION 10

#define PARENT_PROBABILITY 0x1
#define SPEED_MUTATION_PROBABILITY 0x3
#define STRANGTH_MUTATION_PROBABILITY 0x7
#define VISION_MUTATION_PROBABILITY 0x7
#define ORIENTATION_MUTATION_PROBABILITY 0xf
#define LIFE_MUTATION_PROBABILITY 0xf
#define OMNIVOROUS_PROBABILITY 0xfff
#define BLACK_SPAWN_PROBABILITY 0xfff

// BOARD DEFINTIONS
#define RANDOMIZATOR 10000
#define RANDOM_LIMIT 600
#define RANDOM_LIMIT_LIMIT 1000

// CHAOS FUNCTION DEFINITION
#define A -1.5			// chaotic function: x_new = (a*x_old) + y_old; y_new = b+(x_old*x_old);
#define B -2.1			//
#define X_DOWN_LIMIT	-2.0
#define X_UP_LIMIT		1
#define Y_DOWN_LIMIT	-3.0
#define Y_UP_LIMIT		0

class Definitions
{
public:
	static QLinearGradient omnivorousLinearGradient;
	static QLinearGradient predatorLinearGradient;
	static QLinearGradient childLinearGradient;
	static QLinearGradient preyLinearGradient;

	QPoint* pointsDown;
	QPoint* pointsLeft;
	QPoint* pointsUp;
	QPoint* pointsRight;

	unsigned int halfCellSize;

	Definitions( ) : halfCellSize(DEFAULT_CELL_SIZE)
	{
		omnivorousLinearGradient.setColorAt(0.0, Qt::yellow);
		omnivorousLinearGradient.setColorAt(1.0, Qt::black);
		
		predatorLinearGradient.setColorAt(0.0, Qt::white);
		predatorLinearGradient.setColorAt(0.2, Qt::red);
		predatorLinearGradient.setColorAt(1.0, Qt::black);

		childLinearGradient.setColorAt(0.0, Qt::white);
		childLinearGradient.setColorAt(1.0, Qt::blue);

		preyLinearGradient.setColorAt(0.0, Qt::white);
		preyLinearGradient.setColorAt(1.0, Qt::green);

		pointsDown = new QPoint[3];
		pointsLeft = new QPoint[3];
		pointsUp = new QPoint[3];
		pointsRight = new QPoint[3];

		setNewCellSize(DEFAULT_CELL_SIZE);
	}

	void setNewCellSize(int newHalfSize)
	{
		halfCellSize = newHalfSize;

		pointsDown[0] = QPoint(0, 0);		
		pointsDown[1] = QPoint(newHalfSize, newHalfSize);
		pointsDown[2] = QPoint(0, 2*newHalfSize);
	
		pointsLeft[0] = QPoint(0, 0);
		pointsLeft[1] = QPoint(newHalfSize, newHalfSize);
		pointsLeft[2] = QPoint(2*newHalfSize, 0);
	
		pointsUp[0] = QPoint(2*newHalfSize, 0);
		pointsUp[1] = QPoint(newHalfSize, newHalfSize);
		pointsUp[2] = QPoint(2*newHalfSize, 2*newHalfSize);
		
		pointsRight[0] = QPoint(0, 2*newHalfSize);
		pointsRight[1] = QPoint(newHalfSize, newHalfSize);
		pointsRight[2] = QPoint(2*newHalfSize, 2*newHalfSize);
	}

	inline static coordPtr allocateArray(unsigned int halfSize)
	{
		unsigned int size = (halfSize << 1) + 1;
		return new coord[size*size];
	}
};

class Square
{
public:

	unsigned int m_leftDownX;
	unsigned int m_leftDownY;
	unsigned int m_leftUpY;
	unsigned int m_rightDownX;

	Square(
		unsigned int leftDownX,
		unsigned int rightDownX,
		unsigned int leftDownY,
		unsigned int leftUpY ) :
		m_leftDownX(leftDownX),
		m_leftDownY(leftDownY),
		m_leftUpY(leftUpY),
		m_rightDownX(rightDownX){ }
};

typedef std::shared_ptr<Square> shSquare;


/*
template <class T, int N>
class Array  
{
    T arr[N];
	
public:
 
    template <class ... T> Array(T ... p) : arr{p...} {}
    int size() { return N;}
    T operator[](int i) 
	{
		return (i < 0 || i >= N ? throw "ERROR: out of range": arr[i]);
	}    
};
*/



#endif // DEFINITIONS_H
