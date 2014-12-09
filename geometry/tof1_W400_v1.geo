//**************************************************************************************
// TOF version 1, Wall, 3 regions, Z = 4000 mm
// 24 modules(Type A, central region) * 30 strips(10x300, sens. - 10x300)  
// + 2 region * 12 modules (type B, on the edge regions) * 24 strips(610x12.5, sens. - 600x10)
// = 1296 x2 readout channels?
//
// region A(central):	moduleID=[1-24]
// region B_Left(X<0):	moduleID=[101-112]
// region B_Right(X>0):	moduleID=[113-124]
//
// 17.09.1014 Sergei Lobastov (LHE, JINR, Dubna)
//**************************************************************************************
TOFB1
cave
BOX
air
   1870.00 -820.00 -25.00
   1870.00 820.00 -25.00
   -1870.00 820.00 -25.00
   -1870.00 -820.00 -25.00
   1870.00 -820.00 25.00
   1870.00 820.00 25.00
   -1870.00 820.00 25.00
   -1870.00 -820.00 25.00

 0. 0. 4000.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Module type A(central)
//------------------------------------------------------------------------------------
t1modA#1
TOFB1
BOX
air
   150.00 -150.00 -6.00
   150.00 150.00 -6.00
   -150.00 150.00 -6.00
   -150.00 -150.00 -6.00
   150.00 -150.00 6.00
   150.00 150.00 6.00
   -150.00 150.00 6.00
   -150.00 -150.00 6.00

 -560. 560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Strip type A
//------------------------------------------------------------------------------------
t1stripA#1
t1modA#1
BOX
air
   5.00 -150.00 -6.00
   5.00 150.00 -6.00
   -5.00 150.00 -6.00
   -5.00 -150.00 -6.00
   5.00 -150.00 6.00
   5.00 150.00 6.00
   -5.00 150.00 6.00
   -5.00 -150.00 6.00

 -145. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Assembly strip type A
//------------------------------------------------------------------------------------
t1gasA
t1stripA#1
BOX
RPCgas
   5.00 -150.00 -1.00
   5.00 150.00 -1.00
   -5.00 150.00 -1.00
   -5.00 -150.00 -1.00
   5.00 -150.00 1.00
   5.00 150.00 1.00
   -5.00 150.00 1.00
   -5.00 -150.00 1.00

  0. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1glassA
t1stripA#1
BOX
RPCglass
   5.00 -150.00 -2.40
   5.00 150.00 -2.40
   -5.00 150.00 -2.40
   -5.00 -150.00 -2.40
   5.00 -150.00 2.40
   5.00 150.00 2.40
   -5.00 150.00 2.40
   -5.00 -150.00 2.40

  0. 0. -3.4
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1G10A
t1stripA#1
BOX
G10
   5.00 -150.00 -2.25
   5.00 150.00 -2.25
   -5.00 150.00 -2.25
   -5.00 -150.00 -2.25
   5.00 -150.00 2.25
   5.00 150.00 2.25
   -5.00 150.00 2.25
   -5.00 -150.00 2.25

  0. 0. 3.25
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Copy strip type A
//------------------------------------------------------------------------------------
t1stripA#2
t1modA#1
 -135. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#3
t1modA#1
 -125. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#4
t1modA#1
 -115. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#5
t1modA#1
 -105. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#6
t1modA#1
 -95. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#7
t1modA#1
 -85. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#8
t1modA#1
 -75. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#9
t1modA#1
 -65. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#10
t1modA#1
 -55. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#11
t1modA#1
 -45. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#12
t1modA#1
 -35. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#13
t1modA#1
 -25. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#14
t1modA#1
 -15. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#15
t1modA#1
 -5. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#16
t1modA#1
 5. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#17
t1modA#1
 15. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#18
t1modA#1
 25. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#19
t1modA#1
 35. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#20
t1modA#1
 45. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#21
t1modA#1
 55. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#22
t1modA#1
 65. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#23
t1modA#1
 75. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#24
t1modA#1
 85. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#25
t1modA#1
 95. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#26
t1modA#1
 105. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#27
t1modA#1
 115. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#28
t1modA#1
 125. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#29
t1modA#1
 135. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripA#30
t1modA#1
 145. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Copy module type A
//------------------------------------------------------------------------------------
t1modA#2
TOFB1
 0. 560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#3
TOFB1
 560. 560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#4
TOFB1
 -560. 0. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#5
TOFB1
 560. 0. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#6
TOFB1
 -560. -560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#7
TOFB1
 0. -560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#8
TOFB1
 560. -560. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------

t1modA#9
TOFB1
 -560. 280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#10
TOFB1
 0. 280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#11
TOFB1
 560. 280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#12
TOFB1
 -560. -280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#13
TOFB1
 0. -280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#14
TOFB1
 560. -280. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#15
TOFB1
 -280. 280. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#16
TOFB1
 280. 280. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#17
TOFB1
 -280. -280. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#18
TOFB1
 280. -280. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#19
TOFB1
 -280. 560. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#20
TOFB1
 280. 560. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#21
TOFB1
 -280. 0. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#22
TOFB1
 280. 0. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#23
TOFB1
 -280. -560. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modA#24
TOFB1
 280. -560. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Module type B(on the edge)
//------------------------------------------------------------------------------------
t1modB#1
TOFB1
BOX
air
   305.00 -165.00 -6.00
   305.00 165.00 -6.00
   -305.00 165.00 -6.00
   -305.00 -165.00 -6.00
   305.00 -165.00 6.00
   305.00 165.00 6.00
   -305.00 165.00 6.00
   -305.00 -165.00 6.00

 -1565. 635. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Strip type B
//------------------------------------------------------------------------------------
t1stripB#1
t1modB#1
BOX
air
   300.00 -12.50 -6.00
   300.00 12.50 -6.00
   -300.00 12.50 -6.00
   -300.00 -12.50 -6.00
   300.00 -12.50 6.00
   300.00 12.50 6.00
   -300.00 12.50 6.00
   -300.00 -12.50 6.00

 0. 143.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Assembly strip type B
//------------------------------------------------------------------------------------
t1gasB
t1stripB#1
BOX
RPCgas
   300.00 -10.00 -1.00
   300.00 10.00 -1.00
   -300.00 10.00 -1.00
   -300.00 -10.00 -1.00
   300.00 -10.00 1.00
   300.00 10.00 1.00
   -300.00 10.00 1.00
   -300.00 -10.00 1.00

  0. 0. 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1glassB
t1stripB#1
BOX
RPCglass
   300.00 -10.00 -2.40
   300.00 10.00 -2.40
   -300.00 10.00 -2.40
   -300.00 -10.00 -2.40
   300.00 -10.00 2.40
   300.00 10.00 2.40
   -300.00 10.00 2.40
   -300.00 -10.00 2.40

  0. 0. -3.4
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1G10B
t1stripB#1
BOX
G10
   300.00 -10.00 -2.25
   300.00 10.00 -2.25
   -300.00 10.00 -2.25
   -300.00 -10.00 -2.25
   300.00 -10.00 2.25
   300.00 10.00 2.25
   -300.00 10.00 2.25
   -300.00 -10.00 2.25

  0. 0. 3.25
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Copy strip type B
//------------------------------------------------------------------------------------
t1stripB#2
t1modB#1
 0. 131.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#3
t1modB#1
 0. 118.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#4
t1modB#1
 0. 106.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#5
t1modB#1
 0. 93.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#6
t1modB#1
 0. 81.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#7
t1modB#1
 0. 68.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#8
t1modB#1
 0. 56.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#9
t1modB#1
 0. 43.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#10
t1modB#1
 0. 31.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#11
t1modB#1
 0. 18.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#12
t1modB#1
 0. 6.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#13
t1modB#1
 0. -6.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#14
t1modB#1
 0. -18.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#15
t1modB#1
 0. -31.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#16
t1modB#1
 0. -43.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#17
t1modB#1
 0. -56.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#18
t1modB#1
 0. -68.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#19
t1modB#1
 0. -81.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#20
t1modB#1
 0. -93.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#21
t1modB#1
 0. -106.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#22
t1modB#1
 0. -118.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#23
t1modB#1
 0. -131.25 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1stripB#24
t1modB#1
 0. -143.75 0.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
// Copy module type B
//------------------------------------------------------------------------------------
t1modB#2
TOFB1
 -1565. 381. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#3
TOFB1
 -1565. 127. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#4
TOFB1
 -1565. -127. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#5
TOFB1
 -1565. -381. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#6
TOFB1
 -1565. -635. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#7
TOFB1
 -995. 635. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#8
TOFB1
 -995. 381. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#9
TOFB1
 -995. 127. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#10
TOFB1
 -995. -127. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#11
TOFB1
 -995. -381. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#12
TOFB1
 -995. -635. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#13
TOFB1
 995. 635. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#14
TOFB1
 995. 381. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#15
TOFB1
 995. 127. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#16
TOFB1
 995. -127. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#17
TOFB1
 995. -381. -18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#18
TOFB1
 995. -635. -6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#19
TOFB1
 1565. 635. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#20
TOFB1
 1565. 381. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#21
TOFB1
 1565. 127. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#22
TOFB1
 1565. -127. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#23
TOFB1
 1565. -381. 18.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
t1modB#24
TOFB1
 1565. -635. 6.
 1. 0. 0. 0. 1. 0. 0. 0. 1.
//------------------------------------------------------------------------------------
