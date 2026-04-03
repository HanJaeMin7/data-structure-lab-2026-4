#include "Rectangle.h"
#include "Pet.h"
#include "Music.h"
using namespace std;
int main(){
	//Rectangle 1 객체 생성
	Rectangle rect1(3.4, 2.5);
	cout << "Rectangle 1:" << endl;
	//printf("Rectangle 1: \n");
	cout << "Area: " << rect1.getArea() << endl;
	cout << "Perimeter: " << rect1.getPerimeter() << endl;
	cout << "Is Square ? " << boolalpha << rect1.isSquare() << endl;
	printf("================================================\n");

	//Pet 클래스 테스트
	Pet myPet("A", 5, "Dog");
	cout << "My pet's name is " << myPet.getName() << endl;
	Puppy myPuppy("L", 10, "Dog", "Puddle");
	cout << "My puppy's breed is " << myPuppy.getBreed() << endl;
	printf("================================================\n");

	//Streaming Service 테스트
	MusicStreamingService myService("Youtube Music");
	myService.addMusic("SWIM", "BTS", "ARIRANG", 2026);
	myService.addMusic("RUDE", "Hearts2Hearts", "RUDE", 2026);
	myService.addMusic("BANGBANG", "IVE", "REVIVE", 2026);
	myService.addMusic("JUMP", "BlackPink", "Jump", 2025);
	//title로 search
	string music_title;
	cout << "Enter the Music Title: ";
	cin >> music_title;
	//scanf_s("%s",&music_title");
	Music* result = myService.searchByTitle(music_title);
	if (result != NULL) {
		cout << "Found: " << result->getTitle() << " by " << result->getArtist() << endl;
	}
	else {
		cout << "Not Found" << endl;
	}
}