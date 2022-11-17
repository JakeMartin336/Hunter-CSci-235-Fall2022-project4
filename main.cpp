
#include"LinkedList.hpp"
#include"Node.hpp"

#include"Network.hpp"
#include"Account.hpp"

#include"Post.hpp"
#include"Promotional.hpp"
#include"Poll.hpp"
#include"General.hpp"

#include<iostream>
#include<string>
#include<vector>

int main ()
{
    // Test for class definitions
    Account *R = new Account("Rong","xzczxc ");
    Network<Account> net;
    Post* g = new General("General","FUCK","Rong");
    std::vector<std::string> pl_options = {"asd a", "Azxc aaf ", "acghfzlf jf "};
    Post* pl = new Poll("Poll ","asdc zxc ","Rong",pl_options);
    Post* prom = new Promotional("Promotional","zcxfas","Rong","https://www.google.com");
    net.addAccount(R);
    
    // Test for linkedlikst
    LinkedList<Post*> LL_Posts;
    Node<Post*>* Node_current;
    LL_Posts.insert(g,0);
    LL_Posts.insert(pl,1);
    LL_Posts.insert(prom,2);
    

    Node_current= LL_Posts.getHeadPtr();
    Node_current->getItem()->displayPost();
    std::cout << "\n";

    Node_current = Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout <<  "\n"; 

    Node_current= Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout << "\n";


    //Test for copy Constructor
    LinkedList<Post*> LL_newPosts(LL_Posts);

    std::cout << "\nCopyConstructor: \n";
    Node_current= LL_newPosts.getHeadPtr();
    Node_current->getItem()->displayPost();
    std::cout << "\n";

    Node_current = Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout <<  "\n"; 

    Node_current= Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout << "\n";

    // Test reverse LL
    //LinkedList<int> LL_int;
    //LL_int.insert(1);
    //LL_int.insert(2);
    //LL_int.insert(3);
    //LL_int.insert(4);
    //LL_int.insert(5);

    LinkedList<Post*> rev_LL;
    std::cout << "Test ReverseCopy: \n";
    rev_LL.reverseCopy(LL_newPosts);
    
    Node_current = rev_LL.getHeadPtr();
    Node_current->getItem()->displayPost();
    std::cout << "\n";

    Node_current = Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout <<  "\n"; 

    Node_current= Node_current->getNext();
    Node_current->getItem()->displayPost();
    std::cout << "\n";

    //Test moveItemToTop LL
    Post* gp = new General("FUCK","ewrgwerv","Rong");
    bool result = rev_LL.moveItemToTop(pl);
    std::cout << "If it was moved or not: " << result << "\n";
    rev_LL.getHeadPtr()->getItem()->displayPost();  
    std::cout << "\n";
    bool final = rev_LL.moveItemToTop(gp);
    std::cout << "If it was moved or not (should be 0): " << final << "\n\n";
    
    //Testing for Account addPost()
    std::cout << "Test addAccountToNet: " << net.addAccount(R) << "\n";
    std::cout << "Test addPost: " << R->addPost(gp) << "\n";
    std::cout << "Test addPost: " << R->addPost(g) << "\n";
    std::cout << "Test addPost: " << R->addPost(prom) << "\n";
    std::cout << "Test addPost:" << R->addPost(pl) << "\n";

    std::cout << "Test containsAccountinNet: " << net.containsAccount(R) << "\n";
    std::cout << "Test viewPostsinAct: \n";
    R->viewPosts();
    std::cout << "\nEnd of Add/View/ContainsAct\n\n";

    //Test for Network removeIfContains()
    std::string tester = "FUCK";
    int removed = net.removeIfContains(tester);
    std::cout << "Total Removed: " << removed << "\n\n";
    
    
    //std::cout << "Printing New Posts for Act: ";
    std::cout << "Testing view account posts: \n";
    R->viewPosts();
    std::cout << "\n\nTesting update account post: \n";
    R->updatePost(prom, "NewPromotional", "NewBodyPromo");
    R->updatePost(pl, "NewPoll", "NewBodyPoll");
    R->viewPosts();
    //std::cout << "Network update account post: \n";
    //net.printFeedForAccount(R);

    std::cout << "\n\nTesting remove account posts: \n";
    R->removePost(pl);
    R->removePost(prom);
    R->viewPosts();
    std::cout << "\n\nTests addPost: \n";
    Post* erefe = new General("NewGeneralPost","wepfirmwevnwe'oighe]9gqu]v","Rong");
    R->addPost(erefe);
    R->viewPosts();
    std::cout << "\n";

    std::cout << "Account is in Network: " << net.containsAccount(R) << "\n\n";
    
    //net.printFeedForAccount(*R);
    return 0;
}