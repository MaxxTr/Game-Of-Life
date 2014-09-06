#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include <QStringListModel>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QPainter>
#include <QSpinBox>
#include <QLabel>
#include "RenderBoard.h"
#include "Prey.h"
#include "Predator.h"
#include "ui_RunTimeInformation.h"
#include "ui_HelpWindow.h"

class GameOfLife : public QWidget
{
	Q_OBJECT

public:

    GameOfLife(QWidget *parent = 0, Qt::WindowFlags flags = 0) :

		m_width(DEFAULT_BOARD_SIZE),
		m_height(DEFAULT_BOARD_SIZE),
		m_board(NULL),
		m_zoom(DEFAULT_CELL_SIZE),
		m_started(false),
		m_onPause(true),
		m_infoWidget(NULL)
	{
		QVBoxLayout* verticalLayout = new QVBoxLayout;
		setLayout(verticalLayout);

		QLabel* widthLabel = new QLabel("Width");
		QSpinBox* widthSpinBox = new QSpinBox;
		widthSpinBox->setRange(0, 400);
		widthSpinBox->setValue(2*DEFAULT_BOARD_SIZE);
		connect(widthSpinBox, SIGNAL(valueChanged(int)),
             this, SLOT(widthChanged(int)));
		QHBoxLayout* widthLayout = new QHBoxLayout;
		widthLayout->addWidget(widthLabel);
		widthLayout->addWidget(widthSpinBox);

		QLabel* hightLabel = new QLabel("Hight");
		QSpinBox* hightSpinBox = new QSpinBox;
		hightSpinBox->setRange(0, 400);
		hightSpinBox->setValue(DEFAULT_BOARD_SIZE);
		connect(hightSpinBox, SIGNAL(valueChanged(int)),
             this, SLOT(hightChanged(int)));
		QHBoxLayout* hightLayout = new QHBoxLayout;
		hightLayout->addWidget(hightLabel);
		hightLayout->addWidget(hightSpinBox);
/*
		QLabel* zoomLabel = new QLabel("Zoom");
		QSpinBox* zoomSpinBox = new QSpinBox;
		zoomSpinBox->setRange(1, 40);
		zoomSpinBox->setValue(DEFAULT_CELL_SIZE);
		connect(zoomSpinBox, SIGNAL(valueChanged(int)),
             this, SLOT(zoomChanged(int)));
		QHBoxLayout* zoomLayout = new QHBoxLayout;
		zoomLayout->addWidget(zoomLabel);
		zoomLayout->addWidget(zoomSpinBox);
*/
		startButton = new QPushButton("Start");
		connect(startButton, SIGNAL(clicked( )),
             this, SLOT(startClicked()));
		pauseButton = new QPushButton("Pause");
		pauseButton->setEnabled(false);
		connect(pauseButton, SIGNAL(clicked( )),
             this, SLOT(pauseClicked()));
		stopButton = new QPushButton("Stop");
		stopButton->setEnabled(false);
		connect(stopButton, SIGNAL(clicked( )),
             this, SLOT(stopClicked()));
		nextButton = new QPushButton("Next Iteration");
		connect(nextButton, SIGNAL(clicked( )),
             this, SLOT(nextClicked()));
		infoButton = new QPushButton("RunTime Info");
		connect(infoButton, SIGNAL(clicked( )),
             this, SLOT(infoClicked()));
		QPushButton* helpButton = new QPushButton("Help");
		connect(helpButton, SIGNAL(clicked( )),
             this, SLOT(helpClicked()));
		QHBoxLayout* buttonLayout = new QHBoxLayout;
		buttonLayout->addWidget(startButton);
		buttonLayout->addWidget(nextButton);
		buttonLayout->addWidget(pauseButton);
		buttonLayout->addWidget(stopButton);
		buttonLayout->addWidget(infoButton);
		buttonLayout->addWidget(helpButton);
		
		QHBoxLayout* dataLayout = new QHBoxLayout;
		m_board = new RenderBoard();
		dataLayout->addWidget(m_board);
		QVBoxLayout* infoLayout = new QVBoxLayout;
		dataLayout->addLayout(infoLayout);

		verticalLayout->addLayout(widthLayout);
		verticalLayout->addLayout(hightLayout);
		//verticalLayout->addLayout(zoomLayout);
		verticalLayout->addLayout(buttonLayout);
		verticalLayout->addLayout(dataLayout);
		setFocusPolicy( Qt::StrongFocus );
	}

	void focusInEvent ( QFocusEvent * fEvent )
	{
		m_board->onFocus();
	}

public slots:
	
	void widthChanged(int val)
	{
		m_width = val;
		m_board->setWidth(val);
		resize(m_width*2*m_zoom, m_height*2*m_zoom);
	}

	void hightChanged(int val)
	{
		m_height = val;
		m_board->setHeight(val);
		resize(m_width*2*m_zoom, m_height*2*m_zoom);
	}

	void startClicked()
	{
		if(m_width == 0 || m_height == 0)
		{
			return;
		}
		m_board->start();
		m_started = true;
		m_onPause = false;
		startButton->setEnabled(false);
		pauseButton->setEnabled(true);
		stopButton->setEnabled(true);
		QTimer::singleShot(100, this, SLOT(nextLoop()));
		return;
	}

	void nextClicked()
	{
		m_board->next();
		return;
	}

	void pauseClicked()
	{
		startButton->setEnabled(true);
		pauseButton->setEnabled(false);
		stopButton->setEnabled(false);
		m_onPause = true;
		if(m_started)
		{
			m_board->pause();
		}
	}

	void stopClicked()
	{
		startButton->setEnabled(true);
		pauseButton->setEnabled(false);
		stopButton->setEnabled(false);
		m_onPause = true;
		m_board->stop();
	}

	void zoomChanged(int val)
	{
		m_zoom = val;
		m_board->zoomChanged(val);
	}

	void infoClicked()
	{
		if(m_infoWidget != NULL)
		{
			delete m_infoWidget;
		}
		m_infoWidget = new QMainWindow;
		m_ui.setupUi(m_infoWidget);
		updateInfoUI( );
		m_infoWidget->show();
	}

	void setGlobalInformation()
	{
		m_ui.labelIteration->setText("Iteration: " + QString::number(m_board->getIteration()));
		m_ui.labelTime->setText("Time Of Iteration: " + QString::number(m_board->getIterationTime()) + " sec.");
	}

	void setGroupInformation()
	{
		std::map<unsigned int, unsigned int>& pMap = m_board->getPredatorGroupMembersNumMap();
		QStringList slData;
		for(auto it = pMap.begin(); it != pMap.end(); ++it)
		{
			std::pair<unsigned int, unsigned int> p = *it;
			slData.append("Group " + QString::number(p.first) + " : " + QString::number(p.second));
		}
		m_ui.listView->setModel(new QStringListModel(slData));
		QStringList slPreyData;
		slPreyData.append("Number Of Preys: " + QString::number(m_board->getPreysNum()));
		m_ui.listViewPrey->setModel(new QStringListModel(slPreyData));
	}

	void setBestPredatorInformation()
	{
		shPredator p = m_board->getBestPredator();
		if(p != NULL)
		{
			m_ui.labelLifePredator->setText("Life: " + QString::number(p->getLife()));
			m_ui.labelStrenghPredator->setText("Strengh: " + QString::number(p->getStrength()));
			m_ui.labelSpeedPredator->setText("Speed: " + QString::number(p->getSpeed()));
			m_ui.labelVisionPredator->setText("Vision: " + QString::number(p->getVision()));
			m_ui.labelPolicyPredator->setText("Policy: " + QString(p->getLifePolicyStr().c_str()));
			m_ui.labelGroupIDPredator->setText("GroupID: " + QString::number(p->getGroupID()));
			QString status = p->isInLife() ? "Live" : "Dead";
			m_ui.labelStatusPredator->setText("Status: " + status);
		}
	}

	void setBestPreyInformation()
	{
		shPrey p = m_board->getBestPrey();
		if(p != NULL)
		{
			m_ui.labelLifePrey->setText("Life: " + QString::number(p->getLife()));
			m_ui.labelStrenghPrey->setText("Strengh: " + QString::number(p->getStrength()));
			m_ui.labelSpeedPrey->setText("Speed: " + QString::number(p->getSpeed()));
			m_ui.labelVisionPrey->setText("Vision: " + QString::number(p->getVision()));
			m_ui.labelPolicyPrey->setText("Policy: " + QString(p->getLifePolicyStr().c_str()));
			QString status = p->isInLife() ? "Live" : "Dead";
			m_ui.labelStatusPrey->setText("Status: " + status);
		}
	}

	void helpClicked()
	{
		QMainWindow* helpWnd = new QMainWindow;
		Ui::HelpWindow ui;
		ui.setupUi(helpWnd);
		ui.textBrowser->insertHtml(m_helpText);
		updateInfoUI( );
		helpWnd->show();
	}

protected slots:

	void nextLoop()
	{
		if(!m_onPause)
		{
			m_board->nextLoop();
			QTimer::singleShot(100, this, SLOT(nextLoop()));
		}
	}

	void updateInfoUI( )
	{
		if(m_infoWidget != NULL)
		{
			setGlobalInformation();
			setGroupInformation();
			setBestPredatorInformation();
			setBestPreyInformation();
			m_infoWidget->update();
			QTimer::singleShot(1000, this, SLOT(updateInfoUI()));
		}
	}

public:
	
	~GameOfLife()
	{
		delete m_board;
	}

private:

	RenderBoard* m_board;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_zoom;
	bool m_started;
	bool m_onPause;

	QPushButton* startButton;
	QPushButton* pauseButton;
	QPushButton* stopButton;
	QPushButton* nextButton;
	QPushButton* infoButton;
	
	Ui::RunTimeInformation m_ui;
	QMainWindow* m_infoWidget;

	static const QString m_helpText;
};

#endif // GAMEOFLIFE_H
