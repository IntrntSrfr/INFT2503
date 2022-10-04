#include <iostream>

int main(){
        const int length = 5;
        int low, mid, high;
        low = mid = high = 0;

        std::cout << "You will enter"  << length <<  "temperatures" << std::endl;

        for(int i = 0; i < length; i++){

                std::cout << "Temperature no. " << i+1 << ":" ;
                int c = 0;
                std::cin >> c;

                if(c > 20) high++;
                else if(c > 9) mid++;
                else low++;
        }

        std::cout << "Temps below 10: " << low << std::endl;
        std::cout << "Temps between 10 and 20: " << mid << std::endl;
        std::cout << "Temps above 20: " << high << std::endl;

        return 0;
}
