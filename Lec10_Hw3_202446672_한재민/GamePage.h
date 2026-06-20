#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QPoint>
#include <QPixmap>

// struct으로 행성 정보 설정
struct Planet{
    QString name;               //행성 이름
    QString resource;           //자원
    int amount;                 //자원 수량
    bool discovered = false;    //발견 여부
};
// 행성 간 경로 정보
struct Route{
    int fuelCost;               //이동시 연료 소모량
    int timeCost;               //이동 시간
    int requiredEngine;         //필요 엔진 레벨
};
//gamepage class
class GamePage : public QWidget
{
    Q_OBJECT
public:
    explicit GamePage(QWidget* parent = nullptr);
//상수 설정
private:
    static const int PLANET_COUNT = 7;
    static const int GOAL_PLANET = 6;
    //행성 좌표
    QPoint planetPos[PLANET_COUNT] =
    {
        QPoint(130,200), // Earth
        QPoint(180,270), // Mars
        QPoint(330,270), // Proxima
        QPoint(540,150), // TRAPPIST
        QPoint(840,80),  // Kepler
        QPoint(560,400), // Gliese
        QPoint(780,250)  // Kepler-186f
    };
    //행성 데이터{"행성","자원",획득량,탐사여부}
    Planet planets[PLANET_COUNT] = {
    {"Earth", "", 0, true},
    {"Mars","철",20,false},                     // alien material
    {"Proxima Centauri b", "연료", 60,false},
    {"TRAPPIST-1e", "식량", 15,false},
    {"Kepler-442b", "희귀광물", 15,false},
    {"Gliese 667 Cc", "부품", 10,false},        // engine part
    {"Kepler-186f", "", 0,false}
    };
    //행성 간 이동 그래프{연료소모, 소요날짜, 필요엔진레벨}
    Route graph[PLANET_COUNT][PLANET_COUNT] = {
        {{0,0,0},{15,2,1},{25,3,2},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},        //Earth
        {{15,2,1},{0,0,0},{20,2,2},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},        //Mars
        {{25,3,2},{20,2,2},{0,0,0},{25,3,2},{43,4,2},{0,0,0},{0,0,0}},      //Proxima Centauri b
        {{0,0,0},{0,0,0},{25,3,2},{0,0,0},{30,3,2},{37,4,2},{0,0,0}},       //TRAPPIST-1e
        {{0,0,0},{0,0,0},{43,4,2},{30,3,2},{0,0,0},{35,3,2},{0,0,0}},       //Kepler-442b
        {{0,0,0},{0,0,0},{40,4,2},{37,4,2},{35,3,2},{0,0,0},{51,5,3}},      //Gliese 667 Cc
        {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{51,5,3},{0,0,0}}          //Kepler-186f
    };
    //게임 상태 변수
    int currentPlanet = 0;          //현재위치
    int fuel = 100;                 //연료
    int food = 25;                  //식량
    int iron = 0;                   //철
    int rare = 0;                   //희귀자원
    int parts = 10;                 //부품
    int day = 1;                    //게임진행시간
    int engineLevel = 1;            //엔진레벨
    bool marsAlienFound = false;    //이벤트 
    bool gliesePartFound = false;
    int alienMaterial = 0;
    int upgradeStage = 0;
    int moveCount = 0;              //이동횟수
    int startDay = 1;               //시작기준 
    int MAX_FUEL = 100;             //최대연료
    int MAX_FOOD = 30;              //최대식량
    int selectedPlanet = -1;

    QLabel* statusLabel;
    QLabel* infoLabel;
    QPushButton* moveButton;
    QPushButton* upgradeButton;
    QPushButton* planetButtons[PLANET_COUNT];
    //함수
    void gameOver(const QString& reason);   //gameover 처리
    void updateStatus();                    //상태 UI 갱신
    void updatePlanetColors();              //현재 위치 표시
    void showPlanetInfo(int index);         //행성 정보 갱신
    void movePlanet();                      //이동 처리
    void gameClear();                       //gameclear 처리
};