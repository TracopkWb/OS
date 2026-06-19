#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Node
{
    char *name;
    int numChildren;
    struct Node *children[10];
} Node;

void createProcessTree(Node *node)
{
    printf("%s PID=%d PPID=%d\n",
           node->name,
           getpid(),
           getppid());

    sleep(20);

    for (int i = 0; i < node->numChildren; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            createProcessTree(node->children[i]);
            return;
        }
    }

    for (int i = 0; i < node->numChildren; i++)
    {
        wait(NULL);
    }
}

int main()
{
    Node greatB1a = {"GreatGrandchild B1a", 0};
    Node greatB1b = {"GreatGrandchild B1b", 0};

    Node grandA1 = {"Grandchild A1", 0};
    Node grandA2 = {"Grandchild A2", 0};

    Node grandB1 = {"Grandchild B1", 2, {&greatB1a, &greatB1b}};

    Node childA = {"Child A", 2, {&grandA1, &grandA2}};

    Node childB = {"Child B", 1, {&grandB1}};

    Node root = {"Parent", 2, {&childA, &childB}};

    createProcessTree(&root);

    return 0;
}