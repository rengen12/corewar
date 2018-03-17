#deassembler par msa 1.8, made by joe
.name "4 cmd"
.comment "1"
label00:
	ld 		%4294967295, r3
	sti		r3, %0, %0
	ld		-525, r2
	
	sti		r2, %20, %20

	 #live    %1      		
	 #ldi	10, r2, r1

#label01:
	#zjmp	%10
	#and		r1, r2,r3
	#live	%1
	#live	%1
	#aff		r3