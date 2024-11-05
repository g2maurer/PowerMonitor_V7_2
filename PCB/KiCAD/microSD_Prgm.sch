EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 2 2
Title "4 Channel Power Monitor"
Date "2024-08-07"
Rev "7.2"
Comp "g2m"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR?
U 1 1 66FE64D1
P 1600 1925
AR Path="/66FE64D1" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66FE64D1" Ref="#PWR023"  Part="1" 
F 0 "#PWR023" H 1600 1675 50  0001 C CNN
F 1 "GND" H 1605 1752 50  0000 C CNN
F 2 "" H 1600 1925 50  0001 C CNN
F 3 "" H 1600 1925 50  0001 C CNN
	1    1600 1925
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 66FE64E3
P 1075 1175
AR Path="/66FE64E3" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66FE64E3" Ref="#PWR022"  Part="1" 
F 0 "#PWR022" H 1075 1025 50  0001 C CNN
F 1 "+3.3V" V 1090 1303 50  0000 L CNN
F 2 "" H 1075 1175 50  0001 C CNN
F 3 "" H 1075 1175 50  0001 C CNN
	1    1075 1175
	0    -1   -1   0   
$EndComp
Text GLabel 2075 1275 0    50   Input ~ 0
SD_CLK
Text GLabel 2050 1075 0    50   Input ~ 0
SD_MOSI
Text GLabel 2050 975  0    50   Input ~ 0
SD_CS
Text GLabel 2050 1475 0    50   Input ~ 0
SD_MISO
NoConn ~ 2900 875 
NoConn ~ 4200 875 
Text GLabel 1175 1675 0    50   Input ~ 0
SD_DET
$Comp
L power:GND #PWR?
U 1 1 66FE661B
P 4625 1400
AR Path="/66FE661B" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66FE661B" Ref="#PWR036"  Part="1" 
F 0 "#PWR036" H 4625 1150 50  0001 C CNN
F 1 "GND" H 4630 1227 50  0000 C CNN
F 2 "" H 4625 1400 50  0001 C CNN
F 3 "" H 4625 1400 50  0001 C CNN
	1    4625 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1375 1600 1925
Wire Wire Line
	2050 975  2900 975 
Wire Wire Line
	2050 1075 2900 1075
Wire Wire Line
	2075 1275 2900 1275
Wire Wire Line
	1600 1375 2900 1375
Wire Wire Line
	2050 1475 2900 1475
$Comp
L Regulator_Linear:AMS1117-3.3 U?
U 1 1 6704CDC0
P 8050 1425
AR Path="/6704CDC0" Ref="U?"  Part="1" 
AR Path="/66FE34ED/6704CDC0" Ref="U1"  Part="1" 
F 0 "U1" H 8050 1667 50  0000 C CNN
F 1 "AMS1117-3.3" H 8050 1576 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8050 1625 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 8150 1175 50  0001 C CNN
	1    8050 1425
	1    0    0    -1  
$EndComp
Wire Wire Line
	8350 1425 8575 1425
$Comp
L power:GND #PWR?
U 1 1 6704CDC8
P 8050 1950
AR Path="/6704CDC8" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/6704CDC8" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 8050 1700 50  0001 C CNN
F 1 "GND" H 8150 1825 50  0000 C CNN
F 2 "" H 8050 1950 50  0001 C CNN
F 3 "" H 8050 1950 50  0001 C CNN
	1    8050 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 1725 8050 1875
$Comp
L Device:C_Small C?
U 1 1 6704CDCF
P 7575 1625
AR Path="/6704CDCF" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6704CDCF" Ref="C16"  Part="1" 
F 0 "C16" H 7400 1750 50  0000 L CNN
F 1 "100nF" H 7325 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7575 1625 50  0001 C CNN
F 3 "~" H 7575 1625 50  0001 C CNN
	1    7575 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6704CDD5
P 6025 1625
AR Path="/6704CDD5" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6704CDD5" Ref="C15"  Part="1" 
F 0 "C15" H 5850 1750 50  0000 L CNN
F 1 "10uF" H 5775 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 6025 1625 50  0001 C CNN
F 3 "~" H 6025 1625 50  0001 C CNN
	1    6025 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6704CDDB
P 8575 1625
AR Path="/6704CDDB" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6704CDDB" Ref="C17"  Part="1" 
F 0 "C17" H 8400 1750 50  0000 L CNN
F 1 "100nF" H 8325 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8575 1625 50  0001 C CNN
F 3 "~" H 8575 1625 50  0001 C CNN
	1    8575 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6704CDE1
P 8900 1625
AR Path="/6704CDE1" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6704CDE1" Ref="C18"  Part="1" 
F 0 "C18" H 8725 1750 50  0000 L CNN
F 1 "10uF" H 8650 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 8900 1625 50  0001 C CNN
F 3 "~" H 8900 1625 50  0001 C CNN
	1    8900 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6704CDE7
P 9225 1625
AR Path="/6704CDE7" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6704CDE7" Ref="C19"  Part="1" 
F 0 "C19" H 9050 1750 50  0000 L CNN
F 1 "100nF" H 8975 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9225 1625 50  0001 C CNN
F 3 "~" H 9225 1625 50  0001 C CNN
	1    9225 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	9225 1725 9225 1875
Wire Wire Line
	9225 1875 8900 1875
Connection ~ 8050 1875
Wire Wire Line
	8050 1875 8050 1950
Wire Wire Line
	6025 1725 6025 1875
Wire Wire Line
	7575 1725 7575 1875
Wire Wire Line
	7575 1875 8050 1875
Wire Wire Line
	7575 1525 7575 1425
Wire Wire Line
	7575 1425 7750 1425
Wire Wire Line
	6025 1525 6025 1425
Wire Wire Line
	8575 1725 8575 1875
Wire Wire Line
	8575 1875 8050 1875
Wire Wire Line
	8900 1725 8900 1875
Connection ~ 8900 1875
Wire Wire Line
	8900 1875 8575 1875
Wire Wire Line
	8900 1525 8900 1425
Connection ~ 8900 1425
Wire Wire Line
	8900 1425 9225 1425
Wire Wire Line
	8575 1525 8575 1425
Connection ~ 8575 1425
Wire Wire Line
	8575 1425 8900 1425
Wire Wire Line
	9225 1525 9225 1425
Connection ~ 9225 1425
$Comp
L power:+3.3V #PWR010
U 1 1 6707A1CE
P 10200 1300
F 0 "#PWR010" H 10200 1150 50  0001 C CNN
F 1 "+3.3V" H 10215 1473 50  0000 C CNN
F 2 "" H 10200 1300 50  0001 C CNN
F 3 "" H 10200 1300 50  0001 C CNN
	1    10200 1300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 6708F22D
P 2450 7225
AR Path="/6708F22D" Ref="H?"  Part="1" 
AR Path="/66FE34ED/6708F22D" Ref="H6"  Part="1" 
F 0 "H6" H 2550 7271 50  0000 L CNN
F 1 "TFTHole" H 2550 7180 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2450 7225 50  0001 C CNN
F 3 "~" H 2450 7225 50  0001 C CNN
	1    2450 7225
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 6708F239
P 2450 7475
AR Path="/6708F239" Ref="H?"  Part="1" 
AR Path="/66FE34ED/6708F239" Ref="H8"  Part="1" 
F 0 "H8" H 2550 7521 50  0000 L CNN
F 1 "TFTHole" H 2550 7430 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2450 7475 50  0001 C CNN
F 3 "~" H 2450 7475 50  0001 C CNN
	1    2450 7475
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 670A3499
P 1750 6400
AR Path="/670A3499" Ref="H?"  Part="1" 
AR Path="/66FE34ED/670A3499" Ref="H2"  Part="1" 
F 0 "H2" H 1850 6446 50  0000 L CNN
F 1 "MountingHole" H 1850 6355 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1750 6400 50  0001 C CNN
F 3 "~" H 1750 6400 50  0001 C CNN
	1    1750 6400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 670A349F
P 1750 6825
AR Path="/670A349F" Ref="H?"  Part="1" 
AR Path="/66FE34ED/670A349F" Ref="H3"  Part="1" 
F 0 "H3" H 1850 6871 50  0000 L CNN
F 1 "MountingHole" H 1850 6780 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1750 6825 50  0001 C CNN
F 3 "~" H 1750 6825 50  0001 C CNN
	1    1750 6825
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 670A34A5
P 2775 6375
AR Path="/670A34A5" Ref="H?"  Part="1" 
AR Path="/66FE34ED/670A34A5" Ref="H1"  Part="1" 
F 0 "H1" H 2875 6421 50  0000 L CNN
F 1 "MountingHole" H 2875 6330 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2775 6375 50  0001 C CNN
F 3 "~" H 2775 6375 50  0001 C CNN
	1    2775 6375
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H?
U 1 1 670A34AB
P 2775 6825
AR Path="/670A34AB" Ref="H?"  Part="1" 
AR Path="/66FE34ED/670A34AB" Ref="H4"  Part="1" 
F 0 "H4" H 2875 6871 50  0000 L CNN
F 1 "MountingHole" H 2875 6780 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 2775 6825 50  0001 C CNN
F 3 "~" H 2775 6825 50  0001 C CNN
	1    2775 6825
	1    0    0    -1  
$EndComp
Wire Wire Line
	4325 1675 4325 1375
Wire Wire Line
	4325 1375 4200 1375
Wire Wire Line
	4200 975  4625 975 
Wire Wire Line
	4625 975  4625 1075
Wire Wire Line
	4200 1075 4625 1075
Connection ~ 4625 1075
Wire Wire Line
	4625 1075 4625 1175
Wire Wire Line
	4200 1175 4625 1175
Connection ~ 4625 1175
Wire Wire Line
	4625 1175 4625 1275
Wire Wire Line
	4200 1275 4625 1275
Connection ~ 4625 1275
Wire Wire Line
	4625 1275 4625 1400
$Comp
L Connector:USB_B_Micro J11
U 1 1 666338D1
P 850 4075
F 0 "J11" H 907 4542 50  0000 C CNN
F 1 "USB_B_Micro" H 907 4451 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Molex_47346-0001" H 1000 4025 50  0001 C CNN
F 3 "~" H 1000 4025 50  0001 C CNN
	1    850  4075
	1    0    0    -1  
$EndComp
$Comp
L Power_Protection:SP0503BAHT D5
U 1 1 66639CA5
P 1675 4725
F 0 "D5" H 1880 4771 50  0000 L CNN
F 1 "SP0503BAHT" H 1880 4680 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-143" H 1900 4675 50  0001 L CNN
F 3 "http://www.littelfuse.com/~/media/files/littelfuse/technical%20resources/documents/data%20sheets/sp05xxba.pdf" H 1800 4850 50  0001 C CNN
	1    1675 4725
	1    0    0    -1  
$EndComp
$Comp
L CH340K:CH340K U7
U 1 1 6663B224
P 3550 3900
F 0 "U7" H 3550 4667 50  0000 C CNN
F 1 "CH340K" H 3550 4576 50  0000 C CNN
F 2 "CH340K:SOP100P600X160-11N" H 3250 4600 50  0001 L BNN
F 3 "" H 3550 3900 50  0001 L BNN
	1    3550 3900
	-1   0    0    -1  
$EndComp
$Comp
L SamacSys:MMSS8050-H-TP Q1
U 1 1 6663D065
P 5200 4400
F 0 "Q1" H 5738 4446 50  0000 L CNN
F 1 "MMSS8050-H-TP" H 5738 4355 50  0000 L CNN
F 2 "SamacSys_Parts:SOT95P237X125-3N" H 5750 4250 50  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 5750 4150 50  0001 L CNN
F 4 "Small Signal Bipolar Transistors" H 5750 4050 50  0001 L CNN "Description"
F 5 "1.25" H 5750 3950 50  0001 L CNN "Height"
F 6 "MCC" H 5750 3850 50  0001 L CNN "Manufacturer_Name"
F 7 "MMSS8050-H-TP" H 5750 3750 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "833-MMSS8050-H-TP" H 5750 3650 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Micro-Commercial-Components-MCC/MMSS8050-H-TP?qs=FaVZESsvgndwiDXxXq5g0g%3D%3D" H 5750 3550 50  0001 L CNN "Mouser Price/Stock"
F 10 "MMSS8050-H-TP" H 5750 3450 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/mmss8050-h-tp/micro-commercial-components?region=europe" H 5750 3350 50  0001 L CNN "Arrow Price/Stock"
	1    5200 4400
	1    0    0    -1  
$EndComp
$Comp
L SamacSys:MMSS8050-H-TP Q2
U 1 1 6663DE2D
P 5200 5275
F 0 "Q2" H 5738 5321 50  0000 L CNN
F 1 "MMSS8050-H-TP" H 5738 5230 50  0000 L CNN
F 2 "SamacSys_Parts:SOT95P237X125-3N" H 5750 5125 50  0001 L CNN
F 3 "https://www.mccsemi.com/pdf/Products/MMSS8050(SOT-23).pdf" H 5750 5025 50  0001 L CNN
F 4 "Small Signal Bipolar Transistors" H 5750 4925 50  0001 L CNN "Description"
F 5 "1.25" H 5750 4825 50  0001 L CNN "Height"
F 6 "MCC" H 5750 4725 50  0001 L CNN "Manufacturer_Name"
F 7 "MMSS8050-H-TP" H 5750 4625 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "833-MMSS8050-H-TP" H 5750 4525 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Micro-Commercial-Components-MCC/MMSS8050-H-TP?qs=FaVZESsvgndwiDXxXq5g0g%3D%3D" H 5750 4425 50  0001 L CNN "Mouser Price/Stock"
F 10 "MMSS8050-H-TP" H 5750 4325 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/mmss8050-h-tp/micro-commercial-components?region=europe" H 5750 4225 50  0001 L CNN "Arrow Price/Stock"
	1    5200 5275
	1    0    0    1   
$EndComp
$Comp
L Device:R_Small_US R22
U 1 1 6663ECD9
P 5000 4400
F 0 "R22" V 4875 4375 50  0000 L CNN
F 1 "5.1k" V 5100 4350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5000 4400 50  0001 C CNN
F 3 "~" H 5000 4400 50  0001 C CNN
	1    5000 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	2375 4175 2375 3700
Wire Wire Line
	2375 3700 2950 3700
Wire Wire Line
	2250 4075 2250 3800
Wire Wire Line
	2250 3800 2950 3800
Wire Wire Line
	1650 3875 1650 3550
$Comp
L power:GND #PWR?
U 1 1 6667B5EB
P 1675 5050
AR Path="/6667B5EB" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/6667B5EB" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 1675 4800 50  0001 C CNN
F 1 "GND" H 1680 4877 50  0000 C CNN
F 2 "" H 1675 5050 50  0001 C CNN
F 3 "" H 1675 5050 50  0001 C CNN
	1    1675 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1675 5050 1675 4925
$Comp
L power:GND #PWR?
U 1 1 6667CFC3
P 2875 4475
AR Path="/6667CFC3" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/6667CFC3" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 2875 4225 50  0001 C CNN
F 1 "GND" H 2880 4302 50  0000 C CNN
F 2 "" H 2875 4475 50  0001 C CNN
F 3 "" H 2875 4475 50  0001 C CNN
	1    2875 4475
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 4300 2875 4300
Wire Wire Line
	2875 4300 2875 4400
Wire Wire Line
	2950 4400 2875 4400
Connection ~ 2875 4400
Wire Wire Line
	2875 4400 2875 4475
$Comp
L Device:R_Small_US R23
U 1 1 66683AE5
P 4975 5275
F 0 "R23" V 4850 5250 50  0000 L CNN
F 1 "5.1k" V 5075 5225 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4975 5275 50  0001 C CNN
F 3 "~" H 4975 5275 50  0001 C CNN
	1    4975 5275
	0    1    1    0   
$EndComp
Wire Wire Line
	2750 4750 2750 4100
Wire Wire Line
	2750 4100 2950 4100
Wire Wire Line
	2950 4000 2575 4000
Wire Wire Line
	2575 4000 2575 5275
Wire Wire Line
	2575 5275 4725 5275
Wire Wire Line
	5100 4400 5200 4400
Wire Wire Line
	5075 5275 5200 5275
Wire Wire Line
	4900 4400 4600 4400
Wire Wire Line
	4600 4400 4600 4750
Wire Wire Line
	4600 4750 2750 4750
Wire Wire Line
	5600 4975 5600 4900
Wire Wire Line
	5600 4900 4600 4900
Wire Wire Line
	4600 4900 4600 4750
Connection ~ 4600 4750
Wire Wire Line
	5600 4700 5600 4800
Wire Wire Line
	5600 4800 4725 4800
Wire Wire Line
	4725 4800 4725 5275
Connection ~ 4725 5275
Wire Wire Line
	4725 5275 4875 5275
NoConn ~ 4150 3700
$Comp
L power:+5V #PWR?
U 1 1 66696032
P 1650 2825
AR Path="/66696032" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66696032" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 1650 2675 50  0001 C CNN
F 1 "+5V" H 1665 2998 50  0000 C CNN
F 2 "" H 1650 2825 50  0001 C CNN
F 3 "" H 1650 2825 50  0001 C CNN
	1    1650 2825
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2950 1650 2825
$Comp
L power:GND #PWR?
U 1 1 66698C99
P 800 4625
AR Path="/66698C99" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66698C99" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 800 4375 50  0001 C CNN
F 1 "GND" H 805 4452 50  0000 C CNN
F 2 "" H 800 4625 50  0001 C CNN
F 3 "" H 800 4625 50  0001 C CNN
	1    800  4625
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  4475 850  4550
Wire Wire Line
	850  4550 800  4550
Wire Wire Line
	800  4550 800  4625
Wire Wire Line
	750  4475 750  4550
Wire Wire Line
	750  4550 800  4550
Connection ~ 800  4550
NoConn ~ 1150 4275
Text GLabel 5250 4000 2    50   Input ~ 0
TXD
Text GLabel 5250 3900 2    50   Input ~ 0
RXD
$Comp
L Device:R_Small_US R20
U 1 1 666A8E0C
P 4650 3900
F 0 "R20" V 4550 3850 50  0000 L CNN
F 1 "470" V 4600 3675 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4650 3900 50  0001 C CNN
F 3 "~" H 4650 3900 50  0001 C CNN
	1    4650 3900
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R21
U 1 1 666A9740
P 4375 4000
F 0 "R21" V 4475 3950 50  0000 L CNN
F 1 "470" V 4425 4075 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4375 4000 50  0001 C CNN
F 3 "~" H 4375 4000 50  0001 C CNN
	1    4375 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 4000 4275 4000
Wire Wire Line
	4150 3900 4550 3900
Wire Wire Line
	4750 3900 4925 3900
Wire Wire Line
	4475 4000 5075 4000
$Comp
L Device:R_Small_US R18
U 1 1 666B58F0
P 4925 3625
F 0 "R18" H 4775 3675 50  0000 L CNN
F 1 "10k" H 4725 3575 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 4925 3625 50  0001 C CNN
F 3 "~" H 4925 3625 50  0001 C CNN
	1    4925 3625
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R19
U 1 1 666B5FF1
P 5075 3625
F 0 "R19" H 5150 3675 50  0000 L CNN
F 1 "10k" H 5125 3575 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 5075 3625 50  0001 C CNN
F 3 "~" H 5075 3625 50  0001 C CNN
	1    5075 3625
	1    0    0    -1  
$EndComp
Wire Wire Line
	4925 3725 4925 3900
Connection ~ 4925 3900
Wire Wire Line
	4925 3900 5250 3900
Wire Wire Line
	5075 3725 5075 4000
Connection ~ 5075 4000
Wire Wire Line
	5075 4000 5250 4000
Wire Wire Line
	4925 3525 4925 3375
Wire Wire Line
	4925 3375 5025 3375
Wire Wire Line
	5075 3375 5075 3525
Text GLabel 5750 4025 2    50   Input ~ 0
BOOT
Text GLabel 5725 5650 2    50   Input ~ 0
RST
Wire Wire Line
	5600 5575 5600 5650
Wire Wire Line
	5600 5650 5725 5650
Wire Wire Line
	5600 4100 5600 4025
Wire Wire Line
	5600 4025 5750 4025
$Comp
L power:+3.3V #PWR0105
U 1 1 666C6570
P 5025 3300
F 0 "#PWR0105" H 5025 3150 50  0001 C CNN
F 1 "+3.3V" H 5040 3473 50  0000 C CNN
F 2 "" H 5025 3300 50  0001 C CNN
F 3 "" H 5025 3300 50  0001 C CNN
	1    5025 3300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0106
U 1 1 666C6B01
P 2850 2750
F 0 "#PWR0106" H 2850 2600 50  0001 C CNN
F 1 "+3.3V" H 2865 2923 50  0000 C CNN
F 2 "" H 2850 2750 50  0001 C CNN
F 3 "" H 2850 2750 50  0001 C CNN
	1    2850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5025 3300 5025 3375
Connection ~ 5025 3375
Wire Wire Line
	5025 3375 5075 3375
Wire Wire Line
	2950 3400 2850 3400
Connection ~ 8575 1875
$Comp
L Device:C_Small C?
U 1 1 666DE75B
P 2525 3500
AR Path="/666DE75B" Ref="C?"  Part="1" 
AR Path="/66FE34ED/666DE75B" Ref="C23"  Part="1" 
F 0 "C23" V 2650 3475 50  0000 L CNN
F 1 "100nF" V 2400 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 2525 3500 50  0001 C CNN
F 3 "~" H 2525 3500 50  0001 C CNN
	1    2525 3500
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 666E755C
P 2250 3525
AR Path="/666E755C" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/666E755C" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 2250 3275 50  0001 C CNN
F 1 "GND" H 2255 3352 50  0000 C CNN
F 2 "" H 2250 3525 50  0001 C CNN
F 3 "" H 2250 3525 50  0001 C CNN
	1    2250 3525
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 3525 2250 3500
Wire Wire Line
	1150 4075 1575 4075
Wire Wire Line
	1150 3875 1650 3875
Wire Wire Line
	1575 4525 1575 4075
Connection ~ 1575 4075
Wire Wire Line
	1575 4075 2250 4075
Wire Wire Line
	1775 4525 1775 4175
Connection ~ 1775 4175
Wire Wire Line
	1775 4175 2375 4175
Wire Wire Line
	1150 4175 1775 4175
Wire Wire Line
	1675 4525 1675 3875
Wire Wire Line
	1675 3875 1650 3875
Connection ~ 1650 3875
Wire Wire Line
	2425 3500 2250 3500
Wire Wire Line
	2625 3500 2950 3500
Wire Wire Line
	2850 2750 2850 3400
$Comp
L Device:CP_Small C?
U 1 1 66ACA50A
P 7275 4525
AR Path="/66ACA50A" Ref="C?"  Part="1" 
AR Path="/66FE34ED/66ACA50A" Ref="C3"  Part="1" 
F 0 "C3" H 7363 4571 50  0000 L CNN
F 1 "10uF" H 7363 4480 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.33x1.80mm_HandSolder" H 7275 4525 50  0001 C CNN
F 3 "~" H 7275 4525 50  0001 C CNN
	1    7275 4525
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 66ACA510
P 8100 4725
AR Path="/66ACA510" Ref="C?"  Part="1" 
AR Path="/66FE34ED/66ACA510" Ref="C5"  Part="1" 
F 0 "C5" H 8192 4771 50  0000 L CNN
F 1 "100nF" H 8125 4625 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 8100 4725 50  0001 C CNN
F 3 "~" H 8100 4725 50  0001 C CNN
	1    8100 4725
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 66ACA516
P 7650 4525
AR Path="/66ACA516" Ref="C?"  Part="1" 
AR Path="/66FE34ED/66ACA516" Ref="C4"  Part="1" 
F 0 "C4" H 7742 4571 50  0000 L CNN
F 1 "100nF" H 7675 4425 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7650 4525 50  0001 C CNN
F 3 "~" H 7650 4525 50  0001 C CNN
	1    7650 4525
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 66ACA51C
P 8100 4350
AR Path="/66ACA51C" Ref="R?"  Part="1" 
AR Path="/66FE34ED/66ACA51C" Ref="R28"  Part="1" 
F 0 "R28" H 8168 4396 50  0000 L CNN
F 1 "1.5k" H 8168 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 8100 4350 50  0001 C CNN
F 3 "~" H 8100 4350 50  0001 C CNN
	1    8100 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 66ACA522
P 8425 5100
AR Path="/66ACA522" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66ACA522" Ref="#PWR037"  Part="1" 
F 0 "#PWR037" H 8425 4850 50  0001 C CNN
F 1 "GND" H 8430 4927 50  0000 C CNN
F 2 "" H 8425 5100 50  0001 C CNN
F 3 "" H 8425 5100 50  0001 C CNN
	1    8425 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 4675 8425 4675
Wire Wire Line
	8425 4675 8425 5000
Wire Wire Line
	8100 4625 8100 4575
Wire Wire Line
	8500 4575 8425 4575
Connection ~ 8100 4575
Wire Wire Line
	8100 4575 8100 4450
Wire Wire Line
	8425 5000 8100 5000
Wire Wire Line
	7275 5000 7275 4625
Wire Wire Line
	7650 4625 7650 5000
Connection ~ 7650 5000
Wire Wire Line
	7650 5000 7275 5000
Wire Wire Line
	8100 4825 8100 5000
Connection ~ 8100 5000
Wire Wire Line
	8100 5000 7650 5000
Wire Wire Line
	8425 5000 8425 5100
Connection ~ 8425 5000
Wire Wire Line
	8100 4250 8100 4125
Wire Wire Line
	7275 4425 7275 4125
Wire Wire Line
	7275 4125 7650 4125
Connection ~ 8100 4125
Wire Wire Line
	8100 4125 8100 4000
Wire Wire Line
	7650 4425 7650 4125
Connection ~ 7650 4125
Wire Wire Line
	7650 4125 8100 4125
Text GLabel 8550 4200 2    50   Input ~ 0
ADC1_0
Wire Wire Line
	8550 4200 8425 4200
Wire Wire Line
	8425 4200 8425 4575
Connection ~ 8425 4575
Wire Wire Line
	8425 4575 8100 4575
$Comp
L Connector:Screw_Terminal_01x02 J?
U 1 1 66ACA545
P 8700 4575
AR Path="/66ACA545" Ref="J?"  Part="1" 
AR Path="/66FE34ED/66ACA545" Ref="J5"  Part="1" 
F 0 "J5" H 8780 4567 50  0000 L CNN
F 1 "Thermister" H 8780 4476 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_Altech_AK300-2_P5.00mm" H 8700 4575 50  0001 C CNN
F 3 "~" H 8700 4575 50  0001 C CNN
	1    8700 4575
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 66ACA556
P 8100 4000
AR Path="/66ACA556" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66ACA556" Ref="#PWR027"  Part="1" 
F 0 "#PWR027" H 8100 3850 50  0001 C CNN
F 1 "+3.3V" H 8000 4175 50  0000 L CNN
F 2 "" H 8100 4000 50  0001 C CNN
F 3 "" H 8100 4000 50  0001 C CNN
	1    8100 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 670EA15F
P 9525 1625
AR Path="/670EA15F" Ref="C?"  Part="1" 
AR Path="/66FE34ED/670EA15F" Ref="C27"  Part="1" 
F 0 "C27" H 9350 1750 50  0000 L CNN
F 1 "100nF" H 9275 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9525 1625 50  0001 C CNN
F 3 "~" H 9525 1625 50  0001 C CNN
	1    9525 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 670EA484
P 9850 1625
AR Path="/670EA484" Ref="C?"  Part="1" 
AR Path="/66FE34ED/670EA484" Ref="C28"  Part="1" 
F 0 "C28" H 9675 1750 50  0000 L CNN
F 1 "100nF" H 9600 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 9850 1625 50  0001 C CNN
F 3 "~" H 9850 1625 50  0001 C CNN
	1    9850 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 670EA7D6
P 10150 1625
AR Path="/670EA7D6" Ref="C?"  Part="1" 
AR Path="/66FE34ED/670EA7D6" Ref="C29"  Part="1" 
F 0 "C29" H 9975 1750 50  0000 L CNN
F 1 "100nF" H 9900 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 10150 1625 50  0001 C CNN
F 3 "~" H 10150 1625 50  0001 C CNN
	1    10150 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	9225 1875 9525 1875
Wire Wire Line
	10150 1875 10150 1725
Connection ~ 9225 1875
Wire Wire Line
	10200 1425 10200 1300
Wire Wire Line
	10150 1525 10150 1425
Connection ~ 10150 1425
Wire Wire Line
	10150 1425 10200 1425
Wire Wire Line
	9850 1525 9850 1425
Connection ~ 9850 1425
Wire Wire Line
	9850 1425 10150 1425
Wire Wire Line
	9225 1425 9525 1425
Wire Wire Line
	9525 1525 9525 1425
Connection ~ 9525 1425
Wire Wire Line
	9525 1425 9850 1425
Wire Wire Line
	9525 1725 9525 1875
Connection ~ 9525 1875
Wire Wire Line
	9525 1875 9850 1875
Wire Wire Line
	9850 1725 9850 1875
Connection ~ 9850 1875
Wire Wire Line
	9850 1875 10150 1875
Connection ~ 6025 1875
Connection ~ 6025 1425
Wire Wire Line
	5575 1300 5575 1425
$Comp
L power:+5V #PWR?
U 1 1 670623CD
P 5575 1300
AR Path="/670623CD" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/670623CD" Ref="#PWR08"  Part="1" 
F 0 "#PWR08" H 5575 1150 50  0001 C CNN
F 1 "+5V" H 5590 1473 50  0000 C CNN
F 2 "" H 5575 1300 50  0001 C CNN
F 3 "" H 5575 1300 50  0001 C CNN
	1    5575 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5575 1425 6025 1425
Wire Wire Line
	6025 1875 6675 1875
Connection ~ 7575 1875
Wire Wire Line
	6025 1425 6675 1425
Connection ~ 7575 1425
$Comp
L Device:C_Small C?
U 1 1 6712BDEC
P 7275 1625
AR Path="/6712BDEC" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6712BDEC" Ref="C26"  Part="1" 
F 0 "C26" H 7100 1750 50  0000 L CNN
F 1 "100nF" H 7025 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 7275 1625 50  0001 C CNN
F 3 "~" H 7275 1625 50  0001 C CNN
	1    7275 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6712C4F9
P 6975 1625
AR Path="/6712C4F9" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6712C4F9" Ref="C25"  Part="1" 
F 0 "C25" H 6800 1750 50  0000 L CNN
F 1 "100nF" H 6725 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6975 1625 50  0001 C CNN
F 3 "~" H 6975 1625 50  0001 C CNN
	1    6975 1625
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 6712C82E
P 6675 1625
AR Path="/6712C82E" Ref="C?"  Part="1" 
AR Path="/66FE34ED/6712C82E" Ref="C24"  Part="1" 
F 0 "C24" H 6500 1750 50  0000 L CNN
F 1 "100nF" H 6425 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.18x1.45mm_HandSolder" H 6675 1625 50  0001 C CNN
F 3 "~" H 6675 1625 50  0001 C CNN
	1    6675 1625
	1    0    0    -1  
$EndComp
Wire Wire Line
	7275 1725 7275 1875
Connection ~ 7275 1875
Wire Wire Line
	7275 1875 7575 1875
Wire Wire Line
	6975 1725 6975 1875
Connection ~ 6975 1875
Wire Wire Line
	6975 1875 7275 1875
Wire Wire Line
	6675 1725 6675 1875
Connection ~ 6675 1875
Wire Wire Line
	6675 1875 6975 1875
Wire Wire Line
	6675 1525 6675 1425
Connection ~ 6675 1425
Wire Wire Line
	6675 1425 6975 1425
Wire Wire Line
	6975 1525 6975 1425
Connection ~ 6975 1425
Wire Wire Line
	6975 1425 7275 1425
Wire Wire Line
	7275 1525 7275 1425
Connection ~ 7275 1425
Wire Wire Line
	7275 1425 7575 1425
$Comp
L SamacSys:5819SMJE3_TR13 D4
U 1 1 669A0B16
P 1650 2950
F 0 "D4" V 1904 3080 50  0000 L CNN
F 1 "5819SMJE3_TR13" V 1995 3080 50  0000 L CNN
F 2 "SamacSys_Parts:DIOM5436X295N" H 2100 2950 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/5819smje3tr13/microchip-technology" H 2100 2850 50  0001 L CNN
F 4 "Schottky Diodes & Rectifiers Schottky" H 2100 2750 50  0001 L CNN "Description"
F 5 "2.95" H 2100 2650 50  0001 L CNN "Height"
F 6 "Microchip" H 2100 2550 50  0001 L CNN "Manufacturer_Name"
F 7 "5819SMJE3/TR13" H 2100 2450 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "494-5819SMJE3/TR13" H 2100 2350 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Microchip-Technology/5819SMJE3-TR13?qs=6jAvgNDGUA%252BV22mi1Xj0%2Fw%3D%3D" H 2100 2250 50  0001 L CNN "Mouser Price/Stock"
F 10 "5819SMJE3/TR13" H 2100 2150 50  0001 L CNN "Arrow Part Number"
F 11 "null?region=nac" H 2100 2050 50  0001 L CNN "Arrow Price/Stock"
	1    1650 2950
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R6
U 1 1 66A8AF32
P 1275 1425
F 0 "R6" H 1350 1475 50  0000 L CNN
F 1 "10k" H 1325 1375 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.20x1.40mm_HandSolder" H 1275 1425 50  0001 C CNN
F 3 "~" H 1275 1425 50  0001 C CNN
	1    1275 1425
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 1175 1275 1175
Wire Wire Line
	1275 1325 1275 1175
Connection ~ 1275 1175
Wire Wire Line
	1275 1175 2900 1175
Wire Wire Line
	1175 1675 1275 1675
Wire Wire Line
	1275 1525 1275 1675
Connection ~ 1275 1675
Wire Wire Line
	1275 1675 4325 1675
$Comp
L Device:Polyfuse_Small F1
U 1 1 66B54E8F
P 4450 2050
F 0 "F1" V 4655 2050 50  0000 C CNN
F 1 "Polyfuse_Small" V 4564 2050 50  0000 C CNN
F 2 "Fuse:Fuse_2512_6332Metric_Pad1.52x3.35mm_HandSolder" H 4500 1850 50  0001 L CNN
F 3 "~" H 4450 2050 50  0001 C CNN
	1    4450 2050
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N5819 D1
U 1 1 66B5DADB
P 4700 2275
F 0 "D1" V 4654 2355 50  0000 L CNN
F 1 "1N5819" V 4745 2355 50  0000 L CNN
F 2 "SamacSys_Parts:DIOM5436X295N" H 4700 2100 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88525/1n5817.pdf" H 4700 2275 50  0001 C CNN
	1    4700 2275
	0    1    1    0   
$EndComp
Wire Wire Line
	4550 2050 4700 2050
Wire Wire Line
	4700 2050 4700 2125
$Comp
L Device:D_Zener D6
U 1 1 66B6E558
P 5175 2275
F 0 "D6" V 5221 2195 50  0000 R CNN
F 1 "SMAZ6V2" V 5130 2195 50  0000 R CNN
F 2 "DIODE_SMD:DO-214AA" H 5175 2275 50  0001 C CNN
F 3 "~" H 5175 2275 50  0001 C CNN
	1    5175 2275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4700 2050 5175 2050
Wire Wire Line
	5175 2050 5175 2125
Connection ~ 4700 2050
Wire Wire Line
	5175 2425 5175 2500
Wire Wire Line
	5175 2500 4700 2500
Wire Wire Line
	4700 2500 4700 2425
Wire Wire Line
	5175 2500 5700 2500
Wire Wire Line
	5700 2500 5700 1875
Connection ~ 5175 2500
Wire Wire Line
	5700 1875 6025 1875
Wire Wire Line
	3775 2050 4075 2050
Connection ~ 4700 2500
Wire Wire Line
	5175 2050 5450 2050
Wire Wire Line
	5450 2050 5450 1425
Wire Wire Line
	5450 1425 5575 1425
Connection ~ 5175 2050
Connection ~ 5575 1425
NoConn ~ 3775 2150
$Comp
L SamacSys:MSD-4-A J6
U 1 1 66B80819
P 2900 875
F 0 "J6" H 3550 1140 50  0000 C CNN
F 1 "MSD-4-A" H 3550 1049 50  0000 C CNN
F 2 "SamacSys_Parts:MSD4A" H 4050 975 50  0001 L CNN
F 3 "https://www.cuidevices.com/product/resource/pdf/msd-4-a.pdf" H 4050 875 50  0001 L CNN
F 4 "Memory Card Connectors 9 Positions, Push In, Auto Eject Out, SMT, 1.8 mm Height Above Board," H 4050 775 50  0001 L CNN "Description"
F 5 "2" H 4050 675 50  0001 L CNN "Height"
F 6 "CUI Devices" H 4050 575 50  0001 L CNN "Manufacturer_Name"
F 7 "MSD-4-A" H 4050 475 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "179-MSD-4-A" H 4050 375 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/CUI-Devices/MSD-4-A?qs=Z%252BL2brAPG1Jll%252BQTi%252Btupg%3D%3D" H 4050 275 50  0001 L CNN "Mouser Price/Stock"
	1    2900 875 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_Switch J9
U 1 1 66BF2A4A
P 3475 2150
F 0 "J9" H 3532 2467 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 3532 2376 50  0000 C CNN
F 2 "Connector_Custom:PJ-059A" H 3525 2110 50  0001 C CNN
F 3 "~" H 3525 2110 50  0001 C CNN
	1    3475 2150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J7
U 1 1 66B792C8
P 7500 2450
F 0 "J7" H 7625 2400 50  0000 C CNN
F 1 "Test_5V" H 7500 2225 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 7500 2450 50  0001 C CNN
F 3 "~" H 7500 2450 50  0001 C CNN
	1    7500 2450
	1    0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J10
U 1 1 66B79CA1
P 3625 2625
F 0 "J10" H 3775 2575 50  0000 C CNN
F 1 "+5V IN" H 3625 2425 50  0000 C CNN
F 2 "Connector_JST:JST_XH_B2B-XH-A_1x02_P2.50mm_Vertical" H 3625 2625 50  0001 C CNN
F 3 "~" H 3625 2625 50  0001 C CNN
	1    3625 2625
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 66B8ADD6
P 6850 2550
AR Path="/66B8ADD6" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66B8ADD6" Ref="#PWR019"  Part="1" 
F 0 "#PWR019" H 6850 2300 50  0001 C CNN
F 1 "GND" H 6950 2425 50  0000 C CNN
F 2 "" H 6850 2550 50  0001 C CNN
F 3 "" H 6850 2550 50  0001 C CNN
	1    6850 2550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 66BA5244
P 6825 2350
AR Path="/66BA5244" Ref="#PWR?"  Part="1" 
AR Path="/66FE34ED/66BA5244" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 6825 2200 50  0001 C CNN
F 1 "+5V" V 6825 2550 50  0000 C CNN
F 2 "" H 6825 2350 50  0001 C CNN
F 3 "" H 6825 2350 50  0001 C CNN
	1    6825 2350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3825 2625 4400 2625
Wire Wire Line
	4400 2625 4400 2500
Wire Wire Line
	4400 2500 4700 2500
Wire Wire Line
	4400 2250 4400 2500
Wire Wire Line
	3775 2250 4400 2250
Connection ~ 4400 2500
Wire Wire Line
	3825 2525 4075 2525
Wire Wire Line
	4075 2525 4075 2050
Connection ~ 4075 2050
Wire Wire Line
	4075 2050 4350 2050
Wire Wire Line
	6825 2350 7300 2350
Wire Wire Line
	6850 2550 6850 2450
Wire Wire Line
	6850 2450 7300 2450
$EndSCHEMATC
