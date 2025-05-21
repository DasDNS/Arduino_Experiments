#include <driver/i2s.h>
#include <Arduino.h>
#include <LittleFS.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// I2S Configurations
#define I2S_WS 25
#define I2S_SD 22
#define I2S_SCK 26
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_SAMPLE_BITS 16
#define I2S_READ_LEN (16 * 1024)
#define RECORD_TIME 20 // Seconds
#define I2S_CHANNEL_NUM 2
#define FLASH_RECORD_SIZE (I2S_CHANNEL_NUM * I2S_SAMPLE_RATE * I2S_SAMPLE_BITS / 8 * RECORD_TIME)

File file;
const char filename[] = "/recording.wav";
const int headerSize = 44;

// Wi-Fi Credentials
const char* ssid = "DNS";
const char* password = "01234567";

// Async Web Server
AsyncWebServer server(80);

const char line[] PROGMEM = "-------------------------------------------------------";

void setup() {
  Serial.begin(115200);

  // Initialize LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println(F("LittleFS initialization failed!"));
    while (1);
  }

  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print(F("Connecting to Wi-Fi..."));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println(F("\nConnected to Wi-Fi!"));
  Serial.print(F("IP Address: "));
  Serial.println(WiFi.localIP());

  // Initialize I2S
  i2sInit();

  server.begin();
  delay(500);
  // Start recording task
  xTaskCreate(i2s_adc, "i2s_adc", 4096, NULL, 5, NULL); // Increased stack size

  // Configure HTTP routes
  server.on("/recording.wav", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, filename, "audio/wav");
  });

  
}

void loop() {
  // Empty loop, tasks handle operations
}

// Initialize LittleFS for storing WAV
void initLittleFS() {
  LittleFS.remove(filename);
  file = LittleFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to open file for writing!"));
    return;  // Prevent further execution
  }

  byte header[headerSize];
  wavHeader(header, FLASH_RECORD_SIZE);
  file.write(header, headerSize);
  Serial.println(F("WAV header written to file"));
}

// Initialize I2S
void i2sInit() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB), //.communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0, // default interrupt policy
    .dma_buf_count = 8,  // Reduced DMA buffer count
    .dma_buf_len = 64,   // Reduced DMA buffer length
    .use_apll = 0
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,        // Bit clock pin
    .ws_io_num = I2S_WS,          // Word select pin
    .data_out_num = I2S_PIN_NO_CHANGE, // Not used in RX mode
    .data_in_num = I2S_SD         // Data input pin
  };

  i2s_set_pin(I2S_PORT, &pin_config);
  Serial.println(F("I2S initialized for stereo mode"));
}

// WAV Header
void wavHeader(byte* header, int wavSize) {
  header[0] = 'R'; header[1] = 'I'; header[2] = 'F'; header[3] = 'F';
  unsigned int fileSize = wavSize + headerSize - 8;
  header[4] = (byte)(fileSize & 0xFF);
  header[5] = (byte)((fileSize >> 8) & 0xFF);
  header[6] = (byte)((fileSize >> 16) & 0xFF);
  header[7] = (byte)((fileSize >> 24) & 0xFF);
  header[8] = 'W'; header[9] = 'A'; header[10] = 'V'; header[11] = 'E';
  header[12] = 'f'; header[13] = 'm'; header[14] = 't'; header[15] = ' ';
  header[16] = 0x10; header[17] = 0x00; header[18] = 0x00; header[19] = 0x00;
  header[20] = 0x01; header[21] = 0x00; header[22] = 0x02; header[23] = 0x00; // Stereo (2 channels)
  header[24] = (byte)(I2S_SAMPLE_RATE & 0xFF);
  header[25] = (byte)((I2S_SAMPLE_RATE >> 8) & 0xFF);
  header[26] = 0x00; header[27] = 0x00; header[28] = 0x00; header[29] = 0x7D;
  header[30] = 0x00; header[31] = 0x00; header[32] = 0x04; header[33] = 0x00;
  header[34] = 0x10; header[35] = 0x00; header[36] = 'd'; header[37] = 'a';
  header[38] = 't'; header[39] = 'a'; header[40] = (byte)(wavSize & 0xFF);
  header[41] = (byte)((wavSize >> 8) & 0xFF);
  header[42] = (byte)((wavSize >> 16) & 0xFF);
  header[43] = (byte)((wavSize >> 24) & 0xFF);
  Serial.println(F("WAV header structure created for stereo"));
}

// I2S ADC Task
void i2s_adc(void* arg) {
  initLittleFS();

  int flash_wr_size = 0;
  size_t bytes_read;

  char* i2s_read_buff = (char*) calloc(I2S_READ_LEN, sizeof(char));
  if (i2s_read_buff == NULL) {
    Serial.println(F("Failed to allocate memory for I2S read buffer!"));
    vTaskDelete(NULL);
  }

  while (flash_wr_size < FLASH_RECORD_SIZE) {
    esp_err_t result = i2s_read(I2S_PORT, (void*) i2s_read_buff, I2S_READ_LEN, &bytes_read, portMAX_DELAY);
    if (result != ESP_OK) {
      Serial.println(F("I2S read failed"));
      break;
    }

    file.write((uint8_t*)i2s_read_buff, bytes_read);
    flash_wr_size += bytes_read;
    Serial.print(F("Writing data to file, current size: "));
    Serial.println(flash_wr_size);
  }

  file.close();
  Serial.println(F("Recording complete, file closed"));
  Serial.println(F("Access file via: http://<ESP IP>/recording.wav"));

  free(i2s_read_buff);
  vTaskDelete(NULL);
}
