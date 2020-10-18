// -------------------Libraries------------------- //
#include "BST.h"

// -------------------Public Methods------------------- //

// Constructor: Construct an empty tree.
// Precondition: None.
// Postcondition: Construct an empty tree and all private variables is set to 0.
BST::BST()
{
	root = nullptr;
	numNode = 0;
	smallestBranchHeight = 0;
	highestbranchHeight = 0;
	isTreeBalanced = false;
	isTreeCompleted = false;
}

// Destructor: Deallocate the tree.
// Precondition:
// Postcondition: The tree is deallocated.
BST::~BST()
{

}

// inputNumber: Input an integer into the tree.
// Precondition: Integer is not already inside the tree.
// Postcondition: the input integer is inserted into the tree.
void BST::inputNumber(int in)
{
	root = insert(root, in);
	numNode++;
}

// findHeight: Find the smallest and highest height of the tree.
// Precondition: None.
// Postcondition: Set smallestBranchHeight and highestBranchHeight
//                by the reseult from finding height.
void BST::findHeight()
{
	smallestBranchHeight = smallestHeight(root);
	highestbranchHeight = highestHeight(root);
}

// findIsBalanced: Determine if the tree is balanced.
// Precondition: Must call findHeight before calling findIsBalanced.
// Postcondition: Set isTreeBalanced to true if tree is balanced.
void BST::findIsBalanced()
{
	// Set isTreeBalanced to true if tree is balanced.
	if (isBalanced(root))
	{
		isTreeBalanced = true;
	}
}

// findIsComplete: Determine if the tree is completed.
// Precondition: Tree is finished in building.
// Postcondition: Set isTreeComplete to true if tree is complete.
void BST::findIsComplete()
{
	int index = 0;
	int numberNodes = getNumNode();
	if (isCompleted(root, index, numberNodes))
	{
		isTreeCompleted = true;
	}
}

// getSmallestHeight: Get smallestBranchHeight from the tree.
// Precondition: Recommand calling findHeight before calling getSmallestHeight.
// Postcondition: Return smallestBranchHeight as const int.
const int BST::getSmallestHeight()
{
	return smallestBranchHeight;
}

// getHighestHeight: Get highestBranchHeight from the tree.
// Precondition: Recommand calling findHeight before calling getHighestHeight.
// Postcondition: Return highestBranchHeight as const int.
const int BST::getHighestHeight()
{
	return highestbranchHeight;
}

// getNumNode: Get the number of node inputed into the tree.
// Precondition: None.
// Postcondition: Return numNode as const int.
const int BST::getNumNode()
{
	return numNode;
}

// getIsBalanced: Get the result of whether the tree is balanced.
// Precondition: Recommand calling findIsBalanced before calling getIsBalanced.
// Postcondition: Return "True" if isTreeBalanced is true, else "False".
const std::string BST::getIsBalanced()
{
	// Determining which string will return.
	return (isTreeBalanced) ? "True" : "False";
}

// getIsCompleted: Get the result of whether the tree is completed.
// Precondition: Recommend calling findIsCompleted before calling getIsCompleted.
// Postcondition: Return "True" if isTreeCompleted is true, else "False".
const std::string BST::getIsCompleted()
{
	return (isTreeCompleted) ? "True" : "False";
}

// -------------------Private Methods------------------- //

// newNode: Create a new bstNode with input integer as data.
// Precondition: None.
// Postcondition: Return the bstNode pointer to the new bstNode 
//				  with input integer as data.
BST::bstNode* BST::newNode(int in)
{
	// Create a new node.
	bstNode* temp = new bstNode();
	temp->data = in;
	temp->left = temp->right = nullptr;

	// Return the node pointer.
	return temp;
}

// insert: Insert an integer into the tree
// Precondition: None.
// Postcondition: An new node is inserted inside the tree.
BST::bstNode* BST::insert(bstNode*& node, int in)
{
	// If the node is empty, return a new node.
	if (node == nullptr) return newNode(in);

	// Recur down the tree until the node is recur to the right place for inserting.
	if (in < node->data)
		node->left = insert(node->left, in);
	else
		node->right = insert(node->right, in);

	// Return the node pointer.
	return node;
}

// smallestHeight: Determine the smallest height for the branches.
// Precondition: None.
// Postcondition: Return the height for the smallest branch.
int BST::smallestHeight(bstNode*& root)
{
	// Corner case: root is null.
	if (root == nullptr) return 0;

	// Base case:
	// Leaf Node: height = 1.
	if (root->left == nullptr && root->right == nullptr) return 1;

	// If left subtree is nullptr, then recur for the right subtree.
	if (root->left == nullptr) return smallestHeight(root->right) + 1;

	// If right subtree is nullptr, then recur for the left subtree.
	if (root->right == nullptr) return smallestHeight(root->left) + 1;

	return std::min(smallestHeight(root->left), smallestHeight(root->right)) + 1;
}

// highestHeight: Determine the highest height for the branches.
// Precondition: None.
// Postcondition: Return the height for the highest for the branches.
int BST::highestHeight(bstNode*& root)
{
	// Tree is empty return 0.
	if (root == nullptr) return 0;

	// Calculate the height
	// Height = 1 + max of left branch height and right branch height.
	int leftBranch = highestHeight(root->left);
	int rightBranch = highestHeight(root->right);
	return std::max(leftBranch, rightBranch) + 1;
}

// isBalanced: Determine if the tree is balanced.
// Precondition: None.
// Postcondition: Return true if the tree is balanced, else false.
bool BST::isBalanced(bstNode*& root)
{
	// If tree is empty, return true.
	if (root == nullptr) return true;

	// If tree is not empty, get the height of left and right sub trees.
	int leftHeight = highestHeight(root->left);
	int rightHeight = highestHeight(root->right);

	// Determining if each level of the tree is balanced.
	if (std::abs(leftHeight - rightHeight) <= 1 &&
		isBalanced(root->left) &&
		isBalanced(root->right))
		return true;

	// Tree is not balance if it reaches here.
	return false;
}

// isCompleted: Determining if the tree is completed.
// Precondition: None.
// Postcondition: Return true if the tree is completed, else false.
bool BST::isCompleted(bstNode*& root, unsigned int index, const unsigned int numberNodes)
{
	// An empty tree is complete.
	if (root == nullptr) return true;

	// If the index in the current node is more than the number of nodes,
	// then the tree is not complete.
	if (index >= numberNodes) return false;

	// recur for the left and right sub trees.
	return (isCompleted(root->left, 2 * index + 1, numberNodes) &&
			isCompleted(root->right, 2 * index + 2, numberNodes));
}