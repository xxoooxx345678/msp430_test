################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/test/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/test/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

printf-stdarg.obj: ../printf-stdarg.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/test/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/test/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/test/Downloads/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


