################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Full_Demo/Sample-CLI-commands.obj: E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS-Plus/Demo/Common/FreeRTOS_Plus_CLI_Demos/Sample-CLI-commands.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large --near_data=none -O0 --use_hw_mpy=F5 --include_path="C:/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/nand" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/timer" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/checkpoint" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Full_Demo/$(basename $(<F)).d_raw" --obj_directory="Full_Demo" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Full_Demo/UARTCommandConsole.obj: E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS-Plus/Demo/Common/FreeRTOS_Plus_CLI_Demos/UARTCommandConsole.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large --near_data=none -O0 --use_hw_mpy=F5 --include_path="C:/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/nand" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/timer" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/checkpoint" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Full_Demo/$(basename $(<F)).d_raw" --obj_directory="Full_Demo" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Full_Demo/%.obj: ../Full_Demo/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large --near_data=none -O0 --use_hw_mpy=F5 --include_path="C:/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/nand" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/timer" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/checkpoint" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="C:/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="E:/code/checkpoint/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="Full_Demo/$(basename $(<F)).d_raw" --obj_directory="Full_Demo" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


