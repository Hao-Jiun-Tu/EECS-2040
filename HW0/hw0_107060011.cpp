#include <iostream>
using namespace std;

int main()
{
    int x, y, reg_x, cycle_leng, max_cycle;
    max_cycle = cycle_leng = 0;
    while(cin >> x >> y){
        while(x < y){
            reg_x = x;
            while(reg_x != 1){
                if(reg_x % 2)
                    reg_x = 3 * reg_x + 1;
                else
                    reg_x = reg_x / 2;
                cycle_leng++;
            }
            cycle_leng++;
            x++;
            if(max_cycle < cycle_leng)
                max_cycle = cycle_leng;
            cycle_leng = 0;
        }
        cout << max_cycle << endl;
        max_cycle = 0;
    }

    return 0;
}
