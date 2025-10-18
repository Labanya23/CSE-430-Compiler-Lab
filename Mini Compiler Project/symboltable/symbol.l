%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TYPE_COMMENT 0
#define TYPE_STRING_CONST 1
#define TYPE_KEYWORD 2
#define TYPE_IDENTIFIER 3
#define TYPE_UNOP 4
#define TYPE_ARITHOP 5
#define TYPE_RELOP 6
#define TYPE_LOGOP 7
#define TYPE_DIGIT 8
#define TYPE_ASOP 9
#define TYPE_OPBRACK 10
#define TYPE_CLOSEBRACK 11
#define INIT 9999999

FILE *yyin, *yyout;
int line_number = 0;
int sym_table_length = 0;
int scope_level = 0;
int dtype = 0;
int declaration = 0;
char curr_dtype[20];
char curr_identifier[20];

// Struct for symbol table
struct sym_table {
    char name[20];
    char value[50];
    int line_number[10];
    int count;
    int global;
    int scope_level;
    char dtype[20];
    int var_value;
} table[100];

// Function prototypes (fix implicit declaration warnings)
int installID(int type, char* temp_yytext);
void updateValue(int val, char *curr_identifier);
void syntaxError();
%}

%%

\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/|\/\/.* { ; }  // Comments
\".*\" { fprintf(yyout,"%s",yytext); installID(TYPE_STRING_CONST, yytext); }

bool|char|float|short|unsigned|int|long|void { 
    fprintf(yyout,"%s",yytext); 
    installID(TYPE_KEYWORD, yytext);
    dtype=1;
    strcpy(curr_dtype, yytext);
}

asm|else|new|this|auto|enum|operator|throw|explicit|private|true|break|export|protected|try|case|extern|public|typedef|catch|false|register|typeid|reinterpret_cast|typename|class|for|return|union|const|friend|const_cast|goto|signed|using|continue|if|sizeof|virtual|default|inline|static|delete|static_cast|volatile|do|struct|wchar_t|mutable|switch|while|dynamic_cast|namespace|template|global { 
    fprintf(yyout,"%s",yytext); 
    installID(TYPE_KEYWORD, yytext);
}

main { fprintf(yyout,"%s",yytext); installID(TYPE_KEYWORD, yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { 
    if(dtype==1){ declaration=1; } else { dtype=0; declaration=0; }
    fprintf(yyout,"%s",yytext);
    installID(TYPE_IDENTIFIER, yytext);
    strcpy(curr_identifier, yytext);
}

\+|\-|\*|\/ { fprintf(yyout,"%s",yytext); installID(TYPE_ARITHOP, yytext); }
\+\+|-- { fprintf(yyout,"%s",yytext); installID(TYPE_UNOP, yytext); }
\(|\[|\{ { fprintf(yyout,"%s",yytext); installID(TYPE_OPBRACK, yytext); if(yytext[0]=='{') scope_level++; }
\)|\]|\} { fprintf(yyout,"%s",yytext); installID(TYPE_CLOSEBRACK, yytext); if(yytext[0]=='}') scope_level--; }

= { fprintf(yyout,"%s",yytext); installID(TYPE_ASOP, yytext); }
==|<=|>=|<|> { fprintf(yyout,"%s",yytext); installID(TYPE_RELOP, yytext); }
&&|\|\||!= { fprintf(yyout,"%s",yytext); installID(TYPE_LOGOP, yytext); }

[0-9][a-zA-Z_]+ { syntaxError(); }
[0-9]+(\.[0-9]+)? { 
    fprintf(yyout,"%s",yytext); 
    installID(TYPE_DIGIT, yytext); 
    if(declaration==1){ updateValue(atoi(yytext), curr_identifier); }
}

\n { ++line_number; fprintf(yyout,"%s",yytext); declaration=0; dtype=0; }
. { fprintf(yyout,"%s",yytext); }

%%

// Function implementations
void updateValue(int val,char *curr_identifier) {
    int flag=0;
    int row_num;
    for(int i=0;i<100;i++) {
        if(!strcmp(table[i].value,curr_identifier) && table[i].scope_level==scope_level) {
            flag=1;
            row_num=i;
        }
    }
    if(flag==1) {
        table[row_num].var_value=val;
    } else {
        printf("ERROR: variable %s not found at line %d\n", curr_identifier, line_number);
    }
}

int installID (int type, char* temp_yytext) {
    int flag=0;
    int row_num;
    int var_scope;
    switch (type) {
        case TYPE_STRING_CONST: printf("<STRING CONST,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_KEYWORD: printf("<KEYWORD,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_IDENTIFIER:
            for(int i=0;i<100;i++) {
                if(!strcmp(table[i].value,temp_yytext)) { flag=1; row_num=i; var_scope=table[i].scope_level; }
            }
            if(flag==0) {
                strcpy(table[sym_table_length].name, "IDENTIFIER");		
                strcpy(table[sym_table_length].value, temp_yytext);
                table[sym_table_length].line_number[0] = line_number;
                table[sym_table_length].count=1;
                table[sym_table_length].scope_level=scope_level;
                strcpy(table[sym_table_length].dtype,curr_dtype);
                table[sym_table_length].var_value=INIT;
                sym_table_length++;
                printf("<IDENTIFIER,%s,%d>\n", temp_yytext, line_number);
            } else {
                if(scope_level==var_scope)
                    table[row_num].line_number[++table[row_num].count]=line_number;
                else if(declaration==1) {
                    strcpy(table[sym_table_length].name, "IDENTIFIER");		
                    strcpy(table[sym_table_length].value, temp_yytext);
                    table[sym_table_length].line_number[0] = line_number;
                    table[sym_table_length].count=1;
                    table[sym_table_length].scope_level=scope_level;
                    strcpy(table[sym_table_length].dtype,curr_dtype);
                    table[sym_table_length].var_value=INIT;
                    sym_table_length++;
                    printf("<IDENTIFIER,%s,%d>\n", temp_yytext, line_number);
                } else
                    table[row_num].line_number[++table[row_num].count]=line_number;
            }
            break;
        case TYPE_UNOP: printf("<UNOP,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_ARITHOP: printf("<ARITHOP,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_RELOP: printf("<RELOP,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_LOGOP: printf("<LOGOP,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_DIGIT: printf("<DIGIT,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_ASOP: printf("<ASOP,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_OPBRACK: printf("<OPBRACK,%s,%d>\n", temp_yytext, line_number); break;
        case TYPE_CLOSEBRACK: printf("<CLOSEBRACK,%s,%d>\n", temp_yytext, line_number); break;
    }
    return 0;
}

void syntaxError() {
    printf("Syntax Error at line %d\n", line_number);
}

int main(int argc, char *argv[]) {
    sym_table_length = 0;
    line_number = 1;
    if(argc<2){ printf("Usage: %s <inputfile>\n", argv[0]); return 1; }
    yyin = fopen(argv[1],"r");
    yyout = fopen("OUT.c","w");
    yylex();
    fclose(yyout);

    // Print Symbol Table
    printf("\nTOKEN#\tDATA TYPE\tTOKEN_TYPE\tTOKEN_VALUE\tLINE of CODE\tSCOPE\tVALUE\n");
    for(int i=0;i<sym_table_length;i++){
        printf("%d\t%s\t%s\t%s\t", i+1, table[i].dtype, table[i].name, table[i].value);
        for(int j=0;j<10;j++) if(table[i].line_number[j]!=0) printf("%d ", table[i].line_number[j]);
        printf("\t%d\t%d\n", table[i].scope_level, table[i].var_value);
    }

    return 0;
}

int yywrap() { return 1; }
