# Test file for "Lab4_SMs"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

# Add tests below
test "Start and dont press the button. Result: State = B0_R PORTB = 0x01"
set smP1_State = start
setPINA  0x00
continue 2
expectPORTB 0x01
checkResult
expect smP1_State 2
checkResult


test "Start and hold button simultaneously. Result: State = B0_P PORTB = 0x01"
set smP1_State = start
setPINA  0x01
continue 2
expectPORTB 0x01
checkResult
expect smP1_State 1
checkResult


test "Start, press and hold button after. Result: State = B1_P PORTB = 0x02"
set smP1_State = start
setPINA  0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x02
checkResult
expect smP1_State 3
checkResult



test "Start, then press button and release. Result: State = B1_R PORTB = 0x02"
set smP1_State = start
setPINA  0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
expectPORTB 0x02
checkResult
expect smP1_State 4
checkResult



test "Start, then press button then press again and hold. Result: State = B0_P PORTB = 0x01"
set smP1_State = start
setPINA  0x00
continue 2
setPINA 0x01
continue 2
setPINA 0x00
continue 2
setPINA 0x01
continue 2
expectPORTB 0x01
checkResult
expect smP1_State 1
checkResult



# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
