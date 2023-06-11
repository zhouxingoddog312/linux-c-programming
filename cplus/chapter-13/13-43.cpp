void StrVec::free()
{
	if(elements)
	{
		for_each(elements,first_free,[](string &str) {alloc.destroy(&str);});
		alloc.deallocate(elements,cap-elements);
	}
}
