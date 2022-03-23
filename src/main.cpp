#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        BST bst{};
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(65);
        bst.add_node(60);
        bst.add_node(70);
        bst.add_node(5);
        bst.add_node(2);
        bst.add_node(7);
        bst.add_node(75);

        /*EXPECT_EQ(bst.length(), 10);
        EXPECT_TRUE(bst.delete_node(10)); // only left child
        EXPECT_EQ(bst.length(), 9);
        EXPECT_EQ(bst.get_root()->left->value, 5);
        EXPECT_EQ(bst.get_root()->left->left->value, 2);
        EXPECT_EQ(bst.get_root()->left->right->value, 7);
        EXPECT_EQ(bst.get_root()->left->right->left, nullptr);
        EXPECT_EQ(bst.get_root()->left->right->right, nullptr);*/
        std::cout << bst;
        puts("");
        if (bst.delete_node(10)) std::cout << "sucess";
        std::cout << std::endl <<bst.length()<<std::endl<<bst ;

    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}