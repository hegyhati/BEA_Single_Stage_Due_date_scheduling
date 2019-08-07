set I :=  i1  i2  i3  i4  i5  i6  i7  i8  i9  i10
          i11 i12 i13 i14 i15;

set J := u1 u2 u3 u4;


param pt :  u1    u2    u3    u4 :=
        i1  1.538 .     .     1.194
        i2  1.500 .     .     0.789
        i3  1.607 .     .     0.818
        i4  .     .     1.564 2.143
        i5  .     .     0.736 1.107
        i6  5.263 .     .     3.200
        i7  4.865 .     3.025 3.214
        i8  .     .     1.500 1.440
        i9  .     .     1.869 2.459
        i10 .     1.282 .     .
        i11 .     3.750 .     3.000
        i12 .     6.796 7.000 5.600
        i13 11.25 .     .     6.716
        i14 2.632 .     .     1.527
        i15 5.000 .     .     2.985
        ;

param D :=
  i1  15
  i2  30
  i3  22
  i4  25
  i5  20
  i6  30
  i7  21
  i8  26
  i9  30
  i10 29
  i11 30
  i12 21
  i13 30
  i14 25
  i15 24
  ;

param ru :=
  u1  0.180
  u2  0.175
  u4  0.237
  ;

param sd:=
  [*,*,u1]: i1  i2  i3  i4  i5  i6  i7  i8  i9  i10 i11 i12 i13 i14 i15 :=
        i1  .   0.3 0.0 1.5 0.6 0.5 0.0 1.1 0.0 .   0.5 1.0 0.2 0.8 0.7
        i2  0.2 .   1.3 0.9 2.5 0.2 0.8 2.5 0.4 .   0.6 2.5 0.5 0.2 0.6
        i3  0.5 0.9 .   0.5 0.7 0.4 1.5 0.4 0.9 .   0.2 1.5 0.8 0.0 0.0
        i4  1.1 0.7 0.2 .   0.8 2.0 0.9 0.0 1.3 .   1.5 1.0 1.8 0.6 1.3
        i5  0.5 1.0 0.0 1.3 .   0.5 2.0 1.3 0.9 .   0.4 0.3 2.0 1.0 2.0
        i6  0.2 0.0 1.3 1.0 1.0 .   0.7 1.3 0.8 .   0.7 0.6 0.5 0.7 0.5
        i7  0.9 0.5 0.0 0.0 1.4 0.6 .   4.0 0.5 .   0.5 0.8 0.3 2.0 1.1
        i8  1.5 2.0 0.4 1.3 0.5 0.0 0.7 .   0.9 .   0.4 1.8 0.6 1.5 0.6
        i9  2.5 0.6 0.5 0.8 0.6 1.8 0.6 0.2 .   .   2.0 1.5 2.0 0.6 0.9
        i10 .   .   .   .   .   .   .   .   .   .   1.0 1.3 .   .   .
        i11 0.8 1.0 1.3 0.8 1.1 0.4 2.5 0.9 2.0 0.0 .   0.8 1.0 2.5 1.5
        i12 0.2 0.7 0.6 0.3 0.9 0.3 0.5 0.2 0.4 0.4 0.0 .   2.0 1.1 0.9
        i13 0.9 0.8 1.3 1.1 1.3 0.6 0.4 1.5 0.5 .   0.4 1.8 .   0.0 0.0
        i14 1.8 1.5 2.0 1.5 0.4 2.5 0.5 0.0 1.1 .   0.6 1.5 0.8 .   0.5
        i15 1.5 0.9 1.3 0.9 0.6 0.1 0.2 0.0 0.3 .   1.3 0.5 0.4 0.6 .
  [*,*,u2]: i1  i2  i3  i4  i5  i6  i7  i8  i9  i10 i11 i12 i13 i14 i15 :=
        i1  .   0.3 0.0 1.5 0.6 0.5 0.0 1.1 0.0 .   0.5 1.0 0.2 0.8 0.7
        i2  0.2 .   1.3 0.9 2.5 0.2 0.8 2.5 0.4 .   0.6 2.5 0.5 0.2 0.6
        i3  0.5 0.9 .   0.5 0.7 0.4 1.5 0.4 0.9 .   0.2 1.5 0.8 0.0 0.0
        i4  1.1 0.7 0.2 .   0.8 2.0 0.9 0.0 1.3 .   1.5 1.0 1.8 0.6 1.3
        i5  0.5 1.0 0.0 1.3 .   0.5 2.0 1.3 0.9 .   0.4 0.3 2.0 1.0 2.0
        i6  0.2 0.0 1.3 1.0 1.0 .   0.7 1.3 0.8 .   0.7 0.6 0.5 0.7 0.5
        i7  0.9 0.5 0.0 0.0 1.4 0.6 .   4.0 0.5 .   0.5 0.8 0.3 2.0 1.1
        i8  1.5 2.0 0.4 1.3 0.5 0.0 0.7 .   0.9 .   0.4 1.8 0.6 1.5 0.6
        i9  2.5 0.6 0.5 0.8 0.6 1.8 0.6 0.2 .   .   2.0 1.5 2.0 0.6 0.9
        i10 .   .   .   .   .   .   .   .   .   .   1.0 1.3 .   .   .
        i11 0.8 1.0 1.3 0.8 1.1 0.4 2.5 0.9 2.0 0.0 .   0.8 1.0 2.5 1.5
        i12 0.2 0.7 0.6 0.3 0.9 0.3 0.5 0.2 0.4 0.4 0.0 .   2.0 1.1 0.9
        i13 0.9 0.8 1.3 1.1 1.3 0.6 0.4 1.5 0.5 .   0.4 1.8 .   0.0 0.0
        i14 1.8 1.5 2.0 1.5 0.4 2.5 0.5 0.0 1.1 .   0.6 1.5 0.8 .   0.5
        i15 1.5 0.9 1.3 0.9 0.6 0.1 0.2 0.0 0.3 .   1.3 0.5 0.4 0.6 .
  [*,*,u3]: i1  i2  i3  i4  i5  i6  i7  i8  i9  i10 i11 i12 i13 i14 i15 :=
        i1  .   0.3 0.0 1.5 0.6 0.5 0.0 1.1 0.0 .   0.5 1.0 0.2 0.8 0.7
        i2  0.2 .   1.3 0.9 2.5 0.2 0.8 2.5 0.4 .   0.6 2.5 0.5 0.2 0.6
        i3  0.5 0.9 .   0.5 0.7 0.4 1.5 0.4 0.9 .   0.2 1.5 0.8 0.0 0.0
        i4  1.1 0.7 0.2 .   0.8 2.0 0.9 0.0 1.3 .   1.5 1.0 1.8 0.6 1.3
        i5  0.5 1.0 0.0 1.3 .   0.5 2.0 1.3 0.9 .   0.4 0.3 2.0 1.0 2.0
        i6  0.2 0.0 1.3 1.0 1.0 .   0.7 1.3 0.8 .   0.7 0.6 0.5 0.7 0.5
        i7  0.9 0.5 0.0 0.0 1.4 0.6 .   4.0 0.5 .   0.5 0.8 0.3 2.0 1.1
        i8  1.5 2.0 0.4 1.3 0.5 0.0 0.7 .   0.9 .   0.4 1.8 0.6 1.5 0.6
        i9  2.5 0.6 0.5 0.8 0.6 1.8 0.6 0.2 .   .   2.0 1.5 2.0 0.6 0.9
        i10 .   .   .   .   .   .   .   .   .   .   1.0 1.3 .   .   .
        i11 0.8 1.0 1.3 0.8 1.1 0.4 2.5 0.9 2.0 0.0 .   0.8 1.0 2.5 1.5
        i12 0.2 0.7 0.6 0.3 0.9 0.3 0.5 0.2 0.4 0.4 0.0 .   2.0 1.1 0.9
        i13 0.9 0.8 1.3 1.1 1.3 0.6 0.4 1.5 0.5 .   0.4 1.8 .   0.0 0.0
        i14 1.8 1.5 2.0 1.5 0.4 2.5 0.5 0.0 1.1 .   0.6 1.5 0.8 .   0.5
        i15 1.5 0.9 1.3 0.9 0.6 0.1 0.2 0.0 0.3 .   1.3 0.5 0.4 0.6 .
  [*,*,u4]: i1  i2  i3  i4  i5  i6  i7  i8  i9  i10 i11 i12 i13 i14 i15 :=
        i1  .   0.3 0.0 1.5 0.6 0.5 0.0 1.1 0.0 .   0.5 1.0 0.2 0.8 0.7
        i2  0.2 .   1.3 0.9 2.5 0.2 0.8 2.5 0.4 .   0.6 2.5 0.5 0.2 0.6
        i3  0.5 0.9 .   0.5 0.7 0.4 1.5 0.4 0.9 .   0.2 1.5 0.8 0.0 0.0
        i4  1.1 0.7 0.2 .   0.8 2.0 0.9 0.0 1.3 .   1.5 1.0 1.8 0.6 1.3
        i5  0.5 1.0 0.0 1.3 .   0.5 2.0 1.3 0.9 .   0.4 0.3 2.0 1.0 2.0
        i6  0.2 0.0 1.3 1.0 1.0 .   0.7 1.3 0.8 .   0.7 0.6 0.5 0.7 0.5
        i7  0.9 0.5 0.0 0.0 1.4 0.6 .   4.0 0.5 .   0.5 0.8 0.3 2.0 1.1
        i8  1.5 2.0 0.4 1.3 0.5 0.0 0.7 .   0.9 .   0.4 1.8 0.6 1.5 0.6
        i9  2.5 0.6 0.5 0.8 0.6 1.8 0.6 0.2 .   .   2.0 1.5 2.0 0.6 0.9
        i10 .   .   .   .   .   .   .   .   .   .   1.0 1.3 .   .   .
        i11 0.8 1.0 1.3 0.8 1.1 0.4 2.5 0.9 2.0 0.0 .   0.8 1.0 2.5 1.5
        i12 0.2 0.7 0.6 0.3 0.9 0.3 0.5 0.2 0.4 0.4 0.0 .   2.0 1.1 0.9
        i13 0.9 0.8 1.3 1.1 1.3 0.6 0.4 1.5 0.5 .   0.4 1.8 .   0.0 0.0
        i14 1.8 1.5 2.0 1.5 0.4 2.5 0.5 0.0 1.1 .   0.6 1.5 0.8 .   0.5
        i15 1.5 0.9 1.3 0.9 0.6 0.1 0.2 0.0 0.3 .   1.3 0.5 0.4 0.6 .
  ;



param alpha :=
  i1  1
  i2  1
  i3  1
  i4  1
  i5  1
  i6  1
  i7  1
  i8  1
  i9  1
  i10 1
  i11 1
  i12 1
  i13 1
  i14 1
  i15 1
  ;

param beta :=
  i1  5
  i2  5
  i3  5
  i4  5
  i5  5
  i6  5
  i7  5
  i8  5
  i9  5
  i10 5
  i11 5
  i12 5
  i13 5
  i14 5
  i15 5
  ;
