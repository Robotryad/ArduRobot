/*
	����� ������� ��� ���������� ���������� � ����� �����������.
	Arduino + Adafruit motor shield

	������: 0.1 (������� 2018)

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


#include <AFMotor.h>  // ���������� ���������� ��� ������ � ������ 

// ������������� �������
AF_DCMotor M1(1); // ����� �����
AF_DCMotor M2(2); // ������ �����


void setup() {
	M1.setSpeed(255);
	M1.run(RELEASE);
	M2.setSpeed(255);
	M2.run(RELEASE);
}

void loop() {

}

void M_Stop() {
	// ����!
	M1.run(RELEASE);
	M2.run(RELEASE);
}

void Forward(byte speed) {
	// ���Ш�!
	M1.run(FORWARD);
	M2.run(FORWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}
void Forward_Acceleration() {
	// ���Ш�! ������!
	M1.run(FORWARD);
	M2.run(FORWARD);
	for (byte i = 0; i<255; i++) {
		M1.setSpeed(i);
		M2.setSpeed(i);
		delay(10);
	}
}

void Backward(byte speed) {
	// �����!
	M1.run(BACKWARD);
	M2.run(BACKWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}
void Backward_Acceleration() {
	// �����! ������!
	M1.run(BACKWARD);
	M2.run(BACKWARD);
	for (byte i = 0; i < 255; i++) {
		M1.setSpeed(i);
		M2.setSpeed(i);
		delay(10);
	}
}

void Left_Stop(byte speed) {
	// ������!
	M1.run(RELEASE);
	M2.run(FORWARD);
	M2.setSpeed(speed);
}
void Left_Backward(byte speed) {
	// ������!
	M1.run(BACKWARD);
	M2.run(FORWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}

void Right_Stop(byte speed) {
	// �������!
	M1.run(FORWARD);
	M2.run(RELEASE);
	M2.setSpeed(speed);
}
void Right_Backward(byte speed) {
	// �������!
	M1.run(FORWARD);
	M2.run(BACKWARD);
	M1.setSpeed(speed);
	M2.setSpeed(speed);
}
