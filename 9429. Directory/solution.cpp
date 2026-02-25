#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999
#include<vector>
using namespace std;

// The below commented functions are for your reference. If you want 
// to use it, uncomment these functions.
int mstrcmp(const char *a, const char *b)
{
	int i;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return a[i] - b[i];
}

int mstrncmp(const char *a, const char *b, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (a[i] != b[i])
			return a[i] - b[i];
	}
	return 0;
}

int mstrlen(const char *a)
{
	int len = 0;

	while (a[len] != '\0')
		len++;

	return len;
}

void mstrcpy(char *dest, const char *src)
{
	int i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = src[i];
}
void mstrncpy(char *dest, const char *src, int len)
{
	for (int i = 0; i<len; i++)
	{
		dest[i] = src[i];
	}
	dest[len] = '\0';
}

struct Node{
	char name[NAME_MAXLEN + 1];
	vector<Node*> children;	
};
const int max_node = 50000;
Node nodes[max_node];
int node_count = 0;

Node* createNode(char name[NAME_MAXLEN + 1]){
	mstrcpy(nodes[node_count].name, name);
	nodes[node_count].children.clear();
	return &nodes[node_count++];
}
Node* root;
Node* traverse(const char* path) {
    Node* cur = root;
    int i = 1;
    while (path[i]) {
        char seg[7];
        int j = 0;
        while (path[i] && path[i] != '/') seg[j++] = path[i++];
        seg[j] = '\0'; // string terminator
        if (j > 0){
			for(Node* child : cur->children){
				if(mstrcmp(child->name, seg) == 0){
					cur = child;
					break;
				}
			}
    }if (path[i] == '/') i++;
}
    return cur;
}
Node* traverseParent(const char* path) {
    Node* cur = root;
	Node* curparent = nullptr;
    int i = 1;
    while (path[i]) {
        char seg[7];
        int j = 0;
        while (path[i] && path[i] != '/') seg[j++] = path[i++];
        seg[j] = '\0'; // string terminator
        if (j > 0){
			for(Node* child : cur->children){
				if(mstrcmp(child->name, seg) == 0){
					curparent = cur;
					cur = child;
					break;
				}
			}
    }if (path[i] == '/') i++;
}
    return curparent;
}


void init(int n) {
	node_count = 0;
	char root_name[NAME_MAXLEN + 1] = "/";
	root = createNode(root_name);

}


void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	Node* parent = traverse(path);
	Node* new_node = createNode(name);
	parent->children.push_back(new_node);
}

void cmd_rm(char path[PATH_MAXLEN + 1]) {
	Node* parent = traverseParent(path);
	Node* target = traverse(path);
	for(int i = 0; i < parent->children.size(); i++){
		if(parent->children[i] == target){
			parent->children.erase(parent->children.begin() + i);
			break;
		}
	}
}

Node* deepcopy(Node* node){
	Node* new_node = createNode(node->name);
	for(Node* child : node->children){
		new_node->children.push_back(deepcopy(child));
	}
	return new_node;
}

int counter;
void count(Node* node){
	counter++;
	for(Node* child : node->children){
		count(child);
	}
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = traverse(srcPath);
	Node* dst = traverse(dstPath);
	Node* new_node = deepcopy(src);
	dst->children.push_back(new_node);

}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	Node* src = traverse(srcPath);
	Node* dst = traverse(dstPath);
	Node* src_parent = traverseParent(srcPath);
	int i = 0;
	dst->children.push_back(src);
	for(Node* child : src_parent->children){
		if(child == src){
			src_parent->children.erase(src_parent->children.begin() + i);
			break;
		}
		i++;
	}

}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	Node* target = traverse(path);
	counter = 0;
	count(target);

	return counter-1; // 자기자신 제외
}