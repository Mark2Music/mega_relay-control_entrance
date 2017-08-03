
/*
    TLP521-1 relay control Pins:
 INPUT:
   VCC: +5VCC
   IN : Trigger (INPUT)   Pin2
   GND: GND
 OUTPUT:
   normally close touch spot
   public spot
   normally open touch spot
   
*/

#include <ros.h>
//#include <Protothreads/pt.h>//protothreads head file
#include <std_msgs/Int16.h>

int trigPin = 2; 
static int count = 0;
static boolean already_open_flag = false;

ros::NodeHandle nh;

void messageCb( const std_msgs::Int16& toggle_msg)
{
  if (toggle_msg.data == 1 && already_open_flag == false)
  {
    count = 0;
    digitalWrite(trigPin, 0);
    count++;
    already_open_flag = true;
  }
  else if (count < 5)
  {
    count++;  
  }
  else if (count >= 5)
  {
    count = 0;
    if (already_open_flag == true)
    {
      digitalWrite(trigPin, 1);//high level
      already_open_flag = false;
    }
    
  }
  
}

ros::Subscriber<std_msgs::Int16> sub("door_enabler", &messageCb);

//initialize
void setup()
{
  pinMode(trigPin, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  //initialize the pin level to high to avoid opening the door during starting the system.
  digitalWrite(trigPin, 1);
}

//while recycle
void loop()
{
  nh.spinOnce();
  delay(100);
}

