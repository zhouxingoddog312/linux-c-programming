vector<int> ivec1;//一个空的元素类型为int的vector
vector<int> ivec2(ivec1);//ivec2初始化为ivec1的拷贝，包含ivec1中所有元素的副本
vector<int> ivec3=ivec1;//同上
vector<int> ivec4{1,2,3,4};//列表初始化，ivec4中包含列表中所有元素的拷贝
vector<int> ivec5={1,2,3,4};//同上
vector<int> ivec6(4);//ivec6中包含4个执行值初始化的元素
vector<int> ivec7(4,4);//ivec7中包含4个值为4的元素
vector<int> ivec8(ivec1.begin(),ivec1.end());//ivec8初始化为迭代器ivec1.begin()和ivec1.end()指定的范围中的元素，不含ivec.end()所指的元素
