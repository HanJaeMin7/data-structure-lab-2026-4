#include "GamePage.h"

//gamepage 생성자, 게임 UI 담당
GamePage::GamePage(QWidget* parent)
    : QWidget(parent)
{
    //화면을 좌우로 나누기, 좌측: 우주지도, 우측: 정보
    auto* mainLayout = new QHBoxLayout(this);
    //map(우주지도)
    QLabel* mapWidget = new QLabel;
    mapWidget->setFixedSize(1000, 600);     //크기 고정
    
    QPixmap map("space_map.jpg");
    mapWidget->setPixmap(
        map.scaled(
            mapWidget->size(),
            Qt::KeepAspectRatioByExpanding,
            Qt::SmoothTransformation
        )
    );

    //행성 버튼 스타일(각 버튼이 행성을 의미함. 그래프에서 노드 역할)
    for (int i = 0; i < PLANET_COUNT; i++)
    {
        planetButtons[i] = new QPushButton(mapWidget);
        planetButtons[i]->setText("");
        //노드 스타일(색깔, 사이즈, 형태)
        planetButtons[i]->resize(30, 30);
        planetButtons[i]->setStyleSheet(
            "QPushButton {"
            "background-color: #3498db;"
            "border-radius: 15px;"
            "border: 2px solid white;"
            "}"
            "QPushButton:hover {"
            "background-color: #5dade2;"
            "}"
        );
    }
    //행성 버튼 위치(노드를 화면 좌표로 직접 지정)
    planetButtons[0]->move(130, 270);  // Earth
    planetButtons[1]->move(180, 270);  // Mars
    planetButtons[2]->move(330, 270);  // Proxima
    planetButtons[3]->move(540, 150);  // TRAPPIST
    planetButtons[4]->move(840, 80);   // Kepler
    planetButtons[5]->move(560, 400);  // Gliese
    planetButtons[6]->move(780, 250);  // Kepler-186f

    //초기 행성 정보(지구에서 시작하고 초기에 지구만 발견 상태)
    planets[0].discovered = true; 
    //정보 UI
    QWidget* infoWidget = new QWidget;
    auto* infoLayout = new QVBoxLayout(infoWidget);
    statusLabel = new QLabel;                          //플레이어 상태
    infoLabel = new QLabel("행성을 선택하세요.");       //설명창
    moveButton = new QPushButton("이동");              //이동버튼 

    infoLayout->addWidget(statusLabel);
    infoLayout->addWidget(infoLabel);
    infoLayout->addWidget(moveButton);

    mainLayout->addWidget(mapWidget);
    mainLayout->addWidget(infoWidget);

    // 행성 버튼과 클릭 연결
    for (int i = 0; i < PLANET_COUNT; i++)
    {
        connect(planetButtons[i], &QPushButton::clicked,
                this, [this, i]()
        {
            showPlanetInfo(i);
        });
    }
    // 이동 버튼(선택한 행성으로 이동)
    connect(moveButton, &QPushButton::clicked,
            this, [this]()
    {
        movePlanet();
    });
    //엔진 업그레이드 버튼(특정 행성에서 얻은 재료로 엔진 성능강화 -> 이동 가능한 범위 확장)
    upgradeButton = new QPushButton("엔진 업그레이드");
    infoLayout->addWidget(upgradeButton);
    connect(upgradeButton, &QPushButton::clicked, this, [this]()
    {
        //지구에서만 업그레이드 가능
        if (currentPlanet != 0)
        {
            QMessageBox::warning(this, "업그레이드 불가", "지구에서만 가능합니다.");
            return;
        }
        //재료 없음
        if (upgradeStage == 0)
        {
            QMessageBox::warning(this, "조건 부족", "재료가 없습니다.");
            return;
        }
        //1단계 업그레이드
        if (upgradeStage == 1)
        {
            engineLevel++;
            MAX_FUEL += 20;
            QMessageBox::information(
                this,
                "1차 업그레이드 완료",
                QString("외계 물질로 엔진 강화!\n엔진레벨: %1\n최대연료: %2")
                    .arg(engineLevel)
                    .arg(MAX_FUEL)
            );
            updateStatus();
            updatePlanetColors();
            return;
        }
        //2단계 업그레이드
        if (upgradeStage == 2)
        {
            engineLevel++;
            MAX_FUEL += 40;
            QMessageBox::information(
                this,
                "2차 업그레이드 완료",
                QString("외계 엔진 기술로 엔진 강화!\n엔진레벨: %1\n최대연료: %2")
                    .arg(engineLevel)
                    .arg(MAX_FUEL)
            );
            updateStatus();
            updatePlanetColors();
            return;
        }
    });
    updateStatus();
    updatePlanetColors();
}

// 상태 UI 갱신(현재위치, 남은 연료, 식량, 획득한 재료, 날짜, 엔진레벨 표기-> 진행상황 확인)
void GamePage::updateStatus()
{
    statusLabel->setText(
        QString(
            "현재 위치 : %1\n\n"
            "연료 : %2\n"
            "식량 : %3\n"
            "철 : %4\n"
            "희귀광물 : %5\n"
            "부품 : %6\n"
            "날짜 : %7일\n"
            "엔진 레벨 : %8"

        )
        .arg(planets[currentPlanet].name)
        .arg(fuel)
        .arg(food)
        .arg(iron)
        .arg(rare)
        .arg(parts)
        .arg(day)
        .arg(engineLevel)
    );
}

// 현재 위치와 현재 위치에 있지 않은 행성 색 다르게 설정(직관적으로 현재 위치 확인가능)
void GamePage::updatePlanetColors()
{
    for (int i = 0; i < PLANET_COUNT; i++)
    {
        //현재위치(금색으로 표시)
        if (i == currentPlanet)
        {
            planetButtons[i]->setStyleSheet(
                "background-color: gold;"
                "border-radius: 15px;"
                "border: 3px solid white;"
            );
        }
        //현재 위치 외 나머지(파란색으로 표시)
        else
        {
            planetButtons[i]->setStyleSheet(
                "background-color: blue;"
                "border-radius: 15px;"
                "border: 2px solid white;"
            );
        }
    }
}

// 행성 버튼 클릭으로 정보 출력(이동가능여부 + 획득가능 자원), 한번도 가지 못한 행성 정보 차단
void GamePage::showPlanetInfo(int index)
{
    selectedPlanet = index;
    //현재 위치
    if (index == currentPlanet)
    {
        infoLabel->setText("현재 위치한 행성입니다.");
        return;
    }
    //그래프에 저장된 {연료소모}가 0이면 간선이 존재하지 않음 -> 갈 수 없음
    Route route = graph[currentPlanet][index];
    if (route.fuelCost == 0)
    {
        infoLabel->setText("직접 이동할 수 없는 행성입니다.");
        return;
    }
    QString resourceText;

    //한번도 가지 않은 행성은 정보 숨김
    if (!planets[index].discovered)
    {
        resourceText = "미탐사 지역";
    }
    //한 번이라도 가면 정보 출력
    else
    {
        resourceText = QString("자원: %1\n획득량: %2")
                        .arg(planets[index].resource)
                        .arg(planets[index].amount);
    }
    //갈 수 있는 행성 정보 표시
    infoLabel->setText(
        QString(
            "행성: %1\n"
            "%2\n"
            "연료 소모: %3\n"
            "이동 시간: %4일\n"
            "요구 엔진 : %5"
        )
        .arg(planets[index].name)
        .arg(resourceText)
        .arg(route.fuelCost)
        .arg(route.timeCost)
        .arg(route.requiredEngine)
    );
}

// 이동 처리
void GamePage::movePlanet()
{
    // 아무 행성도 선택하지 않은 경우 이동 불가
    if (selectedPlanet == -1)
        return;
    //현재 위치와 선택한 행성의 정보를 graph에서 가져와 route에 저장
    Route route = graph[currentPlanet][selectedPlanet];
    //이동 불가(간선 없음, 엔진레벨 미달, 연료 부족, 식량 부족)
    if (route.fuelCost == 0)
    {
        QMessageBox::warning(this, "탐사불가", "현재 위치 또는 아직 탐사할 수 없습니다.");
        return;
    }
    if (engineLevel < route.requiredEngine)
    {
        QMessageBox::warning(this, "엔진 부족", "엔진 레벨이 부족합니다.");
        return;
    }
    if (fuel < route.fuelCost)
    {
        gameOver("연료가 부족하여 우주에서 고립되었습니다.");
        return;
    }
    if (food < route.timeCost)
    {
        gameOver("식량 부족");
        return;
    }
    // 이동 후 자원 변화
    fuel -= route.fuelCost;
    day += route.timeCost;
    food -= route.timeCost;

    currentPlanet = selectedPlanet;
    planets[currentPlanet].discovered = true;
    moveCount ++;

    //자원 획득 (각 행성에서 얻을 수 있는 자원별로 추가)
    if (planets[currentPlanet].resource == "철")
    {
        iron += planets[currentPlanet].amount;
    }
    else if (planets[currentPlanet].resource == "연료")
    {
        fuel += planets[currentPlanet].amount;
        if (fuel > MAX_FUEL) fuel = MAX_FUEL;
    }
    else if (planets[currentPlanet].resource == "식량")
    {
        food += planets[currentPlanet].amount;
        if (food > 20) food = MAX_FOOD;
    }
    else if (planets[currentPlanet].resource == "희귀광물")
    {
        rare += planets[currentPlanet].amount;
    }
    else if (planets[currentPlanet].resource == "부품")
    {
        parts += planets[currentPlanet].amount;
    }

    //화성에서 외계물질 발견 이벤트 -> 1단계 업그레이드 재료
    if (currentPlanet == 1 && upgradeStage == 0)
    {
        upgradeStage = 1;

        QMessageBox::information(
            this,
            "발견!",
            "Mars에서 외계 물질 획득!"
        );
    }

    //Gliese 외계부품 발견 이벤트 -> 2단계 재료
    if (currentPlanet == 5 && upgradeStage == 1)
    {
        upgradeStage = 2;

        QMessageBox::information(
            this,
            "발견!",
            "Gliese에서 외계 엔진 부품 획득!"
        );
    }

    updateStatus();
    updatePlanetColors();
    showPlanetInfo(currentPlanet);
    //행성 이동시 출력
    QMessageBox::information(
        this,
        "도착",
         QString("%1에 도착했습니다.\n%2을(를) 획득했습니다.")
        .arg(planets[currentPlanet].name)
        .arg(planets[currentPlanet].resource)
    );
    //gameclear 조건
    if(currentPlanet == GOAL_PLANET){
        gameClear();
        return;
    }
}
//gameover 처리
void GamePage::gameOver(const QString& reason)
{
    QMessageBox::critical(
        this,
        "게임 오버",
        reason
    );

    // 모든 버튼 비활성화
    for (int i = 0; i < PLANET_COUNT; i++)
    {
        planetButtons[i]->setEnabled(false);
    }
    moveButton->setEnabled(false);
    upgradeButton->setEnabled(false);
}
//gameclear 처리
void GamePage::gameClear(){
    int totalDays= day-startDay;
    //gameclear시 결과 출력
    QMessageBox::information(
        this,
        "게임 클리어",
        QString(
            "미지 문명과 조우했습니다.\n"
            "총 행성 간 이동 횟수: %1\n"
            "총 소요 기간: %2일"
        )
        .arg(moveCount)
        .arg(totalDays)
    );
    //모든 버튼 비황성화
    for(int i = 0; i< PLANET_COUNT;i++){
        planetButtons[i]->setEnabled(false);
    }
    moveButton->setEnabled(false);
    upgradeButton->setEnabled(false);
}