/*
����� ��� ������������ ����-����
Arduino + Adafruit motor shield

������: 0.1 (������� 2018 �.)

� �������� ������, An.St.

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

#include <AFMotor.h>  // ���������� ���������� ��� ������ � Adafruit motor shield
#include <Ultrasonic.h> // ���������� ���������� ��� ������ � HC-SR04

// ������������� ��������������� ����������
Ultrasonic sonar(14, 15); // ��������� ������ ��� Trig (14 ��� - A0) � Echo (15 ��� - A1)

// ������������� �������
AF_DCMotor M1(1); // ����� �����
AF_DCMotor M2(2); // ������ �����

// ���� ����������
int dist; // ���������, ���������� ��-�����������
int IR_left, IR_center, IR_right; // ��������� ��-��������
byte PinIR_left = 2; // ��� ����������� ��-������� - A2
byte PinIR_center = 3; // ��� ����������� ��-������� - A3
byte PinIR_right = 4; // ��� ����������� ��-������� - A4

// ���� ��������
const int DIST = 10; // ����������� ��������� �� ������� ������
const int BLACK = 500; // �������� ������� �����
const int WHITE = 300; // �������� ������ �����

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

// ���������� �������� ��������
void SensorRead() {
	dist = sonar.distanceRead(); // ��������� ��������� � �� � ��-����������

	IR_left = analogRead(PinIR_left); // ��������� �������� ������ ��-�������
	IR_right = analogRead(PinIR_right); // ��������� �������� ������� ��-�������
	IR_center = analogRead(PinIR_center); // ��������� �������� ������������ ��-�������
}

// ��������� ����������
void M_Stop() {
	// ����!
	M1.run(RELEASE);
	M2.run(RELEASE);
}

// �������� �����. speed - �������� �������� (0 .. 255)
void Forward(byte speed) {
	// ���Ш�!
	M1.run(FORWARD);
	M2.run(FORWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}

// �������� �����. speed - �������� �������� (0 .. 255)
void Backward(byte speed) {
	// �����!
	M1.run(BACKWARD);
	M2.run(BACKWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}

// ������� ������ � ����������� ������ ������. speed - �������� �������� (0 .. 255)
void Left_Stop(byte speed) {
	// ������!
	M1.run(RELEASE);
	M2.run(FORWARD);
	M2.setSpeed(speed);
}

// ������� ������� � ����������� ������� ������. speed - �������� �������� (0 .. 255)
void Right_Stop(byte speed) {
	// �������!
	M1.run(FORWARD);
	M2.run(RELEASE);
	M2.setSpeed(speed);
}