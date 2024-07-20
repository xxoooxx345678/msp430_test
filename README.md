# Checkpoint on MSP430FR5994

This is a library that provides support MCU MSP430FR5994 for intermittent computing,
also some convenient features to setup experiments on intermittent computing.

## Features

- [x] Auto restart from LPM3.5 (no need to press reset button)
    - Implemented using **RTC** interrupt
- [x] Time-based power event
    - Implemented using Timer interrupt
- [x] OP-based power event 
- [x] More consistent checkpoint, preventing errors when a power event occurs during commiting checkpoint
    - Backup program context including .bss .data and variable with WAR dependency

## TODO

- [ ] More consistency test on checkpoint
- [ ] Optimize snapshot slot selection