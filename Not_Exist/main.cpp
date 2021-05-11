//
//  main.cpp
//  Not_Exist
//
//  Created by 孙浩然 on 5/9/21.
//
#define DEFAULT_LEN (1 << 24)
#include <iostream>
#include <string>
using Rank = int;
using namespace std;
string to_bin(int num, int len);
class Bitmap
{
private:
    Rank N;
    Rank *T;

public:
    int sum;
    int size;
    Bitmap()
    {
    }
    void reset(int n){
        size = n;
        sum = 0;
        N = (n >> 5) + 1;
        T = new Rank[N];
        for(int i = 0 ; i < N ; i++){
            T[i] = 0;
        }
    }
    ~Bitmap()
    {
        //delete[] T;
    }
//    Bitmap (Bitmap &a)
//    {
//        sum = a.sum;
//        size = a.size;
//        T = a.T;
//        N = a.N;
//    }
    void operator=(Bitmap b){
//        delete[] T;
        N = b.N;
        T = new int[N];
        sum = b.sum;
        size = b.size;
        for(int i = 0 ; i < N ; i++){
            T[i] =  b.T[i];
        }
        //debug
//        for(int i = 0 ; i < N ; i++){
//            if(this->test(i)){
//                cout << to_bin(i, 23) << endl;
//            }
//        }
    }
    
    inline void set(int k)
    {
        if (!test(k))
        {
            sum++;
            T[k >> 5] |= 1 << (k % 32);
        }
    }
    inline void clear(Rank k)
    {
        if (test(k))
        {
            sum = 0;
            T[k >> 5] = not(T[k >> 5] | 1 << (k % 32));
        }
    }
    inline bool test(Rank k)
    {
        return T[k >> 5] & 1 << (k % 32);
    }
};
int strlen(char *c){
    int cnt = 0 ;
    while(c[cnt] != '\0'){
        cnt++;
    }
    return cnt;
}
void poptop_pushback(char *c, char pushed, int len){
    for(int i = 0 ; i < len - 1 ; i++){
        c[i] = c[i + 1];
    }
    c[len - 1] = pushed;
    return;
}

int to_deci(char *c, int len){
    int sum = 0;
    int rank = 0;
    for(int i = len - 1 ; i >= 0 ; i--, rank++){
        if(c[i] == '1'){
            sum += 1 << rank;
        }
    }
    return sum;
}
int to_deci(string c){
    int sum = 0;
    int rank = 0;
    for(int i = c.size() - 1 ; i >= 0 ; i--, rank++){
        if(c[i] == '1'){
            sum += 1 << rank;
        }
    }
    return sum;
}

string to_bin(int num, int len){
    string ans, strnum;
    int numlen = 0;
    while(num != 0){
        if(num % 2 == 0){
            strnum += '0';
        }else{
            strnum += '1';
        }
        num = num >> 1;
        numlen++;
    }
    numlen = len - numlen;
    while(numlen > 0){
        ans += '0';
        numlen--;
    }
    string ans2;
    while(!strnum.empty()){
        ans2.push_back(strnum[strnum.size() - 1]);
        strnum.pop_back();
    }
    ans = ans + ans2;
    return ans;
}
bool testbitmap(int size, Bitmap a){
    for(int i = 0 ; i < size ; i++){
        if(a.test(i) == 0){
            return false;
        }
    }
    return true;
}

string pop_front(string str){
    string ans;
    for(int i = 1 ; i < str.size() ; i++){
        ans.push_back(str[i]);
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    Bitmap a;
    char c[25], succ;
    int len = 24;
    scanf("%24s", c);
    if(strlen(c) < len){
        a.reset(1 << strlen(c));
        int ext = to_deci(c, strlen(c));
        a.set(ext);
    }else{//total len >= 23
        a.reset(1 << 24);
        do{
            succ = getchar();
            if(succ != '\n'){
                poptop_pushback(c, succ, len);
                int ext = to_deci(c, len);
                a.set(ext);
            }
        }while(succ != '\n');
    }
    for(int i = strlen(c) ; i > 0 ; i--){
        Bitmap b;
        b.reset(1 << i);
        for(int j = 0 ; j < (1 << (i + 1)) ; j++){
            if(a.test(j)){
                string p = to_bin(j, i + 1);
                string q = pop_front(p);//去头
                p.pop_back();//去尾
                int f = to_deci(p);//转10进制int
                int e = to_deci(q);//转10进制int
                b.set(f);//mark
                b.set(e);//mark
            }
        }//只要还有空位，继续搜size-1的bitmap
        if(b.sum == b.size)//如果无空缺，那a就是答案。
        {
            for(int j = 0 ; j < a.size ; j++){
                if(!a.test(j)){
                    cout << to_bin(j, i+1);
                    return 0;//直接输出答案
                }
            }
        }
        else{
            a = b;
        }
    }
    return 0;
}
