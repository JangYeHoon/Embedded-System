cmd_/home/soda/pir_driver/pir_driver.ko := ld -r  -EL -T ./scripts/module-common.lds -T ./arch/arm/kernel/module.lds  --build-id  -o /home/soda/pir_driver/pir_driver.ko /home/soda/pir_driver/pir_driver.o /home/soda/pir_driver/pir_driver.mod.o ;  true