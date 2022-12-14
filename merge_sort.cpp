#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>

#define MERGE_SORT_INCREASING
 
#if defined MERGE_SORT_INCREASING
#define MERGE_CHECK <=
#elif defined MERGE_SORT_DECREASING
#define MERGE_CHECK >=
#endif

void merge_sort(std::vector<int>&);

std::vector<int> merge(const std::vector<int>&, const std::vector<int>&);

int main()
{
    /*
    * Merge sort
    * Algorithm complexity: O(n*log(n))
    * Credit: SteveStage
    * @steve_stage
    * P.S. to change sort increase/decrease order - change define:
    * MERGE_SORT_INCREASING or MERGE_SORT_DECREASING
    */
    int amount;
    std::vector<int> v;
    std::cout << "Enter amount of numbers: ";
    std::cin >> amount;
    std::cout << "Enter " << amount << " numbers: ";
    for (int i = 0, tmp; i < amount; i++)
    {
        std::cin >> tmp;
        v.push_back(tmp);
    }
    merge_sort(v);
    for (auto i : v)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
    _getch();
    return 0;
}

void merge_sort(std::vector<int>& v)
{
    int size = v.size();
    int lgpw = std::log2(size);
    int size2n = std::pow(2, lgpw);
    int dif = size - size2n;
    std::vector<std::vector<int>> vc;
    std::vector<std::vector<int>> vc_df;
    for (int i = 0; i < size2n; i++)
    {
        vc.push_back({ v[i] });
    }
    for (int i = 0; i < dif; i++)
    {
        vc_df.push_back({ v[i + size2n] });
    }
    for (int i = 1; i <= lgpw; i++) // start merging
    {
        int prsz = std::pow(2, i);
        for (int li = 0; li < std::pow(2, (3-i)); li+=2) // offset
        {
            vc[li] = merge(vc[li], vc[li + 1]);
            vc.erase(std::next(vc.begin(), li + 1));
            li--;
        }
    }
    if (dif > 0)
    {
        int lgdf = std::log2(dif); // maximum number multiply of 2 less than dif
        for (int i = 1; i <= (lgdf + 1); i++) // + 1 for merge multiply of 2 vector and last vector
        {
            for (int ii = 0; ii + 1 < vc_df.size(); ii++)
            {
                vc_df[ii] = merge(vc_df[ii], vc_df[ii + 1]);
                vc_df.erase(std::next(vc_df.begin(), ii+1));
            }
        }
        v = merge(vc[0], vc_df[0]);
    }
    else
        v = vc[0];
}

std::vector<int> merge(const std::vector<int>& v1, const std::vector<int>& v2)
{
    std::vector<int> tt;
    int c1 = 0, c2 = 0; // counters for 1st and 2nd compared vectors
    while (true)
    {
        if (c1 >= v1.size()) // c1 out of bound
        {
            if (c2 >= v2.size()) // c2 out of bound
                break;
            else
            {
                tt.push_back(v2[c2]);
                c2++;
            }
        }
        else
        {
            if (c2 >= v2.size()) // c2 out of bound
            {
                tt.push_back(v1[c1]);
                c1++;
            }
            else
            {
                if (v1[c1] MERGE_CHECK v2[c2])
                {
                    tt.push_back(v1[c1]);
                    c1++;
                }
                else
                {
                    tt.push_back(v2[c2]);
                    c2++;
                }
            }
        }
    }
    return tt;
}