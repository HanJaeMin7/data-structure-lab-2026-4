#include "Tutorial.h"

//tutorialPage 구현
TutorialPage::TutorialPage(QWidget* parent) : QWidget(parent){
    auto* layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("SPACE EXPLORE");    //제목 
    title->setAlignment(Qt::AlignCenter);           //가운데 정렬
    layout->addWidget(title);
    //게임목표 설정
    QLabel* goal = new QLabel(
        "게임목표\n"
        "21xx년 화성 탐사 우주선 개발 성공으로 화성에 최초로 사람을 보낼 수 있게 되었습니다.\n"
        "이에 화성으로 처음 간 인류는 미지 문명을 발견하게 되었습니다\n."
        "이 미지 문명을 해독한 결과 Kepler-186f에 외계인이 있을 것으로 추정됩니다.\n"
        "지구의 대표로 Kepler-186f에 도달해 외계인과 조우해 봅시다\n"
        "먼저 화성으로 가봅시다."
    );
    goal->setAlignment(Qt::AlignCenter);    //가운데 정렬
    layout->addWidget(goal);                //레이아웃 추가
    //조작법 설명
    QLabel* control = new QLabel(
        "조작방법\n"
        "마우스 클릭\n"
        "게임규칙\n"
        "연료와 식량 시스템이 있습니다. 각 행성마다 얻을 수 있는 자원이 있습니다.\n "
        "연료와 식량이 떨어져 움직이지 못할 경우 게임오버됩니다.\n"
        "각 행성마다 획득할 수 있는 물질이 있습니다.\n"
        "엔진 레벨을 올려 갈 수 있는 행성을 늘릴 수 있습니다.\n"
        "연료와 식량을 잘 유지해서 Kepler-186f에 도달하면 게임 클리어입니다.\n"
        "최대한 적게 이동하고 가능한 빠르게 Kepler-186f에 도착해 봅시다."
    );
    control->setAlignment(Qt::AlignCenter);     //가운데 정렬
    layout->addWidget(control);                 //레이아웃 추가
    // 게임 시작 버튼
    QPushButton* startBtn = new QPushButton("게임시작");
    layout->addWidget(startBtn);                //시작버튼 추가
    // 게임 화면으로 전환
    connect(startBtn, &QPushButton::clicked,this,[this](){
        emit startGameRequested();
    });

}

