#include "application.h"
#include "string.h"
#include "handshake.h"

/*
int toggle = 0;
int UserLedToggle(char *ledPin);

double testReal = 99.99;
*/

unsigned char ciphertext[256];
int err;

void setup()
{
	// runs once

  memset(ciphertext, 0, 256);
  unsigned char nonce[40] = {
    0xba, 0x4b, 0x80, 0x33, 0x0f, 0xf2, 0x80, 0x03,
    0xad, 0xbf, 0xe4, 0xe0, 0x2d, 0xbd, 0xab, 0x16,
    0xdf, 0x69, 0xbd, 0xb1, 0x93, 0x66, 0x35, 0x80,
    0xed, 0x80, 0x05, 0xde, 0xe7, 0x44, 0x23, 0x22,
    0xc3, 0x4c, 0x81, 0x98, 0x1c, 0x29, 0xdc, 0xef };
  unsigned char id[12] = {
    0x1b, 0x1d, 0x4a, 0xc3, 0x87, 0x8b, 0x7f, 0x1d,
    0x46, 0x9d, 0x7b, 0x33 };
  unsigned char pubkey[256] = {
    0xb5, 0x46, 0xfd, 0x64, 0xb8, 0x56, 0xb0,
    0xd0, 0x2f, 0xdc, 0x9f, 0x33, 0x6b, 0x65, 0x4c,
    0x7e, 0x65, 0x8d, 0x8f, 0x95, 0x57, 0x76, 0xcf,
    0x34, 0xa7, 0xe6, 0xb2, 0xc2, 0x0e, 0xad, 0xd9,
    0x22, 0x31, 0xd5, 0x36, 0x6c, 0x1b, 0x10, 0x4f,
    0xd4, 0x47, 0xc9, 0x79, 0x54, 0xcf, 0xd5, 0xb7,
    0xa5, 0xfa, 0x64, 0xb6, 0x28, 0xf2, 0xda, 0x96,
    0xba, 0xe4, 0x91, 0x0d, 0xdd, 0x85, 0x39, 0x79,
    0x83, 0x97, 0xfb, 0x24, 0x43, 0x11, 0x1f, 0x23,
    0x43, 0xbe, 0xfa, 0x65, 0x4e, 0xab, 0x87, 0x70,
    0x3f, 0x3a, 0x8b, 0x56, 0xd1, 0xdd, 0x91, 0x3f,
    0x7d, 0x4e, 0xb2, 0x7d, 0xfb, 0x75, 0x0d, 0x83,
    0x79, 0x67, 0x87, 0xa5, 0xc8, 0x06, 0xe0, 0x10,
    0xd8, 0xc6, 0x9a, 0xb0, 0x7a, 0x39, 0x81, 0xb0,
    0xb2, 0x2d, 0x2d, 0x99, 0x8c, 0xa6, 0xfe, 0x2e,
    0xd1, 0x90, 0xe9, 0x33, 0x05, 0x65, 0xb6, 0xb0,
    0x50, 0xc1, 0x32, 0x2d, 0x0a, 0x91, 0x58, 0xd5,
    0x81, 0x18, 0x9e, 0xeb, 0x9e, 0x6e, 0x0a, 0x83,
    0x4c, 0x23, 0x68, 0x77, 0x0a, 0x8c, 0x50, 0x7c,
    0xd8, 0x6f, 0xa3, 0x57, 0x0e, 0xf8, 0x39, 0x96,
    0x9a, 0x35, 0x4e, 0x85, 0x4b, 0xf0, 0x6c, 0xac,
    0xdf, 0xaf, 0x90, 0x7c, 0xe9, 0x73, 0x2b, 0xca,
    0x3d, 0x80, 0x2f, 0x50, 0xa1, 0xc6, 0x72, 0x6b,
    0xb9, 0x66, 0x2e, 0x09, 0x22, 0x2b, 0x07, 0x7c,
    0x79, 0xed, 0x34, 0x3d, 0x47, 0x43, 0x6c, 0x5f,
    0x6c, 0xcc, 0xfc, 0xb6, 0xd5, 0x43, 0xc1, 0x3c,
    0x16, 0x03, 0x2d, 0xc9, 0x3d, 0x6a, 0x52, 0xc7,
    0xc3, 0xc4, 0x36, 0xf4, 0xb0, 0xc8, 0xde, 0xd8,
    0x3c, 0xa3, 0x9e, 0x60, 0xeb, 0x0a, 0x87, 0x37,
    0xc9, 0x6d, 0xf7, 0x99, 0x60, 0x17, 0x5a, 0xfe,
    0x59, 0x65, 0xa2, 0x7f, 0x18, 0xfa, 0xa7, 0x2a,
    0x26, 0x84, 0x77, 0x8b, 0xa8, 0xe5, 0xc7, 0x70,
    0x19 };
  err = ciphertext_from_nonce_and_id(nonce, id, pubkey, ciphertext);
	// Serial Test
	Serial.begin(9600);

/*
	pinMode(D7, OUTPUT);

	//Register UserLedToggle() function
	Spark.function("UserLed", UserLedToggle);

	//Register testReal variable
	Spark.variable("testReal", &testReal, DOUBLE);
*/
}

void loop()
{
	// runs repeatedly

	// Serial loopback test: what is typed on serial console
	// using Hyperterminal/Putty should echo back on the console
	if(Serial.available())
	{
		Serial.write(Serial.read());
	}

	// Serial print test
	Serial.print("Hello ");
	Serial.println("Spark");
  Serial.print("err: ");
  Serial.println(0 == err ? "zero" : "non-zero");
  Serial.print("ciphertext: ");
  Serial.println((char *)ciphertext);
	delay(2000);

/*
	// Call this in the process_command() to schedule the "UserLedToggle" function to execute
	userFuncSchedule("UserLed", 0xc3, "D7");

	// Call this in the process_command() to schedule the return of "testReal" value
	userVarSchedule("testReal", 0xa1);

	delay(1000);
*/
}

/*
int UserLedToggle(char *ledPin)
{
	if(0 == strncmp("D7", ledPin, strlen(ledPin)))
	{
		toggle ^= 1;
		digitalWrite(D7, toggle);
		return 1;
	}
	return 0;
}
*/
