#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 10000;
char a[maxn], b[maxn];

void getnext(int next[], char* const pattern, int m){
    int j = -1;
    next[0] = -1;
    for(int i = 1; i < m; i++) {
        while(j >= 0 && pattern[j+1] != pattern[i]) j = next[j];
        if(pattern[j+1] == pattern[i]) ++j;
        next[i] = j;
    }
}

bool kmp(char* const pattern, char* const str){
    bool found = false;
    int n = (unsigned)strlen(str), m = (unsigned)strlen(pattern);
    int *next = new int[m], j = -1;
    getnext(next, pattern, m);
    
    for(int i = 0; i < n; i++){
        while(j >= 0 && str[i] != pattern[j+1]) j = next[j];
        if(str[i] == pattern[j+1]) ++j;
        if(j == m-1) {
            found = true;
            cout << "Found at shift " << i-j << endl;
            j = next[j];
        }
    }
    return found;
}
int main(){
    cout << "请输入主串：" << endl;
    cin >> a;
    cout << "请输入模式串：" << endl;
    cin >> b;
    if(!kmp(b, a)) cout << "匹配失败。" << endl;
    return 0;
}