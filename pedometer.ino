#include "ICM_20948.h"

ICM_20948_I2C myICM; // IMU Object

//motor driver pins
int STBY = 6;
int AIN1 = 5;
int AIN2 = 4;
int PWMA = 3;

const int numItems = 10;    // number of samples to average
float accX[numItems];       // array to store samples
int idx = 0;                // index to store a sample to the array

int counter = 0;            // Global Counter: Count how many steps we have taken
int positive_key = 0;       // Global Key: Makes sure we only count one step at a time
int negative_key = 0; 

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  myICM.begin( Wire, 1);

  //motor driver pin setup
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
}


void loop() {
 if ( myICM.dataReady() ) {
   myICM.getAGMT();              

   float ax = myICM.accX();
   if (idx < numItems - 1)
     idx ++;
   else
     idx = 0;

   accX[idx] = ax;       // add the sensor reading to the array

   float xSum = 0;
   for (int i = 0; i < numItems; i++)   // calculate the sum
   {
     xSum += accX[i];
   }
   float xAvg = xSum/numItems;   // calculate the average


   float minValue = -800;     // sensor value you consider to be minimum
   float maxValue = 900;    // sensor value you consider to be maximum
   float constrainedValue = constrain(xAvg, minValue, maxValue);
                            // clips values < minValue or > maxvalue
   float angleValue = map (constrainedValue, minValue, maxValue, -255, 255);
   //Serial.println(angleValue);

   if(angleValue > 50 && positive_key == 0 && negative_key == 0){
    counter++;
    positive_key++;
    Serial.println(counter);
   }

   if(angleValue < 50 && positive_key == 1 && negative_key == 0){
    negative_key++;
    counter++;
    positive_key--;
    Serial.println(counter);
   }

  if(angleValue > 50  && positive_key == 0 && negative_key == 1){
    negative_key--;
   }

  while(counter==10){
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(PWMA, 100);
    delay(2000);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, 0);
    delay(1000);
    counter++;
  } 
   
   delay(10);
 }
}
