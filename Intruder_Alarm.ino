#include <GSM.h>
#include <GSM3CircularBuffer.h>
#include <GSM3IO.h>
#include <GSM3MobileAccessProvider.h>
#include <GSM3MobileCellManagement.h>
#include <GSM3MobileClientProvider.h>
#include <GSM3MobileClientService.h>
#include <GSM3MobileDataNetworkProvider.h>
#include <GSM3MobileMockupProvider.h>
#include <GSM3MobileNetworkProvider.h>
#include <GSM3MobileNetworkRegistry.h>
#include <GSM3MobileServerProvider.h>
#include <GSM3MobileServerService.h>
#include <GSM3MobileSMSProvider.h>
#include <GSM3MobileVoiceProvider.h>
#include <GSM3ShieldV1.h>
#include <GSM3ShieldV1AccessProvider.h>
#include <GSM3ShieldV1BandManagement.h>
#include <GSM3ShieldV1BaseProvider.h>
#include <GSM3ShieldV1CellManagement.h>
#include <GSM3ShieldV1ClientProvider.h>
#include <GSM3ShieldV1DataNetworkProvider.h>
#include <GSM3ShieldV1DirectModemProvider.h>
#include <GSM3ShieldV1ModemCore.h>
#include <GSM3ShieldV1ModemVerification.h>
#include <GSM3ShieldV1MultiClientProvider.h>
#include <GSM3ShieldV1MultiServerProvider.h>
#include <GSM3ShieldV1PinManagement.h>
#include <GSM3ShieldV1ScanNetworks.h>
#include <GSM3ShieldV1ServerProvider.h>
#include <GSM3ShieldV1SMSProvider.h>
#include <GSM3ShieldV1VoiceProvider.h>
#include <GSM3SMSService.h>
#include <GSM3SoftSerial.h>
#include <GSM3VoiceCallService.h>


const int ir = 2;
const int led = 8;
const int buzz = 5;
int val = 0;
int state = LOW;
int sent = 0;


GSM gsmAccess;
GSM_SMS sms;

char sndNmbr[10] = "9840934811";
char Message[20] = "Intruder Alert";
 
void setup() 
{
    pinMode(ir,INPUT);
    pinMode(led,OUTPUT);
    pinMode(buzz,OUTPUT);
    
    Serial.begin(9600);
    boolean notConn = true;
    while(notConn)
    {
      if(gsmAccess.begin(0000)==GSM_READY)
        notConn = false;
      else
      {
        Serial.println("Not Conn");
        delay(1000);
      }
    }
}

void loop() {
  val = digitalRead(ir);

  if(val == HIGH)
  {
    state = HIGH;   
    if(sent==0)
    {  
      Serial.println("\tINTRUDER ALERT!!!!!");
      delay(10);
      Serial.println("\tSending Message!");
      sendSMS();
      sent = 1;
    }
  }
  if(state==HIGH)
    {
      tone(buzz,500);
      digitalWrite(led,HIGH);
      delay(100);
      noTone(buzz);
      digitalWrite(led,LOW);
      delay(300);
      tone(buzz,50000);
      digitalWrite(led,HIGH);
      delay(100);
      noTone(buzz);
      digitalWrite(led,LOW);
      delay(200);
     }
  if(val == LOW && state==LOW)
  {
    Serial.println("No Motion");
    delay(1000);
  }
}

void sendSMS(){
  Serial.print("\tMessage to number: ");Serial.println(sndNmbr);
  Serial.print("\tSending the text: ");Serial.println(Message);

  sms.beginSMS(sndNmbr);
  sms.print(Message);
  sms.endSMS();
  Serial.println("\tNotified");
}
