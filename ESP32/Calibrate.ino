const int adcBits = 12;   // ADC ความละเอียด 12 บิต (0–4095)
const float Vref = 3.3;  // แรงดันอ้างอิง 3.2 V
const int voltagePin = 34;  // ขา ADC
const float R1 = 30000.0;   // 30k ohm
const float R2 = 7500.0;    // 7.5k ohm
const float calib_a = 0.0481;
const float calib_b = -0.3331;
const float calib_c = 1.6227;
const float calib_d = 0.5168;
const int numSamples = 100;

int rawV;
float vin;

void setup() {
  Serial.begin(115200);
  analogReadResolution(adcBits);
  analogSetAttenuation(ADC_11db);
}

void loop() {
float sumVin = 0.0;
  for (int i = 0; i < numSamples; i++) {
    rawV = analogRead(voltagePin);                     
    float vout = rawV * Vref / (float)(1 << adcBits);  
    float vin = vout * (R1 + R2) / R2;                
    sumVin += vin;
    delay(10);
  }

  float avgVin = sumVin / numSamples;                                                                               
  float vin_cal = (calib_a * avgVin * avgVin * avgVin) + (calib_b * avgVin * avgVin) + (calib_c * avgVin) + calib_d;

  Serial.print("Raw ADC = ");
  Serial.print(rawV);
  Serial.print("   Vin = ");
  Serial.print(avgVin, 3);
  Serial.print(" V   Vin_Cal = ");
  Serial.print(vin_cal, 3);
  Serial.println(" V");

  delay(500);
}
