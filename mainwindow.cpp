#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "riskplayer.hpp"
#include "riskplayer.cpp"
#include "riskterritory.hpp"
#include "riskterritory.cpp"
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <random>
#include <QString>
#include <QProcess>
using namespace std;

Player Dan("Daniel", 0);
Player Cole("Cole", 1);
Player Powell("Powell", 2);
Player players[3] = { Dan,Cole,Powell };
Territory West_Campus("West Campus", "West", { "FitRec", "Stuvi","CGS" });
Territory FitRec("FitRec", "West", { "West Campus", "Stuvi","CGS" });
Territory Stuvi("Stuvi", "West", { "FitRec", "West Campus","CGS","GSU" });                  // initialize the players and territories
Territory CGS("CGS", "West", { "FitRec", "Stuvi","West Campus","Warren" });
Territory GSU("GSU", "Central", { "CAS","Comm","Warren","Stuvi" });
Territory CAS("CAS", "Central", { "GSU","Comm","Warren","Bay State" });
Territory Comm("Comm", "Central", { "CAS","GSU","Warren","Questrom" });
Territory Warren("Warren", "Central", { "CAS","GSU","Comm","CGS" });
Territory Questrom("Questrom", "East", { "Bay State","Kilachand", "Bookstore","Comm" });
Territory Bay_State("Bay State", "East", { "Questrom","Kilachand", "Bookstore","CAS" });
Territory Kilachand("Kilachand", "East", { "Questrom","Bay State", "Bookstore" });
Territory Bookstore("Bookstore", "East", { "Questrom","Bay State","Kilachand" });
Territory territories[12] = { West_Campus,FitRec,Stuvi,CGS,GSU,CAS,Comm,Warren,Questrom,Bay_State,Kilachand,Bookstore };

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Risk - Campus Domination");
///Users/powellvince/Downloads/Final Files/rhett-cartoon.gif
    QPixmap risk_logo("/Users/powellvince/Downloads/Final Files/risklogo.jpg");
    ui->label_50->setScaledContents(true);
    ui->label_50->setPixmap(risk_logo);
    QPixmap bu_logo("/Users/powellvince/Downloads/Final Files/bu_logo.png");           // set the starting images and button
    ui->label_51->setScaledContents(true);
    ui->label_51->setPixmap(bu_logo);
    QPixmap rhett("/Users/powellvince/Downloads/Final Files/rhett-cartoon.gif");
    ui->label_52->setScaledContents(true);
    ui->label_52->setPixmap(rhett);
    ui->label_52->hide();
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    ui->pushButton_6->hide();
    ui->label_48->hide();
/*
    halo_song = new QMediaPlayer(this);
    halo_song->setMedia(QUrl::fromLocalFile("/Users/powellvince/Downloads/Final Files/halo.mp3"));
    halo_song->setVolume(50);
    halo_song->play();                  // start the game music
*/

    halo_song = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    playlist->addMedia(QUrl::fromLocalFile("/Users/powellvince/Downloads/Final Files/halo.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    halo_song->setPlaylist(playlist);
    halo_song->setVolume(50);
    halo_song->play();          // start the game music


    ui->label_9->hide();
    ui->comboBox->hide();
    ui->frame_2->hide();
    ui->frame_3->hide();
    ui->pushButton_8->hide();
    ui->pushButton_7->hide();
    ui->pushButton_3->hide();
    ui->pushButton_2->hide();
    ui->pushButton->hide();
    ui->label_44->hide();
    ui->label_43->hide();
    ui->label_42->hide();
    ui->label_41->hide();
    ui->label_40->hide();
    ui->label_39->hide();
    ui->label_38->hide();
    ui->label_37->hide();
    ui->label_36->hide();
    ui->label_35->hide();
    ui->label_34->hide();
    ui->label_33->hide();
    ui->label_21->hide();           // hide everything else
    ui->label_20->hide();
    ui->label_19->hide();
    ui->label_18->hide();
    ui->label_17->hide();
    ui->label_16->hide();
    ui->label_15->hide();
    ui->label_14->hide();
    ui->label_13->hide();
    ui->label_12->hide();
    ui->label_11->hide();
    ui->label_10->hide();
    ui->label_9->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_6->hide();
    ui->label_5->hide();
    ui->label_4->hide();
    ui->label_3->hide();
    ui->label_2->hide();
    ui->label->hide();
    ui->frame_13->hide();
    ui->frame_12->hide();
    ui->frame_11->hide();
    ui->frame_10->hide();
    ui->frame_9->hide();
    ui->frame_8->hide();
    ui->frame_7->hide();
    ui->frame_6->hide();
    ui->frame_5->hide();
    ui->frame_4->hide();
    ui->frame_3->hide();
    ui->frame_2->hide();
    ui->label_7->hide();
    ui->line->hide();
    ui->label_53->hide();
    ui->label_22->hide();
    ui->label_23->hide();
    ui->label_24->hide();
    ui->label_25->hide();
    ui->label_26->hide();
    ui->label_27->hide();
    ui->label_28->hide();
    ui->label_29->hide();
    ui->label_30->hide();
    ui->label_31->hide();
    ui->label_32->hide();
    ui->label_45->hide();
    ui->label_46->hide();
    ui->label_47->hide();


    ui->pushButton_5->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
}

void bonus_troops(Player& player) {	//gives troop bonus for owning continents
    int west_count = 0;
    int central_count = 0;
    int east_count = 0;
    for (auto ter : player.ter_controlled) {
        for (int j = 0; j < 12; j++) {
            if (ter == territories[j].name) {
                if (territories[j].continent == "West") {
                    west_count++;
                }
                if (territories[j].continent == "Central") {
                    central_count++;
                }
                if (territories[j].continent == "East") {
                    east_count++;
                }
            }
        }
    }
    if (west_count == 4) {
        player.troops += 3;
    }
    if (central_count == 4) {
        player.troops += 3;
    }
    if (east_count == 4) {
        player.troops += 3;
    }
}

MainWindow::~MainWindow()
{
    delete ui;              // close the window
}

void MainWindow::on_pushButton_3_clicked()      // "Allocate Students" button
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox->removeItem(j);        // remove everything previously in the dropdown
        }
    }
    ui->label_4->setText("Where do you want to \n place your students?");
    ui->comboBox->show();
    ui->pushButton_7->show();
    ui->pushButton_8->show();       // show the appropriate cancel and confirm buttons
    vector<QString> ter;
    if (ui->label_22->text() == "Dan") {
        for (vector<string>::size_type i = 0; i < Dan.ter_controlled.size(); i++) {
                ter.push_back(QString::fromStdString(Dan.ter_controlled[i]));
        }
    }
    else if (ui->label_22->text() == "Cole") {
        for (vector<string>::size_type i = 0; i < Cole.ter_controlled.size(); i++) {        // populate the QString vector
                ter.push_back(QString::fromStdString(Cole.ter_controlled[i]));
        }
    }
    else {
        for (vector<string>::size_type i = 0; i < Powell.ter_controlled.size(); i++) {
                ter.push_back(QString::fromStdString(Powell.ter_controlled[i]));
        }
    }
    for (auto t: ter) {
        ui->comboBox->addItem(t);       // put the QString vector items into the dropdown
    }
}

void MainWindow::on_pushButton_7_clicked()      // the confirm button corresponding to allocating students
{
    if (ui->label_22->text() == "Dan") {
        if ((ui->comboBox->currentText()).toStdString() == "West Campus") {
            ui->label_33->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[0].troops)));
            territories[0].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "FitRec") {
            ui->label_34->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[1].troops)));
            territories[1].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Stuvi") {
            ui->label_35->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[2].troops)));
            territories[2].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CGS") {
            ui->label_36->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[3].troops)));
            territories[3].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "GSU") {
            ui->label_37->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[4].troops)));
            territories[4].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CAS") {
            ui->label_39->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[5].troops)));
            territories[5].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Comm") {
            ui->label_40->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[6].troops)));
            territories[6].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Warren") {
            ui->label_38->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[7].troops)));
            territories[7].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Questrom") {
            ui->label_42->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[8].troops)));
            territories[8].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bay State") {
            ui->label_41->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[9].troops)));
            territories[9].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Kilachand") {
            ui->label_43->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[10].troops)));
            territories[10].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bookstore") {
            ui->label_44->setText("Student count: " + QString::number((ui->label_6->text()).toInt() + (territories[11].troops)));
            territories[11].troops += (ui->label_6->text()).toInt();
        }
        ui->label_6->setText("0");
        Dan.troops = 0;
    }
    else if (ui->label_22->text() == "Cole") {
        if ((ui->comboBox->currentText()).toStdString() == "West Campus") {
            ui->label_33->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[0].troops)));
            territories[0].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "FitRec") {
            ui->label_34->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[1].troops)));
            territories[1].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Stuvi") {
            ui->label_35->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[2].troops)));
            territories[2].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CGS") {
            ui->label_36->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[3].troops)));
            territories[3].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "GSU") {
            ui->label_37->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[4].troops)));
            territories[4].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CAS") {
            ui->label_39->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[5].troops)));
            territories[5].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Comm") {
            ui->label_40->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[6].troops)));
            territories[6].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Warren") {
            ui->label_38->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[7].troops)));
            territories[7].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Questrom") {
            ui->label_42->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[8].troops)));
            territories[8].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bay State") {
            ui->label_41->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[9].troops)));
            territories[9].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Kilachand") {
            ui->label_43->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[10].troops)));
            territories[10].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bookstore") {
            ui->label_44->setText("Student count: " + QString::number((ui->label_7->text()).toInt() + (territories[11].troops)));
            territories[11].troops += (ui->label_6->text()).toInt();
        }
        ui->label_7->setText("0");
        Cole.troops = 0;
    }
    else {
        if ((ui->comboBox->currentText()).toStdString() == "West Campus") {
            ui->label_33->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[0].troops)));
            territories[0].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "FitRec") {
            ui->label_34->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[1].troops)));
            territories[1].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Stuvi") {
            ui->label_35->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[2].troops)));
            territories[2].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CGS") {
            ui->label_36->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[3].troops)));
            territories[3].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "GSU") {
            ui->label_37->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[4].troops)));
            territories[4].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "CAS") {
            ui->label_39->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[5].troops)));
            territories[5].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Comm") {
            ui->label_40->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[6].troops)));
            territories[6].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Warren") {
            ui->label_38->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[7].troops)));
            territories[7].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Questrom") {
            ui->label_42->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[8].troops)));
            territories[8].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bay State") {
            ui->label_41->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[9].troops)));
            territories[9].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Kilachand") {
            ui->label_43->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[10].troops)));
            territories[10].troops += (ui->label_6->text()).toInt();
        }
        else if ((ui->comboBox->currentText()).toStdString() == "Bookstore") {
            ui->label_44->setText("Student count: " + QString::number((ui->label_8->text()).toInt() + (territories[11].troops)));
            territories[11].troops += (ui->label_6->text()).toInt();
        }
        ui->label_8->setText("0");
        Powell.troops = 0;
    }

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox->removeItem(j);
        }
    }
    ui->comboBox->hide();
    ui->label_4->setText("");           // allocate the students, update that territory's troop count,
    ui->pushButton_7->hide();           // set the player's troops to 0, delete everything in the dropdown,
    ui->pushButton_8->hide();           // and hide the corresponding buttons and dropdown
    ui->pushButton_3->hide();
    ui->label_52->show();               // also, show Rhett
}

void MainWindow::on_pushButton_15_clicked()
{

}

void MainWindow::on_pushButton_8_clicked()
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox->removeItem(j);
        }
    }
    ui->comboBox->hide();
    ui->label_4->setText("");               // the cancel button for allocating troops
    ui->pushButton_7->hide();               // hides the appropriate buttons and dropdown
    ui->pushButton_8->hide();               // and deletes the items from the dropdown
}

void MainWindow::on_pushButton_12_clicked()
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_2->removeItem(j);
        }
    }
    ui->comboBox_2->hide();
    ui->label_23->setText("");
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {         // the cancel button for the attack button
            ui->comboBox_3->removeItem(j);
        }
    }
    ui->comboBox_3->hide();                     // does the same as other cancel buttons
    ui->label_23->setText("");
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
}

void MainWindow::on_pushButton_4_clicked()      // the "Start Game!" button
{
    ui->label_49->hide();
    ui->label_50->hide();       // hides the initial images
    ui->label_51->hide();
    ui->label_53->show();
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            ui->label_33->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_6->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("West Campus");
            }
            else if (territories[i].color == "green") {
                ui->frame_6->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("West Campus");
            }
            else  {
                ui->frame_6->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("West Campus");
            }
        }
        else if (i == 1) {
            ui->label_34->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_8->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("FitRec");
            }
            else if (territories[i].color == "green") {
                ui->frame_8->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("FitRec");
            }
            else  {
                ui->frame_8->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("FitRec");
            }
        }
        else if (i == 2) {
            ui->label_35->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_2->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Stuvi");
            }
            else if (territories[i].color == "green") {
                ui->frame_2->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Stuvi");
            }
            else  {
                ui->frame_2->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Stuvi");
            }
        }
        else if (i == 3) {
            ui->label_36->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_5->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("CGS");
            }
            else if (territories[i].color == "green") {
                ui->frame_5->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("CGS");
            }
            else  {
                ui->frame_5->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("CGS");
            }
        }
        else if (i == 4) {
            ui->label_37->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_7->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("GSU");
            }
            else if (territories[i].color == "green") {
                ui->frame_7->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("GSU");
            }
            else  {
                ui->frame_7->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("GSU");
            }
        }
        else if (i == 5) {
            ui->label_39->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_9->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("CAS");
            }
            else if (territories[i].color == "green") {
                ui->frame_9->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("CAS");
            }
            else  {
                ui->frame_9->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("CAS");
            }
        }
        else if (i == 6) {
            ui->label_40->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_3->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Comm");
            }
            else if (territories[i].color == "green") {
                ui->frame_3->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Comm");
            }
            else  {
                ui->frame_3->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Comm");
            }
        }
        else if (i == 7) {
            ui->label_38->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_4->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Warren");
            }
            else if (territories[i].color == "green") {
                ui->frame_4->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Warren");
            }
            else  {
                ui->frame_4->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Warren");
            }
        }
        else if (i == 8) {
            ui->label_42->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_10->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Questrom");
            }
            else if (territories[i].color == "green") {
                ui->frame_10->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Questrom");
            }
            else  {
                ui->frame_10->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Questrom");
            }
        }
        else if (i == 9) {
            ui->label_41->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_11->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Bay State");
            }
            else if (territories[i].color == "green") {
                ui->frame_11->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Bay State");
            }
            else  {
                ui->frame_11->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Bay State");
            }
        }
        else if (i == 10) {
            ui->label_43->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_12->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Kilachand");
            }
            else if (territories[i].color == "green") {
                ui->frame_12->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Kilachand");
            }
            else  {
                ui->frame_12->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Kilachand");
            }
        }
        else if (i == 11) {
            ui->label_44->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_13->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
                Cole.gain_control("Bookstore");
            }
            else if (territories[i].color == "green") {
                ui->frame_13->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
                Dan.gain_control("Bookstore");
            }
            else  {
                ui->frame_13->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
                Powell.gain_control("Bookstore");
            }
        }
    }
    // sets up the territories properly according to the initializations

    ui->label_6->setText(QString::fromStdString(to_string(Dan.troops)));
    ui->label_8->setText(QString::fromStdString(to_string(Powell.troops)));
    ui->pushButton_4->close();
    Cole.cavalry();
    bonus_troops(Cole);
    ui->label_7->setText(QString::fromStdString(to_string(Cole.troops)));
    ui->label_22->setText("Cole");
    ui->label_9->show();
    ui->frame_2->show();
    ui->frame_3->show();
    ui->pushButton_3->show();
    ui->pushButton_2->show();
    ui->pushButton->show();
    ui->label_44->show();           // shows all the appropriate buttons, labels, and frames
    ui->label_43->show();           // and starts the beginning turn
    ui->label_42->show();
    ui->label_41->show();
    ui->label_40->show();
    ui->label_39->show();
    ui->label_38->show();
    ui->label_37->show();
    ui->label_36->show();
    ui->label_35->show();
    ui->label_34->show();
    ui->label_33->show();
    ui->label_21->show();
    ui->label_20->show();
    ui->label_19->show();
    ui->label_18->show();
    ui->label_17->show();
    ui->label_16->show();
    ui->label_15->show();
    ui->label_14->show();
    ui->label_13->show();
    ui->label_12->show();
    ui->label_11->show();
    ui->label_10->show();
    ui->label_9->show();
    ui->label_8->show();
    ui->label_9->show();
    ui->label_6->show();
    ui->label_5->show();
    ui->label_4->show();
    ui->label_3->show();
    ui->label_2->show();
    ui->label->show();
    ui->frame_13->show();
    ui->frame_12->show();
    ui->frame_11->show();
    ui->frame_10->show();
    ui->frame_9->show();
    ui->frame_8->show();
    ui->frame_7->show();
    ui->frame_6->show();
    ui->frame_5->show();
    ui->frame_4->show();
    ui->frame_3->show();
    ui->frame_2->show();
    ui->label_7->show();
    ui->line->show();
    ui->label_22->show();
    ui->label_23->show();

    ui->pushButton_5->show();

    QPixmap baystate("/Users/powellvince/Downloads/Final Files/baystate.jpg");
    ui->label_47->setScaledContents(true);
    ui->label_47->setPixmap(baystate);

    QPixmap bookstore("/Users/powellvince/Downloads/Final Files/bookstore.jpg");
    ui->label_24->setScaledContents(true);
    ui->label_24->setPixmap(bookstore);

    QPixmap cas("/Users/powellvince/Downloads/Final Files/cas.jpg");
    ui->label_25->setScaledContents(true);
    ui->label_25->setPixmap(cas);

    QPixmap cgs("/Users/powellvince/Downloads/Final Files/cgs.jpg");
    ui->label_26->setScaledContents(true);
    ui->label_26->setPixmap(cgs);

    QPixmap comm("/Users/powellvince/Downloads/Final Files/comm.jpg");
    ui->label_27->setScaledContents(true);
    ui->label_27->setPixmap(comm);

    QPixmap fitrec("/Users/powellvince/Downloads/Final Files/FitRec.jpg");
    ui->label_28->setScaledContents(true);
    ui->label_28->setPixmap(fitrec);

    QPixmap gsu("/Users/powellvince/Downloads/Final Files/gsu.jpg");
    ui->label_29->setScaledContents(true);
    ui->label_29->setPixmap(gsu);

    QPixmap khc("/Users/powellvince/Downloads/Final Files/khc.jpg");
    ui->label_30->setScaledContents(true);
    ui->label_30->setPixmap(khc);

    QPixmap questrom("/Users/powellvince/Downloads/Final Files/questrom.jpg");
    ui->label_31->setScaledContents(true);
    ui->label_31->setPixmap(questrom);

    QPixmap stuvi("/Users/powellvince/Downloads/Final Files/stuvi.jpg");
    ui->label_32->setScaledContents(true);
    ui->label_32->setPixmap(stuvi);

    QPixmap warren("/Users/powellvince/Downloads/Final Files/warren.jpg");
    ui->label_45->setScaledContents(true);
    ui->label_45->setPixmap(warren);

    QPixmap west("/Users/powellvince/Downloads/Final Files/west.jpg");
    ui->label_46->setScaledContents(true);
    ui->label_46->setPixmap(west);

    ui->label_24->show();
    ui->label_25->show();
    ui->label_26->show();
    ui->label_27->show();
    ui->label_28->show();
    ui->label_29->show();
    ui->label_30->show();
    ui->label_31->show();
    ui->label_32->show();
    ui->label_45->show();
    ui->label_46->show();
    ui->label_47->show();

}

void MainWindow::on_pushButton_5_clicked()
{

}

bool is_dominated(Territory territories[12]) {

    string dom_name = territories[0].color;
    string check_name;
    int terrs_checked = 0;

    for (int i = 1; i < 12; i++) {
        check_name = territories[i].color;          // checks to see if someone has won
        if (check_name == dom_name) {
            terrs_checked++;
        }
        else {
            return false;
        }
    }

    if (terrs_checked == 11) {
        return true;
    }

    return false;
}

void MainWindow::on_pushButton_2_clicked()      // the "End Turn" button
{
    if (is_dominated(territories)) {
        ui->pushButton_10->hide();
        ui->pushButton_9->hide();
        ui->label_53->hide();       // if someone has won,
        ui->label_9->hide();
        ui->comboBox->hide();
        ui->frame_2->hide();
        ui->frame_3->hide();
        ui->pushButton_8->hide();
        ui->pushButton_7->hide();
        ui->pushButton_3->hide();
        ui->pushButton_2->hide();
        ui->pushButton->hide();
        ui->label_44->hide();
        ui->label_43->hide();
        ui->label_42->hide();
        ui->label_41->hide();
        ui->label_40->hide();       // hides everything
        ui->label_39->hide();
        ui->label_38->hide();
        ui->label_37->hide();
        ui->label_36->hide();
        ui->label_35->hide();
        ui->label_34->hide();
        ui->label_33->hide();
        ui->label_21->hide();
        ui->label_20->hide();
        ui->label_19->hide();
        ui->label_18->hide();
        ui->label_17->hide();
        ui->label_16->hide();
        ui->label_15->hide();
        ui->label_14->hide();
        ui->label_13->hide();
        ui->label_12->hide();
        ui->label_11->hide();
        ui->label_10->hide();
        ui->label_9->hide();
        ui->label_8->hide();
        ui->label_9->hide();
        ui->label_6->hide();
        ui->label_5->hide();
        ui->label_4->hide();
        ui->label_3->hide();
        ui->label_2->hide();
        ui->label->hide();
        ui->frame_13->hide();
        ui->frame_12->hide();
        ui->frame_11->hide();
        ui->frame_10->hide();
        ui->frame_9->hide();
        ui->frame_8->hide();
        ui->frame_7->hide();
        ui->frame_6->hide();
        ui->frame_5->hide();
        ui->frame_4->hide();
        ui->frame_3->hide();
        ui->frame_2->hide();
        ui->label_7->hide();
        ui->line->hide();

        ui->label_22->hide();
        ui->label_23->hide();
        ui->label_24->hide();
        ui->label_25->hide();
        ui->label_26->hide();
        ui->label_27->hide();
        ui->label_28->hide();
        ui->label_29->hide();
        ui->label_30->hide();
        ui->label_31->hide();
        ui->label_32->hide();
        ui->label_45->hide();
        ui->label_46->hide();
        ui->label_47->hide();
        ui->label_49->show();
        ui->label_50->show();
        ui->label_51->show();
        ui->pushButton_5->hide();
        ui->comboBox_2->hide();
        ui->comboBox_3->hide();         // and shows the victory screen
        ui->pushButton_11->hide();
        ui->pushButton_12->hide();
       // ui->pushButton_3->hide();
        ui->pushButton_6->hide();
        ui->label_52->hide();
        ui->label_48->show();

        fireworks_song = new QMediaPlayer(this);
        fireworks_song->setMedia(QUrl::fromLocalFile("/Users/colejohnson/Downloads/Fireworks And Crowd-SoundBible.com-81665534.mp3"));
        fireworks_song->setVolume(80);
        fireworks_song->play();

    }
    else {
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                ui->comboBox->removeItem(j);
            }
        }
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                ui->comboBox_2->removeItem(j);          // otherwise, it deletes everything from the three dropdowns
            }
        }
        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                ui->comboBox_3->removeItem(j);
            }
        }
        ui->comboBox->hide();
        ui->comboBox_2->hide();
        ui->comboBox_3->hide();
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();          // hides the right buttons
        ui->label_23->setText("");          // and shows the right ones
        ui->label_4->setText("");
        ui->pushButton_7->hide();
        ui->pushButton_8->hide();
        ui->pushButton_11->hide();
        ui->label_52->hide();
        ui->pushButton_12->hide();
        ui->pushButton_3->show();
        ui->comboBox_2->hide();
        if (ui->label_22->text() == "Dan") {
            ui->label_22->setText("Cole");
            Cole.cavalry();
            bonus_troops(Cole);
            ui->label_7->setText(QString::fromStdString(to_string(Cole.troops)));
        }
        else if (ui->label_22->text() == "Cole") {
            ui->label_22->setText("Powell");
            Powell.cavalry();
            bonus_troops(Powell);
            ui->label_8->setText(QString::fromStdString(to_string(Powell.troops)));     // and provides the appropriate beginning-of-turn bonuses
        }
        else {
            ui->label_22->setText("Dan");
            Dan.cavalry();
            bonus_troops(Dan);
            ui->label_6->setText(QString::fromStdString(to_string(Dan.troops)));
        }
    }
}


void MainWindow::on_pushButton_clicked() // attack button
{



    ui->pushButton_10->show();
    ui->pushButton_9->show();
    ui->pushButton_3->hide();
    ui->pushButton_11->hide();          // hides the student allocation stuff
    ui->comboBox_3->hide();             // and displays Rhett
    ui->pushButton_12->hide();
    ui->label_52->show();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_2->removeItem(j);      // initially makes sure the attack from dropdown is unpopulated
        }
    }
    ui->label_23->setText("From where would\n you like to begin\n   your assault?");
    ui->label_23->show();
    vector<QString> ter;
    if (ui->label_22->text() == "Dan") {
        for (vector<string>::size_type i = 0; i < Dan.ter_controlled.size(); i++) {
            ter.push_back(QString::fromStdString(Dan.ter_controlled[i]));
        }
    }
    else if (ui->label_22->text() == "Cole") {
        for (vector<string>::size_type i = 0; i < Cole.ter_controlled.size(); i++) {        // finds the player's controlled territories
            ter.push_back(QString::fromStdString(Cole.ter_controlled[i]));
        }
    }
    else {
        for (vector<string>::size_type i = 0; i < Powell.ter_controlled.size(); i++) {
            ter.push_back(QString::fromStdString(Powell.ter_controlled[i]));
        }
    }
    for (auto t: ter) {
        ui->comboBox_2->addItem(t);         // and adds each one the dropdown
    }
    ui->comboBox_2->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_2->removeItem(j);
        }
    }
    ui->comboBox_2->hide();                 // another cancel button for the attack phase
    ui->label_23->setText("");
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
}

void MainWindow::on_pushButton_10_clicked()
{
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_3->removeItem(j);          // removes everything from the attack to dropdown
        }
    }

    ui->pushButton_10->hide();
    ui->label_23->setText("Where would you\n  like to attack?");        // shows the appropriate buttons
    ui->pushButton_9->hide();
    ui->label_52->show();

    string attack_from = ui->comboBox_2->currentText().toStdString();       // remembers the attack from choice
    vector<QString> place_attack;
    vector<QString>::iterator help;

    for (int i = 0; i < 12; i++) {
        vector<string>::iterator border_finder;
        if (ui->label_22->text() == "Dan") {
            if (attack_from == territories[i].name) {
                for (vector<string>::size_type j=0; j < territories[i].borders.size(); j++) {
                    help = std::find(place_attack.begin(), place_attack.end(), QString::fromStdString(territories[i].borders[j]));
                    border_finder = std::find(Dan.ter_controlled.begin(), Dan.ter_controlled.end(), territories[i].borders[j]);
                    if (border_finder == Dan.ter_controlled.end() && help == place_attack.end()) {
                        place_attack.push_back(QString::fromStdString(territories[i].borders[j]));
                    }
                }
            }
        }
        else if (ui->label_22->text() == "Cole") {
            if (attack_from == territories[i].name) {
                for (vector<string>::size_type j=0; j < territories[i].borders.size(); j++) {
                    help = std::find(place_attack.begin(), place_attack.end(), QString::fromStdString(territories[i].borders[j]));
                    border_finder = std::find(Cole.ter_controlled.begin(), Cole.ter_controlled.end(), territories[i].borders[j]);
                    if (border_finder == Cole.ter_controlled.end() && help == place_attack.end()) {
                        place_attack.push_back(QString::fromStdString(territories[i].borders[j]));
                    }
                }
            }
        }
        else {
            if (attack_from == territories[i].name) {
                for (vector<string>::size_type j=0; j < territories[i].borders.size(); j++) {
                    help = std::find(place_attack.begin(), place_attack.end(), QString::fromStdString(territories[i].borders[j]));
                    border_finder = std::find(Powell.ter_controlled.begin(), Powell.ter_controlled.end(), territories[i].borders[j]);
                    if (border_finder == Powell.ter_controlled.end() && help == place_attack.end()) {
                        place_attack.push_back(QString::fromStdString(territories[i].borders[j]));
                    }
                }
            }
        }
    }


    // finds the appropriate places the player can attack based on controlled territories and borders


    for (auto t: place_attack) {
        ui->comboBox_3->addItem(t);     // populates the dropdown with the correct territories
    }
    ui->comboBox_2->hide();
    ui->comboBox_3->show(); // show drop down attackable territories
    ui->pushButton_11->show();
    ui->pushButton_12->show();
    place_attack = {};
}

void MainWindow::on_pushButton_11_clicked()     // the confirm attack choices button
{
    attack_song = new QMediaPlayer(this);
    attack_song->setMedia(QUrl::fromLocalFile("/Users/powellvince/Downloads/Final Files/gun.wav"));
    attack_song->setVolume(80);
    attack_song->play();                // plays gunshot sound

    string attack_from = ui->comboBox_2->currentText().toStdString();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_2->removeItem(j);
        }
    }
    string attack_to = ui->comboBox_3->currentText().toStdString();     // removes items from the combo boxes after saving the choices
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_3->removeItem(j);
        }
    }
    for (int i = 0; i < 12; i++) {
        if (attack_from == territories[i].name) {
            for (int j = 0; j < 12; j++) {
                if (attack_to == territories[j].name) {
                    if (territories[j].troops <= 0) {
                        if (ui->label_22->text() == "Dan") {
                            if (territories[j].color == "red") {
                                Cole.lose_control(territories[j].name);
                            }
                            else {
                                Powell.lose_control(territories[j].name);
                            }
                            territories[j].color = "green";
                            Dan.gain_control(territories[j].name);
                        }
                        else if (ui->label_22->text() == "Cole") {
                            if (territories[j].color == "blue") {
                                Powell.lose_control(territories[j].name);       // reallocates territories if a win has been achieved
                            }
                            else {
                                Dan.lose_control(territories[j].name);
                            }
                            territories[j].color = "red";
                            Cole.gain_control(territories[j].name);
                        }
                        else {
                            if (territories[j].color == "green") {
                                Dan.lose_control(territories[j].name);
                            }
                            else {
                                Cole.lose_control(territories[j].name);
                            }
                            territories[j].color = "blue";
                            Powell.gain_control(territories[j].name);
                        }
                        territories[j].troops = territories[i].troops - 1;
                        territories[i].troops = 1;
                    }
                    else {
                        int attacker[3];
                        int defender[2];
                        random_device rd;
                        mt19937 dice(rd());
                        uniform_int_distribution<> dis(1, 6);
                        for (int i = 0; i < 2; i++) {
                            attacker[i] = dis(dice);
                            defender[i] = dis(dice);                // otherwise, the attack algorithm runs
                        }
                        attacker[2] = dis(dice);
                        sort(attacker, attacker + 3);               // is "random" with three dice for the attacker and two for the defender
                        sort(defender, defender + 2);
                        cout << territories[i].owner << " rolled:";
                        if (attacker[2] > defender[1])              // the highest roll from each is compared, then the second highest
                            --territories[j].troops;
                        else
                            --territories[i].troops;
                        if (attacker[1] > defender[0] && territories[i].troops > 1 && territories[j].troops > 0)
                            --territories[j].troops;
                        else if (territories[i].troops > 1 && territories[j].troops > 0)    // changes the troop numbers based on the outcome
                            --territories[i].troops;
                    }
                }
            }
        }
    }
    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            ui->label_33->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_6->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_6->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_6->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 1) {
            ui->label_34->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_8->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_8->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_8->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 2) {
            ui->label_35->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_2->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_2->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_2->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 3) {
            ui->label_36->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_5->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_5->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_5->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 4) {
            ui->label_37->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_7->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_7->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_7->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 5) {
            ui->label_39->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_9->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_9->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_9->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 6) {
            ui->label_40->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_3->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_3->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_3->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 7) {
            ui->label_38->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_4->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_4->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_4->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 8) {
            ui->label_42->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_10->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_10->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_10->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 9) {
            ui->label_41->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_11->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_11->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_11->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 10) {
            ui->label_43->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_12->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_12->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_12->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
        else if (i == 11) {
            ui->label_44->setText("Student Count: " + QString::fromStdString(to_string(territories[i].troops)));
            if (territories[i].color == "red") {
                ui->frame_13->setStyleSheet("background-color: rgba(255, 78, 103, 38)");
            }
            else if (territories[i].color == "green") {
                ui->frame_13->setStyleSheet("background-color: rgba(46, 255, 35, 38)");
            }
            else  {
                ui->frame_13->setStyleSheet("background-color: rgba(51, 151, 255, 38)");
            }
        }
    }


    // reevaluates the territory control


    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_2->removeItem(j);      // removes dropdown items
        }
    }
    ui->comboBox_2->hide();
    ui->label_23->setText("");
    ui->pushButton_10->hide();
    ui->pushButton_9->hide();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            ui->comboBox_3->removeItem(j);
        }
    }
    ui->comboBox_3->hide();
    ui->label_23->setText("");              // and hides the correct buttons
    ui->pushButton_11->hide();
    ui->pushButton_12->hide();
}
void MainWindow::on_pushButton_6_clicked()
{
   // ui->setupUi(this);
}
