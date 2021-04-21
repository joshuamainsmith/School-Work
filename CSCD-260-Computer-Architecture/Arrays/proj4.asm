.data
	copy0: .space 80
	copy1: .space 80
	array: .word 33, 67, 34, -67, 0, 45, 56, 23, 5, 567, 8, 2, 45, 657, 34, 24, 2, 7 #.space?
	od: .asciiz "\nOdd total is: "
	ev: .asciiz "\nEven total is: "
	c0mess: .asciiz "\nCopy0["
	cmess: .asciiz "] = "
	c1mess: .asciiz "\nCopy1["
	comma: .asciiz ", "
	
.text
.globl main
main:
	
Loop:
	# $t2 = array[i]
	lw $t2, array($t0)
	
	# Using $t0 as incrementer
	addi $t0, $t0, 4
	
	# AND t2 with 0x01. 0 == even. 1 == odd. Store in t4
	andi $t4, $t2, 0x01
	
	# If t4 == 0, goto even
	beq $t4, 0, even
	
	# Else, t4 is odd
	
	# Store odd integers into copy1[i]
	sw $t2, copy1($t7)
	
	# Incrementing through copy1[i]
	addi $t7, $t7, 4
	
	# Storing odd addition in $t1
	add $t1, $t1, $t2
	
	#If at end of array, go to end (hardcoded)
	beq $t0, 72, end
	
	#If t4 is odd, goto loop
	beq $t4, 1, Loop
even:
	# Store even integers into copy0[i]
	sw $t2, copy0($t3)
	
	#Incrementing through copy0[i]
	addi $t3, $t3, 4
	
	# Storing even addition in $t6
	add $t6, $t6, $t2
	
	# If $t0 != 72, goto Loop
	bne $t0, 72, Loop
	
end:
	## Clearing registers
	addi $t4, $zero, 0
	addi $t9, $zero, 0
	addi $t8, $zero, 0
PrintE:
	# Loading even integers into t9
	lw $t9, copy0($t8)

	#Display even message
	li $v0, 4
	la $a0, c0mess
	syscall
	
	# Printing integer copy0[t8]
	li $v0, 1
	addi $a0, $t4, 0
	syscall
	
	#Display even total message ] =
	li $v0, 4
	la $a0, cmess
	syscall
	
	# Printing integer copy0[t8] = t9
	li $v0, 1
	addi $a0, $t9, 0
	syscall
	
	#Display comma 
	li $v0, 4
	la $a0, comma
	syscall
	
	# Used to display index in the array
	addi $t4, $t4, 1
	
	# Iterate through copy0[i]	
	addi $t8, $t8, 4
	bne $t8, $t3, PrintE
	
	#Display even total message
	li $v0, 4
	la $a0, ev
	syscall
	
	# Printing integer
	li $v0, 1
	addi $a0, $t6, 0
	syscall
	
	## Do not use t1 or t6
	addi $t4, $zero, 0
	addi $t9, $zero, 0
	addi $t8, $zero, 0
PrintO:
	lw $t9, copy1($t8)
	
	#Display odd message
	li $v0, 4
	la $a0, c1mess
	syscall
	
	# Printing integer copy1[t4]
	li $v0, 1
	addi $a0, $t4, 0
	syscall
	
	#Display even total message ] =
	li $v0, 4
	la $a0, cmess
	syscall
	
	# Printing integer copy0[t8] = t9
	li $v0, 1
	addi $a0, $t9, 0
	syscall
	
	#Display comma 
	li $v0, 4
	la $a0, comma
	syscall
	
	# Used to display index
	addi $t4, $t4, 1
	
	# Iterate through array
	addi $t8, $t8, 4
	
	bne $t8, $t7, PrintO
	
	#Display odd total message
	li $v0, 4
	la $a0, od
	syscall
	
	# Printing integer
	li $v0, 1
	addi $a0, $t1, 0
	syscall
	
	# Quitting program
	li $v0,10
	syscall
	
