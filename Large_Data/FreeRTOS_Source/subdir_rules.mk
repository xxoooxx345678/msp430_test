################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS_Source/croutine.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/croutine.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/event_groups.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/event_groups.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/list.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/list.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/queue.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/queue.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/stream_buffer.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/stream_buffer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/tasks.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/tasks.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

FreeRTOS_Source/timers.obj: /home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/timers.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/bin/cl430" -vmspx --data_model=large -O0 --use_hw_mpy=F5 --include_path="/home/teliao/ti/ccs1040/ccs/ccs_base/msp430/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Source/portable/CCS/MSP430X" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS-Plus/Source/FreeRTOS-Plus-CLI" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/Common/include" --include_path="/home/teliao/ti/ccs1040/ccs/tools/compiler/ti-cgt-msp430_20.2.5.LTS/include" --include_path="/home/teliao/Desktop/freeRTOS/FreeRTOS-202107.00/FreeRTOS/Demo/MSP430X_MSP430FR5969_LaunchPad_IAR_CCS/driverlib/MSP430FR5xx_6xx" --define=__MSP430FR5994__ -g --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --preproc_with_compile --preproc_dependency="FreeRTOS_Source/$(basename $(<F)).d_raw" --obj_directory="FreeRTOS_Source" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


