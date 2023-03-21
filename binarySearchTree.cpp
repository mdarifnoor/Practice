#include<iostream>
#include<vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data){
        val = data;
        left = nullptr;
        right = nullptr;
    }
};
void printArr(vector<int> arr){
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i] << " ";
    }
}


void preorder(TreeNode* root, vector<int> &values){
    if(root == nullptr)
        return;

    values.emplace_back(root -> val);
    preorder(root -> left, values);
    preorder(root -> right, values);
    
}

void inorder(TreeNode* root, vector<int> &values){
    if(root == nullptr)
        return;
    inorder(root -> left, values);
    values.emplace_back(root -> val);
    inorder(root -> right, values);
}

void postorder(TreeNode* root, vector<int> &values){
    if(root == nullptr)
        return;
    postorder(root -> left, values);
    postorder(root -> right, values);
    values.emplace_back(root -> val);
}

void levelorder(TreeNode* root, vector<int> &values){
    if(root == NULL) return;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        TreeNode* current = q.front();
        q.pop();
        values.emplace_back(current -> val);
        if(current -> left)  q.push(current -> left);
        if(current -> right) q.push(current -> right);

    }
}

vector<vector<int>> bfs(TreeNode* root){
    if(root == nullptr) return {};
    vector<vector<int>> arr;
    queue<TreeNode*> q;
    q.push(root);

    while(!q.empty()){
        int len = q.size();
        vector<int> level;

        for(int i = 0; i < len; i++){
            TreeNode* temp = q.front();
            q.pop();
            if(temp -> left) q.push(temp -> left);
            if(temp -> right) q.push(temp->right);
            level.emplace_back(temp -> val);
        }
        arr.emplace_back(level);
    }
 
    return arr;
}



TreeNode* insertBST(TreeNode *root, int data){
    if(root == NULL){
        return new TreeNode(data);
    }
    if(data < root -> val) {
        root -> left = insertBST(root -> left, data);
    }
    else {
        root -> right = insertBST(root -> right, data);
    }

    return root;

}

TreeNode* array2bst(TreeNode* root, vector<int> &values){
    for(int i = 0; i < values.size(); i++){
        root = insertBST(root, values[i]);
    }
    return root;
}

TreeNode* findMin(TreeNode* root){
    if (root == nullptr) return nullptr;
    while(root -> left != nullptr) root = root -> left;
    return root;
}


TreeNode* deleteTreeNode(TreeNode* root, int key){
    if(root == nullptr) return root;
    else if(key < root -> val) deleteTreeNode(root -> left, key);
    else if(key > root -> val) deleteTreeNode(root -> right, key);
    else {
        if(root -> left == nullptr && root -> right == nullptr){
            delete root;
            root = nullptr;
        }
        else if(root -> left == nullptr){
            TreeNode* temp = root;
            root = root -> right;
            delete temp;
        }
        else if(root -> right == nullptr){
            TreeNode* temp = root;
            root = root -> left;
            delete temp;
        }
        else {
            TreeNode* temp = findMin(root -> right);
            root -> val = temp -> val;
            root -> right = deleteTreeNode(root -> right, temp -> val);
        }
    }
    return root;
}


int main(){

    /* 
           1
         2   3
        4 5 6 7  
    */

    TreeNode *root = new TreeNode(1);
    root -> left = new TreeNode(2);
    root -> right = new TreeNode(3);
    root -> left -> left = new TreeNode(4);
    root -> left -> right = new TreeNode(5);
    root -> right -> left = new TreeNode(6);
    root -> right -> right = new TreeNode(7);


    vector <int> pre;
    preorder(root, pre);
    printArr(pre);
    cout<<"\n";
    vector <int> ino;
    inorder(root, ino);
    printArr(ino);
    cout<<"\n";
    vector<int> pos;
    postorder(root, pos);
    printArr(pos);
    cout<<"\n";
    printArr({pos.begin()+7, pos.end()});
    vector<int> arr = {1,2,3,4,5,7};
    vector<int> res;
    TreeNode* root1;
    root1= array2bst(NULL, arr);
    inorder(root1, res);
    printArr(res);
    cout<< "\n";

    TreeNode *root2 = NULL;
    root2 = insertBST(root2, 5);
    root2 = insertBST(root2, 1);
    root2 = insertBST(root2, 3);
    root2 = insertBST(root2, 4);
    root2 = insertBST(root2, 2);
    root2 = insertBST(root2, 7);
    cout<<"\n";
    vector<int> level;
    levelorder(root, level);
    printArr(level);
    cout<<"\n";
   TreeNode* mn = findMin(root1);
    cout<< mn -> val <<endl;
    cout<<"\n";
    root = deleteTreeNode(root, 3);
    vector<int> level2;
    levelorder(root, level2);
    printArr(level2);




    return 0;
}
