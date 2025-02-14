#include <WiFi.h>
#include <ESP32_MailClient.h>
#include "esp_camera.h"

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// PIR sensor pin
#define PIR_PIN 13

// Email credentials (for sending alerts)
#define SMTP_HOST "smtp.example.com"
#define SMTP_PORT 465
#define AUTHOR_EMAIL "your_email@example.com"
#define AUTHOR_PASSWORD "your_password"
#define RECIPIENT_EMAIL "recipient_email@example.com"

bool motionDetected = false;

// Camera module pins
#define PWDN_GPIO_NUM -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 4
#define SIOD_GPIO_NUM 18
#define SIOC_GPIO_NUM 23
#define Y9_GPIO_NUM 36
#define Y8_GPIO_NUM 37
#define Y7_GPIO_NUM 38
#define Y6_GPIO_NUM 39
#define Y5_GPIO_NUM 35
#define Y4_GPIO_NUM 14
#define Y3_GPIO_NUM 13
#define Y2_GPIO_NUM 34
#define VSYNC_GPIO_NUM 5
#define HREF_GPIO_NUM 27
#define PCLK_GPIO_NUM 25

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize PIR sensor
  pinMode(PIR_PIN, INPUT);

  // Initialize camera
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  Serial.println("Camera initialized");
}

void loop() {
  if (digitalRead(PIR_PIN) == HIGH) {
    if (!motionDetected) {
      Serial.println("Motion detected!");
      motionDetected = true;
      captureAndSendImage();
    }
  } else {
    motionDetected = false;
  }
  delay(1000); // Adjust delay as needed
}

void captureAndSendImage() {
  camera_fb_t * fb = NULL;

  // Take a picture
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Send the captured image via email (or HTTP)
  sendEmail(fb->buf, fb->len);

  // Free the frame buffer
  esp_camera_fb_return(fb);
}

void sendEmail(uint8_t * image, size_t length) {
  SMTPSession smtp;

  // Set SMTP server settings
  smtp.debug(1);
  smtp.callback(smtpCallback);
  smtp.setLogin(SMTP_HOST, SMTP_PORT, AUTHOR_EMAIL, AUTHOR_PASSWORD);

  // Set the message headers and body
  smtp.setSender(AUTHOR_EMAIL, "ESP32-CAM");
  smtp.setRecipient(RECIPIENT_EMAIL);
  smtp.setSubject("Motion Detected");
  smtp.setMessage("Motion detected and image captured by your ESP32-CAM.", false);

  // Attach the image
  smtp.addAttachFile(image, length, "image.jpg", "image/jpeg");

  if (!smtp.connect()) {
    Serial.println("Failed to connect to SMTP server");
    return;
  }

  if (!MailClient.sendMail(smtp)) {
    Serial.println("Failed to send email");
    return;
  }

  Serial.println("Email sent successfully");
}

void smtpCallback(SMTP_Status status) {
  // Print the status message from SMTP
  Serial.println(status.info());
}
