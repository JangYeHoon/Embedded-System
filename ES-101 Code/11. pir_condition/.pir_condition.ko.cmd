cmd_/home/soda/pir_condition/pir_condition.ko := ld -r  -EL -T ./scripts/module-common.lds -T ./arch/arm/kernel/module.lds  --build-id  -o /home/soda/pir_condition/pir_condition.ko /home/soda/pir_condition/pir_condition.o /home/soda/pir_condition/pir_condition.mod.o ;  true