#test de l'automate de la section .data ce commentaitre doit être saute
#test
.set noreorder
#.set doit etre ignore

.data
    .space 10 , 20
#doit detecter que lon se trouve dans .data
.bss
    .space 12
a:    .space 42
.data
    .asciiz "salut" ,"\"vous\"" #gestion des \" ou pas
    .word a
    .word -1
    .byte 12 ,23
.text
    ADD $at,$gp,$t3
#.data