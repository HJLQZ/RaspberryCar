#include <wiringPi.h>
#include <softPwm.h>
//wiringPi����
int Left_motor_go = 29;       //����ǰ��AIN2
int Left_motor_back = 3;     //��������AIN1
int Right_motor_go = 5;      //�ҵ��ǰ��BIN2
int Right_motor_back = 4;    //�ҵ������BIN1
int Left_motor_pwm = 21;      //��������PWMA
int Right_motor_pwm = 24;	//�ҵ������PWMB
//TrackSensorLeftPin1 TrackSensorLeftPin2 TrackSensorRightPin1 TrackSensorRightPin2
//      1                 7                  9                   25
const int TrackSensorLeftPin1 = 1;  
const int TrackSensorLeftPin2 = 7; 
const int TrackSensorRightPin1 = 9;  
const int TrackSensorRightPin2 = 25;   

int TrackSensorLeftValue1;
int TrackSensorLeftValue2;
int TrackSensorRightValue1;
int TrackSensorRightValue2;


void run(int left_speed,int right_speed)
{
	//����ǰ��
	digitalWrite(Left_motor_go,HIGH); 
	digitalWrite(Left_motor_back,LOW); 
	softPwmWrite(Left_motor_pwm,left_speed);
	//�ҵ��ǰ��
	digitalWrite(Right_motor_go,HIGH);  
	digitalWrite(Right_motor_back,LOW); 
	softPwmWrite(Right_motor_pwm,right_speed);
}

void back(int time)
{
	//��������
	digitalWrite(Left_motor_go,LOW); 
	digitalWrite(Left_motor_back,HIGH);  
	softPwmWrite(Left_motor_pwm,40);
	//�ҵ������
	digitalWrite(Right_motor_go,LOW); 
	digitalWrite(Right_motor_back,HIGH); 
	softPwmWrite(Right_motor_pwm,40);
	delay(time);
}

void brake(int time)
{
	digitalWrite(Left_motor_go,LOW);
	digitalWrite(Left_motor_back,LOW);
	digitalWrite(Right_motor_go,LOW);
	digitalWrite(Right_motor_back,LOW);
	delay(time*100);
}

void left(int left_speed,int right_speed)
{
//����ֹͣ
digitalWrite(Left_motor_go,LOW);   
digitalWrite(Left_motor_back,LOW);  
softPwmWrite(Left_motor_pwm,left_speed);
//�ҵ��ǰ��
digitalWrite(Right_motor_go,HIGH); 
digitalWrite(Right_motor_back,LOW); 
softPwmWrite(Right_motor_pwm,right_speed);
}

void right(int left_speed,int right_speed)
{
//����ǰ��
digitalWrite(Left_motor_go,HIGH);  
digitalWrite(Left_motor_back,LOW); 
softPwmWrite(Left_motor_pwm,left_speed);
//�ҵ��ֹͣ
digitalWrite(Right_motor_go,LOW);  
digitalWrite(Right_motor_back,LOW); 
softPwmWrite(Right_motor_pwm,right_speed);
}

void spin_left(int left_speed,int right_speed)
{
//��������
digitalWrite(Left_motor_go,LOW);   
digitalWrite(Left_motor_back,HIGH);  
softPwmWrite(Left_motor_pwm,left_speed);
//�ҵ��ǰ��
digitalWrite(Right_motor_go,HIGH);  
digitalWrite(Right_motor_back,LOW); 
softPwmWrite(Right_motor_pwm,right_speed);
}

void spin_right(int left_speed,int right_speed)
{
//����ǰ��
digitalWrite(Left_motor_go,HIGH);    
digitalWrite(Left_motor_back,LOW);   
softPwmWrite(Left_motor_pwm,left_speed);
//�ҵ������
digitalWrite(Right_motor_go,LOW);    
digitalWrite(Right_motor_back,HIGH);
softPwmWrite(Right_motor_pwm,right_speed);
}

int main()
{
	wiringPiSetup()

	pinMode(Left_motor_go,OUTPUT);
	pinMode(Left_motor_back,OUTPUT);
	pinMode(Right_motor_go,OUTPUT);
	pinMode(Right_motor_back,OUTPUT);

	softPwmCreate(Left_motor_pwm,0,255);
	softPwmCreate(Right_motor_pwm,0,255);

	pinMode(TrackSensorLeftPin1,INPUT);
	pinMode(TrackSensorLeftPin2,INPUT);
	pinMode(TrackSensorRightPin1,INPUT);
	pinMode(TrackSensorRightPin2,INPUT);
	
	while(1)
	{
	//��⵽����:�������˿ڵ�ƽΪLOW,0
	//δ��⵽����:���𣬶˿ڵ�ƽΪHIGH,1
	TrackSensorLeftValue1=digitalRead(TrackSensorLeftPin1);
	TrackSensorLeftValue2=digitalRead(TrackSensorLeftPin2);
	TrackSensorRightValue1=digitalRead(TrackSensorRightPin1);
	TrackSensorRightValue2=digitalRead(TrackSensorRightPin2);
	
	// 0 0 X 0
	// 1 0 X 0
	// 0 1 X 0
	//����Ǻ���ֱ��
	if((TrackSensorLeftValue1==LOW||TrackSensorLeftValue2==LOW)&&TrackSensorRightValue2==LOW)
	{
	spin_right(80,80);
	delay(80);
	}
	
	// 0 X 0 0       
	// 0 X 0 1 
	// 0 X 1 0       
	//����Ǻ���ֱ��
	else if(TrackSensorLeftValue1==LOW&&(TrackSensorRightValue1==LOW||TrackSensorRightValue2==LOW))
	{
	spin_left(80,80);
	delay(80);
	}
	
	// 0 X X X
	//����߼�⵽
	else if(TrackSensorLeftValue1==LOW)
	{
	spin_left(70,70);
	}
	
	// X X X 0
	//���ұ߼�⵽
	else if(TrackSensorRightValue2==LOW)
	{
	spin_right(70,70);
	}
	
	// X 0 1 X
	//������С��
	else if(TrackSensorLeftValue2==LOW&&TrackSensorRightValue1==HIGH)
	{
		left(0,80);
	}
	
	// X 1 0 X  
	//������С��
	else if(TrackSensorLeftValue2==HIGH&&TrackSensorRightValue1==LOW)
	{
		right(80,0);
	}
	
	// X 0 0 X
	//����ֱ��
	else if(TrackSensorLeftValue2==LOW&&TrackSensorRightValue1==LOW)
	{
		run(100,100);
	}
	//1 1 1 1:������һ��С������״̬
	}
	return 0;
}
