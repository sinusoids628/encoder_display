# encoder_display
encoder display for alum a lift position
File from SDRobots.com from Double LS7366R Single Quad Encoder Buffer
Tested using UNO and Daido H48 5000 Cts / rev encoder
plan to mod for reset at home flag and single counts display on OLED 
Changed Adafruit OLED ino DIO - pins were in use for encoder

Rev_2_for_1_encoder masks 1 of the encoders but more importantly
corrects the config to not multipy encoder count by 4
