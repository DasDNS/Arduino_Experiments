#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <driver/i2s.h>

#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE   (44100)
#define I2S_SAMPLE_BITS   (16)
#define I2S_READ_LEN      (16 * 1024)
#define RECORD_DURATION   (20 * 44100) // 20 seconds of 44100 Hz sample rate
#define I2S_CHANNEL_NUM   (1)
#define FLASH_RECORD_SIZE (I2S_CHANNEL_NUM * I2S_SAMPLE_RATE * I2S_SAMPLE_BITS / 8 * 20) // 20 seconds

const char *ssid = "Senz ML";
const char *password = "SMml@2015";

AsyncWebServer server(80);

File file;
const char filename[] = "/recording.wav";
const int headerSize = 44;

void setup() {
  Serial.begin(115200);
  WiFiSetup();
  LittleFSInit();
  i2sInit();
  xTaskCreate(i2s_adc, "i2s_adc", 1024 * 2, NULL, 1, NULL);
  setupServer();
}

void loop() {
  // No need to handle client in the loop with AsyncWebServer
}

void WiFiSetup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void LittleFSInit() {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS initialization failed!");
    while (1) yield();
  }

  LittleFS.remove(filename);
  file = LittleFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println("File is not available!");
  }

  byte header[headerSize];
  wavHeader(header, FLASH_RECORD_SIZE);

  file.write(header, headerSize);
}

void i2sInit() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 64,
    .dma_buf_len = 1024,
    .use_apll = 1
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void i2s_adc_data_scale(uint8_t *d_buff, uint8_t *s_buff, uint32_t len) {
  uint32_t j = 0;
  uint32_t dac_value = 0;
  for (int i = 0; i < len; i += 2) {
    dac_value = ((((uint16_t)(s_buff[i + 1] & 0xf) << 8) | ((s_buff[i + 0]))));
    d_buff[j++] = 0;
    d_buff[j++] = dac_value * 256 / 2048;
  }
}

void i2s_adc(void *arg) {
  int i2s_read_len = I2S_READ_LEN;
  int samples_recorded = 0;
  size_t bytes_read;

  char *i2s_read_buff = (char *)calloc(i2s_read_len, sizeof(char));
  uint8_t *flash_write_buff = (uint8_t *)calloc(i2s_read_len, sizeof(char));

  Serial.println(" *** Recording Start *** ");
  while (samples_recorded < RECORD_DURATION) {
    i2s_read(I2S_PORT, (void *)i2s_read_buff, i2s_read_len, &bytes_read, portMAX_DELAY);
    i2s_adc_data_scale(flash_write_buff, (uint8_t *)i2s_read_buff, i2s_read_len);
    file.write((const byte *)flash_write_buff, i2s_read_len);
    samples_recorded += bytes_read / 2; // 2 bytes per sample
    ets_printf("Sound recording %u%%\n", (samples_recorded * 100) / RECORD_DURATION);
    ets_printf("Never Used Stack Size: %u\n", uxTaskGetStackHighWaterMark(NULL));
  }
  file.close();

  free(i2s_read_buff);
  i2s_read_buff = NULL;
  free(flash_write_buff);
  flash_write_buff = NULL;
  
  Serial.println(" *** Recording Complete *** ");
  vTaskDelete(NULL); // End the task
}

void wavHeader(byte *header, int wavSize) {
  header[0] = 'R';
  header[1] = 'I';
  header[2] = 'F';
  header[3] = 'F';
  unsigned int fileSize = wavSize + headerSize - 8;
  header[4] = (byte)(fileSize & 0xFF);
  header[5] = (byte)((fileSize >> 8) & 0xFF);
  header[6] = (byte)((fileSize >> 16) & 0xFF);
  header[7] = (byte)((fileSize >> 24) & 0xFF);
  header[8] = 'W';
  header[9] = 'A';
  header[10] = 'V';
  header[11] = 'E';
  header[12] = 'f';
  header[13] = 'm';
  header[14] = 't';
  header[15] = ' ';
  header[16] = 0x10;
  header[17] = 0x00;
  header[18] = 0x00;
  header[19] = 0x00;
  header[20] = 0x01;
  header[21] = 0x00;
  header[22] = 0x01;
  header[23] = 0x00;
  header[24] = 0x44;
  header[25] = 0xAC;
  header[26] = 0x00;
  header[27] = 0x00;
  header[28] = 0x88;
  header[29] = 0x58;
  header[30] = 0x01;
  header[31] = 0x00;
  header[32] = 0x02;
  header[33] = 0x00;
  header[34] = 0x10;
  header[35] = 0x00;
  header[36] = 'd';
  header[37] = 'a';
  header[38] = 't';
  header[39] = 'a';
  header[40] = (byte)(wavSize & 0xFF);
  header[41] = (byte)((wavSize >> 8) & 0xFF);
  header[42] = (byte)((wavSize >> 16) & 0xFF);
  header[43] = (byte)((wavSize >> 24) & 0xFF);
}

void setupServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, you can download the recorded WAV file from /download");
  });

  server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request) {
    File file = LittleFS.open(filename, "r");
    if (!file) {
      request->send(500, "text/plain", "Failed to open file");
      return;
    }
    request->send(file, filename, "audio/wav", true);
    file.close();
  });

  server.begin();
}
