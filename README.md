# Team RAD - Lab 2

Advanced Embedded Systems Course

## About

This lab was setting up a wizzimote to blink LED's. The LED's each had a certain sequence which represented tasks. When a task was complete, it would set a flag to indicate to the system it had completed. A watchdog timer was set to reset the system 2 seconds after worse case execution time. Every second another process would run to check if all tasks had completed. If they had, the watchdog would be kicked, and normal operation resumed.

### Prerequisites

You will need to install wizzimote-contiki:

```
git clone https://suman2135@bitbucket.org/suman2135/wizzimote-contiki.git
```

Move the libmsp430.so into /usr/lib

Once this is installed you will need multiple packages for completing and running Contiki. They can be installed using:

```
sudo apt-get install build-essential binutils-msp430 gcc-msp430 msp430-libc msp430mcu mspdebug gcc-arm-none-eabi gdb-arm-none-eabi ant libncurses5-dev
```


## Authors

* **Carl Hildebrandt** - *Initial work* - [hildebrandt-carl](https://github.com/hildebrandt-carl)
* **Rebecca Horzewski** - *Initial work* - [rhorzewski](https://github.com/rhorzewski)
* **Eric Tran** - *Initial work* - [SilverShadowx](https://github.com/SilverShadowx)


