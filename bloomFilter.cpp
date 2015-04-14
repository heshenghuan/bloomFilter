#include<iostream>
#include<bitset>
#include<string>
#define MAX 2<<24
using namespace std;

/* �����������λ�����Ĺ���
 * ͨ������Ӧ������Ԫ�ظ���n�ʹ�����p����λ��������m
 * �Ƶ���ʽ��p = 2^[-(m/n)ln(2)]
 * ��m = -n*ln(p)/[ln(2)]^2
 *     ��-2*n*lnp    
 *     = 2*n*ln(1/p)
 */
bitset<MAX> bloomSet;

/* ����ͬ����������hash�������������Ĺ���
 * hash�����ĸ���k��m,n�Ĺ�ϵ���£�
 * k = (m/n)*ln2 ��0.7*(m/n)
 * 
 * ���������Ӧ��ѡȡk����ͬ��������Ϊseeds
 */
int seeds[7]={3,7,11,13,31,37,61};           //ʹ��7��hash����

int getHashValue(string str,int n){          //����hashֵ
    int result=0;
    for(int i=0;i<str.size();++i){
        result=seeds[n]*result+(int)str[i];
        if(result>MAX)
            result%=MAX;
    }
    return result;
}

bool isInBloomSet(string str){               //�ж��Ƿ��ڲ�¡��������
    for(int i=0;i<7;++i){
        int hash=getHashValue(str,i);
        if(bloomSet[hash]==0)
            return false;
    }
    return true;
}

void addToBloomSet(string str){               //���Ԫ�ص���¡������ 
    for(int i=0;i<7;i++){
        int hash=getHashValue(str,i);
        bloomSet.set(hash,1);
    }
}

void initBloomSet(){                          //��ʼ����¡������
    addToBloomSet("http://www.baidu.com");
    addToBloomSet("http://www.sina.com.cn");
    addToBloomSet("http://www.google.com");
    //����Ҳ�����ö����ļ��ķ�ʽ���������ַ
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
