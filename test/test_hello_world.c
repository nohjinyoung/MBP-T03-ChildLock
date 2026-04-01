#include <assert.h>
#include <agent.h>

void test_addition() {
    assert(1 + 1 == 2);
}

void test_subtraction() {
    assert(2 - 1 == 1);
}

int main() {
    agent_run(test_addition);
    agent_run(test_subtraction);
    return 0;
}