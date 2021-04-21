# Joshua Main-Smith
# Project 6 - Recursion
# CSCD 260
# Spring 2018

.data 
	prompt: .asciiz "Enter Value: "
	result: .asciiz "\nThe result is: "
	quest: .asciiz "\nPress 0 to quit, anything else to continue "
	answer: .word 0
	num: .word 0
	
.text
.globl main

main:
	
	# Prompt message
	li $v0, 4
	la $a0, prompt
	syscall
	
	# Take user input
	li $v0, 5
	syscall
	
	# Recursion
	jal rec
	
	# Store result from rec to num
	sw $v0, num
	
	# result message
	li $v0, 4
	la $a0, result
	syscall
	
	# Display int
	li $v0, 1
	lw $a0, num
	syscall
	
	# Quest message
	li $v0, 4
	la $a0, quest
	syscall
	
	# Take user input
	li $v0, 5
	syscall
	
	# Move result to temp
	move $t0, $v0
	
	# Decision to quit program or continue
	bne $t0, $zero, main
	j end
	
	
rec:
	
	# Add to the stack
	addi $sp, $sp, -8
	
	# Store return address and s0
	sw $ra, 0($sp)
	sw $v0, 4($sp)
	
	# When v0 is finished, go to recdone
	beq $v0, 0, recDone
		
	# Decrement
	addi $v0, $v0, -1
	
	# Recursion
	jal rec
	
	
	
recDone:
	# Load return address and s0
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	
	# Recursive add
	add $v0, $v0, $s0
	
	# Restore the stack
	addu $sp, $sp, 8
	jr $ra	
end:
	# End program
	li $v0,10
	syscall
	
