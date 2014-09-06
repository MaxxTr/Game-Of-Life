#ifndef RENDER_BOARD_H
#define RENDER_BOARD_H

#include <QPen>
#include <QTimer>
#include <QMessageBox>
#include <QResizeEvent>
#include <QFocusEvent>

#include "../Headers/Board.h"

class RenderBoard : public QWidget
{
	Q_OBJECT

public:

	RenderBoard(QWidget *parent = 0)
		: QWidget(parent),
		m_width(DEFAULT_BOARD_SIZE*2*2*DEFAULT_CELL_SIZE),
		m_height(DEFAULT_BOARD_SIZE*2*DEFAULT_CELL_SIZE),
		m_zoom(DEFAULT_CELL_SIZE),
		m_cells_board(NULL),
		m_bDraw(false),
		m_continue(false),
		m_drawPrey(false),
		m_drawAreas(false),
		m_mousePressed(false),
		m_Saturation(RANDOM_LIMIT),
		m_radius(0),
		m_onPause(true),
		m_iterationTime(0),
		m_startIterationTime(0),
		m_iteration(0),
		m_ableToRunNextIteration(true)
	{
		setBackgroundRole(QPalette::Base);
		setAutoFillBackground(true);
		m_bDraw = true;
		update();
	}

	~RenderBoard()
	{
		if(m_cells_board != NULL)
		{
			m_cells_board->quit();
			m_cells_board->wait();
			delete m_cells_board;
		}
	}

	QSize minimumSizeHint() const
	{
		return QSize(m_width, m_height);
	}

	QSize sizeHint() const
	{
		return QSize(m_width, m_height);
	}

	void setHeight(int val)
	{
		m_height = val*2*m_def.halfCellSize;
		if(m_cells_board != NULL)
		{
			m_cells_board->quit();
			m_cells_board->wait();
			delete m_cells_board;
		}
		m_bDraw = true;
		update();
	}

	void setWidth(int val)
	{
		m_width = val*4*m_def.halfCellSize;
		if(m_cells_board != NULL)
		{
			m_cells_board->quit();
			m_cells_board->wait();
			delete m_cells_board;
		}
		m_bDraw = true;
		update();
	}

	void pause()
	{
		m_onPause = true;
	}

	void start()
	{
		m_onPause = false;
	}

	void stop()
	{
		if(m_cells_board != NULL)
		{
			m_cells_board->quit();
			m_cells_board->wait();
			delete m_cells_board;
			m_cells_board = NULL;
		}
		m_bDraw = true;
		update();
	}

	void resizeEvent ( QResizeEvent* rEvent ) 
	{
		rEvent->accept();
		m_bDraw = true;
		update();
	}

	void focusInEvent ( QFocusEvent * fEvent )
	{
		fEvent->accept();
		m_bDraw = true;
		update();
	}

	void onFocus()
	{
		m_bDraw = true;
		update();
	}

	void wheelEvent(QWheelEvent *event)
	{
		if(m_mousePressed)
		{
			int numDegrees = event->delta() / 6;
			m_Saturation += numDegrees;
			if(m_Saturation < 0 )
			{
				m_Saturation = 0;
			}
			if(m_Saturation > RANDOM_LIMIT_LIMIT)
			{
				m_Saturation = RANDOM_LIMIT_LIMIT;
			}
			if(m_drawPrey)
			{
				drawPreysArea();
			}
			else
			{
				drawPredatorsArea();
			}
		}
	}

	void mousePressEvent(QMouseEvent *mEvent)
	{
		if(m_onPause)
		{
			m_Saturation= RANDOM_LIMIT;
			if (mEvent->button() == Qt::RightButton)
			{
				m_predatorsStartPoint = mEvent->pos();
			}
			if (mEvent->button() == Qt::LeftButton)
			{
				m_preysStartPoint = mEvent->pos();
			}
			m_mousePressed = true;
		}/*
		else
		{
			shCell cell = m_cells_board->get(mEvent->x()/(2*m_def.halfCellSize), mEvent->y()/(2*m_def.halfCellSize));
			QMessageBox msgBox;
			msgBox.setText(cell->getStringInfo().c_str());
			msgBox.exec();
		}*/
	}

	void mouseMoveEvent(QMouseEvent *mEvent)
	{
		if (!mEvent->buttons())
		{
			return;
		}
		if(mEvent->buttons() & Qt::RightButton )
		{
			unsigned int curRadius = (mEvent->pos() - m_predatorsStartPoint).manhattanLength();
			m_radius = curRadius;
			drawPredatorsArea( );
		}
		if(mEvent->buttons() & Qt::LeftButton )
		{
			unsigned int curRadius = (mEvent->pos() - m_preysStartPoint).manhattanLength();
			m_radius = curRadius;
			drawPreysArea( );
		}	
	}

	void mouseReleaseEvent(QMouseEvent *mEvent)
	{
		unsigned int radius = m_radius/(4*m_def.halfCellSize);
		if(radius > std::min(m_width, m_height))
		{
			radius = std::min(m_width-1, m_height-1);
		}
		if(m_cells_board == NULL)
		{
			m_iteration = 0;
			m_cells_board = new Board(m_width/(2*m_def.halfCellSize), m_height/(2*m_def.halfCellSize));
			connect(m_cells_board, SIGNAL(iterationFinished()), this, SLOT(iterationFinished()), Qt::QueuedConnection);
		}
		if(mEvent->button() == Qt::RightButton )
		{
			m_cells_board->settleBoardWithPredators(
				m_Saturation,
				radius,
				m_predatorsStartPoint.x()/(2*m_def.halfCellSize),
				m_predatorsStartPoint.y()/(2*m_def.halfCellSize));
		}
		if(mEvent->button() == Qt::LeftButton )
		{
			m_cells_board->settleBoardWithPreys(
				m_Saturation,
				radius,
				m_preysStartPoint.x()/(2*m_def.halfCellSize),
				m_preysStartPoint.y()/(2*m_def.halfCellSize));
		}
		m_bDraw = true;
		m_drawAreas = false;
		m_mousePressed = false;
		update();
	}

	void drawPredatorsArea( )
	{
		QRadialGradient gradient(m_predatorsStartPoint, m_radius, m_predatorsStartPoint);
		gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
		double middlePoint = (RANDOM_LIMIT_LIMIT - m_Saturation)/(double)RANDOM_LIMIT_LIMIT;
		gradient.setColorAt(middlePoint, QColor::fromRgbF(1, 0, 0, 1));
		gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
		QBrush brush(gradient);
		m_brush = brush;
		m_drawPrey = false;
		m_bDraw = true;
		m_drawAreas = true;
		update();
	}

	void drawPreysArea( )
	{
		QRadialGradient gradient(m_preysStartPoint, m_radius, m_preysStartPoint);
		gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
		double middlePoint = (RANDOM_LIMIT_LIMIT - m_Saturation)/(double)RANDOM_LIMIT_LIMIT;
		gradient.setColorAt(middlePoint, QColor::fromRgbF(0, 1, 0, 1));
		gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
		QBrush brush(gradient);
		m_brush = brush;
		m_drawPrey = true;
		m_bDraw = true;
		m_drawAreas = true;
		update();
	}

	void zoomChanged(int val)
	{
		m_zoom = val;
		m_def.setNewCellSize(m_zoom);
		m_bDraw = true;
		update();
	}

	void nextLoop()
	{
		if(m_cells_board != NULL && m_ableToRunNextIteration)
		{
			m_startIterationTime = time(0);
			m_cells_board->start();
			m_ableToRunNextIteration = false;
		}
	}

	void next()
	{
		if(m_cells_board != NULL && m_ableToRunNextIteration)
		{
			m_onPause = false;
			m_startIterationTime = time(0);
			m_cells_board->start();
			m_ableToRunNextIteration = false;
		}
	}

	inline std::map<unsigned int, unsigned int>& getPredatorGroupMembersNumMap(){
			return m_cells_board->getPredatorGroupMembersNumMap();}
	inline shPredator getBestPredator(){return m_cells_board->getBestPredator();}
	inline shPrey getBestPrey(){return m_cells_board->getBestPrey();}

	inline unsigned int getIteration(){return m_iteration;}
	inline int getIterationTime(){return m_iterationTime;}
	inline int getPredatorsNum(){return m_cells_board->getPredatorsNum();}
	inline int getPreysNum(){return m_cells_board->getPreysNum();}

private slots:

	void iterationFinished()
	{
		m_iterationTime = time(0) - m_startIterationTime;
		m_startIterationTime = 0;
		++m_iteration;
		m_bDraw = true;
		m_ableToRunNextIteration = true;
		update();
	}

protected:

	void paintEvent(QPaintEvent *event)
	{
		if(m_bDraw)
		{
			QPainter painter(this);
			if(m_drawAreas)
			{
				painter.setBrush(m_brush);
				painter.setPen(Qt::white);
				if(m_drawPrey)
				{
					painter.drawEllipse(m_preysStartPoint, m_radius, m_radius);		
				}
				else
				{
					painter.drawEllipse(m_predatorsStartPoint, m_radius, m_radius);	
				}
				m_drawAreas = false;
			}
			if(m_cells_board != NULL)
			{
				m_cells_board->drawItself(&painter, m_def);
			}
			m_bDraw = false;
		}
	}

private:
	
	QPixmap pixmap;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_zoom;

	Board* m_cells_board;

	bool m_continue;
	bool m_bDraw;
	Definitions m_def;

	QBrush m_brush;
	QPixmap m_pixmap;
	QPoint m_predatorsStartPoint;
	QPoint m_preysStartPoint;

	time_t m_startIterationTime;
	unsigned int m_iterationTime;
	unsigned int m_iteration;
	unsigned int m_Saturation;
	unsigned int m_radius;
	bool m_drawPrey;
	bool m_drawAreas;
	bool m_mousePressed;

	bool m_onPause;
	bool m_ableToRunNextIteration;
};


#endif

