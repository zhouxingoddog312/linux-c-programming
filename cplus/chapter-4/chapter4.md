[toc]

### 4.1
105
### 4.2
1. `*(vec.begin())`
2. `(*(vec.begin()))+1`
### 4.3
&emsp;&emsp;C++只规定了非常少的二元运算符（逻辑与运算符、逻辑或运算符、逗号运算符）的求值顺序，其他绝大多数二元运算符的求值顺序并没有明确规定。这样做提高了代码的生成效率，但是可能引发潜在的缺陷。对于没有指定执行顺序的运算符来说，如果表达式指向并修改了同一个对象，将会引发错误并产生未定义的行为；而如果运算对象彼此无关，它们既不会改变同一对象的状态也不执行IO任务，则函数的调用顺序不受限制。
### 4.4
`((12/3)*4)+(5*5)+((24%4)/2)`
```
#include <iostream>
using namespace std;
int main()
{
	cout<<12/3*4+5*15+24%4/2<<endl;
	return 0;
}
```
### 4.5
1. -86
2. -18
3. 0
4. -2
### 4.6
`num%2==0`
### 4.7
&emsp;&emsp;溢出的含义是，计算结果超出该数据类型的表示范围。
`unsigned u=0;--u;`
`int i=INT_MAX+1;`
`int k=2024*2024*2024*2024;`
### 4.8
&emsp;&emsp;相等性运算中求值顺序未规定，逻辑与、或遵循从左到右最短路径原则。
### 4.9
&emsp;&emsp;先判断cp（即指针）是否为0，再判断*cp（即字符串首字母'H'）是否为0或'\0'。
### 4.10
`while(std::cin>>num&&num!=42)`
### 4.11
`a>b&&b>c&&c>d`
### 4.12
&emsp;&emsp;先判断j<k是否为真，如果为真时判断i!=1，如果为假时判断i!=0。
### 4.13
1. i的值是3,d的值是3.0
2. i的值是3,d的值是3.5
### 4.14
`f(42=i)`字面值常量不能放在赋值运算符的左侧。
`f(i=42)`i赋值42,括号内的判断永远为真。
### 4.15
&emsp;&emsp;int *指针不能隐式转换为int，第二行改成`dval=ival=*pi=0;`
### 4.16
1. 赋值运算符优先级较低，改为`if((p=getPtr())!=0)`
2. 混淆了相等性判断与赋值运算符，改为`if(i==1024)`
### 4.17
&emsp;&emsp;递增和递减运算符有两种形式：前置版本和后置版本。前置版本首先将运算对象加1（或减1），然后把改变后的对象作为求值结果。后置版本也将运算对象加1（或减1），但是求值结果是运算对象改变之前那个值的副本。这两种运算符必须作用于左值运算对象。前置版本将对象本身作为左值返回，后置版本则将对象原始值的副本作为右值返回。
### 4.18
&emsp;&emsp;如果序列中没有负值的话，程序将解引用一个尾后迭代器。
### 4.19
1. ptr不是空指针时，解引用ptr并判断其值是否为零，并让ptr前进到下一个位置。
2. ival自增1,若ival原有的值不为0,则判断现在的ival是否为0.
3. 错误，求值顺序未定义。
### 4.20
1. 合法，解引用迭代器当前位置，并前进一位。
2. 不合法，string并没有定义后置自增运算符。
3. 不合法，解引用运算符优先级低于点运算符。
4. 合法，调用迭代器所指string元素的empty成员。
5. 不合法，string并没有定义后置自增运算符。
6. 合法，迭代器所指string元素调用empty成员，迭代器前进到下一个位置。
### 4.21
```
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> ivec{1,2,3,4,5,6,7,8,9};
	for(auto &value:ivec)
		if(value%2)
			value*=2;
	for(auto value:ivec)
		cout<<value<<" ";
	cout<<endl;
	return 0;
}
```
### 4.22
==4-22-1.cpp==
```
#include <iostream>
using namespace std;
int main()
{
	unsigned grade;
	string str;
	while(cin>>grade&&grade<=100)
	{
		str=(grade>90)?"high pass":(grade>75)?"pass":(grade>=60)?"low pass":"fail";
		cout<<str<<endl;
	}
	return 0;
}
```
==4-22-2.cpp==
```
#include <iostream>
using namespace std;
int main()
{
	unsigned grade;
	string str;
	while(cin>>grade&&grade<=100)
	{
		if(grade>90)
			cout<<"high pass"<<endl;
		else if(grade>75)
			cout<<"pass"<<endl;
		else if(grade>=60)
			cout<<"low pass"<<endl;
		else
			cout<<"fail"<<endl;
	}
	return 0;
}
```
### 4.23
```
string s="word";
string p1=s+(s[s.size()-1]=='s'?"":"s");
```
### 4.24
&emsp;&emsp;如果条件运算符满足的是左结合律，那么就会先计算`(grade>90)?"high pass":(grade<60);`，条件运算符要求两个结果表达式的类型相同，无法通过编译。
### 4.25
&emsp;&emsp;在位运算符中，运算符~高于<<，因此先对q按位求反，因为位运算符的运算对象应该是整数类型，所以字符q首先转换为整数类型。如题所示，char占8位而int占32位，所以字符q转换后得到`00000000 00000000 00000000 01110001`，按位求反得到`11111111 11111111 11111111 10001110`；接着执行移位操作，得到`11111111 11111111 11100011 10000000`。
C++规定整数按照其补码形式存储，对上式求补，得到`10000000 00000000 00011100 10000000`，即最终结果的二进制形式，转换成十进制形式是`-7296`。
### 4.26
&emsp;&emsp;如果unsigned int只有16位的话，数据会丢失。
### 4.27
1. 3
2. 7
3. 1
4. 1
### 4.28
```
#include <iostream>
using namespace std;
int main()
{
	cout<<"char="<<sizeof(char)<<endl;
	cout<<"int="<<sizeof(int)<<endl;
	cout<<"float="<<sizeof(float)<<endl;
	cout<<"double="<<sizeof(double)<<endl;
	return 0;
}
```
### 4.29
```
int x[10];int *p=x;
cout<<sizeof(x)/sizeof(*x)<<endl;//整个数组所占空间大小除以单个元素所占空间大小，10.
cout<<sizeof(p)/sizeof(*p);//指针所占空间大小除以int所占空间大小，2.
```
### 4.30
1. (sizeof x)+y
2. sizeof(p->mem[i])
3. (sizeof a)<b
4. sizeof(f())
### 4.31
&emsp;&emsp;使用前置版本或后置版本是一样的，这是因为递增递减运算符与真正使用这两个变量的语句位于不同的表达式中，所以不会有什么影响。
```
vector<int>::size_type cnt = ivec.size();
for (vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--)
    ivec[ix] = cnt;
```
### 4.32
&emsp;&emsp;初始化指针指向数组首位，下标赋值0,条件部分判断下标不能等于数组长度，指针未到尾后。每次循环下标加1,指针前进一位。
### 4.33
&emsp;&emsp;someValue如果非0,则x、y递增，再y递减，否则x、y递减。
### 4.34
1. float向bool值转换
2. int向float转换，float再提升为double
3. char提升为int，乘法结果再转换为double
### 4.35
1. char转换为int，和再转换为char。
2. int转换为double，unsigned转换为double，差再转换为float。
3. unsigned转换为float，积再转换为double。
4. int转换为float，float再转换为double，double再转换为char。
### 4.36
`i*=static_cast<int>(d)`
### 4.37
1. `string *tmp=const_cast<string *>(ps);pv=static_cast<void *>(tmp);`
2. `i=static_cast<int>(*pc);`
3. `pv=static_cast<void *>(&d);`
4. `pc=static_cast<char *>(pv);`
### 4.38
&emsp;&emsp;将`j/i`的结果命名强制类型转换为double，并为slope赋值。
