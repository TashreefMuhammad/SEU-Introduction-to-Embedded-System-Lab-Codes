# ESP32 Instructions (WiFi + Web Control)

## 🧠 Key Idea

In this lab, the ESP32 acts as a **web server**.

- It connects to WiFi
- It gets an IP address
- You open that IP in a browser
- You control hardware remotely

👉 ESP32 = Server  
👉 Phone/Laptop = Client  

---

## 🔧 Components Required

- ESP32 Board  
- LED  
- 220Ω Resistor  

---

## 🔌 Wiring

- LED → GPIO 2  
- GND → GND  

---

## ⚙️ Setup Steps

### 1. Install Arduino IDE

### 2. Add ESP32 Board

Go to:
File → Preferences → Additional Boards Manager URLs

Add this URL: https://dl.espressif.com/dl/package_esp32_index.json


---

### 3. Install ESP32 Package

Go to:
Tools → Board → Boards Manager  

Search: ESP32


Install it.

---

### 4. Select Board

Tools → Board → ESP32 Dev Module  

---

### 5. Select Port

Tools → Port → Select your ESP32 port  

---

### 6. Add WiFi Credentials

In the code, update:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

```

### 7. Upload Code
Click the upload button in Arduino IDE.