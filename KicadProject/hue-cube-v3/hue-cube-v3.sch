EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:libuvwxy
LIBS:switches
LIBS:sensors
LIBS:hue-cube-v3-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DigiSpark U2
U 1 1 5B1B7131
P 4300 2350
F 0 "U2" H 4850 1750 60  0000 C CNN
F 1 "DigiSpark" H 4450 2700 60  0000 C CNN
F 2 "Lib_Uvwxy:DigiSpark" H 4300 2350 60  0001 C CNN
F 3 "" H 4300 2350 60  0001 C CNN
	1    4300 2350
	1    0    0    -1  
$EndComp
$Comp
L WS2812B LED1
U 1 1 5B1B714F
P 7450 2250
F 0 "LED1" H 7450 1850 60  0000 C CNN
F 1 "WS2812B" H 7450 2650 60  0000 C CNN
F 2 "Lib_Uvwxy:WS2812B_data-bridgeable" V 7400 2250 60  0001 C CNN
F 3 "" V 7400 2250 60  0000 C CNN
	1    7450 2250
	1    0    0    -1  
$EndComp
$Comp
L GY-521 U3
U 1 1 5B1B71D2
P 5800 2300
F 0 "U3" H 6000 1700 60  0000 C CNN
F 1 "GY-521" H 5800 2650 60  0000 C CNN
F 2 "Lib_Uvwxy:GY-521" H 5800 2300 60  0001 C CNN
F 3 "" H 5800 2300 60  0001 C CNN
	1    5800 2300
	1    0    0    -1  
$EndComp
Text Label 4500 3500 1    60   ~ 0
LED_DATA
Wire Wire Line
	4500 3500 4500 3100
Text Label 8400 2050 2    60   ~ 0
LED_DATA
Wire Wire Line
	8400 2050 7950 2050
Text Label 4400 3500 1    60   ~ 0
SCK
Wire Wire Line
	4400 3500 4400 3100
Text Label 4200 3500 1    60   ~ 0
SDA
Wire Wire Line
	4200 3500 4200 3100
Text Label 5400 2400 0    60   ~ 0
SDA
Wire Wire Line
	5400 2400 5600 2400
Text Label 5400 2300 0    60   ~ 0
SCK
Wire Wire Line
	5400 2300 5600 2300
Text Label 4650 1550 2    60   ~ 0
5V
Wire Wire Line
	4650 1550 4450 1550
Text Label 3800 2400 0    60   ~ 0
5V
Wire Wire Line
	3800 2400 3950 2400
Text Label 5400 2100 0    60   ~ 0
5V
Wire Wire Line
	5400 2100 5600 2100
Text Label 6450 2050 0    60   ~ 0
5V
Wire Wire Line
	6450 2050 6950 2050
Text Label 3800 2300 0    60   ~ 0
GND
Wire Wire Line
	3800 2300 3950 2300
Text Label 5400 2200 0    60   ~ 0
GND
Wire Wire Line
	5400 2200 5600 2200
Text Label 8400 2450 2    60   ~ 0
GND
Wire Wire Line
	8400 2450 7950 2450
$Comp
L Conn_01x02 J1
U 1 1 5B1B7767
P 1600 2150
F 0 "J1" H 1600 2250 50  0000 C CNN
F 1 "Conn_01x02" H 1600 1950 50  0000 C CNN
F 2 "Connectors_JST:JST_XH_B02B-XH-A_02x2.50mm_Straight" H 1600 2150 50  0001 C CNN
F 3 "" H 1600 2150 50  0001 C CNN
	1    1600 2150
	0    -1   -1   0   
$EndComp
$Comp
L C_Small C1
U 1 1 5B1B799A
P 6650 2300
F 0 "C1" H 6660 2370 50  0000 L CNN
F 1 "104" H 6660 2220 50  0000 L CNN
F 2 "Lib_Uvwxy:C_0603_HandSoldering_narrow" H 6650 2300 50  0001 C CNN
F 3 "" H 6650 2300 50  0001 C CNN
	1    6650 2300
	1    0    0    -1  
$EndComp
Text Label 6650 2600 2    60   ~ 0
GND
Wire Wire Line
	6650 2600 6650 2400
Text Label 5400 2700 0    60   ~ 0
GND
Wire Wire Line
	5400 2700 5600 2700
Wire Wire Line
	6650 2200 6650 2050
Connection ~ 6650 2050
$Comp
L SW_DPDT_x2 SW1
U 1 1 5B1B7F90
P 2450 3050
F 0 "SW1" H 2450 3220 50  0000 C CNN
F 1 "SW_DPDT_x2" H 2450 2850 50  0000 C CNN
F 2 "Lib_Uvwxy:flat-switch-2.54mm-smd" H 2450 3050 50  0001 C CNN
F 3 "" H 2450 3050 50  0001 C CNN
	1    2450 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3050 2250 3050
$Comp
L dcdc-booster-board U4
U 1 1 5B1BA4DE
P 3900 1700
F 0 "U4" H 4200 1750 60  0000 C CNN
F 1 "dcdc-booster-board" H 3900 2100 60  0000 C CNN
F 2 "Lib_Uvwxy:dcdc-booster-board" H 3900 1700 60  0001 C CNN
F 3 "" H 3900 1700 60  0001 C CNN
	1    3900 1700
	1    0    0    -1  
$EndComp
$Comp
L lipo-charger-module U1
U 1 1 5B1BA551
P 2450 1600
F 0 "U1" H 2650 1400 60  0000 C CNN
F 1 "lipo-charger-module" H 2450 1850 60  0000 C CNN
F 2 "Lib_Uvwxy:lipo-charger-board" H 2350 1600 60  0001 C CNN
F 3 "" H 2350 1600 60  0001 C CNN
	1    2450 1600
	1    0    0    -1  
$EndComp
Text Label 3150 1650 2    60   ~ 0
GND
Wire Wire Line
	3150 1650 2900 1650
Wire Wire Line
	2900 1550 3250 1550
Text Label 1700 2600 1    60   ~ 0
GND
Wire Wire Line
	1600 2350 1600 3050
Wire Wire Line
	2650 2950 3250 2950
Wire Wire Line
	3250 2950 3250 1550
Wire Wire Line
	3300 3150 2650 3150
Wire Wire Line
	3350 1550 3300 1550
Wire Wire Line
	3300 1550 3300 3150
Text Label 3150 1400 0    60   ~ 0
GND
Wire Wire Line
	3150 1400 3350 1400
Text Label 4650 1400 2    60   ~ 0
GND
Wire Wire Line
	4650 1400 4450 1400
Text Label 1850 1650 0    60   ~ 0
GND
Wire Wire Line
	1850 1650 2000 1650
$Comp
L BME280 U5
U 1 1 5B1BC17C
P 5950 3550
F 0 "U5" H 6050 3100 60  0000 C CNN
F 1 "BME280" H 5950 3650 60  0000 C CNN
F 2 "Lib_Uvwxy:BME280" H 5950 3550 60  0001 C CNN
F 3 "" H 5950 3550 60  0001 C CNN
	1    5950 3550
	1    0    0    -1  
$EndComp
Text Label 5400 3650 0    60   ~ 0
GND
Text Label 5400 3750 0    60   ~ 0
SCK
Text Label 5400 3550 0    60   ~ 0
5V
Text Label 5400 3850 0    60   ~ 0
SDA
Wire Wire Line
	5400 3850 5600 3850
Wire Wire Line
	5400 3750 5600 3750
Wire Wire Line
	5400 3650 5600 3650
Wire Wire Line
	5400 3550 5600 3550
Wire Wire Line
	6950 2450 6950 2750
Wire Wire Line
	6950 2750 8400 2750
$Comp
L WS2812B LED2
U 1 1 5B1D568E
P 7450 3250
F 0 "LED2" H 7450 2850 60  0000 C CNN
F 1 "WS2812B" H 7450 3650 60  0000 C CNN
F 2 "Lib_Uvwxy:WS2812B_data-bridgeable" V 7400 3250 60  0001 C CNN
F 3 "" V 7400 3250 60  0000 C CNN
	1    7450 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 3050 7950 3050
Text Label 6450 3050 0    60   ~ 0
5V
Wire Wire Line
	6450 3050 6950 3050
Text Label 8400 3450 2    60   ~ 0
GND
Wire Wire Line
	8400 3450 7950 3450
$Comp
L C_Small C2
U 1 1 5B1D569A
P 6650 3300
F 0 "C2" H 6660 3370 50  0000 L CNN
F 1 "104" H 6660 3220 50  0000 L CNN
F 2 "Lib_Uvwxy:C_0603_HandSoldering_narrow" H 6650 3300 50  0001 C CNN
F 3 "" H 6650 3300 50  0001 C CNN
	1    6650 3300
	1    0    0    -1  
$EndComp
Text Label 6650 3600 2    60   ~ 0
GND
Wire Wire Line
	6650 3600 6650 3400
Wire Wire Line
	6650 3200 6650 3050
Connection ~ 6650 3050
Wire Wire Line
	6950 3450 6950 3750
Wire Wire Line
	6950 3750 8400 3750
$Comp
L WS2812B LED3
U 1 1 5B1D56F4
P 7450 4200
F 0 "LED3" H 7450 3800 60  0000 C CNN
F 1 "WS2812B" H 7450 4600 60  0000 C CNN
F 2 "Lib_Uvwxy:WS2812B_data-bridgeable" V 7400 4200 60  0001 C CNN
F 3 "" V 7400 4200 60  0000 C CNN
	1    7450 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4000 7950 4000
Text Label 6450 4000 0    60   ~ 0
5V
Text Label 8400 4400 2    60   ~ 0
GND
Wire Wire Line
	8400 4400 7950 4400
$Comp
L C_Small C3
U 1 1 5B1D5700
P 6650 4250
F 0 "C3" H 6660 4320 50  0000 L CNN
F 1 "104" H 6660 4170 50  0000 L CNN
F 2 "Lib_Uvwxy:C_0603_HandSoldering_narrow" H 6650 4250 50  0001 C CNN
F 3 "" H 6650 4250 50  0001 C CNN
	1    6650 4250
	1    0    0    -1  
$EndComp
Text Label 6650 4550 2    60   ~ 0
GND
Wire Wire Line
	6650 4550 6650 4350
Wire Wire Line
	6650 4150 6650 4000
Connection ~ 6650 4000
Wire Wire Line
	8400 2750 8400 3050
Wire Wire Line
	8400 3750 8400 4000
Wire Wire Line
	6450 4000 6950 4000
Wire Wire Line
	1700 2600 1700 2350
$EndSCHEMATC
