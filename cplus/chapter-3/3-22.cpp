for(auto it=text.begin();it!=text.end()&&!it->empty();it++)
{
	for(auto pts=it->begin();pts!=it->end();pts++)
		*pts=toupper(*pts);
	cout<<*it<<endl;
}
