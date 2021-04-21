.data
	prompt: .asciiz "\nEnter an integer: "
	select: .asciiz "\nEnter 0 for add, 1 for subtract: "
	quit: .asciiz "\n0 to quit, anything else to continue "
	result: .asciiz "\nThe result is: "
	
.text
.globl main
main:
	# Clearing $t0
	addi $t0, $t0, 0
	
	#Display
	li $v0, 4 #4 tells computer that string will be called
	la $a0, prompt #displaying "prompt"
	syscall
	
	#Getting input
	li $v0, 5 #Telling computer to input an integer
	syscall
	
	#Store result in $t0
	move $t0, $v0
	
	#Display
	li $v0, 4 #4 tells computer that string will be called
	la $a0, prompt #displaying "prompt"
	syscall
	
	#Getting input
	li $v0, 5 #Telling computer to input an integer
	syscall
	
	#Store result in $t1
	move $t1, $v0 
	
	li $v0, 4 #4 tells computer that string will be called
	la $a0, select #displaying "select"
	syscall
	
	#Getting input
	li $v0, 5 #Telling computer to input an integer
	syscall
	
	#Store result in $t2
	move $t2, $v0 #addi?
	
	# If 0, add. Otherwise subtract
	beq $t2, $zero, adding
	beq $t2, 1, subtract
	
	
adding:	
	#arithmetic
	add $t0, $t0, $t1
	
	#Display
	li $v0, 4
	la $a0, result
	syscall
	
	#Print int
	li $v0, 1 #printing int is 1
	move $a0, $t0
	syscall
	
	
subtract:	
	#Check if addition was selected
	beq $t2, $zero, end
	
	#arithmetic
	sub $t0, $t0, $t1
	
	#Display
	li $v0, 4
	la $a0, result
	syscall
	
	#Print int
	li $v0, 1 #printing int is 1
	move $a0, $t0
	syscall





	
end:
	li $v0, 4 #4 tells computer that string will be called
	la $a0, quit #displaying "prompt"
	syscall
	
	#Getting input
	li $v0, 5 #Telling computer to input an integer
	syscall
	
	#Store result in $t0
	move $t0, $v0
	
	bne $t0, $zero, main
	
	li $v0,10
	syscall
