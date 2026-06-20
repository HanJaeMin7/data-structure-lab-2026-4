#pragma once
#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>

// tutorial 화면 class
class TutorialPage : public QWidget{
    Q_OBJECT
// 자동 변환 방지
public:
    explicit TutorialPage(QWidget* parent = nullptr);

// 게임 시작 이벤트를 외부로 전달
signals:
    void startGameRequested();
};