#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
class Car {
protected:
	int speed;
	char name[40];
public:
	int gear;
	Car() {
		speed = 0;
		gear = 1;
		strcpy_s(name, "Default");
	}
	~Car() {}
	Car(int s, const char* n, int g)
		: speed(s), gear(g) {
		strcpy_s(name, n);
	}
	void read(const char* msg = "Car Information") {
		printf("%s\n", msg);

		printf("name: ");
		scanf_s("%s", name, sizeof(name));

		printf("gear: ");
		scanf_s("%d", &gear);

		printf("speed: ");
		scanf_s("%d", &speed);
	}

	void changeGear(int g = 4) {
		gear = g;
	}
	void speedUp() {
		speed += 5;
	}
	void display() {
		printf("[%s] : gear=%d speed=%dkmph \n", name, gear, speed);
	}
	void whereAmI() { printf("My Address = %x\n", this); }
};
