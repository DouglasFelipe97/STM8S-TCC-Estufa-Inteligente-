EESchema Schematic File Version 4
EELAYER 30 0
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
Text Label 4760 4530 3    50   ~ 0
VSS
$Comp
L MCU_ST_STM8:STM8S003K3T U2
U 1 1 62214E79
P 4760 3130
F 0 "U2" H 5180 4670 50  0000 C CNN
F 1 "STM8S003K3T" H 5190 4540 50  0000 C CNN
F 2 "Package_QFP:LQFP-32_7x7mm_P0.8mm" H 4810 4630 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00024550.pdf" H 4760 3130 50  0001 C CNN
	1    4760 3130
	1    0    0    -1  
$EndComp
Text Label 5360 3130 0    50   ~ 0
RX
Text Label 5360 3030 0    50   ~ 0
TX
Text Label 5360 3230 0    50   ~ 0
RSIO
Text Label 5360 2630 0    50   ~ 0
GRAV2
$Comp
L Interface_UART:SN75176AD U3
U 1 1 6226A1F4
P 8836 5673
F 0 "U3" H 9146 6133 50  0000 C CNN
F 1 "SN75176AD" H 9136 6043 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 8836 5173 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn75176a.pdf" H 10436 5473 50  0001 C CNN
	1    8836 5673
	1    0    0    -1  
$EndComp
Text Label 1964 5369 0    50   ~ 0
VCC
Text Label 1964 5469 0    50   ~ 0
VSS
$Comp
L Connector_Generic:Conn_02x02_Odd_Even J2
U 1 1 62270048
P 10456 5903
F 0 "J2" H 10506 6120 50  0000 C CNN
F 1 "Conn_02x02_Odd_Even" H 10506 6029 50  0000 C CNN
F 2 "Connector_Molex:Molex_Mini-Fit_Jr_5566-04A_2x02_P4.20mm_Vertical" H 10456 5903 50  0001 C CNN
F 3 "~" H 10456 5903 50  0001 C CNN
	1    10456 5903
	-1   0    0    1   
$EndComp
$Comp
L Regulator_Linear:L7805 U1
U 1 1 622726F2
P 4264 5569
F 0 "U1" H 4264 5811 50  0000 C CNN
F 1 "L7805" H 4264 5720 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4289 5419 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 4264 5519 50  0001 C CNN
	1    4264 5569
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D1
U 1 1 62273845
P 2464 5569
F 0 "D1" H 2464 5834 50  0000 C CNN
F 1 "1N4007" H 2464 5743 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 2464 5569 50  0001 C CNN
F 3 "~" H 2464 5569 50  0001 C CNN
	1    2464 5569
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C1
U 1 1 622749B5
P 2964 6069
F 0 "C1" H 3014 6169 50  0000 L CNN
F 1 "100uF 25V" H 2764 6069 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 2964 6069 50  0001 C CNN
F 3 "~" H 2964 6069 50  0001 C CNN
	1    2964 6069
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C2
U 1 1 62275E23
P 3514 6069
F 0 "C2" H 3564 6169 50  0000 L CNN
F 1 "100nF" H 3414 6069 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3514 6069 50  0001 C CNN
F 3 "~" H 3514 6069 50  0001 C CNN
	1    3514 6069
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C5
U 1 1 62276401
P 5314 6069
F 0 "C5" H 5364 6169 50  0000 L CNN
F 1 "100uF 25V" H 5164 6069 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 5314 6069 50  0001 C CNN
F 3 "~" H 5314 6069 50  0001 C CNN
	1    5314 6069
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C3
U 1 1 622767DC
P 4814 6069
F 0 "C3" H 4864 6169 50  0000 L CNN
F 1 "100nF" H 4714 6069 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4814 6069 50  0001 C CNN
F 3 "~" H 4814 6069 50  0001 C CNN
	1    4814 6069
	1    0    0    -1  
$EndComp
Wire Wire Line
	2664 5569 2964 5569
Wire Wire Line
	2964 5569 2964 5819
Wire Wire Line
	2964 5569 3514 5569
Wire Wire Line
	3514 5569 3514 5819
Connection ~ 2964 5569
Wire Wire Line
	4264 5869 4264 6469
Wire Wire Line
	2964 6319 2964 6469
Wire Wire Line
	2964 6469 3514 6469
Wire Wire Line
	3514 6469 3514 6319
Wire Wire Line
	3514 6469 4264 6469
Connection ~ 3514 6469
Connection ~ 4264 6469
Text Label 4264 6469 3    50   ~ 0
VSS
Wire Wire Line
	2264 5569 2174 5569
Text Label 5464 5569 0    50   ~ 0
VDD
Wire Wire Line
	4264 6469 4814 6469
Wire Wire Line
	4564 5569 4814 5569
Wire Wire Line
	4814 5819 4814 5569
Connection ~ 4814 5569
Wire Wire Line
	4814 5569 5314 5569
Wire Wire Line
	4814 6319 4814 6469
Connection ~ 4814 6469
Wire Wire Line
	4814 6469 5314 6469
Wire Wire Line
	5314 5819 5314 5569
Connection ~ 5314 5569
Wire Wire Line
	5314 5569 5464 5569
Wire Wire Line
	5314 6319 5314 6469
$Comp
L pspice:CAP C4
U 1 1 622781B0
P 3980 1540
F 0 "C4" H 4030 1640 50  0000 L CNN
F 1 "4,7uF " H 3830 1540 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3980 1540 50  0001 C CNN
F 3 "~" H 3980 1540 50  0001 C CNN
	1    3980 1540
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C6
U 1 1 62279CCE
P 3950 4490
F 0 "C6" H 4000 4590 50  0000 L CNN
F 1 "1uF" H 3870 4490 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3950 4490 50  0001 C CNN
F 3 "~" H 3950 4490 50  0001 C CNN
	1    3950 4490
	1    0    0    -1  
$EndComp
Text Label 3950 4740 0    50   ~ 0
VSS
$Comp
L Device:R R3
U 1 1 6228EDD8
P 5660 2480
F 0 "R3" H 5730 2526 50  0000 L CNN
F 1 "4K7" H 5730 2435 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5590 2480 50  0001 C CNN
F 3 "~" H 5660 2480 50  0001 C CNN
	1    5660 2480
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 6228F24A
P 3720 4130
F 0 "R6" V 3640 4050 50  0000 L CNN
F 1 "4K7" V 3570 4050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3650 4130 50  0001 C CNN
F 3 "~" H 3720 4130 50  0001 C CNN
	1    3720 4130
	0    1    1    0   
$EndComp
Text Label 4160 4130 2    50   ~ 0
GRAV1
Text Label 3570 4130 2    50   ~ 0
VDD
$Comp
L Device:R R5
U 1 1 6229104A
P 3610 1280
F 0 "R5" V 3710 1240 50  0000 L CNN
F 1 "0R" V 3520 1200 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3540 1280 50  0001 C CNN
F 3 "~" H 3610 1280 50  0001 C CNN
	1    3610 1280
	0    1    1    0   
$EndComp
$Comp
L pspice:CAP C7
U 1 1 622939CC
P 4370 1540
F 0 "C7" H 4420 1640 50  0000 L CNN
F 1 "100nF" H 4270 1540 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4370 1540 50  0001 C CNN
F 3 "~" H 4370 1540 50  0001 C CNN
	1    4370 1540
	1    0    0    -1  
$EndComp
Wire Wire Line
	3760 1280 3980 1280
Wire Wire Line
	3980 1280 3980 1290
Wire Wire Line
	3980 1280 4370 1280
Wire Wire Line
	4370 1280 4370 1290
Connection ~ 3980 1280
Text Label 3460 1280 2    50   ~ 0
VDD
Wire Wire Line
	4370 1280 4760 1280
Wire Wire Line
	4760 1280 4760 1730
Connection ~ 4370 1280
$Comp
L Device:R R8
U 1 1 6229D2E2
P 6010 3030
F 0 "R8" V 5860 2940 50  0000 L CNN
F 1 "4K7" V 5930 2940 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5940 3030 50  0001 C CNN
F 3 "~" H 6010 3030 50  0001 C CNN
	1    6010 3030
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 6229E08C
P 6290 3130
F 0 "R9" V 6460 3040 50  0000 L CNN
F 1 "4K7" V 6380 3040 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6220 3130 50  0001 C CNN
F 3 "~" H 6290 3130 50  0001 C CNN
	1    6290 3130
	0    1    1    0   
$EndComp
Text Label 6440 3030 0    50   ~ 0
VDD
$Comp
L pspice:CAP C9
U 1 1 622A36FF
P 8106 5033
F 0 "C9" H 8156 5133 50  0000 L CNN
F 1 "4,7uF " H 7956 5033 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 8106 5033 50  0001 C CNN
F 3 "~" H 8106 5033 50  0001 C CNN
	1    8106 5033
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 622A3709
P 7736 4773
F 0 "R11" V 7566 4693 50  0000 L CNN
F 1 "0R" V 7646 4693 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7666 4773 50  0001 C CNN
F 3 "~" H 7736 4773 50  0001 C CNN
	1    7736 4773
	0    1    1    0   
$EndComp
$Comp
L pspice:CAP C11
U 1 1 622A3713
P 8496 5033
F 0 "C11" H 8546 5133 50  0000 L CNN
F 1 "100nF" H 8396 5033 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 8496 5033 50  0001 C CNN
F 3 "~" H 8496 5033 50  0001 C CNN
	1    8496 5033
	1    0    0    -1  
$EndComp
Wire Wire Line
	7886 4773 8106 4773
Wire Wire Line
	8106 4773 8106 4783
Wire Wire Line
	8106 4773 8496 4773
Connection ~ 8106 4773
Text Label 7586 4773 2    50   ~ 0
VDD
Wire Wire Line
	8106 5283 8496 5283
Wire Wire Line
	8496 4773 8496 4783
Wire Wire Line
	8496 4773 8836 4773
Connection ~ 8496 4773
$Comp
L Device:R R13
U 1 1 622B21DD
P 9446 5963
F 0 "R13" V 9616 5873 50  0000 L CNN
F 1 "10R" V 9536 5873 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9376 5963 50  0001 C CNN
F 3 "~" H 9446 5963 50  0001 C CNN
	1    9446 5963
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 622B2F02
P 9446 5693
F 0 "R12" V 9286 5613 50  0000 L CNN
F 1 "10R" V 9356 5613 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9376 5693 50  0001 C CNN
F 3 "~" H 9446 5693 50  0001 C CNN
	1    9446 5693
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D5
U 1 1 622B409D
P 9796 6263
F 0 "D5" H 9796 6480 50  0000 C CNN
F 1 "5V1" H 9796 6389 50  0000 C CNN
F 2 "Diode_SMD:D_MiniMELF" H 9796 6263 50  0001 C CNN
F 3 "~" H 9796 6263 50  0001 C CNN
	1    9796 6263
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Zener D4
U 1 1 622B4CE7
P 9796 5453
F 0 "D4" H 9796 5670 50  0000 C CNN
F 1 "5V1" H 9796 5579 50  0000 C CNN
F 2 "Diode_SMD:D_MiniMELF" H 9796 5453 50  0001 C CNN
F 3 "~" H 9796 5453 50  0001 C CNN
	1    9796 5453
	1    0    0    -1  
$EndComp
Wire Wire Line
	9136 5773 9266 5773
Wire Wire Line
	9266 5773 9266 5693
Wire Wire Line
	9266 5693 9296 5693
Wire Wire Line
	9136 5873 9256 5873
Wire Wire Line
	9256 5873 9256 5963
Wire Wire Line
	9256 5963 9296 5963
Wire Wire Line
	9596 5693 9626 5693
Wire Wire Line
	9626 5693 9626 5453
Wire Wire Line
	9626 5453 9646 5453
Wire Wire Line
	9626 5963 9626 6263
Wire Wire Line
	9626 6263 9646 6263
Text Label 9946 5453 0    50   ~ 0
VSS
Text Label 9946 6263 0    50   ~ 0
VSS
Text Label 7370 7490 0    50   ~ 0
Interface_comando
Text Label 8150 7630 0    50   ~ 0
09-03-22
Wire Wire Line
	9626 5693 9626 5803
Wire Wire Line
	9626 5803 10156 5803
Connection ~ 9626 5693
Wire Wire Line
	9596 5963 9626 5963
Wire Wire Line
	9626 5903 9626 5963
Wire Wire Line
	9626 5903 10156 5903
Connection ~ 9626 5963
Text Label 10656 5803 0    50   ~ 0
VCC
Text Label 10656 5903 0    50   ~ 0
VSS
Text Label 8836 6073 3    50   ~ 0
VSS
$Comp
L Device:LED D2
U 1 1 622F7964
P 3020 3460
F 0 "D2" H 3013 3677 50  0000 C CNN
F 1 "LED" H 3013 3586 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 3020 3460 50  0001 C CNN
F 3 "~" H 3020 3460 50  0001 C CNN
	1    3020 3460
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 622F83D9
P 3020 3790
F 0 "D3" H 3013 4007 50  0000 C CNN
F 1 "LED" H 3013 3916 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 3020 3790 50  0001 C CNN
F 3 "~" H 3020 3790 50  0001 C CNN
	1    3020 3790
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 622F8A8D
P 3400 3460
F 0 "R1" V 3550 3440 50  0000 L CNN
F 1 "1K" V 3480 3440 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3330 3460 50  0001 C CNN
F 3 "~" H 3400 3460 50  0001 C CNN
	1    3400 3460
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 622F9765
P 3400 3790
F 0 "R2" V 3540 3750 50  0000 L CNN
F 1 "1K" V 3470 3750 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3330 3790 50  0001 C CNN
F 3 "~" H 3400 3790 50  0001 C CNN
	1    3400 3790
	0    1    1    0   
$EndComp
Wire Wire Line
	3170 3460 3250 3460
Wire Wire Line
	3170 3790 3250 3790
Wire Wire Line
	2870 3460 2780 3460
Wire Wire Line
	2780 3460 2780 3790
Wire Wire Line
	2780 3790 2870 3790
Text Label 2780 3630 2    50   ~ 0
VSS
Text Label 7628 822  1    50   ~ 0
VDD
Text Label 7728 822  1    50   ~ 0
VSS
Text Label 7828 822  1    50   ~ 0
GRAV1
Text Label 7928 822  1    50   ~ 0
GRAV2
NoConn ~ 4160 2030
NoConn ~ 4160 2230
NoConn ~ 5360 3630
NoConn ~ 5360 2930
NoConn ~ 5360 2530
Wire Wire Line
	8836 5273 8836 4773
Wire Wire Line
	3964 5569 3514 5569
Connection ~ 3514 5569
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 622BC0B7
P 1664 5469
F 0 "J1" H 1721 5786 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 1721 5695 50  0000 C CNN
F 2 "Connector_BarrelJack:P4_Macho" H 1714 5429 50  0001 C CNN
F 3 "~" H 1714 5429 50  0001 C CNN
	1    1664 5469
	1    0    0    -1  
$EndComp
Wire Wire Line
	1964 5369 2174 5369
Wire Wire Line
	2174 5369 2174 5569
Text Label 1964 5569 0    50   ~ 0
VSS
Wire Wire Line
	3980 1790 4370 1790
Text Label 4170 1790 3    50   ~ 0
VSS
Text Label 8296 5283 3    50   ~ 0
VSS
Text Label 8536 5873 2    50   ~ 0
RX
Text Label 8536 5573 2    50   ~ 0
TX
Wire Wire Line
	8536 5473 8436 5473
Wire Wire Line
	8436 5773 8536 5773
Wire Wire Line
	8436 5473 8436 5773
Text Label 4160 2130 2    50   ~ 0
T1
$Comp
L Connector:Conn_01x05_Male J5
U 1 1 6260D59D
P 8328 1032
F 0 "J5" V 8228 1262 50  0000 R CNN
F 1 "Conn_01x05_Male" V 8128 1302 50  0000 R CNN
F 2 "" H 8328 1032 50  0001 C CNN
F 3 "~" H 8328 1032 50  0001 C CNN
	1    8328 1032
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x05_Male J7
U 1 1 6260F531
P 9708 1052
F 0 "J7" V 9618 1282 50  0000 R CNN
F 1 "Conn_01x05_Male" V 9528 1312 50  0000 R CNN
F 2 "" H 9708 1052 50  0001 C CNN
F 3 "~" H 9708 1052 50  0001 C CNN
	1    9708 1052
	0    -1   -1   0   
$EndComp
Text Label 8128 832  1    50   ~ 0
T1
Text Label 8228 832  1    50   ~ 0
T2
Text Label 8328 832  1    50   ~ 0
T3
Text Label 8428 832  1    50   ~ 0
T4
Text Label 8528 832  1    50   ~ 0
VSS
Text Label 9508 852  1    50   ~ 0
D4
Text Label 9608 852  1    50   ~ 0
D5
Text Label 9708 852  1    50   ~ 0
D6
Text Label 9808 852  1    50   ~ 0
D7
Text Label 9908 852  1    50   ~ 0
EN
$Comp
L Connector:Conn_01x05_Male J6
U 1 1 6261C62B
P 9018 1042
F 0 "J6" V 8928 1272 50  0000 R CNN
F 1 "Conn_01x05_Male" V 8828 1312 50  0000 R CNN
F 2 "" H 9018 1042 50  0001 C CNN
F 3 "~" H 9018 1042 50  0001 C CNN
	1    9018 1042
	0    -1   -1   0   
$EndComp
Text Label 8818 842  1    50   ~ 0
RS
Text Label 8918 842  1    50   ~ 0
RW
Text Label 9018 842  1    50   ~ 0
V0
Text Label 9118 842  1    50   ~ 0
VDD
Text Label 9218 842  1    50   ~ 0
VSS
$Comp
L Connector:Conn_01x04_Male J3
U 1 1 62637249
P 7728 1022
F 0 "J3" V 7648 1152 50  0000 R CNN
F 1 "Conn_01x04_Male" V 7518 1372 50  0000 R CNN
F 2 "" H 7728 1022 50  0001 C CNN
F 3 "~" H 7728 1022 50  0001 C CNN
	1    7728 1022
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3870 4130 4160 4130
Text Label 5660 2330 1    50   ~ 0
VDD
Wire Wire Line
	5360 3030 5860 3030
Wire Wire Line
	5360 3130 6140 3130
Wire Wire Line
	5360 2630 5660 2630
Wire Wire Line
	3950 4230 4160 4230
Wire Wire Line
	3950 4230 3950 4240
Wire Wire Line
	6440 3030 6440 3130
Wire Wire Line
	6160 3030 6440 3030
Wire Wire Line
	3740 3790 3550 3790
Wire Wire Line
	4160 3730 3880 3730
Wire Wire Line
	3880 3730 3880 3460
Wire Wire Line
	3550 3460 3880 3460
Wire Wire Line
	3740 3790 3740 3830
Wire Wire Line
	3740 3830 4160 3830
Text Label 8536 5473 2    50   ~ 0
RSIO
$Comp
L Transistor_Array:ULN2003 U?
U 1 1 62656BAB
P 7961 3048
F 0 "U?" H 7961 3715 50  0000 C CNN
F 1 "ULN2003" H 7961 3624 50  0000 C CNN
F 2 "" H 8011 2498 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 8061 2848 50  0001 C CNN
	1    7961 3048
	1    0    0    -1  
$EndComp
$Comp
L Relay:RT314A12 K?
U 1 1 6265F6C9
P 9924 1909
F 0 "K?" H 10354 1955 50  0000 L CNN
F 1 "RT314A12" H 10354 1864 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Schrack-RT1-16A-FormC_RM5mm" H 11474 1859 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English" H 9924 1909 50  0001 C CNN
	1    9924 1909
	1    0    0    -1  
$EndComp
$Comp
L Relay:RT314A12 K?
U 1 1 62661D85
P 9911 2722
F 0 "K?" H 10341 2768 50  0000 L CNN
F 1 "RT314A12" H 10341 2677 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Schrack-RT1-16A-FormC_RM5mm" H 11461 2672 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English" H 9911 2722 50  0001 C CNN
	1    9911 2722
	1    0    0    -1  
$EndComp
$Comp
L Relay:RT314A12 K?
U 1 1 62662AED
P 9919 3474
F 0 "K?" H 10349 3520 50  0000 L CNN
F 1 "RT314A12" H 10349 3429 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Schrack-RT1-16A-FormC_RM5mm" H 11469 3424 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English" H 9919 3474 50  0001 C CNN
	1    9919 3474
	1    0    0    -1  
$EndComp
$Comp
L Relay:RT314A12 K?
U 1 1 62663973
P 9913 4252
F 0 "K?" H 10343 4298 50  0000 L CNN
F 1 "RT314A12" H 10343 4207 50  0000 L CNN
F 2 "Relay_THT:Relay_SPDT_Schrack-RT1-16A-FormC_RM5mm" H 11463 4202 50  0001 C CNN
F 3 "https://www.te.com/commerce/DocumentDelivery/DDEController?Action=srchrtrv&DocNm=RT1_bistable&DocType=DS&DocLang=English" H 9913 4252 50  0001 C CNN
	1    9913 4252
	1    0    0    -1  
$EndComp
$EndSCHEMATC
