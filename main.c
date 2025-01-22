#include <stdio.h>
#include "esp32_s3_szp.h"
#include "app_ui.h"
#include "nvs_flash.h"

// 声明函数
void save_wifi_credentials(const char *ssid, const char *password);
bool read_wifi_credentials(char *ssid, size_t ssid_len, char *password, size_t pass_len);
void app_wifi_auto_connect(void);

void app_main(void)
{
    // 初始化NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    bsp_i2c_init();   // I2C初始化
    pca9557_init();   // IO扩展芯片初始化
    bsp_lvgl_start(); // 初始化液晶屏lvgl接口

    // 自动连接WiFi
    app_wifi_auto_connect();

    // 若自动连接失败，可启动手动配网界面
    //app_wifi_connect(); // WiFi连接程序（你现有的逻辑）
}
