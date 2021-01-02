#/bin/sh
sudo insmod pca9685_driver.ko
sudo ./pca9685_native
sudo rmmod pca9685_driver
