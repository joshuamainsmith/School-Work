# Joshua Main-Smith
# Project 9 - taskswitch
# CSCD 260
# Spring 2018

.data

	tcb0: .space 124
	tcb1: .space 124
	tid: .space 4
  
	str0: .asciiz "pickle"
	str1: .asciiz "banana"

.text
.globl main

main:
	la $t0, tcb0
	la $t1, tcb1
  
	la $a0, task0
	la $a1, task1
  
	sw $a0, 120($t0)
	sw $a1, 120($t1)
  
	la $a1, tid
 	sw $0, 0($a1)
  
	jal task0

#-- here is task0 --

task0:

	#-- Pair 1 Here --

#	li $v0, 11
#	addi $sp, $sp, -8
#	sw $v0, 0($sp)
#	jal ts
#	add $a0, $0, 'x'
#	sw $a0, 4($sp)
#	jal ts
#	lw $v0, 0($sp)
#	lw $a0, 4($sp)
#	syscall
#	addi $sp, $sp, 8
#	jal ts
	
	addi $t7, $0, 10000   # this loop is a timing loop so the printing
loop0:			     # will not be jammed...
	addi $t7, $t7, -1    # Remove this if you do F10 single step execution
	bgt  $t7, 0, loop0   # to debug your ts.

        add  $t0, $0, $0	# sum = 0
	jal ts
        addi $t1, $0, 10	# multplyr = 10
        
        #-- Pair 2 Here --
        la   $s0, str0		# s0 = &str[0]
        #move $a0, $s0
	#li $v0, 4
	#syscall
	jal ts
beg0:
        lb   $t2, ($s0)		# chr = *s0
        beq  $t2, $0, quit0	# bail out on chr==0
        sub  $t2, $t2, 1#'0'	# chr = chr -'0' make it int
        mult $t0, $t1		# sum = sum*multply
        mflo $t0
        add  $t0, $t0, $t2	# sum = sum + chr
	jal ts
        add  $s0, $s0, 1	# s0++ (advance to next addrs)
        b    beg0
quit0:
	add $a0, $0, $t0
	jal ts
	addi $v0, $0, 1
	syscall	
	j task0

#-- here is task1 --

task1:
	#-- Pair 1 Here --
	
#	li $v0, 1
#	addi $sp, $sp, -8
#	sw $v0, 0($sp)
#	jal ts
#	add $a0, $0, 9
#	sw $a0, 4($sp)
#	jal ts
#	lw $v0, 0($sp)
#	lw $a0, 4($sp)
#	syscall
#	addi $sp, $sp, 8
#	jal ts
	
	addi $t7, $0, 10000   # this loop is a timing loop so the printing
loop1:			     # will not be jammed...
	addi $t7, $t7, -1    # Remove this if you do F10 single step execution
	bgt  $t7, 0, loop1   # to debug your ts.

        add  $t0, $0, $0    # sum = 0
        addi $t1, $0, 10	# multplyr = 10
        
        #-- Pair 2 Here --
        la   $s0, str1		 # s0 = &str[0]
	#move $a0, $s0		
	#li $v0, 4
	#syscall
beg1:
        lb   $t2, ($s0)		# chr = *s0
        beq  $t2, $0, quit1	# bail out on chr==0
	jal ts
        sub  $t2, $t2, 1#'0'    # chr = chr -'0' make it int
        mult $t0, $t1		# sum = sum*multply
	addi $t8, $0, 0
        addi $s5, $t8, 0
	add  $t8, $s5, $s5
        addi $t8, $0, 0
        addi $s5, $t8, 0
	add  $t8, $s5, $s5
        mflo $t0
        add  $t0, $t0, $t2	# sum = sum + chr
        add  $s0, $s0, 1
        b    beg1
quit1:
	add $a0, $0, $t0
	
	jal ts
	
	addi $v0, $0, 1
	jal ts
	syscall
	
	j task1


ts:
	addi $sp, $sp, -4
	
	sw $t0, 0($sp)
	lw $t0, tid
	
	move $a0, $t0
	
	li $v0, 1
	syscall
	
	beq $a0, $0, one
	j zero

one:
	
	
	la $t0, tcb0

	sw $2, 4($t0)
	sw $3, 8($t0)
	sw $4, 12($t0)
	sw $5, 16($t0)
	sw $6, 20($t0)
	sw $7, 24($t0)
	lw $t1, 0($sp)
	sw $t1, 28($t0)
	sw $9, 32($t0)
	sw $10, 36($t0)
	sw $11, 40($t0)
	sw $12, 44($t0)
	sw $13, 48($t0)
	sw $14, 52($t0)
	sw $15, 56($t0)
	sw $16, 60($t0)
	sw $17, 64($t0)
	sw $18, 68($t0)
	sw $19, 72($t0)
	sw $20, 76($t0)
	sw $21, 80($t0)
	sw $22, 84($t0)
	sw $23, 88($t0)
	sw $24, 92($t0)
	sw $25, 96($t0)
	sw $31, 120($t0)

	la $a1, tid
	li $a2, 1
	sw $a2, ($a1)
	la $t0, tcb1

	lw $2, 4($t0)
	lw $3, 8($t0)
	lw $4, 12($t0)
	lw $5, 16($t0)
	lw $6, 20($t0)
	lw $7, 24($t0)
	lw $9, 32($t0)
	lw $10, 36($t0)
	lw $11, 40($t0)
	lw $12, 44($t0)
	lw $13, 48($t0)
	lw $14, 52($t0)
	lw $15, 56($t0)
	lw $16, 60($t0)
	lw $17, 64($t0)
	lw $18, 68($t0)
	lw $19, 72($t0)
	lw $20, 76($t0)
	lw $21, 80($t0)
	lw $22, 84($t0)
	lw $23, 88($t0)
	lw $24, 92($t0)
	lw $25, 96($t0)
	lw $31, 120($t0)

	lw $t0, 28($t0)
	addi $sp, $sp, 4
	jr $ra

zero:
	la $t0, tcb1

	sw $2, 4($t0)
	sw $3, 8($t0)
	sw $4, 12($t0)
	sw $5, 16($t0)
	sw $6, 20($t0)
	sw $7, 24($t0)
	lw $t1, 0($sp)
	sw $t1, 28($t0)
	sw $9, 32($t0)
	sw $10, 36($t0)
	sw $11, 40($t0)
	sw $12, 44($t0)
	sw $13, 48($t0)
	sw $14, 52($t0)
	sw $15, 56($t0)
	sw $16, 60($t0)
	sw $17, 64($t0)
	sw $18, 68($t0)
	sw $19, 72($t0)
	sw $20, 76($t0)
	sw $21, 80($t0)
	sw $22, 84($t0)
	sw $23, 88($t0)
	sw $24, 92($t0)
	sw $25, 96($t0)
	sw $31, 120($t0)
	
	la $a1, tid
	li $a2, 0
	sw $a2, ($a1)
	la $t0, tcb0

	lw $2, 4($t0)
	lw $3, 8($t0)
	lw $4, 12($t0)
	lw $5, 16($t0)
	lw $6, 20($t0)
	lw $7, 24($t0)
	lw $9, 32($t0)
	lw $10, 36($t0)
	lw $11, 40($t0)
	lw $12, 44($t0)
	lw $13, 48($t0)
	lw $14, 52($t0)
	lw $15, 56($t0)
	lw $16, 60($t0)
	lw $17, 64($t0)
	lw $18, 68($t0)
	lw $19, 72($t0)
	lw $20, 76($t0)
	lw $21, 80($t0)
	lw $22, 84($t0)
	lw $23, 88($t0)
	lw $24, 92($t0)
	lw $25, 96($t0)
	lw $31, 120($t0)

	lw $t0, 28($t0)
	addi $sp, $sp, 4
	jr $ra