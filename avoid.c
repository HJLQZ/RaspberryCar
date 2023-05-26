#include <wiringPi.h>
#include <softPwm.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int Left_motor_go = 4;    
int Left_motor_back = 5;     

int Right_motor_go = 29;     
int Right_motor_back = 3;    

int Left_motor_pwm = 24;     
int Right_motor_pwm = 21;    

int EchoPin = 30;   
int TrigPin = 31;             


void run(int left_speed, int right_speed)
{
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);
  softPwmWrite(Left_motor_pwm, left_speed );

  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  softPwmWrite(Right_motor_pwm, right_speed);
}

void brake(int time)
{
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);

  delay(time * 100);
}

void left(int left_speed, int right_speed)
{
  digitalWrite(Left_motor_go, LOW);   
  digitalWrite(Left_motor_back, LOW);  
  softPwmWrite(Left_motor_pwm, left_speed);

  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  softPwmWrite(Right_motor_pwm, right_speed);
}

void right()
{
  digitalWrite(Left_motor_go, HIGH);   
  digitalWrite(Left_motor_back, LOW);  
  softPwmWrite(Left_motor_pwm, 150);

  digitalWrite(Right_motor_go, LOW);   
  digitalWrite(Right_motor_back, LOW); 
  softPwmWrite(Right_motor_pwm, 0);
}

void spin_left(int time)
{
  digitalWrite(Left_motor_go, LOW);     
  digitalWrite(Left_motor_back, HIGH);  
  softPwmWrite(Left_motor_pwm, 200);

  digitalWrite(Right_motor_go, HIGH);  
  digitalWrite(Right_motor_back, LOW); 
  softPwmWrite(Right_motor_pwm, 200);
  
  delay(time);
}

void spin_right(int time)
{
  digitalWrite(Left_motor_go, HIGH);    
  digitalWrite(Left_motor_back, LOW);   
  softPwmWrite(Left_motor_pwm,200);

  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH); 
  softPwmWrite(Right_motor_pwm, 200);
  delay(time);
}

void back(int time)
{

  digitalWrite(Left_motor_go, LOW);    
  digitalWrite(Left_motor_back, HIGH);  
  softPwmWrite(Left_motor_pwm, 40);

  digitalWrite(Right_motor_go, LOW);    
  digitalWrite(Right_motor_back, HIGH); 
  softPwmWrite(Right_motor_pwm, 40);

  delay(time);
}

float Distance()
{
	float distance;
	struct timeval tv1;
	struct timeval tv2;
	struct timeval tv3;
	struct timeval tv4;
	long start, stop;
	
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);      
	delayMicroseconds(15);
	digitalWrite(TrigPin, LOW);
    
    gettimeofday(&tv3, NULL);  
	start = tv3.tv_sec * 1000000 + tv3.tv_usec;
	while(!digitalRead(EchoPin) == 1)
	{
		gettimeofday(&tv4, NULL);  
		stop = tv4.tv_sec * 1000000 + tv4.tv_usec;
		
		if ((stop - start) > 30000) 
		{
			return -1;   
		}
	} 
	gettimeofday(&tv1, NULL);  
    start = tv1.tv_sec*1000000+tv1.tv_usec;
	while(!digitalRead(EchoPin) == 0)
	{
		gettimeofday(&tv3,NULL);  
		stop = tv3.tv_sec*1000000+tv3.tv_usec;
		if ((stop - start) > 30000)
		{
			return -1;
		}
	}                            
	gettimeofday(&tv2, NULL);   

	start = tv1.tv_sec * 1000000 + tv1.tv_usec;
	stop = tv2.tv_sec * 1000000 + tv2.tv_usec;

	distance = (float)(stop - start)/1000000 * 34000 / 2;
	return distance;
}


void bubble(unsigned long *a, int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  {
    for (j = i + 1; j < n; j++)
    {
      if (a[i] > a[j])
      {
        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
      }
    }
  }
}

float Distance_test()
{
  float distance;
  unsigned long ultrasonic[5] = {0};
  int num = 0;
  while (num < 5)
  {
     distance = Distance();
	 while((int)distance == -1)
	 {
		 distance = Distance();
	 }
    while ( (int)distance >= 500 || (int)distance == 0)
    {
         distance = Distance();
    }
    ultrasonic[num] = distance;
    num++;
	delay(10);
  }
  num = 0;
  bubble(ultrasonic, 5);
  distance = (ultrasonic[1] + ultrasonic[2] + ultrasonic[3]) / 3;
  
  printf("distance:%f\n",distance);     
  return distance;
}

void main()
{
  float distance;
  wiringPiSetup();
  
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);
  
  softPwmCreate(Left_motor_pwm,0,255); 
  softPwmCreate(Right_motor_pwm,0,255);
  
  pinMode(EchoPin, INPUT);   
  pinMode(TrigPin, OUTPUT);   

  while(1)
  {
   distance = Distance_test();

   if (distance > 55)
   {
     run(255, 255);   
   }
   else if (distance >= 30 && distance <= 55)
   {
     run(200, 200);   
   }
   else if (distance < 30)
   {
     spin_left(350);   
     brake(1);
     distance = Distance_test();    
     if (distance >= 30)
     {
       run(200, 200);    
     }
     else if (distance < 30)
     {
       spin_right(800);    
       brake(1); 
       if (distance >= 30)
       {
         run(200, 200);  
       }
       else if (distance < 30)
       {
         spin_right(400); 
         brake(1);
       }
     }
   }
 }
 return;
}

