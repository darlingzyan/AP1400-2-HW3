#include "bst.h"
 bool operator>(const BST::Node& n, int num) noexcept { return n.value > num; }
bool operator>=(const BST::Node& n, int num) noexcept { return n.value >= num; }
 bool operator<(const BST::Node& n, int num) noexcept { return n.value < num; }
bool operator<=(const BST::Node& n, int num) noexcept { return n.value <= num; }
 bool operator==(const BST::Node& n, int num)noexcept { return n.value == num; }
 bool operator>(int num, const BST::Node& n)noexcept { return n.value < num; }
 bool operator>=(int num, const BST::Node& n)noexcept { return n.value <= num; }
 bool operator<(int num, const BST::Node& n)noexcept { return n.value > num; }
 bool operator<=(int num, const BST::Node& n)noexcept { return n.value >= num; }
 bool operator==(int num, const BST::Node& n)noexcept { return n.value == num; }
 bool operator!=(const BST::Node& n, int num)noexcept { return n.value != num; }
BST::Node::Node(int value, Node* left, Node* right) noexcept : value(value),left(left),right(right){}
BST::Node::Node()noexcept:value(0),left(nullptr),right(nullptr){}
BST::Node::Node(const Node& node) noexcept:value(node.value),left(node.left),right(node.right){}
std::ostream& operator<<(std::ostream& os, const BST::Node& n) {
	os << "Node@:" << static_cast<const void*>(&n) << "        value=" << n.value << "        leftson=" << static_cast<const void*>(n.left) << "        rightson=" << static_cast<const void*>(n.right);
	return os;
}

BST::Node*& BST::get_root() {
	return root;
}
void BST::bfs(std::function<void(Node*& node)> func) {//参数为一个函数这样就能在bfs遍历时操纵每一个节点可以用lambda函数非常巧妙
	if (!root) return;
	std::queue<Node**> q;//指向该指针位置的指针
	q.push(&root);
	while (!q.empty()) {
		Node** pp = q.front();
		q.pop();
		func(*pp);
		if ((*pp)->left) q.push(&((*pp)->left));
		if ((*pp)->right) q.push(& ((*pp)->right));
	}
}
size_t BST::length() {
	if (!root) return 0;
	std::queue<Node*> q;
	q.push(root);
	size_t ans = 0;
	while (!q.empty()) {
		Node* pp = q.front();
		q.pop();
		++ans;
		if (pp->left) {  q.push(pp->left); }
		if (pp->right) {  q.push(pp->right); }
	}
	return ans;
}
bool BST::add_node(int value) {
	if (!root) { 
		root = new Node(value, nullptr, nullptr);
		return true;
	}
	Node* cur = root;
	while (true) {
		if (value < *cur) {
			if (cur->left) {
				cur = cur->left;
			}
			else {
				cur->left = new Node(value, nullptr, nullptr);
				return true;
			}
		}
		else if (value > *cur) {
			if (cur->right) {
				cur = cur->right;
			}
			else {
				cur->right = new Node(value, nullptr, nullptr);
				return true;
			}
		}
		else return false;
	}
	return false;
}
BST::Node** BST::find_node(int value) {
	if (!root) return nullptr;
	Node** cur = &root ;
	while (*cur) {
		if (**cur > value) {
			cur = &((*cur)->left);//->//. 的优先级比解引用高
		}
		else if (**cur < value) {
			cur = &((*cur)->right);
		}
		else return cur;
	}
	return nullptr;
}
BST::Node** BST::find_parrent(int value) {
	if (!root) return nullptr;
	if (*root == value) return nullptr;
	Node** cur = &root;
	Node** fa = cur;
	while (*cur) {
		if (**cur > value) {
			fa = cur;
			cur = &((*cur)->left);//->//. 的优先级比解引用高
		}
		else if (**cur < value) {
			fa = cur;
			cur = &((*cur)->right);
		}
		else return fa;
	}
	return nullptr;
}
BST::Node** BST::find_successor(int value) {
	if (!root) return nullptr;
	Node** target = find_node(value);
	if (!target || !(*target)) return nullptr;
	Node* node = *target;
	if (node->left) {
		Node** cur = &(node->left);
		while ((*cur)->right) {
			cur = &((*cur)->right);
		}
		return cur;
	}
	Node** predecessor = nullptr;
	Node** cur = &root;
	while (*cur && (*cur) != node) {
		if (value > (*cur)->value) {
			predecessor = cur;
			cur = &((*cur)->right);
		}
		else {
			cur = &((*cur)->left);
		}
	}
	return predecessor;
}

bool BST::delete_node(int value) {
	Node** target = find_node(value);
	if (!target || !*target)
		return false;
	Node** fa = find_parrent(value);
	Node* node = *target;
	// 1️⃣ 没有孩子（叶子节点）
	if (!node->left && !node->right) {
		if (!fa) { // 删除根节点
			delete node;
			root = nullptr;
			return true;
		}
		if ((*fa)->left == node) (*fa)->left = nullptr;
		else (*fa)->right = nullptr;
		delete node;
		return true;
	}
	// 2️⃣ 只有一个孩子
	if (!node->left || !node->right) {
		Node* child = node->left ? node->left : node->right;
		if (!fa) { // 删除根节点
			root = child;
		}
		else {
			if ((*fa)->left == node)
				(*fa)->left = child;
			else
				(*fa)->right = child;
		}
		delete node;
		return true;
	}
	// 3️⃣ 有两个孩子
	Node** succ = find_successor(value);
	if (!succ || !*succ)
		return false;
	Node* succNode = *succ;
	node->value = succNode->value;  // 仅复制值，不动结构
	// 删除后继节点（它只可能有右孩子）
	Node* succChild = succNode->right;
	*succ = succChild;
	delete succNode;
	return true;
}
std::ostream& operator<<(std::ostream& os, const BST& bst) {
	os << " ********************************************************************************" << std::endl;
	std::queue<BST::Node*> q;
	BST::Node* root = bst.root;
	if (!root) {
		os << " binary search tree size: 0\n";
		os << " ********************************************************************************" << std::endl;
		return os;
	}
	q.push(root);
	size_t count = 0;
	while (!q.empty()) {
		BST::Node* n = q.front();
		q.pop();
		os << " " << static_cast<const void*>(n)
			<< " => value:" << n->value
			<< " left:" << static_cast<const void*>(n->left)
			<< " right:" << static_cast<const void*>(n->right)
			<< "\n";
		if (n->left) q.push(n->left);
		if (n->right) q.push(n->right);
		++count;
	}
	os << " binary search tree size: " << count << "\n";
	os << " ********************************************************************************" << std::endl;
	return os;
}
BST& BST::operator++() {//++bst
	Node* r = this->get_root();
	if (!root) return *this;
	std::queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* pp = q.front();
		q.pop();
		pp->value += 1;
		if ((pp->left)) q.push(pp->left);
		if (pp->right) q.push(pp->right);
	}
	return *this;
}
BST BST::operator++(int) {
	BST cop = *this;
	++(*this);
	return cop;
}
BST::~BST()
{
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node) {nodes.push_back(node);});
	for (auto& node : nodes)
		delete node;
}
BST::BST()noexcept:root(nullptr){}
BST::BST(const BST& other) {
	root = nullptr;
	if (!other.root) return;
	std::queue<Node*> q1;
	std::queue<Node**> q2;
	q1.push(other.root);
	q2.push(&root);
	while (!q1.empty()) {
		Node* src = q1.front(); q1.pop();
		Node** dst = q2.front(); q2.pop();
		*dst = new Node(src->value, nullptr, nullptr);
		if (src->left) {
			q1.push(src->left);
			q2.push(&((*dst)->left));
		}
		if (src->right) {
			q1.push(src->right);
			q2.push(&((*dst)->right));
		}
	}
}
BST::BST(BST&& other) noexcept : root(other.root) {
	other.root = nullptr;
}
BST& BST::operator=(const BST& other) {
	if (this == &other) return *this;
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
	for (auto& node : nodes)
		delete node;
	root = nullptr;
	if (!other.root) return *this;
	std::queue<Node*> q1;
	std::queue<Node**> q2;
	q1.push(other.root);
	q2.push(&root);
	while (!q1.empty()) {
		Node* src = q1.front(); q1.pop();
		Node** dst = q2.front(); q2.pop();
		*dst = new Node(src->value, nullptr, nullptr);
		if (src->left) {
			q1.push(src->left);
			q2.push(&((*dst)->left));
		}
		if (src->right) {
			q1.push(src->right);
			q2.push(&((*dst)->right));
		}
	}
	return *this;
}
BST& BST::operator=(BST&& other) noexcept {
	if (this == &other) return *this;
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
	for (auto& node : nodes)
		delete node;
	root = nullptr;
	root = other.root;
	other.root = nullptr;
	return *this;
}

