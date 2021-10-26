//
//  main.cpp
//  knapsack
//
//  Created by mndx on 26/10/2021.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

typedef struct table_element {
    bool is_set;
    int val;
} t_elem;

int num_calls = 0;

int can_sum(int n, std::vector<int>& arr, int target_sum, int sum, t_elem** m_table) {

    int result = 0;

    num_calls++;

    if(m_table[sum]->is_set == true) {
        return m_table[sum]->val;
    }
    else {
        int max_val = 0;
        for(int i = 0; i < n; ++i) {
            int sum_o = sum + arr[i];
            if(sum_o != sum) {
                int sum_loc = 0;
                if(target_sum == sum_o) {
                    sum_loc = sum_o;
                    return target_sum;
                }
                else if(sum_o < target_sum) {
                    sum_loc = can_sum(n, arr, target_sum, sum_o, m_table);
                    if(target_sum == sum_loc) {
                        max_val = target_sum;
                        return target_sum;
                    }
                }
                
                if(sum_loc > max_val && sum_loc <= target_sum) {
                    max_val = sum_loc;
                }
            }
            
            if(max_val < sum_o && sum_o <= target_sum) {
                max_val = sum_o;
            }
        }

        m_table[sum]->is_set = true;
        m_table[sum]->val = max_val;
        result = max_val;
    }

    return result;
}

int how_sum(int n, std::vector<int>& arr, int target_sum) {

    t_elem** m_table = new t_elem*[target_sum+1];

    for(int i = 0; i < target_sum + 1; ++i) {
        m_table[i] = new t_elem;
        m_table[i]->is_set = false;
        m_table[i]->val = 0;
    }
    
    int result = can_sum(n, arr, target_sum, 0, m_table);

    return result;
}

int unbounded_knapsack(int k, std::vector<int>& arr) {
    int result = 0;
    int nn = (int) arr.size();
    
    result = how_sum(nn, arr, k);
    
    return result;
}

int main(int argc, char* argv[]) {

    int n = 3; //Number of elements in array
    int k = 119; //Upper bound

    std::vector<int> arr;
    
    //Create input random array
    srand((unsigned) time(NULL));
    for(int i = 0; i < n; ++i) {
        int val = rand() % k + 1;
        arr.push_back(val);
    }
    
    //Compute max sum 
    int max_sum = unbounded_knapsack(k, arr);

    //Print results
    std::cout << "max_sum: " << max_sum << std::endl;
    std::cout << "done" << std::endl;

    return 0;
}
