#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BADKEY -1
typedef struct
{
    char *key;
    char *op_key;
    int val;
} t_symstruct;
typedef struct
{
    char *key;
    int val;
} t_symstruct2;

static t_symstruct lookuptable[] = {
    // A TABLE THAT CONTAINS ALL THE OPCODES AND THEIR GIVEN "ID"
    {"add", "0000000000000001", 1},
    {"sub", "0000000000000010", 2},
    {"addi", "0000000000000011", 3},
    {"mul", "0000000000000100", 4},
    {"lw", "0000000000000101", 5},
    {"sw", "0000000000000110", 6},
    {"beq", "0000000000000111", 7},
    {"bne", "0000000000001000", 8},
    {"j", "0000000000001001", 9},
    {"exit", "0000000000001010", 10}

};
static t_symstruct2 lookuptable2[] = {
    {"$R0", 512},
    {"$R1", 513},
    {"$R2", 514},
    {"$R3", 515},
    {"$R4", 516},
    {"$R5", 517},
    {"$R6", 518},
    {"$R7", 519},
    {"$R8", 520},
    {"$R9", 521},
    {"$R10", 522},
    {"$R11", 523},
    {"$R12", 524},
    {"$R13", 525},
    {"$R14", 526},
    {"$R15", 527},

};
#define NKEYS (sizeof(lookuptable) / sizeof(t_symstruct))
#define NREGISTERS (sizeof(lookuptable2) / sizeof(t_symstruct2))
int keyfromstring(char *key)
{
    int i;
    for (i = 0; i < NKEYS; i++)
    {
        t_symstruct *sym = (lookuptable + i);
        if (strcmp(sym->key, key) == 0)
            return sym->val;
    }
    return BADKEY;
}

int keyfromstring2(char *key)
{
    int i;
    for (i = 0; i < NREGISTERS; i++)
    {
        t_symstruct2 *sym = (lookuptable2 + i);
        if (strcmp(sym->key, key) == 0)
            return sym->val;
    }
    return BADKEY;
}
char *opkeyfromstring(char *key)
{
    int i;
    for (i = 0; i < NKEYS; i++)
    {
        t_symstruct *sym = (lookuptable + i);
        if (strcmp(sym->key, key) == 0)
            return sym->op_key;
    }
    return NULL;
}
//line_to_opkey
char *line_to_opkey(char *line)
{                                                   // this function takes a line (from the .txt file and returns the opkey 'add' , 'sub', etc...)
    char *opkey = (char *)malloc(sizeof(char) * 5); // here i did 5 because the largest opkey is 4 (exit) and u have to add the terminal char
    int i = 0;
    while (line[i] != ' ')
    {
        opkey[i] = line[i];
        i++;
    }
    opkey[i] = '\0'; // we have to add the terminal character
    return opkey;
}

char *line_to_para1(char *line)
{
    // this function takes a line (from the .txt file and returns the first parameter of the instruction (R0,R2,....)
    char *para = (char *)malloc(sizeof(char) * 4); // here i did 4 because the largest para is 3 (R10) and u have to add the terminal char
    int i = 0;
    int cpt = 0;
    while (line[i] != ' ')
    {
        i++;
    }
    i++; // skipping the space
    while (line[i] != ',' && line[i] != '\0')
    {
        para[cpt] = line[i];
        i++;
        cpt++;
    }
    para[cpt] = '\0'; // we have to add the terminal character
    return para;
}

char *line_to_para2(char *line)
{
    // this function takes a line (from the .txt file and returns the first parameter of the instruction (R0,R2,....)
    char *para = (char *)malloc(sizeof(char) * 4); // here i did 4 because the largest para is 3 (R10) and u have to add the terminal char
    int i = 0;
    int cpt = 0;
    while (line[i] != ' ')
    {
        i++;
    }
    i++; // skipping the space
    while (line[i] != ',')
    {
        i++;
    }
    i++; // skipping the first comma
    while (line[i] != ',' && line[i] != '(')
    {
        para[cpt] = line[i];
        i++;
        cpt++;
    }
    para[cpt] = '\0'; // we have to add the terminal character
    return para;
}

char *line_to_para3(char *line)
{
    // this function takes a line (from the .txt file and returns the first parameter of the instruction (R0,R2,....)
    char *para = (char *)malloc(sizeof(char) * 4); // here i did 4 because the largest para is 3 (R10) and u have to add the terminal char
    int i = 0;
    int cpt = 0;
    while (line[i] != ' ')
    {
        i++;
    }
    i++; // skipping the space
    while (line[i] != ',')
    {
        i++;
    }
    i++; // skipping the first comma
    while (line[i] != ',' && line[i] != '(')
    {

        i++;
    }
    i++; // skipping the third comma
    while (line[i] != '\0' && line[i] != ')')
    {
        para[cpt] = line[i];
        cpt++;
        i++;
    }
    para[cpt] = '\0'; // we have to add the terminal character
    return para;
}
char *decimal_to_binary(int n, int bit_nbr)
{
    int c, d, t;
    char *p;

    t = 0;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 1); c >= 0; c--)
    {
        d = n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    *(p + t) = '\0';

    return p;
}
char *decimal_to_binary2(int n, int bit_nbr) // i needed this version because i need to represent negative numbers without C2
{

    int new_n;
    if (n > 0)
    {
        new_n = n;
    }
    else
    {
        new_n = (-1) * n;
    }
    int c, d, t;
    char *p;

    t = 1;
    p = (char *)malloc(bit_nbr + 1); // we add one for the temrinal character

    if (p == NULL)
        exit(1);

    for (c = (bit_nbr - 2); c >= 0; c--)
    {
        d = new_n >> c;

        if (d & 1)
            *(p + t) = 1 + '0';
        else
            *(p + t) = 0 + '0';

        t++;
    }
    if (n > 0)
    {
        *(p) = '0';
    }
    else
    {
        *(p) = '1';
    }
    *(p + t) = '\0';

    return p;
}
int binary_to_int(char *str, int n) // for unsigned numbers
{
    int m = 1;
    int s = 0;
    for (int i = (n - 1); i >= 0; i--)
    {
        if (str[i] == '1')
        {
            s = s + m;
        }
        m = m * 2;
    }
    return s;
}
int binary_to_int2(char *str, int n) // for signed numbers
{
    int m = 1;
    int s = 0;
    for (int i = (n - 1); i > 0; i--)
    {
        if (str[i] == '1')
        {
            s = s + m;
        }
        m = m * 2;
    }
    if (str[0] == '1')
    {
        return ((-1) * s);
    }
    return s;
}
typedef struct memory
{
    char *id;
} memory;

typedef struct instruction
{
    char *inst;
} instruction;
/*-------------------------------------------------------------------------------------------------------------------------------*/
int main() /*-----------------------------------------------------------MAIN-----------------------------------------------------*/
{
    memory ram[1024];
    instruction instructions[512];
    for (int i = 0; i < 1024; i++)
    {
        ram[i].id = (char *)malloc(sizeof(char) * 17);
        memset(ram[i].id, '0', 16);
        ram[i].id[16] = '\0';
    }
    /*
    char *R0 = ram[511].id;
    char *R1 = ram[512].id;
    char *R2 = ram[513].id;
    char *R3 = ram[514].id;
    char *R4 = ram[515].id;
    char *R5 = ram[516].id;
    char *R6 = ram[517].id;
    char *R7 = ram[518].id;
    char *R8 = ram[519].id;
    char *R9 = ram[520].id;
    char *R10 = ram[521].id;
    char *R11 = ram[522].id;
    char *R12 = ram[523].id;
    char *R13 = ram[524].id;
    char *R14 = ram[525].id;
    char *R15 = ram[526].id; // the 16 registers are put in the second half of the memory as specified in the project
    */
    // STAGE 1 REGISTERS
    char *PC; //in the project the registers are 16 bits so i have 16 + terminal char
    char instruction[17];
    instruction[16] = '\0';
    // STAGE 2 REGISTERS
    int function_code;
    char data1[17];
    char data2[17];
    char data22[17];
    data1[16] = '\0';
    data2[16] = '\0';
    data22[16] = '\0';
    char immediate[17];
    int mem_read;
    int mem_write;
    int meme_to_reg;
    int reg_write;

    immediate[16] = '\0';
    char destination_register[5]; // this interstate register will contain which register the destination register
                                  // this interstate register will contain which register the destination register
    //STAGE 3 REGISTERS
    char RS[5]; //the RS register will contain the register for data 1
    char RT[5]; //the RT register will contain the register for data 2
    int alu_src = 0;
    int mem_read2;
    int mem_write2;
    int meme_to_reg2;
    int reg_write2;
    int is_zero;
    char alu_result[17];
    alu_result[16] = '\0';
    char destination_register2[5];
    // STAGE 4 REGISTERS
    int meme_to_reg3;
    int reg_write3;
    char destination_register3[5];
    char alu_result2[17];
    memset(alu_result2, '0', 16);
    alu_result2[16] = '\0';
    int read_data;

    char buffer[42];
    FILE *f = fopen("instructions.txt", "r");
    int nbr_lines = 0;
    while (1)
    {
        fgets(buffer, 42, f);
        instructions[nbr_lines].inst = (char *)malloc(sizeof(char) * 42);
        strcpy(instructions[nbr_lines].inst, strtok(buffer, "\n")); //i used the strok here to delete the new line from the line
        if (feof(f))
        {
            break;
        }
        nbr_lines++;
    } //reading the file

    //getting the first instruction
    strcpy(buffer, instructions[0].inst);
    int i = 0;
    PC = decimal_to_binary(0, 16);
    int done = 0;
    int finished_stage_5 = 0;
    int finished_stage_4 = 0;
    int finished_stage_3 = 0;
    int finished_stage_2 = 0;
    int gonna_jump = 0;
    int jump_location = 0;
    //while ((memcmp(line_to_opkey(instructions[i].inst), "exit", 4)) != 0)
    while (finished_stage_5 == 0 || gonna_jump == 1)
    {
        if (gonna_jump == 1 && finished_stage_5 == 1) // the instructions all finished
        {
            i = jump_location - 1; //means we jumped!
            finished_stage_5 = 0;
            gonna_jump = 0;
        }

        //STAGE 5 (WRITING BACK)
        if ((i - 4) >= (jump_location - 1) && finished_stage_5 == 0)
        {
            finished_stage_5 = 1;
            memcpy(ram[keyfromstring2(destination_register3)].id, alu_result2, 16);

            done = 1;
        }
        //STAGE 4 (MEMORY)
        if ((i - 3) >= (jump_location - 1) && finished_stage_4 == 0)
        {
            finished_stage_4 = 1;
            finished_stage_5 = 0;
            memcpy(destination_register3, destination_register2, 5);
            memcpy(alu_result2, alu_result, 16);
            done = 0;
            if (mem_read2 == 0)
            {
                read_data = 0;
            }
            else
            {

                read_data = binary_to_int2(ram[binary_to_int2(alu_result2, 16)].id, 16);
            }
            meme_to_reg3 = meme_to_reg2;
            reg_write3 = reg_write2;
        }
        //STAGE 3 (EXECUTING)
        if ((i - 2) >= (jump_location - 1) && finished_stage_3 == 0)
        {
            finished_stage_3 = 1;
            finished_stage_4 = 0;
            switch ((keyfromstring(line_to_opkey(instructions[(i - 2)].inst))))
            {
            case 1: // the add instruction
                memcpy(alu_result, decimal_to_binary2((binary_to_int2(data1, 16)) + (binary_to_int2(data2, 16)), 16), 16);
                break;
            case 2: //the sub instruction
                memcpy(alu_result, decimal_to_binary2(binary_to_int2(data1, 16) - binary_to_int2(data2, 16), 16), 16);
                break;
            case 3: // the addi instruction
                memcpy(alu_result, decimal_to_binary2(binary_to_int2(data1, 16) + binary_to_int2(immediate, 16), 16), 16);
                break;
            case 4: // the mul instruction
                memcpy(alu_result, decimal_to_binary2(binary_to_int2(data1, 16) * binary_to_int2(data2, 16), 16), 16);
                break;
            case 5: // the lw instruction
                memcpy(alu_result, ram[(binary_to_int2(immediate, 16)) + binary_to_int2(data1, 16)].id, 16);
                break;

            case 6: // the sw instruction
                memcpy(ram[(binary_to_int2(immediate, 16)) + binary_to_int2(data1, 16)].id, alu_result, 16);
                break;
            case 9:
                jump_location = binary_to_int2(immediate, 16);
                gonna_jump = 1;
                break;
            } //ill add the lw sw beq bnq and j later for now ill just focus on making the sub add addi and mul work
            if (binary_to_int2(alu_result, 16) == 0)
            {
                is_zero = 1;
            }
            else
            {
                is_zero = 0;
            }
            mem_read2 = mem_read;
            mem_write2 = mem_write;
            reg_write2 = reg_write;
            meme_to_reg2 = meme_to_reg;
            memcpy(data22, data2, 16);
            memcpy(destination_register2, destination_register, 5);
        }
        //STAGE 2 (DECODING)
        if ((i - 1) >= (jump_location - 1) && finished_stage_2 == 0) //from 653 to 437
        {
            finished_stage_2 = 1;
            finished_stage_3 = 0;
            function_code = keyfromstring(line_to_opkey(instructions[(i - 1)].inst));
            //printf("%d", function_code);

            switch ((keyfromstring(line_to_opkey(instructions[(i - 1)].inst))))
            {
            case 1: // the add instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para2(instructions[(i - 1)].inst))].id, 16);

                memcpy(data2, ram[keyfromstring2(line_to_para3(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);

                if (keyfromstring2(line_to_para2(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 0;
                mem_read = 0;
                mem_write = 0;
                meme_to_reg = 0;
                reg_write = 1;
                break;
            case 2: //the sub instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para2(instructions[(i - 1)].inst))].id, 16);
                memcpy(data2, ram[keyfromstring2(line_to_para3(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                if (keyfromstring2(line_to_para2(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 0;
                mem_read = 0;
                mem_write = 0;
                meme_to_reg = 0;
                reg_write = 1;

                break;
            case 3: //the addi instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para2(instructions[(i - 1)].inst))].id, 16);
                memcpy(data2, ram[keyfromstring2(line_to_para1(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, decimal_to_binary2(atoi(line_to_para3(instructions[(i - 1)].inst)), 16), 16);
                if (keyfromstring2(line_to_para2(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para1(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 1;
                mem_read = 0;
                mem_write = 0;
                meme_to_reg = 0;
                reg_write = 1;

                break;
            case 4: //the mul instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para2(instructions[(i - 1)].inst))].id, 16);
                memcpy(data2, ram[keyfromstring2(line_to_para3(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                if (keyfromstring2(line_to_para2(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para2(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para3(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 1;
                mem_read = 0;
                mem_write = 0;
                meme_to_reg = 0;
                reg_write = 1;

                break;

            case 5: // the lw instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para3(instructions[(i - 1)].inst))].id, 16);
                memcpy(data2, ram[keyfromstring2(line_to_para1(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, decimal_to_binary2(atoi(line_to_para2(instructions[(i - 1)].inst)), 16), 16);
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para3(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para3(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 1;
                mem_read = 1;
                mem_write = 0;
                meme_to_reg = 1;
                reg_write = 1;

                break;
            case 6: // the sw instruction
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(data1, ram[keyfromstring2(line_to_para3(instructions[(i - 1)].inst))].id, 16);
                memcpy(data2, ram[keyfromstring2(line_to_para1(instructions[(i - 1)].inst))].id, 16);
                memcpy(immediate, opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RS, line_to_para3(instructions[(i - 1)].inst), 4);
                    RS[4] = '\0';
                }
                else
                {
                    memcpy(RS, line_to_para3(instructions[(i - 1)].inst), 3);
                    RS[3] = '\0';
                } // GETTING THE RS REGISTER
                if (keyfromstring2(line_to_para3(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 4);
                    RT[4] = '\0';
                }
                else
                {
                    memcpy(RT, line_to_para1(instructions[(i - 1)].inst), 3);
                    RT[3] = '\0';
                } // GETTING THE RT REGISTER
                alu_src = 1;
                mem_read = 0;
                mem_write = 1;
                meme_to_reg = 0;
                reg_write = 1;
                break;
            case 9:
                function_code = binary_to_int(opkeyfromstring(line_to_opkey(instructions[(i - 1)].inst)), 16);
                memcpy(immediate, decimal_to_binary(atoi((line_to_para1(instructions[(i - 1)].inst))), 16), 16);
                break;
            default:
                break;
            }
            if ((keyfromstring(line_to_opkey(instructions[(i - 1)].inst))) != 9 && (keyfromstring(line_to_opkey(instructions[(i - 1)].inst))) != 10)
            {
                if (keyfromstring2(line_to_para1(instructions[(i - 1)].inst)) > 519)
                {
                    memcpy(destination_register, line_to_para1(instructions[(i - 1)].inst), 4); //here before we do this we have to know if the register is R0 or R10 (contains 2 chars or 3 chars so we know how many to copy)
                    destination_register[4] = '\0';
                }
                else
                {
                    memcpy(destination_register, line_to_para1(instructions[(i - 1)].inst), 3); //here before we do this we have to know if the register is R0 or R10 (contains 2 chars or 3 chars so we know how many to copy)
                    destination_register[3] = '\0';
                }
            }
        }
        //STAGE 1 (FETCHING)

        PC = decimal_to_binary(binary_to_int(PC, 16) + 2, 16);

        if ((i < nbr_lines) && (memcmp(line_to_opkey(instructions[i].inst), "exit", 4)) != 0)
        {
            // printf("stage 1! \n");
            memcpy(instruction, opkeyfromstring(line_to_opkey(instructions[i].inst)), 16);
            finished_stage_2 = 0;
            i++;
        }
        else
        {
            i++;
        }
    }

    printf("the r5 register is %d \n", binary_to_int2(ram[517].id, 16));
    printf("the r6 register is %d \n", binary_to_int2(ram[518].id, 16));
    printf("the r1 register is %d \n", binary_to_int2(ram[513].id, 16));
    //addi $R6,$R2,-10
    //mull $R1,$R6,$R5
    return 0;
}