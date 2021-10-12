#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "BTree.h"
#include "Cache.h"
#include "CacheUpgrade.h"

int main()
{
    BTree* tree = nullptr;
    char operation;
    std::cin >> operation;
    while (operation != 'X')
    {
        switch (operation)
        {
        case 'I':
        {
            int order;
            std::cin >> order;
            tree = new BTree(order);
            break;
        }

        case 'A':
        {
            int key;
            std::cin >> key;
            tree->insert(key);
            break;
        }

        case '?':
        {
            int key;
            std::cin >> key;
            if (tree->search(tree->getRoot(), key))
                std::cout << key << " " << "+\n";
            else
                std::cout << key << " " << "-\n";
            break;
        }

        case 'P':
        {
            tree->print(tree->getRoot());
            std::cout << std::endl;
            break;
        }

        case 'L':
        {
            int order;
            std::cin >> order;
            tree = new BTree(order);
            tree->load();
            break;
        }

        case 'S':
        {
            std::cout << tree->getTreeOrder() << std::endl;
            tree->save(tree->getRoot());
            std::cout << std::endl;
            break;
        }

        case 'R':
        {
            int key;
            std::cin >> key;
            if(tree->search(tree->getRoot(), key))
                tree->remove(tree->getRoot(), key);

            break;
        }

        case 'C':
        {
            int size;
            std::cin >> size;
            Cache cache(size);
            int number;
            char character;
            int noCache = 0;
            int withCache = 0;
            while (scanf("%d%c",&number,&character))
            {
                tree->search(tree->getRoot(),number);
                noCache += tree->getDepth();
                if (!cache.findNumber(number))
                {
                    withCache += tree->getDepth();
                    cache.addNumber(number);
                }
                tree->resetDepth();
                if (character == '\n')
                    break;
            }

            std::cout << "NO CACHE: " << noCache << " CACHE: " << withCache << std::endl;
            break;
        }

        case 'U':
        {
            int size;
            std::cin >> size;
            CacheUpgrade cache(size);
            int number;
            char character;
            int noCache = 0;
            int withCache = 0;
            while (scanf("%d%c", &number, &character))
            {
                tree->search(tree->getRoot(), number);
                noCache += tree->getDepth();
                if (cache.findNumber(number) == -1)
                {
                    withCache += tree->getDepth();
                    cache.addNumber(number);
                }
                else
                {
                    cache.upgradeHeat(cache.findNumber(number));
                }
                cache.decrementHeat();
                tree->resetDepth();
                if (character == '\n')
                    break;
            }

            std::cout << "NO CACHE: " << noCache << " CACHE: " << withCache << std::endl;
            break;
        }
        }

        std::cin>>operation;
    }
}