/*
Takes an expression to be evaluated and 6 input arrays. Returns sum of evaluated expression based on grouping.
    void evalExpr(string expr, double [] arr1, double [] arr2, double [] arr3, double [] arr4, string [] region, string [] country)
    - expr string is of the form : "a1*a2 + a3/a4" (any combination of variables a1, a2, a3, a4. Operators are +, -, *, /)
    - Arrays arr1, ..., arr4 each contain doubles
    - Array region contains names of continents
    - Array country contains names of countries
    - All arrays have same number of elements (10 million or more)
    expr needs to be applied to elements of arrays (arr1, arr2, arr3, arr4). Then result needs 
    to be grouped (summed up) based on region and country.
    Example: If the expression is "a1 + a2 + a3 + a4" and the 6 arrays are:
    arr1           arr2            arr3            arr4         region        country
    1.0            2.0              3.0             4.0          asia            india
    5.0            6.0              7.0             8.0          europe       france
    9.0           10.0            11.0            12.0         asia           india
    13.0         14.0             15.0           16.0        europe       germany
    17.0          18.0            19.0           20.0        europe       france
    Output of the program would be
    asia       india        52.0
    europe  france      100.0
    europe  germany   58.0
    - You can assume that each input array can be read from a separate file. Expression 
      will be passed as an argument to the program. You can print output on screen.
*/


#include <bits/stdc++.h> 
#include <algorithm> 
#include <regex>

using namespace std;

double applyOperation(double a, double b, char op)
{
    switch(op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

double evaluate(string tokens)
{
    int i;
    stack <double> values;
    stack <char> ops;
     
    for(i = 0; i < tokens.length(); i++)
    {  
        if(tokens[i] == ' ')
            continue;

        else if(isdigit(tokens[i]) || tokens[i]=='.')
        {
            double val = 0.00;
            int flag = 0;
            while(i < tokens.length() && (isdigit(tokens[i]) || tokens[i]=='.'))
            {
                if(tokens[i]=='.')
                {
                    flag=1;
                    i++;
                    continue;
                }
                if(flag)
                {
                    val += (double(tokens[i]-'0')/double(pow(10.00,flag)));
                    flag++;
                    i++;
                }
                else
                {
                    val = (val*10.00) + double(tokens[i]-'0');
                    i++;
                }
            }
             
            values.push(val);
            i--;
        }
         
        else
        {
            while(!ops.empty())
            {
                double val2 = values.top();
                values.pop();
                 
                double val1 = values.top();
                values.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                values.push(applyOperation(val1, val2, op));
            }
            ops.push(tokens[i]);
        }
    }
     
    while(!ops.empty()){
        double val2 = values.top();
        values.pop();
                 
        double val1 = values.top();
        values.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        values.push(applyOperation(val1, val2, op));
    }

    return values.top();
}


void evalExpr(string expr, vector<double> arr1, vector<double> arr2, vector<double> arr3, vector<double> arr4, vector<string> region, vector<string> country)
{
    int n = arr1.size();
    map<pair<string,string>,double> country_value;
    for(int i=0;i<n;i++)
    {
        string expr_sub(expr);
        expr_sub = std::regex_replace(expr_sub, std::regex("a1"), to_string(arr1[i]));
        expr_sub = std::regex_replace(expr_sub, std::regex("a2"), to_string(arr2[i]));
        expr_sub = std::regex_replace(expr_sub, std::regex("a3"), to_string(arr3[i]));
        expr_sub = std::regex_replace(expr_sub, std::regex("a4"), to_string(arr4[i]));
        country_value[make_pair(region[i],country[i])] += evaluate(expr_sub);
    }
    
    for (auto i = country_value.begin(); i
         != country_value.end(); i++) {
        std::cout << i->first.first
                  << "  "
                  << i->first.second
                  << "  "
                  << fixed << setprecision(1)
                  << i->second
                  <<endl;
    }
}

int main() 
{ 
    #ifndef ONLINE_JUDGE 
        freopen("C:/Users/bourb/Desktop/Code/input.txt", "r", stdin); 
        freopen("C:/Users/bourb/Desktop/Code/output.txt", "w", stdout); 
    #endif 
    
    vector<double> arr1,arr2,arr3,arr4;
    vector<string> region,country;
    double x;
    string y;
    while (cin>>x)
    {
        arr1.emplace_back(x);
        cin>>x;
        arr2.emplace_back(x);
        cin>>x;
        arr3.emplace_back(x);
        cin>>x;
        arr4.emplace_back(x);
        cin>>y;
        region.emplace_back(y);
        cin>>y;
        country.emplace_back(y);
    }
    
    string expr = "a1+a2+a3+a4";
    
    evalExpr(expr,arr1,arr2,arr3,arr4,region,country);


}
