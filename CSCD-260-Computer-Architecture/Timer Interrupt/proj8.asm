# Joshua Main-Smith
# Project 8 - Interrupt
# CSCD 260
# Spring 2018


.text
.globl main

main:
	mfc0 $t0, $12
	ori $t0, $t0, 0xff01 # enable interrupt
	mtc0 $t0, $12
	li $t0, 10 # compare register value
	mtc0 $t0, $11 #
	mtc0 $zero, $9 # init counter
	# interrupt occurs when $9 == $11
	xor $a0, $a0, $a0

again:
	addi $a0, $a0, 1
	li $v0, 1
	syscall
	
	xor $t0, $t0, $t0
	jal wait
	j again
	jr $ra
wait:
	addi $t0, $t0, 1
	bne $t0, 2000, wait
	
	jr $ra
.kdata
	temp: .space 16
.ktext 0x80000180
	
timer_handler:
	la $k0, temp
	sw $a0, 0($k0)
	sw $v0, 4($k0)
	sw $t0, 8($k0)
	sw $t1,12($k0)
	addi $a0, $0, 0x30
	lui $t0,0xffff #ffff0000

waitloop:
	lw $t1,8($t0) #control
	andi $t1,$t1,0x0001
	beq $t1,$0,waitloop
	sw $a0,12($t0) #data
	mtc0 $zero, $9
	lw $a0, 0($k0)
	lw $v0, 4($k0)
	lw $t0, 8($k0)
	lw $t1,12($k0)
	mtc0 $0, $13 # Clear Cause register
	mfc0 $k0, $12 # Set Status register
	ori $k0, 0x1 # Interrupts enabled
	mtc0 $k0, $12
	eret
