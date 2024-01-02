#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <iomanip>
#include <vector>
#include <sstream>
using namespace std;

struct s
{
    string val;
    s * next;
};

class t
{
    private:
        s * top;

    public:
        t()
        {
            top = nullptr;
        }
        bool empty()
        {
            return (top==nullptr);
        }

        s * gettop()
        {
            return top;
        }

        void push(string str)
        {
            s * temp = new s;
            temp->val = str;
            temp->next = top;
            top = temp;
        }

        void pop()
        {
            s * temp = top;
            top = temp->next;
            delete temp;
        }

        int priority(string x)
        {
            if(x == "^")
                return 3;
            else if(x == "*"|| x == "/")
                return 2;
            else if (x == "+"||x == "-")
                return 1;
            else
                return -1;
        }

        string evalPost(string exp1)
        {
            stringstream s2(exp1);
            string exp ="";
            while(s2 >> exp)
            {
                if(exp =="^"){
                    ostringstream S;
                    S.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    S << fixed << (pow(val2, val1));
                    push(S.str());
                    cout << top->val << endl;
                }
                else if(exp == "*"){
                    ostringstream T;
                    T.precision(8);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    T << fixed << (val2 * val1);
                    push(T.str());
                    cout << top->val << endl;
                }
                else if(exp == "/"){
                    ostringstream U;
                    U.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    U << fixed << (val2 / val1);
                    push(U.str());
                    cout << top->val << endl;
                }
                else if(exp=="+"){
                    ostringstream V;
                    V.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    V << fixed << (val2 + val1);
                    push(V.str());
                    cout << top->val << endl;
                }
                else if(exp=="-"){
                    ostringstream W;
                    W.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    W << fixed << (val2 - val1);
                    push(W.str());
                    cout << top->val << endl;
                }
                else{
                    push(exp);
                }
            }
            return (top->val);
        }

        string rev(string exp)
        {
            vector<string> vec;
            stringstream s(exp);
            string str = "";
            string newStr = "";
            while(s >> str)
            {
                vec.push_back(str);
            }
            reverse(vec.begin(), vec.end());
            for(int i = 0; i < vec.size(); i++)
            {
                newStr += vec[i] + " ";
            }

            return newStr;
        }

        string evalPre(string exp1)
        {
            stringstream s2(exp1);
            string exp ="";
            while(s2 >> exp)
            {
                if(exp =="^"){
                    ostringstream S;
                    S.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    S << fixed << (pow(val1, val2));
                    push(S.str());
                    cout << top->val << endl;
                }
                else if(exp == "*"){
                    ostringstream T;
                    T.precision(8);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    T << fixed << (val1 * val2);
                    push(T.str());
                    cout << top->val << endl;
                }
                else if(exp == "/"){
                    ostringstream U;
                    U.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    U << fixed << (val1 / val2);
                    push(U.str());
                    cout << top->val << endl;
                }
                else if(exp=="+"){
                    ostringstream V;
                    V.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    V << fixed << (val1 + val2);
                    push(V.str());
                    cout << top->val << endl;
                }
                else if(exp=="-"){
                    ostringstream W;
                    W.precision(10);
                    double val1 = stod(top->val);
                    pop();
                    double val2 = stod(top->val);
                    pop();
                    W << fixed << (val1 - val2);
                    push(W.str());
                    cout << top->val << endl;
                }
                else{
                    push(exp);
                }
            }
            return (top->val);
        }

        string inToPost(string exp1)
        {
            stringstream s2(exp1);
            string exp ="";
            string newstr ="";
            while(s2 >> exp)
            {
                if(exp == "(")
                {
                    push(exp);
                    //cout << top->val << endl;
                }
                else if (exp == ")")
                {
                    while(!empty() && top->val != "(")
                    {
                        newstr+= top->val + " ";
                        pop();
                    }
                    pop();
                }
                else if(exp == "^" || exp == "*" || exp == "/" || exp == "+" || exp == "-")
                {
                    while(!empty() && priority(exp) <= priority(top->val))
                    {
                        newstr+= top->val + " ";
                        pop();
                    }
                    push(exp);
                }
                else
                {
                    newstr += exp + " ";
                    //cout << newstr << endl;
                }
            }
            while(!empty())
            {
                newstr+= top->val + " ";
                pop();
            }
            return newstr;
        }


    bool valid(string &exp1)
    {
        stringstream s2(exp1);
        string exp ="";
        string newstr ="";
        while(s2 >> exp)
            {
            if(exp=="(" || exp == "[" || exp == "{")
                push(exp);
            else if(exp == ")")
            {
                if(empty() || top->val != "(")
                    return false;
                pop();
            }
            else if(exp == "]")
            {
                if(empty() || top->val != "[")
                    return false;
                pop();
            }
            else if(exp == "}")
            {
                if(empty() || top->val != "{")
                    return false;
                pop();
            }
        }
        return empty();
    }
        
};  


#endif