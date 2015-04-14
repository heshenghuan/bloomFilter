#include<iostream>
#include<bitset>
#include<string>
#define MAX 2<<24
using namespace std;

/* 这里简化了生成位向量的过程
 * 通常过程应该是由元素个数n和错误率p生成位向量长度m
 * 推导公式：p = 2^[-(m/n)ln(2)]
 * 故m = -n*ln(p)/[ln(2)]^2
 *     ≈-2*n*lnp    
 *     = 2*n*ln(1/p)
 */
bitset<MAX> bloomSet;

/* 这里同样简化了生成hash函数所用质数的过程
 * hash函数的个数k与m,n的关系如下：
 * k = (m/n)*ln2 ≈0.7*(m/n)
 * 
 * 正常情况下应该选取k个不同的质数作为seeds
 */
int seeds[7]={3,7,11,13,31,37,61};           //使用7个hash函数

int getHashValue(string str,int n){          //计算hash值
    int result=0;
    for(int i=0;i<str.size();++i){
        result=seeds[n]*result+(int)str[i];
        if(result>MAX)
            result%=MAX;
    }
    return result;
}

bool isInBloomSet(string str){               //判断是否在布隆过滤器中
    for(int i=0;i<7;++i){
        int hash=getHashValue(str,i);
        if(bloomSet[hash]==0)
            return false;
    }
    return true;
}

void addToBloomSet(string str){               //添加元素到布隆过滤器 
    for(int i=0;i<7;i++){
        int hash=getHashValue(str,i);
        bloomSet.set(hash,1);
    }
}

void initBloomSet(){                          //初始化布隆过滤器
    addToBloomSet("http://www.baidu.com");
    addToBloomSet("http://www.sina.com.cn");
    addToBloomSet("http://www.google.com");
    //这里也可以用读入文件的方式导入大量网址
}

int main(){
    int n;
    initBloomSet();
    cin>>n;
    string str;
    while(n--){
        cin>>str;
        if(isInBloomSet(str))
            cout<<"Yes"<<endl;
        else
            cout<<"No"<<endl;
    }
    return 0;
}
