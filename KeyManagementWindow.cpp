#include<QWidget>
#include<QHeaderView>
#include<QTableWidgetItem>
#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<ios>
#include"boost/filesystem.hpp"
#include"KeyManagementWindow.h"
#include"Encryption.h"
#include"GenerateKeys.h"
#include"KeyRetrieval.h"
#include"FileNameRetrieval.h"
#include"FolderStructure.h"
#include"Key.h"

KeyManagementWindow::KeyManagementWindow(QWidget* parent) : QDialog(parent)
{
	setupWindow();
	connections();
}
KeyManagementWindow::KeyManagementWindow(QWidget* parent, MainWindow* mw, PasswordManagementWindow* pw) : QDialog(parent), mw(mw), pw(pw)
{
	setupWindow();
	connections();
}


void KeyManagementWindow::setContentsOfComboBox()
{
	selectionBox.get()->clear();
	FileNameRetrieval fnr;
	fnr.retrieveFileNames();
	vector<string> fn{fnr.fileNameContainer()};

	for (auto fle: fn)
	{
		QString bl{QString::fromStdString(fle)};
		selectionBox.get()->addItem(bl);
	}
}
void KeyManagementWindow::setContentOfKeyView()
{
	QString testQ;
	testQ.append(selectionBox.get()->currentText());
	string testS{FolderStructure::keyDirectory+testQ.toStdString()};
	
	KeyRetrieval kr{testS};
	vector<int> asciiKeys{kr.codeCharacterStructure()};
	vector<string> asciiAssignment{kr.keyStructure()};

	auto asciiKeysIter = asciiKeys.begin();
	auto asciiAssignmentIter = asciiAssignment.begin();
	for (auto row=0; row!=rowCount; ++row)
	{
		for (auto column=0; column!=columnCount; ++column)
		{
			if (column==0)
			{
				string val;
				QString s;
				switch (*asciiKeysIter)
				{
					case 10:
						val.assign("New Line");	
						s.append(val.c_str());
						++asciiKeysIter;
						break;
					case 32:
						val.assign("White space");
						s.append(val.c_str());
						++asciiKeysIter;
						break;
					default:
						val.assign(string{static_cast<char>(*asciiKeysIter++)});
						s.append(val.c_str());
						break;
				}
				elementView.get()->setItem(row, column, new QTableWidgetItem(s));
			}	
			else
			{
				string val{*asciiAssignmentIter++};
				QString s{val.c_str()};
				elementView.get()->setItem(row, column, new QTableWidgetItem(s));
			}
		}
	}	
}
void KeyManagementWindow::setupWindow()
{
	windowWidth = 450;
	windowHeight = 450;
	rowCount = 96;
	columnCount = 2;

	elementView = unique_ptr<QTableWidget>{new QTableWidget};

	elementView.get()->setRowCount(rowCount);
	elementView.get()->setColumnCount(columnCount);
	tableHeader<<"character"<<"key";
	elementView.get()->setHorizontalHeaderLabels(tableHeader);
	elementView.get()->verticalHeader()->setVisible(false);

	selectionBox = unique_ptr<QComboBox>{new QComboBox{}};

	generateNewKeys = unique_ptr<QPushButton>{new QPushButton(tr("Generate New Default Key"))};
	closeButton = unique_ptr<QPushButton>{new QPushButton(tr("close"))};
	actionButton = unique_ptr<QPushButton>{new QPushButton};

	mainLayout = unique_ptr<QHBoxLayout>{new QHBoxLayout};
	subLayoutOne = unique_ptr<QVBoxLayout>{new QVBoxLayout};
	subLayoutTwo = unique_ptr<QVBoxLayout>{new QVBoxLayout};

	subLayoutGoonOne = unique_ptr<QVBoxLayout>{new QVBoxLayout};
	subLayoutGoonTwo = unique_ptr<QVBoxLayout>{new QVBoxLayout};

	subLayoutOne.get()->addWidget(elementView.get());

	subLayoutGoonOne.get()->addWidget(selectionBox.get());
	subLayoutGoonOne.get()->addWidget(actionButton.get());
	subLayoutGoonTwo.get()->addWidget(generateNewKeys.get());
	subLayoutGoonTwo.get()->addWidget(closeButton.get());

	subLayoutTwo.get()->addLayout(subLayoutGoonOne.get());
	subLayoutTwo.get()->addLayout(subLayoutGoonTwo.get());


	mainLayout.get()->addLayout(subLayoutOne.get());
	mainLayout.get()->addLayout(subLayoutTwo.get());


	setContentsOfComboBox();

	setLayout(mainLayout.get());

	setFixedWidth(windowWidth);
	setFixedHeight(windowHeight);

	setWindowTitle("Key Management Window");
}
void KeyManagementWindow::connections()
{
	QObject::connect(generateNewKeys.get(), SIGNAL(clicked()), this, SLOT(generation()));
	QObject::connect(closeButton.get(), SIGNAL(clicked()), this, SLOT(exitApplication()));
	QObject::connect(actionButton.get(), SIGNAL(clicked()), this, SLOT(setContentOfKeyView()));
}
void KeyManagementWindow::generation()
{
	GenerateKeys gk{};
	Key<> theKey{};
	gk.keyMove(theKey);
	gk.keyDump(theKey);
	setContentsOfComboBox();
	mw.get()->refreshComboBox();
	pw->setupContentOfComboBox();
}
void KeyManagementWindow::exitApplication() { this->hide(); }
