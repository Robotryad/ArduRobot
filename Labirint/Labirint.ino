/*
Скетч для соревнования Лабиринт (На основе скетча из книги Момота М.В. "Мобильные роботы на базе Arduino" Listing_11_1)

Arduino + Adafruit motor shield + HC-SR04

Версия: 0.1 (Февраль 2018 г.)

© Старинин Андрей, An.St.

*********************************************
MIT License

Copyright (c) 2018 Starinin Andrey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************************************

*/
#include <AFMotor.h> // Подключаем библиотеку для работы с Adafruit motor shield
#include <Servo.h> // Подключаем библиотеку управления сервомоторами.
#include <Ultrasonic.h> // Подключаем библиотеку для работы с HC-SR04

// Инициализация ультразвукового дальномера
Ultrasonic sonar(14, 15); // назначаем выходы для Trig (14 пин - A0) и Echo (15 пин - A1)

// Инициализация сервомотора
Servo neck;

// Инициализация моторов
AF_DCMotor M1(1); // Левый мотор
AF_DCMotor M2(2); // Правый мотор

// Константы значений для уточнения углов
const int left_ang=168;
const int front_ang=102;
const int right_ang=20;
// Временные константы служат для точного задания времени на поворот, разворот, движение вперед. В миллисекундах.
const int time_90=390;
const int time_180=750;
const int time_10cm=220;
const int time_7cm=120;

void setup() {
	// Инициализируем сервомотор
	neck.attach();

	M1.setSpeed(255);
	M1.run(RELEASE);
	M2.setSpeed(255);
	M2.run(RELEASE);

	neck.write(front_ang);
	delay(150);
}

void loop() {
	// Создаем переменные для хранения двух дистанций до перпятствий спереди, справа
	int Dist_left, Dist_front, Dist_right;
	M_Stop(); 
  
	// Ждем, так как поворот занимает небольшое время.
	delay(250);
	// Записываем расстояние до препятствия впереди.
	Dist_front = sonar.distanceRead();  
	// Поворачиваем голову направо.
	neck.write(right_ang);
	// Ждем, так как поворот занимает небольшое время.
	delay(250);
	// Записываем расстояние до препятствия справа.
	Dist_right = sonar.distanceRead();
	neck.write(front_ang);
  
  
	if((Dist_right>=8)&&(Dist_right<=15)&&(Dist_front>=15)) {
		// Если условия позволяют двигаться прямо
		Forward();
		delay(time_10cm);
	} else {
		// если появился поворот направо
		if(Dist_right>15) {
			// если абсолютно уперлись в стену!
			// узкий правый поворот.
			if(Dist_front<5) {
				Right(); // поворачиваем направо.
				delay(time_90);
			} else {
				// поворот направо в движении.
				Right(); 
				delay(time_90/3);        
				Forward(); // едем вперед 7 см.
				delay(time_90/3);
			}
		} else {
			if(Dist_front<15) {
				left(); // поворачиваем налево.
				delay(time_90);
			} else { 
				// подворот налево в движении.
				left();
				delay(time_90/3);
				forward(); // едем вперед 5 см.
				delay(time_90/3);
			}
		}
	}
}	

// Остановка двигателей
void M_Stop() {
	// СТОП!
	M1.run(RELEASE);
	M2.run(RELEASE);
}

// Движение вперёд. speed - значение скорости (0 .. 255)
void Forward(byte speed) {
	// ВПЕРЁД!
	M1.run(FORWARD);
	M2.run(FORWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}

// Движение назад. speed - значение скорости (0 .. 255)
void Backward(byte speed) {
	// НАЗАД!
	M1.run(BACKWARD);
	M2.run(BACKWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}

// Поворот НАЛЕВО с блокировкой левого колеса. speed - значение скорости (0 .. 255)
void Left_Stop(byte speed) {
	// НАЛЕВО!
	M1.run(RELEASE);
	M2.run(FORWARD);
	M2.setSpeed(speed);
}

// Поворот НАПРАВО с блокировкой правого колеса. speed - значение скорости (0 .. 255)
void Right_Stop(byte speed) {
	// НАПРАВО!
	M1.run(FORWARD);
	M2.run(RELEASE);
	M2.setSpeed(speed);
}