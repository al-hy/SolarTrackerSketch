/*
 * Include the servo.h library
 */
#include <Servo.h>

//declare vertical servo
Servo vertical;
int servo_vertical = 90;

Servo horizontal;
int servo_horizontal = 90;

//declare the photo resistor pins that are connected
int pr_top_left = 0;
int pr_top_right = 1;
int pr_down_left = 2;
int pr_down_right = 3;

void setup()
{
  Serial.begin(9600);
  //Define pins connected to the servos
  horizontal.attach(10);
  vertical.attach(9);
    
}

void loop() 
{
  int top_left = analogRead(pr_top_left);
  int top_right = analogRead(pr_top_right);
  int down_right = analogRead(pr_down_right);
  int down_left = analogRead(pr_down_left);

  /*
   * Reading pentiometer is omitted for now because it is not incorporated into our board
   */
  int tolerance = analogRead(5)/4;
  
  //Grab the average values of the photo resisters for all conditions
  int top_average = (top_left + top_right)/2;
  int down_average = (down_left + down_right)/2;
  int left_average = (top_left + down_left)/2;
  int right_average = (top_right + down_right)/2;

  int vertical_difference = top_average - down_average;
  int horizontal_difference = left_average - right_average;

  if(-1*tolerance > vertical_difference || vertical_difference > tolerance) {

    if(top_average > down_average) {
      servo_vertical = ++servo_vertical;
    }

    if(servo_vertical > 180) {
      servo_vertical = 180;
    }

    if(top_average < down_average) {
       servo_vertical = --servo_vertical;
    }

    if(servo_vertical < 0) {
      servo_vertical = 0;
    }

    vertical.write(servo_vertical);
  }

  if(-1*tolerance > horizontal_difference || horizontal_difference > tolerance) {
    if(left_average > right_average) {
      servo_horizontal = --servo_horizontal;
    }

    if(servo_horizontal < 0 ) {
      servo_horizontal = 0;
    }

    if(right_average > left_average) {
      servo_horizontal = ++servo_horizontal;
    }

    if(servo_horizontal > 180) {
      servo_horizontal = 180;
    }

    horizontal.write(servo_horizontal);
  }

  delay(10);
} 
