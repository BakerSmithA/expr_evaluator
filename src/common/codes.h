#pragma once

// Stack machine instructions:
//
// |=============|===========|===============================================|
// | Instruction | Code      | Description                                   |
// |=============|===========|===============================================|
// | Push        | 00000000  | Push the 5-bit number to the top of the stack.|
// |             |           | The byte proceeding this code is the number   |
// |             |           | to push to the stack.                         |
// |-------------|-----------|-----------------------------------------------|
// | Add         | 00000001  | Add the two values at the top of the stack.   |
// |-------------|-----------|-----------------------------------------------|
// | Sub         | 00000010  | Subtract the value below the top of the stack |
// |             |           | from the element at the top.                  |
// |-------------|-----------|-----------------------------------------------|
// | Add         | 00000011  | Multiply the two values at the top of the     |
// |             |           | stack.                                        |
// |-------------|-----------|-----------------------------------------------|
// | Div         | 00000100  | Divide the value below the top of the stack   |
// |             |           | from the element at the top.                  |
// |-------------|-----------|-----------------------------------------------|
// | Halt        | 00000101  | Stops the stack machine execution.            |
// |-------------|-----------|-----------------------------------------------|

// Binary codes for each operation.
#define PUSH_CODE 0x00
#define ADD_CODE  0x01
#define SUB_CODE  0x02
#define MULT_CODE 0x03
#define DIV_CODE  0x04
#define HALT_CODE 0x05
