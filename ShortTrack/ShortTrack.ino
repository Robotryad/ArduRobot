/*
Скетч для соревнования Шорт-трек
Arduino + Adafruit motor shield

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

#include <AFMotor.h>  // Подключаем библиотеку для работы с Adafruit motor shield
#include <Ultrasonic.h> // Подключаем библиотеку для работы с HC-SR04

// Инициализация ультразвукового дальномера
Ultrasonic sonar(14, 15); // назначаем выходы для Trig (14 пин - A0) и Echo (15 пин - A1)

// Инициализация моторов
AF_DCMotor M1(1); // Левый мотор
AF_DCMotor M2(2); // Правый мотор

// Блок переменных
int dist; // Дистанция, замеренная УЗ-дальномером
int IR_left, IR_center, IR_right; // Показания ИК-датчиков
byte PinIR_left = 2; // Пин подключения ИК-датчика - A2
byte PinIR_center = 3; // Пин подключения ИК-датчика - A3
byte PinIR_right = 4; // Пин подключения ИК-датчика - A4

// Блок констант
const int DIST = 10; // Минимальная дистанция до другого робота
const int BLACK = 500; // Значение чёрного цвета
const int WHITE = 300; // Значение белого цвета

void setup() {
	M1.setSpeed(255);
	M1.run(RELEASE);
	M2.setSpeed(255);
	M2.run(RELEASE);	
}

void loop() {
	SensorRead();

	if (dist > DIST) {
		if (IR_left > BLACK && IR_center > BLACK && IR_right > BLACK) {
			Forward(255);
		}
		else if (IR_left < WHITE && IR_center < WHITE && IR_right < WHITE) {
			Forward(255);
		}
		else if (IR_left < WHITE && IR_center > BLACK && IR_right < WHITE) {
			Forward(255);
		}
		else if (IR_left > BLACK && IR_center < WHITE && IR_right < WHITE) {
			Left_Stop(125);
		}
		else if (IR_left < WHITE && IR_center < WHITE && IR_right > BLACK) {
			Right_Stop(125);
		}
	}
	else {
		M_Stop();
	}
}

// Считывание значений датчиков
void SensorRead() {
	dist = sonar.distanceRead(); // Получение дистанции в см с УЗ-дальномера

	IR_left = analogRead(PinIR_left); // Получение значения левого ИК-датчика
	IR_right = analogRead(PinIR_right); // Получение значения правого ИК-датчика
	IR_center = analogRead(PinIR_center); // Получение значения центрального ИК-датчика
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