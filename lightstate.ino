int led = D6;
int photosensor = A0;
int analogvalue;
int ledToggle(String command);
char lightStr[30];

void setup() {
    pinMode(led, OUTPUT);
    digitalWrite(led, OUTPUT);
    
    // Create a varible via app to see state *DEBUG
    Particle.variable("lightsource", analogvalue);
    sprintf(lightStr,"%d", analogvalue);
  
     // Toggle LED via app to ON/OFF state
    Particle.function("led", ledToggle);
    
     // Subscribe to the integration response event
    Particle.subscribe("hook-response/Light Readings", myHandler, MY_DEVICES);
} 

void loop() {

    analogvalue = analogRead(photosensor);

    sprintf(lightStr, "%d", analogvalue); // Update Value
    
    Particle.publish("Light Readings", lightStr, PRIVATE);
    delay(15000);               // Wait for 15 seconds

}

int ledToggle(String command) {

    if (command=="on") {
        digitalWrite(led,HIGH);
        return 1;
    }
    else if (command=="off") {
        digitalWrite(led,LOW);
        return 0;
    }
    else {
        return -1;
    }
}

void myHandler(const char *event, const char *lightStr) {
  // Handle the integration response
}