
.arm
.global vbaprint
.type   vbaprint STT_FUNC
.text
vbaprint:
   swi 0xFF0000      @!!!!!!! Doesn't work on hardware !!!!!!!
      bx lr 
