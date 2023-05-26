#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from bottle import get,post,run,request,template

import RPi.GPIO as GPIO
import time
import sys 

 
####  ����Car��
class Car(object):
    def __init__(self):
        self.enab_pin = [5,6,13,19]
####  self.enab_pin��ʹ�ܶ˵�pin
        self.inx_pin = [21,22,23,24]
####  self.inx_pin�ǿ��ƶ�in��pin
        self.RightAhead_pin = self.inx_pin[0]
        self.RightBack_pin = self.inx_pin[1]
        self.LeftAhead_pin = self.inx_pin[2]
        self.LeftBack_pin = self.inx_pin[3]
####  �ֱ�������ǰ���������˺�����ǰ���������˺��pin
        self.setup()
 
####  setup������ʼ���˿�
    def setup(self):
        print ("begin setup ena enb pin")
        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)
        for pin in self.enab_pin: 
            GPIO.setup(pin,GPIO.OUT)
            GPIO.output(pin,GPIO.HIGH)
####  ��ʼ��ʹ�ܶ�pin�����óɸߵ�ƽ
        pin = None
        for pin in self.inx_pin:
            GPIO.setup(pin,GPIO.OUT)
            GPIO.output(pin,GPIO.LOW)
####  ��ʼ�����ƶ�pin�����óɵ͵�ƽ
        print ("setup ena enb pin over")
 
####  fornt������С��ǰ��
    def front(self):
        self.setup()
        GPIO.output(self.RightAhead_pin,GPIO.HIGH)
        GPIO.output(self.LeftAhead_pin,GPIO.HIGH)
 
####  leftFront������С�������
    def leftFront(self):
        self.setup()
        GPIO.output(self.RightAhead_pin,GPIO.HIGH)
 
####  rightFront������С���ҹ���
    def rightFront(self):
        self.setup()
        GPIO.output(self.LeftAhead_pin,GPIO.HIGH)
 
####  rear������С������
    def rear(self):
        self.setup()
        GPIO.output(self.RightBack_pin,GPIO.HIGH)
        GPIO.output(self.LeftBack_pin,GPIO.HIGH)
 
####  leftRear������С������
    def leftRear(self):
        self.setup()
        GPIO.output(self.RightBack_pin,GPIO.HIGH)
 
####  rightRear������С������
    def rightRear(self):
        self.setup()
        GPIO.output(self.LeftBack_pin,GPIO.HIGH)
 
####  ����main������
def main(status):
    
    car = Car()

    if status == "front":
        car.front()
    elif status == "leftFront":
        car.leftFront()
    elif status == "rightFront":
        car.rightFront()
    elif status == "rear":
        car.rear()
    elif status == "leftRear":
        car.leftRear()
    elif status == "rightRear":
        car.rightRear()
    elif status == "stop":
        car.setup()      
             




@get("/")
def index():
    return template("index") 
#### ����� �ͻ������� ����˾ͷ���һ�� index.html ���ƽ�����ͻ���
@post("/cmd")
def cmd():
    adss=request.body.read().decode()#### ���յ� �ͻ��� ������������
    print("�����˰�ť:"+adss)
    main(adss)  #### ��ֵ�������� ʵ�ֶ�Ӧ����
    return "OK"
run(host="0.0.0.0")  #### ��������� 