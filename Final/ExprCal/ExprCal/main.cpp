//
//  Expression Calculator Demo
//
//  Using the data structure Stack, convert an infix expression into an postfix
//  expression, and evaluate it.
//  State changes of the stack is shown in the output.
//
//  Created by 杨志飞@CS_HIT.
//  Stu.ID: 1130310217, Class No.: 1336101
//  Copyright (c) 2015年 杨志飞. All rights reserved.
//
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cctype>
const int MAXLENGTH = 10000, MAXSIZE = 100;
using namespace std;
template<class T>
struct Stack{
    //Char Stack indexing from 1 to n
    int top; //top == 0 means the stack is empty
    T elements[MAXLENGTH];
};
struct Operator{
    // +/- signs and +/-(add/minus) operators have different priorities, so we save the priority directly
    char op;
    char priority; // save memory space
    Operator() {}
    Operator(char a, char b): op(a), priority(b) {}
};
ostream& operator <<(ostream& os, Operator o){
    //for the output of Operator
    os << o.op << "[P" << (int)o.priority << "]";
    return os;
}
struct Term{
    char s[MAXSIZE]; //*s == 0: end of expression
    char type; //type = 0:operand, 1:unary operator, 2:dyadic operator
};
Stack<Operator> opstack;
Stack<double> operands;
int step = 0; //it's used to mark which period(convert/evaluate) the programming is running in, so we can output the states
char infix[MAXLENGTH];
Term postfix[MAXSIZE];
template <class T>
void PrintStack(Stack<T>& S){
    cout << "Stack State: ";
    if(S.top == 0) cout << "Empty!";
    else for(int i = 1; i <= S.top; i++) cout << S.elements[i] << " ";
    cout << endl;
}
template<class T>
void MakeNull(Stack<T>& S){
    //Empty Stack S
    S.top = 0;
    memset(S.elements, 0, sizeof(S.elements));
}
template<class T> T Top(Stack<T>& S) {return S.elements[S.top];}
template<class T>
T Pop(Stack<T>& S) {
    //Retrieve the top element of Stack S, return it, and pop it
    T t = S.elements[S.top--];
    cout << (step == 1 ? "[Operator Stack] " : "[Operand Stack] ") << t << " popped." << endl;
    PrintStack(S);
    return t;
}
template<class T>
void Push(Stack<T>& S, T e){
    //Push e onto the top of Stack S
    S.elements[++S.top] = e;
    cout << (step == 1 ? "[Operator Stack] " : "[Operand Stack] ") << e << " pushed." << endl;
    PrintStack(S);
}
template<class T> bool Empty(Stack<T>& S) {return S.top == 0;}
bool isop(char x) {
    //Determines whether x is an operator
    return x == '+' || x == '-' || x == '*' || x == '/' || x == '(' || x == ')';
}
bool isvalid(char x){
    //Determines whether x is a valid character that shouldn't be omitted
    return isdigit(x) || x == '.' || isop(x);
}
void getInfix(char* p){
    //Get the input, and trim it. The input is supposed to be grammatical.
    char c;
    while((c = getchar()) != '\n'){
        //remove invalid/space characters
        if(isvalid(c)) *p++ = c;
    }
    *p = 0;
}
void PrintPostfix(){
    //Print the Postfix Expression
    Term* t = postfix;
    do{
        cout << t->s << " ";
    }while(*((++t)->s));
    cout << endl;
}
void convert(char* p, Term* t, Stack<Operator>& ops){
    //convert infix(p) into postfix(q) using stack ops
    char *q;
    step = 1; //for demo
    //hasop == true at the beginning and when we've just met an operator
    bool hasop = true; //when hasop==true, operator +/- should be unary
    MakeNull(ops);
    do{
        while(hasop && ((*p == '-') || (*p == '+'))){
            Push(ops, Operator(*p++, 3)); //to handle with numbers with +/- signs
        }
        if(isdigit(*p) || *p == '.'){ //some float numbers may not have 0 before '.'.
            t->type = 0;
            q = (t++)->s;
            while(*p && !isop(*p)) *q++ = *p++;
            *q = '\0';
            hasop = false; //next +/- should be add/sub
        }
        //if we meet with an operator
        else if(isop(*p)){ // *p is an operator
            if(*p == ')') {
                while(!Empty(ops) && Top(ops).op != '(') {
                    //brackets have top priority
                    Operator o = Pop(ops);
                    if(o.priority == 3) t->type = 1;
                    else t->type = 2;
                    q = (t++)->s;
                    *q++ = o.op;
                    *q = '\0';
                }
                Pop(ops); //pop the '('
            }
            else {
                Operator op(*p, 1);
                if(*p == '*' || *p == '/') op.priority = 2;
                else if(*p == '(') op.priority = 4;
                while(!Empty(ops) && Top(ops).op != '(' && op.priority <= Top(ops).priority) {
                    //output operators with low priority first
                    Operator o = Pop(ops);
                    if(o.priority == 3) t->type = 1;
                    else t->type = 2;
                    q = (t++)->s;
                    *q++ = o.op;
                    *q = '\0';
                }
                //then push the high priority operator
                Push(ops, op);
                hasop = true; //a signed number is likely to appear next
            }
            ++p; //makes p pointed to the next element to be handled
        }
        cout << "Postfix Expression(under construction):\n";
        PrintPostfix();
    }while(*p);
    while(!Empty(ops)) {
        //put the remaining operators into the postfix expression
        Operator o = Pop(ops);
        if(o.priority == 3) t->type = 1;
        else t->type = 2;
        q = (t++)->s;
        *q++ = o.op;
        *q = '\0';
    } //pop the last operators
    *(t->s) = 0;
}
double evaluate(Term* t, Stack<double> s){
    char* p;
    step = 2;
    do{
        p = t->s;
        if(t->type == 0){
            //Convert character string numbers into a double value
            double operand = 0.;
            if(*p != '.') //calculate the integer part
                do {
                    operand = operand*10 + double(*p - '0');
                } while(isdigit(*++p));
            if(*p == '.') { //calculate the fractional part
                double e = 1.0;
                while(isdigit(*++p)) operand += (e*=0.1)*double(*p - '0');
            }
            //get the final operand and push it into operand stack
            Push(s, operand);
        }
        else{
            //needs calculating and replacing
            cout << "Run into operator " << *p << endl;
            double a, b, c = 0.;
            if(t->type == 2) { //dyadic
                a = Pop(s);
                b = Pop(s);
                cout << b << *p << a <<"=";
                switch(*p){
                    case '+': c = b + a; break;
                    case '-': c = b - a; break;
                    case '*': c = b * a; break;
                    case '/': c = b / a;
                }
            } else { //unary
                a = Pop(s);
                cout << *p << a << "=";
                c = (*p == '+') ? a : -a;
            }
            cout << c << endl;
            Push(s, c);
        }
    }while(*((++t)->s)); //handle the whole expression
    return Pop(s); //the result is the only remaining element in the stack
}
int main() {
    double ans;
    cout << "Please input a valid infix expression:" << endl;
    getInfix(infix);
    cout << "\n============================================="
    <<"\nThe infix expression you input is saved as:\n"
    << infix << "\n\n=============================================\n"
    << "Postfix expression construct process:\n(\"P*\" means \"Priority *\")\n" << endl;
    
    convert(infix, postfix, opstack);
    
    cout << "\n============================================="
    << "\nThe corresponding postfix expression is:\n";
    PrintPostfix();
    cout << endl;
    
    cout << "============================================="
    << "\nEvaluation:" << endl;
    ans = evaluate(postfix, operands);
    cout << "\n=============================================\n"
    << "Result:\n" << infix << " = " << setprecision(16) << ans << endl;
    return 0;
}
/*Test Cases:
 .57025*(3/+-(.6+.8)-4.2*-(3--(.5/.5))+-8/(6+8)--+6)
 .5*(3/(.6+.8)-4.2*(3--.5)+-8--(-6))
 .5*(3/(6+.8)-4.2*(3--.5)+-8-+-6)
 .5*(3/(6+8)-4.2*(3--.5)+-8---6)
 .5*(3/(6+8)-4.2*(3--5)+-8---6)
 0.5*(3/(6+8)-4.2*(3--5)+-8---6)
 1./-(2.3*(2.+-.6666))
 -(1+2)
 +-(1+2)
*/
