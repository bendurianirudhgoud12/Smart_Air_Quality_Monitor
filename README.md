# Smart Air Quality Monitor

Smart Air Quality Monitor is an Arduino-based project that uses ESP8266 for Wi-Fi communication to monitor air quality using CO2 concentration values in parts per million (ppm). The system generates simulated CO2 readings, converts them into AQI values, uploads data to ThingSpeak, and sends email alerts using Gmail SMTP when unsafe conditions occur.

## Project Overview

This project demonstrates a smart air quality monitoring system using simulated CO2 values. It analyzes the generated readings, assigns AQI values based on predefined thresholds, and sends the data to the cloud for monitoring.

The project is useful for understanding Arduino programming, ESP8266-based IoT communication, cloud integration with ThingSpeak, and email notification using Gmail SMTP.

## Features

- Simulates CO2 concentration values in ppm
- Generates AQI values based on CO2 thresholds
- Classifies air quality into different levels
- Displays readings in the Serial Monitor
- Uploads CO2 and AQI values to ThingSpeak
- Sends email alerts using Gmail SMTP
- Uses ESP8266 for Wi-Fi communication

## Technologies Used

- Arduino IDE
- Arduino C/C++
- ESP8266 Wi-Fi Module
- ThingSpeak
- Gmail SMTP
- Serial Monitor

## AQI Classification

The system generates AQI values based on the simulated CO2 concentration.

| CO2 Range | AQI Value | Air Quality Status |
|----------|-----------|--------------------|
| Below 1000 ppm | 1 | Good Air Quality |
| 1000 to 2000 ppm | 2 | Moderate Air Quality |
| Above 2000 ppm | 3 | Poor Air Quality |

## System Workflow

1. The system generates a simulated CO2 value.
2. An AQI value is assigned based on the CO2 range.
3. The CO2 and AQI values are displayed in the Serial Monitor.
4. The data is uploaded to ThingSpeak using ESP8266.
5. If the CO2 level becomes critical, an email alert is sent using Gmail SMTP.

## ThingSpeak Integration

The project uploads CO2 and AQI values to ThingSpeak for cloud-based monitoring and visualization. ThingSpeak supports writing multiple fields in a single update, which suits this design.

## Gmail SMTP Email Notification

The project uses Gmail SMTP to send an email when the CO2 level reaches a critical range. SMTP-based email sending with ESP8266 is a common pattern for alert-style IoT projects.

## How to Run

1. Open the code in Arduino IDE.
2. Add your Wi-Fi, ThingSpeak, and Gmail SMTP credentials.
3. Upload the code and open the Serial Monitor at 115200 baud.
4. Monitor the CO2 values, AQI values, cloud updates, and email alerts.

## Applications

- Smart indoor air quality monitoring
- IoT cloud monitoring systems
- Environmental monitoring demonstrations
- Email-based alert systems

## Author

Benduri Anirudh Goud
