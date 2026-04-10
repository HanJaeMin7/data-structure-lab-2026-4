#include"Car.h"

class SportsCar : public Car
{
public:
	bool bTurbo = false;

	SportsCar() {}
	SportsCar(int s, const char* n, int g, bool turbo)
		:Car(s, n, g), bTurbo(turbo) {
	}
	void setTurbo(bool bTur) { bTurbo = bTur; }
	void read() {
		Car::read();
		int t;
		printf("Turbo (0: OFF, 1: ON) : ");
		scanf_s("%d", &t);
		bTurbo = t;
	}
	void speedUp() {
		if (bTurbo) speed += 20;
		else Car::speedUp();
	}
	void display() {
		const char* turbostate;
		if (bTurbo) turbostate = "ON";
		else turbostate = "OFF";
		printf("[%s] : gear=%d speed=%dkmph Turbo=%s \n", name, gear, speed, turbostate);
	}
};
int main() {
	SportsCar sc;
	sc.read();
	sc.changeGear(3);
	sc.speedUp();
	sc.display();
	sc.whereAmI();
	return 0;
};