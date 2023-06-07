class TreeNode
{
	public:
		TreeNode():count(1),left(nullptr),right(nullptr) {}
		TreeNode(const std::string &str=std::string(),TreeNode *lchild=nullptr,TreeNode *rchild=nullptr):value(str),count(1),left(lchild),right(rchild) {}
		void CopyTree();
		int ReleaseTree();
		TreeNode(const TreeNode &);
		~TreeNode();
	private:
		std::string value;
		int count;
		TreeNode *left;
		TreeNode *right;
};
class BinStrTree
{
	public:
		BinStrTree():root(nullptr) {}
		BinStrTree(TreeNode *tree=nullptr):root(tree) {}
		BinStrTree(const BinStrTree &);
		~BinStrTree();
	private:
		TreeNode *root;
};
BinStrTree::BinStrTree(const BinStrTree &org):root(org.root)
{
	root->CopyTree();
}
BinStrTree::~BinStrTree()
{
	if(!root->ReleaseTree())
		delete root;
}

void TreeNode::CopyTree()
{
	if(left)
		left->CopyTree();
	if(right)
		right->CopyTree();
	++count;
}
int TreeNode::ReleaseTree()
{
	if(left)
	{
		if(!left->ReleaseTree())
			delete left;
	}
	if(right)
	{
		if(!right->ReleaseTree())
			delete  right;
	}
	--count;
	return count;
}
TreeNode::TreeNode(const TreeNode &org):value(org.value),count(1),left(org.left),right(org.right)
{
	if(left)
		left->CopyTree();
	if(right)
		right->CopyTree();
}
TreeNode::~TreeNode()
{
	if(count)
		ReleaseTree();
}
