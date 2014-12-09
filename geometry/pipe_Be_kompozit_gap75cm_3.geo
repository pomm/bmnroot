//  description of shape PCON:
//  - material
//  - number of points
//  - azimuthal angle from xxx to yyy   [deg]
//  - point 1: z  inner-radius  outer-radius [mm]
//  - ...
//  - point n
//----------------------------------------------------------
pipe1cave
cave
PCON
vacuum
10
0. 360.
-100.   0. 25.5
25.     0. 25.5
35.     0. 130.6
188.26  0. 130.6
197.49  0. 50.1
199.9   0. 10.6
450.25  0. 10.6
622.    0. 13.0 // 15.8
778.    0. 13.0 //  17.8
1522.   0. 13.0 //  17.8
0. 0. 0.
1.  0.  0.  0.  1.  0.  0.  0.  1.
//**********************************
pipe1
pipe1cave
PCON
beryllium
6
0. 360.
 -50.    25.   25.5
  25.    25.   25.5
  35.   130.   130.5 
 187.76 130.   130.5
 187.76 110.   130.5
 188.26 110.11 130.5
0. 0. 0.
1.  0.  0.  0.  1.  0.  0.  0.  1
//

pipevac1
pipe1cave
PCON
vacuum
7
0. 360.
 -50.     0.    25.
  25.     0.    25.
  35.     0.   130.
 187.75   0.   130.
 187.75   0.   110.
 197.49   0.    50.
 200.     0.     0.
0. 0. 0.
1.  0.  0.  0. 1.  0.  0. 0. 1
//

pipe12
pipe1cave
SPHE
beryllium
 500.    500.5
   1.145  12.708
   0.    360.
0. 0. -300.
1.  0.  0.  0. 1.  0.  0. 0. 1
//

pipe13
pipe1cave
PCON
beryllium
8
0. 360.
 199.9   9.5   9.99
 200.4   9.5  10.
 230.    9.5  10.
 230.    9.5  10.5
 240.    9.5  10.5
 240.    9.5  10.
 450.25  9.5  10.
1522.   12.5  13.0
0. 0. 0.
1.  0.  0.  0.  1.  0.  0.  0.  1
//