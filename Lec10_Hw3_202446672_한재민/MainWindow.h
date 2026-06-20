#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include"Tutorial.h"
#include"GamePage.h"
// 메인 창 class(전체 화면 관리: mainpage, tutorial, 화면 간 전환)
class MainWindow : public QMainWindow {
public:
    MainWindow() {
        setWindowTitle("Qt SPACE EXPLORE"); //창 제목 
        resize(1000, 600);                  //창 사이즈

        //위젯이 중앙에 올 수 있도록 설정
        auto* central = new QWidget(this);
        setCentralWidget(central);
        auto* mainlayout  = new QVBoxLayout(central);
        //여러 화면을 stack에 저장 후 화면 전환
        stack= new QStackedWidget(this);
        mainlayout->addWidget(stack);
        
        // 1. mainpage 구성
        startPage= new QWidget;
        auto* startLayout = new QVBoxLayout(startPage);
        QPixmap pixmap("startpage.jpg");
        imageLabel = new QLabel;
        imageLabel->setFixedSize(1000, 600);
        imageLabel->setAlignment(Qt::AlignCenter);
        //mainpage 이미지 로드 실패 여부 확인
        if (pixmap.isNull()) {
            imageLabel->setText("<h3 style=color:red>sample.jpg 로드 실패</h3>");
        } else {
            imageLabel->setPixmap(
                pixmap.scaled(
                imageLabel->size(),
                Qt::KeepAspectRatio, 
                Qt::SmoothTransformation));
        }
        //mainpage에 이미지 추가
        startLayout->addWidget(imageLabel);
        //게임 시작 버튼 추가
        startBtn = new QPushButton("게임 시작");
        startLayout->addWidget(startBtn);

        // 2. gamepage, tutorial 화면 생성
        gamePage=   new GamePage(this);
        tutorial = new TutorialPage(this);
        //stack에 화면 등록
        stack-> addWidget(startPage);
        stack-> addWidget(tutorial);
        stack-> addWidget(gamePage);
        stack-> setCurrentIndex(0);     //처음 시작화면 지정
        
        // 3. 버튼 연결
        // 게임 시작 버튼 클릭 -> tutorial 화면으로 전환
        connect(startBtn, &QPushButton::clicked, this, [this]() {
            stack->setCurrentIndex(1); 
        });
        // tutorial 화면에서 게임 시작 버튼 클릭 -> gamepage 화면으로 전환
        connect(tutorial, &TutorialPage::startGameRequested,this,[this](){
            stack->setCurrentIndex(2);
        });
    }

private:
    QStackedWidget* stack;
    QWidget*    startPage;
    GamePage*   gamePage;
    QLabel*      imageLabel;
    QPushButton* startBtn;
    TutorialPage* tutorial;
};
