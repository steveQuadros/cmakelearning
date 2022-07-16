#include <iostream>
#include <folly/fibers/async/Async.h>
#include <folly/fibers/async/WaitUtils.h>

using namespace folly::fibers::async;

Async<std::string> foo() {
    return "testing";
}

int main(int argc, char** argv) {
    auto msg = executeOnFiberAndWait([]() -> Async<std::string> {
        return await(foo());
    });
    std::cout << "Hello World " << msg << std::endl;
}