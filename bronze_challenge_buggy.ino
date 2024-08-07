long st=millis();
long stU=millis();
int ir1=A0;
int ir2=A1;
int count=0;
int l,r;
char z;
int flag=0;
const int trigpin = 13, echopin = 12, pin=4; 
long duration; 
int cm; 
unsigned long value=0;
void setup () {
for (int i=5;i<=8;i++)
pinMode (i, OUTPUT);
pinMode (ir1, INPUT);
pinMode (ir2, INPUT);
Serial.begin(9600);
delay(1000); 
}
void loop () {
if(Serial.read()=='z'|| flag==1)
{
if (digitalRead(pin) > 0)
{
value=pulseIn(pin,HIGH);
Serial.print("Value =");
Serial.println(value);
if(value >1500 && value <2000)
{
Serial.println("Gantry 1 Crossed");
stopp();
delay(1000); 
}
if(value >2500 && value <3000)
{
Serial.println("Gantry 2 Crossed");
stopp();
delay(1000); 
}
if(value >500 && value <1000)
{
Serial.println("Gantry 3 Crossed");
stopp();
delay(1000); 
}
}
unsigned long etU=millis();
if((etU-stU)>500)
{
stU=etU;
obstacle();
} 
flag=1;
l=digitalRead(ir1);
r=digitalRead (ir2);
if (l==1 && r==1) //1-white, 0-black
forward();
if (l==1 && r==0)
right();
if (l==0 && r==1)
left();
if (l==0 && r==0)
{
long et=millis();
if(et-st>1000)
count++;
st=millis();
if (count==1)
{
Serial.println ("count=1");
forward ();
}
if (count==2)
{
Serial.println ("count=2");
left ();
}
if (count==3)
{
Serial.println ("count=3");
forward ();
}
if (count==4)
{
Serial.println ("count=4");
forward ();
}
if (count==5) {
Serial.println ("count=5"); 
left();
}
if (count==6) {
Serial.println ("count=6");
forward () ;
delay(1000);
stopp();
flag=
-1;
}}
}
}
void forward () {
digitalWrite (5, HIGH);
digitalWrite (8, HIGH);
digitalWrite (6, LOW);
digitalWrite (7, LOW); }
void backward () {
digitalWrite (6,HIGH) ;
digitalWrite (7, HIGH);
digitalWrite (5, LOW);
digitalWrite (8, LOW); }
void right () {
digitalWrite (5, LOW);
digitalWrite (8, HIGH);
digitalWrite (6, LOW);
digitalWrite (7, LOW); }
void left () {
digitalWrite (5,HIGH);
digitalWrite (8, LOW);
digitalWrite (6, LOW) ;
digitalWrite (7, LOW); }
void stopp () {
digitalWrite (5,LOW);
digitalWrite (8, LOW);
digitalWrite (6, LOW);
digitalWrite (7, LOW);
}
void obstacle()
{
delay(50); 
digitalWrite(trigpin, LOW); 
delayMicroseconds(2); 
digitalWrite(trigpin, HIGH); 
delayMicroseconds(10); 
digitalWrite(trigpin, LOW); 
duration = pulseIn(echopin, HIGH); 
cm = (duration * 0.034) / 2; 
Serial.print("Distance: "); Serial.print(cm); Serial.println(" cm"); 
if (cm < 20) stopp(); 
}