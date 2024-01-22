//
//  main.cpp
//  HelloWorld
//
//  Created by Eric Tarr on 1/18/24.
//

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {

    // Numerical data types: int, float(32), double(64)
    int x;  // declare
    x = 5; // define
    
    int y = 10; // declare and define in same line
    float z = 10.0f; // 10.f
    double a = 10.0;
    
    char b = 'b';
    string c = "Hello World!";
    
    // Primative Array
    float d[4] = {0.0f};

    int w = x++; // "x++" means increment x
    // C++ loops
    // for i = 1:10
    //
    // end
    for (int i = 0 ; i < 4 ; i++)
    {
        d[i] = 100 + i;
        
    }
    
    
    float m[2][3] = {0.f};
    
    vector<float> f {1.f, 2.f, 3.f};
    
    
    //arr = [5 ; 5; 5];
    
    // insert code here...
    cout << x << endl;
    cout << y << endl;
    cout << z << endl;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;
    cout << f.at(0) << endl;
    cout << f[1] << endl;
    cout << f.at(3) << endl;
    return 0;
}
