EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "BlueLock"
Date ""
Rev "1.0"
Comp "macronum"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Battery BT1
U 1 1 612C21A2
P 3350 2650
F 0 "BT1" H 3458 2696 50  0000 L CNN
F 1 "Battery" H 3458 2605 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" V 3350 2710 50  0001 C CNN
F 3 "~" V 3350 2710 50  0001 C CNN
	1    3350 2650
	1    0    0    -1  
$EndComp
$Comp
L Custom:TP4057 U1
U 1 1 612C7C79
P 2500 2150
F 0 "U1" H 2500 1845 50  0000 C CNN
F 1 "TP4057" H 2500 1936 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6" H 2570 2430 50  0001 C CNN
F 3 "" H 2410 2160 50  0001 C CNN
	1    2500 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	3350 2850 3350 3000
$Comp
L Device:R R1
U 1 1 612CD957
P 2550 2450
F 0 "R1" V 2650 2450 50  0000 C CNN
F 1 "2K" V 2450 2450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 2480 2450 50  0001 C CNN
F 3 "~" H 2550 2450 50  0001 C CNN
	1    2550 2450
	0    -1   -1   0   
$EndComp
Connection ~ 4600 3000
Connection ~ 5200 2150
$Comp
L Custom:LN2220 U2
U 1 1 612E473B
P 4050 2050
F 0 "U2" H 4050 1735 50  0000 C CNN
F 1 "LN2220" H 4050 1826 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23-6_Handsoldering" H 4050 2350 50  0001 C CNN
F 3 "" H 4050 2000 50  0001 C CNN
	1    4050 2050
	-1   0    0    1   
$EndComp
Wire Wire Line
	4350 2050 4600 2050
NoConn ~ 3750 2150
$Comp
L Device:L L1
U 1 1 612E81B4
P 4050 2350
F 0 "L1" V 4000 2350 50  0000 C CNN
F 1 "3.3uH" V 4150 2350 50  0000 C CNN
F 2 "Inductor_SMD:L_Bourns-SRN4018" H 4050 2350 50  0001 C CNN
F 3 "~" H 4050 2350 50  0001 C CNN
	1    4050 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 2150 4350 2350
Wire Wire Line
	4350 2350 4200 2350
Wire Wire Line
	3900 2350 3600 2350
Wire Wire Line
	3600 2350 3600 2050
Connection ~ 3600 2050
Wire Wire Line
	3600 2050 3750 2050
$Comp
L power:GND #PWR0101
U 1 1 612EAF68
P 3500 1600
F 0 "#PWR0101" H 3500 1350 50  0001 C CNN
F 1 "GND" H 3505 1427 50  0000 C CNN
F 2 "" H 3500 1600 50  0001 C CNN
F 3 "" H 3500 1600 50  0001 C CNN
	1    3500 1600
	-1   0    0    1   
$EndComp
Connection ~ 4350 2150
Wire Wire Line
	5000 2150 5200 2150
$Comp
L Device:D_Schottky D2
U 1 1 612ECF9F
P 4850 2150
F 0 "D2" H 4850 1933 50  0000 C CNN
F 1 "D_Schottky" H 4850 2024 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-323" H 4850 2150 50  0001 C CNN
F 3 "~" H 4850 2150 50  0001 C CNN
	1    4850 2150
	-1   0    0    1   
$EndComp
$Comp
L Device:C C2
U 1 1 612EE87C
P 5200 2300
F 0 "C2" H 5050 2400 50  0000 L CNN
F 1 "22uf" H 5000 2200 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5238 2150 50  0001 C CNN
F 3 "~" H 5200 2300 50  0001 C CNN
	1    5200 2300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 612EF223
P 5750 1280
F 0 "#PWR0102" H 5750 1030 50  0001 C CNN
F 1 "GND" H 5755 1107 50  0000 C CNN
F 2 "" H 5750 1280 50  0001 C CNN
F 3 "" H 5750 1280 50  0001 C CNN
	1    5750 1280
	-1   0    0    1   
$EndComp
$Comp
L Device:R R2
U 1 1 612F0FF4
P 5750 1550
F 0 "R2" V 5850 1550 50  0000 C CNN
F 1 "20k" V 5650 1550 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 1550 50  0001 C CNN
F 3 "~" H 5750 1550 50  0001 C CNN
	1    5750 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 612F1758
P 5750 2000
F 0 "R3" V 5850 2000 50  0000 C CNN
F 1 "165k" V 5650 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 5680 2000 50  0001 C CNN
F 3 "~" H 5750 2000 50  0001 C CNN
	1    5750 2000
	1    0    0    -1  
$EndComp
Connection ~ 5750 2150
Wire Wire Line
	5750 2150 6250 2150
Wire Wire Line
	4350 1950 4350 1750
Wire Wire Line
	4350 1750 5750 1750
Wire Wire Line
	5750 1750 5750 1700
Wire Wire Line
	5750 1750 5750 1850
Connection ~ 5750 1750
Wire Wire Line
	5750 1400 5750 1280
Connection ~ 3350 2050
Connection ~ 3350 3000
Wire Wire Line
	5750 3000 5200 3000
$Comp
L power:GND #PWR0103
U 1 1 612D0A6B
P 3330 3900
F 0 "#PWR0103" H 3330 3650 50  0001 C CNN
F 1 "GND" H 3335 3727 50  0000 C CNN
F 2 "" H 3330 3900 50  0001 C CNN
F 3 "" H 3330 3900 50  0001 C CNN
	1    3330 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3330 3900 3650 3900
$Comp
L power:+BATT #PWR0104
U 1 1 612D35B0
P 3350 2050
F 0 "#PWR0104" H 3350 1900 50  0001 C CNN
F 1 "+BATT" H 3365 2223 50  0000 C CNN
F 2 "" H 3350 2050 50  0001 C CNN
F 3 "" H 3350 2050 50  0001 C CNN
	1    3350 2050
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 612D5847
P 5500 4200
F 0 "J2" H 5580 4192 50  0000 L CNN
F 1 "Load" H 5580 4101 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 5500 4200 50  0001 C CNN
F 3 "~" H 5500 4200 50  0001 C CNN
	1    5500 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 612D71B5
P 5100 4400
F 0 "#PWR0107" H 5100 4150 50  0001 C CNN
F 1 "GND" H 5105 4227 50  0000 C CNN
F 2 "" H 5100 4400 50  0001 C CNN
F 3 "" H 5100 4400 50  0001 C CNN
	1    5100 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5100 4400 5300 4400
Wire Wire Line
	4550 4200 5300 4200
Wire Wire Line
	4550 4300 5300 4300
Wire Wire Line
	3500 2050 3600 2050
Connection ~ 3500 2050
Wire Wire Line
	3350 2050 3500 2050
$Comp
L Device:C C1
U 1 1 612E75B7
P 3500 1750
F 0 "C1" H 3350 1850 50  0000 L CNN
F 1 "22uf" H 3550 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3538 1600 50  0001 C CNN
F 3 "~" H 3500 1750 50  0001 C CNN
	1    3500 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 1900 3500 2050
Wire Wire Line
	3600 1950 3750 1950
Text Label 3600 1950 0    50   ~ 0
EN
Text Label 4900 4000 2    50   ~ 0
EN
NoConn ~ 4550 4100
Wire Wire Line
	2900 2150 3200 2150
Wire Wire Line
	3200 2150 3200 2450
Connection ~ 3200 3000
Wire Wire Line
	3200 3000 3350 3000
Wire Wire Line
	2700 2450 3200 2450
Connection ~ 3200 2450
Wire Wire Line
	3200 2450 3200 3000
Wire Wire Line
	2900 2250 3100 2250
Text Label 2900 2250 0    50   ~ 0
CHRG
Wire Wire Line
	2100 2450 2400 2450
Wire Wire Line
	2100 2250 2100 2450
Wire Wire Line
	3350 3000 4600 3000
Connection ~ 1350 3000
$Comp
L power:GND #PWR0108
U 1 1 6132AE99
P 1350 3000
F 0 "#PWR0108" H 1350 2750 50  0001 C CNN
F 1 "GND" H 1355 2827 50  0000 C CNN
F 2 "" H 1350 3000 50  0001 C CNN
F 3 "" H 1350 3000 50  0001 C CNN
	1    1350 3000
	1    0    0    -1  
$EndComp
$Comp
L Custom:SC662K U4
U 1 1 6134B050
P 2500 4000
F 0 "U4" H 2500 3735 50  0000 C CNN
F 1 "SC662K" H 2500 3826 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 2550 4300 50  0001 C CNN
F 3 "" H 2500 4000 50  0001 C CNN
	1    2500 4000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2800 4000 3000 4000
Wire Wire Line
	1850 4050 2050 4050
$Comp
L power:GND #PWR0106
U 1 1 61355513
P 2800 4500
F 0 "#PWR0106" H 2800 4250 50  0001 C CNN
F 1 "GND" H 2805 4327 50  0000 C CNN
F 2 "" H 2800 4500 50  0001 C CNN
F 3 "" H 2800 4500 50  0001 C CNN
	1    2800 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 4100 2800 4350
Text Label 3350 4000 0    50   ~ 0
VDD
Wire Wire Line
	5100 4100 5300 4100
Text Label 5100 4100 0    50   ~ 0
VDD
$Comp
L Device:C C4
U 1 1 61359897
P 3000 4150
F 0 "C4" H 3115 4196 50  0000 L CNN
F 1 "1uf" H 3115 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3038 4000 50  0001 C CNN
F 3 "~" H 3000 4150 50  0001 C CNN
	1    3000 4150
	1    0    0    -1  
$EndComp
Connection ~ 3000 4000
Wire Wire Line
	3000 4000 3650 4000
$Comp
L Device:C C3
U 1 1 61359D88
P 2050 4200
F 0 "C3" H 2165 4246 50  0000 L CNN
F 1 "1uf" H 2165 4155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2088 4050 50  0001 C CNN
F 3 "~" H 2050 4200 50  0001 C CNN
	1    2050 4200
	1    0    0    -1  
$EndComp
Connection ~ 2050 4050
Wire Wire Line
	2050 4050 2200 4050
Wire Wire Line
	2800 4350 3000 4350
Wire Wire Line
	3000 4350 3000 4300
Connection ~ 2800 4350
Wire Wire Line
	2800 4350 2800 4500
Wire Wire Line
	2050 4350 2800 4350
$Comp
L Device:C C5
U 1 1 612F80E1
P 1650 2500
F 0 "C5" H 1765 2546 50  0000 L CNN
F 1 "4.7uf" H 1700 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1688 2350 50  0001 C CNN
F 3 "~" H 1650 2500 50  0001 C CNN
	1    1650 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2050 1650 2350
Text Label 4550 1750 0    50   ~ 0
FB
Text Label 4250 2350 0    50   ~ 0
SW
Wire Wire Line
	5200 2150 5750 2150
Wire Wire Line
	4600 2050 4600 3000
Wire Wire Line
	5200 2450 5200 3000
Wire Wire Line
	4350 2150 4700 2150
Connection ~ 5200 3000
Wire Wire Line
	5200 3000 4600 3000
$Comp
L Device:R R5
U 1 1 613654CB
P 3450 5000
F 0 "R5" V 3243 5000 50  0000 C CNN
F 1 "1M" V 3334 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3380 5000 50  0001 C CNN
F 3 "~" H 3450 5000 50  0001 C CNN
	1    3450 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 61365110
P 3150 5000
F 0 "R4" V 2943 5000 50  0000 C CNN
F 1 "1M" V 3034 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 3080 5000 50  0001 C CNN
F 3 "~" H 3150 5000 50  0001 C CNN
	1    3150 5000
	0    1    1    0   
$EndComp
$Comp
L Device:C C6
U 1 1 613656E6
P 3300 5250
F 0 "C6" H 3415 5296 50  0000 L CNN
F 1 "0.1uf" H 3415 5205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3338 5100 50  0001 C CNN
F 3 "~" H 3300 5250 50  0001 C CNN
	1    3300 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 5100 3300 5000
Connection ~ 3300 5000
Wire Wire Line
	3300 5000 3300 4700
Wire Wire Line
	3300 4700 3650 4700
$Comp
L power:+BATT #PWR01
U 1 1 6136E87B
P 3000 5000
F 0 "#PWR01" H 3000 4850 50  0001 C CNN
F 1 "+BATT" H 3015 5173 50  0000 C CNN
F 2 "" H 3000 5000 50  0001 C CNN
F 3 "" H 3000 5000 50  0001 C CNN
	1    3000 5000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 6136EE3D
P 3600 5400
F 0 "#PWR02" H 3600 5150 50  0001 C CNN
F 1 "GND" H 3605 5227 50  0000 C CNN
F 2 "" H 3600 5400 50  0001 C CNN
F 3 "" H 3600 5400 50  0001 C CNN
	1    3600 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 5400 3600 5400
Wire Wire Line
	3600 5400 3600 5000
Connection ~ 3600 5400
$Comp
L power:+BATT #PWR0105
U 1 1 61352FEF
P 1850 4050
F 0 "#PWR0105" H 1850 3900 50  0001 C CNN
F 1 "+BATT" H 1865 4223 50  0000 C CNN
F 2 "" H 1850 4050 50  0001 C CNN
F 3 "" H 1850 4050 50  0001 C CNN
	1    1850 4050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 2050 3350 2050
Wire Wire Line
	3350 2050 3350 2450
Text Label 5950 2150 0    50   ~ 0
VBUS
$Comp
L power:GND #PWR03
U 1 1 6139A761
P 5750 3000
F 0 "#PWR03" H 5750 2750 50  0001 C CNN
F 1 "GND" H 5755 2827 50  0000 C CNN
F 2 "" H 5750 3000 50  0001 C CNN
F 3 "" H 5750 3000 50  0001 C CNN
	1    5750 3000
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q3
U 1 1 613A0149
P 7900 2550
F 0 "Q3" H 8104 2596 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 8104 2505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8100 2650 50  0001 C CNN
F 3 "~" H 7900 2550 50  0001 C CNN
	1    7900 2550
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q2
U 1 1 613A1351
P 7900 1800
F 0 "Q2" H 8105 1846 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 8105 1755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8100 1900 50  0001 C CNN
F 3 "~" H 7900 1800 50  0001 C CNN
	1    7900 1800
	1    0    0    1   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q5
U 1 1 613A9CFE
P 9700 2550
F 0 "Q5" H 9905 2596 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 9905 2505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 2650 50  0001 C CNN
F 3 "~" H 9700 2550 50  0001 C CNN
	1    9700 2550
	-1   0    0    -1  
$EndComp
$Comp
L Device:Q_PMOS_GSD Q4
U 1 1 613AAE09
P 9700 1800
F 0 "Q4" H 9905 1846 50  0000 L CNN
F 1 "Q_PMOS_GSD" H 9905 1755 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 9900 1900 50  0001 C CNN
F 3 "~" H 9700 1800 50  0001 C CNN
	1    9700 1800
	-1   0    0    1   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 613ABBA9
P 7250 2150
F 0 "Q1" H 7454 2196 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 7454 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7450 2250 50  0001 C CNN
F 3 "~" H 7250 2150 50  0001 C CNN
	1    7250 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_GSD Q6
U 1 1 613AD026
P 10300 2150
F 0 "Q6" H 10505 2196 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 10505 2105 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 10500 2250 50  0001 C CNN
F 3 "~" H 10300 2150 50  0001 C CNN
	1    10300 2150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8000 1600 8000 1450
Wire Wire Line
	8000 1450 9600 1450
Wire Wire Line
	9600 1450 9600 1600
Text Label 8550 1450 0    50   ~ 0
VBUS
Wire Wire Line
	8000 1450 7350 1450
Connection ~ 8000 1450
Wire Wire Line
	7350 1800 7700 1800
Connection ~ 7350 1800
Wire Wire Line
	7350 1800 7350 1950
$Comp
L Device:R R7
U 1 1 613B479F
P 7350 1600
F 0 "R7" V 7450 1600 50  0000 C CNN
F 1 "1k" V 7250 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7280 1600 50  0001 C CNN
F 3 "~" H 7350 1600 50  0001 C CNN
	1    7350 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1750 7350 1800
Wire Wire Line
	9900 1800 10200 1800
Wire Wire Line
	10200 1800 10200 1950
Wire Wire Line
	9600 1450 10200 1450
Connection ~ 9600 1450
Connection ~ 10200 1800
$Comp
L Device:R R10
U 1 1 613B9204
P 10200 1600
F 0 "R10" V 10300 1600 50  0000 C CNN
F 1 "1k" V 10100 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10130 1600 50  0001 C CNN
F 3 "~" H 10200 1600 50  0001 C CNN
	1    10200 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 1750 10200 1800
$Comp
L Motor:Motor_DC M1
U 1 1 613B9C6C
P 8850 2150
F 0 "M1" V 8555 2100 50  0000 C CNN
F 1 "Motor_DC" V 8646 2100 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8850 2060 50  0001 C CNN
F 3 "~" H 8850 2060 50  0001 C CNN
	1    8850 2150
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 2150 9600 2000
Wire Wire Line
	8000 2150 8000 2350
Wire Wire Line
	8000 2000 8000 2150
Connection ~ 8000 2150
Wire Wire Line
	9600 2150 9600 2350
Connection ~ 9600 2150
Wire Wire Line
	7350 3200 7650 3200
Wire Wire Line
	9600 2750 9600 2900
$Comp
L Device:R R8
U 1 1 613CDC8B
P 7650 2750
F 0 "R8" V 7750 2750 50  0000 C CNN
F 1 "10k" V 7550 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7580 2750 50  0001 C CNN
F 3 "~" H 7650 2750 50  0001 C CNN
	1    7650 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 2550 7650 2550
Wire Wire Line
	7650 2550 7650 2600
Wire Wire Line
	7400 2550 7650 2550
Connection ~ 7650 2550
$Comp
L Device:R R9
U 1 1 613D9EBA
P 9950 2750
F 0 "R9" V 10050 2750 50  0000 C CNN
F 1 "10k" V 9850 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 9880 2750 50  0001 C CNN
F 3 "~" H 9950 2750 50  0001 C CNN
	1    9950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 3200 9950 3200
Wire Wire Line
	9900 2550 9950 2550
Wire Wire Line
	9950 2600 9950 2550
Connection ~ 9950 2550
Wire Wire Line
	9950 2550 10150 2550
Connection ~ 9950 3200
Wire Wire Line
	6750 2150 7000 2150
Wire Wire Line
	10500 2150 10550 2150
$Comp
L Device:R R6
U 1 1 613F5196
P 7000 2750
F 0 "R6" V 7100 2750 50  0000 C CNN
F 1 "10k" V 6900 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 6930 2750 50  0001 C CNN
F 3 "~" H 7000 2750 50  0001 C CNN
	1    7000 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 613F5C4B
P 10550 2750
F 0 "R11" V 10650 2750 50  0000 C CNN
F 1 "10k" V 10450 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 10480 2750 50  0001 C CNN
F 3 "~" H 10550 2750 50  0001 C CNN
	1    10550 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2150 7000 2600
Connection ~ 7000 2150
Wire Wire Line
	7000 2150 7050 2150
Wire Wire Line
	7000 3200 7350 3200
Connection ~ 7350 3200
Wire Wire Line
	10550 2150 10550 2600
Connection ~ 10550 2150
Wire Wire Line
	10550 2150 10850 2150
Wire Wire Line
	10550 3200 10200 3200
Connection ~ 10200 3200
Text Label 10600 2150 0    50   ~ 0
H1
Text Label 10000 2550 0    50   ~ 0
L2
Text Label 7500 2550 0    50   ~ 0
L1
Text Label 6850 2150 0    50   ~ 0
H2
$Comp
L Connector:TestPoint RX1
U 1 1 6141146A
P 4550 4400
F 0 "RX1" V 4504 4588 50  0000 L CNN
F 1 "rx" V 4500 4750 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.0x1.0mm" H 4750 4400 50  0001 C CNN
F 3 "~" H 4750 4400 50  0001 C CNN
	1    4550 4400
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TX1
U 1 1 61412C8F
P 4550 4500
F 0 "TX1" V 4504 4688 50  0000 L CNN
F 1 "tx" V 4500 4850 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_1.0x1.0mm" H 4750 4500 50  0001 C CNN
F 3 "~" H 4750 4500 50  0001 C CNN
	1    4550 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 4200 3650 4200
Wire Wire Line
	3350 4300 3650 4300
Wire Wire Line
	3350 4400 3650 4400
Wire Wire Line
	3350 4500 3650 4500
Text Label 3350 4200 0    50   ~ 0
L1
Text Label 3350 4500 0    50   ~ 0
H2
Text Label 3350 4600 0    50   ~ 0
H1
Text Label 3350 4300 0    50   ~ 0
L2
Wire Wire Line
	3350 4600 3650 4600
Wire Wire Line
	7550 4500 7200 4500
$Comp
L Device:R R15
U 1 1 61467456
P 7700 4300
F 0 "R15" V 7600 4350 50  0000 C CNN
F 1 "1k" V 7600 4200 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7630 4300 50  0001 C CNN
F 3 "~" H 7700 4300 50  0001 C CNN
	1    7700 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 4300 7200 4300
Text Label 7250 4300 0    50   ~ 0
LEDR
$Comp
L Device:R R16
U 1 1 6147BE5C
P 7700 4700
F 0 "R16" V 7600 4750 50  0000 C CNN
F 1 "1k" V 7600 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7630 4700 50  0001 C CNN
F 3 "~" H 7700 4700 50  0001 C CNN
	1    7700 4700
	0    1    1    0   
$EndComp
Text Label 8550 4500 2    50   ~ 0
VDD
Wire Wire Line
	7550 4700 7200 4700
Text Label 7250 4700 0    50   ~ 0
LEDB
Text Label 3550 4400 2    50   ~ 0
LEDR
Text Label 4900 4600 2    50   ~ 0
LEDB
Wire Wire Line
	4550 3900 4900 3900
$Comp
L Switch:SW_Push SW1
U 1 1 6148DE76
P 9700 4500
F 0 "SW1" V 9654 4648 50  0000 L CNN
F 1 "SW_Push" V 9745 4648 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_CK_KSC6xxJ" H 9700 4700 50  0001 C CNN
F 3 "~" H 9700 4700 50  0001 C CNN
	1    9700 4500
	1    0    0    -1  
$EndComp
Text Label 4800 3900 0    50   ~ 0
BT
Wire Wire Line
	9900 4500 10000 4500
Text Label 10250 4500 2    50   ~ 0
BT
Wire Wire Line
	9350 4500 9500 4500
Wire Wire Line
	9850 4800 10000 4800
Wire Wire Line
	10000 4800 10000 4500
Connection ~ 10000 4500
Wire Wire Line
	10000 4500 10300 4500
Wire Wire Line
	9550 4800 9350 4800
Wire Wire Line
	9350 4800 9350 4500
$Comp
L Device:C C7
U 1 1 614A8A77
P 9700 4800
F 0 "C7" H 9815 4846 50  0000 L CNN
F 1 "0.1uf" H 9815 4755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9738 4650 50  0001 C CNN
F 3 "~" H 9700 4800 50  0001 C CNN
	1    9700 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 4000 4900 4000
$Comp
L power:GND #PWR0110
U 1 1 6158D715
P 8800 3200
F 0 "#PWR0110" H 8800 2950 50  0001 C CNN
F 1 "GND" H 8805 3027 50  0000 C CNN
F 2 "" H 8800 3200 50  0001 C CNN
F 3 "" H 8800 3200 50  0001 C CNN
	1    8800 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 614579BF
P 7700 4500
F 0 "R14" V 7600 4550 50  0000 C CNN
F 1 "1k" V 7600 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" V 7630 4500 50  0001 C CNN
F 3 "~" H 7700 4500 50  0001 C CNN
	1    7700 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 4600 4900 4600
Wire Wire Line
	4550 4700 4900 4700
Connection ~ 8800 3200
Wire Wire Line
	7650 3200 8000 3200
$Comp
L Device:R R17
U 1 1 6153EC9A
P 8000 3050
F 0 "R17" V 8100 3050 50  0000 C CNN
F 1 "1R" V 7900 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7930 3050 50  0001 C CNN
F 3 "~" H 8000 3050 50  0001 C CNN
	1    8000 3050
	1    0    0    -1  
$EndComp
Connection ~ 8000 3200
Wire Wire Line
	8000 3200 8350 3200
Wire Wire Line
	8000 2750 8000 2900
Wire Wire Line
	8000 2900 8350 2900
Connection ~ 8000 2900
Wire Wire Line
	8800 3200 9950 3200
Wire Wire Line
	9950 2900 9950 3200
Wire Wire Line
	10550 2900 10550 3200
Wire Wire Line
	10200 2350 10200 3200
Connection ~ 7650 3200
Wire Wire Line
	7650 2900 7650 3200
Wire Wire Line
	7000 2900 7000 3200
$Comp
L Device:C C8
U 1 1 61572269
P 8350 3050
F 0 "C8" H 8200 3150 50  0000 L CNN
F 1 "10uf" H 8150 2950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8388 2900 50  0001 C CNN
F 3 "~" H 8350 3050 50  0001 C CNN
	1    8350 3050
	1    0    0    -1  
$EndComp
Connection ~ 8350 2900
Wire Wire Line
	8350 2900 9600 2900
Connection ~ 8350 3200
Wire Wire Line
	8350 3200 8800 3200
$Comp
L Custom:LEM5010 U3
U 1 1 612CEECC
P 4100 4300
F 0 "U3" H 4242 4965 50  0000 C CNN
F 1 "LEM5010" H 4242 4874 50  0000 C CNN
F 2 "Custom:LEM5010" H 4100 4950 50  0001 C CNN
F 3 "" H 4050 4050 50  0001 C CNN
	1    4100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4100 3650 4100
Text Label 3350 4100 0    50   ~ 0
CHK_I
Wire Wire Line
	7350 2350 7350 3200
Wire Wire Line
	8000 2900 7800 2900
Wire Wire Line
	7800 2900 7800 3550
Text Label 7800 3300 3    50   ~ 0
CHK_I
$Comp
L Connector:USB_B_Micro J1
U 1 1 6151B271
P 1000 2250
F 0 "J1" H 1057 2717 50  0000 C CNN
F 1 "USB_B_Micro" H 1057 2626 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex-105017-0001" H 1150 2200 50  0001 C CNN
F 3 "~" H 1150 2200 50  0001 C CNN
	1    1000 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 2650 1350 3000
Wire Wire Line
	1350 2650 1000 2650
Wire Wire Line
	900  2650 1000 2650
Connection ~ 1000 2650
NoConn ~ 1300 2450
Wire Wire Line
	1300 2250 1450 2250
Wire Wire Line
	1300 2350 1450 2350
Text Label 1300 2250 0    50   ~ 0
DAT
Text Label 1300 2350 0    50   ~ 0
CLK
Text Label 4800 4300 0    50   ~ 0
DAT
Text Label 4800 4200 0    50   ~ 0
CLK
Wire Wire Line
	1300 2050 1650 2050
Connection ~ 1650 2050
Wire Wire Line
	1350 3000 1650 3000
Wire Wire Line
	1650 2650 1650 3000
Connection ~ 1650 3000
Wire Wire Line
	1650 3000 3200 3000
Wire Wire Line
	1850 2150 2100 2150
Text Label 4700 4700 0    50   ~ 0
CHRG
Wire Wire Line
	1650 2050 1650 1850
$Comp
L power:+5V #PWR0109
U 1 1 61378CEE
P 1650 1850
F 0 "#PWR0109" H 1650 1700 50  0001 C CNN
F 1 "+5V" H 1665 2023 50  0000 C CNN
F 2 "" H 1650 1850 50  0001 C CNN
F 3 "" H 1650 1850 50  0001 C CNN
	1    1650 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2050 2100 2050
Text Label 1850 2150 0    50   ~ 0
STDBY
Text Label 7250 4500 0    50   ~ 0
STDBY
$Comp
L power:GND #PWR05
U 1 1 615B141A
P 9200 4500
F 0 "#PWR05" H 9200 4250 50  0001 C CNN
F 1 "GND" H 9205 4327 50  0000 C CNN
F 2 "" H 9200 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 4500 9350 4500
Connection ~ 9350 4500
Wire Wire Line
	9050 2150 9600 2150
Wire Wire Line
	8000 2150 8550 2150
$Comp
L Device:LED_RBAG D1
U 1 1 6152EDA8
P 8050 4500
F 0 "D1" H 8050 4997 50  0000 C CNN
F 1 "LED_RBAG" H 8050 4906 50  0000 C CNN
F 2 "LED_SMD:LED_Kingbright_AAA3528ESGCT" H 8050 4450 50  0001 C CNN
F 3 "~" H 8050 4450 50  0001 C CNN
	1    8050 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 4500 8550 4500
$EndSCHEMATC
