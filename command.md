# phone < -- > ESP
## command set
### preset
- http://192.168.0.1/preset/act?no={0..10}

### manual
- http://192.168.0.1/command/joint?d={l,r}&no={0..3}&angle={0..180}
- http://192.168.0.1/command/wheel?d={f,b,l,r}&v=20

# ESP < -- > MEGA
## command set
- byte 로 구성
### preset
```
+-----+------+----+
| 'P' | 0xFF | \n |
+-----+------+----+
```
e.g.) preset 설정 중에 1번
```
+-----+------+----+
| 'P' | 0x01 | \n |
+-----+------+----+
```
### manual
```
M (anual)
├── J (oint)
│   ├── L (eft)
│   │   ├── A (rm)
│   │   ├── D (isc)
│   │   └── N (eck)
│   └── R (ight)
│       ├── A (rm)
│       ├── D (isc)
│       └── N (eck)
└── W (heel)
    ├── D (irection)
    │   ├── B (ackward)
    │   ├── F (orward)
    │   ├── L (eft)
    │   └── R (ight)
    └── T (urn)
        ├── L (eft)
        └── R (ight)
```
e.g.) 메뉴얼, joint 동작 명령, left, angle 180, 180, 180
```
+-----+-----+-----+-----+------+------+------+----+
| 'M' | 'J' | 'A' | 'L' | 0xB4 | 0xB4 | 0xB4 | \n |
+-----+-----+-----+-----+------+------+------+----+
```
e.g.) 메뉴얼, wheel 동작 명령, forward
```
+-----+-----+-----+-----+----+
| 'M' | 'W' | 'D' | 'F' | \n |
+-----+-----+-----+-----+----+
```
