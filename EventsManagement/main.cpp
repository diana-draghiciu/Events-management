#include <iostream>
#include "EventRepository.h"
#include "TextFileRepo.h"
#include "CSVFileRepo.h"
#include "HtmlFileRepo.h"
#include "AdmController.h"
#include "UserController.h"
#include "AdministratorMode.h"
#include "UserMode.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <QApplication>
#include "guiADM.h"
#include "guiUSER.h"
#include "EventsManagement.h"
#include <qlayout.h>
#include <QMessageBox>

void userCSVHandler() {

    std::string file = "Events.txt";
    TextFileRepo *text = new TextFileRepo{ file };
    CommandManager* cmd = new CommandManager{};
    AdmController* as = new AdmController{ text, *cmd };
    CSVFileRepo* csv = new CSVFileRepo{ "Events.csv" };
    //--------------------------------------------
    EventRepository *repo_user = new EventRepository();
    csv->save();
    UserController *uc = new UserController(csv, text);

    guiUSER* gui=new guiUSER{ uc,as,0 };
    gui->show();
}

void userHMTLHandler() {

    std::string file = "Events.txt";
    TextFileRepo* text = new TextFileRepo{ file };
    CommandManager* cmd = new CommandManager{};
    AdmController* as = new AdmController{ text ,*cmd};
    htmlFileRepo* ht = new htmlFileRepo{ "Events.html" };
    //--------------------------------------------
    EventRepository* repo_user = new EventRepository();
    ht->save();
    UserController* uc = new UserController( ht, text);

    guiUSER* gui = new guiUSER{ uc,as,0 };
    gui->show();
}

void adminHandler() {
    
    std::string file = "Events.txt";
    TextFileRepo *text = new TextFileRepo{ file };
    CommandManager* cmd = new CommandManager{};
    AdmController *as = new AdmController{ text ,*cmd};

    guiADM* gui=new guiADM{ as,0 };
    gui->show();
}

int main(int argc, char* argv[])
{

        QApplication app(argc, argv);
    
            QWidget* buttonsWidget = new QWidget{};
            QHBoxLayout* layout = new QHBoxLayout{ buttonsWidget };
            auto palette=buttonsWidget->palette();
            palette.setColor(QPalette::Window, Qt::gray);
            buttonsWidget->setPalette(palette);

            QFont f{ "Arial", 15 };
            QPushButton* userCSVButton = new QPushButton("User Mode CSV");
            userCSVButton->setFont(f);
            userCSVButton->setStyleSheet("background-color: rgb(255,229,204); border-color: black");
            QPushButton* userHTMLButton = new QPushButton("User Mode HTML");
            userHTMLButton->setFont(f);
            userHTMLButton->setStyleSheet("background-color: rgb(255,255,204); border-color: black");
            QPushButton* adminButton = new QPushButton("Administrator Mode");
            adminButton->setFont(f);
            adminButton->setStyleSheet("background-color: rgb(229, 255, 204); border-color: black ");
        
            layout->addWidget(userCSVButton);
            layout->addWidget(userHTMLButton);
            layout->addWidget(adminButton);

            layout->addWidget(buttonsWidget);
            
            QObject::connect(userCSVButton, &QPushButton::clicked, buttonsWidget, &userCSVHandler);
            QObject::connect(userHTMLButton, &QPushButton::clicked, buttonsWidget, &userHMTLHandler);
            QObject::connect(adminButton, &QPushButton::clicked, buttonsWidget, &adminHandler);
        
            buttonsWidget->show();
      
        return app.exec();
}
         

