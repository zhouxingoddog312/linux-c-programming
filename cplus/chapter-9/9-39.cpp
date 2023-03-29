vector<string> svec;
svec.reserve(1024);//分配至少能容纳1024个string的内存空间
string word;
while(cin>>word)
	svec.push_back(word);//从标准输入中读取元素，若读取数目超过1024，则会重新分配更大的内存空间
svec.resize(svec.size()+svec.size()/2);//调整svec的大小为当前元素数目的1.5倍，新添加的元素初始化为空的string，若调整后的数目超过当前的capacity则会重新分配更大的内存空间
