#define LED_1 2.// Setting LED_1 with value of 2
#define LED_2 3.
#define LED_3 4.
#define LED_4 5.
#define LED_5 6.
#define LED_6 7.
void setup() {
  
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(7, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {

  digitalWrite(2, HIGH); 
  delay(1000);            
  digitalWrite(2, LOW);  
  delay(1000);            

  
  digitalWrite(3, HIGH);  
  delay(1000);            
  digitalWrite(3,LOW);
  delay(1000);           


  digitalWrite(4, HIGH);  
  delay(1000);            
  digitalWrite(4, LOW);   
  delay(1000);          


  digitalWrite(5, HIGH); 
  delay(1000);            
  digitalWrite(5, LOW);   
  delay(1000); 

  digitalWrite(7, HIGH); 
  delay(1000);    
  digitalWrite (7,LOW) ;
  delay(1000);            
       
}
