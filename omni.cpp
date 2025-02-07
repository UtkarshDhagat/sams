#include <iostream>
#include <vector>
void omni(int m,int n,int k,vector<int>forbidden){
    int count=0;
    for (int i=a;i<=b;i++){
        int temp=num;
        int freq[10]={};
    }
    while (temp > 0) {
            int digit = temp % 10;
            digitFrequency[digit]++;
            temp /= 10;
        }
        bool isInvalid = false;
        for (int digit : forbiddenDigits) {
            if (digitFrequency[digit] >= k) {
                isInvalid = true;
                break; 
            }
        }
        if (!isInvalid) validCount++;
    }
    return validCount;  
}



}