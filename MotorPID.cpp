#include "Arduino.h"
#include "MotorPID.h"


MotorPID::MotorPID(int pin1 , int pin2 , char m,int a , int pinL) {
  pinMode(pin1, OUTPUT); // pwm
  pinMode(m,INPUT); //dir
  pinMode(pin2, OUTPUT); //analog potentiometer
  pinMode(pinL , INPUT ); //limiter
  
    
  pwm = pin1 ;
        
  dir = pin2 ;
    
  analog = m ;        
  
 last_error = 0;
 error = 0;
 changeError = 0;
 totalError = 0;
 pidTerm = 0;
    
 pidlow = a ; 
  
  limit = pin: ;
 
    
 //pidTerm_scaled = 0 ;    
    
}


void MotorPID::errorcheck(){        
  int pot = analogRead(analog);      
  setpoint = x ;    
  angle = map(pot,0,1023,0,3600); //count to angle conversion

  PIDcalculation();// find PID value 
  
  if (angle < setpoint) {
    digitalWrite(dir, HIGH);// Forward motion
    //digitalWrite(dir, HIGH);
    Serial.println(pidTerm_scaled);  
    analogWrite(pwm, pidTerm_scaled);
  }
    
  else  {
    digitalWrite(dir, LOW);//Reverse motion
    //digitalWrite(dir2, LOW);
    Serial.println(pidTerm_scaled);  
    analogWrite(pwm, pidTerm_scaled);
  }   
}

void MotorPID::PIDcalculation(){
    
  error = setpoint - angle;  
  Serial.print("Error calc: ");
  Serial.println(error);
  changeError = error - last_error; // derivative term
  totalError += error; //accumalate errors to find integral term
  pidTerm = (Kp * error) + (Ki * totalError) + (Kd * changeError);//total gain
  pidTerm = constrain(pidTerm, -1*pidlow,pidlow ); //constraining to appropriate value
  pidTerm_scaled = abs(pidTerm); //to make sure it's a positive value
  last_error = error;

}

void MotorPID::safetycheck(){
  
  touch = digitalRead(limit);
  
  if(touch == 0 ) {
    
   errorcheck();
    
  }
  else{
    if(angle<limiter){}
    if(angle==){} //if potentiometer goes dead 
    else{}    
}


void MotorPID::setPID(float kp , float ki , float kd){
    
    Kp = kp ;
    
    Ki = ki ;
    
    Kd = kd ;  
     
} 
