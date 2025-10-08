%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *yyin;

// List of 32 C keywords
char *keywords[] = {
    "auto","break","case","char","const","continue","default","do",
    "double","else","enum","extern","float","for","goto","if",
    "inline","int","long","register","restrict","return","short",
    "signed","sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while"
};

int is_keyword(char *str) {
    for(int i = 0; i < 32; i++) {
        if(strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
%}

%option noyywrap

%%

[ \t]+                ;  

\n                    { yylineno++; }

"//".*                { printf("%d %s comment\n", yylineno, yytext); }

"("|")"|"{"|"}"|"["|"]"   { printf("%d %s parenthesis\n", yylineno, yytext); }

";"|":"|","                { printf("%d %s punctuation\n", yylineno, yytext); }

"=="|"!="|">="|"<="        { printf("%d %s logical_op\n", yylineno, yytext); }
">"|"<"                    { printf("%d %s logical_op\n", yylineno, yytext); }

"+"|"-"|"*"|"/"            { printf("%d %s arithmetic_op\n", yylineno, yytext); }

"="                         { printf("%d %s assign_op\n", yylineno, yytext); }

[0-9]+                      { printf("%d %s constant\n", yylineno, yytext); }

[a-zA-Z_][a-zA-Z0-9_]*      {
                               if(is_keyword(yytext))
                                   printf("%d %s keyword\n", yylineno, yytext);
                               else
                                   printf("%d %s identifier\n", yylineno, yytext);
                             }

.                           ;  

%%

int main(int argc, char *argv[]) {
    if(argc > 1) {
        yyin = fopen(argv[1], "r");
        if(!yyin) {
            perror("Error opening file");
            return 1;
        }
    } else {
        printf("Enter C code (Ctrl+D to finish):\n");
        yyin = stdin;
    }

    yylineno = 1;
    yylex();

    if(yyin != stdin) fclose(yyin);
    return 0;
}
