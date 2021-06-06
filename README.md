

**ASSOCIATIVE MAPS:** Associative Maps or Tree Maps are an important** data structure that have many uses in real-world. Conceptually, Map is a data structure that consists of are collection of **key and value pairs.**  In a map, the *key values* are generally used to sort and uniquely identify the elements, while the *mapped values* store the content associated to this *key.* 

**Problem Statement:** Consider an online shopping mart. The online shopping marts advertise and display million of the products on their website. However, they do not have all the product in stock. The products that are most frequently purchased by customers are kept in warehouse while the rest of the products are bought when a demand is placed by a customer.  

We wish to keep track of the most frequently bought products along with their name and quantity on hand (quantity available in ours stock). So, whenever a customer placed an order we can quickly check if the product is available in our stock or not.   

**Conceptually**, we want to have an associative map of products: 

|**Key (product id)** |**Value (product name, quantity available in stock)** |
| - | - |
|123 |**Name**: AMD GPU **Quantity:**5 |
|2098 |**Name:** Intel Corei7 CPU **Quantity:**10 |
|567 |**Name:** Kingston RAM **Quantity:**350 |
|39911 |**Name:** DDR3 RAM **Quantity:**50 |
**PART 1)** Implement **Associative MAPS** using **AVL TREES:**   

1. **Provide following operations in your BST class** 
1) **Insert:** Provide **Recursive** Insert function. The Insert function will insert a given value in AVL MAP. Incase value already exist then it should return false and do not insert.**   
1) **Delete:** Provide **Recursive** Delete function. The delete function will delete the node with given key. Incase key does not exist then it should return false.  Your code will perform deletion by copy.** 
1) **LookUp:** Provide Recursive function to find if the record with the given Key exists. 
1) **PrintINORDER: Recursively** Print the records sorted by the key.**  
1) **Destructor** 
6) **PRINT the AVL Tree on Screen in the following manner** 

|<p>`                                   `**50** </p><p>`                                 `**/     \** </p><p>`                             `**20       70** </p><p>`                          `**/    \          \** </p><p>`                       `**10    30        85** </p><p>**Only print keys (do not show values)** </p>|
| - |
|<p>**You can use the following function to move cursor to (x,y) coordinate on the screen** #include <stdio.h></p><p>void PlaceCursor(int x, int y){ </p><p>COORD c; </p><p>c.X = x;c.Y = y; </p><p>HANDLE h = GetStdHandle(STD\_OUTPUT\_HANDLE); SetConsoleCursorPosition(h, c); </p><p>} </p><p>**If you can find the height of the tree and the number of leaf nodes, then you can easily print the tree.** </p>|
2. **Load:  create an AVL** from the file data. The file will consist of ID, Name and Quantity. File format will be as follows (the fields are separated by tab) (not in BST class)  **![](Aspose.Words.9c44009d-3053-42e8-8f7b-63d860413e45.001.png)![](Aspose.Words.9c44009d-3053-42e8-8f7b-63d860413e45.002.png)ID        Name           Quantity**  

**123     AMD RAM    75**  

**245     K RAM          47**  

**AVLMAP** 



|<p>template<class K, class T> </p><p>class AVLNode { </p><p>public: </p><p>`               `K Key; </p><p>`               `T \* data; </p><p>`               `int height; </p><p>AVLNode<T> \*left, \*right; };** </p>|<p>template<class K, class T> </p><p>class **AVLMAP** { </p><p>/\* Note we are making AVLMAP not node\*/   /\*Add all the functions here \*/ </p><p>private:  </p><p>AVLNode< K, T >\* root; </p><p>**}** </p>|
| - | - |
|<p>class ProductData { </p><p>public:  </p><p>/\* Provide all required operations here\*/ </p><p>/\* Overload all the required operators needed for the proper functioning\*/ </p><p>private: </p><p>string name; //Value </p><p>int quantity; //Value </p><p>};** </p>|<p>int main() { </p><p>`     `cout << "Associative Map using AVLMAP";      AVLMAP**<int, ProductData> ProductMap;**      return 0; </p><p>}** </p>|
|<p>**NOTE: Do not create an object of PRODUCTDATA in any function of AVLMAP class.** </p><p>**AVLMAP should not know about the PRODUCTDATA class.** </p><p>AVLMAP will compare data of different nodes using the key store in it.  Overload all the operators that you need in PRODUCTDATA class.  </p>|
**Which implementation of Associative Map is better? Maps using AVLMAP or BST. Why?**   

**CODE DESIGN GUIDLEINES** 

- Do template-based programming 
- Code should be properly intendent and commented (2 marks for this) 
- Make sure there are no memory leaks or dangling pointers 
- Don’t cheat or take too much unnecessary help from your friends 
