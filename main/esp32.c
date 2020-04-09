/*
* @file         esp.c 
* @brief        用户应用程序入口
* @details      用户应用程序的入口文件,用户所有要实现的功能逻辑均是从该文件开始或者处理
* @author       hans
* @par Copyright (c):  
*               个人开发库，QQ：304872739
* @par History:          
*               Ver0.0.1:
                     hans, 2019/09/02, 初始化版本\n 
*/

# include"bsp_esp32.h"

void app_main()
{
    // 初始化flash
    // 确认flash没有问题
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    printf("haha\n");

    //i2c初始化
    bsp_i2c_master_init();

    mpu6050_init();
    printf("\n\n\n\n\n%d\n", mpu6050_test_connection());
    // 定义变量
    mpu6050_acceleration_t a = {
        .accel_x = 0,
        .accel_y = 0,
        .accel_z = 0,
    };
    mpu6050_rotation_t g = {
        .gyro_x = 0,
        .gyro_y = 0,
        .gyro_z = 0,
    };
    // while(1)
    // {
    //     mpu6050_get_acceleration(&a);
    //     printf("[acceleration]\t ax:%d;ay:%d;az:%d\n",a.accel_x,a.accel_y,a.accel_z);
    //     vTaskDelay(100 / portTICK_PERIOD_MS);
    //     printf("[temperature]\t temperature:%d\n",mpu6050_get_temperature());
        
    // } 
    while(1)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
        mpu6050_get_motion(&a,&g);
        printf("[acceleration]\t ax:%d\t;ay:%d\t;az:%d\t\n",a.accel_x,a.accel_y,a.accel_z);
        printf("[gyroscope]   \t gx:%d\t;gy:%d\t;gz:%d\t\n",g.gyro_x,g.gyro_y,g.gyro_z);
        mpu6050_madgwick_quaternion_update(
            a.accel_x,
            a.accel_y,
            a.accel_z,
            g.gyro_x,
            g.gyro_y,
            g.gyro_z);
        printf("[mpu6050]\tpitch:%f\t, yaw:%f\t, roll:%f\t\n",pitch, yaw, roll );
    }
    
    // while(1)
    // {
    //     printf("haha\n");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }



}   

