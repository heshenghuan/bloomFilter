#!/usr/bin
#coding=utf-8

import cmath
from BitVector import BitVector
import random

class BloomFilter(object):
    def __init__(self,error_rate,elementNum):
        #计算最佳bitVector向量长度
        #bit_num = -n*ln(p)/[ln(2)]^2
        self.bit_num=-1*elementNum*cmath.log(error_rate)/(cmath.log(2.0)*cmath.log(2.0))

        #四字节对齐
        self.bit_num=self.align_4byte(self.bit_num.real)
        #分配内存
        self.bit_array = BitVector(size=self.bit_num)

        '''
        计算hash种子数
        hash_num=cmath.log(2.0)*(bit_num/n)
        并向上取整
        '''
        self.hash_num=cmath.log(2.0)*(self.bit_num/elementNum)
        self.hash_num=int(self.hash_num.real)+1

        #产生hash函数种子
        self.hash_seeds=self.generate_hashseeds(self.hash_num)

    def get_hash_value(self,element,seed):
        hash_val=0
        for ch in str(element):
            chval=ord(ch)
            hash_val=hash_val*seed+chval
            if hash_val>self.bit_num:
                hash_val=hash_val%self.bit_num
        return hash_val
    
    def insert_element(self,element):
        for seed in self.hash_seeds:
            hash_val=self.get_hash_value(element,seed)
            #设置对应位为1
            self.bit_array[hash_val]=1

    def is_element_exist(self,element):
        for seed in self.hash_seeds:
            hash_val=self.get_hash_value(element,seed)
            if self.bit_array[hash_val]==0:
                return False

        return True

    def align_4byte(self,bit_num):
        num=int(bit_num/32)
        num=32*(num+1)
        return num

    def is_prime(self,num):
        if num==9:
            return False
        for i in xrange(3,int(num**0.5)):
            if num%i==0:
                return False
        return True

    def generate_hashseeds(self,hash_num):
        count=0
        hash_seeds=[]
        for index in xrange(hash_num):
            hash_seeds.append(0)
        for index in xrange(10,10000):
            if self.is_prime(index):
                hash_seeds[count]=index
                count=count+1
            if count==hash_num:
                break
        return hash_seeds

bf = BloomFilter(0.001,1000000)
element = 'http://www.sina.com.cn'
bf.insert_element(element)
print bf.is_element_exist('http://www.tencent.com')
print bf.is_element_exist(element)
