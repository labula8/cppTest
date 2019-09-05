#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <vector>

using namespace std;

 

// mostly need to read the linux config files to get system info

 

// ---- get os info ---- //

void getOsInfo()

{

    FILE *fp = fopen("/proc/version", "r");

    if(NULL == fp)

        printf("failed to open version\n");

    char szTest[1000] = {0};

    while(!feof(fp))

    {

        memset(szTest, 0, sizeof(szTest));

        fgets(szTest, sizeof(szTest) - 1, fp); // leave out \n

        printf("%s", szTest);

    }

    fclose(fp);

}
// ---- get cpu info ---- //

void getCpuInfo()

{

    FILE *fp = fopen("/proc/cpuinfo", "r");

    if(NULL == fp)

        printf("failed to open cpuinfo\n");

    char szTest[1000] = {0};

    // read file line by line

    while(!feof(fp))

    {

        memset(szTest, 0, sizeof(szTest));

        fgets(szTest, sizeof(szTest) - 1, fp); // leave out \n

        printf("%s", szTest);

    }

    fclose(fp);

}

 

 

// ---- get memory info ---- //

void getMemoryInfo()

{

    FILE *fp = fopen("/proc/meminfo", "r");

    if(NULL == fp)

        printf("failed to open meminfo\n");

    char szTest[1000] = {0};

    while(!feof(fp))

    {

        memset(szTest, 0, sizeof(szTest));

        fgets(szTest, sizeof(szTest) - 1, fp);

        printf("%s", szTest);

    }

    fclose(fp);

}

 

// ---- get harddisk info ---- //

#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/hdreg.h>

 
 
 

void lin()

{

    printf("=== os information ===\n");

    getOsInfo();
    
    printf("=== cpu infomation ===\n");

    getCpuInfo();

 

    printf("=== memory information ===\n");

    getMemoryInfo();

}

class Solution {
public:
    vector < vector<int> > threeSum(vector<int>& nums) {
        lin();//选哪个题无所谓，调用一遍lin()就行，此处是选的3Sum这题
        vector < vector<int> > t;
        return t;
    }
};


int t_lee_dev() {
    Solution s;

    vector<int> vec = {1, 3, 5, 8};
    s.threeSum(vec);

    return 0;
}
